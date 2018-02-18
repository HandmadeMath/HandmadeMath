// Initializer/finalizer sample for MSVC and GCC/Clang.
// 2010-2016 Joe Lowe. Released into the public domain.
#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
    #define _INITIALIZER_T(f) f##_t_
    #define _INITIALIZER_U(f) f##_
    #define INITIALIZER(f) \
        static void f(void); \
        struct _INITIALIZER_T(f) { _INITIALIZER_T(f)(void) { f(); } }; static _INITIALIZER_T(f) _INITIALIZER_U(f); \
        static void f(void)
#elif defined(_MSC_VER)
    #pragma section(".CRT$XCU",read)
    #define INITIALIZER2_(f,p) \
        static void f(void); \
        __declspec(allocate(".CRT$XCU")) void (*f##_)(void) = f; \
        __pragma(comment(linker,"/include:" p #f "_")) \
        static void f(void)
    #ifdef _WIN64
        #define INITIALIZER(f) INITIALIZER2_(f,"")
    #else
        #define INITIALIZER(f) INITIALIZER2_(f,"_")
    #endif
#else
    #define INITIALIZER(f) \
        static void f(void) __attribute__((constructor)); \
        static void f(void)
#endif
