#include "header.h"
#include "common_helpers.h"

#if ENABLE_KERNEL_LOAD_DATA_ENFORCEMENT

SEC("lsm/kernel_load_data")
int BPF_PROG(my_kernel_load_data, enum kernel_load_data_id id, bool contents){
    if(id != LOADING_MODULE)
        return 0;

    struct event *my_event = NULL;
    __u32 tgid = 0;

    my_event = bpf_ringbuf_reserve(&rb, sizeof(*my_event), 0);
    if(!my_event){
        #if ERROR_MATRIX
        update_error_stats(ERR_RINGBUF_RESERV);
        #endif
        goto exit;
    }

    // prevent leaking memory to userland.
    __builtin_memset(my_event, 0, sizeof(*my_event)); 

    tgid = bpf_get_current_pid_tgid() >> 32;
    // remove unlikely macro because i think init can module load
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

    my_event->severity = SEV_BLOCK;
    my_event->event_id = EVT_LOAD_DATA;

    bpf_ringbuf_submit(my_event, 0);

    return -EPERM;

exit:
    if(my_event)
        bpf_ringbuf_discard(my_event, 0);
    return -EPERM;
}

#endif