#include "header.h"
#include "common_helpers.h"

#if ENABLE_KERNEL_READ_FILE_ENFORCEMENT

SEC("lsm/kernel_read_file")
int BPF_PROG(my_kernel_read_file, struct file *file, enum kernel_read_file_id id, bool contents){
    if(id != READING_MODULE)
        return 0;

    struct event *my_event = NULL;
    struct inode *my_inode = NULL;
    struct dentry *current_parent = NULL;
    struct dentry *next_parent = NULL;
    struct super_block *my_super_block = NULL;
    __u64 i_no = 0;
    __u32 s_dev = 0;
    __u32 tgid = 0;
    __u32 uid = 1000; // not zero for ya
    int ret = -1;
    __u16 mode = 0;

    /*
    *   Another sanity issue,
    *
    *   need = void *ringbuf, {&rb}
    *   but put = event *my_event, 
    *
    *   ; my_event = bpf_ringbuf_reserve(my_event, sizeof(*my_event), 0); @ kernel_read_file_lsm.bpf.c:16
    *   4: (b7) r1 = 0                        ; R1_w=0
    *   5: (b7) r2 = 24                       ; R2_w=24
    *   6: (b7) r3 = 0                        ; R3_w=0
    *   7: (85) call bpf_ringbuf_reserve#131
    *   R1 type=scalar expected=map_ptr
    *
    */
    my_event = bpf_ringbuf_reserve(&rb, sizeof(*my_event), 0);
    if(!my_event){
        // What if ringbuf reserve fails? Use the error matrix, but never, ever return EPERM for ringbuf failures.
        #if ERROR_MATRIX
        update_error_stats(ERR_RINGBUF_RESERV);
        #endif
        goto after_ringbuf;
    }

    /*
    *   prevent leaking memory to userland.
    *
    *   Mmm,thanks god compiler never remove it
    *
    *   Xlated,
    *
    *    __builtin_memset(my_event, 0, sizeof(*my_event)); 
    *   32: (63) *(u32 *)(r7 +20) = r1
    *   33: (63) *(u32 *)(r7 +16) = r1
    *   34: (63) *(u32 *)(r7 +12) = r1
    *   35: (63) *(u32 *)(r7 +8) = r1
    *   36: (63) *(u32 *)(r7 +4) = r1
    *   37: (63) *(u32 *)(r7 +0) = r1
    *
    *   Jited
    *
    *   ; __builtin_memset(my_event, 0, sizeof(*my_event)); 
    *   a5:	movl	%edi, 20(%r13)
    *   a9:	movl	%edi, 16(%r13)
    *   ad:	movl	%edi, 12(%r13)
    *   b1:	movl	%edi, 8(%r13)
    *   b5:	movl	%edi, 4(%r13)
    *   b9:	movl	%edi, (%r13)
    *
    *   4 bytes write (4 bytes x 6 times, thats how this write our 24 bytes of memory)
    */
    __builtin_memset(my_event, 0, sizeof(*my_event)); 

    tgid = bpf_get_current_pid_tgid() >> 32;
    // remove unlikely macro because i think init can module load
    if(unlikely(tgid == 0) || tgid == 1){
        #if ERROR_MATRIX
        update_error_stats(ERR_SWAPPER_OR_INIT_PROCESS_ACCESS_FINIT_MODULE);
        #endif
        // no return
    }

    my_event->pid = tgid;

    if(bpf_get_current_comm(&my_event->comm, sizeof(my_event->comm)) < 0){
        #if ERROR_MATRIX
        update_error_stats(ERR_COMM);
        #endif
        /*
        *   Make sure you clear the comm.
        *   Otherwise, you are leaking 7 bytes of data from the kernel.
        *
        *   And its byte store but im not gonna change that because look at this I closed pr
        *       - https://github.com/falcosecurity/libs/pull/3026
        *
        *    __builtin_memcpy(&my_event->comm, "Unknown!", sizeof("Unknown!"));
        *   85: (73) *(u8 *)(r8 +8) = r1
        *   86: (b7) r1 = 33
        *   87: (73) *(u8 *)(r8 +7) = r1
        *   88: (b7) r1 = 119
        *   89: (73) *(u8 *)(r8 +5) = r1
        *   90: (b7) r1 = 111
        *   91: (73) *(u8 *)(r8 +4) = r1
        *   92: (b7) r1 = 107
        *   93: (73) *(u8 *)(r8 +2) = r1
        *   94: (b7) r1 = 110
        *   95: (73) *(u8 *)(r8 +6) = r1
        *   96: (73) *(u8 *)(r8 +3) = r1
        *   97: (73) *(u8 *)(r8 +1) = r1
        *   98: (b7) r1 = 85
        *   99: (73) *(u8 *)(r8 +0) = r1
        *   100: (b4) w1 = 2
        *
        *   lesson is very simple: never try to outsmart the compiler when it's ring buffer memory.
        */
        __builtin_memcpy(&my_event->comm, "Unknown!", sizeof("Unknown!"));
    }

after_ringbuf:
    if(unlikely(!file)){
        data_transfer_to_userland(my_event, EVT_FILE_NOT_FOUND, 
            SEV_BLOCK, ERR_FILE_NOT_FOUND);

        return -EPERM;
    }


/*
*   These checks are highly bypassable. 
*   But the goal is not to stop attackers; the goal is to fail more often and log every failure.
*   This gives defenders more information and more behavioral analysis of attacks.
*/

    /*
    *   - TOCTOU gap
    *       - Can't change a file while we read file permissions and owner?
    *
    *   My assumption:
    *       - There was a gap.
    *       - But actually, beyond that gap, there was a real practical issue.
    *       - look,
    *           1. To load a kernel module, an attacker needs root permission.
    *           2. If an attacker has root permission, the attacker can change the file owner and permissions.
    *
    *       - To address the TOCTOU gap, we can add parent-folder permission and ownership checks.
    *
    *       - But as I said earlier,
    *       - If the attacker has root permission, this means it is nothing for him.
    *
    *       - So the goal is not to stop all attacks; it is to raise the price 
    */
    my_inode = BPF_CORE_READ(file, f_inode);
    if(!my_inode){
        data_transfer_to_userland(my_event, EVT_FAILED_TO_GET_INODE, 
            SEV_BLOCK, ERR_FAILED_TO_GET_INODE);

        return -EPERM;
    }

    // never try to use BPF_CORE_READ,
    // because helper failed you will see uid = 0
    // so it means root
    ret = BPF_CORE_READ_INTO(&uid, my_inode, i_uid.val); 
    if(ret < 0){
        data_transfer_to_userland(my_event, EVT_FAILED_TO_GET_FILE_UID, 
            SEV_BLOCK, ERR_FAILED_TO_GET_FILE_UID);

        return -EPERM;
    }

    if(uid != 0){
        data_transfer_to_userland(my_event, EVT_ROOT_NOT_OWN_THIS_FILE, 
            SEV_BLOCK, ERR_ROOT_NOT_OWN_THIS_FILE);

        return -EPERM;
    } // end of the file permission check

    // add script kiddi filter😁
    // Happy kitty, sleepy kitty, purr, purr, purr
    mode = BPF_CORE_READ(my_inode, i_mode);
    if(mode == 0){
        data_transfer_to_userland(my_event, EVT_INODE_MODE_NOT_FOUND, 
            SEV_BLOCK, ERR_INODE_MODE_NOT_FOUND);

        return -EPERM;
    }

    if(mode & 0022){
        data_transfer_to_userland(my_event, EVT_UNSAFE_WRITE_PERMISSION, 
            SEV_BLOCK, ERR_UNSAFE_WRITE_PERMISSION);

        return -EPERM;
    }

    // folder permission check
    current_parent = BPF_CORE_READ(file, f_path.dentry, d_parent);
    if(!current_parent){
        data_transfer_to_userland(my_event, EVT_PARENT_DIR_NOT_FOUND, 
            SEV_BLOCK, ERR_PARENT_DIR_NOT_FOUND);

        return -EPERM;
    }

    my_inode = BPF_CORE_READ(current_parent, d_inode);
    if(!my_inode){
        data_transfer_to_userland(my_event, EVT_FAILED_TO_GET_INODE, 
            SEV_BLOCK, ERR_FAILED_TO_GET_INODE);

        return -EPERM;
    }

    ret = BPF_CORE_READ_INTO(&uid, my_inode, i_uid.val);
    if(ret < 0){
        data_transfer_to_userland(my_event, EVT_FAILED_TO_GET_FOLDER_UID, 
            SEV_BLOCK, ERR_FAILED_TO_GET_FOLDER_UID);

        return -EPERM;
    }

    if(uid != 0){
        data_transfer_to_userland(my_event, EVT_ROOT_NOT_OWN_THIS_FOLDER, 
            SEV_BLOCK, ERR_ROOT_NOT_OWN_THIS_FOLDER);

        return -EPERM;
    }

    /*
    *   The Verifier and Scalar are such a sweet couple! 
    *   Scalar’s favorite thing in the world is an invalid mem access.
    *   so every time I hit one, the Verifier screams, 
    *   'Scalar, sweetie, come look at what this stupid developer did now!'
    *
    *   ; mode = my_inode->i_mode; @ kernel_read_file_lsm.bpf.c:431
    *   904: (69) r1 = *(u16 *)(r7 +0)
    *   R7 invalid mem access 'scalar'
    *
    *   Dont forget to use helper
    *   Because when pointer dereferenc developer trust it
    *   But verifier doesnt.
    */
    mode = BPF_CORE_READ(my_inode, i_mode);
    if(mode == 0){
        data_transfer_to_userland(my_event, EVT_INODE_MODE_NOT_FOUND, 
            SEV_BLOCK, ERR_INODE_MODE_NOT_FOUND);

        return -EPERM;
    }

    if(mode & 0022){
        data_transfer_to_userland(my_event, EVT_UNSAFE_WRITE_PERMISSION, 
            SEV_BLOCK, ERR_UNSAFE_WRITE_PERMISSION);

        return -EPERM;
    }

    /*
    *   - Top priority and final checkpoint
    *   - Put this last, you will get more info.
    *   - We follow the strict rules here; every failure = block.
    */
    current_parent = BPF_CORE_READ(file, f_path.dentry, d_parent);
    if(!current_parent){
        data_transfer_to_userland(my_event, EVT_PARENT_DIR_NOT_FOUND, 
            SEV_BLOCK, ERR_PARENT_DIR_NOT_FOUND);

        return -EPERM;
    }

    // loop 8 times with prag,a unroll
    #pragma unroll
    for(int i = 0; i < DIR_DEPTH; i++){ // put 8 to macro

        struct ino_key my_ino_key = {0};

        my_super_block = BPF_CORE_READ(current_parent, d_inode, i_sb);
        if(!my_super_block){
            data_transfer_to_userland(my_event, EVT_FAILED_TO_EXTRACT_SUPER_BLOCK, 
                SEV_BLOCK, ERR_FAILED_TO_EXTRACT_SUPER_BLOCK);

            return -EPERM;
        }

        ret = BPF_CORE_READ_INTO(&i_no, current_parent, d_inode, i_ino);
        if(ret < 0){
            data_transfer_to_userland(my_event, EVT_FAILED_TO_GET_INODE_NUMBER, 
                SEV_BLOCK, ERR_FAILED_TO_GET_INODE_NUMBER);

            return -EPERM;
        }

        ret = BPF_CORE_READ_INTO(&s_dev,my_super_block, s_dev);
        if(ret < 0){
            data_transfer_to_userland(my_event, EVT_FAILED_TO_GET_S_DEV, 
                SEV_BLOCK, ERR_FAILED_TO_GET_S_DEV);

            return -EPERM;
        }

        my_ino_key.ino = i_no;
        my_ino_key.dev = s_dev;

        /*
        *   Benifits:
        *       - If I compare path strings, it runs O(N) times.
        *       -  because it totally depends on path length.
        *       - But now we check it O(1) times.
        *       - no byte-by-byte check, just one check and decide success or failure; that's it.
        */
        __u32 *value = bpf_map_lookup_elem(&trusted_dir_inode, &my_ino_key);
        if(value && *value == 1)
            goto cleanup;

        next_parent = BPF_CORE_READ(current_parent, d_parent);
        if(!next_parent){
            data_transfer_to_userland(my_event, EVT_PARENT_DIR_NOT_FOUND, 
                SEV_BLOCK, ERR_PARENT_DIR_NOT_FOUND);

            return -EPERM;
        }

        if(current_parent == next_parent){
            data_transfer_to_userland(my_event, EVT_NON_WHITELIST_PATH, 
                SEV_BLOCK, ERR_NON_WHITELIST_PATH);

            return -EPERM;
        }

        current_parent = next_parent;
    } // end of the top priority check

     /*
    *   Critical - If you never block, You have huge blindspot,
    *   But according to noice you should tune this limit.
    *   non match + so many subdirectories have
    */
    data_transfer_to_userland(my_event, EVT_EXCESSIVE_DEPTH, 
        SEV_BLOCK, ERR_EXCESSIVE_DEPTH);

    return -EPERM;

    // cleanup
cleanup:
    if(my_event)
        bpf_ringbuf_discard(my_event, 0);

    return 0;
}

#endif

/*
Observation

1. /lib/modules = i_ino: 944151, dev: 265289730
2. /another folder = i_ino: 656643, dev: 265289730
3. /lib/modules to my my own module = i_ino: 921464, dev: 265289730
*/

// read assembly and optimize this before release, that is must