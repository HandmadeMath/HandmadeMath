/*
  HandmadeMath.h v1.13.0

  This is a single header file with a bunch of useful functions for game and
  graphics math operations.

  =============================================================================

  To disable SSE intrinsics, you MUST

  #define HANDMADE_MATH_NO_SSE

  in EXACTLY one C or C++ file that includes this header, BEFORE the
  include, like this:

     #define HANDMADE_MATH_NO_SSE
     #include "HandmadeMath.h"

  =============================================================================

  If you would prefer not to use the HMM_ prefix on function names, you can

  #define HMM_PREFIX

  To use a custom prefix instead, you can

  #define HMM_PREFIX(name) YOUR_PREFIX_##name

  =============================================================================

  To use HandmadeMath without the CRT, you MUST

     #define HMM_PROVIDE_MATH_FUNCTIONS

  Provide your own implementations of SinF, CosF, ACosF, ExpF, and LogF
  in EXACTLY one C or C++ file that includes this header,
  BEFORE the include, like this (assuming your functions take radians):

     #define HMM_PROVIDE_MATH_FUNCTIONS
     #define HMM_ANGLE_USER_TO_INTERNAL(a) (HMM_PREFIX(ToRadians)(a))
     #define HMM_ANGLE_INTERNAL_TO_USER(a) (a)
     #define HMM_SINF MySinF
     #define HMM_COSF MyCosF
     #define HMM_TANF MyTanF
     #define HMM_SQRTF MySqrtF
     #define HMM_EXPF MyExpF
     #define HMM_LOGF MyLogF
     #define HMM_ACOSF MyACosF
     #include "HandmadeMath.h"

  If you do not define all of these, HandmadeMath.h will use the
  versions of these functions that are provided by the CRT.

  =============================================================================

  LICENSE

  This software is in the public domain. Where that dedication is not
  recognized, you are granted a perpetual, irrevocable license to copy,
  distribute, and modify this file as you see fit.

  CREDITS

  Written by Zakary Strange (strangezak@protonmail.com && @strangezak)

  Functionality:
   Matt Mascarenhas (@miblo_)
   Aleph
   FieryDrake (@fierydrake)
   Gingerbill (@TheGingerBill)
   Ben Visness (@bvisness)
   Trinton Bullard (@Peliex_Dev)
   @AntonDan

  Fixes:
   Jeroen van Rijn (@J_vanRijn)
   Kiljacken (@Kiljacken)
   Insofaras (@insofaras)
   Daniel Gibson (@DanielGibson)
*/

// Dummy macros for when test framework is not present.
#ifndef COVERAGE
#define COVERAGE(a, b)
#endif

#ifndef ASSERT_COVERED
#define ASSERT_COVERED(a)
#endif

/* let's figure out if SSE is really available (unless disabled anyway)
   (it isn't on non-x86/x86_64 platforms or even x86 without explicit SSE support)
   => only use "#ifdef HANDMADE_MATH__USE_SSE" to check for SSE support below this block! */
#ifndef HANDMADE_MATH_NO_SSE

# ifdef _MSC_VER
   /* MSVC supports SSE in amd64 mode or _M_IX86_FP >= 1 (2 means SSE2) */
#  if defined(_M_AMD64) || ( defined(_M_IX86_FP) && _M_IX86_FP >= 1 )
#   define HANDMADE_MATH__USE_SSE 1
#  endif
# else /* not MSVC, probably GCC, clang, icc or something that doesn't support SSE anyway */
#  ifdef __SSE__ /* they #define __SSE__ if it's supported */
#   define HANDMADE_MATH__USE_SSE 1
#  endif /*  __SSE__ */
# endif /* not _MSC_VER */

#endif /* #ifndef HANDMADE_MATH_NO_SSE */

#ifdef HANDMADE_MATH__USE_SSE
#include <xmmintrin.h>
#endif

#ifndef HANDMADE_MATH_H
#define HANDMADE_MATH_H

#ifdef _MSC_VER
#pragma warning(disable:4201)
#endif

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
#if (defined(__GNUC__) && (__GNUC__ == 4 && __GNUC_MINOR__ < 8)) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wmissing-braces"
#endif
#ifdef __clang__
#pragma GCC diagnostic ignored "-Wgnu-anonymous-struct"
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif
#endif

#if defined(__GNUC__) || defined(__clang__)
#define HMM_DEPRECATED(msg) __attribute__((deprecated(msg)))
#elif defined(_MSC_VER)
#define HMM_DEPRECATED(msg) __declspec(deprecated(msg))
#else
#define HMM_DEPRECATED(msg)
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#define HMM_INLINE static inline

#if !defined(HMM_SINF) || !defined(HMM_COSF) || !defined(HMM_TANF) || \
    !defined(HMM_SQRTF) || !defined(HMM_EXPF) || !defined(HMM_LOGF) || \
    !defined(HMM_ACOSF) || !defined(HMM_ATANF)|| !defined(HMM_ATAN2F)
#include <math.h>
#endif

#if !defined(HMM_USE_DEGREE_INPUT) \
    && !defined(HMM_USE_TURN_INPUT) \
    && !defined(HMM_USE_RADIAN_INPUT)
#define HMM_USE_RADIAN_INPUT
#endif
    
#define HMM_PI 3.14159265358979323846
#define HMM_PI32 3.14159265359f
#define HMM_DEG180 180.0
#define HMM_DEG18032 180.0f
#define HMM_TURNHALF 0.5
#define HMM_TURNHALF32 0.5f
#define HMM_RadToDeg (HMM_DEG180/HMM_PI)
#define HMM_RadToTurn (HMM_TURNHALF/HMM_PI)
#define HMM_DegToRad (HMM_PI/HMM_DEG180)
#define HMM_DegToTurn (HMM_TURNHALF/HMM_DEG180)
#define HMM_TurnToRad (HMM_PI/HMM_TURNHALF)
#define HMM_TurnToDeg (HMM_DEG180/HMM_TURNHALF)

#if defined(HMM_USE_RADIAN_INPUT)
#define HMM_AngleRad(a) (a)
#define HMM_AngleDeg(a) ((a)*HMM_DegToRad)
#define HMM_AngleTurn(a) ((a)*HMM_TurnToRad)
#elif defined(HMM_USE_DEGREE_INPUT) 
#define HMM_AngleRad(a) ((a)*HMM_RadToDeg)
#define HMM_AngleDeg(a) (a)
#define HMM_AngleTurn(a) ((a)*HMM_TurnToDeg)
#elif defined(HMM_USE_TURN_INPUT)
#define HMM_AngleRad(a) ((a)*HMM_RadToTurn)
#define HMM_AngleDeg(a) ((a)*HMM_DegToTurn)
#define HMM_AngleTurn(a) (a)
#endif

#if !defined(HMM_PROVIDE_MATH_FUNCTIONS)
/* Conversion function to the unit the trig functions need angles in.
   Define as one of HMM_ToRadians, HMM_ToDegrees, or HMM_ToTurns. */
#define HMM_ANGLE_USER_TO_INTERNAL(a) (HMM_PREFIX(ToRadians)(a))
/* Conversion function to the User's input angle unit from the internal unit.
   If your internal and input angle units are the same simply define:
#define HMM_ANGLE_INTERNAL_TO_USER(a) (a) 
   Default internal angle unit is radians. */
#if defined(HMM_USE_RADIAN_INPUT)
#define HMM_ANGLE_INTERNAL_TO_USER(a) (a) 
#elif defined(HMM_USE_DEGREE_INPUT)
#define HMM_ANGLE_INTERNAL_TO_USER(a) ((a)*HMM_RadToDeg)
#elif defined(HMM_USE_TURN_INPUT)
#define HMM_ANGLE_INTERNAL_TO_USER(a) ((a)*HMM_RadToTurn)
#endif
    
#define HMM_SINF sinf
#define HMM_COSF cosf
#define HMM_TANF tanf
#define HMM_SQRTF sqrtf
#define HMM_EXPF expf
#define HMM_LOGF logf
#define HMM_ACOSF acosf
#define HMM_ATANF atanf
#define HMM_ATAN2F atan2f
#endif

#define HMM_MIN(a, b) ((a) > (b) ? (b) : (a))
#define HMM_MAX(a, b) ((a) < (b) ? (b) : (a))
#define HMM_ABS(a) ((a) > 0 ? (a) : -(a))
#define HMM_MOD(a, m) (((a) % (m)) >= 0 ? ((a) % (m)) : (((a) % (m)) + (m)))
#define HMM_SQUARE(x) ((x) * (x))

#ifndef HMM_PREFIX
#define HMM_PREFIX(name) HMM_##name
#endif

typedef union HMM_Vec2
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

    struct
    {
        float Width, Height;
    };

    float Elements[2];

#ifdef __cplusplus
    inline float &operator[](const int &Index)
    {
        return Elements[Index];
    }
#endif
} HMM_Vec2;
typedef HMM_Vec2 HMM_PREFIX(Vec2);

typedef union HMM_Vec3
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
        HMM_Vec2 XY;
        float Ignored0_;
    };

    struct
    {
        float Ignored1_;
        HMM_Vec2 YZ;
    };

    struct
    {
        HMM_Vec2 UV;
        float Ignored2_;
    };

    struct
    {
        float Ignored3_;
        HMM_Vec2 VW;
    };

    float Elements[3];

#ifdef __cplusplus
    inline float &operator[](const int &Index)
    {
        return Elements[Index];
    }
#endif
} HMM_Vec3;
typedef HMM_Vec3 HMM_PREFIX(Vec3);

typedef union HMM_Vec4
{
    struct
    {
        union
        {
            HMM_Vec3 XYZ;
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
            HMM_Vec3 RGB;
            struct
            {
                float R, G, B;
            };
        };

        float A;
    };

    struct
    {
        HMM_Vec2 XY;
        float Ignored0_;
        float Ignored1_;
    };

    struct
    {
        float Ignored2_;
        HMM_Vec2 YZ;
        float Ignored3_;
    };

    struct
    {
        float Ignored4_;
        float Ignored5_;
        HMM_Vec2 ZW;
    };

    float Elements[4];

#ifdef HANDMADE_MATH__USE_SSE
    __m128 InternalElementsSSE;
#endif

#ifdef __cplusplus
    inline float &operator[](const int &Index)
    {
        return Elements[Index];
    }
#endif
} HMM_Vec4;
typedef HMM_Vec4 HMM_PREFIX(Vec4);

typedef union HMM_Mat4
{
    float Elements[4][4];

#ifdef HANDMADE_MATH__USE_SSE
    __m128 Columns[4];

    HMM_DEPRECATED("Our matrices are column-major, so this was named incorrectly. Use Columns instead.")
    __m128 Rows[4];
#endif

#ifdef __cplusplus
    inline HMM_Vec4 operator[](const int &Index)
    {
        HMM_Vec4 Result;
        float* Column = Elements[Index];
        

        Result.Elements[0] = Column[0];
        Result.Elements[1] = Column[1];
        Result.Elements[2] = Column[2];
        Result.Elements[3] = Column[3];

        return Result;
    }
#endif
} HMM_Mat4;
typedef HMM_Mat4 HMM_PREFIX(Mat4);

typedef union HMM_Quat
{
    struct
    {
        union
        {
            HMM_Vec3 XYZ;
            struct
            {
                float X, Y, Z;
            };
        };

        float W;
    };

    float Elements[4];

#ifdef HANDMADE_MATH__USE_SSE
    __m128 InternalElementsSSE;
#endif
} HMM_Quat;
typedef HMM_Quat HMM_PREFIX(Quat);

typedef signed int HMM_Bool;
typedef HMM_Bool HMM_PREFIX(Bool); /* TODO(lcf): seems kinda silly */


/*
 * Angle unit conversion functions
 */
HMM_INLINE float HMM_PREFIX(ToRadians)(float Angle)
{
#if defined(HMM_USE_RADIAN_INPUT)
    float Result = Angle;
#elif defined(HMM_USE_DEGREE_INPUT) 
    float Result = Angle * HMM_DegToRad;
#elif defined(HMM_USE_TURN_INPUT)
    float Result = Angle * HMM_TurnToRad;
#endif
    
    return (Result);
}

HMM_INLINE float HMM_PREFIX(ToDegrees)(float Angle)
{
#if defined(HMM_USE_RADIAN_INPUT)
    float Result = Angle * HMM_RadToDeg;
#elif defined(HMM_USE_DEGREE_INPUT) 
    float Result = Angle;
#elif defined(HMM_USE_TURN_INPUT)
    float Result = Angle * HMM_TurnToDeg;
#endif
    
    return (Result);
}

HMM_INLINE float HMM_PREFIX(ToTurns)(float Angle)
{
#if defined(HMM_USE_RADIAN_INPUT)
    float Result = Angle * HMM_RadToTurn;
#elif defined(HMM_USE_DEGREE_INPUT) 
    float Result = Angle * HMM_DegToTurn;
#elif defined(HMM_USE_TURN_INPUT)
    float Result = Angle;
#endif
    
    return (Result);
}

/*
 * Floating-point math functions
 */

