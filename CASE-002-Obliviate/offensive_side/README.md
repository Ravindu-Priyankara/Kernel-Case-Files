# Obliviate — Offensive Side

## Overview

This directory contains the kernel module used in CASE-002: Obliviate.

The main goal of this research is to investigate cryptographic key material inside the Linux kernel using:

* Loadable Kernel Module (LKM)
* kprobe
* Kernel function arguments
* Kernel memory reading and writing

The research focuses on HMAC and AES key material, including HMAC-SHA256 key preparation and cryptographic state handling.

This is an ongoing research project.

---

## Research Goals

The current research includes:

* Extracting the HMAC key.
* Changing the HMAC key.
* Extracting HMAC inner and outer states.
* Extracting the AES key.
* Investigating the effects of changing cryptographic key material.
* Understanding kernel memory safety, concurrency, and system stability.

Each research operation is controlled through a configuration flag.

---

## Directory Structure

```text
offensive_side/
├── config/
│   └── obliviate_config.h
├── headers/
│   ├── custom_header.h
│   ├── kallsyms_header.h
│   └── main_header.h
├── helpers/
│   ├── aes_helpers.h
|   ├── composite_helpers.h
│   ├── hmac_helpers.h
│   ├── hmac_states_helpers.h
│   └── validation_helpers.h
├── Makefile
├── obliviate.c
└── README.md
```

---

## Configuration

Configuration file:

[obliviate_config.h](config/obliviate_config.h)

The configuration file controls which research operation is enabled.

Only **one research flag can be enabled at a time**.

The configuration includes:

| Flag                     | Purpose                                 |
| ------------------------ | --------------------------------------- |
| `REVEAL_THE_HMAC_KEY`    | Extract the HMAC key                    |
| `CHANGE_THE_HMAC_KEY`    | Change the HMAC key                     |
| `REVEAL_THE_HMAC_STATES` | Extract HMAC states                     |
| `CHANGE_THE_HMAC_STATES` | Future HMAC state modification research |
| `REVEAL_THE_AES_KEY`     | Extract the AES key                     |
| `FREE_KERNEL_PANIC`      | Experimental AES key modification       |
| `UNFORGIVABLE_KERNEL_CURSE ` | Full automatic method               |
| `DEBUG_MODE`             | Enable or disable debug mode            |

### Configuration Rules

* Enable only one research flag per iteration.
* At least one research flag must be enabled.
* Multiple research flags are rejected during compilation.
* HMAC state modification is temporarily disabled.
* Debug mode accepts only `0` or `1`.

The configuration uses compile-time checks to prevent invalid combinations.

---

## Source Files

### Main Module

[obliviate.c](obliviate.c)

The main kernel module entry point.

It is responsible for initializing and cleaning up the module and connecting the research helpers.

### Configuration

[obliviate_config.h](config/obliviate_config.h)

Contains the research flags and compile-time validation rules.

### AES Helpers

[aes_helpers.h](helpers/aes_helpers.h)

Contains the kprobe handlers related to AES key extraction and experimental key modification.

The handlers target `__hmac_sha256_preparekey`.

### Composite Helpers

[composite_helpers.h](helpers/composite_helpers.h)

Automate the keys extraction and changing.

### HMAC Helpers

[hmac_helpers.h](helpers/hmac_helpers.h)

Contains the HMAC key-related research implementation.

### HMAC State Helpers

[hmac_states_helpers.h](helpers/hmac_states_helpers.h)

Contains the HMAC inner and outer state research implementation.

### Validation Helpers

[validation_helpers.h](helpers/validation_helpers.h)

Contains validation-related helper functions.

### Custom Headers

[custom_header.h](headers/custom_header.h)

Contains custom declarations and shared definitions.

### Kallsyms Header

[kallsyms_header.h](headers/kallsyms_header.h)

Contains declarations related to kernel symbol lookup.

### Main Header

[main_header.h](headers/main_header.h)

Contains shared headers, definitions, and declarations used by the module.

---

## Kprobe Target

The current kprobe targets:

```c
__hmac_sha256_preparekey
```

This function is used during HMAC-SHA256 key preparation.

The research uses the function's kernel arguments to investigate the key material and related memory.

---

## Safety Notice

This module is intended for controlled kernel research and testing.

Some research modes read or modify kernel memory. Incorrect assumptions about memory layout, pointer relationships, or key ownership can lead to memory corruption, crashes, or unexpected behavior.

The experiments should be performed in an isolated test environment.

Do not enable experimental modification modes without understanding their potential effects.

---

## Current Status

The project is ongoing.

Current research areas:

* HMAC key extraction
* HMAC key modification
* HMAC state extraction
* AES key extraction
* Kernel memory manipulation

Future research will investigate HMAC state modification separately.

---

## Related Research

* CASE-001: [Copy Fail](../../CASE-001-copy-fail/README.md)
* CASE-002: Obliviate
