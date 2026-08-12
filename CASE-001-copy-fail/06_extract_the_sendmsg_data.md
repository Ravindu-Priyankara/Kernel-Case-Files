# Extracting the sendmsg data

```py
 i=d('00');
 u.sendmsg([b"A"*4+c],[(h,3,i*4),(h,2,b'\x10'+i*19),(h,4,b'\x08'+i*3),],32768);
```

- CLAIM
    - Identify exploit sending data through `sendmsg` syscall.

- TEST
    - run scripts/trace_sendmsg.bt

- RESULT
    - read artifacts/sendmsg_output.txt

- OBSERVATIONS
    - Call 40 times sendmsg syscalls, and each time send 4 bytes from the `ELF` payload.
    - Each call has three `control message headers`.

- INTERPRETATION
    - payload data
        - in script we saw this
            - `b"A"*4+c`
        - runtime we saw this
            - `AAAA\x7fELF`
        - meaning
            - 4A's + 4 bytes from ELF file.
    
    - 1st control message data
        - in script we saw this
            - `(h,3,i*4)`
        - runtime we saw it like this
            - Control message length: 20
            - Control message level: 279
            - Control message type: 3
            - Control message data: \x00\x00\x00\x00 

            - explanations
                - level -> 279 -> SOL_ALG
                    - defined in `include/linux/socket.h`
                - type -> 3 -> IP_HDRINCL
                    - defined in `include/uapi/linux/in.h`


    - 2nd control message data
        - in script we saw this
            - `(h,2,b'\x10'+i*19)`
        - runtime we saw it like this
            - Control message length: 36
            - Control message level: 279
            - Control message type: 2
            - Control message data: \x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00 

            - explanations
                - level -> 279 -> SOL_ALG
                    - defined in `include/linux/socket.h`
                - type -> 2 -> IP_TTL
                    - defined in `include/uapi/linux/in.h`

    - 3rd control message data
        - in script we saw this
            - `(h,4,b'\x08'+i*3)`
        - runtime we saw it like this
            - Control message length: 20
            - Control message level: 279
            - Control message type: 4
            - Control message data: \x08\x00\x00\x00 

            - explanations
                - level -> 279 -> SOL_ALG
                    - defined in `include/linux/socket.h`
                - type -> 4 -> IP_OPTIONS
                    - defined in `include/uapi/linux/in.h`

    - flags
        - decimal value = 32768
        - hex value = 0x8000
        - enabled flag
            - MSG_MORE
        - defined in `include/linux/socket.h`

- STATUS
    - `[CONFIRMED]`

- TODO
    - Trace ancillary-data processing inside the kernel
