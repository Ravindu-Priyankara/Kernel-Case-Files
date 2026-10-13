#ifndef OBLIVIATE_AES_HELPERS_H
#define OBLIVIATE_AES_HELPERS_H

#include "headers/main_header.h"

/*
*   - There were multiple methods available to extract the AES and HMAC keys. 
*       As shown in my *Kernel Case 001*, 
*       there are several reliable functions we could have used.
*
*   - However, for this instance, 
*       I chose the most unsafe approach: pointer subtraction-based key extraction.
*
*   - This approach introduces a few critical limitations and risks:
*
*       1. `__hmac_sha256_preparekey` is a shared low-level helper used across dozens of kernel subsystems.
*       2. Pointer subtraction-based AES key extraction works exclusively for the `authencesn` algorithm. 
*           For any other algorithm, it will return memory corruption or arbitrary data.
*       3. While reading memory this way is relatively low-risk (though still not 100% safe), 
*           writing to it is extremely dangerous. You cannot guarantee you are modifying the actual AES key, which presents a worst-case scenario for system stability.
*
*   - I executed this technique within a strictly controlled environment. 
*       I strongly advise against taking unnecessary risks—understand the underlying concepts, 
*       but do not execute this code without a complete grasp of its implications.
*
*/
#if REVEAL_THE_AES_KEY
static int extract_aes_key_prehandler(struct kprobe *kps, struct pt_regs *regs);
#endif

#if FREE_KERNEL_PANIC
static int change_aes_key_prehandler(struct kprobe *kps, struct pt_regs *regs);
#endif

#if (REVEAL_THE_AES_KEY || FREE_KERNEL_PANIC)
static struct kprobe kp ={
    .symbol_name = "__hmac_sha256_preparekey",
    #if REVEAL_THE_AES_KEY
    .pre_handler = extract_aes_key_prehandler,
    #endif
    #if FREE_KERNEL_PANIC
    .pre_handler = change_aes_key_prehandler
    #endif
};
#endif

#if REVEAL_THE_AES_KEY

// removed debug msges completly, 
static int extract_aes_key_prehandler(struct kprobe *kps, struct pt_regs *regs){
    if(!kps || !regs)
        return 0;

    u8 *raw_key = NULL;
    size_t raw_key_len = 0;
    u8 *header_ptr = NULL;
    u8 header_buffer[HEADER_SIZE] = {0};
    long ret = 0;
    struct rtattr *rta = NULL;
    struct crypto_authenc_key_param *param = NULL;
    unsigned int enckeylen = 0;
    u8 *raw_aes_key = NULL;
    u8 aes_key_buffer[O_MAX_SIZE] = {0};
    u8 hmac_key_buffer[O_MAX_SIZE] = {0};

    raw_key = (u8 *)regs_get_kernel_argument(regs, 2);
    raw_key_len = (size_t)regs_get_kernel_argument(regs, 3);

    if(IS_ERR_OR_NULL(raw_key))
        return 0;

    if(raw_key_len == 0 || raw_key_len > O_MAX_SIZE)
        return 0;

    header_ptr = raw_key - HEADER_SIZE;
    if(unlikely(!header_ptr))
        return 0;

    ret = copy_from_kernel_nofault(header_buffer, header_ptr, HEADER_SIZE);
    if(ret != 0)
        return 0;

    rta = (struct rtattr *)header_buffer;
    if(unlikely(!rta))
        return 0;

    pr_info("rtattr_len: %hu and rtattr_type: %hu\n", rta->rta_len, rta->rta_type);

    /*
    *   helps to reduce risk, but not 100%
    */
    if(rta->rta_type != CRYPTO_AUTHENC_KEYA_PARAM)
        return 0;

    param = RTA_DATA(rta);
    if(IS_ERR_OR_NULL(param))
        return 0;

    enckeylen = be32_to_cpu(param->enckeylen);
    if(!enckeylen)
        return 0;

    raw_aes_key = raw_key + raw_key_len;
    if(unlikely(!raw_aes_key))
        return 0;

    ret = copy_from_kernel_nofault(aes_key_buffer, raw_aes_key, (size_t)enckeylen);
    if(ret != 0)
        return 0;

    pr_info("AES_raw_key: %*ph \n", (int)enckeylen, aes_key_buffer);

    ret = copy_from_kernel_nofault(hmac_key_buffer, raw_key, raw_key_len);
    if(ret != 0)
        return 0;

    pr_info("HMAC_raw_key: %*ph \n", (int)raw_key_len, hmac_key_buffer);

    memzero_explicit(aes_key_buffer, enckeylen);
    memzero_explicit(hmac_key_buffer, raw_key_len);

    /*
    *   sample output:
    *
    *   [ 1722.115895] rtattr_len: 8 and rtattr_type: 1
    *   [ 1722.116111] AES_raw_key: 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 
    *   [ 1722.116186] HMAC_raw_key: 02 02 02 02 02 02 02 02 02 02 02 02 02 02 02 02
    *
    */

    return 0;
}
NOKPROBE_SYMBOL(extract_aes_key_prehandler);
#endif

