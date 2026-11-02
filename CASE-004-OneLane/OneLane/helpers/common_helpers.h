#ifndef ONELANE_COMMON_HELPERS_H
#define ONELANE_COMMON_HELPERS_H

/*
*  NMI_MASK define like this
*       #define NMI_MASK	(__IRQ_MASK(NMI_BITS)     << NMI_SHIFT)
*       #define __IRQ_MASK(x)	((1UL << (x))-1)
*       #define NMI_SHIFT	(HARDIRQ_SHIFT + HARDIRQ_BITS)
*
*       #define HARDIRQ_SHIFT	(SOFTIRQ_SHIFT + SOFTIRQ_BITS)
*
*       #define SOFTIRQ_SHIFT	(PREEMPT_SHIFT + PREEMPT_BITS)
*       #define PREEMPT_SHIFT	0
*       #define PREEMPT_BITS	8
*       #define SOFTIRQ_BITS	8
*       #define HARDIRQ_BITS	4
*       #define NMI_BITS	4
*
*       Now 
*           1. HARDIRQ_SHIFT = ((0 + 8) + 8)
*           2. NMI_SHIFT = (16 + 4)
*           3. NMI_BITS = 4
*           4. NMI_MASK = (((1UL << (4))-1) << 20)
*
*      it means NMI_MASK = (((1UL << (4))-1) << 20) = 0xf00000
*
*
*   Oh my god, my brain is hurting😂
*
*   Why take one step forward when you can do a backflip, 
*   a spin, and a triple loop-de-loop just to end up in the exact same spot?
*
*/

//Dont laugh to naked truth
#ifndef MY_NMI_MASK 
#define MY_NMI_MASK 0xf00000
#endif

/*
*   Now need HARDIRQ_MASK
*
*   #define HARDIRQ_MASK	(__IRQ_MASK(HARDIRQ_BITS) << HARDIRQ_SHIFT)
*   #define __IRQ_MASK(x)	((1UL << (x))-1)
*
*   #define HARDIRQ_BITS	4
*
*   Now
*       - HARDIRQ_SHIFT = ((0 + 8) + 8)
*       - HARDIRQ_MASK = (((1UL << (4))-1) << 16)
*
*   It means HARDIRQ_MASK = (((1UL << (4))-1) << 16) = 0xf0000
*/

#ifndef MY_HARDIRQ_MASK
#define MY_HARDIRQ_MASK 0xf0000
#endif

/*
*   SOFTIRQ_MASK
*
*   #define SOFTIRQ_MASK	(__IRQ_MASK(SOFTIRQ_BITS) << SOFTIRQ_SHIFT)
*   #define __IRQ_MASK(x)	((1UL << (x))-1)
*   #define SOFTIRQ_SHIFT	(PREEMPT_SHIFT + PREEMPT_BITS)
*
*   #define PREEMPT_SHIFT	0
*   #define PREEMPT_BITS	8
*   #define SOFTIRQ_BITS	8
*
*   Now
*       - SOFTIRQ_SHIFT = (0 + 8)
*       - SOFTIRQ_MASK = (((1UL << (8))-1) << 8)
*
*   It means SOFTIRQ_MASK = (((1UL << (8))-1) << 8) = 0xff00
*/
#ifndef My_SOFTIRQ_MASK
#define My_SOFTIRQ_MASK 0xff00
#endif

#ifndef MY_SOFTIRQ_OFFSET
#define MY_SOFTIRQ_OFFSET (1ULL << 8)
#endif

//didnt get the preempt mask.

// switch off MSB, 01111111111111111111111111111111b
#ifndef SIGN_BIT
#define SIGN_BIT 0x7fffffff
#endif

/*
*   I saw __preempt_count in kallsym as a global or exported variable, located in the data section. So now we need to get that.
*   
*   D __preempt_count
*/
extern const int __preempt_count __ksym __weak;
extern const int bpf_in_nmi(void) __ksym __weak;
extern const int bpf_in_hardirq(void) __ksym __weak;
extern const int bpf_in_serving_softirq(void) __ksym __weak;


