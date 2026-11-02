#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <bpf/libbpf.h>
#include <bpf/bpf.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <errno.h>

#include "config.h"
#include "flags.h"
#include "handler/static_data_structures.h"
#include "handler/handler.h" // must be positioned at the end of the queue
#include "main.skel.h"

#define PIN_PATH "/sys/fs/bpf/onelane_perf"

static volatile sig_atomic_t running = 1;

void handle_signal(int sig)
{
    running = 0;
}

int main()
{
    // Configure SIGINT/SIGTERM using sigaction WITHOUT SA_RESTART
    struct sigaction sa = {
        .sa_handler = handle_signal,
        .sa_flags = 0 // Critical: ensures blocking calls like scanf return EINTR on Ctrl+C
    };
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);

    struct main_bpf *main_bpf = NULL;
    //int err = -1;

    struct rlimit rlim_new = {
        .rlim_cur = RLIM_INFINITY,
        .rlim_max = RLIM_INFINITY,
    };
    setrlimit(RLIMIT_MEMLOCK, &rlim_new);

    printf("\n\t4f 6e 65 4c 61 6e 65\n\n");
    printf("One lane, but still, your car can crash.\n\n");

    main_bpf = main_bpf__open();
    if (!main_bpf) {
        printf("Failed to open eBPF program!\n");
        return 1;
    }

    if (main_bpf__load(main_bpf)) {
        printf("Failed to load eBPF program!\n");
        goto cleanup;
    }

    #if DEBUG_MODE
    struct bpf_program *prog;
    bpf_object__for_each_program(prog, main_bpf->obj) {
        print_prog_info(prog);
    }
    #endif

    int perf_prog_fd = bpf_program__fd(main_bpf->progs.my_nmi_interrupt_handler);

    // Remove any stale pin from a previous crash
    unlink(PIN_PATH);

    if (bpf_obj_pin(perf_prog_fd, PIN_PATH) < 0) {
        perror("bpf_obj_pin failed");
    } else {
        printf("[+] Pinned NMI handler to %s\n", PIN_PATH);
    }

    if (main_bpf__attach(main_bpf)) {
        printf("Failed to attach eBPF program!\n");
        goto cleanup;
    }

    char command;

    // Loop exits immediately on Ctrl+C because scanf returns -1 with errno == EINTR
    while (running && scanf(" %c", &command) == 1) {
        __u32 key = 0;
        __u32 freeze = (command == 'f') ? 1 : 0;

        int freeze_fd = bpf_map__fd(main_bpf->maps.freeze_stats);

        if (bpf_map_update_elem(freeze_fd, &key, &freeze, BPF_ANY) < 0) {
            perror("freeze_stats update");
            continue;
        }

        if (freeze) {
            printf("Frozen!\n");
            sleep(1);
            evt_matrix(bpf_map__fd(main_bpf->maps.evt_stats));
        } else if (command == 'r') {
            printf("Counters resumed!\n");
        }
    }

cleanup:
    printf("\nCleaning up...\n");

    // Remove the pinned file on exit
    unlink(PIN_PATH);

    if (main_bpf)
        main_bpf__destroy(main_bpf);

    return 0;
}