#ifndef ONELANE_CONFIG_H
#define ONELANE_CONFIG_H

#ifndef ENABLE_RE_ENTRY
#define ENABLE_RE_ENTRY 1
#endif

#ifndef ENABLE_x86_64_BACKPORT
#define ENABLE_x86_64_BACKPORT 0
#endif

#ifndef DEBUG_MODE
#define DEBUG_MODE 1
#endif

#if((ENABLE_RE_ENTRY != 0) && (ENABLE_RE_ENTRY != 1))
#error "Just 1 or 0"
#endif

#if((ENABLE_x86_64_BACKPORT != 0) && (ENABLE_x86_64_BACKPORT != 1))
#error"just 1 or 0"
#endif

#if((DEBUG_MODE != 0) && (DEBUG_MODE != 1))
#error"just 1 or 0"
#endif

#endif