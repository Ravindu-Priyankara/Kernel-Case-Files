#include "header.h"
#include "common_helpers.h"

#if ENABLE_FILE_OPEN_ENFORCEMENT

SEC("lsm/file_open")
int BPF_PROG(my_file_open, struct file *file){

    struct ino_key my_ino_key = {0};
    struct event *my_event = NULL;
    struct dentry *current_parent = NULL;
    struct dentry *next_parent = NULL;
    __u32 *value = NULL;
    __u64 i_no = 0;
    __u32 my_sdev = 0;
    __u32 tgid = 0;
    __u32 file_flags;
    int ret;

    my_event = bpf_ringbuf_reserve(&rb, sizeof(*my_event), 0);
    if(!my_event){
        #if ERROR_MATRIX
        update_error_stats(ERR_RINGBUF_RESERV);
        #endif
        goto after_ringbuf;
    }

    __builtin_memset(my_event, 0, sizeof(*my_event));

    tgid = bpf_get_current_pid_tgid() >> 32;
    // remove unlikely macro because I think init can file write
    if(unlikely(tgid == 0) || tgid == 1){
        #if ERROR_MATRIX
        update_error_stats(ERR_SWAPPER_OR_INIT_PROCESS_ACCESS_FINIT_MODULE);
        #endif
    }

    if(bpf_get_current_comm(&my_event->comm, sizeof(my_event->comm)) < 0){
        #if ERROR_MATRIX
        update_error_stats(ERR_COMM);
        #endif

        __builtin_memcpy(&my_event->comm, "Unknown!", sizeof("Unknown!"));
    }

after_ringbuf:
    if(unlikely(!file)){
        data_transfer_to_userland(my_event, EVT_FILE_NOT_FOUND, 
            SEV_BLOCK, ERR_FILE_NOT_FOUND);

        return -EPERM;
    }

    current_parent = BPF_CORE_READ(file, f_path.dentry, d_parent);
    if(!current_parent){
        data_transfer_to_userland(my_event, EVT_PARENT_DIR_NOT_FOUND, 
            SEV_BLOCK, ERR_PARENT_DIR_NOT_FOUND);

        return -EPERM;
    }

    #pragma unroll
    for(int i = 0; i < DIR_DEPTH; i++){
        ret = BPF_CORE_READ_INTO(&i_no, current_parent, d_inode, i_ino);
        if(ret < 0){
            data_transfer_to_userland(my_event, EVT_INODE_MODE_NOT_FOUND, 
                SEV_BLOCK, ERR_INODE_MODE_NOT_FOUND);

            return -EPERM;
        }

        ret = BPF_CORE_READ_INTO(&my_sdev, current_parent, d_inode, i_sb, s_dev);
        if(ret < 0){
            data_transfer_to_userland(my_event, EVT_FAILED_TO_GET_S_DEV, 
                SEV_BLOCK, ERR_FAILED_TO_GET_S_DEV);

            return -EPERM;
        }

        my_ino_key.ino = i_no;
        my_ino_key.dev = my_sdev;

        value = bpf_map_lookup_elem(&trusted_dir_inode, &my_ino_key);
        if(value && *value == 1){
            goto perm_check;
        }

        next_parent = BPF_CORE_READ(current_parent, d_parent);
        if(!next_parent){
            data_transfer_to_userland(my_event, EVT_PARENT_DIR_NOT_FOUND, 
                SEV_BLOCK, ERR_PARENT_DIR_NOT_FOUND);

            return -EPERM;
        }

        /*
        * Hmm, forget to release ringbuf memory and just put return 0;
        *
        *   ; if(next_parent == current_parent){ @ file_open_lsm.bpf.c:96
        *   642: (1d) if r1 == r9 goto pc+44 687: R0_w=0 R1_w=scalar(umin=1) 
        *   R6=ringbuf_mem(ref_obj_id=2,sz=24) R7=fp-40 R8=scalar(id=79) R9=scalar(id=78,umin=1) 
        *   R10=fp0 fp-8=mmmmscalar(id=81,smin=0,smax=umax=0xffffffff,var_off=(0x0; 0xffffffff)) fp-16=scalar(id=80) fp-24=mmmmmmmm 
        *   fp-32=mmmm???? fp-40=mmmmmmmm fp-48=mmmmmmmm fp-56=trusted_ptr_file() fp-64=scalar(id=53,umin=1) refs=2
        *   ; int BPF_PROG(my_file_open, struct file *file){ @ file_open_lsm.bpf.c:7
        *   687: (95) exit
        *   Unreleased reference id=2 alloc_insn=11
        *   BPF_EXIT instruction in main prog would lead to reference leak
        *
        */
        if(next_parent == current_parent){
            // not our target
            goto cleanup;
        }

        current_parent = next_parent;

    }

    /*
    *   Critical - If you never block, You have huge blindspot,
    *   But according to noice you should tune this limit.
    *   non match + so many subdirectories have
    */
    data_transfer_to_userland(my_event, EVT_EXCESSIVE_DEPTH, 
        SEV_BLOCK, ERR_EXCESSIVE_DEPTH);

    return -EPERM;

    // if path match do perm check
perm_check:
    ret = BPF_CORE_READ_INTO(&file_flags, file, f_flags);
    if(ret < 0){
        data_transfer_to_userland(my_event, EVT_FAILED_TO_GET_FILE_FLAGS, 
            SEV_BLOCK, ERR_FAILED_TO_GET_FILE_FLAGS);

        return -EPERM;
    }

    // doesnt care about file type
    if(file_flags && file_flags & (O_WRONLY | O_RDWR | O_CREAT)){
        data_transfer_to_userland(my_event, EVT_NO_PERM_TO_MODIFI_WHITELIST_PATH_HAS_DATA, 
            SEV_BLOCK, ERR_NO_PERM_TO_MODIFI_WHITELIST_PATH_HAS_DATA);

        return -EPERM; // eaccess also better error code.
    }

cleanup:
    if(my_event)
        bpf_ringbuf_discard(my_event, 0);

    // welcome others
    return 0;
}

#endif

/*
*   Tested commands:
*
*   1. sudo sh -c 'echo "test" > /lib/modules/test.txt'
*   2. sudo cp /bin/ls /lib/modules/ls_copy
*   3. sudo python3 -c "open('/lib/modules/test.py', 'w').write('test')"
*
*   Edge case:
*       - first "sduo touch /lib/modules/hello.c" => blocked
*       - second "sduo touch /lib/modules/hello.c" => no blocked
*           - but you cant write that created file
*       - I will show this on video proof
*
*   ex:
*       - run `sudo curl -L -o sample.jpg https://wikimedia.org`
*       - now it block
*       - but it create just empty file
*       - if you again run this it always block, 
*
*       - but in touch command it already success 
*       - because even block after also it create empty file
*       - you cant write but just empty file exsists
*
*/