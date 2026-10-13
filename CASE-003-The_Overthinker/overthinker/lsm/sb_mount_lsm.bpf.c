#include "header.h"
#include "common_helpers.h"


#if ENABLE_SB_MOUNT_ENFORCEMENT

SEC("lsm/sb_mount")
int BPF_PROG(my_sb_mount, const char *dev_name, const struct path *path,
    const char *type, unsigned long flags, void *data){

        struct ino_key my_ino_key = {0};
        struct event *my_event = NULL;
        struct inode *my_inode = NULL;
        struct dentry *current_parent = NULL;
        struct dentry *next_parent = NULL;
        __u64 i_no = 0;
        __u32 my_sdev = 0;
        __u32 *value = NULL;
        __u32 tgid = 0;
        int ret = -1;

        my_event = bpf_ringbuf_reserve(&rb, sizeof(*my_event), 0);
        if(!my_event){
            #if ERROR_MATRIX
            update_error_stats(ERR_RINGBUF_RESERV);
            #endif
            goto after_ringbuf;
        }

        // prevent data leak
        __builtin_memset(my_event, 0, sizeof(*my_event));

        tgid = bpf_get_current_pid_tgid() >> 32;
        // remove unlikely macro because i think init can modu_load
        if(unlikely(tgid == 0) || tgid == 1){
            #if ERROR_MATRIX
            update_error_stats(ERR_SWAPPER_OR_INIT_PROCESS_ACCESS_FINIT_MODULE);
            #endif
        }

        my_event->pid = tgid;

        if(bpf_get_current_comm(&my_event->comm, sizeof(my_event->comm)) < 0){
            #if ERROR_MATRIX
            update_error_stats(ERR_COMM);
            #endif
            __builtin_memcpy(&my_event->comm, "Unknown!", sizeof("Unknown!"));
        }

after_ringbuf:
        if(!path){
            data_transfer_to_userland(my_event, EVT_PATH_NOT_FOUND, 
                SEV_BLOCK, ERR_PATH_NOT_FOUND);

            return -EPERM;
        }

        current_parent = BPF_CORE_READ(path, dentry, d_parent);
        if(!current_parent){
            data_transfer_to_userland(my_event, EVT_PARENT_DIR_NOT_FOUND, 
                SEV_BLOCK, ERR_PARENT_DIR_NOT_FOUND);
            return -EPERM;
        }

        // next iteration need optimized this
        #pragma unroll
        for(int i = 0; i < DIR_DEPTH; i++){

            if(i == 0){
                my_inode = BPF_CORE_READ(path, dentry, d_inode);
                if(!my_inode){
                    data_transfer_to_userland(my_event, EVT_FAILED_TO_GET_INODE, 
                        SEV_BLOCK, ERR_FAILED_TO_GET_INODE);

                    return -EPERM;
                }
            }
            if(i != 0){
                my_inode = BPF_CORE_READ(current_parent, d_inode);
                if(!my_inode){
                    data_transfer_to_userland(my_event, EVT_FAILED_TO_GET_INODE, 
                        SEV_BLOCK, ERR_FAILED_TO_GET_INODE);

                    return -EPERM;
                }
            }

            ret = BPF_CORE_READ_INTO(&i_no, my_inode, i_ino);
            if(ret < 0){
                data_transfer_to_userland(my_event, EVT_INODE_MODE_NOT_FOUND, 
                    SEV_BLOCK, ERR_INODE_MODE_NOT_FOUND);

                return -EPERM;
            }

            ret = BPF_CORE_READ_INTO(&my_sdev, my_inode, i_sb, s_dev);
            if(ret < 0){
                data_transfer_to_userland(my_event, EVT_FAILED_TO_GET_S_DEV, 
                    SEV_BLOCK, ERR_FAILED_TO_GET_S_DEV);

                return -EPERM;
            }

            my_ino_key.ino = i_no;
            my_ino_key.dev = my_sdev;

            value = bpf_map_lookup_elem(&trusted_dir_inode, &my_ino_key);
            if(value && *value == 1){
                data_transfer_to_userland(my_event, EVT_TRY_TO_MOUNT_RESTRICTED_PATH, 
                    SEV_BLOCK, ERR_TRY_TO_MOUNT_RESTRICTED_PATH);

                return -EPERM;
            }

            next_parent = BPF_CORE_READ(current_parent, d_parent);
            if(!next_parent){
                data_transfer_to_userland(my_event, EVT_PARENT_DIR_NOT_FOUND, 
                    SEV_BLOCK, ERR_PARENT_DIR_NOT_FOUND);

                return -EPERM;
            }

            if(next_parent == current_parent){
                goto cleanup;
            }

            /*
            *   Eww, I just spent two hours imagining why it behaves this way
            *
            *   First iteration =>  /usr/lib/modules/hello
            *   Second iteration => /usr/lib/
            *   Third iteration => /usr/
            *
            *   Did you notice that only once it goes back twice?
            *
            *   reason:
            *   If we forget to skip this part when i = 0, we get the parent twice; that's why 
            *   /usr/lib/modules/hello
            *   became 
            *   /usr/lib/
            *
            *   Debugging trick
            *
            *   - What you see first
            *
            *   1. Detection not triggered
            *   2. mm everyone knows the next step: just put some bpf_printk😂
            *   3. You will see i_ino , s_dev and iteration number
            *   4. The number never answers. This is where I struggle most: figuring out how to get the path using these numbers.
            *   5. Just simply use this command
            *       find / -inum <inode number> 2>/dev/null
            *
            *   6. Now you see the bug 
            *   7. After you understand the bug, it's just a few minutes' task.
            *
            *   Funny thing is.
            *   Writing new code: 10 minutes. 
            *   Figure out why that new code broke my detection: 1 hour and 55 minutes.😂
            */
            if(i != 0){
                current_parent = next_parent;
            }
            
        }

        /*
        *   Critical - If you never block, You have huge blindspot,
        *   But according to noice you should tune this limit.
        *   non match + so many subdirectories have
        */
        data_transfer_to_userland(my_event, EVT_EXCESSIVE_DEPTH, 
            SEV_BLOCK, ERR_EXCESSIVE_DEPTH);

        return -EPERM;

cleanup:
        if(my_event)
            bpf_ringbuf_discard(my_event, 0);

        return 0;

}

#endif

/*
*   command: sudo mount --bind /tmp/hello /lib/modules
*       |-> trigger mount syscall
*           |=> sys_mount()
*               |=> copy_mount_string(type)
*               |=> copy_mount_string(dev_name)
*               |=> copy_mount_options(data)
*               |=> do_mount()
*                   |=> path_mount()
*                       |=> security_sb_mount() <= this is the our lsm hook trigger point
*/