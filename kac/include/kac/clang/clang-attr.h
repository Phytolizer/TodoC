#ifndef KAC_CLANG_ATTR_H_
#define KAC_CLANG_ATTR_H_

#include "kac/clang/clang-ext.h"

#if KAC__HAS_C2X
#define KAC_CLANG_ATTR(x, ...) [[clang::x __VA_OPT__((__VA_ARGS__))]]
#else
#define KAC_CLANG_ATTR(...) __attribute__((__VA_ARGS__))
#endif

#endif // KAC_CLANG_ATTR_H_
