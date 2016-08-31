/*
  HandmadeMath.h v0.6

  This is a single header file with a bunch of useful functions for
  basic game math operations.

  ==========================================================================

  You MUST

     #define HANDMADE_MATH_IMPLEMENTATION

  in EXACTLY one C or C++ file that includes this header, BEFORE the
  include, like this:

     #define HANDMADE_MATH_IMPLEMENTATION
     #include "HandmadeMath.h"

  All other files should just #include "HandmadeMath.h" without the #define.

  ==========================================================================

  For overloaded and operator overloaded versions of the base C functions,
  you MUST

     #define HANDMADE_MATH_CPP_MODE

  in EXACTLY one C or C++ file that includes this header, BEFORE the
  include, like this:

     #define HANDMADE_MATH_IMPLEMENTATION
     #define HANDMADE_MATH_CPP_MODE
     #include "HandmadeMath.h"

  All other files should just #include "HandmadeMath.h" without the #define.

  ==========================================================================

  To disable SSE intrinsics, you MUST

  #define HANDMADE_MATH_NO_SSE

  in EXACTLY one C or C++ file that includes this header, BEFORE the
  include, like this:

     #define HANDMADE_MATH_IMPLEMENTATION
     #define HANDMADE_MATH_CPP_MODE
     #define HANDMADE_MATH_NO_SSE
     #include "HandmadeMath.h"

     or

     #define HANDMADE_MATH_IMPLEMENTATION
     #define HANDMADE_MATH_NO_SSE
     #include "HandmadeMath.h"

  ==========================================================================

  To disable inlining functions, you MUST

  #define HANDMADE_MATH_NO_INLINE

  in EXACTLY one C or C++ file that includes this header, BEFORE the
  include, like this:

     #define HANDMADE_MATH_IMPLEMENTATION
     #define HANDMADE_MATH_CPP_MODE
     #define HANDMADE_MATH_NO_INLINE
     #include "HandmadeMath.h"

  All other files should just #include "HandmadeMath.h" without the #define.

  ==========================================================================
  
  To Disable the CRT, you MUST 

     #define HMM_SINF MySinF
     #define HMM_COSF MyCosF
     #define HMM_TANF MyTanF
     #define HMM_EXPF MyExpF
     #define HMM_LOGF MyLogF
  
  Provide your own implementations of SinF, CosF, TanF, ExpF and LogF
  in EXACTLY one C or C++ file that includes this header, BEFORE the
  include, like this:     

     #define HMM_SINF MySinF
     #define HMM_COSF MyCosF
     #define HMM_TANF MyTanF
     #define HMM_EXPF MyExpF
     #define HMM_LOGF MyLogF
     #define HANDMADE_MATH_IMPLEMENTATION
     #define HANDMADE_MATH_CPP_MODE
     #include "HandmadeMath.h"

  If you do not define all five of these, HandmadeMath.h will use the
  versions of these functions that are provided by the CRT.

  ==========================================================================

  Version History:
      0.2 (*) Updated documentation
          (*) Better C compliance
          (*) Prefix all handmade math functions 
          (*) Better operator overloading
      0.2a
          (*) Prefixed Macros
      0.2b
          (*) Disabled warning 4201 on MSVC as it is legal is C11
          (*) Removed the f at the end of HMM_PI to get 64bit precision
      0.3
          (*) Added +=, -=, *=, /= for hmm_vec2, hmm_vec3, hmm_vec4
      0.4
          (*) SSE Optimized HMM_SqrtF
          (*) SSE Optimized HMM_RSqrtF
          (*) Removed CRT
      0.5
          (*) Added scalar multiplication and division for vectors
              and matrices
          (*) Added matrix subtraction and += for hmm_mat4
          (*) Reconciled all headers and implementations
          (*) Tidied up, and filled in a few missing operators
      0.5.1
          (*) Ensured column-major order for matrices throughout
          (*) Fixed HMM_Translate producing row-major matrices
      0.5.2
          (*) Fixed SSE code in HMM_SqrtF
          (*) Fixed SSE code in HMM_RSqrtF
      0.6
          (*) Added Unit testing
          (*) Made HMM_Power faster
          (*) Fixed possible efficiency problem with HMM_Normalize 
          (*) RENAMED HMM_LengthSquareRoot to HMM_LengthSquared
          (*) RENAMED HMM_RSqrtF to HMM_RSquareRootF
          (*) RENAMED HMM_SqrtF to HMM_SquareRootF
          (*) REMOVED Inner function (user should use Dot now)
          (*) REMOVED HMM_FastInverseSquareRoot function declaration

  LICENSE

  This software is in the public domain. Where that dedication is not
  recognized, you are granted a perpetual, irrevocable license to copy,
  distribute, and modify this file as you see fit.

  CREDITS

  Written by Zakary Strange (zak@handmade.network && @strangezak)

  Functionality:
   Matt Mascarenhas (@miblo_)
   Aleph
   FieryDrake (@fierydrake)
   Gingerbill (@TheGingerBill)
   Ben Visness (@bvisness) 

  Fixes:
   Jeroen van Rijn (@J_vanRijn)
   Kiljacken (@Kiljacken)
   Insofaras (@insofaras)
*/

#include <xmmintrin.h>

#ifndef HANDMADE_MATH_H
#define HANDMADE_MATH_H

#ifdef _MSC_VER
#pragma warning(disable:4201)
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef HANDMADEMATH_STATIC
#define HMMDEF static
#else
#define HMMDEF extern
#endif

#ifdef HANDMADE_MATH_NO_INLINE
#define HINLINE
#elif _MSC_VER && !__INTEL_COMPILER
#define HINLINE __inline
#else
#define HINLINE inline
#endif

#if !defined(HMM_SINF) || !defined(HMM_COSF) || !defined(HMM_TANF) || \
    !defined(HMM_EXPF) || !defined(HMM_LOGF)
#include <math.h>    
#endif
    
#ifndef HMM_SINF
#define HMM_SINF sinf
#endif    
        
#ifndef HMM_COSF
#define HMM_COSF cosf
#endif    
        
#ifndef HMM_TANF
#define HMM_TANF tanf
#endif        
    
#ifndef HMM_EXPF
#define HMM_EXPF expf
#endif

#ifndef HMM_LOGF
#define HMM_LOGF logf
#endif

#define HMM_PI32 3.14159265359f
#define HMM_PI 3.14159265358979323846

#define HMM_MIN(a, b) (a) > (b) ? (b) : (a)
#define HMM_MAX(a, b) (a) < (b) ? (b) : (a)
#define HMN_ABS(a) (a) < 0 ? -(a) : (a)
#define HMM_MOD(a, m) ((a) % (m)) >= 0 ? ((a) % (m)) : (((a) % (m)) + (m))
#define HMM_SQUARE(x) ((x) * (x))

typedef union hmm_vec2
{
    struct
    {
        float X, Y;
    };

    struct
    {
        float U, V;
    };

    struct
    {
        float Left, Right;
    };

    float Elements[2];
} hmm_vec2;

typedef union hmm_vec3
{
    struct
    {
        float X, Y, Z;
    };

    struct
    {
        float U, V, W;
    };

    struct
    {
        float R, G, B;
    };

    struct
    {
        hmm_vec2 XY;
        float Ignored0_;
    };

    struct
    {
        float Ignored1_;
        hmm_vec2 YZ;
    };

    struct
    {
        hmm_vec2 UV;
        float Ignored2_;
    };

    struct
    {
        float Ignored3_;
        hmm_vec2 VW;
    };

    float Elements[3];
} hmm_vec3;

