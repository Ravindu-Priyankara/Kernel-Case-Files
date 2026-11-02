#ifndef ONELANE_STATIC_DATA_STRUCTURES_H
#define ONELANE_STATIC_DATA_STRUCTURES_H

/*
*   Human-readable labels for every event slot.
*   No trailing ": " here, the printer handles layout.
*/
static const char * const evt_codes[MAX_EVT] = {
    [EVT_CPU0_TRIGGER_AMOUNT]       = "Events triggered on CPU0",
    [EVT_CPU0_PROGRAM_COUNTER]      = "Events counted on CPU0",
    [EVT_OTHER_CPU_TRIGGER_AMOUNT]  = "Events triggered on other CPUs",
    [EVT_OTHER_CPU_PROGRAM_COUNTER] = "Events counted on other CPUs",
    [EVT_IN_NMI]                    = "Fired inside NMI context",
    [EVT_IN_HARDIRQ]                = "Fired inside hard IRQ context",
    [EVT_IN_SOFTIRQ]                = "Fired inside soft IRQ context"
};

static __u64 samples[MAX_EVT] = {0};

#endif