COVERAGE(HMM_SinF, 1)
HMM_INLINE float HMM_PREFIX(SinF)(float Angle)
{
    ASSERT_COVERED(HMM_SinF);

    float Result = HMM_SINF(HMM_ANGLE_USER_TO_INTERNAL(Angle));

    return (Result);
}

COVERAGE(HMM_CosF, 1)
HMM_INLINE float HMM_PREFIX(CosF)(float Angle)
{
    ASSERT_COVERED(HMM_CosF);

    float Result = HMM_COSF(HMM_ANGLE_USER_TO_INTERNAL(Angle));

    return (Result);
}

COVERAGE(HMM_ACosF, 1)
HMM_INLINE float HMM_PREFIX(ACosF)(float Angle)
{
    ASSERT_COVERED(HMM_ACosF);

    float Result = HMM_ANGLE_INTERNAL_TO_USER(HMM_ACOSF(Angle));

    return (Result);
}

COVERAGE(HMM_TanF, 1)
HMM_INLINE float HMM_PREFIX(TanF)(float Angle)
{
    ASSERT_COVERED(HMM_TanF);
    float Result = HMM_TANF(HMM_ANGLE_USER_TO_INTERNAL(Angle));
    return (Result);
}

COVERAGE(HMM_ExpF, 1)
HMM_INLINE float HMM_PREFIX(ExpF)(float Float)
{
    ASSERT_COVERED(HMM_ExpF);

    float Result = HMM_EXPF(Float);

    return (Result);
}

COVERAGE(HMM_LogF, 1)
HMM_INLINE float HMM_PREFIX(LogF)(float Float)
{
    ASSERT_COVERED(HMM_LogF);

    float Result = HMM_LOGF(Float);

    return (Result);
}

COVERAGE(HMM_SqrtF, 1)
HMM_INLINE float HMM_PREFIX(SqrtF)(float Float)
{
    ASSERT_COVERED(HMM_SqrtF);

    float Result;

#ifdef HANDMADE_MATH__USE_SSE
    __m128 In = _mm_set_ss(Float);
    __m128 Out = _mm_sqrt_ss(In);
    Result = _mm_cvtss_f32(Out);
#else
    Result = HMM_SQRTF(Float);
#endif

    return(Result);
}

COVERAGE(HMM_InvSqrtF, 1)
HMM_INLINE float HMM_PREFIX(InvSqrtF)(float Float)
{
    ASSERT_COVERED(HMM_InvSqrtF);

    float Result;

#ifdef HANDMADE_MATH__USE_SSE
    __m128 In = _mm_set_ss(Float);
    __m128 Out = _mm_rsqrt_ss(In);
    Result = _mm_cvtss_f32(Out);
#else
    Result = 1.0f/HMM_PREFIX(SqrtF)(Float);
#endif

    return(Result);
}

COVERAGE(HMM_Power, 2)
HMM_INLINE float HMM_PREFIX(Power)(float Base, int Exponent)
{
    ASSERT_COVERED(HMM_Power);

    float Result = 1.0f;
    float Mul = Exponent < 0 ? 1.f / Base : Base;
    int X = Exponent < 0 ? -Exponent : Exponent;
    while (X)
    {
        if (X & 1)
        {
            ASSERT_COVERED(HMM_Power);

            Result *= Mul;
        }

        Mul *= Mul;
        X >>= 1;
    }

    return (Result);
}

COVERAGE(HMM_PowerF, 1)
HMM_INLINE float HMM_PREFIX(PowerF)(float Base, float Exponent)
{
    ASSERT_COVERED(HMM_PowerF);

    float Result = HMM_EXPF(Exponent * HMM_LOGF(Base));

    return (Result);
}


/*
 * Utility functions
 */

COVERAGE(HMM_Lerp, 1)
HMM_INLINE float HMM_PREFIX(Lerp)(float A, float Time, float B)
{
    ASSERT_COVERED(HMM_Lerp);

    float Result = (1.0f - Time) * A + Time * B;

    return (Result);
}

COVERAGE(HMM_Clamp, 1)
HMM_INLINE float HMM_PREFIX(Clamp)(float Min, float Value, float Max)
{
    ASSERT_COVERED(HMM_Clamp);

    float Result = Value;

    if(Result < Min)
    {
        Result = Min;
    }

    if(Result > Max)
    {
        Result = Max;
    }

    return (Result);
}


/*
 * Vector initialization
 */

COVERAGE(HMM_V2, 1)
HMM_INLINE HMM_Vec2 HMM_PREFIX(V2)(float X, float Y)
{
    ASSERT_COVERED(HMM_V2);

    HMM_Vec2 Result;

    Result.X = X;
    Result.Y = Y;

    return (Result);
}

COVERAGE(HMM_V2I, 1)
HMM_INLINE HMM_Vec2 HMM_PREFIX(V2I)(int X, int Y)
{
    ASSERT_COVERED(HMM_V2I);

    HMM_Vec2 Result;

    Result.X = (float)X;
    Result.Y = (float)Y;

    return (Result);
}

COVERAGE(HMM_V3, 1)
HMM_INLINE HMM_Vec3 HMM_PREFIX(V3)(float X, float Y, float Z)
{
    ASSERT_COVERED(HMM_V3);

    HMM_Vec3 Result;

    Result.X = X;
    Result.Y = Y;
    Result.Z = Z;

    return (Result);
}

COVERAGE(HMM_V3I, 1)
HMM_INLINE HMM_Vec3 HMM_PREFIX(V3I)(int X, int Y, int Z)
{
    ASSERT_COVERED(HMM_V3I);

    HMM_Vec3 Result;

    Result.X = (float)X;
    Result.Y = (float)Y;
    Result.Z = (float)Z;

    return (Result);
}

COVERAGE(HMM_V4, 1)
HMM_INLINE HMM_Vec4 HMM_PREFIX(V4)(float X, float Y, float Z, float W)
{
    ASSERT_COVERED(HMM_V4);

    HMM_Vec4 Result;

#ifdef HANDMADE_MATH__USE_SSE
    Result.InternalElementsSSE = _mm_setr_ps(X, Y, Z, W);
#else
    Result.X = X;
    Result.Y = Y;
    Result.Z = Z;
    Result.W = W;
#endif

    return (Result);
}

COVERAGE(HMM_V4I, 1)
HMM_INLINE HMM_Vec4 HMM_PREFIX(V4I)(int X, int Y, int Z, int W)
{
    ASSERT_COVERED(HMM_V4I);

    HMM_Vec4 Result;

#ifdef HANDMADE_MATH__USE_SSE
    Result.InternalElementsSSE = _mm_setr_ps((float)X, (float)Y, (float)Z, (float)W);
#else
    Result.X = (float)X;
    Result.Y = (float)Y;
    Result.Z = (float)Z;
    Result.W = (float)W;
#endif

    return (Result);
}

COVERAGE(HMM_V4V, 1)
HMM_INLINE HMM_Vec4 HMM_PREFIX(V4V)(HMM_Vec3 Vector, float W)
{
    ASSERT_COVERED(HMM_V4V);

    HMM_Vec4 Result;

#ifdef HANDMADE_MATH__USE_SSE
    Result.InternalElementsSSE = _mm_setr_ps(Vector.X, Vector.Y, Vector.Z, W);
#else
    Result.XYZ = Vector;
    Result.W = W;
#endif

    return (Result);
}


/*
 * Binary vector operations
 */

COVERAGE(HMM_AddV2, 1)
HMM_INLINE HMM_Vec2 HMM_PREFIX(AddV2)(HMM_Vec2 Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_AddV2);

    HMM_Vec2 Result;

    Result.X = Left.X + Right.X;
    Result.Y = Left.Y + Right.Y;

    return (Result);
}

COVERAGE(HMM_AddV3, 1)
HMM_INLINE HMM_Vec3 HMM_PREFIX(AddV3)(HMM_Vec3 Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_AddV3);

    HMM_Vec3 Result;

    Result.X = Left.X + Right.X;
    Result.Y = Left.Y + Right.Y;
    Result.Z = Left.Z + Right.Z;

    return (Result);
}

COVERAGE(HMM_AddV4, 1)
HMM_INLINE HMM_Vec4 HMM_PREFIX(AddV4)(HMM_Vec4 Left, HMM_Vec4 Right)
{
    ASSERT_COVERED(HMM_AddV4);

    HMM_Vec4 Result;

#ifdef HANDMADE_MATH__USE_SSE
    Result.InternalElementsSSE = _mm_add_ps(Left.InternalElementsSSE, Right.InternalElementsSSE);
#else
    Result.X = Left.X + Right.X;
    Result.Y = Left.Y + Right.Y;
    Result.Z = Left.Z + Right.Z;
    Result.W = Left.W + Right.W;
#endif

    return (Result);
}

COVERAGE(HMM_SubV2, 1)
HMM_INLINE HMM_Vec2 HMM_PREFIX(SubV2)(HMM_Vec2 Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_SubV2);

    HMM_Vec2 Result;

    Result.X = Left.X - Right.X;
    Result.Y = Left.Y - Right.Y;

    return (Result);
}

COVERAGE(HMM_SubV3, 1)
HMM_INLINE HMM_Vec3 HMM_PREFIX(SubV3)(HMM_Vec3 Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_SubV3);

    HMM_Vec3 Result;

    Result.X = Left.X - Right.X;
    Result.Y = Left.Y - Right.Y;
    Result.Z = Left.Z - Right.Z;

    return (Result);
}

COVERAGE(HMM_SubV4, 1)
HMM_INLINE HMM_Vec4 HMM_PREFIX(SubV4)(HMM_Vec4 Left, HMM_Vec4 Right)
{
    ASSERT_COVERED(HMM_SubV4);

    HMM_Vec4 Result;

#ifdef HANDMADE_MATH__USE_SSE
    Result.InternalElementsSSE = _mm_sub_ps(Left.InternalElementsSSE, Right.InternalElementsSSE);
#else
    Result.X = Left.X - Right.X;
    Result.Y = Left.Y - Right.Y;
    Result.Z = Left.Z - Right.Z;
    Result.W = Left.W - Right.W;
#endif

    return (Result);
}

COVERAGE(HMM_MulV2, 1)
HMM_INLINE HMM_Vec2 HMM_PREFIX(MulV2)(HMM_Vec2 Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_MulV2);

    HMM_Vec2 Result;

    Result.X = Left.X * Right.X;
    Result.Y = Left.Y * Right.Y;

    return (Result);
}

COVERAGE(HMM_MulV2F, 1)
HMM_INLINE HMM_Vec2 HMM_PREFIX(MulV2F)(HMM_Vec2 Left, float Right)
{
    ASSERT_COVERED(HMM_MulV2F);

    HMM_Vec2 Result;

    Result.X = Left.X * Right;
    Result.Y = Left.Y * Right;

    return (Result);
}

COVERAGE(HMM_MulV3, 1)
HMM_INLINE HMM_Vec3 HMM_PREFIX(MulV3)(HMM_Vec3 Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_MulV3);

    HMM_Vec3 Result;

    Result.X = Left.X * Right.X;
    Result.Y = Left.Y * Right.Y;
    Result.Z = Left.Z * Right.Z;

    return (Result);
}

COVERAGE(HMM_MulV3F, 1)
HMM_INLINE HMM_Vec3 HMM_PREFIX(MulV3F)(HMM_Vec3 Left, float Right)
{
    ASSERT_COVERED(HMM_MulV3F);

    HMM_Vec3 Result;

    Result.X = Left.X * Right;
    Result.Y = Left.Y * Right;
    Result.Z = Left.Z * Right;

    return (Result);
}

COVERAGE(HMM_MulV4, 1)
HMM_INLINE HMM_Vec4 HMM_PREFIX(MulV4)(HMM_Vec4 Left, HMM_Vec4 Right)
{
    ASSERT_COVERED(HMM_MulV4);

    HMM_Vec4 Result;

#ifdef HANDMADE_MATH__USE_SSE
    Result.InternalElementsSSE = _mm_mul_ps(Left.InternalElementsSSE, Right.InternalElementsSSE);
#else
    Result.X = Left.X * Right.X;
    Result.Y = Left.Y * Right.Y;
    Result.Z = Left.Z * Right.Z;
    Result.W = Left.W * Right.W;
#endif

    return (Result);
}

COVERAGE(HMM_MulV4F, 1)
HMM_INLINE HMM_Vec4 HMM_PREFIX(MulV4F)(HMM_Vec4 Left, float Right)
{
    ASSERT_COVERED(HMM_MulV4F);

    HMM_Vec4 Result;

#ifdef HANDMADE_MATH__USE_SSE
    __m128 Scalar = _mm_set1_ps(Right);
    Result.InternalElementsSSE = _mm_mul_ps(Left.InternalElementsSSE, Scalar);
#else
    Result.X = Left.X * Right;
    Result.Y = Left.Y * Right;
    Result.Z = Left.Z * Right;
    Result.W = Left.W * Right;
#endif

    return (Result);
}