typedef union hmm_vec4
{
    struct
    {
        union
        {
            hmm_vec3 XYZ;
            struct
            {
                float X, Y, Z;
            };
        };

        float W;
    };
    struct
    {
        union
        {
            hmm_vec3 RGB;
            struct
            {
                float R, G, B;
            };
        };

        float A;
    };

    struct
    {
        hmm_vec2 XY;
        float Ignored0_;
        float Ignored1_;
    };

    struct
    {
        float Ignored2_;
        hmm_vec2 YZ;
        float Ignored3_;
    };

    struct
    {
        float Ignored4_;
        float Ignored5_;
        hmm_vec2 ZW;
    };

    float Elements[4];
} hmm_vec4;

typedef union hmm_mat4
{
    float Elements[4][4];
} hmm_mat4;

typedef hmm_vec2 hmm_v2;
typedef hmm_vec3 hmm_v3;
typedef hmm_vec4 hmm_v4;
typedef hmm_mat4 hmm_m4;    

HMMDEF float HMM_SinF(float Angle);
HMMDEF float HMM_TanF(float Angle);
HMMDEF float HMM_CosF(float Angle);
HMMDEF float HMM_ExpF(float Float);
HMMDEF float HMM_LogF(float Float);

HMMDEF float HMM_ToRadians(float Degrees);
HMMDEF float HMM_SquareRootF(float Float);
HMMDEF float HMM_RSquareRootF(float Float);
HMMDEF float HMM_LengthSquared(hmm_vec3 A);
HMMDEF float HMM_Length(hmm_vec3 A);    
HMMDEF float HMM_Power(float Base, int Exponent);
HMMDEF float HMM_PowerF(float Base, float Exponent);
HMMDEF float HMM_Lerp(float A, float Time, float B);
HMMDEF float HMM_Clamp(float Min, float Value, float Max);

HMMDEF hmm_vec3 HMM_Normalize(hmm_vec3 A);
HMMDEF hmm_vec3 HMM_Cross(hmm_vec3 VecOne, hmm_vec3 VecTwo);

HMMDEF float HMM_DotVec2(hmm_vec2 VecOne, hmm_vec2 VecTwo);
HMMDEF float HMM_DotVec3(hmm_vec3 VecOne, hmm_vec3 VecTwo);
HMMDEF float HMM_DotVec4(hmm_vec4 VecOne, hmm_vec4 VecTwo);

HMMDEF hmm_vec2 HMM_Vec2i(int X, int Y);
HMMDEF hmm_vec2 HMM_Vec2(float X, float Y);
HMMDEF hmm_vec3 HMM_Vec3(float X, float Y, float Z);
HMMDEF hmm_vec3 HMM_Vec3i(int X, int Y, int Z);
HMMDEF hmm_vec4 HMM_Vec4(float X, float Y, float Z, float W);
HMMDEF hmm_vec4 HMM_Vec4i(int X, int Y, int Z, int W);
HMMDEF hmm_vec4 HMM_Vec4v(hmm_vec3 Vector, float W);

HMMDEF hmm_vec2 HMM_AddVec2(hmm_vec2 Left, hmm_vec2 Right);
HMMDEF hmm_vec3 HMM_AddVec3(hmm_vec3 Left, hmm_vec3 Right);
HMMDEF hmm_vec4 HMM_AddVec4(hmm_vec4 Left, hmm_vec4 Right);

HMMDEF hmm_vec2 HMM_SubtractVec2(hmm_vec2 Left, hmm_vec2 Right);
HMMDEF hmm_vec3 HMM_SubtractVec3(hmm_vec3 Left, hmm_vec3 Right);
HMMDEF hmm_vec4 HMM_SubtractVec4(hmm_vec4 Left, hmm_vec4 Right);

HMMDEF hmm_vec2 HMM_MultiplyVec2(hmm_vec2 Left, hmm_vec2 Right);
HMMDEF hmm_vec2 HMM_MultiplyVec2f(hmm_vec2 Left, float Right);
HMMDEF hmm_vec3 HMM_MultiplyVec3(hmm_vec3 Left, hmm_vec3 Right);
HMMDEF hmm_vec3 HMM_MultiplyVec3f(hmm_vec3 Left, float Right);
HMMDEF hmm_vec4 HMM_MultiplyVec4(hmm_vec4 Left, hmm_vec4 Right);
HMMDEF hmm_vec4 HMM_MultiplyVec4f(hmm_vec4 Left, float Right);

HMMDEF hmm_vec2 HMM_DivideVec2(hmm_vec2 Left, hmm_vec2 Right);
HMMDEF hmm_vec2 HMM_DivideVec2f(hmm_vec2 Left, float Right);
HMMDEF hmm_vec3 HMM_DivideVec3(hmm_vec3 Left, hmm_vec3 Right);
HMMDEF hmm_vec3 HMM_DivideVec3f(hmm_vec3 Left, float Right);
HMMDEF hmm_vec4 HMM_DivideVec4(hmm_vec4 Left, hmm_vec4 Right);
HMMDEF hmm_vec4 HMM_DivideVec4f(hmm_vec4 Left, float Right);

HMMDEF hmm_mat4 HMM_Mat4(void);
HMMDEF hmm_mat4 HMM_Mat4d(float Diagonal);
HMMDEF hmm_mat4 HMM_AddMat4(hmm_mat4 Left, hmm_mat4 Right);
HMMDEF hmm_mat4 HMM_SubtractMat4(hmm_mat4 Left, hmm_mat4 Right);
HMMDEF hmm_mat4 HMM_MultiplyMat4(hmm_mat4 Left, hmm_mat4 Right);
HMMDEF hmm_mat4 HMM_MultiplyMat4f(hmm_mat4 Matrix, float Scalar);
HMMDEF hmm_vec4 HMM_MultiplyMat4ByVec4(hmm_mat4 Matrix, hmm_vec4 Vector);
HMMDEF hmm_mat4 HMM_DivideMat4f(hmm_mat4 Matrix, float Scalar);

HMMDEF hmm_mat4 HMM_Transpose(hmm_mat4 Matrix);

HMMDEF hmm_mat4 HMM_Orthographic(float Left, float Right, float Bottom, float Top, float Near, float Far);
HMMDEF hmm_mat4 HMM_Perspective(float FOV, float AspectRatio, float Near, float Far);
HMMDEF hmm_mat4 HMM_Translate(hmm_vec3 Translation);
HMMDEF hmm_mat4 HMM_Rotate(float Angle, hmm_vec3 Axis);
HMMDEF hmm_mat4 HMM_Scale(hmm_vec3 Scale);

HMMDEF hmm_mat4 HMM_LookAt(hmm_vec3 Eye, hmm_vec3 Center, hmm_vec3 Up);

#ifdef __cplusplus
}
#endif

#ifdef HANDMADE_MATH_CPP_MODE

HMMDEF float HMM_Dot(hmm_vec2 VecOne, hmm_vec2 VecTwo);
HMMDEF float HMM_Dot(hmm_vec3 VecOne, hmm_vec3 VecTwo);
HMMDEF float HMM_Dot(hmm_vec4 VecOne, hmm_vec4 VecTwo);

