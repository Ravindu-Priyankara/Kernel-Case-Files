#include "header.h"
#include "common_helpers.h"

#if ENABLE_MOVE_MOUNT_ENFORCEMENT

SEC("lsm/move_mount")
int BPF_PROG(my_move_mount, const struct path *from_path, const struct path *to_path){

    struct ino_key my_ino_key = {0};
    struct event *my_event = NULL;
    struct dentry *current_parent = NULL;
    struct dentry *next_parent = NULL;
    struct inode *my_inode = NULL;
    __u64 i_no = 0;
    __u32 my_sdev = 0;
    __u32 tgid = 0;
    __u32 *value = NULL;
    int ret = 0;

    my_event = bpf_ringbuf_reserve(&rb, sizeof(*my_event), 0);
    if(!my_event){
        #if ERROR_MATRIX
        update_error_stats(ERR_RINGBUF_RESERV);
        #endif

        goto after_ringbuf;
    }

    __builtin_memset(my_event, 0, sizeof(*my_event));

    tgid = bpf_get_current_pid_tgid() >> 32;
    // remove unlikely macro because i think init can file mount
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
    if(unlikely(!to_path)){
        data_transfer_to_userland(my_event, EVT_PATH_NOT_FOUND, 
            SEV_BLOCK, ERR_PATH_NOT_FOUND);

        return -EPERM;
    }

    // path->dentry->d_inode->i_ino;
    // path->dentry->d_inode->i_sb->s_dev;

    current_parent = BPF_CORE_READ(to_path, dentry, d_parent);
    if(!current_parent){
        data_transfer_to_userland(my_event, EVT_PARENT_DIR_NOT_FOUND, 
            SEV_BLOCK, ERR_PARENT_DIR_NOT_FOUND);

        return -EPERM;
    }

    #pragma unroll
    for(int i = 0; i < DIR_DEPTH; i++){

        if(i == 0){
            my_inode = BPF_CORE_READ(to_path, dentry, d_inode);
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