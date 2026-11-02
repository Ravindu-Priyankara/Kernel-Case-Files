#define _GNU_SOURCE
#include <stdio.h>
#include <sched.h>
#include <linux/perf_event.h>
#include <linux/hw_breakpoint.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <bpf/bpf.h>
#include <linux/bpf.h>

static long perf_event_open(struct perf_event_attr *hw_event, pid_t pid,
                            int cpu, int group_fd, unsigned long flags) {
    return syscall(__NR_perf_event_open, hw_event, pid, cpu, group_fd, flags);
}

int main(){

    struct perf_event_attr attr = {0};
    int fd, ret = 0;

    // need to force go through CPU0
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(0, &mask);

    if(sched_setaffinity(0, sizeof(mask), (const cpu_set_t *)&mask) < 0){
        perror("sched_setaffinity failed!");
        return 1;
    }

    // setup CPU hardware cycle counter nmi evennt

    /*
    *   enum perf_type_id {
    *       PERF_TYPE_HARDWARE			= 0,
    *       PERF_TYPE_SOFTWARE			= 1,
    *       PERF_TYPE_TRACEPOINT			= 2,
    *       PERF_TYPE_HW_CACHE			= 3,
    *       PERF_TYPE_RAW				= 4,
    *       PERF_TYPE_BREAKPOINT			= 5,
    *    
    *       PERF_TYPE_MAX,
    *    };
    */
    // in virtual machines hardware flag not worked
    //attr.type = PERF_TYPE_HARDWARE;
    attr.type = PERF_TYPE_SOFTWARE;
    attr.size = sizeof(struct perf_event_attr);

    /*
    *   enum perf_hw_id {
    *
    *       PERF_COUNT_HW_CPU_CYCLES		= 0,
    *       PERF_COUNT_HW_INSTRUCTIONS		= 1,
    *       PERF_COUNT_HW_CACHE_REFERENCES		= 2,
    *       PERF_COUNT_HW_CACHE_MISSES		= 3,
    *       PERF_COUNT_HW_BRANCH_INSTRUCTIONS	= 4,
    *       PERF_COUNT_HW_BRANCH_MISSES		= 5,
    *       PERF_COUNT_HW_BUS_CYCLES		= 6,
    *       PERF_COUNT_HW_STALLED_CYCLES_FRONTEND	= 7,
    *       PERF_COUNT_HW_STALLED_CYCLES_BACKEND	= 8,
    *       PERF_COUNT_HW_REF_CPU_CYCLES		= 9,
    *
    *       PERF_COUNT_HW_MAX,	
    *   };
    */
    //attr.config = PERF_COUNT_HW_CPU_CYCLES;
    attr.config = PERF_COUNT_SW_CPU_CLOCK;
    //attr.sample_period = 300;
    attr.sample_period = 50; // every 50 cpu cycles,
    attr.pinned = 1;

    /*
    * redundand, already zero
    */
    // attr.disabled       = 0;
    // attr.exclude_kernel = 0;
    // attr.exclude_user   = 0;
    // attr.inherit        = 0;

    int bpf_prog_fd = bpf_obj_get("/sys/fs/bpf/onelane_perf");
    if (bpf_prog_fd < 0) {
        perror("bpf_obj_get failed — Is Onelane running?");
        return 1;
    }

    // pid = -1, group -1, and cpu 0
    fd = perf_event_open(&attr, -1, 0, -1, 0);
    if(fd < 0){
        perror("perf_event_open failed");
        return 1;
    }

    if(ioctl(fd, PERF_EVENT_IOC_SET_BPF, bpf_prog_fd) < 0){
        perror("PERF_EVENT_IOC_SET_BPF failed!");
        ret = 1;
        goto cleanup;
    }

    if(ioctl(fd, PERF_EVENT_IOC_ENABLE, 0) < 0){
        perror("failed to enable perf event");
        ret = 1;
        goto cleanup;
    }

    printf("[+] NMI Hardware Interrupt Driver active on CPU 0.\n");
    printf("[+] Hammering CPU syscalls to force NMI interrupts mid-execution...\n");

    for (int i = 0; i < 10000000; i++) {
        syscall(SYS_gettid);
    }


cleanup:

    close(fd);
    return ret;
}