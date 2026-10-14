#ifndef OVERTHINKER_CONFIG_H 
#define OVERTHINKER_CONFIG_H

// Flags you should configure
#ifndef ENABLE_TRACING
#define ENABLE_TRACING 1
#endif

#ifndef ENABLE_ENFORCEMENT
#define ENABLE_ENFORCEMENT 1
#endif

#ifndef DEBUG_MODE
#define DEBUG_MODE 0
#endif

#ifndef ERROR_MATRIX
#define ERROR_MATRIX 1
#endif

#ifndef BLOCK_ANY_ATTACK
#define BLOCK_ANY_ATTACK 0
#endif

// how many times we need to go back and check parent folder i_ino and s_dev
#ifndef DIR_DEPTH
#define DIR_DEPTH 12
#endif

// keep it in seconds
#ifndef ERROR_MATRIX_DELAY
#define ERROR_MATRIX_DELAY 60 * 60 // every 1 hour
//#define ERROR_MATRIX_DELAY 1 * 60 //debug
#endif

// control panel
#if ENABLE_TRACING

#ifndef ENABLE_FINIT_MODULE_TRACER
#define ENABLE_FINIT_MODULE_TRACER 1
#endif

#ifndef ENABLE_INIT_MODULE_TRACER
#define ENABLE_INIT_MODULE_TRACER 1
#endif

#endif

#if ENABLE_ENFORCEMENT

#ifndef ENABLE_KERNEL_LOAD_DATA_ENFORCEMENT
#define ENABLE_KERNEL_LOAD_DATA_ENFORCEMENT 1
#endif

#ifndef ENABLE_KERNEL_READ_FILE_ENFORCEMENT
#define ENABLE_KERNEL_READ_FILE_ENFORCEMENT 1
#endif

#ifndef ENABLE_SB_MOUNT_ENFORCEMENT
#define ENABLE_SB_MOUNT_ENFORCEMENT 1
#endif

#ifndef ENABLE_MOVE_MOUNT_ENFORCEMENT
#define ENABLE_MOVE_MOUNT_ENFORCEMENT 1
#endif

#ifndef ENABLE_FILE_OPEN_ENFORCEMENT
#define ENABLE_FILE_OPEN_ENFORCEMENT 1
#endif

#ifndef ENABLE_PATH_RENAME_ENFORCEMENT
#define ENABLE_PATH_RENAME_ENFORCEMENT 1
#endif

#ifndef ENABLE_PATH_MKDIR_ENFORCEMENT
#define ENABLE_PATH_MKDIR_ENFORCEMENT 1
#endif

#endif

#ifndef EPERM
#define EPERM 1
#endif

/*
*   Look, I don't care who you are: 
*   leave this flag alone, or enjoy explaining to the security team why eBPF suddenly can't see anything.
*/
#ifndef O_WRONLY
#define O_WRONLY 00000001
#endif

#ifndef O_RDWR
#define O_RDWR 00000002
#endif

#ifndef O_CREAT
#define O_CREAT 00000100
#endif


// validation{Don't mess with this at all}
#if((ENABLE_TRACING != 0) && (ENABLE_TRACING != 1))
#error"Invalid enforcement flag"
#endif

#if((ENABLE_ENFORCEMENT != 0) && (ENABLE_ENFORCEMENT != 1))
#error"Invalid enforcement flag"
#endif

#if((ENABLE_ENFORCEMENT != 1) && (ENABLE_TRACING != 1))
#error"What should I do?"
#endif

#if((ENABLE_FINIT_MODULE_TRACER != 0) && (ENABLE_FINIT_MODULE_TRACER != 1))
#error"Invalid flag!"
#endif

#if((ENABLE_INIT_MODULE_TRACER != 0) && (ENABLE_INIT_MODULE_TRACER != 1))
#error"Invalid flag!"
#endif

#if((ENABLE_SB_MOUNT_ENFORCEMENT != 0) && (ENABLE_SB_MOUNT_ENFORCEMENT != 1))
#error"Invalid flag"
#endif

#if((ENABLE_MOVE_MOUNT_ENFORCEMENT != 0) && (ENABLE_MOVE_MOUNT_ENFORCEMENT != 1))
#error"Invalid flag"
#endif

#if((ENABLE_FILE_OPEN_ENFORCEMENT != 0) && (ENABLE_FILE_OPEN_ENFORCEMENT != 1))
#error"Invalid flag"
#endif

#if((ENABLE_PATH_RENAME_ENFORCEMENT != 0) && (ENABLE_PATH_RENAME_ENFORCEMENT != 1))
#error"Invalid flag"
#endif

#if((ENABLE_PATH_MKDIR_ENFORCEMENT != 0) && (ENABLE_PATH_MKDIR_ENFORCEMENT != 1))
#error"Invalid flag"
#endif

#if((BLOCK_ANY_ATTACK != 0) && (BLOCK_ANY_ATTACK != 1))
#error"Invalid flag"
#endif

#if((DEBUG_MODE != 0) && (DEBUG_MODE != 1))
#error"Invalid debug mode"
#endif

#if((ERROR_MATRIX != 0) && (ERROR_MATRIX != 1))
#error"Invalid error matrix flag"
#endif

#if(ERROR_MATRIX < 0)
#error"Hey, time traveler, you can’t go back. There’s nothing left there to save."
#endif

#if((!ERROR_MATRIX) && (ERROR_MATRIX_DELAY)) 
#warning"Did you forget to set the error matrix delay?"
#endif

#if(ERROR_MATRIX_DELAY > 24 * 60 * 60)
#warning"This delay is great. It matches my social life — completely dead."
#endif

#if (EPERM != 1)
#error"You cant change eperm value"
#endif

#if(DIR_DEPTH < 0 )
#error"Huh, are you serious right now?"
#endif

#if(DIR_DEPTH > 15)
#error"Put your own credit card on the AWS billing account first."
#endif

#if((O_WRONLY != 00000001) || (O_RDWR != 00000002) || (O_CREAT != 00000100))
#error"Don't touch this flag unless your goal is to invite hackers to store their malware in our most trusted directory."
#endif

#endif