COVERAGE(HMM_DivV2, 1)
HMM_INLINE HMM_Vec2 HMM_PREFIX(DivV2)(HMM_Vec2 Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_DivV2);

    HMM_Vec2 Result;

    Result.X = Left.X / Right.X;
    Result.Y = Left.Y / Right.Y;

    return (Result);
}

COVERAGE(HMM_DivV2F, 1)
HMM_INLINE HMM_Vec2 HMM_PREFIX(DivV2F)(HMM_Vec2 Left, float Right)
{
    ASSERT_COVERED(HMM_DivV2F);

    HMM_Vec2 Result;

    Result.X = Left.X / Right;
    Result.Y = Left.Y / Right;

    return (Result);
}

COVERAGE(HMM_DivV3, 1)
HMM_INLINE HMM_Vec3 HMM_PREFIX(DivV3)(HMM_Vec3 Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_DivV3);

    HMM_Vec3 Result;

    Result.X = Left.X / Right.X;
    Result.Y = Left.Y / Right.Y;
    Result.Z = Left.Z / Right.Z;

    return (Result);
}

COVERAGE(HMM_DivV3F, 1)
HMM_INLINE HMM_Vec3 HMM_PREFIX(DivV3F)(HMM_Vec3 Left, float Right)
{
    ASSERT_COVERED(HMM_DivV3F);

    HMM_Vec3 Result;

    Result.X = Left.X / Right;
    Result.Y = Left.Y / Right;
    Result.Z = Left.Z / Right;

    return (Result);
}

COVERAGE(HMM_DivV4, 1)
HMM_INLINE HMM_Vec4 HMM_PREFIX(DivV4)(HMM_Vec4 Left, HMM_Vec4 Right)
{
    ASSERT_COVERED(HMM_DivV4);

    HMM_Vec4 Result;

#ifdef HANDMADE_MATH__USE_SSE
    Result.InternalElementsSSE = _mm_div_ps(Left.InternalElementsSSE, Right.InternalElementsSSE);
#else
    Result.X = Left.X / Right.X;
    Result.Y = Left.Y / Right.Y;
    Result.Z = Left.Z / Right.Z;
    Result.W = Left.W / Right.W;
#endif

    return (Result);
}

COVERAGE(HMM_DivV4F, 1)
HMM_INLINE HMM_Vec4 HMM_PREFIX(DivV4F)(HMM_Vec4 Left, float Right)
{
    ASSERT_COVERED(HMM_DivV4F);

    HMM_Vec4 Result;

#ifdef HANDMADE_MATH__USE_SSE
    __m128 Scalar = _mm_set1_ps(Right);
    Result.InternalElementsSSE = _mm_div_ps(Left.InternalElementsSSE, Scalar);
#else
    Result.X = Left.X / Right;
    Result.Y = Left.Y / Right;
    Result.Z = Left.Z / Right;
    Result.W = Left.W / Right;
#endif

    return (Result);
}

COVERAGE(HMM_EqV2, 1)
HMM_INLINE HMM_Bool HMM_PREFIX(EqV2)(HMM_Vec2 Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_EqV2);

    HMM_Bool Result = (Left.X == Right.X && Left.Y == Right.Y);

    return (Result);
}

COVERAGE(HMM_EqV3, 1)
HMM_INLINE HMM_Bool HMM_PREFIX(EqV3)(HMM_Vec3 Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_EqV3);

    HMM_Bool Result = (Left.X == Right.X && Left.Y == Right.Y && Left.Z == Right.Z);

    return (Result);
}

COVERAGE(HMM_EqV4, 1)
HMM_INLINE HMM_Bool HMM_PREFIX(EqV4)(HMM_Vec4 Left, HMM_Vec4 Right)
{
    ASSERT_COVERED(HMM_EqV4);

    HMM_Bool Result = (Left.X == Right.X && Left.Y == Right.Y && Left.Z == Right.Z && Left.W == Right.W);

    return (Result);
}

COVERAGE(HMM_DotV2, 1)
HMM_INLINE float HMM_PREFIX(DotV2)(HMM_Vec2 Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_DotV2);

    float Result = (Left.X * Right.X) + (Left.Y * Right.Y);

    return (Result);
}

COVERAGE(HMM_DotV3, 1)
HMM_INLINE float HMM_PREFIX(DotV3)(HMM_Vec3 Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_DotV3);

    float Result = (Left.X * Right.X) + (Left.Y * Right.Y) + (Left.Z * Right.Z);

    return (Result);
}

COVERAGE(HMM_DotV4, 1)
HMM_INLINE float HMM_PREFIX(DotV4)(HMM_Vec4 Left, HMM_Vec4 Right)
{
    ASSERT_COVERED(HMM_DotV4);

    float Result;

    // NOTE(zak): IN the future if we wanna check what version SSE is support
    // we can use _mm_dp_ps (4.3) but for now we will use the old way.
    // Or a r = _mm_mul_ps(v1, v2), r = _mm_hadd_ps(r, r), r = _mm_hadd_ps(r, r) for SSE3
#ifdef HANDMADE_MATH__USE_SSE
    __m128 SSEResultOne = _mm_mul_ps(Left.InternalElementsSSE, Right.InternalElementsSSE);
    __m128 SSEResultTwo = _mm_shuffle_ps(SSEResultOne, SSEResultOne, _MM_SHUFFLE(2, 3, 0, 1));
    SSEResultOne = _mm_add_ps(SSEResultOne, SSEResultTwo);
    SSEResultTwo = _mm_shuffle_ps(SSEResultOne, SSEResultOne, _MM_SHUFFLE(0, 1, 2, 3));
    SSEResultOne = _mm_add_ps(SSEResultOne, SSEResultTwo);
    _mm_store_ss(&Result, SSEResultOne);
#else
    Result = (Left.X * Right.X) + (Left.Y * Right.Y) + (Left.Z * Right.Z) + (Left.W * Right.W);
#endif

    return (Result);
}

COVERAGE(HMM_Cross, 1)
HMM_INLINE HMM_Vec3 HMM_PREFIX(Cross)(HMM_Vec3 Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_Cross);

    HMM_Vec3 Result;

    Result.X = (Left.Y * Right.Z) - (Left.Z * Right.Y);
    Result.Y = (Left.Z * Right.X) - (Left.X * Right.Z);
    Result.Z = (Left.X * Right.Y) - (Left.Y * Right.X);

    return (Result);
}


/*
 * Unary vector operations
 */

COVERAGE(HMM_LenSqrV2, 1)
HMM_INLINE float HMM_PREFIX(LenSqrV2)(HMM_Vec2 A)
{
    ASSERT_COVERED(HMM_LenSqrV2);

    float Result = HMM_PREFIX(DotV2)(A, A);

    return (Result);
}

COVERAGE(HMM_LenSqrV3, 1)
HMM_INLINE float HMM_PREFIX(LenSqrV3)(HMM_Vec3 A)
{
    ASSERT_COVERED(HMM_LenSqrV3);

    float Result = HMM_PREFIX(DotV3)(A, A);

    return (Result);
}

COVERAGE(HMM_LenSqrV4, 1)
HMM_INLINE float HMM_PREFIX(LenSqrV4)(HMM_Vec4 A)
{
    ASSERT_COVERED(HMM_LenSqrV4);

    float Result = HMM_PREFIX(DotV4)(A, A);

    return (Result);
}

COVERAGE(HMM_LenV2, 1)
HMM_INLINE float HMM_PREFIX(LenV2)(HMM_Vec2 A)
{
    ASSERT_COVERED(HMM_LenV2);

    float Result = HMM_PREFIX(SqrtF)(HMM_PREFIX(LenSqrV2)(A));

    return (Result);
}

COVERAGE(HMM_LenV3, 1)
HMM_INLINE float HMM_PREFIX(LenV3)(HMM_Vec3 A)
{
    ASSERT_COVERED(HMM_LenV3);

    float Result = HMM_PREFIX(SqrtF)(HMM_PREFIX(LenSqrV3)(A));

    return (Result);
}

COVERAGE(HMM_LenV4, 1)
HMM_INLINE float HMM_PREFIX(LenV4)(HMM_Vec4 A)
{
    ASSERT_COVERED(HMM_LenV4);

    float Result = HMM_PREFIX(SqrtF)(HMM_PREFIX(LenSqrV4)(A));

    return(Result);
}

COVERAGE(HMM_NormV2, 2)
HMM_INLINE HMM_Vec2 HMM_PREFIX(NormV2)(HMM_Vec2 A)
{
    ASSERT_COVERED(HMM_NormV2);

    HMM_Vec2 Result = {0};

    float ALen = HMM_PREFIX(LenV2)(A);

    /* NOTE(kiljacken): We need a zero check to not divide-by-zero */
    if (ALen != 0.0f)
    {
        ASSERT_COVERED(HMM_NormV2);

        Result.X = A.X * (1.0f / ALen);
        Result.Y = A.Y * (1.0f / ALen);
    }

    return (Result);
}

COVERAGE(HMM_NormV3, 2)
HMM_INLINE HMM_Vec3 HMM_PREFIX(NormV3)(HMM_Vec3 A)
{
    ASSERT_COVERED(HMM_NormV3);

    HMM_Vec3 Result = {0};

    float ALen = HMM_PREFIX(LenV3)(A);

    /* NOTE(kiljacken): We need a zero check to not divide-by-zero */
    if (ALen != 0.0f)
    {
        ASSERT_COVERED(HMM_NormV3);

        Result.X = A.X * (1.0f / ALen);
        Result.Y = A.Y * (1.0f / ALen);
        Result.Z = A.Z * (1.0f / ALen);
    }

    return (Result);
}

COVERAGE(HMM_NormV4, 2)
HMM_INLINE HMM_Vec4 HMM_PREFIX(NormV4)(HMM_Vec4 A)
{
    ASSERT_COVERED(HMM_NormV4);

    HMM_Vec4 Result = {0};

    float ALen = HMM_PREFIX(LenV4)(A);

    /* NOTE(kiljacken): We need a zero check to not divide-by-zero */
    if (ALen != 0.0f)
    {
        ASSERT_COVERED(HMM_NormV4);

        float Multiplier = 1.0f / ALen;

#ifdef HANDMADE_MATH__USE_SSE
        __m128 SSEMultiplier = _mm_set1_ps(Multiplier);
        Result.InternalElementsSSE = _mm_mul_ps(A.InternalElementsSSE, SSEMultiplier);
#else
        Result.X = A.X * Multiplier;
        Result.Y = A.Y * Multiplier;
        Result.Z = A.Z * Multiplier;
        Result.W = A.W * Multiplier;
#endif
    }

    return (Result);
}

COVERAGE(HMM_FastNormV2, 1)
HMM_INLINE HMM_Vec2 HMM_PREFIX(FastNormV2)(HMM_Vec2 A)
{
    ASSERT_COVERED(HMM_FastNormV2);

    return HMM_PREFIX(MulV2F)(A, HMM_PREFIX(InvSqrtF)(HMM_PREFIX(DotV2)(A, A)));
}

COVERAGE(HMM_FastNormV3, 1)
HMM_INLINE HMM_Vec3 HMM_PREFIX(FastNormV3)(HMM_Vec3 A)
{
    ASSERT_COVERED(HMM_FastNormV3);

    return HMM_PREFIX(MulV3F)(A, HMM_PREFIX(InvSqrtF)(HMM_PREFIX(DotV3)(A, A)));
}

COVERAGE(HMM_FastNormV4, 1)
HMM_INLINE HMM_Vec4 HMM_PREFIX(FastNormV4)(HMM_Vec4 A)
{
    ASSERT_COVERED(HMM_FastNormV4);

    return HMM_PREFIX(MulV4F)(A, HMM_PREFIX(InvSqrtF)(HMM_PREFIX(DotV4)(A, A)));
}


/*
 * SSE stuff
 */

#ifdef HANDMADE_MATH__USE_SSE
COVERAGE(HMM_LinearCombineSSE, 1)
HMM_INLINE __m128 HMM_PREFIX(LinearCombineSSE)(__m128 Left, HMM_Mat4 Right)
{
    ASSERT_COVERED(HMM_LinearCombineSSE);

    __m128 Result;
    Result = _mm_mul_ps(_mm_shuffle_ps(Left, Left, 0x00), Right.Columns[0]);
    Result = _mm_add_ps(Result, _mm_mul_ps(_mm_shuffle_ps(Left, Left, 0x55), Right.Columns[1]));
    Result = _mm_add_ps(Result, _mm_mul_ps(_mm_shuffle_ps(Left, Left, 0xaa), Right.Columns[2]));
    Result = _mm_add_ps(Result, _mm_mul_ps(_mm_shuffle_ps(Left, Left, 0xff), Right.Columns[3]));

    return (Result);
}
#endif


/*
 * Matrix functions
 */

COVERAGE(HMM_M4, 1)
HMM_INLINE HMM_Mat4 HMM_PREFIX(M4)(void)
{
    ASSERT_COVERED(HMM_M4);

    HMM_Mat4 Result = {0};

    return (Result);
}