HMMDEF hmm_vec2 HMM_Add(hmm_vec2 Left, hmm_vec2 Right);
HMMDEF hmm_vec3 HMM_Add(hmm_vec3 Left, hmm_vec3 Right);
HMMDEF hmm_vec4 HMM_Add(hmm_vec4 Left, hmm_vec4 Right);
HMMDEF hmm_mat4 HMM_Add(hmm_mat4 Left, hmm_mat4 Right);

HMMDEF hmm_vec2 HMM_Subtract(hmm_vec2 Left, hmm_vec2 Right);
HMMDEF hmm_vec3 HMM_Subtract(hmm_vec3 Left, hmm_vec3 Right);
HMMDEF hmm_vec4 HMM_Subtract(hmm_vec4 Left, hmm_vec4 Right);
HMMDEF hmm_mat4 HMM_Subtract(hmm_mat4 Left, hmm_mat4 Right);

HMMDEF hmm_vec2 HMM_Multiply(hmm_vec2 Left, hmm_vec2 Right);
HMMDEF hmm_vec2 HMM_Multiply(hmm_vec2 Left, float Right);
HMMDEF hmm_vec3 HMM_Multiply(hmm_vec3 Left, hmm_vec3 Right);
HMMDEF hmm_vec3 HMM_Multiply(hmm_vec3 Left, float Right);
HMMDEF hmm_vec4 HMM_Multiply(hmm_vec4 Left, hmm_vec4 Right);
HMMDEF hmm_vec4 HMM_Multiply(hmm_vec4 Left, float Right);
HMMDEF hmm_mat4 HMM_Multiply(hmm_mat4 Left, hmm_mat4 Right);
HMMDEF hmm_mat4 HMM_Multiply(hmm_mat4 Left, float Right);
HMMDEF hmm_vec4 HMM_Multiply(hmm_mat4 Matrix, hmm_vec4 Vector);

HMMDEF hmm_vec2 HMM_Divide(hmm_vec2 Left, hmm_vec2 Right);
HMMDEF hmm_vec2 HMM_Divide(hmm_vec2 Left, float Right);
HMMDEF hmm_vec3 HMM_Divide(hmm_vec3 Left, hmm_vec3 Right);
HMMDEF hmm_vec3 HMM_Divide(hmm_vec3 Left, float Right);
HMMDEF hmm_vec4 HMM_Divide(hmm_vec4 Left, hmm_vec4 Right);
HMMDEF hmm_vec4 HMM_Divide(hmm_vec4 Left, float Right);
HMMDEF hmm_mat4 HMM_Divide(hmm_mat4 Left, float Right);

HMMDEF hmm_vec2 operator+(hmm_vec2 Left, hmm_vec2 Right);
HMMDEF hmm_vec3 operator+(hmm_vec3 Left, hmm_vec3 Right);
HMMDEF hmm_vec4 operator+(hmm_vec4 Left, hmm_vec4 Right);
HMMDEF hmm_mat4 operator+(hmm_mat4 Left, hmm_mat4 Right);

HMMDEF hmm_vec2 operator-(hmm_vec2 Left, hmm_vec2 Right);
HMMDEF hmm_vec3 operator-(hmm_vec3 Left, hmm_vec3 Right);
HMMDEF hmm_vec4 operator-(hmm_vec4 Left, hmm_vec4 Right);
HMMDEF hmm_mat4 operator-(hmm_mat4 Left, hmm_mat4 Right);

HMMDEF hmm_vec2 operator*(hmm_vec2 Left, hmm_vec2 Right);
HMMDEF hmm_vec3 operator*(hmm_vec3 Left, hmm_vec3 Right);
HMMDEF hmm_vec4 operator*(hmm_vec4 Left, hmm_vec4 Right);
HMMDEF hmm_mat4 operator*(hmm_mat4 Left, hmm_mat4 Right);

HMMDEF hmm_vec2 operator*(hmm_vec2 Left, float Right);
HMMDEF hmm_vec3 operator*(hmm_vec3 Left, float Right);
HMMDEF hmm_vec4 operator*(hmm_vec4 Left, float Right);
HMMDEF hmm_mat4 operator*(hmm_mat4 Left, float Right);

HMMDEF hmm_vec2 operator*(float Left, hmm_vec2 Right);
HMMDEF hmm_vec3 operator*(float Left, hmm_vec3 Right);
HMMDEF hmm_vec4 operator*(float Left, hmm_vec4 Right);
HMMDEF hmm_mat4 operator*(float Left, hmm_mat4 Right);

HMMDEF hmm_vec4 operator*(hmm_mat4 Matrix, hmm_vec4 Vector);

HMMDEF hmm_vec2 operator/(hmm_vec2 Left, hmm_vec2 Right);
HMMDEF hmm_vec3 operator/(hmm_vec3 Left, hmm_vec3 Right);
HMMDEF hmm_vec4 operator/(hmm_vec4 Left, hmm_vec4 Right);

HMMDEF hmm_vec2 operator/(hmm_vec2 Left, float Right);
HMMDEF hmm_vec3 operator/(hmm_vec3 Left, float Right);
HMMDEF hmm_vec4 operator/(hmm_vec4 Left, float Right);
HMMDEF hmm_mat4 operator/(hmm_mat4 Left, float Right);

HMMDEF hmm_vec2 & operator+=(hmm_vec2 &Left, hmm_vec2 Right);
HMMDEF hmm_vec3 & operator+=(hmm_vec3 &Left, hmm_vec3 Right);
HMMDEF hmm_vec4 & operator+=(hmm_vec4 &Left, hmm_vec4 Right);
HMMDEF hmm_mat4 & operator+=(hmm_mat4 &Left, hmm_mat4 Right);

HMMDEF hmm_vec2 & operator-=(hmm_vec2 &Left, hmm_vec2 Right);
HMMDEF hmm_vec3 & operator-=(hmm_vec3 &Left, hmm_vec3 Right);
HMMDEF hmm_vec4 & operator-=(hmm_vec4 &Left, hmm_vec4 Right);
HMMDEF hmm_mat4 & operator-=(hmm_mat4 &Left, hmm_mat4 Right);

HMMDEF hmm_vec2 & operator*=(hmm_vec2 &Left, hmm_vec2 Right);
HMMDEF hmm_vec3 & operator*=(hmm_vec3 &Left, hmm_vec3 Right);
HMMDEF hmm_vec4 & operator*=(hmm_vec4 &Left, hmm_vec4 Right);

HMMDEF hmm_vec2 & operator*=(hmm_vec2 &Left, float Right);
HMMDEF hmm_vec3 & operator*=(hmm_vec3 &Left, float Right);
HMMDEF hmm_vec4 & operator*=(hmm_vec4 &Left, float Right);
HMMDEF hmm_mat4 & operator*=(hmm_mat4 &Left, float Right);

HMMDEF hmm_vec2 & operator/=(hmm_vec2 &Left, hmm_vec2 Right);
HMMDEF hmm_vec3 & operator/=(hmm_vec3 &Left, hmm_vec3 Right);
HMMDEF hmm_vec4 & operator/=(hmm_vec4 &Left, hmm_vec4 Right);

