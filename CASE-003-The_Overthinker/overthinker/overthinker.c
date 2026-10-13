#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <bpf/libbpf.h>
#include <time.h>
#include <bpf/bpf.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>

#include "config.h"
#include "flags.h"
#include "colors.h"
#include "events.h"
#include "handler/static_data_structures.h"
#include "handler/handler.h" // must be positioned at the end of the queue

#include "main.skel.h"

static volatile int running = 1;

void handle_signal(int sig)
{
    running = 0;
}

#if ERROR_MATRIX
void *error_matrix_worker(void *arg)
{
    int map_fd = *(int *)arg;

    while (running) {
        for (int i = 0; i < ERROR_MATRIX_DELAY && running; i++) {
            sleep(1);
        }

        if (running) {
            error_matrix(map_fd);
        }
    }
    return NULL;
}
#endif

int main()
{
    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);

    struct main_bpf *main_bpf = NULL;
    struct ring_buffer *u_rb = NULL;
    int err = -1, tdi_map_fd = -1;

#if ERROR_MATRIX
    pthread_t err_thread;
    int err_thread_created = 0;
    int map_fd = -1;
#endif

    struct rlimit rlim_new = {
        .rlim_cur = RLIM_INFINITY,
        .rlim_max = RLIM_INFINITY,
    };
    setrlimit(RLIMIT_MEMLOCK, &rlim_new);

    main_bpf = main_bpf__open();
    if (!main_bpf) {
        printf(OVERTHINKER_LINE OVERTHINKER_ERROR "Failed to open eBPF program!\n");
        return 1;
    }

    if (main_bpf__load(main_bpf)) {
        printf(OVERTHINKER_LINE OVERTHINKER_ERROR "Failed to load eBPF program!\n");
        goto cleanup;
    }

    if (main_bpf__attach(main_bpf)) {
        printf(OVERTHINKER_LINE OVERTHINKER_ERROR "Failed to attach eBPF program!\n");
        goto cleanup;
    }

    printf(RED "\n\t4F 76 65 72 74 68 69 6E 6B 65 72\n\n" WHITE);
    #if(!BLOCK_ANY_ATTACK)
    printf(OVERTHINKER_LINE OVERTHINKER_INFO "We don't just hunt malware. We hunt the hope that your system will ever boot again.\n\n");
    #endif

    #if(BLOCK_ANY_ATTACK)
    printf(OVERTHINKER_LINE OVERTHINKER_INFO "We don't fix vulnerabilities. We just make sure the system doesn't survive long enough to exploit them.\n\n");
    #endif

    int rb_map_fd = bpf_map__fd(main_bpf->maps.rb);
    if (rb_map_fd < 0) {
        printf(OVERTHINKER_LINE OVERTHINKER_ERROR "Invalid ringbuffer map fd found!\n");
        err = rb_map_fd;
        goto cleanup;
    }

    u_rb = ring_buffer__new(rb_map_fd, event_handler, NULL, NULL);
    if (!u_rb) {
        printf(OVERTHINKER_LINE OVERTHINKER_ERROR "Failed to create new ringbuf manager!\n");
        err = -1;
        goto cleanup;
    }

#if ERROR_MATRIX
    map_fd = bpf_map__fd(main_bpf->maps.error_stats);
    if (map_fd >= 0) {
        if (pthread_create(&err_thread, NULL, error_matrix_worker, &map_fd) == 0) {
            err_thread_created = 1;
        } else {
            printf(OVERTHINKER_LINE OVERTHINKER_ERROR "Failed to spawn error matrix thread!\n");
        }
    }
#endif

    tdi_map_fd = bpf_map__fd(main_bpf->maps.trusted_dir_inode);
    register_trusted_directory(tdi_map_fd, "/lib/modules");
    register_trusted_directory(tdi_map_fd, "/usr/lib/modules");

    while (running) {
        err = ring_buffer__poll(u_rb, 100);
        if (err == -EINTR) {
            err = 0;
            break;
        }

        if (err < 0) {
            printf(OVERTHINKER_LINE OVERTHINKER_ERROR "Error polling ringbuffer!\n");
            break;
        }
    }

cleanup:
#if ERROR_MATRIX
    if (err_thread_created) {
        pthread_join(err_thread, NULL);
    }
#endif

    if (u_rb)
        ring_buffer__free(u_rb);

    if (main_bpf)
        main_bpf__destroy(main_bpf);

    if (err == 0) 
        return 0;

    // 0 = success, 1 ... 255 = failures
    return err < 0 ? -err : 0;
}