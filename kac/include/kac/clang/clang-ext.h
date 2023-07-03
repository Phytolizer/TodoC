#ifndef KAC_CLANG_EXT_H_
#define KAC_CLANG_EXT_H_

#if defined(__STDC_VERSION__) && __STDC_VERSION__ > 201710L
#define KAC__HAS_C2X 1
#else
#define KAC__HAS_C2X 0
#endif

#ifndef __has_builtin
#define __has_builtin(x) 0
#endif

#ifndef __has_feature
#define __has_feature(x) 0
#endif

#ifndef __has_extension
#define __has_extension __has_feature
#endif

// [[x]]
#ifndef __has_c_attribute
#define __has_c_attribute(x) 0
#endif

// __attribute__((x))
#ifndef __has_attribute
#define __has_attribute(x) 0
#endif

#endif // KAC_CLANG_EXT_H_
