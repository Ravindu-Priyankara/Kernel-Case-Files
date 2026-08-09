#!/usr/bin/env python3

import struct
import sys

def main(path, output):

    with open(path, "rb") as f:
        data = f.read()

    # ------------------------------------------------------------
    # ELF header
    # ------------------------------------------------------------

    if data[:4] != b"\x7fELF":
        raise ValueError("Not an ELF file")

    if data[4] != 2 or data[5] != 1:
        raise ValueError("Expected ELF64 little-endian")

    ehdr = list(struct.unpack_from(
        "<16sHHIQQQIHHHHHH",
        data,
        0
    ))

    (
        e_ident,
        e_type,
        e_machine,
        e_version,
        e_entry,
        e_phoff,
        e_shoff,
        e_flags,
        e_ehsize,
        e_phentsize,
        e_phnum,
        e_shentsize,
        e_shnum,
        e_shstrndx,
    ) = ehdr

    # ------------------------------------------------------------
    # Find executable PT_LOAD
    # ------------------------------------------------------------

    executable = None

    for i in range(e_phnum):

        off = e_phoff + i * e_phentsize

        phdr = struct.unpack_from(
            "<IIQQQQQQ",
            data,
            off
        )

        p_type, p_flags, p_offset, p_vaddr, p_paddr, \
        p_filesz, p_memsz, p_align = phdr

        # PT_LOAD + PF_X
        if p_type == 1 and (p_flags & 1):
            executable = phdr
            break

    if executable is None:
        raise RuntimeError("Executable PT_LOAD not found")

    (
        p_type,
        p_flags,
        p_offset,
        p_vaddr,
        p_paddr,
        p_filesz,
        p_memsz,
        p_align,
    ) = executable

    # ------------------------------------------------------------
    # Find .text
    # ------------------------------------------------------------

    if e_shoff == 0 or e_shnum == 0:
        raise RuntimeError("No section headers")

    # Section-name string table
    shstr_off = e_shoff + e_shstrndx * e_shentsize

    shstr = struct.unpack_from(
        "<IIQQQQIIQQ",
        data,
        shstr_off
    )

    shstr_data = data[
        shstr[4]:shstr[4] + shstr[5]
    ]

    text = None

    for i in range(e_shnum):

        off = e_shoff + i * e_shentsize

        sh = struct.unpack_from(
            "<IIQQQQIIQQ",
            data,
            off
        )

        sh_name = sh[0]
        sh_offset = sh[4]
        sh_size = sh[5]

        end = shstr_data.find(b"\x00", sh_name)

        if end == -1:
            continue

        name = shstr_data[sh_name:end]

        if name == b".text":
            text = sh
            break

    if text is None:
        raise RuntimeError(".text not found")

    (
        sh_name,
        sh_type,
        sh_flags,
        sh_addr,
        sh_offset,
        sh_size,
        sh_link,
        sh_info,
        sh_addralign,
        sh_entsize,
    ) = text

    text_data = data[
        sh_offset:sh_offset + sh_size
    ]

    # ------------------------------------------------------------
    # New minimal layout
    # ------------------------------------------------------------

    new_phoff = 0x40

    # ELF header = 64
    # PHDR       = 56
    new_text_offset = 64 + 56

    # Keep original virtual mapping delta.
    #
    # Original:
    #     p_vaddr - p_offset
    #
    # New:
    #     new_vaddr - new_offset

    load_bias = p_vaddr - p_offset

    new_vaddr = new_text_offset + load_bias

    # ------------------------------------------------------------
    # Rewrite ELF header
    # ------------------------------------------------------------

    ehdr[5] = new_phoff      # e_phoff
    ehdr[6] = 0              # e_shoff
    ehdr[10] = 1             # e_phnum
    ehdr[11] = 0             # e_shentsize
    ehdr[12] = 0             # e_shnum
    ehdr[13] = 0             # e_shstrndx

    # Entry point now points to new .text address
    ehdr[4] = new_vaddr

    new_ehdr = struct.pack(
        "<16sHHIQQQIHHHHHH",
        *ehdr
    )

    # ------------------------------------------------------------
    # Rewrite program header
    # ------------------------------------------------------------

    new_phdr = struct.pack(
        "<IIQQQQQQ",

        1,                  # PT_LOAD
        5,                  # PF_R | PF_X

        new_text_offset,   # p_offset
        new_vaddr,         # p_vaddr
        new_vaddr,         # p_paddr

        len(text_data),    # p_filesz
        len(text_data),    # p_memsz

        0x1000              # p_align
    )

    # ------------------------------------------------------------
    # Build ELF
    # ------------------------------------------------------------

    with open(output, "wb") as f:

        f.write(new_ehdr)
        f.write(new_phdr)
        f.write(text_data)

    print(f"[+] Created: {output}")
    print(f"[+] Size: {64 + 56 + len(text_data)} bytes")


if __name__ == "__main__":

    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} <input-elf> <output-elf>")
        sys.exit(1)

    main(sys.argv[1], sys.argv[2])
