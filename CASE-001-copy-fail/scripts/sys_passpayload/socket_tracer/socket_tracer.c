/*
*   - intention (fluff section)
*           - When I use `crash vmlinux` command,
*           - It takes so much waiting time + manually go struct and extracting time.
*           - So that's how I started writing this module.
*           - This is fragile across kernel versions. 
*           - But we can make it highly configurable. 
*           - And it's saved many times.
*
*           - But I just wonder this module developing time cost is almost every time higher than running `crash vmlinux` command 20 times?😁
*
*           - So anyway, this module is for my research project, and I think it's not a waste at all.
*
*   - Supporting linux kernel versions:
*        - Target to support at least 6.0 to upper.
*
*   - Tested linux kernel version:
*       - 6.17.0
*   
*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/moduleparam.h>
#include <linux/kstrtox.h>
#include <linux/sched.h>
#include <linux/err.h>
#include <linux/fs.h>
#include <linux/net.h>
#include <linux/fdtable.h>
#include <linux/pid.h>
#include <linux/rcupdate.h>
#include <linux/sched/task.h>
#include <linux/atomic/atomic-instrumented.h>
#include <linux/stat.h>
#include <linux/file.h>
#include <net/sock.h>
#include <linux/version.h>
#include <linux/pid_namespace.h>
#include <linux/file_ref.h>

/*
*   ST_SUPPORT: The linux kernel version guard.
*
*   Arguments:
*   @W: comparison operators(ex: '<', '>', '>=', '<=', '==')
*   @X: Major kernel version
*   @Y: Minor kernel version
*   @Z: Patch/Revision level
*
*   Example usage: #if(ST_SUPPORT(>, 6, 17, 0))
*/
#define ST_SUPPORT(W, X, Y, Z) (LINUX_VERSION_CODE W KERNEL_VERSION(X, Y, Z))

// negative values act as a defensive guard whenever the user attempts to load a module without parameters.
static pid_t pid = -1;
static int fd = -1;

MODULE_PARM_DESC(pid, "Should be pass the valid process id.");
MODULE_PARM_DESC(fd, "Valid file descripter");

// negative values prohibited
static int param_set_fd_and_pid(const char *val, const struct kernel_param *kp){
    int my_val = -1, ret = -1, base = 10;

    ret = kstrtoint(val, base, &my_val);
    if(ret < 0){
        return ret;
    }

    if(my_val < 0){
        return -EINVAL;
    }

    return param_set_int(val, kp);
}

static const struct kernel_param_ops my_fd_and_pid_param_ops = {
    .set = param_set_fd_and_pid,
    .get = param_get_int,
};

module_param_cb(fd, &my_fd_and_pid_param_ops, &fd, 0);
module_param_cb(pid, &my_fd_and_pid_param_ops, &pid, 0);

