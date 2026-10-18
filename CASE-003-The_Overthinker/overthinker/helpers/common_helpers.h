#ifndef OVERTHINKER_COMMON_HELPERS_H
#define OVERTHINKER_COMMON_HELPERS_H

#include "header.h"

static __always_inline void update_error_stats(__u32 error_id){

    if(error_id >= MAX_ERRORS)
        return;

    __u64 *value = bpf_map_lookup_elem(&error_stats, &error_id);
    if(!value)
        return;
    __sync_fetch_and_add(value, 1);
}

static __always_inline void data_transfer_to_userland(struct event *my_event,
     __u16 EVT_HEADER, __u8 SEVERITY, __u32 ERR_HEADER){

        if(EVT_HEADER > EVT_MAX || SEVERITY > SEV_BLOCK || ERR_HEADER > MAX_ERRORS)
            return;
        /*
        *   Scalar, oh my darling😂
        *
        *   ; my_event->event_id = EVT_HEADER; @ common_helpers.h:93
        *   111: (6b) *(u16 *)(r6 +6) = r1
        *   R6 invalid mem access 'scalar'
        *
        *   Mmmm, forget to check my_event is valid!
        */
        if(my_event){
            my_event->severity = SEVERITY;
            my_event->event_id = EVT_HEADER;
            bpf_ringbuf_submit(my_event, 0);
        }

        #if ERROR_MATRIX
        update_error_stats(ERR_HEADER);
        #endif
}

#endif