# Kernel load data LSM

- CLAIM
    - Block all modules that tried to load via init_module.

- INTERPRETATION
    - What types of things can trigger the `init_module` syscall
        1. Kernel module
        2. Linux firmware
        3. etc.

    - Our approach
        - Block all kernel modules that try to load via the `init_module` syscall

    - How we filter Kernel modules to BLOCK
        - We checked kernel_load_data_id is equal to LOADING_MODULE, if it yes we blocked it, 
        - because it is a kernel module.

    - Architecture of kernel_load_data LSM hook
        1. filter kernel modules
        2. use ringbuf to pass event details to userland
        3. If it fails, we update the error matrix

- STATUS
    - `[CONFIRM]`