COVERAGE(HMM_M4d, 1)
HMM_INLINE HMM_Mat4 HMM_PREFIX(M4d)(float Diagonal)
{
    ASSERT_COVERED(HMM_M4d);

    HMM_Mat4 Result = HMM_PREFIX(M4)();

    Result.Elements[0][0] = Diagonal;
    Result.Elements[1][1] = Diagonal;
    Result.Elements[2][2] = Diagonal;
    Result.Elements[3][3] = Diagonal;

    return (Result);
}

COVERAGE(HMM_Transpose, 1)
HMM_INLINE HMM_Mat4 HMM_PREFIX(Transpose)(HMM_Mat4 Matrix)
{
    ASSERT_COVERED(HMM_Transpose);

    HMM_Mat4 Result = Matrix;

#ifdef HANDMADE_MATH__USE_SSE
    _MM_TRANSPOSE4_PS(Result.Columns[0], Result.Columns[1], Result.Columns[2], Result.Columns[3]);
#else
    int Columns;
    for(Columns = 0; Columns < 4; ++Columns)
    {
        int Rows;
        for(Rows = 0; Rows < 4; ++Rows)
        {
            Result.Elements[Rows][Columns] = Matrix.Elements[Columns][Rows];
        }
    }
#endif


    return (Result);
}

COVERAGE(HMM_AddM4, 1)
HMM_INLINE HMM_Mat4 HMM_PREFIX(AddM4)(HMM_Mat4 Left, HMM_Mat4 Right)
{
    ASSERT_COVERED(HMM_AddM4);

    HMM_Mat4 Result;

#ifdef HANDMADE_MATH__USE_SSE
    Result.Columns[0] = _mm_add_ps(Left.Columns[0], Right.Columns[0]);
    Result.Columns[1] = _mm_add_ps(Left.Columns[1], Right.Columns[1]);
    Result.Columns[2] = _mm_add_ps(Left.Columns[2], Right.Columns[2]);
    Result.Columns[3] = _mm_add_ps(Left.Columns[3], Right.Columns[3]);
#else
     int Columns;
    for(Columns = 0; Columns < 4; ++Columns)
    {
        int Rows;
        for(Rows = 0; Rows < 4; ++Rows)
        {
            Result.Elements[Columns][Rows] = Left.Elements[Columns][Rows] + Right.Elements[Columns][Rows];
        }
    }
#endif

   
    return (Result);
}

COVERAGE(HMM_SubM4, 1)
HMM_INLINE HMM_Mat4 HMM_PREFIX(SubM4)(HMM_Mat4 Left, HMM_Mat4 Right)
{
    ASSERT_COVERED(HMM_SubM4);

    HMM_Mat4 Result;

#ifdef HANDMADE_MATH__USE_SSE
    Result.Columns[0] = _mm_sub_ps(Left.Columns[0], Right.Columns[0]);
    Result.Columns[1] = _mm_sub_ps(Left.Columns[1], Right.Columns[1]);
    Result.Columns[2] = _mm_sub_ps(Left.Columns[2], Right.Columns[2]);
    Result.Columns[3] = _mm_sub_ps(Left.Columns[3], Right.Columns[3]);
#else
    int Columns;
    for(Columns = 0; Columns < 4; ++Columns)
    {
        int Rows;
        for(Rows = 0; Rows < 4; ++Rows)
        {
            Result.Elements[Columns][Rows] = Left.Elements[Columns][Rows] - Right.Elements[Columns][Rows];
        }
    }
#endif
 
    return (Result);
}

COVERAGE(HMM_MulM4, 1)
HMM_INLINE HMM_Mat4 HMM_PREFIX(MulM4)(HMM_Mat4 Left, HMM_Mat4 Right)
{
    ASSERT_COVERED(HMM_MulM4);

    HMM_Mat4 Result;

#ifdef HANDMADE_MATH__USE_SSE
    Result.Columns[0] = HMM_PREFIX(LinearCombineSSE)(Right.Columns[0], Left);
    Result.Columns[1] = HMM_PREFIX(LinearCombineSSE)(Right.Columns[1], Left);
    Result.Columns[2] = HMM_PREFIX(LinearCombineSSE)(Right.Columns[2], Left);
    Result.Columns[3] = HMM_PREFIX(LinearCombineSSE)(Right.Columns[3], Left);
#else
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
#endif

    return (Result);
}


COVERAGE(HMM_MulM4f, 1)
HMM_INLINE HMM_Mat4 HMM_PREFIX(MulM4f)(HMM_Mat4 Matrix, float Scalar)
{
    ASSERT_COVERED(HMM_MulM4f);

    HMM_Mat4 Result;

#ifdef HANDMADE_MATH__USE_SSE
    __m128 SSEScalar = _mm_set1_ps(Scalar);
    Result.Columns[0] = _mm_mul_ps(Matrix.Columns[0], SSEScalar);
    Result.Columns[1] = _mm_mul_ps(Matrix.Columns[1], SSEScalar);
    Result.Columns[2] = _mm_mul_ps(Matrix.Columns[2], SSEScalar);
    Result.Columns[3] = _mm_mul_ps(Matrix.Columns[3], SSEScalar);
#else
    int Columns;
    for(Columns = 0; Columns < 4; ++Columns)
    {
        int Rows;
        for(Rows = 0; Rows < 4; ++Rows)
        {
            Result.Elements[Columns][Rows] = Matrix.Elements[Columns][Rows] * Scalar;
        }
    }
#endif

    return (Result);
}

COVERAGE(HMM_MulM4ByV4, 1)
HMM_INLINE HMM_Vec4 HMM_PREFIX(MulM4ByV4)(HMM_Mat4 Matrix, HMM_Vec4 Vector)
{
    ASSERT_COVERED(HMM_MulM4ByV4);

    HMM_Vec4 Result;

#ifdef HANDMADE_MATH__USE_SSE
    Result.InternalElementsSSE = HMM_PREFIX(LinearCombineSSE)(Vector.InternalElementsSSE, Matrix);
#else
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
#endif

    return (Result);
}


COVERAGE(HMM_DivM4f, 1)
HMM_INLINE HMM_Mat4 HMM_PREFIX(DivM4f)(HMM_Mat4 Matrix, float Scalar)
{
    ASSERT_COVERED(HMM_DivM4f);

    HMM_Mat4 Result;

#ifdef HANDMADE_MATH__USE_SSE
    __m128 SSEScalar = _mm_set1_ps(Scalar);
    Result.Columns[0] = _mm_div_ps(Matrix.Columns[0], SSEScalar);
    Result.Columns[1] = _mm_div_ps(Matrix.Columns[1], SSEScalar);
    Result.Columns[2] = _mm_div_ps(Matrix.Columns[2], SSEScalar);
    Result.Columns[3] = _mm_div_ps(Matrix.Columns[3], SSEScalar);
#else
    int Columns;
    for(Columns = 0; Columns < 4; ++Columns)
    {
        int Rows;
        for(Rows = 0; Rows < 4; ++Rows)
        {
            Result.Elements[Columns][Rows] = Matrix.Elements[Columns][Rows] / Scalar;
        }
    }
#endif

    return (Result);
}

/*
 * Common graphics transformations
 */

COVERAGE(HMM_Orthographic, 1)
HMM_INLINE HMM_Mat4 HMM_PREFIX(Orthographic)(float Left, float Right, float Bottom, float Top, float Near, float Far)
{
    ASSERT_COVERED(HMM_Orthographic);

    HMM_Mat4 Result = HMM_PREFIX(M4)();

    Result.Elements[0][0] = 2.0f / (Right - Left);
    Result.Elements[1][1] = 2.0f / (Top - Bottom);
    Result.Elements[2][2] = 2.0f / (Near - Far);
    Result.Elements[3][3] = 1.0f;

    Result.Elements[3][0] = (Left + Right) / (Left - Right);
    Result.Elements[3][1] = (Bottom + Top) / (Bottom - Top);
    Result.Elements[3][2] = (Far + Near) / (Near - Far);

    return (Result);
}

COVERAGE(HMM_Perspective, 1)
HMM_INLINE HMM_Mat4 HMM_PREFIX(Perspective)(float FOV, float AspectRatio, float Near, float Far)
{
    ASSERT_COVERED(HMM_Perspective);

    HMM_Mat4 Result = HMM_PREFIX(M4)();

    // See https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/gluPerspective.xml

    float Cotangent = 1.0f / HMM_PREFIX(TanF)(FOV / 2.0);
    
    Result.Elements[0][0] = Cotangent / AspectRatio;
    Result.Elements[1][1] = Cotangent;
    Result.Elements[2][3] = -1.0f;
    Result.Elements[2][2] = (Near + Far) / (Near - Far);
    Result.Elements[3][2] = (2.0f * Near * Far) / (Near - Far);
    Result.Elements[3][3] = 0.0f;

    return (Result);
}

COVERAGE(HMM_Translate, 1)
HMM_INLINE HMM_Mat4 HMM_PREFIX(Translate)(HMM_Vec3 Translation)
{
    ASSERT_COVERED(HMM_Translate);

    HMM_Mat4 Result = HMM_PREFIX(M4d)(1.0f);

    Result.Elements[3][0] = Translation.X;
    Result.Elements[3][1] = Translation.Y;
    Result.Elements[3][2] = Translation.Z;

    return (Result);
}