HMMDEF hmm_vec2 & operator/=(hmm_vec2 &Left, float Right);
HMMDEF hmm_vec3 & operator/=(hmm_vec3 &Left, float Right);
HMMDEF hmm_vec4 & operator/=(hmm_vec4 &Left, float Right);
HMMDEF hmm_mat4 & operator/=(hmm_mat4 &Left, float Right);

#endif /* HANDMADE_MATH_CPP */

#endif /* HANDMADE_MATH_H */

#ifdef HANDMADE_MATH_IMPLEMENTATION

HINLINE float
HMM_SinF(float Angle)
{
    float Result = 0;

    Result = HMM_SINF(Angle);
    return (Result);
}

HINLINE float
HMM_CosF(float Angle)
{
    float Result = 0;

    Result = HMM_COSF(Angle);
    return (Result);
}

HINLINE float
HMM_TanF(float Radians)
{
    float Result = 0;

    Result = HMM_TANF(Radians);
    return (Result);
}

HINLINE float
HMM_ExpF(float Float)
{
    float Result = 0;

    Result = HMM_EXPF(Float);
    return (Result);
}

HINLINE float
HMM_LogF(float Float)
{
    float Result = 0;

    Result = HMM_LOGF(Float);
    return (Result);
}

HINLINE float
HMM_SquareRootF(float Value)
{
    float Result = 0;

#ifdef HANDMADE_MATH_NO_SSE
    Result = sqrtf(Value);
#else        
    __m128 In = _mm_set_ss(Value);
    __m128 Out = _mm_sqrt_ss(In);
    Result = _mm_cvtss_f32(Out);
#endif 

    return(Result);
}

HINLINE float
HMM_RSquareRootF(float Value)
{
    float Result = 0;

#ifdef HANDMADE_MATH_NO_SSE
    Result = 1.0f/HMM_SqrtF(Value);    
#else        
    __m128 In = _mm_set_ss(Value);
    __m128 Out = _mm_rsqrt_ss(In);
    Result = _mm_cvtss_f32(Out);
#endif

    return(Result);
}

HINLINE float
HMM_ToRadians(float Degrees)
{
    float Result = 0;

    Result = Degrees * (HMM_PI32 / 180.0f);
    return (Result);
}

HINLINE float
HMM_DotVec2(hmm_vec2 VecOne, hmm_vec2 VecTwo)
{
    float Result = 0;

    Result = (VecOne.X * VecTwo.X) + (VecOne.Y * VecTwo.Y);
    return (Result);
}

HINLINE float
HMM_DotVec3(hmm_vec3 VecOne, hmm_vec3 VecTwo)
{
    float Result = 0;

    Result = (VecOne.X * VecTwo.X) + (VecOne.Y * VecTwo.Y) + (VecOne.Z * VecTwo.Z);
    return (Result);
}

HINLINE float
HMM_DotVec4(hmm_vec4 VecOne, hmm_vec4 VecTwo)
{
    float Result = 0;

    Result = (VecOne.X * VecTwo.X) + (VecOne.Y * VecTwo.Y) + (VecOne.Z * VecTwo.Z) + (VecOne.W * VecTwo.W);
    return (Result);
}

HINLINE float
HMM_LengthSquared(hmm_vec3 A)
{
    float Result = 0;

    Result = HMM_DotVec3(A, A);
    return (Result);
}

HINLINE float
HMM_Length(hmm_vec3 A)
{
    float Result = 0;

    Result = HMM_SquareRootF(HMM_LengthSquared(A));
    return (Result);
}

HINLINE float
HMM_Power(float Base, int Exponent)
{
    float Result = 1.0f;
    float Mul = Exponent < 0 ? 1.f / Base : Base;
    unsigned int X = Exponent < 0 ? -Exponent : Exponent;
    while (X)
    {
        if (X & 1)
        {
            Result *= Mul;
        }
        Mul *= Mul;
        X >>= 1;
    }
    return (Result);
}

HINLINE float
HMM_PowerF(float Base, float Exponent)
{
    return expf(Exponent * logf(Base));
}

HINLINE float
HMM_Lerp(float A, float Time, float B)
{
    float Result = 0;

    Result = (1.0f - Time) * A + Time * B;
    return (Result);
}

HINLINE float
HMM_Clamp(float Min, float Value, float Max)
{
    float Result = Value;

    if(Result < Min)
    {
        Result = Min;
    }
    else if(Result > Max)
    {
        Result = Max;
    }

    return (Result);
}

HINLINE hmm_vec3
HMM_Normalize(hmm_vec3 A)
{
    hmm_vec3 Result = {0};

    float VectorLength = HMM_Length(A);
    
    Result.X = A.X * (1.0f / VectorLength);
    Result.Y = A.Y * (1.0f / VectorLength);
    Result.Z = A.Z * (1.0f / VectorLength);
    
    return (Result);
}

HINLINE hmm_vec3
HMM_Cross(hmm_vec3 VecOne, hmm_vec3 VecTwo)
{
    hmm_vec3 Result = {0};

    Result.X = (VecOne.Y * VecTwo.Z) - (VecOne.Z * VecTwo.Y);
    Result.Y = (VecOne.Z * VecTwo.X) - (VecOne.X * VecTwo.Z);
    Result.Z = (VecOne.X * VecTwo.Y) - (VecOne.Y * VecTwo.X);

    return (Result);
}

HINLINE hmm_vec2
HMM_Vec2(float X, float Y)
{
    hmm_vec2 Result = {0};

    Result.X = X;
    Result.Y = Y;

    return (Result);
}

HINLINE hmm_vec2
HMM_Vec2i(int X, int Y)
{
    hmm_vec2 Result = {0};

    Result.X = (float)X;
    Result.Y = (float)Y;

    return (Result);
}

HINLINE hmm_vec3
HMM_Vec3(float X, float Y, float Z)
{
    hmm_vec3 Result = {0};

    Result.X = X;
    Result.Y = Y;
    Result.Z = Z;

    return (Result);
}

HINLINE hmm_vec3
HMM_Vec3i(int X, int Y, int Z)
{
    hmm_vec3 Result = {0};

    Result.X = (float)X;
    Result.Y = (float)Y;
    Result.Z = (float)Z;

    return (Result);
}

HINLINE hmm_vec4
HMM_Vec4(float X, float Y, float Z, float W)
{
    hmm_vec4 Result = {0};

    Result.X = X;
    Result.Y = Y;
    Result.Z = Z;
    Result.W = W;

    return (Result);
}

HINLINE hmm_vec4
HMM_Vec4i(int X, int Y, int Z, int W)
{
    hmm_vec4 Result = {0};

    Result.X = (float)X;
    Result.Y = (float)Y;
    Result.Z = (float)Z;
    Result.W = (float)W;

    return (Result);
}

HINLINE hmm_vec4
HMM_Vec4v(hmm_vec3 Vector, float W)
{
    hmm_vec4 Result = {0};

    Result.XYZ = Vector;
    Result.W = W;

    return (Result);
}

HINLINE hmm_vec2
HMM_AddVec2(hmm_vec2 Left, hmm_vec2 Right)
{
    hmm_vec2 Result = {0};

    Result.X = Left.X + Right.X;
    Result.Y = Left.Y + Right.Y;

    return (Result);
}

HINLINE hmm_vec3
HMM_AddVec3(hmm_vec3 Left, hmm_vec3 Right)
{
    hmm_vec3 Result = {0};

    Result.X = Left.X + Right.X;
    Result.Y = Left.Y + Right.Y;
    Result.Z = Left.Z + Right.Z;

    return (Result);
}

