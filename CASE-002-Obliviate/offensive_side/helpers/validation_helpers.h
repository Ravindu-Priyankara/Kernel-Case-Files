#ifndef OBLIVIATE_VALIDATION_HELPERS_H
#define OBLIVIATE_VALIDATION_HELPERS_H

#include "headers/main_header.h"

/*
*   ST_SUPPORT: The linux kernel version guard.
*
*   Arguments:
*   @W: comparison operators(ex: '<', '>', '>=', '<=', '==')
*   @X: Major kernel version
*   @Y: Minor kernel version
*   @Z: Patch/Revision level
*
*   Example usage: #if(OB_SUPPORT(>, 6, 17, 0))
*/
#define OB_SUPPORT(W, X, Y, Z) (LINUX_VERSION_CODE W KERNEL_VERSION(X, Y, Z))

static inline int obliviate_permission_check(void){
    if(!capable(CAP_SYS_ADMIN))
        return -EPERM;
    return 0;
}


#endif