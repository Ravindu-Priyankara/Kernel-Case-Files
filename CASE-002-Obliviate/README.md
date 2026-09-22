# CASE-002-Obliviate

## Overview

## Investigation Goals

- Understanding these concepts:
    

## Investigation Notes

### 1. Introduction

1. [Importance of the __hmac_sha256_preparekey function](01_importance_of_hmac_sha256_preparekey_func.md)

### 2. Offensive side

1. [Extracting the hmac key](02_extracting_the_hmac_key.md)
2. [Understanding the keys stored in memory](03_understanding_the_keys_stored_in_memory.md)
3. [Change the hmac keys](04_changing_the_hmac_key.md)
4. [Expose the hmac states](05_expose_the_hmac_state.md)
5. [AES and HMAC key memory layout](06_aes_and_hmac_key_memory_layout.md)

### 3. defensive side

## assets/

- Screenshots and images used to explain the investigation.

## Main tools

1. GDB
2. crash
3. radare2
4. readelf
5. objdump
6. bpftrace
7. addr2line
8. custom c programs

## Current Status



## Related Research

- [CASE-001-copy-fail](../CASE-001-copy-fail/README.md)