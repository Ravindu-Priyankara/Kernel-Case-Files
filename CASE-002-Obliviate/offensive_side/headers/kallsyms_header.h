#ifndef OBLIVIATE_KALLSYMS_HEADER_H
#define OBLIVIATE_KALLSYMS_HEADER_H

#if (!REVEAL_THE_HMAC_KEY || !REVEAL_THE_AES_KEY)
typedef unsigned long (*kallsyms_lookup_name_t)(const char *name);
kallsyms_lookup_name_t my_kallsyms_lookup_name __ro_after_init = NULL;
#endif

#endif