COVERAGE(HMM_Rotate, 1)
HMM_INLINE HMM_Mat4 HMM_PREFIX(Rotate)(float Angle, HMM_Vec3 Axis)
{
    ASSERT_COVERED(HMM_Rotate);

    HMM_Mat4 Result = HMM_PREFIX(M4d)(1.0f);

    Axis = HMM_PREFIX(NormV3)(Axis);

    float SinTheta = HMM_PREFIX(SinF)(Angle);
    float CosTheta = HMM_PREFIX(CosF)(Angle);
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



COVERAGE(HMM_Scale, 1)
HMM_INLINE HMM_Mat4 HMM_PREFIX(Scale)(HMM_Vec3 Scale)
{
    ASSERT_COVERED(HMM_Scale);

    HMM_Mat4 Result = HMM_PREFIX(M4d)(1.0f);

    Result.Elements[0][0] = Scale.X;
    Result.Elements[1][1] = Scale.Y;
    Result.Elements[2][2] = Scale.Z;

    return (Result);
}

COVERAGE(HMM_LookAt, 1)
HMM_INLINE HMM_Mat4 HMM_PREFIX(LookAt)(HMM_Vec3 Eye, HMM_Vec3 Center, HMM_Vec3 Up)
{
    ASSERT_COVERED(HMM_LookAt);

    HMM_Mat4 Result;

    HMM_Vec3 F = HMM_PREFIX(NormV3)(HMM_PREFIX(SubV3)(Center, Eye));
    HMM_Vec3 S = HMM_PREFIX(NormV3)(HMM_PREFIX(Cross)(F, Up));
    HMM_Vec3 U = HMM_PREFIX(Cross)(S, F);

    Result.Elements[0][0] = S.X;
    Result.Elements[0][1] = U.X;
    Result.Elements[0][2] = -F.X;
    Result.Elements[0][3] = 0.0f;

    Result.Elements[1][0] = S.Y;
    Result.Elements[1][1] = U.Y;
    Result.Elements[1][2] = -F.Y;
    Result.Elements[1][3] = 0.0f;

    Result.Elements[2][0] = S.Z;
    Result.Elements[2][1] = U.Z;
    Result.Elements[2][2] = -F.Z;
    Result.Elements[2][3] = 0.0f;

    Result.Elements[3][0] = -HMM_PREFIX(DotV3)(S, Eye);
    Result.Elements[3][1] = -HMM_PREFIX(DotV3)(U, Eye);
    Result.Elements[3][2] = HMM_PREFIX(DotV3)(F, Eye);
    Result.Elements[3][3] = 1.0f;

    return (Result);
}

/*
 * Quaternion operations
 */

COVERAGE(HMM_Q, 1)
HMM_INLINE HMM_Quat HMM_PREFIX(Q)(float X, float Y, float Z, float W)
{
    ASSERT_COVERED(HMM_Q);

    HMM_Quat Result;

#ifdef HANDMADE_MATH__USE_SSE
    Result.InternalElementsSSE = _mm_setr_ps(X, Y, Z, W);
#else
    Result.X = X;
    Result.Y = Y;
    Result.Z = Z;
    Result.W = W;
#endif

    return (Result);
}

COVERAGE(HMM_QV4, 1)
HMM_INLINE HMM_Quat HMM_PREFIX(QV4)(HMM_Vec4 Vector)
{
    ASSERT_COVERED(HMM_QV4);

    HMM_Quat Result;

#ifdef HANDMADE_MATH__USE_SSE
    Result.InternalElementsSSE = Vector.InternalElementsSSE;
#else
    Result.X = Vector.X;
    Result.Y = Vector.Y;
    Result.Z = Vector.Z;
    Result.W = Vector.W;
#endif

    return (Result);
}

COVERAGE(HMM_AddQ, 1)
HMM_INLINE HMM_Quat HMM_PREFIX(AddQ)(HMM_Quat Left, HMM_Quat Right)
{
    ASSERT_COVERED(HMM_AddQ);

    HMM_Quat Result;

#ifdef HANDMADE_MATH__USE_SSE
    Result.InternalElementsSSE = _mm_add_ps(Left.InternalElementsSSE, Right.InternalElementsSSE);
#else

    Result.X = Left.X + Right.X;
    Result.Y = Left.Y + Right.Y;
    Result.Z = Left.Z + Right.Z;
    Result.W = Left.W + Right.W;
#endif

    return (Result);
}

COVERAGE(HMM_SubQ, 1)
HMM_INLINE HMM_Quat HMM_PREFIX(SubQ)(HMM_Quat Left, HMM_Quat Right)
{
    ASSERT_COVERED(HMM_SubQ);

    HMM_Quat Result;

#ifdef HANDMADE_MATH__USE_SSE
    Result.InternalElementsSSE = _mm_sub_ps(Left.InternalElementsSSE, Right.InternalElementsSSE);
#else

    Result.X = Left.X - Right.X;
    Result.Y = Left.Y - Right.Y;
    Result.Z = Left.Z - Right.Z;
    Result.W = Left.W - Right.W;
#endif

    return (Result);
}

COVERAGE(HMM_MulQ, 1)
HMM_INLINE HMM_Quat HMM_PREFIX(MulQ)(HMM_Quat Left, HMM_Quat Right)
{
    ASSERT_COVERED(HMM_MulQ);

    HMM_Quat Result;

#ifdef HANDMADE_MATH__USE_SSE
    __m128 SSEResultOne = _mm_xor_ps(_mm_shuffle_ps(Left.InternalElementsSSE, Left.InternalElementsSSE, _MM_SHUFFLE(0, 0, 0, 0)), _mm_setr_ps(0.f, -0.f, 0.f, -0.f));
    __m128 SSEResultTwo = _mm_shuffle_ps(Right.InternalElementsSSE, Right.InternalElementsSSE, _MM_SHUFFLE(0, 1, 2, 3));
    __m128 SSEResultThree = _mm_mul_ps(SSEResultTwo, SSEResultOne);

    SSEResultOne = _mm_xor_ps(_mm_shuffle_ps(Left.InternalElementsSSE, Left.InternalElementsSSE, _MM_SHUFFLE(1, 1, 1, 1)) , _mm_setr_ps(0.f, 0.f, -0.f, -0.f));
    SSEResultTwo = _mm_shuffle_ps(Right.InternalElementsSSE, Right.InternalElementsSSE, _MM_SHUFFLE(1, 0, 3, 2));
    SSEResultThree = _mm_add_ps(SSEResultThree, _mm_mul_ps(SSEResultTwo, SSEResultOne));

    SSEResultOne = _mm_xor_ps(_mm_shuffle_ps(Left.InternalElementsSSE, Left.InternalElementsSSE, _MM_SHUFFLE(2, 2, 2, 2)), _mm_setr_ps(-0.f, 0.f, 0.f, -0.f));
    SSEResultTwo = _mm_shuffle_ps(Right.InternalElementsSSE, Right.InternalElementsSSE, _MM_SHUFFLE(2, 3, 0, 1));
    SSEResultThree = _mm_add_ps(SSEResultThree, _mm_mul_ps(SSEResultTwo, SSEResultOne));

    SSEResultOne = _mm_shuffle_ps(Left.InternalElementsSSE, Left.InternalElementsSSE, _MM_SHUFFLE(3, 3, 3, 3));
    SSEResultTwo = _mm_shuffle_ps(Right.InternalElementsSSE, Right.InternalElementsSSE, _MM_SHUFFLE(3, 2, 1, 0));
    Result.InternalElementsSSE = _mm_add_ps(SSEResultThree, _mm_mul_ps(SSEResultTwo, SSEResultOne));
#else
    Result.X = (Left.X * Right.W) + (Left.Y * Right.Z) - (Left.Z * Right.Y) + (Left.W * Right.X);
    Result.Y = (-Left.X * Right.Z) + (Left.Y * Right.W) + (Left.Z * Right.X) + (Left.W * Right.Y);
    Result.Z = (Left.X * Right.Y) - (Left.Y * Right.X) + (Left.Z * Right.W) + (Left.W * Right.Z);
    Result.W = (-Left.X * Right.X) - (Left.Y * Right.Y) - (Left.Z * Right.Z) + (Left.W * Right.W);
#endif

    return (Result);
}

COVERAGE(HMM_MulQF, 1)
HMM_INLINE HMM_Quat HMM_PREFIX(MulQF)(HMM_Quat Left, float Multiplicative)
{
    ASSERT_COVERED(HMM_MulQF);

    HMM_Quat Result;

#ifdef HANDMADE_MATH__USE_SSE
    __m128 Scalar = _mm_set1_ps(Multiplicative);
    Result.InternalElementsSSE = _mm_mul_ps(Left.InternalElementsSSE, Scalar);
#else
    Result.X = Left.X * Multiplicative;
    Result.Y = Left.Y * Multiplicative;
    Result.Z = Left.Z * Multiplicative;
    Result.W = Left.W * Multiplicative;
#endif

    return (Result);
}

COVERAGE(HMM_DivQF, 1)
HMM_INLINE HMM_Quat HMM_PREFIX(DivQF)(HMM_Quat Left, float Divnd)
{
    ASSERT_COVERED(HMM_DivQF);

    HMM_Quat Result;

#ifdef HANDMADE_MATH__USE_SSE
    __m128 Scalar = _mm_set1_ps(Divnd);
    Result.InternalElementsSSE = _mm_div_ps(Left.InternalElementsSSE, Scalar);
#else
    Result.X = Left.X / Divnd;
    Result.Y = Left.Y / Divnd;
    Result.Z = Left.Z / Divnd;
    Result.W = Left.W / Divnd;
#endif

    return (Result);
}

COVERAGE(HMM_DotQ, 1)
HMM_INLINE float HMM_PREFIX(DotQ)(HMM_Quat Left, HMM_Quat Right)
{
    ASSERT_COVERED(HMM_DotQ);

    float Result;

#ifdef HANDMADE_MATH__USE_SSE
    __m128 SSEResultOne = _mm_mul_ps(Left.InternalElementsSSE, Right.InternalElementsSSE);
    __m128 SSEResultTwo = _mm_shuffle_ps(SSEResultOne, SSEResultOne, _MM_SHUFFLE(2, 3, 0, 1));
    SSEResultOne = _mm_add_ps(SSEResultOne, SSEResultTwo);
    SSEResultTwo = _mm_shuffle_ps(SSEResultOne, SSEResultOne, _MM_SHUFFLE(0, 1, 2, 3));
    SSEResultOne = _mm_add_ps(SSEResultOne, SSEResultTwo);
    _mm_store_ss(&Result, SSEResultOne);
#else
    Result = (Left.X * Right.X) + (Left.Y * Right.Y) + (Left.Z * Right.Z) + (Left.W * Right.W);
#endif

    return (Result);
}


COVERAGE(HMM_InvQ, 1)
HMM_INLINE HMM_Quat HMM_PREFIX(InvQ)(HMM_Quat Left)
{
    ASSERT_COVERED(HMM_InvQ);
    
    HMM_Quat Result;

    Result.X = -Left.X;
    Result.Y = -Left.Y;
    Result.Z = -Left.Z;
    Result.W = Left.W;

    Result = HMM_PREFIX(DivQF)(Result, (HMM_PREFIX(DotQ)(Left, Left)));

    return (Result);
}


COVERAGE(HMM_NormQ, 1)
HMM_INLINE HMM_Quat HMM_PREFIX(NormQ)(HMM_Quat Left)
{
    ASSERT_COVERED(HMM_NormQ);

    HMM_Quat Result;

    float Len = HMM_PREFIX(SqrtF)(HMM_PREFIX(DotQ)(Left, Left));
    Result = HMM_PREFIX(DivQF)(Left, Len);

    return (Result);
}

COVERAGE(HMM_NLerp, 1)
HMM_INLINE HMM_Quat HMM_PREFIX(NLerp)(HMM_Quat Left, float Time, HMM_Quat Right)
{
    ASSERT_COVERED(HMM_NLerp);

    HMM_Quat Result;

#ifdef HANDMADE_MATH__USE_SSE
    __m128 ScalarLeft = _mm_set1_ps(1.0f - Time);
    __m128 ScalarRight = _mm_set1_ps(Time);
    __m128 SSEResultOne = _mm_mul_ps(Left.InternalElementsSSE, ScalarLeft);
    __m128 SSEResultTwo = _mm_mul_ps(Right.InternalElementsSSE, ScalarRight);
    Result.InternalElementsSSE = _mm_add_ps(SSEResultOne, SSEResultTwo);
#else
    Result.X = HMM_PREFIX(Lerp)(Left.X, Time, Right.X);
    Result.Y = HMM_PREFIX(Lerp)(Left.Y, Time, Right.Y);
    Result.Z = HMM_PREFIX(Lerp)(Left.Z, Time, Right.Z);
    Result.W = HMM_PREFIX(Lerp)(Left.W, Time, Right.W);
#endif
    Result = HMM_PREFIX(NormQ)(Result);

    return (Result);
}

COVERAGE(HMM_Slerp, 1)
HMM_INLINE HMM_Quat HMM_PREFIX(Slerp)(HMM_Quat Left, float Time, HMM_Quat Right)
{
    ASSERT_COVERED(HMM_Slerp);

    HMM_Quat Result;
    HMM_Quat QLeft;
    HMM_Quat QRight;

    float Cos_Theta = HMM_PREFIX(DotQ)(Left, Right);
    float Angle = HMM_PREFIX(ACosF)(Cos_Theta);

    float S1 = HMM_PREFIX(SinF)((1.0f - Time) * Angle);
    float S2 = HMM_PREFIX(SinF)(Time * Angle);
    float Is = 1.0f / HMM_PREFIX(SinF)(Angle);

    QLeft = HMM_PREFIX(MulQF)(Left, S1);
    QRight = HMM_PREFIX(MulQF)(Right, S2);

    Result = HMM_PREFIX(AddQ)(QLeft, QRight);
    Result = HMM_PREFIX(MulQF)(Result, Is);

    return (Result);
}

COVERAGE(HMM_QToM4, 1)
HMM_INLINE HMM_Mat4 HMM_PREFIX(QToM4)(HMM_Quat Left)
{
    ASSERT_COVERED(HMM_QToM4);

    HMM_Mat4 Result;

    HMM_Quat NormalizedQ = HMM_PREFIX(NormQ)(Left);

    float XX, YY, ZZ,
          XY, XZ, YZ,
          WX, WY, WZ;

    XX = NormalizedQ.X * NormalizedQ.X;
    YY = NormalizedQ.Y * NormalizedQ.Y;
    ZZ = NormalizedQ.Z * NormalizedQ.Z;
    XY = NormalizedQ.X * NormalizedQ.Y;
    XZ = NormalizedQ.X * NormalizedQ.Z;
    YZ = NormalizedQ.Y * NormalizedQ.Z;
    WX = NormalizedQ.W * NormalizedQ.X;
    WY = NormalizedQ.W * NormalizedQ.Y;
    WZ = NormalizedQ.W * NormalizedQ.Z;

    Result.Elements[0][0] = 1.0f - 2.0f * (YY + ZZ);
    Result.Elements[0][1] = 2.0f * (XY + WZ);
    Result.Elements[0][2] = 2.0f * (XZ - WY);
    Result.Elements[0][3] = 0.0f;

    Result.Elements[1][0] = 2.0f * (XY - WZ);
    Result.Elements[1][1] = 1.0f - 2.0f * (XX + ZZ);
    Result.Elements[1][2] = 2.0f * (YZ + WX);
    Result.Elements[1][3] = 0.0f;

    Result.Elements[2][0] = 2.0f * (XZ + WY);
    Result.Elements[2][1] = 2.0f * (YZ - WX);
    Result.Elements[2][2] = 1.0f - 2.0f * (XX + YY);
    Result.Elements[2][3] = 0.0f;

    Result.Elements[3][0] = 0.0f;
    Result.Elements[3][1] = 0.0f;
    Result.Elements[3][2] = 0.0f;
    Result.Elements[3][3] = 1.0f;

    return (Result);
}

// This method taken from Mike Day at Insomniac Games.
// https://d3cw3dd2w32x2b.cloudfront.net/wp-content/uploads/2015/01/matrix-to-quat.pdf
//
// Note that as mentioned at the top of the paper, the paper assumes the matrix
// would be *post*-multiplied to a vector to rotate it, meaning the matrix is
// the transpose of what we're dealing with. But, because our matrices are
// stored in column-major order, the indices *appear* to match the paper.
//
// For example, m12 in the paper is row 1, column 2. We need to transpose it to
// row 2, column 1. But, because the column comes first when referencing
// elements, it looks like M.Elements[1][2].
//
// Don't be confused! Or if you must be confused, at least trust this
// comment. :)
COVERAGE(HMM_M4ToQ, 4)
HMM_INLINE HMM_Quat HMM_PREFIX(M4ToQ)(HMM_Mat4 M)
{
    float T;
    HMM_Quat Q;

    if (M.Elements[2][2] < 0.0f) {
        if (M.Elements[0][0] > M.Elements[1][1]) {
            ASSERT_COVERED(HMM_M4ToQ);

            T = 1 + M.Elements[0][0] - M.Elements[1][1] - M.Elements[2][2];
            Q = HMM_PREFIX(Q)(
                T,
                M.Elements[0][1] + M.Elements[1][0],
                M.Elements[2][0] + M.Elements[0][2],
                M.Elements[1][2] - M.Elements[2][1]
            );
        } else {
            ASSERT_COVERED(HMM_M4ToQ);

            T = 1 - M.Elements[0][0] + M.Elements[1][1] - M.Elements[2][2];
            Q = HMM_PREFIX(Q)(
                M.Elements[0][1] + M.Elements[1][0],
                T,
                M.Elements[1][2] + M.Elements[2][1],
                M.Elements[2][0] - M.Elements[0][2]
            );
        }
    } else {
        if (M.Elements[0][0] < -M.Elements[1][1]) {
            ASSERT_COVERED(HMM_M4ToQ);

            T = 1 - M.Elements[0][0] - M.Elements[1][1] + M.Elements[2][2];
            Q = HMM_PREFIX(Q)(
                M.Elements[2][0] + M.Elements[0][2],
                M.Elements[1][2] + M.Elements[2][1],
                T,
                M.Elements[0][1] - M.Elements[1][0]
            );
        } else {
            ASSERT_COVERED(HMM_M4ToQ);

            T = 1 + M.Elements[0][0] + M.Elements[1][1] + M.Elements[2][2];
            Q = HMM_PREFIX(Q)(
                M.Elements[1][2] - M.Elements[2][1],
                M.Elements[2][0] - M.Elements[0][2],
                M.Elements[0][1] - M.Elements[1][0],
                T
            );
        }
    }

    Q = HMM_PREFIX(MulQF)(Q, 0.5f / HMM_PREFIX(SqrtF)(T));

    return Q;
}

COVERAGE(HMM_QFromAxisAngle, 1)
HMM_INLINE HMM_Quat HMM_PREFIX(QFromAxisAngle)(HMM_Vec3 Axis, float AngleOfRotation)
{
    ASSERT_COVERED(HMM_QFromAxisAngle);

    HMM_Quat Result;

    HMM_Vec3 AxisNormalized = HMM_PREFIX(NormV3)(Axis);
    float SineOfRotation = HMM_PREFIX(SinF)(AngleOfRotation / 2.0f);

    Result.XYZ = HMM_PREFIX(MulV3F)(AxisNormalized, SineOfRotation);
    Result.W = HMM_PREFIX(CosF)(AngleOfRotation / 2.0f);

    return (Result);
}

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

COVERAGE(HMM_LenV2CPP, 1)
HMM_INLINE float HMM_PREFIX(Len)(HMM_Vec2 A)
{
    ASSERT_COVERED(HMM_LenV2CPP);

    float Result = HMM_PREFIX(LenV2)(A);
    return (Result);
}

COVERAGE(HMM_LenV3CPP, 1)
HMM_INLINE float HMM_PREFIX(Len)(HMM_Vec3 A)
{
    ASSERT_COVERED(HMM_LenV3CPP);

    float Result = HMM_PREFIX(LenV3)(A);

    return (Result);
}

COVERAGE(HMM_LenV4CPP, 1)
HMM_INLINE float HMM_PREFIX(Len)(HMM_Vec4 A)
{
    ASSERT_COVERED(HMM_LenV4CPP);

    float Result = HMM_PREFIX(LenV4)(A);

    return (Result);
}

COVERAGE(HMM_LenSqrV2CPP, 1)
HMM_INLINE float HMM_PREFIX(LenSqr)(HMM_Vec2 A)
{
    ASSERT_COVERED(HMM_LenSqrV2CPP);

    float Result = HMM_PREFIX(LenSqrV2)(A);

    return (Result);
}

COVERAGE(HMM_LenSqrV3CPP, 1)
HMM_INLINE float HMM_PREFIX(LenSqr)(HMM_Vec3 A)
{
    ASSERT_COVERED(HMM_LenSqrV3CPP);

    float Result = HMM_PREFIX(LenSqrV3)(A);

    return (Result);
}

COVERAGE(HMM_LenSqrV4CPP, 1)
HMM_INLINE float HMM_PREFIX(LenSqr)(HMM_Vec4 A)
{
    ASSERT_COVERED(HMM_LenSqrV4CPP);

    float Result = HMM_PREFIX(LenSqrV4)(A);

    return (Result);
}

COVERAGE(HMM_NormV2CPP, 1)
HMM_INLINE HMM_Vec2 HMM_PREFIX(Norm)(HMM_Vec2 A)
{
    ASSERT_COVERED(HMM_NormV2CPP);

    HMM_Vec2 Result = HMM_PREFIX(NormV2)(A);

    return (Result);
}

COVERAGE(HMM_NormV3CPP, 1)
HMM_INLINE HMM_Vec3 HMM_PREFIX(Norm)(HMM_Vec3 A)
{
    ASSERT_COVERED(HMM_NormV3CPP);

    HMM_Vec3 Result = HMM_PREFIX(NormV3)(A);

    return (Result);
}

COVERAGE(HMM_NormV4CPP, 1)
HMM_INLINE HMM_Vec4 HMM_PREFIX(Norm)(HMM_Vec4 A)
{
    ASSERT_COVERED(HMM_NormV4CPP);

    HMM_Vec4 Result = HMM_PREFIX(NormV4)(A);

    return (Result);
}

COVERAGE(HMM_FastNormV2CPP, 1)
HMM_INLINE HMM_Vec2 HMM_PREFIX(FastNorm)(HMM_Vec2 A)
{
    ASSERT_COVERED(HMM_FastNormV2CPP);

    HMM_Vec2 Result = HMM_PREFIX(FastNormV2)(A);

    return (Result);
}

COVERAGE(HMM_FastNormV3CPP, 1)
HMM_INLINE HMM_Vec3 HMM_PREFIX(FastNorm)(HMM_Vec3 A)
{
    ASSERT_COVERED(HMM_FastNormV3CPP);

    HMM_Vec3 Result = HMM_PREFIX(FastNormV3)(A);

    return (Result);
}

COVERAGE(HMM_FastNormV4CPP, 1)
HMM_INLINE HMM_Vec4 HMM_PREFIX(FastNorm)(HMM_Vec4 A)
{
    ASSERT_COVERED(HMM_FastNormV4CPP);

    HMM_Vec4 Result = HMM_PREFIX(FastNormV4)(A);

    return (Result);
}

COVERAGE(HMM_NormQCPP, 1)
HMM_INLINE HMM_Quat HMM_PREFIX(Norm)(HMM_Quat A)
{
    ASSERT_COVERED(HMM_NormQCPP);

    HMM_Quat Result = HMM_PREFIX(NormQ)(A);

    return (Result);
}

COVERAGE(HMM_DotV2CPP, 1)
HMM_INLINE float HMM_PREFIX(Dot)(HMM_Vec2 Left, HMM_Vec2 VecTwo)
{
    ASSERT_COVERED(HMM_DotV2CPP);

    float Result = HMM_PREFIX(DotV2)(Left, VecTwo);

    return (Result);
}

COVERAGE(HMM_DotV3CPP, 1)
HMM_INLINE float HMM_PREFIX(Dot)(HMM_Vec3 Left, HMM_Vec3 VecTwo)
{
    ASSERT_COVERED(HMM_DotV3CPP);

    float Result = HMM_PREFIX(DotV3)(Left, VecTwo);

    return (Result);
}

COVERAGE(HMM_DotV4CPP, 1)
HMM_INLINE float HMM_PREFIX(Dot)(HMM_Vec4 Left, HMM_Vec4 VecTwo)
{
    ASSERT_COVERED(HMM_DotV4CPP);

    float Result = HMM_PREFIX(DotV4)(Left, VecTwo);

    return (Result);
}

COVERAGE(HMM_DotQCPP, 1)
HMM_INLINE float HMM_PREFIX(Dot)(HMM_Quat QuatOne, HMM_Quat QuatTwo)
{
    ASSERT_COVERED(HMM_DotQCPP);

    float Result = HMM_PREFIX(DotQ)(QuatOne, QuatTwo);

    return (Result);
}

COVERAGE(HMM_AddV2CPP, 1)
HMM_INLINE HMM_Vec2 HMM_PREFIX(Add)(HMM_Vec2 Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_AddV2CPP);

    HMM_Vec2 Result = HMM_PREFIX(AddV2)(Left, Right);

    return (Result);
}

