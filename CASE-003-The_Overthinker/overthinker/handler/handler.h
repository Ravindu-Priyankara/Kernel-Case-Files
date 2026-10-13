#ifndef OVERTHINKER_HANDLER_H
#define OVERTHINKER_HANDLER_H

// https://elixir.bootlin.com/linux/v6.17/source/include/linux/kdev_t.h#L12
#define MINORBITS	20
#define MKDEV(ma,mi)	(((uint32_t)(ma & 0xfff) << MINORBITS) | (uint32_t)(mi & 0xfffff))

/*
*   Extract the error matrix from percpu array
*
*   @map_fd: percpu array map id
*
*/
static void error_matrix(int map_fd){
    int ret = -1, ncpus = -1; 

    if(map_fd < 0){
        printf(OVERTHINKER_LINE OVERTHINKER_ERROR"Invalid map fd to error stats!\n");
        return;
    }

    ncpus = libbpf_num_possible_cpus();
    if(ncpus < 0){
        printf(OVERTHINKER_LINE OVERTHINKER_ERROR"libbpf_num_possible_cpus helper failed!\n");
        return;
    }

    __u64 *values = calloc(ncpus, sizeof(__u64));
    if(!values){
        printf(OVERTHINKER_LINE OVERTHINKER_ERROR"Failed to allocate memory to error matrix!\n");
        return;
    }

    printf(OVERTHINKER_LINE OVERTHINKER_INFO"Overthinker error matrix!\n");

    for(int i = 0; i < MAX_ERRORS; i++){
        __u64 total_errors = 0;

        ret = bpf_map_lookup_elem(map_fd, &i, values);
        if(ret < 0){
            printf(OVERTHINKER_LINE OVERTHINKER_ERROR"Failed map lookup in error matrix: key = %d \n", i);
            continue;
        }

        for(int j = 0; j< ncpus; j++){
            total_errors += values[j];
        }
        printf(OVERTHINKER_LINE OVERTHINKER_ERROR"%s : %llu \n", error_codes[i], total_errors);
    }

    printf(OVERTHINKER_LINE OVERTHINKER_INFO"End of the overthinker error matrix!\n");

    free(values);
}

/*
*   Ring buffer event handler
*
*   @return
*       - always try return 0 to stop failing ringbuf polling.
*/
static int event_handler(void *ctx, void *data, size_t size){
    if(!data || size == 0){
        printf(OVERTHINKER_LINE OVERTHINKER_ERROR"Empty sample recieved!\n");
        return 0; // negative values stop polling
    }

    if(size < sizeof(struct event)){
        printf(OVERTHINKER_LINE OVERTHINKER_ERROR"Currupt or under size sample recieved! (%zu bytes)", size);
        return 0;
    }

    // Direct O(1) string lookup
    const struct event *my_event = (const struct event *)data;

    if(my_event->event_id < 0 || my_event->event_id >= EVT_MAX){
        printf(OVERTHINKER_LINE OVERTHINKER_ERROR"Invalid event id found! %d \n", my_event->event_id);
        return 0;
    }

    // validate before apply
    const char *evt_string = EVENT_STRING[my_event->event_id];
    if(!evt_string){
        evt_string = "Unknown string found!";
    }

    switch(my_event->severity){
        case SEV_ERR:
            printf(OVERTHINKER_LINE OVERTHINKER_ERROR"PID: %d, COMM: %.16s %s\n", 
                my_event->pid ,my_event->comm ,evt_string);
            break;
        case SEV_INFO:
            printf(OVERTHINKER_LINE OVERTHINKER_INFO"PID: %d, COMM: %.16s %s\n", 
                my_event->pid ,my_event->comm ,evt_string);
            break;
        case SEV_BLOCK:
            printf(OVERTHINKER_LINE OVERTHINKER_BLOCK"PID: %d, COMM: %.16s %s\n", 
                my_event->pid ,my_event->comm ,evt_string);
            break;
        default:
            printf(OVERTHINKER_LINE OVERTHINKER_INFO"PID: %d, COMM: %.16s [UNKNOWN SEVERITY]: %d, [EVT_STRING]: %s", 
                my_event->pid, my_event->comm, my_event->severity, evt_string);
    }

    return 0;
}

static void register_trusted_directory(int map_fd, const char *path){
    if(map_fd < 0 || !path)
        return;

    struct stat st;

    if(stat(path, &st) == 0){
        struct {
            uint64_t ino;
            uint32_t dev;
        }key = {
            .ino = st.st_ino,
            .dev = MKDEV(major(st.st_dev), minor(st.st_dev)),
        };

        uint32_t value = 1;

        // TODO: intentionally failed this and observe what wil happen via lsm.
        if(bpf_map_update_elem(map_fd, &key, &value, BPF_ANY) < 0){
            printf(OVERTHINKER_LINE OVERTHINKER_ERROR"Failed to register trusted directory informations!\n");
        }
    }

}

//TODO: need to fix yoda English.
#endif