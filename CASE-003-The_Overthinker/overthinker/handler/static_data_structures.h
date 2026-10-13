#ifndef OVERTHINKER_STATIC_DATA_STRUCTURES_H
#define OVERTHINKER_STATIC_DATA_STRUCTURES_H

/*
*   This array stores the event strings.
*/
static const char * const EVENT_STRING[EVT_MAX] = {
    [EVT_FINIT_MODULE] = "triggered finit_module syscall!",
    [EVT_INIT_MODULE] = "triggered init module syscall!",
    [EVT_LOAD_DATA] = "Tried to load lkm via a prohibited method!",
    [EVT_FILE_NOT_FOUND] = "File not found!",
    [EVT_PARENT_DIR_NOT_FOUND] = "Parent directory not found!",
    [EVT_FAILED_TO_EXTRACT_SUPER_BLOCK] = "Failed to extract super block!",
    [EVT_FAILED_TO_GET_INODE_NUMBER] = "Failed to get inode number",
    [EVT_FAILED_TO_GET_S_DEV] = "Failed to get s_dev!",
    [EVT_NON_WHITELIST_PATH] = "Try to module load via non whitelisted path!",
    [EVT_FAILED_TO_GET_INODE] = "Failed to get inode!",
    [EVT_FAILED_TO_GET_FILE_UID] = "Failed to get file UID!",
    [EVT_ROOT_NOT_OWN_THIS_FILE] = "Try to run module that not owned by root!",
    [EVT_FAILED_TO_GET_FOLDER_UID] = "Failed to get folder UID!",
    [EVT_ROOT_NOT_OWN_THIS_FOLDER] = "Try to run module but folder not owned by root!",
    [EVT_INODE_MODE_NOT_FOUND] = "Failed to get inode number!",
    [EVT_UNSAFE_WRITE_PERMISSION] = "Unsafe write permission detected!",
    [EVT_PATH_NOT_FOUND] = "Path not found, pls bring a torch next time!",
    [EVT_TRY_TO_MOUNT_RESTRICTED_PATH] = "Try mounting to the restricted path!",
    [EVT_FAILED_TO_GET_FILE_FLAGS] = "Filed to get file flags!",
    [EVT_NO_PERM_TO_MODIFI_WHITELIST_PATH_HAS_DATA] = "Try to modify our whitelisted path has data!",
    [EVT_TRY_TO_MOVE_FILE_TO_OUR_WHITELIST_PATH] = "Try to move file to our whitelist past!",
    [EVT_EXCESSIVE_DEPTH] = "So many nested sub-directories detected!",
    [EVT_NO_PERM_TO_MAKE_FOLDERS_ON_WHITELIST_PATH] = "Try to make folders on our whitlisted path!",
};

/*
*   This array stores the error matrix strings.
*/
static const char * const error_codes[MAX_ERRORS] = {
    [ERR_RINGBUF_RESERV] = "Ringbuf reserv failed",
    [ERR_SWAPPER_OR_INIT_PROCESS_ACCESS_FINIT_MODULE] = "Swapper or init process involment",
    [ERR_COMM] = "Failed to extract comm",
    [ERR_INVALID_MASK] = "Invalid bitmask flags",
    [ERR_FILE_NOT_FOUND] = "File not found!",
    [ERR_PARENT_DIR_NOT_FOUND] = "Parent directory not found!",
    [ERR_FAILED_TO_EXTRACT_SUPER_BLOCK] = "Failed to extract super block!",
    [ERR_FAILED_TO_GET_INODE_NUMBER] = "Failed to get inode number",
    [ERR_FAILED_TO_GET_S_DEV] = "Failed to get s_dev!",
    [ERR_NON_WHITELIST_PATH] = "Try to module load via non whitelisted path!",
    [ERR_FAILED_TO_GET_INODE] = "Failed to get inode!",
    [ERR_FAILED_TO_GET_FILE_UID] = "Failed to get file UID!",
    [ERR_ROOT_NOT_OWN_THIS_FILE] = "Try to run module that not owned by root!",
    [ERR_FAILED_TO_GET_FOLDER_UID] = "Failed to get folder UID!",
    [ERR_ROOT_NOT_OWN_THIS_FOLDER] = "Try to run module but folder not owned by root!",
    [ERR_INODE_MODE_NOT_FOUND] = "Failed to get inode mode!",
    [ERR_UNSAFE_WRITE_PERMISSION] = "Unsafe write permission detected!",
    [ERR_PATH_NOT_FOUND] = "Path not found!",
    [ERR_TRY_TO_MOUNT_RESTRICTED_PATH] = "Try mounting to the restricted path!",
    [ERR_FAILED_TO_GET_FILE_FLAGS] = "Filed to get file flags!",
    [ERR_NO_PERM_TO_MODIFI_WHITELIST_PATH_HAS_DATA] = "Try to modify our whitelisted path has data!",
    [ERR_TRY_TO_MOVE_FILE_TO_OUR_WHITELIST_PATH] = "Try to move file to our whitelist past!",
    [ERR_EXCESSIVE_DEPTH] = "So many nested sub-directories detected!",
    [ERR_NO_PERM_TO_MAKE_FOLDERS_ON_WHITELIST_PATH] = "Try to make folders on our whitlisted path!",
};

#endif