#ifndef KAC_CLANG_WARN_H_
#define KAC_CLANG_WARN_H_

#include "kac/clang/clang-ext.h"

#ifdef __clang__

#pragma clang system_header

#pragma clang diagnostic warning "-Wall"
#pragma clang diagnostic warning "-Wextra"

#pragma clang diagnostic error "-Warray-bounds-pointer-arithmetic"
#pragma clang diagnostic warning "-Warray-parameter"
#pragma clang diagnostic error "-Wbitfield-enum-conversion"
#pragma clang diagnostic error "-Wbool-operation"
#pragma clang diagnostic warning "-Wbitwise-op-parentheses"
#pragma clang diagnostic warning "-Wcast-function-type"
#pragma clang diagnostic error "-Wcomma"
#pragma clang diagnostic warning "-Wconversion"
#pragma clang diagnostic warning "-Wcovered-switch-default"
#pragma clang diagnostic error "-Wdeprecated"
#pragma clang diagnostic error "-Wembedded-directive"
#pragma clang diagnostic ignored "-Wempty-translation-unit"

#ifndef KAC_WARN_NO_PEDANTIC
#pragma clang diagnostic warning "-Wpedantic"
#endif

#endif // __clang__

#endif // KAC_CLANG_WARN_H_