COVERAGE(HMM_AddV3CPP, 1)
HMM_INLINE HMM_Vec3 HMM_PREFIX(Add)(HMM_Vec3 Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_AddV3CPP);

    HMM_Vec3 Result = HMM_PREFIX(AddV3)(Left, Right);

    return (Result);
}

COVERAGE(HMM_AddV4CPP, 1)
HMM_INLINE HMM_Vec4 HMM_PREFIX(Add)(HMM_Vec4 Left, HMM_Vec4 Right)
{
    ASSERT_COVERED(HMM_AddV4CPP);

    HMM_Vec4 Result = HMM_PREFIX(AddV4)(Left, Right);

    return (Result);
}

COVERAGE(HMM_AddM4CPP, 1)
HMM_INLINE HMM_Mat4 HMM_PREFIX(Add)(HMM_Mat4 Left, HMM_Mat4 Right)
{
    ASSERT_COVERED(HMM_AddM4CPP);

    HMM_Mat4 Result = HMM_PREFIX(AddM4)(Left, Right);

    return (Result);
}

COVERAGE(HMM_AddQCPP, 1)
HMM_INLINE HMM_Quat HMM_PREFIX(Add)(HMM_Quat Left, HMM_Quat Right)
{
    ASSERT_COVERED(HMM_AddQCPP);

    HMM_Quat Result = HMM_PREFIX(AddQ)(Left, Right);

    return (Result);
}

COVERAGE(HMM_SubV2CPP, 1)
HMM_INLINE HMM_Vec2 HMM_PREFIX(Sub)(HMM_Vec2 Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_SubV2CPP);

    HMM_Vec2 Result = HMM_PREFIX(SubV2)(Left, Right);

    return (Result);
}

COVERAGE(HMM_SubV3CPP, 1)
HMM_INLINE HMM_Vec3 HMM_PREFIX(Sub)(HMM_Vec3 Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_SubV3CPP);

    HMM_Vec3 Result = HMM_PREFIX(SubV3)(Left, Right);

    return (Result);
}

COVERAGE(HMM_SubV4CPP, 1)
HMM_INLINE HMM_Vec4 HMM_PREFIX(Sub)(HMM_Vec4 Left, HMM_Vec4 Right)
{
    ASSERT_COVERED(HMM_SubV4CPP);

    HMM_Vec4 Result = HMM_PREFIX(SubV4)(Left, Right);

    return (Result);
}

COVERAGE(HMM_SubM4CPP, 1)
HMM_INLINE HMM_Mat4 HMM_PREFIX(Sub)(HMM_Mat4 Left, HMM_Mat4 Right)
{
    ASSERT_COVERED(HMM_SubM4CPP);

    HMM_Mat4 Result = HMM_PREFIX(SubM4)(Left, Right);

    return (Result);
}

COVERAGE(HMM_SubQCPP, 1)
HMM_INLINE HMM_Quat HMM_PREFIX(Sub)(HMM_Quat Left, HMM_Quat Right)
{
    ASSERT_COVERED(HMM_SubQCPP);

    HMM_Quat Result = HMM_PREFIX(SubQ)(Left, Right);

    return (Result);
}

COVERAGE(HMM_MulV2CPP, 1)
HMM_INLINE HMM_Vec2 HMM_PREFIX(Mul)(HMM_Vec2 Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_MulV2CPP);

    HMM_Vec2 Result = HMM_PREFIX(MulV2)(Left, Right);

    return (Result);
}

COVERAGE(HMM_MulV2FCPP, 1)
HMM_INLINE HMM_Vec2 HMM_PREFIX(Mul)(HMM_Vec2 Left, float Right)
{
    ASSERT_COVERED(HMM_MulV2FCPP);

    HMM_Vec2 Result = HMM_PREFIX(MulV2F)(Left, Right);

    return (Result);
}

COVERAGE(HMM_MulV3CPP, 1)
HMM_INLINE HMM_Vec3 HMM_PREFIX(Mul)(HMM_Vec3 Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_MulV3CPP);

    HMM_Vec3 Result = HMM_PREFIX(MulV3)(Left, Right);

    return (Result);
}

COVERAGE(HMM_MulV3FCPP, 1)
HMM_INLINE HMM_Vec3 HMM_PREFIX(Mul)(HMM_Vec3 Left, float Right)
{
    ASSERT_COVERED(HMM_MulV3FCPP);

    HMM_Vec3 Result = HMM_PREFIX(MulV3F)(Left, Right);

    return (Result);
}