HINLINE hmm_vec4
HMM_AddVec4(hmm_vec4 Left, hmm_vec4 Right)
{
    hmm_vec4 Result = {0};

    Result.X = Left.X + Right.X;
    Result.Y = Left.Y + Right.Y;
    Result.Z = Left.Z + Right.Z;
    Result.W = Left.W + Right.W;

    return (Result);
}

HINLINE hmm_vec2
HMM_SubtractVec2(hmm_vec2 Left, hmm_vec2 Right)
{
    hmm_vec2 Result = {0};

    Result.X = Left.X - Right.X;
    Result.Y = Left.Y - Right.Y;

    return (Result);
}

HINLINE hmm_vec3
HMM_SubtractVec3(hmm_vec3 Left, hmm_vec3 Right)
{
    hmm_vec3 Result = {0};

    Result.X = Left.X - Right.X;
    Result.Y = Left.Y - Right.Y;
    Result.Z = Left.Z - Right.Z;

    return (Result);
}

HINLINE hmm_vec4
HMM_SubtractVec4(hmm_vec4 Left, hmm_vec4 Right)
{
    hmm_vec4 Result = {0};

    Result.X = Left.X - Right.X;
    Result.Y = Left.Y - Right.Y;
    Result.Z = Left.Z - Right.Z;
    Result.W = Left.W - Right.W;

    return (Result);
}

HINLINE hmm_vec2
HMM_MultiplyVec2(hmm_vec2 Left, hmm_vec2 Right)
{
    hmm_vec2 Result = {0};

    Result.X = Left.X * Right.X;
    Result.Y = Left.Y * Right.Y;

    return (Result);
}

HINLINE hmm_vec2
HMM_MultiplyVec2f(hmm_vec2 Left, float Right)
{
    hmm_vec2 Result = {0};

    Result.X = Left.X * Right;
    Result.Y = Left.Y * Right;

    return (Result);
}

HINLINE hmm_vec3
HMM_MultiplyVec3(hmm_vec3 Left, hmm_vec3 Right)
{
    hmm_vec3 Result = {0};

    Result.X = Left.X * Right.X;
    Result.Y = Left.Y * Right.Y;
    Result.Z = Left.Z * Right.Z;

    return (Result);
}

HINLINE hmm_vec3
HMM_MultiplyVec3f(hmm_vec3 Left, float Right)
{
    hmm_vec3 Result = {0};

    Result.X = Left.X * Right;
    Result.Y = Left.Y * Right;
    Result.Z = Left.Z * Right;

    return (Result);
}

HINLINE hmm_vec4
HMM_MultiplyVec4(hmm_vec4 Left, hmm_vec4 Right)
{
    hmm_vec4 Result = {0};

    Result.X = Left.X * Right.X;
    Result.Y = Left.Y * Right.Y;
    Result.Z = Left.Z * Right.Z;
    Result.W = Left.W * Right.W;

    return (Result);
}

HINLINE hmm_vec4
HMM_MultiplyVec4f(hmm_vec4 Left, float Right)
{
    hmm_vec4 Result = {0};

    Result.X = Left.X * Right;
    Result.Y = Left.Y * Right;
    Result.Z = Left.Z * Right;
    Result.W = Left.W * Right;

    return (Result);
}

HINLINE hmm_vec2
HMM_DivideVec2(hmm_vec2 Left, hmm_vec2 Right)
{
    hmm_vec2 Result = {0};

    Result.X = Left.X / Right.X;
    Result.Y = Left.Y / Right.Y;

    return (Result);
}

HINLINE hmm_vec2
HMM_DivideVec2f(hmm_vec2 Left, float Right)
{
    hmm_vec2 Result = {0};

    Result.X = Left.X / Right;
    Result.Y = Left.Y / Right;

    return (Result);
}

HINLINE hmm_vec3
HMM_DivideVec3(hmm_vec3 Left, hmm_vec3 Right)
{
    hmm_vec3 Result = {0};

    Result.X = Left.X / Right.X;
    Result.Y = Left.Y / Right.Y;
    Result.Z = Left.Z / Right.Z;

    return (Result);
}

HINLINE hmm_vec3
HMM_DivideVec3f(hmm_vec3 Left, float Right)
{
    hmm_vec3 Result = {0};

    Result.X = Left.X / Right;
    Result.Y = Left.Y / Right;
    Result.Z = Left.Z / Right;

    return (Result);
}

HINLINE hmm_vec4
HMM_DivideVec4(hmm_vec4 Left, hmm_vec4 Right)
{
    hmm_vec4 Result = {0};

    Result.X = Left.X / Right.X;
    Result.Y = Left.Y / Right.Y;
    Result.Z = Left.Z / Right.Z;
    Result.W = Left.W / Right.W;

    return (Result);
}

HINLINE hmm_vec4
HMM_DivideVec4f(hmm_vec4 Left, float Right)
{
    hmm_vec4 Result = {0};

    Result.X = Left.X / Right;
    Result.Y = Left.Y / Right;
    Result.Z = Left.Z / Right;
    Result.W = Left.W / Right;

    return (Result);
}

HINLINE hmm_mat4
HMM_Mat4()
{
    hmm_mat4 Result = {0};

    return (Result);
}

hmm_mat4
HMM_Mat4d(float Diagonal)
{
    hmm_mat4 Result = HMM_Mat4();

    Result.Elements[0][0] = Diagonal;
    Result.Elements[1][1] = Diagonal;
    Result.Elements[2][2] = Diagonal;
    Result.Elements[3][3] = Diagonal;

    return (Result);
}

HINLINE hmm_mat4
HMM_AddMat4(hmm_mat4 Left, hmm_mat4 Right)
{
    hmm_mat4 Result = HMM_Mat4();

    int Columns;
    for(Columns = 0; Columns < 4; ++Columns)
    {
        int Rows;
        for(Rows = 0; Rows < 4; ++Rows)
        {
            Result.Elements[Columns][Rows] = Left.Elements[Columns][Rows] + Right.Elements[Columns][Rows];
        }
    }

    return (Result);
}

HINLINE hmm_mat4
HMM_SubtractMat4(hmm_mat4 Left, hmm_mat4 Right)
{
    hmm_mat4 Result = HMM_Mat4();

    int Columns;
    for(Columns = 0; Columns < 4; ++Columns)
    {
        int Rows;
        for(Rows = 0; Rows < 4; ++Rows)
        {
            Result.Elements[Columns][Rows] = Left.Elements[Columns][Rows] - Right.Elements[Columns][Rows];
        }
    }

    return (Result);
}

hmm_mat4
HMM_MultiplyMat4(hmm_mat4 Left, hmm_mat4 Right)
{
    hmm_mat4 Result = HMM_Mat4();

    int Columns;
    for(Columns = 0; Columns < 4; ++Columns)
    {
        int Rows;
        for(Rows = 0; Rows < 4; ++Rows)
        {
            float Sum = 0;
            int CurrentMatrice;
            for(CurrentMatrice = 0; CurrentMatrice < 4; ++CurrentMatrice)
            {
                Sum += Left.Elements[CurrentMatrice][Rows] * Right.Elements[Columns][CurrentMatrice];
            }

            Result.Elements[Columns][Rows] = Sum;
        }
    }

    return (Result);
}

