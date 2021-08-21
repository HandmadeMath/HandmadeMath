# Handmade Math

[![Build Status](https://travis-ci.org/HandmadeMath/Handmade-Math.svg?branch=master)](https://travis-ci.org/StrangeZak/Handmade-Math)

A single-file, cross-platform, public domain game math library for C/C++.

To get started, go download [the latest release](https://github.com/HandmadeMath/Handmade-Math/releases).

-----

Version         | Changes        |
----------------|----------------|
**1.12.1** | Added extra parentheses around some macros |
**1.12.0** | Added Unary Minus operator for `HMM_Vec2`, `HMM_Vec3`, and `HMM_Vec4`. |
**1.11.1** | Added HMM_PREFIX macro to a few functions that were missing it. |
**1.11.0** | Added ability to customize or remove the default `HMM_` prefix on function names by defining a macro called `HMM_PREFIX(name)`. |
**1.10.1** | Removed stdint.h, this doesn't exist on some really old compilers and we didn't really use it anyways. |
**1.10.0** | Made HMM_Perspective use vertical FOV instead of horizontal FOV for consistency with other graphics APIs. |
**1.9.0** | Added SSE versions of quaternion operations. |
**1.8.0** | Added fast vector normalization routines that use fast inverse square roots.
**1.7.1** | Changed operator[] to take a const ref int instead of an int.
**1.7.0** | Renamed the 'Rows' member of hmm_mat4 to 'Columns'. Since our matrices are column-major, this should have been named 'Columns' from the start. 'Rows' is still present, but has been deprecated.
**1.6.0** | Added array subscript operators for vector and matrix types in C++. This is provided as a convenience, but be aware that it may incur an extra function call in unoptimized builds.
**1.5.1** | Fixed a bug with uninitialized elements in HMM_LookAt.
**1.5.0** | Changed internal structure for better performance and inlining. As a result, `HANDMADE_MATH_NO_INLINE` has been removed and no longer has any effect.
**1.4.0** | Fixed bug when using C mode. SSE'd all vec4 operations. Removed zeroing for better performance.
**1.3.0** | Removed need to `#define HANDMADE_MATH_CPP_MODE`. C++ definitions are now included automatically in C++ environments.
**1.2.0** | Added equality functions for `HMM_Vec2`, `HMM_Vec3`, and `HMM_Vec4`, and SSE'd `HMM_MultiplyMat4` and `HMM_Transpose`.
**1.1.5** | Added `Width` and `Height` to `HMM_Vec2`, and made it so you can supply your own `SqrtF`.
**1.1.4** | Fixed SSE being included on platforms that don't support it, and fixed divide-by-zero errors when normalizing zero vectors.
**1.1.3** | Fixed compile error in C mode
**1.1.2** | Fixed invalid HMMDEF's in the function definitions
**1.1.1** | Resolved compiler warnings on gcc and g++
**1.1**   | Quaternions! |
**1.0**   | Lots of testing |
**0.7**   | Added HMM_Vec2, and HMM_Vec4 versions of  HMM_LengthSquared, HMM_Length, and HMM_Normalize.   |
**0.6**   | Made HMM_Power faster, Fixed possible efficiency problem with HMM_Normalize, RENAMED HMM_LengthSquareRoot to HMM_LengthSquared, RENAMED HMM_RSqrtF to HMM_RSquareRootF, RENAMED HMM_SqrtF to HMM_SquareRootF, REMOVED Inner function (user should use Dot now), REMOVED HMM_FastInverseSquareRoot function declaration |
**0.5.2**   | Fixed SSE code in HMM_SqrtF and HMM_RSqrtF |
**0.5.1**   | Fixed HMM_Translate producing row-major matrices, ensured column-major order for matrices throughout |
**0.5**     | Added scalar operations on vectors and matrices, added += and -= for hmm_mat4, reconciled headers and implementations, tidied up in general |
**0.4**     | Added SSE Optimized HMM_SqrtF, HMM_RSqrtF, Removed use of C Runtime | 
**0.3**     | Added +=,-=, *=, /= for hmm_vec2, hmm_vec3, hmm_vec4 | 
**0.2b**    | Disabled warning C4201 on MSVC, Added 64bit precision on HMM_PI | 
**0.2a**    | Prefixed Macros | 
**0.2**     | Updated Documentation, Fixed C Compliance, Prefixed all functions, and added better operator overloading | 
**0.1**     | Initial Version | 

-----

## FAQ

**What's the license?**

This library is in the public domain. You can do whatever you want with it.

**Where can I contact you to ask questions?**

Feel free to make Github issues for any questions, concerns, or problems you encounter.
