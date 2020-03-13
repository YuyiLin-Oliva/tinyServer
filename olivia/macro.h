#ifndef __MACRO_H
#define __MACRO_H

#include <string.h>
#include <assert.h>
#include "log.h"
//#include "util.h"

#if defined __GNUC__ || defined __llvm__
/// LIKCLY 宏的封装, 告诉编译器优化,条件大概率成立
#   define OLIVIA_LIKELY(x)       __builtin_expect(!!(x), 1)
/// UNLIKCLY 宏的封装, 告诉编译器优化,条件大概率不成立
#   define OLIVIA_UNLIKELY(x)     __builtin_expect(!!(x), 0)
#else
#   define OLIVIA_LIKELY(x)      (x)
#   define OLIVIA_UNLIKELY(x)      (x)
#endif


#define OLIVIA_ASSERT(x) \
    if(OLIVIA_UNLIKELY(!(x))) { \
        LOG_ERROR(LOG_ROOT()) << "ASSERTION: " #x \
            << "\nbacktrace:\n" \
            << olivia::BacktraceToString(100, 2, "    "); \
        assert(x);\
    }

#define OLIVIA_ASSERT2(x, w) \
    if(OLIVIA_UNLIKELY(!(x))) { \
        LOG_ERROR(LOG_ROOT()) << "ASSERTION: " #x \
            << "\n" << w \
            << "\nbacktrace:\n" \
            << olivia::BacktraceToString(100, 2, "    "); \
        assert(x); \
    }


#endif