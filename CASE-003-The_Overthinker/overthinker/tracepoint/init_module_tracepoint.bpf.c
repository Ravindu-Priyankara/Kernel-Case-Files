#include "header.h"
#include "common_helpers.h"

#if ENABLE_INIT_MODULE_TRACER

SEC("tracepoint/syscalls/sys_enter_init_module")
int my_init_module(struct trace_event_raw_sys_enter *ctx){
    struct event *my_event = NULL;
    __u32 tgid = 0;

    my_event = bpf_ringbuf_reserve(&rb, sizeof(*my_event), 0);
    if(!my_event){
        #if ERROR_MATRIX
        update_error_stats(ERR_RINGBUF_RESERV);
        #endif
        return 0;
    }

    // prevent leaking memory to userland.
    __builtin_memset(my_event, 0, sizeof(*my_event)); 

    tgid = bpf_get_current_pid_tgid()>>32;
    if(unlikely(tgid == 0) || tgid == 1){
        #if ERROR_MATRIX
        update_error_stats(ERR_SWAPPER_OR_INIT_PROCESS_ACCESS_FINIT_MODULE);
        #endif
        bpf_ringbuf_discard(my_event, 0);
        return 0;
    }

    my_event->pid = tgid;

    if(bpf_get_current_comm(&my_event->comm, sizeof(my_event->comm)) < 0){
        #if ERROR_MATRIX
        update_error_stats(ERR_COMM);
        #endif
        bpf_ringbuf_discard(my_event, 0);
        return 0;
    }

    my_event->severity = SEV_INFO;
    my_event->event_id = EVT_FINIT_MODULE;

    bpf_ringbuf_submit(my_event, 0);

    return 0;
}

#endif