# recv syscall failure

- CLAIM
    - `recv` syscall failed all the time.

- TEST
    - run /scripts/reproducer/exploit
    - settings = enable debug info

- RESULT

**recv syscall failure in debug message perspective**
<img src="./assets/recv-failure-debug-msg.png" alt="recv syscall failure">

**recv syscall failure in strace**
<img src="./assets/recv-failure-strace.png" alt="recv syscall failure in strace">

- TODO
    - Find a reason for the recv syscall failure.

- STATUS
    - `[CONFIRMED]`