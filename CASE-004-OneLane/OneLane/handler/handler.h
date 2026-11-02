#ifndef ONELANE_HANDLER_H
#define ONELANE_HANDLER_H

// https://elixir.bootlin.com/linux/v6.17/source/include/linux/kdev_t.h#L12
#define MINORBITS	20
#define MKDEV(ma,mi)	(((uint32_t)(ma & 0xfff) << MINORBITS) | (uint32_t)(mi & 0xfffff))

/* Box layout: │ <label:44> <value:14> │  -> 61 columns between the borders */
#define BOX_LABEL_W  44
#define BOX_VALUE_W  14
#define BOX_INNER_W  (1 + BOX_LABEL_W + 1 + BOX_VALUE_W + 1)

/* 1234567 -> "1,234,567" */
static const char *fmt_u64(__u64 v, char *buf, size_t sz)
{
    char raw[32];
    int len = snprintf(raw, sizeof(raw), "%llu", (unsigned long long)v);
    size_t o = 0;

    for (int i = 0; i < len && o + 2 < sz; i++) {
        if (i > 0 && (len - i) % 3 == 0)
            buf[o++] = ',';
        buf[o++] = raw[i];
    }
    buf[o] = '\0';
    return buf;
}

static void box_rule(const char *l, const char *m, const char *r)
{
    printf("%s", l);
    for (int i = 0; i < BOX_INNER_W; i++)
        printf("%s", m);
    printf("%s\n", r);
}

static void box_text(const char *text)
{
    printf("│ %-*s │\n", BOX_INNER_W - 2, text);
}

static void box_title(const char *text)
{
    int pad = (BOX_INNER_W - (int)strlen(text)) / 2;
    printf("│%*s%s%*s│\n", pad, "", text,
           BOX_INNER_W - pad - (int)strlen(text), "");
}

static void box_row(const char *label, __u64 value)
{
    char num[32];
    fmt_u64(value, num, sizeof(num));
    printf("│ %-*s %*s │\n", BOX_LABEL_W, label, BOX_VALUE_W, num);
}

/*
*   Extract the evt matrix from percpu array and print a report.
*
*   @map_fd: percpu array map fd
*/
static void evt_matrix(int map_fd){
    int ret = -1, ncpus = -1;

    if(map_fd < 0){
        printf("Invalid map fd for the event stats map!\n");
        return;
    }

    ncpus = libbpf_num_possible_cpus();
    if(ncpus < 0){
        printf("libbpf_num_possible_cpus failed!\n");
        return;
    }

    __u64 *values = calloc(ncpus, sizeof(__u64));
    if(!values){
        printf("Out of memory while reading event stats!\n");
        return;
    }

    for(__u32 i = 0; i < MAX_EVT; i++){
        __u64 total = 0;

        ret = bpf_map_lookup_elem(map_fd, &i, values);
        if(ret < 0){
            printf("Map lookup failed for event key %u\n", i);
            continue;
        }

        for(int j = 0; j < ncpus; j++)
            total += values[j];

        samples[i] = total;
    }

    free(values);

    /* Saturating subtraction: never print a wrapped-around huge number */
    __u64 trig = samples[EVT_CPU0_TRIGGER_AMOUNT];
    __u64 cnt  = samples[EVT_CPU0_PROGRAM_COUNTER];
    __u64 lost = trig > cnt ? trig - cnt : 0;
    double loss_pct = trig ? (double)lost * 100.0 / (double)trig : 0.0;

    printf("\n");
    box_rule("┌", "─", "┐");
    box_title("ONELANE  ·  EVENT REPORT");
    box_rule("├", "─", "┤");

    box_text("CPU ACTIVITY");
    box_row(evt_codes[EVT_CPU0_TRIGGER_AMOUNT],       samples[EVT_CPU0_TRIGGER_AMOUNT]);
    box_row(evt_codes[EVT_CPU0_PROGRAM_COUNTER],      samples[EVT_CPU0_PROGRAM_COUNTER]);
    box_row(evt_codes[EVT_OTHER_CPU_TRIGGER_AMOUNT],  samples[EVT_OTHER_CPU_TRIGGER_AMOUNT]);
    box_row(evt_codes[EVT_OTHER_CPU_PROGRAM_COUNTER], samples[EVT_OTHER_CPU_PROGRAM_COUNTER]);
    box_rule("├", "─", "┤");

    box_text("INTERRUPT CONTEXT");
    box_row(evt_codes[EVT_IN_NMI],     samples[EVT_IN_NMI]);
    box_row(evt_codes[EVT_IN_HARDIRQ], samples[EVT_IN_HARDIRQ]);
    box_row(evt_codes[EVT_IN_SOFTIRQ], samples[EVT_IN_SOFTIRQ]);
    box_rule("├", "─", "┤");

    box_text("ANALYSIS");
    box_row("Events lost on CPU0", lost);

    char line[96];
    snprintf(line, sizeof(line), "Loss rate: %.4f%%", loss_pct);
    box_text(line);
    box_text(lost == 0 ? "Verdict: ✔ no events lost, clean run"
                       : "Verdict: ✘ events lost (re-entry suspected)");
    box_rule("└", "─", "┘");
    printf("\n");
}

// for debug
#if DEBUG_MODE
static void print_prog_info(struct bpf_program *prog)
{
    int prog_fd = bpf_program__fd(prog);
    struct bpf_prog_info info = {};
    __u32 len = sizeof(info);

    if (bpf_prog_get_info_by_fd(prog_fd, &info, &len)) {
        perror("bpf_prog_get_info_by_fd");
        return;
    }

    __u32 xlated = info.xlated_prog_len / (__u32)sizeof(struct bpf_insn);

    printf("\n");
    box_rule("┌", "─", "┐");
    box_title("VERIFIER REPORT");
    box_rule("├", "─", "┤");
    box_text(bpf_program__name(prog));
    box_row("Original instructions",        bpf_program__insn_cnt(prog));
    box_row("Translated instructions",      xlated);
    box_row("Translated size (bytes)",      info.xlated_prog_len);
    box_row("JIT-compiled size (bytes)",    info.jited_prog_len);
    box_row("Verifier processed insns",     info.verified_insns);
    box_row("Maps used",                    info.nr_map_ids);

    char line[96];
    snprintf(line, sizeof(line), "Complexity: %.3f%% of the 1M insn limit",
             info.verified_insns * 100.0 / 1000000.0);
    box_text(line);
    box_rule("└", "─", "┘");
}
#endif

#endif