static __always_inline void decider(void);

static __always_inline void update_evt_stats(__u32 error_id, __u8 method){

    if(error_id >= MAX_EVT)
        return;

    __u64 *value = NULL;

    #if ENABLE_x86_64_BACKPORT
    decider();
    #endif

    value = bpf_map_lookup_elem(&evt_stats, &error_id);
    if(!value){
        // When numbers are mismatched, this will be shown if it's a map failure or something else
        bpf_printk("Map lookup failed! \n");
        return;
    }

    // no re-entry condition
    if(method == 0){

        __sync_fetch_and_add(value, 1);

        return;
    }

    // expand the re-entry window intentionally

    volatile __u64 tmp = *value;

    __u32 dummy_key = 0;
    bpf_map_lookup_elem(&freeze_stats, &dummy_key);

    *value = tmp + 1;

}


/*
*   We need to identify the interrupt type first.
*       1. bpf_in_nmi
*       2. bpf_in_hardirq
*       3. bpf_in_serving_softirq
*
*   But the issue is that these all introduce kernel 7.0. So we need to do this magic manually.
*/

/*
*   --------------
*   | bpf_in_nmi |
*   --------------
*   bpf_in_nmi was introduced in kernel 7.0. 
*   So we need to make one manually because my kernel is not >= 7.0
*
*   Lets see how kernel developers did this magic
*
*   static inline int bpf_in_nmi(void)
*   {
*	    return get_preempt_count() & NMI_MASK;
*   }
*
*   static inline int get_preempt_count(void)
*   {
*       #if defined(bpf_target_x86)
*	        // By default, read the per-CPU __preempt_count. //
*	        if (bpf_ksym_exists(&__preempt_count))
*		        return *(int *) bpf_this_cpu_ptr(&__preempt_count);
*
*	        //
*	        * If __preempt_count does not exist, try to read preempt_count under
*	        * struct pcpu_hot. Between v6.1 and v6.14 -- more specifically,
*	        * [64701838bf057, 46e8fff6d45fe), preempt_count had been managed
*	        * under struct pcpu_hot.
*	        //
*	        if (bpf_core_field_exists(pcpu_hot.preempt_count))
*		        return ((struct pcpu_hot___local *)
*			        bpf_this_cpu_ptr(&pcpu_hot))->preempt_count;
*       #elif defined(bpf_target_arm64)
*	        return bpf_get_current_task_btf()->thread_info.preempt.count;
*       #elif defined(bpf_target_powerpc)
*	        return bpf_get_current_task_btf()->thread_info.preempt_count;
*       #elif defined(bpf_target_s390)
*	        return bpf_get_lowcore()->preempt_count;
*       #elif defined(bpf_target_loongarch)
*	        return bpf_get_current_task_btf()->thread_info.preempt_count;
*       #elif defined(bpf_target_riscv)
*	        return bpf_get_current_task_btf()->thread_info.preempt_count;
*       #endif
*	        return 0;
*   }
*
*   Mmmm different archs use different methods now lets make it our version.
*
*/

/*
*   I just check this on Arm64 kernel it hasnt __preempt_count on kallsyms. so this version will only work some x86
*   And arm or other archs we need apply kernel developper way. But I didnt implement it here because I havent resources to verify is it working.
*   So without checking its look like guessing so I hate it
*   Put macro and set it default to 0, if user need ,they will enable
*/
static __always_inline int my_preempt_count(void){

    int preempt_count = 0;

    int *preempt_count_ptr = (int *)bpf_this_cpu_ptr(&__preempt_count);
    if(!preempt_count_ptr)
        return 0;

    preempt_count = *preempt_count_ptr;

    // critical: need to rm sign bit otherwise we see huge negative number
    preempt_count = preempt_count & SIGN_BIT;

    return preempt_count;
}

static __always_inline int my_bpf_in_nmi(void){
    int preempt_count = my_preempt_count();

    if(!preempt_count)
        return 0;

    if(preempt_count & MY_NMI_MASK)
        return 1;

    return 0;
}

