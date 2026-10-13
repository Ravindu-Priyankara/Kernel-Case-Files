#ifndef OVERTHINKER_COMMON_HELPERS_H
#define OVERTHINKER_COMMON_HELPERS_H

#include "header.h"

static __always_inline void update_error_stats(__u32 error_id){

    if(error_id >= MAX_ERRORS)
        return;

    __u64 *value = bpf_map_lookup_elem(&error_stats, &error_id);
    if(!value)
        return;

    /*
    *   - for future me:
    * 
    *   - If I increment the value like this `*value += 1`,
    *   - It takes 3 steps. Look at this
    *
    *   xlated view
    *       *value += 1;
    *       16: (79) r1 = *(u64 *)(r0 +0)
    *       17: (07) r1 += 1
    *       18: (7b) *(u64 *)(r0 +0) = r1
    *
    *   jited view
    *       *value += 1;
    *       56:	movq	(%rax), %rdi
    *       5a:	addq	$1, %rdi
    *       5e:	movq	%rdi, (%rax)
    *
    *   Simply, it means,
    *       1. read the value
    *       2. increment the value(write)
    *       3. update the value
    *
    *   assumptions
    *       1. The document says PERCPU-ARRAY prevents multicore races.
    *       2. But imagine this scenario
    *
    *       - in CPU0
    *       - execute probe A
    *       - probe A reads value
    *       - interrupt happens
    *       - probe B executes <= imagine some stupid person attaches a hook to the interrupt context, maybe his name, starting from R.
    *       - probe B is also doing arithmetic 
    *       - probe B exits
    *       - probe A continues
    *       - probe A is doing arithmetic
    *       - but now we miss 1 value
    *
    *   All happen on CPU0, not a multi-thread issue.
    *   So, to save my neck, I choose to add an atomic fetch-and-add.
    *
    *   Now the gap is tighter; look at the assembly. 
    *   But....... without real data, assuming everything is true, we call it religion.
    *
    *   Final decision.
    *       - Who cares if I put atomic or just arithmetic in my code?
    *       - This is just POC code. 
    *
    *   choice is yours
    *
    *   Now you know why I named this program 'Overthinker'. Isn't it fair?
    *
    *   Reference:
    *       - https://docs.ebpf.io/linux/concepts/concurrency/
    *       - https://docs.kernel.org/bpf/map_array.html
    */
    //*value += 1;
    __sync_fetch_and_add(value, 1);
    /*
    *   After atomic:
    *
    *   xlated view
    *   17: (db) r1 = atomic64_fetch_add((u64 *)(r0 +0), r1)
    *
    *   jited view
    *   5b:	lock
    *   5c:	xaddq	%rdi, (%rax)
    */
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