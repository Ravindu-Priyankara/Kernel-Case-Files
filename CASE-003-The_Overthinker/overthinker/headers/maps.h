#ifndef OVERTHINKER_MAPS_H
#define OVERTHINKER_MAPS_H

#include "flags.h"

/*
*   - Dev note:
*       - Array maps are preallocated at load time
*       - So lookup failure after never try to update it.
*/
struct {
    __uint(type, BPF_MAP_TYPE_PERCPU_ARRAY);
    __uint(max_entries, MAX_ERRORS);
    __type(key, __u32);
    __type(value, __u64);
}error_stats SEC(".maps");

struct {
    __uint(type, BPF_MAP_TYPE_RINGBUF);
    __uint(max_entries, 256 * 1024); // change the size after complete.
}rb SEC(".maps");

struct ino_key {
    __u64 ino;
    __u32 dev;
};

struct {
    __uint(type, BPF_MAP_TYPE_HASH);
    __uint(max_entries, 64);
    __type(key, struct ino_key);
    __type(value, __u32);
}trusted_dir_inode SEC(".maps");

#endif