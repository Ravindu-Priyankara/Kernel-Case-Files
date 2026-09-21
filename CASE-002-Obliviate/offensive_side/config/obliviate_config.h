#ifndef OBLIVIATE_CONFIG_H
#define OBLIVIATE_CONFIG_H

/*
*   - You can change these flags. 
*   - rule is pretty simple.
*       1. Just enable whatever you need, but only one flag per 1 iteration.
*/
#ifndef REVEAL_THE_HMAC_KEY
#define REVEAL_THE_HMAC_KEY 1
#endif

#ifndef CHANGE_THE_HMAC_KEY
#define CHANGE_THE_HMAC_KEY 0
#endif

#ifndef REVEAL_THE_HMAC_STATES
#define REVEAL_THE_HMAC_STATES 0
#endif

/*
*   - This flag will be enabled in the next research.
*   - This needs separate focus.
*/
#ifndef CHANGE_THE_HMAC_STATES
#define CHANGE_THE_HMAC_STATES 0
#endif

/*
*   temporary disable this flag
*/
#if CHANGE_THE_HMAC_STATES
#error "Disabled temporary.."
#endif

/*
*   | Think twice before enabling these two flags |
*/

#ifndef REVEAL_THE_AES_KEY
#define REVEAL_THE_AES_KEY 0
#endif

#ifndef FREE_KERNEL_PANIC
#define FREE_KERNEL_PANIC 0
#endif

/*
*   - Full automatic options:
*       - show original keys(HMAC and AES)
*       - change keys to our keys(both)
*
*   - Warning:
*       - Ministry of Magic Warning Notice
*/
#ifndef UNFORGIVABLE_KERNEL_CURSE
#define UNFORGIVABLE_KERNEL_CURSE 0  // Bye-bye keys!
#endif
/*
*   | End of the flags |
*/

/*
*   | Enable or disable the debug mode |
*/

#ifndef DEBUG_MODE
#define DEBUG_MODE 0
#endif

/*
*   | validations |
*/

// max
#if ((REVEAL_THE_HMAC_KEY) + (CHANGE_THE_HMAC_KEY) + (REVEAL_THE_HMAC_STATES) + \
    (CHANGE_THE_HMAC_STATES) + (REVEAL_THE_AES_KEY) + (FREE_KERNEL_PANIC) + (UNFORGIVABLE_KERNEL_CURSE)) > 1
#error"You can't enable multiple flags."
#endif

// min
#if ((REVEAL_THE_HMAC_KEY) + (CHANGE_THE_HMAC_KEY) + (REVEAL_THE_HMAC_STATES) + \
    (CHANGE_THE_HMAC_STATES) + (REVEAL_THE_AES_KEY) + (FREE_KERNEL_PANIC) + (UNFORGIVABLE_KERNEL_CURSE)) == 0
#error"Minimally, at least enable 1 flag"
#endif

/*
*   - Negative check
*       - This isn't effective here.
*       - Because we only check whether there was or wasn't the flag.
*      - But from a defensive coding angle, that's worth adding.
*/
#if((REVEAL_THE_HMAC_KEY < 0) || (CHANGE_THE_HMAC_KEY < 0) || (REVEAL_THE_HMAC_STATES < 0) || \
    (CHANGE_THE_HMAC_STATES < 0) || (REVEAL_THE_AES_KEY < 0) || (FREE_KERNEL_PANIC < 0) || (UNFORGIVABLE_KERNEL_CURSE < 0))
#warning("You mistakenly inserted the negative value.") // continue =>
#endif

#if ((DEBUG_MODE != 0) && (DEBUG_MODE != 1))
#error("Value invalid.(Debug mode)")
#endif


#endif