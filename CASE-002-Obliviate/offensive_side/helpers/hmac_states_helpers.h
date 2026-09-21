#ifndef OBLIVIATE_HMAC_STATES_HELPERS_H
#define OBLIVIATE_HMAC_STATES_HELPERS_H

#if REVEAL_THE_HMAC_STATES
static int reveal_the_hmac_states_prehandler(struct kprobe *kps, struct pt_regs *regs);
#endif

#if REVEAL_THE_HMAC_STATES
static struct kprobe kps = {
    .symbol_name = "__hmac_sha256_preparekey",
    .pre_handler = reveal_the_hmac_states_prehandler,
};
#endif

/*
*   Alternatives:
*
*   - We can use this method but need percpu for that.
*       1. Hook this function entry.
*       2. Extract istate and ostate and write them to global variables
*       3. register hook with the offset after operation done.
*       4. access data via second hook.
*       5. and read the value
*
*  so I thought this is simple than above one🤔.
*  Because the above one needs to think deeply about instances.
*/
#if REVEAL_THE_HMAC_STATES
static int reveal_the_hmac_states_prehandler(struct kprobe *kps, struct pt_regs *regs){
    if(!kps || !regs)
        return 0;

    struct sha256_block_state *istate = NULL;
    struct sha256_block_state *ostate = NULL;
    struct sha256_block_state *iv = NULL;
    u8 *raw_key = NULL;
    size_t raw_key_len = 0;
    kallsyms_lookup_name_t my_local_kallsyms_lookup_name_t = NULL;
    void (*my_sha256_blocks_generic)(struct sha256_block_state *, const u8 *, size_t);

    istate = (struct sha256_block_state *)regs_get_kernel_argument(regs, 0);
    ostate = (struct sha256_block_state *)regs_get_kernel_argument(regs, 1);
    iv = (struct sha256_block_state *)regs_get_kernel_argument(regs, 4);
    raw_key = (u8 *)regs_get_kernel_argument(regs, 2);
    raw_key_len = (size_t)regs_get_kernel_argument(regs, 3);
    my_local_kallsyms_lookup_name_t = READ_ONCE(my_kallsyms_lookup_name);

    if(IS_ERR_OR_NULL(istate) || IS_ERR_OR_NULL(ostate) || IS_ERR_OR_NULL(iv) 
    || IS_ERR_OR_NULL(raw_key) || (IS_ERR_OR_NULL(my_kallsyms_lookup_name)))
        return 0;

    if(raw_key_len == 0 || raw_key_len > O_MAX_SIZE)
        return 0;

    my_sha256_blocks_generic = (void(*)(struct sha256_block_state *, const u8 *, size_t))my_local_kallsyms_lookup_name_t("sha256_blocks_generic");
    if(!my_sha256_blocks_generic)
        return 0;

    union {
        u8 b[O_MAX_SIZE];
        unsigned long w[O_MAX_SIZE / sizeof(unsigned long)];
    } derived_key = {0};

    memcpy(derived_key.b, raw_key, raw_key_len);

    for(size_t i = 0; i < ARRAY_SIZE(derived_key.w); i++)
        derived_key.w[i] ^= REPEAT_BYTE(HMAC_IPAD_VALUE);

    *istate = *iv;
    my_sha256_blocks_generic(istate, derived_key.b, 1);

    for(size_t i = 0; i < ARRAY_SIZE(derived_key.w); i++)
        derived_key.w[i] ^= REPEAT_BYTE(HMAC_OPAD_VALUE ^ HMAC_IPAD_VALUE);

    *ostate = *iv;
    my_sha256_blocks_generic(ostate, derived_key.b, 1);

    pr_info("Istate: %*ph \n", (int)SHA256_STATE_WORDS, istate->h);
    pr_info("Ostate: %*ph \n", (int)SHA256_STATE_WORDS, ostate->h);

    // cleanup the we polluted data.
    memzero_explicit(istate->h, SHA256_STATE_WORDS);
    memzero_explicit(ostate->h, SHA256_STATE_WORDS);

    // wipe out the key
    memzero_explicit(&derived_key, sizeof(derived_key));

    /*
    *   Example output:(run twice)
    *
    *   [  342.000132] Istate: 45 ef 70 ad 8a a4 57 0e 
    *   [  342.000446] Ostate: 2a ea 00 5f e1 11 0a aa 
    *   [  371.862156] Istate: 45 ef 70 ad 8a a4 57 0e 
    *   [  371.862335] Ostate: 2a ea 00 5f e1 11 0a aa
    */

    return 0;
}
NOKPROBE_SYMBOL(reveal_the_hmac_states_prehandler);
#endif


#if REVEAL_THE_HMAC_STATES
static inline int register_reveal_the_hmac_state_kprobe(void){
    int ret = 0;

    ret = register_kprobe(&kps);
    if(!ret)
        WRITE_ONCE(probe_hooked, true);

    return ret;
}

static inline void unregister_reveal_the_hmac_state_kprobe(void){
    if(READ_ONCE(probe_hooked))
        unregister_kprobe(&kps);
}
#endif

#endif