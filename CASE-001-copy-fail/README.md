# CASE-001-copy-fail

## Overview

This case is an investigation into an AF_ALG-related kernel exploit and its execution path inside the Linux kernel.

I investigated the kernel using static analysis, dynamic tracing, debugging, and small custom programs.

The investigation is still ongoing.

## Investigation Goals

- Understanding these concepts:
    1. How does this exploit work?
    2. What are the underlying mechanisms of this exploit?

## Investigation Notes

### Payload Analysis

1. [Understand the Exploit](01_understand_the_exploit.md)
2. [Extracting the Payload](02_extracting_the_payload.md)
3. [Reconstruct the Payload](03_reconstruct_the_payload.md)
4. [Original Payload vs Reconstructed Payload](04_original_payload_vs_reconstructed_payload.md)
5. [Build a Minimal Payload](05_build_a_minimal_payload.md)
6. [Extract the sendmsg Data](06_extract_the_sendmsg_data.md)
7. [recv Syscall Failure](07_recv_syscall_failure.md)
8. [Given File Modified](08_given_file_modified.md)

### AF_ALG and Crypto Subsystem

9. [AF_ALG Module Loading](09_af_alg_module_loading.md)
10. [Few More Modules Loaded](10_few_more_modules_loaded.md)
11. [Jump to algif_aead Module](11_jump_to_algif_aead_module.md)
12. [Crypto Key Randomization](12_crypto_key_randomization.md)
13. [Decoding the Key Bytes](13_decoding_the_key_bytes.md)
14. [Crypto AEAD Struct Involvement](14_crypto_aead_struct_involvement.md)
15. [Set Maximum Authsize According to the Algorithm](15_set_maximum_authsize_according_to_the_algorithm.md)
16. [Decoding the CRA Flags](16_decoding_the_cra_flags.md)
17. [CRA Name and CRA Driver Name](17_cra_name_&_cra_driver_name.md)
18. [Manual Pointer Subtraction to Jump AEAD Alg](18_manual_pointer_subtraction_to_jump_aead_alg.md)
19. [Check Setkey Use SHASH or Not](19_check_setkey_use_shash_or_not.md)
20. [Get the Setkey Function Pointer (SHASH Alg)](20_get_the_setkey_function_pointer%28shash_alg%29.md)
21. [HMAC-SHA256 Preparekey](21_hmac_sha256_preparekey.md)
22. [Extracting Inner and Outer States](22_Extracting_inner_and_outer_states.md)
23. [Replace the Authsize](23_replace_the_authsize.md)

## Scripts/

1. [Decode the zlib based compressed payload](scripts/decode_the_loop.py)
2. [Extract the elf payload](scripts/extract_the_payload.py)
3. [Create custom elf](scripts/custom_elf.py)
4. [exploit reproducer](scripts/reproducer/exploit.c)
5. [Socket tracer(LKM based)](scripts/sys_passpayload/socket_tracer/socket_tracer.c)
6. [Socket caller](scripts/sys_passpayload/socket_caller.c)
7. [Bind syscall caller](scripts/sys_passpayload/bind_caller.c)
8. [Find setkey address via shash_alg](scripts/shash_alg.bt)
9. [Trace sendmsg](scripts/trace_sendmsg.bt)
10. [Check using_shash enable or not](scripts/using_shash-tracer.bt)
11. [Setkey](scripts/sys_passpayload/setkey.c)
12. [Monitor key preparation](scripts/sys_passpayload/key_prepare.bt)
13. [State extraction](scripts/sys_passpayload/block_state_extractor.bt)
14. [Key randomizer](scripts/randomizer/key_randomizer.c)
15. [Monitor authsize changer](scripts/sys_passpayload/authsize.c)

## Payload/

1. [Reconstructed payload](payload/reconstructed_payload.asm)
- Others are executables, so check it yourself..

## Artifacts/

1. [My c reproducer trace result](artifacts/trace/c-trace-output.md)
2. [Original payload trace result](artifacts/trace/python-trace-output.md)
3. [AF_ALG module relocations table](artifacts/relocation.txt)
4. [AF_ALG module sections](artifacts/sections.txt)
5. [Sendmsg output](artifacts/sendmsg_output.txt)

## assets/

- Screenshots and images used to explain the investigation.

## Main tools

1. GDB
2. crash
3. radare2
4. readelf
5. objdump
6. bpftrace
7. xxd
8. dd
9. custom c programs
10. python scripts

## Current Status

The investigation has covered the AF_ALG execution path, AEAD structures, HMAC-SHA256 key preparation, and related key material.

Some parts of the investigation are still being analyzed.

**This case is not considered fully closed until the remaining research questions are documented and the results are reproducible.**

## Related Research

- CASE-002-Obliviate