# Kernel Case Files

**A Linux Kernel Investigator who documents case files.**

This repository contains my investigations into Linux kernel internals, memory, cryptographic operations, and security mechanisms.

I use source code, disassembly, debugging, tracing, and small experiments to understand what the kernel actually does.

I don't want to stop at reading the source code. I want to follow the execution, inspect the memory, compare the assembly, and verify the behavior.

Sometimes the answer is simple.

Sometimes one small detail ruins an entire week. 😂

## Case Files

### CASE-001: Copy Fail

**Investigating a cryptographic payload through the Linux kernel.**

This investigation follows a payload through the AF_ALG interface and into the kernel's AEAD implementation.

The case file documents payload reconstruction, kernel module loading, cryptographic algorithm structures, function pointers, and the investigation of a `recv()` failure.

- Focus: AF_ALG, AEAD, payload analysis, function pointers, and kernel debugging.
- Includes: investigation notes, scripts, traces, binary artifacts, and memory-layout diagrams.

[Open CASE-001](./CASE-001-copy-fail/README.md)

### CASE-002: Obliviate

**Investigating HMAC and AES key handling inside the Linux kernel.**

This investigation explores how cryptographic key material moves through the kernel's crypto implementation, with a focus on HMAC key preparation and the `authencesn` construction.

It examines key extraction, memory layout, HMAC inner and outer states, and experimental key modification using a custom kernel module.

- Focus: Linux kernel crypto, HMAC-SHA256, AES, AF_ALG, and runtime investigation.
- Includes: investigation notes, a custom LKM, tracing tools, test programs, and screenshots.

[Open CASE-002](./CASE-002-Obliviate/README.md)

### CASE-003: The Overthinker

**An experimental eBPF-based Linux security project.**

The goal is to investigate and block suspicious activity around sensitive kernel operations, including kernel module loading.

The initial implementation is written, but testing, review, and documentation are still in progress.

- Focus: eBPF, Linux Security Module (LSM) hooks, tracepoints, and runtime enforcement.
- Status: experimental; not production-ready.

[Open CASE-003](./CASE-003-The_Overthinker/README.md)

## How I Investigate

My usual approach is to follow the evidence:

1. **Read the source** — understand the intended behavior.
2. **Inspect the binary** — examine instructions, registers, structures, and function pointers.
3. **Trace execution** — observe what happens at runtime.
4. **Inspect memory** — verify addresses, layouts, and data.
5. **Test the explanation** — build a small experiment and compare the results.
6. **Document the case** — record the evidence, assumptions, and conclusions.

The goal is not just to find an answer. It's to understand *why* that answer is correct.

## Repository Structure

```text
Kernel-Case-Files/
├── CASE-001-copy-fail/
├── CASE-002-Obliviate/
├── CASE-003-The_Overthinker/
├── LICENSE
└── README.md
```

Each case file contains its own investigation notes and supporting materials. Depending on the case, this may include source code, scripts, traces, screenshots, diagrams, and test artifacts.


## Disclaimer

These case files document technical research and experiments in controlled environments.

Some techniques involve kernel memory inspection, custom kernel modules, or security enforcement. They can crash a system, expose sensitive data, or interfere with normal kernel operations.

Code and findings may depend on the kernel version, configuration, and implementation being investigated. Experimental code should not be treated as production-ready without independent review and testing.

The purpose of this repository is to document findings and make the investigation process reproducible where possible, not to claim that every observation represents a kernel vulnerability.

## Why Case Files?

Because I don't want to memorize magic.

I want to know what happens behind the function call, where the pointer leads, what the CPU executes, and why the system behaves the way it does.

**Read the source. Follow the execution. Verify the evidence.**

One case at a time.