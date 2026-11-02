# Build Guide

This document explains how to configure and build OneLane, including the eBPF program, userspace loader, and interrupt trigger.

## 1. Project Structure

```text
OneLane/
├── config/
│   └── config.h
├── handler/
│   ├── handler.h
│   └── static_data_structures.h
├── headers/
│   ├── flags.h
│   ├── header.h
│   └── maps.h
├── helpers/
│   └── common_helpers.h
├── hooks/
│   ├── perf_event.bpf.c
│   └── sys_enter_tracepoint.bpf.c
├── triggers/
│   ├── Makefile
│   └── trigger.c
├── main.bpf.c
├── onelane.c
├── Makefile
└── build.md
```

## 2. Build Dependencies

OneLane uses Clang/LLVM to compile eBPF code and libbpf to load and interact with the generated eBPF skeleton.

Required tools:

- `clang`
- `llvm-strip`
- `bpftool`
- `gcc`
- `make`
- `libbpf`
- `libelf`
- `zlib`

On Ubuntu, the required packages can be installed with:

```bash
sudo apt update

sudo apt install -y \
    build-essential \
    clang \
    llvm \
    libbpf-dev \
    libelf-dev \
    zlib1g-dev \
    bpftool \
    linux-tools-common
```

Check that the required commands are available:

```bash
clang --version
llvm-strip --version
bpftool version
gcc --version
```

**Kernel BTF requirement**

The root Makefile generates `vmlinux.h` from the running kernel:

```bash
bpftool btf dump file /sys/kernel/btf/vmlinux format c
```

Therefore, the running kernel must expose BTF information through:

```text
/sys/kernel/btf/vmlinux
```

Check whether it exists:

```bash
ls -l /sys/kernel/btf/vmlinux
```

If it is missing, the `vmlinux.h` generation step cannot complete.

## 3. Configuration

Configuration options are located in:

```text
config/config.h
```

Default configuration:

```c
#define ENABLE_RE_ENTRY 1
#define ENABLE_x86_64_BACKPORT 0
#define DEBUG_MODE 1
```

Each option accepts only `0` or `1`. Invalid values cause a compilation error.

| Option | Default | Description |
|---|---:|---|
| `ENABLE_RE_ENTRY` | `1` | Enables the re-entry experiment configuration. |
| `ENABLE_x86_64_BACKPORT` | `0` | Enables the manual x86-64 interrupt-state detection fallback. |
| `DEBUG_MODE` | `1` | Controls debug mode. |

To change an option, edit `config/config.h` before building.

For example, to enable the manual x86-64 backport:

```c
#define ENABLE_x86_64_BACKPORT 1
```

### Important: x86-64 Backport Limitation

The manual backport in `helpers/common_helpers.h` is not a universal kernel compatibility implementation.

It uses:

- `__preempt_count`
- `bpf_this_cpu_ptr()`
- Manually defined interrupt-state masks
- x86-64-specific assumptions about the preemption counter layout

The implementation uses these masks:

```c
#define MY_NMI_MASK       0xf00000
#define MY_HARDIRQ_MASK   0xf0000
#define My_SOFTIRQ_MASK   0xff00
#define MY_SOFTIRQ_OFFSET (1ULL << 8)
```

These values are based on the x86-64 preemption counter layout used by the implementation.

**Do not assume this backport works across all kernel versions.**

The required symbol and its layout may differ depending on the kernel version and configuration. This implementation does not provide the alternative `pcpu_hot` access path or architecture-specific implementations for ARM64 and other architectures.

In particular, the manual fallback has not been implemented and verified for ARM64 or other architectures.

The default is therefore:

```c
#define ENABLE_x86_64_BACKPORT 0
```

When the native `bpf_in_nmi()`, `bpf_in_hardirq()`, and `bpf_in_serving_softirq()` helpers are available, the implementation can use those helpers without relying on the manual fallback.

When they are unavailable, enabling the backport requires verifying that the target kernel provides the expected x86-64 symbol and layout.

**The Makefile's architecture detection does not imply that the backport supports every detected architecture.**

## 4. Architecture Detection

The root Makefile automatically detects the build architecture:

```make
ARCH ?= $(shell uname -m | sed 's/x86_64/x86/' | sed 's/aarch64/arm64/')
```

The detected architecture is passed to Clang:

```make
-target bpf -D__TARGET_ARCH_$(ARCH)
```

The current mapping includes:

| System architecture | BPF target macro |
|---|---|
| `x86_64` | `__TARGET_ARCH_x86` |
| `aarch64` | `__TARGET_ARCH_arm64` |

Other architectures are not explicitly mapped by this Makefile.

## 5. Build the Main Program

Navigate to the OneLane directory:

```bash
cd CASE-004-OneLane/OneLane
```

Build the project:

```bash
make
```

The default target builds the userspace executable:

```text
build/onelane
```

### What happens during the build?

The root Makefile performs these steps:

**Step 1 — Generate `vmlinux.h`**

```bash
bpftool btf dump file /sys/kernel/btf/vmlinux format c > gen/vmlinux.h
```

Generated file:

```text
gen/vmlinux.h
```

**Step 2 — Compile the eBPF program**

```bash
clang -g -O2 -target bpf ...
```

Generated file:

```text
build/main.bpf.o
```

Debug information is stripped from the object using:

```bash
llvm-strip -g build/main.bpf.o
```

**Step 3 — Generate the eBPF skeleton**

```bash
bpftool gen skeleton build/main.bpf.o > gen/main.skel.h
```

Generated file:

```text
gen/main.skel.h
```

**Step 4 — Compile the userspace loader**

The userspace program is compiled and linked against:

```text
-lbpf -lelf -lz
```

Final executable:

```text
build/onelane
```

## 6. Build the Interrupt Trigger

The interrupt trigger has its own Makefile.

Navigate to the trigger directory:

```bash
cd triggers
```

Build:

```bash
make
```

This produces:

```text
triggers/trigger
```

The trigger Makefile uses:

```bash
gcc -fsanitize=address,undefined \
    -fno-omit-frame-pointer \
    -g \
    trigger.c \
    -o trigger \
    -lbpf
```

The trigger is built separately from the main OneLane program.

Return to the OneLane directory after building:

```bash
cd ..
```

## 7. Optional: Inspect Compilation Stages

The root Makefile provides additional targets for inspecting the eBPF compilation process.

These are useful when investigating how the source code is transformed before it becomes eBPF bytecode.

### LLVM Intermediate Representation

```bash
make ir
```

Output:

```text
build/main.bpf.ll
```

### LLVM Bitcode

```bash
make bc
```

Output:

```text
build/main.bpf.bc
```

### Preprocessed C Source

```bash
make prep
```

Output:

```text
build/main.bpf.i
```

These targets are useful for examining compiler transformations and investigating unexpected eBPF instruction generation.

## 8. Clean Build Artifacts

To remove generated files from the main project:

```bash
make clean
```

This removes:

```text
build/
gen/
```

To remove the separately compiled interrupt trigger:

```bash
cd triggers
make clean
```

This removes:

```text
trigger
```

## 9. Build Summary

From the `OneLane/` directory:

```bash
# Build the main eBPF program and userspace loader
make

# Build the interrupt trigger
make -C triggers

# Optional compilation inspection
make ir
make bc
make prep

# Clean the main project
make clean

# Clean the trigger
make -C triggers clean
```

---

**Note:** Building the project does not automatically guarantee that every feature works on every kernel version or architecture. In particular, the manual x86-64 backport requires independent verification against the target kernel.

OneLane is an experimental Linux kernel investigation. Verify kernel capabilities, BTF availability, architecture support, and configuration before running it.