# HOOKS

| Name | purpose |
|-----|----|
| file_open | Block file operations inside whitelist path(writing side only) |
| kernel_load_data | Block kernel modules that try to load via init_module syscall |
| kernel_read_file | checkpoint to when module load via finit_module syscall |
| move_mount | block bind mounting to whitelist path |
| sb_mount | block bind mounting to whitelist path |
| path_mkdir | stop making folders inside whitelist folder |
| path_rename | block if someone try to mv their files to whitelist path |

<!-- Oh my god, I feel like a month of work did like one day after writing this documentation. --!>