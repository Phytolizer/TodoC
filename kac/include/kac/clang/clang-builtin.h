#ifndef KAC_CLANG_BUILTIN_H_
#define KAC_CLANG_BUILTIN_H_

#include "kac/clang/clang-ext.h"

#if __has_builtin(__builtin_assume)
#define KAC_ASSUME(x) __builtin_assume(x)
#else
#define KAC_ASSUME(x) (void)0
#endif

#if __has_builtin(__builtin_unreachable)
#define KAC_UNREACHABLE() __builtin_unreachable()
#else
#define KAC_UNREACHABLE() (void)0
#endif

#if __has_builtin(__builtin_expect)
#define KAC_EXPECT(a, b) __builtin_expect((a), (b))
#else
#define KAC_EXPECT(a, b) (a)
#endif

#if __has_builtin(__builtin_debugtrap)
#define KAC_DEBUGTRAP() __builtin_debugtrap()
#else
#include <stdlib.h>
#define KAC_DEBUGTRAP() abort()
#endif

#endif // KAC_CLANG_BUILTIN_H_