static int __init init_func(void){

    // internal kernel structures
    struct task_struct *st_task_struct = NULL;
    struct pid *st_pid = NULL;
    struct pid_namespace *st_ns = NULL;
    struct files_struct *st_files = NULL;
    struct fdtable *st_fdt = NULL;
    struct file *st_file = NULL;
    struct socket *st_socket = NULL;
    struct sock *st_sock = NULL;
    struct proto_ops *st_ops = NULL;
    struct module *st_module = NULL;
    static int ret = -ENOENT;

    // display warning about versions
    #if(ST_SUPPORT(<, 6, 0, 0))
    pr_warn("This module will break on this kernel. The supported range is 6.0+\n"); 
    #endif

    #if (ST_SUPPORT(>, 6, 5, 0))
        scoped_guard(rcu){
    #else
        rcu_read_lock();
    #endif

    st_pid = find_vpid(pid);
    if(!st_pid){
        pr_err("PID structure not found for the given process! \n");

        #if (!ST_SUPPORT(>, 6, 5, 0))
            rcu_read_unlock();
        #endif

        return -ESRCH;
    }

    st_task_struct = pid_task(st_pid, PIDTYPE_PID);
    if(!st_task_struct){
        pr_err("The process could not be found with the PID provided by the user. \n");

        #if (!ST_SUPPORT(>, 6, 5, 0))
            rcu_read_unlock();
        #endif

        return -ESRCH;
    }
    get_task_struct(st_task_struct);

    st_ns = task_active_pid_ns(st_task_struct);
    if(!st_ns){
        pr_err("Pid namespace not found! \n");

        #if (!ST_SUPPORT(>, 6, 5, 0))
            rcu_read_unlock();
        #endif

        return -ENOENT;
    }
    if(pid > st_ns->pid_max){
        pr_err("Invalid pid number! \n");

        #if (!ST_SUPPORT(>, 6, 5, 0))
            rcu_read_unlock();
        #endif

        return -EINVAL;
    }

    #if (ST_SUPPORT(>, 6, 5, 0))
        }
    #else
        rcu_read_unlock();
    #endif

    task_lock(st_task_struct);
    st_files = (struct files_struct *)st_task_struct->files;
    if(likely(st_files)){
        // I didn't find a proper API to match kernel 6.17.0, I think I missed it.
        if(!(atomic_inc_not_zero(&st_files->count))){ 
            st_files = NULL;
        }
    }
    task_unlock(st_task_struct);
    
    if(!st_files){
        pr_err("Failed to get a pointer to given files struct! \n");

        goto cls_task;
    }

    #if (ST_SUPPORT(>, 6, 5, 0))
        scoped_guard(rcu){
    #else
        rcu_read_lock();
    #endif

    st_fdt = (struct fdtable *)files_fdtable(st_files);
    if(unlikely(!st_fdt)){ // need test with bytecode, 
        pr_err("Failed to get a pointer to given fd table! \n");

        #if (!ST_SUPPORT(>, 6, 5, 0))
            rcu_read_unlock();
        #endif

        goto cls_files;
    }

    // protect from out of bound memory read
    if(fd >= st_fdt->max_fds){
        pr_err("Invalid file descripter! \n");

        #if (!ST_SUPPORT(>, 6, 5, 0))
            rcu_read_unlock();
        #endif

        goto cls_files;
    }

    /*
    *   We can't use fget here. Because fget internally uses the current macro.
    *   So we need someone else's file ref count increment. Not our process.
    *   So that's why we can't use fget here.
    *
    *   But fput focuses on the given file ref count decrement. So that's why we use fput.
    */
    st_file =  (struct file *)rcu_dereference(st_fdt->fd[fd]);
    if(st_file){
        // need version guard
        #if(ST_SUPPORT(>=,6, 13, 0))
            if(!(file_ref_get(&st_file->f_ref))){
                st_file = NULL;
            }
        #else
            atomic_long_inc(&st_file->f_count); // kernel 6.13 this f_count changes to f_ref
        #endif
    }

    #if (ST_SUPPORT(>, 6, 5, 0))
        }
    #else
        rcu_read_unlock();
    #endif

    if(!st_file){
        pr_err("Failed to get a pointer to given file! \n");

        goto cls_files;
    }

    if(S_ISSOCK(st_file->f_inode->i_mode)){

        st_socket  = sock_from_file(st_file);
        if(!st_socket){
            pr_err("Failed to get a pointer to given socket! \n");

            goto cls_file;
        }

        lock_sock(st_socket->sk);
        st_sock = (struct sock *)st_socket->sk;
        if(st_sock){
            sock_hold(st_sock);
        }
        release_sock(st_socket->sk);

        if(!st_sock){
            pr_err("Failed to get a pointer to given socket! \n");

            goto cls_file;
        }

        st_ops = (struct proto_ops *)st_socket->ops;
        if(!st_ops){
            pr_err("Failed to get a pointer to given ops table! \n");

            goto cls_sock;
        }

        #if (ST_SUPPORT(>, 6, 5, 0))
            scoped_guard(rcu){
        #else
            rcu_read_lock();
        #endif

        st_module = (struct module *)st_ops->owner;
        if(st_module){
            if(!(try_module_get(st_module))){
                st_module = NULL;
            }
        }

        #if (ST_SUPPORT(>, 6, 5, 0))
            }
        #else
            rcu_read_unlock();
        #endif
        if(!st_module){
            pr_info("Module not found! \n");

            goto cls_sock;
        }

        // Configure whatever you need
        pr_info("Socket state: %d \n", st_socket->state);
        pr_info("Socket type: %d \n", st_socket->type);
        pr_info("Socket flags: %lu \n", st_socket->flags);

        //proto_ops
        pr_info("Socket family: %d \n", st_ops->family);

        pr_info("Module owner: %s \n", st_module->name);

        ret = 0;    
        goto cls_module;
    }else{
        goto cls_file;
    }

cls_module:
    module_put(st_module);
    st_module = NULL;

cls_sock:
    sock_put(st_sock);
    st_sock = NULL;

cls_file:
    fput(st_file);
    st_file = NULL;

cls_files:
    atomic_dec(&st_files->count);
    st_files = NULL;

cls_task:
    put_task_struct(st_task_struct);
    st_task_struct = NULL;

    return ret;
}

static void __exit exit_func(void){
    pr_info("Module unloaded!\n");
}

// metadata
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ravindu Priyankara");
MODULE_DESCRIPTION("Fragile Socket tracer..😁");
MODULE_VERSION("1.0");

// init & exit registration
module_init(init_func);
module_exit(exit_func);