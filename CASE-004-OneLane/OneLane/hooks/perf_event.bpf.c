
#include "header.h"
#include "common_helpers.h"

SEC("perf_event")
int my_nmi_interrupt_handler(struct bpf_perf_event_data *ctx){

    __u32 key = 0;
    __u32 *freeze = bpf_map_lookup_elem(&freeze_stats, &key);

    // ignore hammering while reading
    if (freeze && *freeze)
        return 0;

    // get !CPU0 events data
    __u32 cpu = bpf_get_smp_processor_id();
    if(cpu != 0){
        update_evt_stats(EVT_OTHER_CPU_TRIGGER_AMOUNT, 0);
        update_evt_stats(EVT_OTHER_CPU_PROGRAM_COUNTER, ENABLE_RE_ENTRY);
    }

    // get CPU0 events data 
    update_evt_stats(EVT_CPU0_TRIGGER_AMOUNT, 0);
    update_evt_stats(EVT_CPU0_PROGRAM_COUNTER, ENABLE_RE_ENTRY);

   return 0;
}