COVERAGE(HMM_MulV4CPP, 1)
HMM_INLINE HMM_Vec4 HMM_PREFIX(Mul)(HMM_Vec4 Left, HMM_Vec4 Right)
{
    ASSERT_COVERED(HMM_MulV4CPP);

    HMM_Vec4 Result = HMM_PREFIX(MulV4)(Left, Right);

    return (Result);
}

COVERAGE(HMM_MulV4FCPP, 1)
HMM_INLINE HMM_Vec4 HMM_PREFIX(Mul)(HMM_Vec4 Left, float Right)
{
    ASSERT_COVERED(HMM_MulV4FCPP);

    HMM_Vec4 Result = HMM_PREFIX(MulV4F)(Left, Right);

    return (Result);
}

COVERAGE(HMM_MulM4CPP, 1)
HMM_INLINE HMM_Mat4 HMM_PREFIX(Mul)(HMM_Mat4 Left, HMM_Mat4 Right)
{
    ASSERT_COVERED(HMM_MulM4CPP);

    HMM_Mat4 Result = HMM_PREFIX(MulM4)(Left, Right);

    return (Result);
}

COVERAGE(HMM_MulM4fCPP, 1)
HMM_INLINE HMM_Mat4 HMM_PREFIX(Mul)(HMM_Mat4 Left, float Right)
{
    ASSERT_COVERED(HMM_MulM4fCPP);

    HMM_Mat4 Result = HMM_PREFIX(MulM4f)(Left, Right);

    return (Result);
}

COVERAGE(HMM_MulM4ByV4CPP, 1)
HMM_INLINE HMM_Vec4 HMM_PREFIX(Mul)(HMM_Mat4 Matrix, HMM_Vec4 Vector)
{
    ASSERT_COVERED(HMM_MulM4ByV4CPP);

    HMM_Vec4 Result = HMM_PREFIX(MulM4ByV4)(Matrix, Vector);

    return (Result);
}

COVERAGE(HMM_MulQCPP, 1)
HMM_INLINE HMM_Quat HMM_PREFIX(Mul)(HMM_Quat Left, HMM_Quat Right)
{
    ASSERT_COVERED(HMM_MulQCPP);

    HMM_Quat Result = HMM_PREFIX(MulQ)(Left, Right);

    return (Result);
}

COVERAGE(HMM_MulQFCPP, 1)
HMM_INLINE HMM_Quat HMM_PREFIX(Mul)(HMM_Quat Left, float Right)
{
    ASSERT_COVERED(HMM_MulQFCPP);

    HMM_Quat Result = HMM_PREFIX(MulQF)(Left, Right);

    return (Result);
}

COVERAGE(HMM_DivV2CPP, 1)
HMM_INLINE HMM_Vec2 HMM_PREFIX(Div)(HMM_Vec2 Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_DivV2CPP);

    HMM_Vec2 Result = HMM_PREFIX(DivV2)(Left, Right);

    return (Result);
}

COVERAGE(HMM_DivV2FCPP, 1)
HMM_INLINE HMM_Vec2 HMM_PREFIX(Div)(HMM_Vec2 Left, float Right)
{
    ASSERT_COVERED(HMM_DivV2FCPP);

    HMM_Vec2 Result = HMM_PREFIX(DivV2F)(Left, Right);

    return (Result);
}

COVERAGE(HMM_DivV3CPP, 1)
HMM_INLINE HMM_Vec3 HMM_PREFIX(Div)(HMM_Vec3 Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_DivV3CPP);

    HMM_Vec3 Result = HMM_PREFIX(DivV3)(Left, Right);

    return (Result);
}

COVERAGE(HMM_DivV3FCPP, 1)
HMM_INLINE HMM_Vec3 HMM_PREFIX(Div)(HMM_Vec3 Left, float Right)
{
    ASSERT_COVERED(HMM_DivV3FCPP);

    HMM_Vec3 Result = HMM_PREFIX(DivV3F)(Left, Right);

    return (Result);
}

COVERAGE(HMM_DivV4CPP, 1)
HMM_INLINE HMM_Vec4 HMM_PREFIX(Div)(HMM_Vec4 Left, HMM_Vec4 Right)
{
    ASSERT_COVERED(HMM_DivV4CPP);

    HMM_Vec4 Result = HMM_PREFIX(DivV4)(Left, Right);

    return (Result);
}

COVERAGE(HMM_DivV4FCPP, 1)
HMM_INLINE HMM_Vec4 HMM_PREFIX(Div)(HMM_Vec4 Left, float Right)
{
    ASSERT_COVERED(HMM_DivV4FCPP);

    HMM_Vec4 Result = HMM_PREFIX(DivV4F)(Left, Right);

    return (Result);
}

COVERAGE(HMM_DivM4fCPP, 1)
HMM_INLINE HMM_Mat4 HMM_PREFIX(Div)(HMM_Mat4 Left, float Right)
{
    ASSERT_COVERED(HMM_DivM4fCPP);

    HMM_Mat4 Result = HMM_PREFIX(DivM4f)(Left, Right);

    return (Result);
}

COVERAGE(HMM_DivQFCPP, 1)
HMM_INLINE HMM_Quat HMM_PREFIX(Div)(HMM_Quat Left, float Right)
{
    ASSERT_COVERED(HMM_DivQFCPP);

    HMM_Quat Result = HMM_PREFIX(DivQF)(Left, Right);

    return (Result);
}

COVERAGE(HMM_EqV2CPP, 1)
HMM_INLINE HMM_Bool HMM_PREFIX(Eq)(HMM_Vec2 Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_EqV2CPP);

    HMM_Bool Result = HMM_PREFIX(EqV2)(Left, Right);

    return (Result);
}

COVERAGE(HMM_EqV3CPP, 1)
HMM_INLINE HMM_Bool HMM_PREFIX(Eq)(HMM_Vec3 Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_EqV3CPP);

    HMM_Bool Result = HMM_PREFIX(EqV3)(Left, Right);

    return (Result);
}

COVERAGE(HMM_EqV4CPP, 1)
HMM_INLINE HMM_Bool HMM_PREFIX(Eq)(HMM_Vec4 Left, HMM_Vec4 Right)
{
    ASSERT_COVERED(HMM_EqV4CPP);

    HMM_Bool Result = HMM_PREFIX(EqV4)(Left, Right);

    return (Result);
}

COVERAGE(HMM_AddV2Op, 1)
HMM_INLINE HMM_Vec2 operator+(HMM_Vec2 Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_AddV2Op);

    HMM_Vec2 Result = HMM_PREFIX(AddV2)(Left, Right);

    return (Result);
}

COVERAGE(HMM_AddV3Op, 1)
HMM_INLINE HMM_Vec3 operator+(HMM_Vec3 Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_AddV3Op);

    HMM_Vec3 Result = HMM_PREFIX(AddV3)(Left, Right);

    return (Result);
}

COVERAGE(HMM_AddV4Op, 1)
HMM_INLINE HMM_Vec4 operator+(HMM_Vec4 Left, HMM_Vec4 Right)
{
    ASSERT_COVERED(HMM_AddV4Op);

    HMM_Vec4 Result = HMM_PREFIX(AddV4)(Left, Right);

    return (Result);
}

COVERAGE(HMM_AddM4Op, 1)
HMM_INLINE HMM_Mat4 operator+(HMM_Mat4 Left, HMM_Mat4 Right)
{
    ASSERT_COVERED(HMM_AddM4Op);

    HMM_Mat4 Result = HMM_PREFIX(AddM4)(Left, Right);

    return (Result);
}

COVERAGE(HMM_AddQOp, 1)
HMM_INLINE HMM_Quat operator+(HMM_Quat Left, HMM_Quat Right)
{
    ASSERT_COVERED(HMM_AddQOp);

    HMM_Quat Result = HMM_PREFIX(AddQ)(Left, Right);

    return (Result);
}

COVERAGE(HMM_SubV2Op, 1)
HMM_INLINE HMM_Vec2 operator-(HMM_Vec2 Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_SubV2Op);

    HMM_Vec2 Result = HMM_PREFIX(SubV2)(Left, Right);

    return (Result);
}

COVERAGE(HMM_SubV3Op, 1)
HMM_INLINE HMM_Vec3 operator-(HMM_Vec3 Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_SubV3Op);

    HMM_Vec3 Result = HMM_PREFIX(SubV3)(Left, Right);

    return (Result);
}

COVERAGE(HMM_SubV4Op, 1)
HMM_INLINE HMM_Vec4 operator-(HMM_Vec4 Left, HMM_Vec4 Right)
{
    ASSERT_COVERED(HMM_SubV4Op);

    HMM_Vec4 Result = HMM_PREFIX(SubV4)(Left, Right);

    return (Result);
}

COVERAGE(HMM_SubM4Op, 1)
HMM_INLINE HMM_Mat4 operator-(HMM_Mat4 Left, HMM_Mat4 Right)
{
    ASSERT_COVERED(HMM_SubM4Op);

    HMM_Mat4 Result = HMM_PREFIX(SubM4)(Left, Right);

    return (Result);
}

COVERAGE(HMM_SubQOp, 1)
HMM_INLINE HMM_Quat operator-(HMM_Quat Left, HMM_Quat Right)
{
    ASSERT_COVERED(HMM_SubQOp);

    HMM_Quat Result = HMM_PREFIX(SubQ)(Left, Right);

    return (Result);
}

COVERAGE(HMM_MulV2Op, 1)
HMM_INLINE HMM_Vec2 operator*(HMM_Vec2 Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_MulV2Op);

    HMM_Vec2 Result = HMM_PREFIX(MulV2)(Left, Right);

    return (Result);
}

COVERAGE(HMM_MulV3Op, 1)
HMM_INLINE HMM_Vec3 operator*(HMM_Vec3 Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_MulV3Op);

    HMM_Vec3 Result = HMM_PREFIX(MulV3)(Left, Right);

    return (Result);
}

COVERAGE(HMM_MulV4Op, 1)
HMM_INLINE HMM_Vec4 operator*(HMM_Vec4 Left, HMM_Vec4 Right)
{
    ASSERT_COVERED(HMM_MulV4Op);

    HMM_Vec4 Result = HMM_PREFIX(MulV4)(Left, Right);

    return (Result);
}

COVERAGE(HMM_MulM4Op, 1)
HMM_INLINE HMM_Mat4 operator*(HMM_Mat4 Left, HMM_Mat4 Right)
{
    ASSERT_COVERED(HMM_MulM4Op);

    HMM_Mat4 Result = HMM_PREFIX(MulM4)(Left, Right);

    return (Result);
}

COVERAGE(HMM_MulQOp, 1)
HMM_INLINE HMM_Quat operator*(HMM_Quat Left, HMM_Quat Right)
{
    ASSERT_COVERED(HMM_MulQOp);

    HMM_Quat Result = HMM_PREFIX(MulQ)(Left, Right);

    return (Result);
}

COVERAGE(HMM_MulV2FOp, 1)
HMM_INLINE HMM_Vec2 operator*(HMM_Vec2 Left, float Right)
{
    ASSERT_COVERED(HMM_MulV2FOp);

    HMM_Vec2 Result = HMM_PREFIX(MulV2F)(Left, Right);

    return (Result);
}

COVERAGE(HMM_MulV3FOp, 1)
HMM_INLINE HMM_Vec3 operator*(HMM_Vec3 Left, float Right)
{
    ASSERT_COVERED(HMM_MulV3FOp);

    HMM_Vec3 Result = HMM_PREFIX(MulV3F)(Left, Right);

    return (Result);
}

COVERAGE(HMM_MulV4FOp, 1)
HMM_INLINE HMM_Vec4 operator*(HMM_Vec4 Left, float Right)
{
    ASSERT_COVERED(HMM_MulV4FOp);

    HMM_Vec4 Result = HMM_PREFIX(MulV4F)(Left, Right);

    return (Result);
}

COVERAGE(HMM_MulM4fOp, 1)
HMM_INLINE HMM_Mat4 operator*(HMM_Mat4 Left, float Right)
{
    ASSERT_COVERED(HMM_MulM4fOp);

    HMM_Mat4 Result = HMM_PREFIX(MulM4f)(Left, Right);

    return (Result);
}

COVERAGE(HMM_MulQFOp, 1)
HMM_INLINE HMM_Quat operator*(HMM_Quat Left, float Right)
{
    ASSERT_COVERED(HMM_MulQFOp);

    HMM_Quat Result = HMM_PREFIX(MulQF)(Left, Right);

    return (Result);
}

COVERAGE(HMM_MulV2FOpLeft, 1)
HMM_INLINE HMM_Vec2 operator*(float Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_MulV2FOpLeft);

    HMM_Vec2 Result = HMM_PREFIX(MulV2F)(Right, Left);

    return (Result);
}

COVERAGE(HMM_MulV3FOpLeft, 1)
HMM_INLINE HMM_Vec3 operator*(float Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_MulV3FOpLeft);

    HMM_Vec3 Result = HMM_PREFIX(MulV3F)(Right, Left);

    return (Result);
}

