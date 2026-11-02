// shared header
#ifndef ONELANE_FLAGS_H
#define ONELANE_FLAGS_H

// for event matrix
enum evt_type {
    EVT_CPU0_TRIGGER_AMOUNT = 0,
    EVT_CPU0_PROGRAM_COUNTER,
    EVT_OTHER_CPU_TRIGGER_AMOUNT,
    EVT_OTHER_CPU_PROGRAM_COUNTER,
    EVT_IN_NMI,
    EVT_IN_HARDIRQ,
    EVT_IN_SOFTIRQ,
    MAX_EVT
};

#endif