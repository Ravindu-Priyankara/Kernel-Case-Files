#ifndef OVERTHINKER_HEADER_H
#define OVERTHINKER_HEADER_H

#include "vmlinux.h"
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>
#include <bpf/bpf_core_read.h>
#include "config.h"
#include "events.h"
#include "flags.h"
#include "maps.h"

char LICENSE[] SEC("license") = "GPL";

#endif