COVERAGE(HMM_MulV4FOpLeft, 1)
HMM_INLINE HMM_Vec4 operator*(float Left, HMM_Vec4 Right)
{
    ASSERT_COVERED(HMM_MulV4FOpLeft);

    HMM_Vec4 Result = HMM_PREFIX(MulV4F)(Right, Left);

    return (Result);
}

COVERAGE(HMM_MulM4fOpLeft, 1)
HMM_INLINE HMM_Mat4 operator*(float Left, HMM_Mat4 Right)
{
    ASSERT_COVERED(HMM_MulM4fOpLeft);

    HMM_Mat4 Result = HMM_PREFIX(MulM4f)(Right, Left);

    return (Result);
}

COVERAGE(HMM_MulQFOpLeft, 1)
HMM_INLINE HMM_Quat operator*(float Left, HMM_Quat Right)
{
    ASSERT_COVERED(HMM_MulQFOpLeft);

    HMM_Quat Result = HMM_PREFIX(MulQF)(Right, Left);

    return (Result);
}

COVERAGE(HMM_MulM4ByV4Op, 1)
HMM_INLINE HMM_Vec4 operator*(HMM_Mat4 Matrix, HMM_Vec4 Vector)
{
    ASSERT_COVERED(HMM_MulM4ByV4Op);

    HMM_Vec4 Result = HMM_PREFIX(MulM4ByV4)(Matrix, Vector);

    return (Result);
}

COVERAGE(HMM_DivV2Op, 1)
HMM_INLINE HMM_Vec2 operator/(HMM_Vec2 Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_DivV2Op);

    HMM_Vec2 Result = HMM_PREFIX(DivV2)(Left, Right);

    return (Result);
}

COVERAGE(HMM_DivV3Op, 1)
HMM_INLINE HMM_Vec3 operator/(HMM_Vec3 Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_DivV3Op);

    HMM_Vec3 Result = HMM_PREFIX(DivV3)(Left, Right);

    return (Result);
}

COVERAGE(HMM_DivV4Op, 1)
HMM_INLINE HMM_Vec4 operator/(HMM_Vec4 Left, HMM_Vec4 Right)
{
    ASSERT_COVERED(HMM_DivV4Op);

    HMM_Vec4 Result = HMM_PREFIX(DivV4)(Left, Right);

    return (Result);
}

COVERAGE(HMM_DivV2FOp, 1)
HMM_INLINE HMM_Vec2 operator/(HMM_Vec2 Left, float Right)
{
    ASSERT_COVERED(HMM_DivV2FOp);

    HMM_Vec2 Result = HMM_PREFIX(DivV2F)(Left, Right);

    return (Result);
}

COVERAGE(HMM_DivV3FOp, 1)
HMM_INLINE HMM_Vec3 operator/(HMM_Vec3 Left, float Right)
{
    ASSERT_COVERED(HMM_DivV3FOp);

    HMM_Vec3 Result = HMM_PREFIX(DivV3F)(Left, Right);

    return (Result);
}

COVERAGE(HMM_DivV4FOp, 1)
HMM_INLINE HMM_Vec4 operator/(HMM_Vec4 Left, float Right)
{
    ASSERT_COVERED(HMM_DivV4FOp);

    HMM_Vec4 Result = HMM_PREFIX(DivV4F)(Left, Right);

    return (Result);
}

COVERAGE(HMM_DivM4fOp, 1)
HMM_INLINE HMM_Mat4 operator/(HMM_Mat4 Left, float Right)
{
    ASSERT_COVERED(HMM_DivM4fOp);

    HMM_Mat4 Result = HMM_PREFIX(DivM4f)(Left, Right);

    return (Result);
}

COVERAGE(HMM_DivQFOp, 1)
HMM_INLINE HMM_Quat operator/(HMM_Quat Left, float Right)
{
    ASSERT_COVERED(HMM_DivQFOp);

    HMM_Quat Result = HMM_PREFIX(DivQF)(Left, Right);

    return (Result);
}

COVERAGE(HMM_AddV2Assign, 1)
HMM_INLINE HMM_Vec2 &operator+=(HMM_Vec2 &Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_AddV2Assign);

    return (Left = Left + Right);
}

COVERAGE(HMM_AddV3Assign, 1)
HMM_INLINE HMM_Vec3 &operator+=(HMM_Vec3 &Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_AddV3Assign);

    return (Left = Left + Right);
}

COVERAGE(HMM_AddV4Assign, 1)
HMM_INLINE HMM_Vec4 &operator+=(HMM_Vec4 &Left, HMM_Vec4 Right)
{
    ASSERT_COVERED(HMM_AddV4Assign);

    return (Left = Left + Right);
}

COVERAGE(HMM_AddM4Assign, 1)
HMM_INLINE HMM_Mat4 &operator+=(HMM_Mat4 &Left, HMM_Mat4 Right)
{
    ASSERT_COVERED(HMM_AddM4Assign);

    return (Left = Left + Right);
}

COVERAGE(HMM_AddQAssign, 1)
HMM_INLINE HMM_Quat &operator+=(HMM_Quat &Left, HMM_Quat Right)
{
    ASSERT_COVERED(HMM_AddQAssign);

    return (Left = Left + Right);
}

COVERAGE(HMM_SubV2Assign, 1)
HMM_INLINE HMM_Vec2 &operator-=(HMM_Vec2 &Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_SubV2Assign);

    return (Left = Left - Right);
}

COVERAGE(HMM_SubV3Assign, 1)
HMM_INLINE HMM_Vec3 &operator-=(HMM_Vec3 &Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_SubV3Assign);

    return (Left = Left - Right);
}

COVERAGE(HMM_SubV4Assign, 1)
HMM_INLINE HMM_Vec4 &operator-=(HMM_Vec4 &Left, HMM_Vec4 Right)
{
    ASSERT_COVERED(HMM_SubV4Assign);

    return (Left = Left - Right);
}

COVERAGE(HMM_SubM4Assign, 1)
HMM_INLINE HMM_Mat4 &operator-=(HMM_Mat4 &Left, HMM_Mat4 Right)
{
    ASSERT_COVERED(HMM_SubM4Assign);

    return (Left = Left - Right);
}

COVERAGE(HMM_SubQAssign, 1)
HMM_INLINE HMM_Quat &operator-=(HMM_Quat &Left, HMM_Quat Right)
{
    ASSERT_COVERED(HMM_SubQAssign);

    return (Left = Left - Right);
}

COVERAGE(HMM_MulV2Assign, 1)
HMM_INLINE HMM_Vec2 &operator*=(HMM_Vec2 &Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_MulV2Assign);

    return (Left = Left * Right);
}

COVERAGE(HMM_MulV3Assign, 1)
HMM_INLINE HMM_Vec3 &operator*=(HMM_Vec3 &Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_MulV3Assign);

    return (Left = Left * Right);
}

COVERAGE(HMM_MulV4Assign, 1)
HMM_INLINE HMM_Vec4 &operator*=(HMM_Vec4 &Left, HMM_Vec4 Right)
{
    ASSERT_COVERED(HMM_MulV4Assign);

    return (Left = Left * Right);
}

COVERAGE(HMM_MulV2FAssign, 1)
HMM_INLINE HMM_Vec2 &operator*=(HMM_Vec2 &Left, float Right)
{
    ASSERT_COVERED(HMM_MulV2FAssign);

    return (Left = Left * Right);
}

COVERAGE(HMM_MulV3FAssign, 1)
HMM_INLINE HMM_Vec3 &operator*=(HMM_Vec3 &Left, float Right)
{
    ASSERT_COVERED(HMM_MulV3FAssign);

    return (Left = Left * Right);
}

COVERAGE(HMM_MulV4FAssign, 1)
HMM_INLINE HMM_Vec4 &operator*=(HMM_Vec4 &Left, float Right)
{
    ASSERT_COVERED(HMM_MulV4FAssign);

    return (Left = Left * Right);
}

COVERAGE(HMM_MulM4fAssign, 1)
HMM_INLINE HMM_Mat4 &operator*=(HMM_Mat4 &Left, float Right)
{
    ASSERT_COVERED(HMM_MulM4fAssign);

    return (Left = Left * Right);
}

COVERAGE(HMM_MulQFAssign, 1)
HMM_INLINE HMM_Quat &operator*=(HMM_Quat &Left, float Right)
{
    ASSERT_COVERED(HMM_MulQFAssign);

    return (Left = Left * Right);
}

COVERAGE(HMM_DivV2Assign, 1)
HMM_INLINE HMM_Vec2 &operator/=(HMM_Vec2 &Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_DivV2Assign);

    return (Left = Left / Right);
}

COVERAGE(HMM_DivV3Assign, 1)
HMM_INLINE HMM_Vec3 &operator/=(HMM_Vec3 &Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_DivV3Assign);

    return (Left = Left / Right);
}

COVERAGE(HMM_DivV4Assign, 1)
HMM_INLINE HMM_Vec4 &operator/=(HMM_Vec4 &Left, HMM_Vec4 Right)
{
    ASSERT_COVERED(HMM_DivV4Assign);

    return (Left = Left / Right);
}

COVERAGE(HMM_DivV2FAssign, 1)
HMM_INLINE HMM_Vec2 &operator/=(HMM_Vec2 &Left, float Right)
{
    ASSERT_COVERED(HMM_DivV2FAssign);

    return (Left = Left / Right);
}

COVERAGE(HMM_DivV3FAssign, 1)
HMM_INLINE HMM_Vec3 &operator/=(HMM_Vec3 &Left, float Right)
{
    ASSERT_COVERED(HMM_DivV3FAssign);

    return (Left = Left / Right);
}

COVERAGE(HMM_DivV4FAssign, 1)
HMM_INLINE HMM_Vec4 &operator/=(HMM_Vec4 &Left, float Right)
{
    ASSERT_COVERED(HMM_DivV4FAssign);

    return (Left = Left / Right);
}

COVERAGE(HMM_DivM4fAssign, 1)
HMM_INLINE HMM_Mat4 &operator/=(HMM_Mat4 &Left, float Right)
{
    ASSERT_COVERED(HMM_DivM4fAssign);

    return (Left = Left / Right);
}

COVERAGE(HMM_DivQFAssign, 1)
HMM_INLINE HMM_Quat &operator/=(HMM_Quat &Left, float Right)
{
    ASSERT_COVERED(HMM_DivQFAssign);

    return (Left = Left / Right);
}

COVERAGE(HMM_EqV2Op, 1)
HMM_INLINE HMM_Bool operator==(HMM_Vec2 Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_EqV2Op);

    return HMM_PREFIX(EqV2)(Left, Right);
}

COVERAGE(HMM_EqV3Op, 1)
HMM_INLINE HMM_Bool operator==(HMM_Vec3 Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_EqV3Op);

    return HMM_PREFIX(EqV3)(Left, Right);
}

COVERAGE(HMM_EqV4Op, 1)
HMM_INLINE HMM_Bool operator==(HMM_Vec4 Left, HMM_Vec4 Right)
{
    ASSERT_COVERED(HMM_EqV4Op);

    return HMM_PREFIX(EqV4)(Left, Right);
}

COVERAGE(HMM_EqV2OpNot, 1)
HMM_INLINE HMM_Bool operator!=(HMM_Vec2 Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_EqV2OpNot);

    return !HMM_PREFIX(EqV2)(Left, Right);
}

COVERAGE(HMM_EqV3OpNot, 1)
HMM_INLINE HMM_Bool operator!=(HMM_Vec3 Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_EqV3OpNot);

    return !HMM_PREFIX(EqV3)(Left, Right);
}

COVERAGE(HMM_EqV4OpNot, 1)
HMM_INLINE HMM_Bool operator!=(HMM_Vec4 Left, HMM_Vec4 Right)
{
    ASSERT_COVERED(HMM_EqV4OpNot);

    return !HMM_PREFIX(EqV4)(Left, Right);
}

COVERAGE(HMM_UnaryMinusV2, 1)
HMM_INLINE HMM_Vec2 operator-(HMM_Vec2 In)
{
    ASSERT_COVERED(HMM_UnaryMinusV2);

    HMM_Vec2 Result;
    Result.X = -In.X;
    Result.Y = -In.Y;
    return(Result);
}

COVERAGE(HMM_UnaryMinusV3, 1)
HMM_INLINE HMM_Vec3 operator-(HMM_Vec3 In)
{
    ASSERT_COVERED(HMM_UnaryMinusV3);

    HMM_Vec3 Result;
    Result.X = -In.X;
    Result.Y = -In.Y;
    Result.Z = -In.Z;
    return(Result);
}

COVERAGE(HMM_UnaryMinusV4, 1)
HMM_INLINE HMM_Vec4 operator-(HMM_Vec4 In)
{
    ASSERT_COVERED(HMM_UnaryMinusV4);

    HMM_Vec4 Result;
#if HANDMADE_MATH__USE_SSE
    Result.InternalElementsSSE = _mm_xor_ps(In.InternalElementsSSE, _mm_set1_ps(-0.0f));
#else
    Result.X = -In.X;
    Result.Y = -In.Y;
    Result.Z = -In.Z;
    Result.W = -In.W;
#endif
    return(Result);
}

#endif /* __cplusplus */

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif

#endif /* HANDMADE_MATH_H */



