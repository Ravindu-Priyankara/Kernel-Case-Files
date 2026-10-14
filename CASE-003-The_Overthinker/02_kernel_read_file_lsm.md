# Kernel read file LSM

- CLAIM
    - When someone tries to load a module via the `finit_module` syscall, they should pass our test; they will be blocked

- INTERPRETATION
    - First, we filter the events that try to load Linux kernel modules.
    - Next, they need to pass various checks

- Checks
    1. First of all, we check whether the kernel module is owned by root or not.
    2. Next check is to see whether the kernel module has write permission except root; if the answer is yes, you are blocked
    3. Next one is folder owner check; if it is not owned by root, we block it.
    4. Same as file, our next check is folder write permission, so except root, no one should have write permission.
    5. Next, we check whether the module location is equal to the whitelisted path; if it is not equal, we block it.

- STATUS
    - `[CONFIRM]`