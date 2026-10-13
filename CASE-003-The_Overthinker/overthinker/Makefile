# Directories
CONFIG     := config
HEADERS    := headers
LSM        := lsm
TRACEPOINT := tracepoint
HELPERS	   := helpers
BUILD_DIR  := build
GEN_DIR    := gen

# Toolchain
CLANG      ?= clang
LLVM_STRIP ?= llvm-strip
BPFTOOL    ?= bpftool
CC         ?= gcc

# Target architecture detection
ARCH ?= $(shell uname -m | sed 's/x86_64/x86/' | sed 's/aarch64/arm64/')

# Include paths (adds -I./gen so vmlinux.h can be included cleanly)
INCLUDES   := -I. -I./$(GEN_DIR) -I./$(CONFIG) -I./$(HEADERS) -I./$(LSM) -I./$(TRACEPOINT) -I./$(HELPERS)

# Flags
BPF_CFLAGS := -g -O2 -target bpf -D__TARGET_ARCH_$(ARCH) $(INCLUDES)
CFLAGS     := -g -Wall $(INCLUDES)
#for debug
#CFLAGS := -g3 -O0 -fsanitize=address,undefined -fno-omit-frame-pointer -Wall $(INCLUDES)
LIBS       := -lbpf -lelf -lz

# Files & Targets
BPF_SRC    := main.bpf.c
BPF_OBJ    := $(BUILD_DIR)/main.bpf.o
SKEL_HDR   := $(GEN_DIR)/main.skel.h
USER_SRC   := overthinker.c
TARGET     := $(BUILD_DIR)/overthinker

.PHONY: all clean

all: $(TARGET)

# 1. Create build/ and gen/ directories
$(BUILD_DIR) $(GEN_DIR):
	@mkdir -p $@

# 2. Generate vmlinux.h from running kernel BTF
$(GEN_DIR)/vmlinux.h: | $(GEN_DIR)
	@echo "  GEN-BTF  $@"
	@$(BPFTOOL) btf dump file /sys/kernel/btf/vmlinux format c > $@

# 3. Compile BPF code to BPF bytecode object (.o)
$(BPF_OBJ): $(BPF_SRC) $(GEN_DIR)/vmlinux.h | $(BUILD_DIR)
	@echo "  BPF-CC   $@"
	@$(CLANG) $(BPF_CFLAGS) -c $< -o $@
	@$(LLVM_STRIP) -g $@

# 4. Generate C skeleton header from BPF object
$(SKEL_HDR): $(BPF_OBJ) | $(GEN_DIR)
	@echo "  GEN-SKEL $@"
	@$(BPFTOOL) gen skeleton $< > $@

# 5. Compile userland program and link libbpf
$(TARGET): $(USER_SRC) $(SKEL_HDR) | $(BUILD_DIR)
	@echo "  CC       $@"
	@$(CC) $(CFLAGS) $< -o $@ $(LIBS)
	@echo "Build complete: $@"

clean:
	@echo "  CLEAN"
	@rm -rf $(BUILD_DIR) $(GEN_DIR)