hmm_mat4
HMM_MultiplyMat4f(hmm_mat4 Matrix, float Scalar)
{
    hmm_mat4 Result = HMM_Mat4();

    int Columns;
    for(Columns = 0; Columns < 4; ++Columns)
    {
        int Rows;
        for(Rows = 0; Rows < 4; ++Rows)
        {
            Result.Elements[Columns][Rows] = Matrix.Elements[Columns][Rows] * Scalar;
        }
    }

    return (Result);
}

hmm_vec4
HMM_MultiplyMat4ByVec4(hmm_mat4 Matrix, hmm_vec4 Vector)
{
    hmm_vec4 Result = {0};
    
    int Columns, Rows;
    for(Rows = 0; Rows < 4; ++Rows)
    {
        float Sum = 0;
        for(Columns = 0; Columns < 4; ++Columns)
        {
            Sum += Matrix.Elements[Columns][Rows] * Vector.Elements[Columns];
        }
        
        Result.Elements[Rows] = Sum;
    }
    
    return (Result);
}

hmm_mat4
HMM_DivideMat4f(hmm_mat4 Matrix, float Scalar)
{
    hmm_mat4 Result = HMM_Mat4();

    int Columns;
    for(Columns = 0; Columns < 4; ++Columns)
    {
        int Rows;
        for(Rows = 0; Rows < 4; ++Rows)
        {
            Result.Elements[Columns][Rows] = Matrix.Elements[Columns][Rows] / Scalar;
        }
    }

    return (Result);
}

hmm_mat4
HMM_Transpose(hmm_mat4 Matrix)
{
    hmm_mat4 Result = HMM_Mat4();

    int Columns;
    for(Columns = 0; Columns < 4; ++Columns)
    {
        int Rows;
        for(Rows = 0; Rows < 4; ++Rows)
        {
            Result.Elements[Rows][Columns] = Matrix.Elements[Columns][Rows];
        }
    }

    return (Result);
}

hmm_mat4
HMM_Orthographic(float Left, float Right, float Bottom, float Top, float Near, float Far)
{
    hmm_mat4 Result = HMM_Mat4d(1.0f);

    Result.Elements[0][0] = 2.0f / (Right - Left);
    Result.Elements[1][1] = 2.0f / (Top - Bottom);
    Result.Elements[2][2] = 2.0f / (Near - Far);

    Result.Elements[3][0] = (Left + Right) / (Left - Right);
    Result.Elements[3][1] = (Bottom + Top) / (Bottom - Top);
    Result.Elements[3][2] = (Far + Near) / (Near - Far);

    return (Result);
}

hmm_mat4
HMM_Perspective(float FOV, float AspectRatio, float Near, float Far)
{
    hmm_mat4 Result = HMM_Mat4d(1.0f);

    float TanThetaOver2 = HMM_TanF(FOV * (HMM_PI32 / 360.0f));
    
    Result.Elements[0][0] = 1.0f / TanThetaOver2;
    Result.Elements[1][1] = AspectRatio / TanThetaOver2;
    Result.Elements[2][3] = -1.0f;
    Result.Elements[2][2] = (Near + Far) / (Near - Far);
    Result.Elements[3][2] = (2.0f * Near * Far) / (Near - Far);
    Result.Elements[3][3] = 0.0f;

    return (Result);
}

hmm_mat4
HMM_Translate(hmm_vec3 Translation)
{
    hmm_mat4 Result = HMM_Mat4d(1.0f);

    Result.Elements[3][0] = Translation.X;
    Result.Elements[3][1] = Translation.Y;
    Result.Elements[3][2] = Translation.Z;

    return (Result);
}

hmm_mat4
HMM_Rotate(float Angle, hmm_vec3 Axis)
{
    hmm_mat4 Result = HMM_Mat4d(1.0f);
    
    Axis = HMM_Normalize(Axis);
    
    float SinTheta = HMM_SinF(HMM_ToRadians(Angle));
    float CosTheta = HMM_CosF(HMM_ToRadians(Angle));
    float CosValue = 1.0f - CosTheta;
    
    Result.Elements[0][0] = (Axis.X * Axis.X * CosValue) + CosTheta;
    Result.Elements[0][1] = (Axis.X * Axis.Y * CosValue) + (Axis.Z * SinTheta);
    Result.Elements[0][2] = (Axis.X * Axis.Z * CosValue) - (Axis.Y * SinTheta);
    
    Result.Elements[1][0] = (Axis.Y * Axis.X * CosValue) - (Axis.Z * SinTheta);
    Result.Elements[1][1] = (Axis.Y * Axis.Y * CosValue) + CosTheta;
    Result.Elements[1][2] = (Axis.Y * Axis.Z * CosValue) + (Axis.X * SinTheta);
    
    Result.Elements[2][0] = (Axis.Z * Axis.X * CosValue) + (Axis.Y * SinTheta);
    Result.Elements[2][1] = (Axis.Z * Axis.Y * CosValue) - (Axis.X * SinTheta);
    Result.Elements[2][2] = (Axis.Z * Axis.Z * CosValue) + CosTheta;
    
    return (Result);
}

hmm_mat4
HMM_LookAt(hmm_vec3 Eye, hmm_vec3 Center, hmm_vec3 Up)
{
    hmm_mat4 Result = {0};

    hmm_vec3 F = HMM_Normalize(HMM_SubtractVec3(Center, Eye));
    hmm_vec3 S = HMM_Normalize(HMM_Cross(F, Up));
    hmm_vec3 U = HMM_Cross(S, F);

    Result.Elements[0][0] = S.X;
    Result.Elements[0][1] = U.X;
    Result.Elements[0][2] = -F.X;

    Result.Elements[1][0] = S.Y;
    Result.Elements[1][1] = U.Y;
    Result.Elements[1][2] = -F.Y;

    Result.Elements[2][0] = S.Z;
    Result.Elements[2][1] = U.Z;
    Result.Elements[2][2] = -F.Z;

    Result.Elements[3][0] = -HMM_DotVec3(S, Eye);
    Result.Elements[3][1] = -HMM_DotVec3(U, Eye);
    Result.Elements[3][2] = HMM_DotVec3(F, Eye);
    Result.Elements[3][3] = 1.0f;

    return (Result);
}

hmm_mat4
HMM_Scale(hmm_vec3 Scale)
{
    hmm_mat4 Result = HMM_Mat4d(1.0f);

    Result.Elements[0][0] = Scale.X;
    Result.Elements[1][1] = Scale.Y;
    Result.Elements[2][2] = Scale.Z;

    return (Result);
}

#ifdef HANDMADE_MATH_CPP_MODE

HINLINE float 
HMM_Dot(hmm_vec2 VecOne, hmm_vec2 VecTwo)
{
    float Result = 0;
    
    Result = HMM_DotVec2(VecOne, VecTwo);
    
    return(Result);
}

HINLINE float 
HMM_Dot(hmm_vec3 VecOne, hmm_vec3 VecTwo)
{
    float Result = 0;
    
    Result = HMM_DotVec3(VecOne, VecTwo);
    
    return(Result);
}

HMMDEF float 
HMM_Dot(hmm_vec4 VecOne, hmm_vec4 VecTwo)
{
    float Result = 0;
    
    Result = HMM_DotVec4(VecOne, VecTwo);
    
    return(Result);
}

