#include "header.h"

#if ENABLE_FINIT_MODULE_TRACER
#include "finit_module_tracepoint.bpf.c"
#endif

#if ENABLE_INIT_MODULE_TRACER
#include "init_module_tracepoint.bpf.c"
#endif

#if ENABLE_KERNEL_LOAD_DATA_ENFORCEMENT
#include "kernel_load_data_lsm.bpf.c"
#endif

#if ENABLE_KERNEL_READ_FILE_ENFORCEMENT
#include "kernel_read_file_lsm.bpf.c"
#endif

#if ENABLE_SB_MOUNT_ENFORCEMENT
#include "sb_mount_lsm.bpf.c"
#endif

#if ENABLE_MOVE_MOUNT_ENFORCEMENT
#include "move_mount_lsm.bpf.c"
#endif

#if ENABLE_FILE_OPEN_ENFORCEMENT
#include "file_open_lsm.bpf.c"
#endif

#if ENABLE_PATH_RENAME_ENFORCEMENT
#include "path_rename_lsm.bpf.c"
#endif

#if ENABLE_PATH_MKDIR_ENFORCEMENT
#include "path_mkdir_lsm.bpf.c"
#endif