#if FREE_KERNEL_PANIC
static int change_aes_key_prehandler(struct kprobe *kps, struct pt_regs *regs){
    if(!kps || !regs)
        return 0;

    u8 *raw_key = NULL;
    size_t raw_key_len = 0;
    u8 *header_ptr = NULL;
    u8 header_buffer[HEADER_SIZE] = {0};
    long ret = 0;
    struct rtattr *rta = NULL;
    struct crypto_authenc_key_param *param = NULL;
    unsigned int enckeylen = 0;
    u8 *raw_aes_key = NULL;
    // Never randomize this every iteration; it will break the design.
    u8 aes_key_buffer[O_MAX_SIZE] = {[0 ... (O_MAX_SIZE -1)] = 'P'};
    kallsyms_lookup_name_t my_local_kallsyms_lookup_name = NULL;
    long (*local_copy_to_kernel_nofault)(void *, const void *, size_t);

    raw_key = (u8 *)regs_get_kernel_argument(regs, 2);
    raw_key_len = (size_t)regs_get_kernel_argument(regs, 3);
    my_local_kallsyms_lookup_name = READ_ONCE(my_kallsyms_lookup_name);

    if(IS_ERR_OR_NULL(raw_key) || IS_ERR_OR_NULL(my_local_kallsyms_lookup_name))
        return 0;

    if(raw_key_len == 0 || raw_key_len > O_MAX_SIZE)
        return 0;

    local_copy_to_kernel_nofault = (long (*)(void *, const void *, size_t))my_local_kallsyms_lookup_name("copy_to_kernel_nofault");
    if(!local_copy_to_kernel_nofault)
        return 0;

    header_ptr = raw_key - HEADER_SIZE;
    if(unlikely(!header_ptr))
        return 0;

    ret = copy_from_kernel_nofault(header_buffer, header_ptr, (size_t)HEADER_SIZE);
    if(ret != 0)
        return 0;

    rta = (struct rtattr *)header_buffer;
    /*
    *   stack pointer, IS_ERR_OR_NULL always false here — paranoia only
    */
    if(IS_ERR_OR_NULL(rta))
        return 0;

    if(rta->rta_type != CRYPTO_AUTHENC_KEYA_PARAM)
        return 0;

    param = RTA_DATA(rta);
    if(IS_ERR_OR_NULL(param))
        return 0;

    enckeylen = be32_to_cpu(param->enckeylen);
    if(!enckeylen)
        return 0;

    raw_aes_key = raw_key + raw_key_len;
    if(unlikely(!raw_aes_key))
        return 0;

    /*
    *   C.S. Lewis said, 
    *       "When I became a man, 
    *       I put away childish things, including the fear of childishness and the desire to be very grown up." 
    *
    *   Yes, he did, but I didn't; that's the issue😁
    */
    pr_info("[Obliviate]: wand points to memory and said obliviate!\n");
    ret = local_copy_to_kernel_nofault(raw_aes_key, aes_key_buffer, (size_t)enckeylen);
    if(ret != 0)
        return 0;

    memzero_explicit(aes_key_buffer, O_MAX_SIZE);

    return 0;
}
NOKPROBE_SYMBOL(change_aes_key_prehandler);
#endif

#if (REVEAL_THE_AES_KEY || FREE_KERNEL_PANIC)
static inline int register_aes_key_extractor(void){
    int ret = 0;

    ret = register_kprobe(&kp);
    if(!ret)
        WRITE_ONCE(probe_hooked, true);

    return ret;
}

static inline void unregister_aes_key_extractor(void){
    if(READ_ONCE(probe_hooked)){
        unregister_kprobe(&kp);
    }
}
#endif

#endif