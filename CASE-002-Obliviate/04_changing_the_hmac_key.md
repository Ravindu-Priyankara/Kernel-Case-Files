# Changing the HMAC key

- CLAIM
    - Change the hmac key inside the kernel memory.

- TEST
    - open offensive_side/config/obliviate_config.h
    - enable this flag
        - CHANGE_THE_HMAC_KEY
    - load the kernel module
    - run triggers/get_hash
    - unload the kernel module
    - run triggers/get_hash

- RESULT
<img src="./assets/hmac_key_change.png" alt="hmac key changing">

- OBSERVATION
    - Even with the same program, the same key, and the same message, we can clearly see that the hash value changed completely after loading the module.

- INTERPRETATION
    - to change the hmac key we follow these steps
        1. The HMAC key is a byte array.
        2. We replace that byte array with our byte array(our key).

    - Special things.
        - We avoid memcpy there. 
        - Because there wasn't fault protection, 
        - it could cause a kernel panic if something went wrong.
        - So we used the copy_to_kernel_nofault api to more safety. 

    - But with some tricks. So if you need to understand that, read this file.
        - [hmac_helpers](offensive_side/helpers/hmac_helpers.h)

- STATUS
    - `[CONFIRM]`