HINLINE hmm_vec2
HMM_Add(hmm_vec2 Left, hmm_vec2 Right)
{
    hmm_vec2 Result = {0};

    Result = HMM_AddVec2(Left, Right);
    return (Result);
}

HINLINE hmm_vec3
HMM_Add(hmm_vec3 Left, hmm_vec3 Right)
{
    hmm_vec3 Result = {0};

    Result = HMM_AddVec3(Left, Right);
    return (Result);
}

HMMDEF HINLINE hmm_vec4
HMM_Add(hmm_vec4 Left, hmm_vec4 Right)
{
    hmm_vec4 Result = {0};

    Result = HMM_AddVec4(Left, Right);
    return (Result);
}

HINLINE hmm_mat4
HMM_Add(hmm_mat4 Left, hmm_mat4 Right)
{
    hmm_mat4 Result = {0};

    Result = HMM_AddMat4(Left, Right);
    return (Result);
}

HINLINE hmm_vec2
HMM_Subtract(hmm_vec2 Left, hmm_vec2 Right)
{
    hmm_vec2 Result = {0};

    Result = HMM_SubtractVec2(Left, Right);
    return (Result);
}

HINLINE hmm_vec3
HMM_Subtract(hmm_vec3 Left, hmm_vec3 Right)
{
    hmm_vec3 Result = {0};

    Result = HMM_SubtractVec3(Left, Right);
    return (Result);
}

HINLINE hmm_vec4
HMM_Subtract(hmm_vec4 Left, hmm_vec4 Right)
{
    hmm_vec4 Result = {0};

    Result = HMM_SubtractVec4(Left, Right);
    return (Result);
}

HINLINE hmm_mat4
HMM_Subtract(hmm_mat4 Left, hmm_mat4 Right)
{
    hmm_mat4 Result = {0};

    Result = HMM_SubtractMat4(Left, Right);
    return (Result);
}

HINLINE hmm_vec2
HMM_Multiply(hmm_vec2 Left, hmm_vec2 Right)
{
    hmm_vec2 Result = {0};

    Result = HMM_MultiplyVec2(Left, Right);
    return (Result);
}

HINLINE hmm_vec2
HMM_Multiply(hmm_vec2 Left, float Right)
{
    hmm_vec2 Result = {0};

    Result = HMM_MultiplyVec2f(Left, Right);
    return (Result);
}

HINLINE hmm_vec3
HMM_Multiply(hmm_vec3 Left, hmm_vec3 Right)
{
    hmm_vec3 Result = {0};

    Result = HMM_MultiplyVec3(Left, Right);
    return (Result);
}

HINLINE hmm_vec3
HMM_Multiply(hmm_vec3 Left, float Right)
{
    hmm_vec3 Result = {0};

    Result = HMM_MultiplyVec3f(Left, Right);
    return (Result);
}

HINLINE hmm_vec4
HMM_Multiply(hmm_vec4 Left, hmm_vec4 Right)
{
    hmm_vec4 Result = {0};

    Result = HMM_MultiplyVec4(Left, Right);
    return (Result);
}

HINLINE hmm_vec4
HMM_Multiply(hmm_vec4 Left, float Right)
{
    hmm_vec4 Result = {0};

    Result = HMM_MultiplyVec4f(Left, Right);
    return (Result);
}

HINLINE hmm_mat4
HMM_Multiply(hmm_mat4 Left, hmm_mat4 Right)
{
    hmm_mat4 Result = {0};

    Result = HMM_MultiplyMat4(Left, Right);
    return (Result);
}

HINLINE hmm_mat4
HMM_Multiply(hmm_mat4 Left, float Right)
{
    hmm_mat4 Result = {0};

    Result = HMM_MultiplyMat4f(Left, Right);
    return (Result);
}

HINLINE hmm_vec4
HMM_Multiply(hmm_mat4 Matrix, hmm_vec4 Vector)
{
    hmm_vec4 Result = {0};

    Result = HMM_MultiplyMat4ByVec4(Matrix, Vector);
    return (Result);
}

HINLINE hmm_vec2
HMM_Divide(hmm_vec2 Left, hmm_vec2 Right)
{
    hmm_vec2 Result = {0};

    Result = HMM_DivideVec2(Left, Right);
    return (Result);
}

HINLINE hmm_vec2
HMM_Divide(hmm_vec2 Left, float Right)
{
    hmm_vec2 Result = {0};

    Result = HMM_DivideVec2f(Left, Right);
    return (Result);
}

HINLINE hmm_vec3
HMM_Divide(hmm_vec3 Left, hmm_vec3 Right)
{
    hmm_vec3 Result = {0};

    Result = HMM_DivideVec3(Left, Right);
    return (Result);
}

HINLINE hmm_vec3
HMM_Divide(hmm_vec3 Left, float Right)
{
    hmm_vec3 Result = {0};

    Result = HMM_DivideVec3f(Left, Right);
    return (Result);
}

HINLINE hmm_vec4
HMM_Divide(hmm_vec4 Left, hmm_vec4 Right)
{
    hmm_vec4 Result = {0};

    Result = HMM_DivideVec4(Left, Right);
    return (Result);
}

HINLINE hmm_vec4
HMM_Divide(hmm_vec4 Left, float Right)
{
    hmm_vec4 Result = {0};

    Result = HMM_DivideVec4f(Left, Right);
    return (Result);
}

HINLINE hmm_mat4
HMM_Divide(hmm_mat4 Left, float Right)
{
    hmm_mat4 Result = {0};

    Result = HMM_DivideMat4f(Left, Right);
    return (Result);
}

HINLINE hmm_vec2
operator+(hmm_vec2 Left, hmm_vec2 Right)
{
    hmm_vec2 Result = {0};

    Result = HMM_Add(Left, Right);
    return (Result);
}

HINLINE hmm_vec3
operator+(hmm_vec3 Left, hmm_vec3 Right)
{
    hmm_vec3 Result = {0};

    Result = HMM_Add(Left, Right);
    return (Result);
}

HINLINE hmm_vec4
operator+(hmm_vec4 Left, hmm_vec4 Right)
{
    hmm_vec4 Result = {0};

    Result = HMM_Add(Left, Right);
    return (Result);
}

HINLINE hmm_mat4
operator+(hmm_mat4 Left, hmm_mat4 Right)
{
    hmm_mat4 Result = {0};

    Result = HMM_Add(Left, Right);
    return (Result);
}

HINLINE hmm_vec2
operator-(hmm_vec2 Left, hmm_vec2 Right)
{
    hmm_vec2 Result = {0};

    Result = HMM_Subtract(Left, Right);
    return (Result);
}

HINLINE hmm_vec3
operator-(hmm_vec3 Left, hmm_vec3 Right)
{
    hmm_vec3 Result = {0};

    Result = HMM_Subtract(Left, Right);
    return (Result);
}

HINLINE hmm_vec4
operator-(hmm_vec4 Left, hmm_vec4 Right)
{
    hmm_vec4 Result = {0};

    Result = HMM_Subtract(Left, Right);
    return (Result);
}

HINLINE hmm_mat4
operator-(hmm_mat4 Left, hmm_mat4 Right)
{
    hmm_mat4 Result = {0};

    Result = HMM_Subtract(Left, Right);
    return (Result);
}

