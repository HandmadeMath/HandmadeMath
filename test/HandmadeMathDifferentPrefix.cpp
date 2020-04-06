#define HMM_PREFIX(name) WOW_##name

#define HANDMADE_MATH_IMPLEMENTATION
#define HANDMADE_MATH_NO_INLINE
#include "../HandmadeMath.h"

int main() {
    hmm_vec4 a = WOW_Vec4(1, 2, 3, 4);
    hmm_vec4 b = WOW_Vec4(5, 6, 7, 8);

    WOW_Add(a, b);
}
