#ifndef ONELANE_MAPS_H
#define ONELANE_MAPS_H

#include "flags.h"

struct {
    __uint(type, BPF_MAP_TYPE_PERCPU_ARRAY);
    __uint(max_entries, MAX_EVT);
    __type(key, __u32);
    __type(value, __u64);
}evt_stats SEC(".maps");

struct {
    __uint(type, BPF_MAP_TYPE_ARRAY);
    __uint(max_entries, 1);
    __type(key, __u32);
    __type(value, __u32);
} freeze_stats SEC(".maps");

#endif