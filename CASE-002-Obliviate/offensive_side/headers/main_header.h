#ifndef OBLIVATE_MAIN_HEADER_H
#define OBLIVATE_MAIN_HEADER_H

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>

#include <linux/capability.h>
#include <linux/types.h>
#include <linux/version.h>
#include <linux/kprobes.h>
#include <linux/compiler.h>
#include <crypto/sha2.h>
#include <linux/err.h>
#include <linux/uaccess.h>
#include <linux/string.h>
#include <linux/ptrace.h>
#include <linux/rtnetlink.h>
#include <crypto/authenc.h>
#include <asm/byteorder.h>
#include <crypto/hmac.h>
#include <linux/array_size.h>

#ifndef O_MAX_SIZE
#define O_MAX_SIZE 64
#endif

static bool probe_hooked __read_mostly = false;

#endif