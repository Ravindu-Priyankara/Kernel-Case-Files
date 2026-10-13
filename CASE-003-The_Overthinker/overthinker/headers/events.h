//shared header
#ifndef OVERTHINKER_EVENTS_H
#define OVERTHINKER_EVENTS_H

#define COMM_SIZE 16

struct event {
    __u32 pid;
    __u8 severity;
    /*
    *   used for allignment
    *   But it's dangerous if you never clean it before passing it to userland.
    *   Every ringbuf event you pass leaks 1 byte of memory from the kernel.
    */
    __u8 reserved;
    __u16 event_id;
    char comm[COMM_SIZE];
};

_Static_assert(sizeof(struct event) == 24, "ERROR: event struct should be 24 bytes!");
_Static_assert(offsetof(struct event, event_id) == 6, "ERROR: event_id must be at offset 7!");

#endif