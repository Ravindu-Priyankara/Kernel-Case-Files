# Linux kernel module loading mechanisms

- CLAIM
    - There are two syscalls we can use for loading a kernel module(except directly putting it into memory)
        1. finit_module (SYSCALL NUMBER = 313)
        2. init_module (SYSCALL NUMBER = 175)

- TEST
    - trace the insmod, modprobe or your custom script.

- RESULT

**Insmod utility**
<img src="./assets/insmod.png" alt="trace the insmod utility">

**Modprobe utility**
<img src="./assets/modprobe.png" alt="trace the modprobe utility">

**My custom script**
<img src="./assets/custom.png" alt="trace the custom script">

- STATUS
    - `[CONFIRM]`