HINLINE hmm_vec2
operator*(hmm_vec2 Left, hmm_vec2 Right)
{
    hmm_vec2 Result = {0};

    Result = HMM_Multiply(Left, Right);
    return (Result);
}

HINLINE hmm_vec3
operator*(hmm_vec3 Left, hmm_vec3 Right)
{
    hmm_vec3 Result = {0};

    Result = HMM_Multiply(Left, Right);
    return (Result);
}

HINLINE hmm_vec4
operator*(hmm_vec4 Left, hmm_vec4 Right)
{
    hmm_vec4 Result = HMM_Multiply(Left, Right);

    return (Result);
}

HINLINE hmm_vec2
operator*(hmm_vec2 Left, float Right)
{
    hmm_vec2 Result = {0};

    Result = HMM_Multiply(Left, Right);
    return (Result);
}

HINLINE hmm_vec3
operator*(hmm_vec3 Left, float Right)
{
    hmm_vec3 Result = {0};

    Result = HMM_Multiply(Left, Right);
    return (Result);
}

HINLINE hmm_vec4
operator*(hmm_vec4 Left, float Right)
{
    hmm_vec4 Result = {0};

    Result = HMM_Multiply(Left, Right);
    return (Result);
}

HINLINE hmm_mat4
operator*(hmm_mat4 Left, float Right)
{
    hmm_mat4 Result = {0};

    Result = HMM_Multiply(Left, Right);
    return (Result);
}

HINLINE hmm_vec2
operator*(float Left, hmm_vec2 Right)
{
    hmm_vec2 Result = {0};

    Result = HMM_Multiply(Right, Left);
    return (Result);
}

HINLINE hmm_vec3
operator*(float Left, hmm_vec3 Right)
{
    hmm_vec3 Result = {0};

    Result = HMM_Multiply(Right, Left);
    return (Result);
}

HINLINE hmm_vec4
operator*(float Left, hmm_vec4 Right)
{
    hmm_vec4 Result = {0};

    Result = HMM_Multiply(Right, Left);
    return (Result);
}

HINLINE hmm_mat4
operator*(float Left, hmm_mat4 Right)
{
    hmm_mat4 Result = {0};

    Result = HMM_Multiply(Right, Left);
    return (Result);
}

HINLINE hmm_mat4
operator*(hmm_mat4 Left, hmm_mat4 Right)
{
    hmm_mat4 Result = {0};

    Result = HMM_Multiply(Left, Right);
    return (Result);
}

HINLINE hmm_vec4
operator*(hmm_mat4 Matrix, hmm_vec4 Vector)
{
    hmm_vec4 Result = {0};

    Result = HMM_Multiply(Matrix, Vector);
    return (Result);
}

HINLINE hmm_vec2
operator/(hmm_vec2 Left, hmm_vec2 Right)
{
    hmm_vec2 Result = {0};

    Result = HMM_Divide(Left, Right);
    return (Result);
}

HINLINE hmm_vec3
operator/(hmm_vec3 Left, hmm_vec3 Right)
{
    hmm_vec3 Result = HMM_Divide(Left, Right);

    return (Result);
}

HINLINE hmm_vec4
operator/(hmm_vec4 Left, hmm_vec4 Right)
{
    hmm_vec4 Result = {0};

    Result = HMM_Divide(Left, Right);
    return (Result);
}

HINLINE hmm_vec2
operator/(hmm_vec2 Left, float Right)
{
    hmm_vec2 Result = {0};

    Result = HMM_Divide(Left, Right);
    return (Result);
}

HINLINE hmm_vec3
operator/(hmm_vec3 Left, float Right)
{
    hmm_vec3 Result = {0};

    Result = HMM_Divide(Left, Right);
    return (Result);
}

HINLINE hmm_vec4
operator/(hmm_vec4 Left, float Right)
{
    hmm_vec4 Result = {0};

    Result = HMM_Divide(Left, Right);
    return (Result);
}

HINLINE hmm_mat4
operator/(hmm_mat4 Left, float Right)
{
    hmm_mat4 Result = {0};

    Result = HMM_Divide(Left, Right);
    return (Result);
}

HINLINE hmm_vec2 &
operator+=(hmm_vec2 &Left, hmm_vec2 Right)
{    
    return (Left = Left + Right);
}

HINLINE hmm_vec3 &
operator+=(hmm_vec3 &Left, hmm_vec3 Right)
{    
    return (Left = Left + Right);
}

HINLINE hmm_vec4 &
operator+=(hmm_vec4 &Left, hmm_vec4 Right)
{    
    return (Left = Left + Right);
}

HINLINE hmm_mat4 &
operator+=(hmm_mat4 &Left, hmm_mat4 Right)
{
    return (Left = Left + Right);
}

HINLINE hmm_vec2 &
operator-=(hmm_vec2 &Left, hmm_vec2 Right)
{    
    return (Left = Left - Right);
}

HINLINE hmm_vec3 &
operator-=(hmm_vec3 &Left, hmm_vec3 Right)
{    
    return (Left = Left - Right);
}

HINLINE hmm_vec4 &
operator-=(hmm_vec4 &Left, hmm_vec4 Right)
{    
    return (Left = Left - Right);
}

HINLINE hmm_mat4 &
operator-=(hmm_mat4 &Left, hmm_mat4 Right)
{
    return (Left = Left - Right);
}

HINLINE hmm_vec2 &
operator/=(hmm_vec2 &Left, hmm_vec2 Right)
{    
    return (Left = Left / Right);
}

HINLINE hmm_vec3 &
operator/=(hmm_vec3 &Left, hmm_vec3 Right)
{    
    return (Left = Left / Right);
}

HINLINE hmm_vec4 &
operator/=(hmm_vec4 &Left, hmm_vec4 Right)
{    
    return (Left = Left / Right);
}

HINLINE hmm_vec2 &
operator/=(hmm_vec2 &Left, float Right)
{
    return (Left = Left / Right);
}

HINLINE hmm_vec3 &
operator/=(hmm_vec3 &Left, float Right)
{
    return (Left = Left / Right);
}

HINLINE hmm_vec4 &
operator/=(hmm_vec4 &Left, float Right)
{
    return (Left = Left / Right);
}

HINLINE hmm_mat4 &
operator/=(hmm_mat4 &Left, float Right)
{
    return (Left = Left / Right);
}

HINLINE hmm_vec2 &
operator*=(hmm_vec2 &Left, hmm_vec2 Right)
{    
    return (Left = Left * Right);
}

HINLINE hmm_vec3 &
operator*=(hmm_vec3 &Left, hmm_vec3 Right)
{    
    return (Left = Left * Right);
}

HINLINE hmm_vec4 &
operator*=(hmm_vec4 &Left, hmm_vec4 Right)
{    
    return (Left = Left * Right);
}

HINLINE hmm_vec2 &
operator*=(hmm_vec2 &Left, float Right)
{
    return (Left = Left * Right);
}

HINLINE hmm_vec3 &
operator*=(hmm_vec3 &Left, float Right)
{
    return (Left = Left * Right);
}

HINLINE hmm_vec4 &
operator*=(hmm_vec4 &Left, float Right)
{
    return (Left = Left * Right);
}

HINLINE hmm_mat4 &
operator*=(hmm_mat4 &Left, float Right)
{
    return (Left = Left * Right);
}

#endif /* HANDMADE_MATH_CPP_MODE */

#endif /* HANDMADE_MATH_IMPLEMENTATION */
