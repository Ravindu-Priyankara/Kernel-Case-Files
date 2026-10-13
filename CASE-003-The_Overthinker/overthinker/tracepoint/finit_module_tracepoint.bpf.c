#include "header.h"
#include "common_helpers.h"

#if ENABLE_FINIT_MODULE_TRACER

SEC("tracepoint/syscalls/sys_enter_finit_module")
int my_finit_module(struct trace_event_raw_sys_enter *ctx){

    struct event *my_event = NULL;
    __u32 tgid = 0;

    /*
    *   If my code doesn't actively try to degrade my mental health 
    *   through an endless loop of compiler errors and screaming verifiers, 
    *   it's not mine.
    *   
    *   ; my_event->pid = tgid; @ finit_module_tracepoint.bpf.c:32
    *   38: (63) *(u32 *)(r6 +12) = r0
    *   invalid access to memory, mem_size=8 off=12 size=4
    *   R6 min value is outside of the allowed memory range
    *
    *   - root cause
    *       - I reserve 8 byte of memory and try to access offset 12,
    *       - verifier point
    *           - mem_size=8 off=12 size=4
    *       - Dont forget astric mark😁
    */
    my_event = bpf_ringbuf_reserve(&rb, sizeof(*my_event), 0);
    if(!my_event){
        #if ERROR_MATRIX
        update_error_stats(ERR_RINGBUF_RESERV);
        #endif

        return 0;
    }

    // prevent leaking memory to userland.
    __builtin_memset(my_event, 0, sizeof(*my_event)); 

    tgid = bpf_get_current_pid_tgid() >> 32;
    if(unlikely(tgid == 0) || tgid == 1){
        #if ERROR_MATRIX
        update_error_stats(ERR_SWAPPER_OR_INIT_PROCESS_ACCESS_FINIT_MODULE);
        #endif

        /*
        *   Sanity issue
        *
        *   Verifier doesn't just point out syntax errors anymore. 
        *   It looks at my logic, sighs, and asks if I've slept in the last 48 hours.
        *
        *   58: (b4) w0 = 0                       ; R0_w=0 refs=2
        *   59: (95) exit
        *   Unreleased reference id=2 alloc_insn=4
        *   BPF_EXIT instruction in main prog would lead to reference leak
        *
        *   Dont forget to discard reserved ring buffer sample
        */
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