static __always_inline int my_bpf_in_hardirq(void){
    int preempt_count = my_preempt_count();

    if(!preempt_count)
        return 0;

    if(preempt_count & MY_HARDIRQ_MASK){
        return 1;
    }

    return 0;
}

static __always_inline int my_bpf_in_serving_softirq(void){
    int preempt_count = my_preempt_count();

    if(!preempt_count)
        return 0;

    if(preempt_count & My_SOFTIRQ_MASK)
        return 1;

    return 0;
}

static __always_inline void decider(void){

    __u32 evt;
    __u64 *value = NULL;
    bool h_kern = true;

    if(!bpf_ksym_exists(bpf_in_nmi) || !bpf_ksym_exists(bpf_in_hardirq) || !bpf_ksym_exists(bpf_in_serving_softirq))
        h_kern = false;

    if((h_kern && bpf_in_nmi()) || (!h_kern && my_bpf_in_nmi())){
        evt = EVT_IN_NMI;
        value = bpf_map_lookup_elem(&evt_stats, &evt);
        if(value)
            __sync_fetch_and_add(value, 1);
    }

    if((h_kern && bpf_in_hardirq()) || (!h_kern && my_bpf_in_hardirq())){
        evt = EVT_IN_HARDIRQ;
        value = bpf_map_lookup_elem(&evt_stats, &evt);
        if(value)
            __sync_fetch_and_add(value, 1);
    }

    if((h_kern && bpf_in_serving_softirq()) || (!h_kern && my_bpf_in_serving_softirq())){
        evt = EVT_IN_SOFTIRQ;
        value = bpf_map_lookup_elem(&evt_stats, &evt);
        if(value)
            __sync_fetch_and_add(value, 1);
    }

    return;
}

#endif

/*
*   After eliminate re-entry
*
*   1. Before interrupt 0 events loss
*
*       Frozen!
*       Total CPU0 events that triggered:  : 1270 
*       Total CPU0 Program counter:  : 1270 
*       Total other CPU events that triggered:  : 973 
*       Total other CPU program counter:  : 973 
*       NMI (interrupt context) through triggered events:  : 0 
*       HARDIRQ (interrupt context) through triggered events:  : 0 
*       SOFTIRQ (interrupt context) through triggered events:  : 0 
*
*       Analyse
*       You missed 0 events!
*
*   2. After interrupt 0 event loss
*
*       Frozen!
*       Total CPU0 events that triggered:  : 10648524 
*       Total CPU0 Program counter:  : 10648524 
*       Total other CPU events that triggered:  : 5873 
*       Total other CPU program counter:  : 5873 
*       NMI (interrupt context) through triggered events:  : 0 
*       HARDIRQ (interrupt context) through triggered events:  : 1282914 
*       SOFTIRQ (interrupt context) through triggered events:  : 2882 
*
*   Analyse
*       You missed 0 events!
*
*   Before eliminate re-entry
*
*   1. Before interrupt 0 events lost
*
*       Frozen!
*       Total CPU0 events that triggered:  : 1339 
*       Total CPU0 Program counter:  : 1339 
*       Total other CPU events that triggered:  : 1207 
*       Total other CPU program counter:  : 1207 
*       NMI (interrupt context) through triggered events:  : 0 
*       HARDIRQ (interrupt context) through triggered events:  : 0 
*       SOFTIRQ (interrupt context) through triggered events:  : 0 
*
*   Analyse
*       You missed 0 events!
*
*   2. After interrupt 30343 events miss
*
*       Frozen!
*       Total CPU0 events that triggered:  : 10674261 
*       Total CPU0 Program counter:  : 10643918 
*       Total other CPU events that triggered:  : 9010 
*       Total other CPU program counter:  : 9010 
*       NMI (interrupt context) through triggered events:  : 0 
*       HARDIRQ (interrupt context) through triggered events:  : 1326496 
*       SOFTIRQ (interrupt context) through triggered events:  : 4898 
*
*       Analyse
*       You missed 30343 events!
*
*/