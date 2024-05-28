/*
  HandmadeMath.h v2.0.0

  This is a single header file with a bunch of useful types and functions for
  games and graphics. Consider it a lightweight alternative to GLM that works
  both C and C++.

  =============================================================================
  CONFIG
  =============================================================================

  By default, all angles in Handmade Math are specified in radians. However, it
  can be configured to use degrees or turns instead. Use one of the following
  defines to specify the default unit for angles:

    #define HANDMADE_MATH_USE_RADIANS
    #define HANDMADE_MATH_USE_DEGREES
    #define HANDMADE_MATH_USE_TURNS

  Regardless of the default angle, you can use the following functions to
  specify an angle in a particular unit:

    HMM_AngleRad(radians)
    HMM_AngleDeg(degrees)
    HMM_AngleTurn(turns)

  The definitions of these functions change depending on the default unit.

  -----------------------------------------------------------------------------

  Handmade Math ships with SSE (SIMD) implementations of several common
  operations. To disable the use of SSE intrinsics, you must define
  HANDMADE_MATH_NO_SSE before including this file:

    #define HANDMADE_MATH_NO_SSE
    #include "HandmadeMath.h"

  -----------------------------------------------------------------------------

  To use Handmade Math without the C runtime library, you must provide your own
  implementations of basic math functions. Otherwise, HandmadeMath.h will use
  the runtime library implementation of these functions.

  Define HANDMADE_MATH_PROVIDE_MATH_FUNCTIONS and provide your own
  implementations of HMM_SINF, HMM_COSF, HMM_TANF, HMM_ACOSF, and HMM_SQRTF
  before including HandmadeMath.h, like so:

    #define HANDMADE_MATH_PROVIDE_MATH_FUNCTIONS
    #define HMM_SINF MySinF
    #define HMM_COSF MyCosF
    #define HMM_TANF MyTanF
    #define HMM_ACOSF MyACosF
    #define HMM_SQRTF MySqrtF
    #include "HandmadeMath.h"

  By default, it is assumed that your math functions take radians. To use
  different units, you must define HMM_ANGLE_USER_TO_INTERNAL and
  HMM_ANGLE_INTERNAL_TO_USER. For example, if you want to use degrees in your
  code but your math functions use turns:

    #define HMM_ANGLE_USER_TO_INTERNAL(a) ((a)*HMM_DegToTurn)
    #define HMM_ANGLE_INTERNAL_TO_USER(a) ((a)*HMM_TurnToDeg)

  =============================================================================

  LICENSE

  This software is in the public domain. Where that dedication is not
  recognized, you are granted a perpetual, irrevocable license to copy,
  distribute, and modify this file as you see fit.

  =============================================================================

  CREDITS

  Originally written by Zakary Strange.

  Functionality:
   Zakary Strange (strangezak@protonmail.com && @strangezak)
   Matt Mascarenhas (@miblo_)
   Aleph
   FieryDrake (@fierydrake)
   Gingerbill (@TheGingerBill)
   Ben Visness (@bvisness)
   Trinton Bullard (@Peliex_Dev)
   @AntonDan
   Logan Forman (@dev_dwarf)

  Fixes:
   Jeroen van Rijn (@J_vanRijn)
   Kiljacken (@Kiljacken)
   Insofaras (@insofaras)
   Daniel Gibson (@DanielGibson)
*/

#ifndef HANDMADE_MATH_H
#define HANDMADE_MATH_H

// Dummy macros for when test framework is not present.
#ifndef COVERAGE
# define COVERAGE(a, b)
#endif

#ifndef ASSERT_COVERED
# define ASSERT_COVERED(a)
#endif

#ifdef HANDMADE_MATH_NO_SSE
# warning "HANDMADE_MATH_NO_SSE is deprecated, use HANDMADE_MATH_NO_SIMD instead"
# define HANDMADE_MATH_NO_SIMD
#endif

/* let's figure out if SSE is really available (unless disabled anyway)
   (it isn't on non-x86/x86_64 platforms or even x86 without explicit SSE support)
   => only use "#ifdef HANDMADE_MATH__USE_SSE" to check for SSE support below this block! */
#ifndef HANDMADE_MATH_NO_SIMD
# ifdef _MSC_VER /* MSVC supports SSE in amd64 mode or _M_IX86_FP >= 1 (2 means SSE2) */
#  if defined(_M_AMD64) || ( defined(_M_IX86_FP) && _M_IX86_FP >= 1 )
#   define HANDMADE_MATH__USE_SSE 1
#  endif
# else /* not MSVC, probably GCC, clang, icc or something that doesn't support SSE anyway */
#  ifdef __SSE__ /* they #define __SSE__ if it's supported */
#   define HANDMADE_MATH__USE_SSE 1
#  endif /*  __SSE__ */
# endif /* not _MSC_VER */
# ifdef __ARM_NEON
#  define HANDMADE_MATH__USE_NEON 1
# endif /* NEON Supported */
#endif /* #ifndef HANDMADE_MATH_NO_SIMD */

#if (!defined(__cplusplus) && defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L)
# define HANDMADE_MATH__USE_C11_GENERICS 1
#endif

#ifdef HANDMADE_MATH__USE_SSE
# include <xmmintrin.h>
#endif

#ifdef HANDMADE_MATH__USE_NEON
# include <arm_neon.h>
#endif

#ifdef _MSC_VER
#pragma warning(disable:4201)
#endif

#if defined(__GNUC__) || defined(__clang__)
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wfloat-equal"
# pragma GCC diagnostic ignored "-Wmissing-braces"
# ifdef __clang__
#  pragma GCC diagnostic ignored "-Wgnu-anonymous-struct"
#  pragma GCC diagnostic ignored "-Wmissing-field-initializers"
# endif
#endif

#if defined(__GNUC__) || defined(__clang__)
# define HMM_DEPRECATED(msg) __attribute__((deprecated(msg)))
#elif defined(_MSC_VER)
# define HMM_DEPRECATED(msg) __declspec(deprecated(msg))
#else
# define HMM_DEPRECATED(msg)
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#if !defined(HANDMADE_MATH_USE_DEGREES) \
    && !defined(HANDMADE_MATH_USE_TURNS) \
    && !defined(HANDMADE_MATH_USE_RADIANS)
# define HANDMADE_MATH_USE_RADIANS
#endif

#define HMM_PI 3.14159265358979323846
#define HMM_PI32 3.14159265359f
#define HMM_DEG180 180.0
#define HMM_DEG18032 180.0f
#define HMM_TURNHALF 0.5
#define HMM_TURNHALF32 0.5f
#define HMM_RadToDeg ((float)(HMM_DEG180/HMM_PI))
#define HMM_RadToTurn ((float)(HMM_TURNHALF/HMM_PI))
#define HMM_DegToRad ((float)(HMM_PI/HMM_DEG180))
#define HMM_DegToTurn ((float)(HMM_TURNHALF/HMM_DEG180))
#define HMM_TurnToRad ((float)(HMM_PI/HMM_TURNHALF))
#define HMM_TurnToDeg ((float)(HMM_DEG180/HMM_TURNHALF))

#if defined(HANDMADE_MATH_USE_RADIANS)
# define HMM_AngleRad(a) (a)
# define HMM_AngleDeg(a) ((a)*HMM_DegToRad)
# define HMM_AngleTurn(a) ((a)*HMM_TurnToRad)
#elif defined(HANDMADE_MATH_USE_DEGREES)
# define HMM_AngleRad(a) ((a)*HMM_RadToDeg)
# define HMM_AngleDeg(a) (a)
# define HMM_AngleTurn(a) ((a)*HMM_TurnToDeg)
#elif defined(HANDMADE_MATH_USE_TURNS)
# define HMM_AngleRad(a) ((a)*HMM_RadToTurn)
# define HMM_AngleDeg(a) ((a)*HMM_DegToTurn)
# define HMM_AngleTurn(a) (a)
#endif

#if !defined(HANDMADE_MATH_PROVIDE_MATH_FUNCTIONS)
# include <math.h>
# define HMM_SINF sinf
# define HMM_COSF cosf
# define HMM_TANF tanf
# define HMM_SQRTF sqrtf
# define HMM_ACOSF acosf
#endif

#if !defined(HMM_ANGLE_USER_TO_INTERNAL)
# define HMM_ANGLE_USER_TO_INTERNAL(a) (HMM_ToRad(a))
#endif

#if !defined(HMM_ANGLE_INTERNAL_TO_USER)
# if defined(HANDMADE_MATH_USE_RADIANS)
#  define HMM_ANGLE_INTERNAL_TO_USER(a) (a)
# elif defined(HANDMADE_MATH_USE_DEGREES)
#  define HMM_ANGLE_INTERNAL_TO_USER(a) ((a)*HMM_RadToDeg)
# elif defined(HANDMADE_MATH_USE_TURNS)
#  define HMM_ANGLE_INTERNAL_TO_USER(a) ((a)*HMM_RadToTurn)
# endif
#endif

#define HMM_MIN(a, b) ((a) > (b) ? (b) : (a))
#define HMM_MAX(a, b) ((a) < (b) ? (b) : (a))
#define HMM_ABS(a) ((a) > 0 ? (a) : -(a))
#define HMM_MOD(a, m) (((a) % (m)) >= 0 ? ((a) % (m)) : (((a) % (m)) + (m)))
#define HMM_SQUARE(x) ((x) * (x))

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
    inline float &operator[](int Index) { return Elements[Index]; }
    inline const float& operator[](int Index) const { return Elements[Index]; }
#endif
} HMM_Vec2;

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
        float _Ignored0;
    };

    struct
    {
        float _Ignored1;
        HMM_Vec2 YZ;
    };

    struct
    {
        HMM_Vec2 UV;
        float _Ignored2;
    };

    struct
    {
        float _Ignored3;
        HMM_Vec2 VW;
    };

    float Elements[3];

#ifdef __cplusplus
    inline float &operator[](int Index) { return Elements[Index]; }
    inline const float &operator[](int Index) const { return Elements[Index]; }
#endif
} HMM_Vec3;

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
        float _Ignored0;
        float _Ignored1;
    };

    struct
    {
        float _Ignored2;
        HMM_Vec2 YZ;
        float _Ignored3;
    };

    struct
    {
        float _Ignored4;
        float _Ignored5;
        HMM_Vec2 ZW;
    };

    float Elements[4];

#ifdef HANDMADE_MATH__USE_SSE
    __m128 SSE;
#endif

#ifdef HANDMADE_MATH__USE_NEON
    float32x4_t NEON;
#endif

#ifdef __cplusplus
    inline float &operator[](int Index) { return Elements[Index]; }
    inline const float &operator[](int Index) const { return Elements[Index]; }
#endif
} HMM_Vec4;

typedef union HMM_Mat2
{
    float Elements[2][2];
    HMM_Vec2 Columns[2];

#ifdef __cplusplus
    inline HMM_Vec2 &operator[](int Index) { return Columns[Index]; }
    inline const HMM_Vec2 &operator[](int Index) const { return Columns[Index]; }
#endif
} HMM_Mat2;

typedef union HMM_Mat3
{
    float Elements[3][3];
    HMM_Vec3 Columns[3];

#ifdef __cplusplus
    inline HMM_Vec3 &operator[](int Index) { return Columns[Index]; }
    inline const HMM_Vec3 &operator[](int Index) const { return Columns[Index]; }
#endif
} HMM_Mat3;

typedef union HMM_Mat4
{
    float Elements[4][4];
    HMM_Vec4 Columns[4];

#ifdef __cplusplus
    inline HMM_Vec4 &operator[](int Index) { return Columns[Index]; }
    inline const HMM_Vec4 &operator[](int Index) const { return Columns[Index]; }
#endif
} HMM_Mat4;

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
    __m128 SSE;
#endif
#ifdef HANDMADE_MATH__USE_NEON
    float32x4_t NEON;
#endif
} HMM_Quat;

typedef signed int HMM_Bool;

/*
 * Angle unit conversion functions
 */
static inline float HMM_ToRad(float Angle)
{
#if defined(HANDMADE_MATH_USE_RADIANS)
    float Result = Angle;
#elif defined(HANDMADE_MATH_USE_DEGREES)
    float Result = Angle * HMM_DegToRad;
#elif defined(HANDMADE_MATH_USE_TURNS)
    float Result = Angle * HMM_TurnToRad;
#endif

    return Result;
}

static inline float HMM_ToDeg(float Angle)
{
#if defined(HANDMADE_MATH_USE_RADIANS)
    float Result = Angle * HMM_RadToDeg;
#elif defined(HANDMADE_MATH_USE_DEGREES)
    float Result = Angle;
#elif defined(HANDMADE_MATH_USE_TURNS)
    float Result = Angle * HMM_TurnToDeg;
#endif

    return Result;
}

static inline float HMM_ToTurn(float Angle)
{
#if defined(HANDMADE_MATH_USE_RADIANS)
    float Result = Angle * HMM_RadToTurn;
#elif defined(HANDMADE_MATH_USE_DEGREES)
    float Result = Angle * HMM_DegToTurn;
#elif defined(HANDMADE_MATH_USE_TURNS)
    float Result = Angle;
#endif

    return Result;
}

/*
 * Floating-point math functions
 */

COVERAGE(HMM_SinF, 1)
static inline float HMM_SinF(float Angle)
{
    ASSERT_COVERED(HMM_SinF);
    return HMM_SINF(HMM_ANGLE_USER_TO_INTERNAL(Angle));
}

COVERAGE(HMM_CosF, 1)
static inline float HMM_CosF(float Angle)
{
    ASSERT_COVERED(HMM_CosF);
    return HMM_COSF(HMM_ANGLE_USER_TO_INTERNAL(Angle));
}

COVERAGE(HMM_TanF, 1)
static inline float HMM_TanF(float Angle)
{
    ASSERT_COVERED(HMM_TanF);
    return HMM_TANF(HMM_ANGLE_USER_TO_INTERNAL(Angle));
}

COVERAGE(HMM_ACosF, 1)
static inline float HMM_ACosF(float Arg)
{
    ASSERT_COVERED(HMM_ACosF);
    return HMM_ANGLE_INTERNAL_TO_USER(HMM_ACOSF(Arg));
}

COVERAGE(HMM_SqrtF, 1)
static inline float HMM_SqrtF(float Float)
{
    ASSERT_COVERED(HMM_SqrtF);

    float Result;

#ifdef HANDMADE_MATH__USE_SSE
    __m128 In = _mm_set_ss(Float);
    __m128 Out = _mm_sqrt_ss(In);
    Result = _mm_cvtss_f32(Out);
#elif defined(HANDMADE_MATH__USE_NEON)
    float32x4_t In = vdupq_n_f32(Float);
    float32x4_t Out = vsqrtq_f32(In);
    Result = vgetq_lane_f32(Out, 0);
#else
    Result = HMM_SQRTF(Float);
#endif

    return Result;
}

COVERAGE(HMM_InvSqrtF, 1)
static inline float HMM_InvSqrtF(float Float)
{
    ASSERT_COVERED(HMM_InvSqrtF);

    float Result;

    Result = 1.0f/HMM_SqrtF(Float);

    return Result;
}


/*
 * Utility functions
 */

COVERAGE(HMM_Lerp, 1)
static inline float HMM_Lerp(float A, float Time, float B)
{
    ASSERT_COVERED(HMM_Lerp);
    return (1.0f - Time) * A + Time * B;
}

COVERAGE(HMM_Clamp, 1)
static inline float HMM_Clamp(float Min, float Value, float Max)
{
    ASSERT_COVERED(HMM_Clamp);

    float Result = Value;

    if (Result < Min)
    {
        Result = Min;
    }

    if (Result > Max)
    {
        Result = Max;
    }

    return Result;
}


/*
 * Vector initialization
 */

COVERAGE(HMM_V2, 1)
static inline HMM_Vec2 HMM_V2(float X, float Y)
{
    ASSERT_COVERED(HMM_V2);

    HMM_Vec2 Result;
    Result.X = X;
    Result.Y = Y;

    return Result;
}

COVERAGE(HMM_V3, 1)
static inline HMM_Vec3 HMM_V3(float X, float Y, float Z)
{
    ASSERT_COVERED(HMM_V3);

    HMM_Vec3 Result;
    Result.X = X;
    Result.Y = Y;
    Result.Z = Z;

    return Result;
}

COVERAGE(HMM_V4, 1)
static inline HMM_Vec4 HMM_V4(float X, float Y, float Z, float W)
{
    ASSERT_COVERED(HMM_V4);

    HMM_Vec4 Result;

#ifdef HANDMADE_MATH__USE_SSE
    Result.SSE = _mm_setr_ps(X, Y, Z, W);
#elif defined(HANDMADE_MATH__USE_NEON)
    float32x4_t v = {X, Y, Z, W};
    Result.NEON = v;
#else
    Result.X = X;
    Result.Y = Y;
    Result.Z = Z;
    Result.W = W;
#endif

    return Result;
}

COVERAGE(HMM_V4V, 1)
static inline HMM_Vec4 HMM_V4V(HMM_Vec3 Vector, float W)
{
    ASSERT_COVERED(HMM_V4V);

    HMM_Vec4 Result;

#ifdef HANDMADE_MATH__USE_SSE
    Result.SSE = _mm_setr_ps(Vector.X, Vector.Y, Vector.Z, W);
#elif defined(HANDMADE_MATH__USE_NEON)
    float32x4_t v = {Vector.X, Vector.Y, Vector.Z, W};
    Result.NEON = v;
#else
    Result.XYZ = Vector;
    Result.W = W;
#endif

    return Result;
}


/*
 * Binary vector operations
 */

COVERAGE(HMM_AddV2, 1)
static inline HMM_Vec2 HMM_AddV2(HMM_Vec2 Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_AddV2);

    HMM_Vec2 Result;
    Result.X = Left.X + Right.X;
    Result.Y = Left.Y + Right.Y;

    return Result;
}

COVERAGE(HMM_AddV3, 1)
static inline HMM_Vec3 HMM_AddV3(HMM_Vec3 Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_AddV3);

    HMM_Vec3 Result;
    Result.X = Left.X + Right.X;
    Result.Y = Left.Y + Right.Y;
    Result.Z = Left.Z + Right.Z;

    return Result;
}

COVERAGE(HMM_AddV4, 1)
static inline HMM_Vec4 HMM_AddV4(HMM_Vec4 Left, HMM_Vec4 Right)
{
    ASSERT_COVERED(HMM_AddV4);

    HMM_Vec4 Result;

#ifdef HANDMADE_MATH__USE_SSE
    Result.SSE = _mm_add_ps(Left.SSE, Right.SSE);
#elif defined(HANDMADE_MATH__USE_NEON)
    Result.NEON = vaddq_f32(Left.NEON, Right.NEON);
#else
    Result.X = Left.X + Right.X;
    Result.Y = Left.Y + Right.Y;
    Result.Z = Left.Z + Right.Z;
    Result.W = Left.W + Right.W;
#endif

    return Result;
}

COVERAGE(HMM_SubV2, 1)
static inline HMM_Vec2 HMM_SubV2(HMM_Vec2 Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_SubV2);

    HMM_Vec2 Result;
    Result.X = Left.X - Right.X;
    Result.Y = Left.Y - Right.Y;

    return Result;
}

COVERAGE(HMM_SubV3, 1)
static inline HMM_Vec3 HMM_SubV3(HMM_Vec3 Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_SubV3);

    HMM_Vec3 Result;
    Result.X = Left.X - Right.X;
    Result.Y = Left.Y - Right.Y;
    Result.Z = Left.Z - Right.Z;

    return Result;
}

COVERAGE(HMM_SubV4, 1)
static inline HMM_Vec4 HMM_SubV4(HMM_Vec4 Left, HMM_Vec4 Right)
{
    ASSERT_COVERED(HMM_SubV4);

    HMM_Vec4 Result;

#ifdef HANDMADE_MATH__USE_SSE
    Result.SSE = _mm_sub_ps(Left.SSE, Right.SSE);
#elif defined(HANDMADE_MATH__USE_NEON)
    Result.NEON = vsubq_f32(Left.NEON, Right.NEON);
#else
    Result.X = Left.X - Right.X;
    Result.Y = Left.Y - Right.Y;
    Result.Z = Left.Z - Right.Z;
    Result.W = Left.W - Right.W;
#endif

    return Result;
}

COVERAGE(HMM_MulV2, 1)
static inline HMM_Vec2 HMM_MulV2(HMM_Vec2 Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_MulV2);

    HMM_Vec2 Result;
    Result.X = Left.X * Right.X;
    Result.Y = Left.Y * Right.Y;

    return Result;
}

COVERAGE(HMM_MulV2F, 1)
static inline HMM_Vec2 HMM_MulV2F(HMM_Vec2 Left, float Right)
{
    ASSERT_COVERED(HMM_MulV2F);

    HMM_Vec2 Result;
    Result.X = Left.X * Right;
    Result.Y = Left.Y * Right;

    return Result;
}

COVERAGE(HMM_MulV3, 1)
static inline HMM_Vec3 HMM_MulV3(HMM_Vec3 Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_MulV3);

    HMM_Vec3 Result;
    Result.X = Left.X * Right.X;
    Result.Y = Left.Y * Right.Y;
    Result.Z = Left.Z * Right.Z;

    return Result;
}

COVERAGE(HMM_MulV3F, 1)
static inline HMM_Vec3 HMM_MulV3F(HMM_Vec3 Left, float Right)
{
    ASSERT_COVERED(HMM_MulV3F);

    HMM_Vec3 Result;
    Result.X = Left.X * Right;
    Result.Y = Left.Y * Right;
    Result.Z = Left.Z * Right;

    return Result;
}

COVERAGE(HMM_MulV4, 1)
static inline HMM_Vec4 HMM_MulV4(HMM_Vec4 Left, HMM_Vec4 Right)
{
    ASSERT_COVERED(HMM_MulV4);

    HMM_Vec4 Result;

#ifdef HANDMADE_MATH__USE_SSE
    Result.SSE = _mm_mul_ps(Left.SSE, Right.SSE);
#elif defined(HANDMADE_MATH__USE_NEON)
    Result.NEON = vmulq_f32(Left.NEON, Right.NEON);
#else
    Result.X = Left.X * Right.X;
    Result.Y = Left.Y * Right.Y;
    Result.Z = Left.Z * Right.Z;
    Result.W = Left.W * Right.W;
#endif

    return Result;
}

COVERAGE(HMM_MulV4F, 1)
static inline HMM_Vec4 HMM_MulV4F(HMM_Vec4 Left, float Right)
{
    ASSERT_COVERED(HMM_MulV4F);

    HMM_Vec4 Result;

#ifdef HANDMADE_MATH__USE_SSE
    __m128 Scalar = _mm_set1_ps(Right);
    Result.SSE = _mm_mul_ps(Left.SSE, Scalar);
#elif defined(HANDMADE_MATH__USE_NEON)
    Result.NEON = vmulq_n_f32(Left.NEON, Right);
#else
    Result.X = Left.X * Right;
    Result.Y = Left.Y * Right;
    Result.Z = Left.Z * Right;
    Result.W = Left.W * Right;
#endif

    return Result;
}

COVERAGE(HMM_DivV2, 1)
static inline HMM_Vec2 HMM_DivV2(HMM_Vec2 Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_DivV2);

    HMM_Vec2 Result;
    Result.X = Left.X / Right.X;
    Result.Y = Left.Y / Right.Y;

    return Result;
}

COVERAGE(HMM_DivV2F, 1)
static inline HMM_Vec2 HMM_DivV2F(HMM_Vec2 Left, float Right)
{
    ASSERT_COVERED(HMM_DivV2F);

    HMM_Vec2 Result;
    Result.X = Left.X / Right;
    Result.Y = Left.Y / Right;

    return Result;
}

COVERAGE(HMM_DivV3, 1)
static inline HMM_Vec3 HMM_DivV3(HMM_Vec3 Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_DivV3);

    HMM_Vec3 Result;
    Result.X = Left.X / Right.X;
    Result.Y = Left.Y / Right.Y;
    Result.Z = Left.Z / Right.Z;

    return Result;
}

COVERAGE(HMM_DivV3F, 1)
static inline HMM_Vec3 HMM_DivV3F(HMM_Vec3 Left, float Right)
{
    ASSERT_COVERED(HMM_DivV3F);

    HMM_Vec3 Result;
    Result.X = Left.X / Right;
    Result.Y = Left.Y / Right;
    Result.Z = Left.Z / Right;

    return Result;
}

COVERAGE(HMM_DivV4, 1)
static inline HMM_Vec4 HMM_DivV4(HMM_Vec4 Left, HMM_Vec4 Right)
{
    ASSERT_COVERED(HMM_DivV4);

    HMM_Vec4 Result;

#ifdef HANDMADE_MATH__USE_SSE
    Result.SSE = _mm_div_ps(Left.SSE, Right.SSE);
#elif defined(HANDMADE_MATH__USE_NEON)
    Result.NEON = vdivq_f32(Left.NEON, Right.NEON);
#else
    Result.X = Left.X / Right.X;
    Result.Y = Left.Y / Right.Y;
    Result.Z = Left.Z / Right.Z;
    Result.W = Left.W / Right.W;
#endif

    return Result;
}

COVERAGE(HMM_DivV4F, 1)
static inline HMM_Vec4 HMM_DivV4F(HMM_Vec4 Left, float Right)
{
    ASSERT_COVERED(HMM_DivV4F);

    HMM_Vec4 Result;

#ifdef HANDMADE_MATH__USE_SSE
    __m128 Scalar = _mm_set1_ps(Right);
    Result.SSE = _mm_div_ps(Left.SSE, Scalar);
#elif defined(HANDMADE_MATH__USE_NEON)
    float32x4_t Scalar = vdupq_n_f32(Right);
    Result.NEON = vdivq_f32(Left.NEON, Scalar);
#else
    Result.X = Left.X / Right;
    Result.Y = Left.Y / Right;
    Result.Z = Left.Z / Right;
    Result.W = Left.W / Right;
#endif

    return Result;
}

COVERAGE(HMM_EqV2, 1)
static inline HMM_Bool HMM_EqV2(HMM_Vec2 Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_EqV2);
    return Left.X == Right.X && Left.Y == Right.Y;
}

COVERAGE(HMM_EqV3, 1)
static inline HMM_Bool HMM_EqV3(HMM_Vec3 Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_EqV3);
    return Left.X == Right.X && Left.Y == Right.Y && Left.Z == Right.Z;
}

COVERAGE(HMM_EqV4, 1)
static inline HMM_Bool HMM_EqV4(HMM_Vec4 Left, HMM_Vec4 Right)
{
    ASSERT_COVERED(HMM_EqV4);
    return Left.X == Right.X && Left.Y == Right.Y && Left.Z == Right.Z && Left.W == Right.W;
}

COVERAGE(HMM_DotV2, 1)
static inline float HMM_DotV2(HMM_Vec2 Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_DotV2);
    return (Left.X * Right.X) + (Left.Y * Right.Y);
}

COVERAGE(HMM_DotV3, 1)
static inline float HMM_DotV3(HMM_Vec3 Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_DotV3);
    return (Left.X * Right.X) + (Left.Y * Right.Y) + (Left.Z * Right.Z);
}

COVERAGE(HMM_DotV4, 1)
static inline float HMM_DotV4(HMM_Vec4 Left, HMM_Vec4 Right)
{
    ASSERT_COVERED(HMM_DotV4);

    float Result;

    // NOTE(zak): IN the future if we wanna check what version SSE is support
    // we can use _mm_dp_ps (4.3) but for now we will use the old way.
    // Or a r = _mm_mul_ps(v1, v2), r = _mm_hadd_ps(r, r), r = _mm_hadd_ps(r, r) for SSE3
#ifdef HANDMADE_MATH__USE_SSE
    __m128 SSEResultOne = _mm_mul_ps(Left.SSE, Right.SSE);
    __m128 SSEResultTwo = _mm_shuffle_ps(SSEResultOne, SSEResultOne, _MM_SHUFFLE(2, 3, 0, 1));
    SSEResultOne = _mm_add_ps(SSEResultOne, SSEResultTwo);
    SSEResultTwo = _mm_shuffle_ps(SSEResultOne, SSEResultOne, _MM_SHUFFLE(0, 1, 2, 3));
    SSEResultOne = _mm_add_ps(SSEResultOne, SSEResultTwo);
    _mm_store_ss(&Result, SSEResultOne);
#elif defined(HANDMADE_MATH__USE_NEON)
    float32x4_t NEONMultiplyResult = vmulq_f32(Left.NEON, Right.NEON);
    float32x4_t NEONHalfAdd = vpaddq_f32(NEONMultiplyResult, NEONMultiplyResult);
    float32x4_t NEONFullAdd = vpaddq_f32(NEONHalfAdd, NEONHalfAdd);
    Result = vgetq_lane_f32(NEONFullAdd, 0);
#else
    Result = ((Left.X * Right.X) + (Left.Z * Right.Z)) + ((Left.Y * Right.Y) + (Left.W * Right.W));
#endif

    return Result;
}

COVERAGE(HMM_Cross, 1)
static inline HMM_Vec3 HMM_Cross(HMM_Vec3 Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_Cross);

    HMM_Vec3 Result;
    Result.X = (Left.Y * Right.Z) - (Left.Z * Right.Y);
    Result.Y = (Left.Z * Right.X) - (Left.X * Right.Z);
    Result.Z = (Left.X * Right.Y) - (Left.Y * Right.X);

    return Result;
}


/*
 * Unary vector operations
 */

COVERAGE(HMM_LenSqrV2, 1)
static inline float HMM_LenSqrV2(HMM_Vec2 A)
{
    ASSERT_COVERED(HMM_LenSqrV2);
    return HMM_DotV2(A, A);
}

COVERAGE(HMM_LenSqrV3, 1)
static inline float HMM_LenSqrV3(HMM_Vec3 A)
{
    ASSERT_COVERED(HMM_LenSqrV3);
    return HMM_DotV3(A, A);
}

COVERAGE(HMM_LenSqrV4, 1)
static inline float HMM_LenSqrV4(HMM_Vec4 A)
{
    ASSERT_COVERED(HMM_LenSqrV4);
    return HMM_DotV4(A, A);
}

COVERAGE(HMM_LenV2, 1)
static inline float HMM_LenV2(HMM_Vec2 A)
{
    ASSERT_COVERED(HMM_LenV2);
    return HMM_SqrtF(HMM_LenSqrV2(A));
}

COVERAGE(HMM_LenV3, 1)
static inline float HMM_LenV3(HMM_Vec3 A)
{
    ASSERT_COVERED(HMM_LenV3);
    return HMM_SqrtF(HMM_LenSqrV3(A));
}

COVERAGE(HMM_LenV4, 1)
static inline float HMM_LenV4(HMM_Vec4 A)
{
    ASSERT_COVERED(HMM_LenV4);
    return HMM_SqrtF(HMM_LenSqrV4(A));
}

COVERAGE(HMM_NormV2, 1)
static inline HMM_Vec2 HMM_NormV2(HMM_Vec2 A)
{
    ASSERT_COVERED(HMM_NormV2);
    return HMM_MulV2F(A, HMM_InvSqrtF(HMM_DotV2(A, A)));
}

COVERAGE(HMM_NormV3, 1)
static inline HMM_Vec3 HMM_NormV3(HMM_Vec3 A)
{
    ASSERT_COVERED(HMM_NormV3);
    return HMM_MulV3F(A, HMM_InvSqrtF(HMM_DotV3(A, A)));
}

COVERAGE(HMM_NormV4, 1)
static inline HMM_Vec4 HMM_NormV4(HMM_Vec4 A)
{
    ASSERT_COVERED(HMM_NormV4);
    return HMM_MulV4F(A, HMM_InvSqrtF(HMM_DotV4(A, A)));
}

/*
 * Utility vector functions
 */

COVERAGE(HMM_LerpV2, 1)
static inline HMM_Vec2 HMM_LerpV2(HMM_Vec2 A, float Time, HMM_Vec2 B)
{
    ASSERT_COVERED(HMM_LerpV2);
    return HMM_AddV2(HMM_MulV2F(A, 1.0f - Time), HMM_MulV2F(B, Time));
}

COVERAGE(HMM_LerpV3, 1)
static inline HMM_Vec3 HMM_LerpV3(HMM_Vec3 A, float Time, HMM_Vec3 B)
{
    ASSERT_COVERED(HMM_LerpV3);
    return HMM_AddV3(HMM_MulV3F(A, 1.0f - Time), HMM_MulV3F(B, Time));
}

COVERAGE(HMM_LerpV4, 1)
static inline HMM_Vec4 HMM_LerpV4(HMM_Vec4 A, float Time, HMM_Vec4 B)
{
    ASSERT_COVERED(HMM_LerpV4);
    return HMM_AddV4(HMM_MulV4F(A, 1.0f - Time), HMM_MulV4F(B, Time));
}

/*
 * SSE stuff
 */

COVERAGE(HMM_LinearCombineV4M4, 1)
static inline HMM_Vec4 HMM_LinearCombineV4M4(HMM_Vec4 Left, HMM_Mat4 Right)
{
    ASSERT_COVERED(HMM_LinearCombineV4M4);

    HMM_Vec4 Result;
#ifdef HANDMADE_MATH__USE_SSE
    Result.SSE = _mm_mul_ps(_mm_shuffle_ps(Left.SSE, Left.SSE, 0x00), Right.Columns[0].SSE);
    Result.SSE = _mm_add_ps(Result.SSE, _mm_mul_ps(_mm_shuffle_ps(Left.SSE, Left.SSE, 0x55), Right.Columns[1].SSE));
    Result.SSE = _mm_add_ps(Result.SSE, _mm_mul_ps(_mm_shuffle_ps(Left.SSE, Left.SSE, 0xaa), Right.Columns[2].SSE));
    Result.SSE = _mm_add_ps(Result.SSE, _mm_mul_ps(_mm_shuffle_ps(Left.SSE, Left.SSE, 0xff), Right.Columns[3].SSE));
#elif defined(HANDMADE_MATH__USE_NEON)
    Result.NEON = vmulq_laneq_f32(Right.Columns[0].NEON, Left.NEON, 0);
    Result.NEON = vfmaq_laneq_f32(Result.NEON, Right.Columns[1].NEON, Left.NEON, 1);
    Result.NEON = vfmaq_laneq_f32(Result.NEON, Right.Columns[2].NEON, Left.NEON, 2);
    Result.NEON = vfmaq_laneq_f32(Result.NEON, Right.Columns[3].NEON, Left.NEON, 3);
#else
    Result.X = Left.Elements[0] * Right.Columns[0].X;
    Result.Y = Left.Elements[0] * Right.Columns[0].Y;
    Result.Z = Left.Elements[0] * Right.Columns[0].Z;
    Result.W = Left.Elements[0] * Right.Columns[0].W;

    Result.X += Left.Elements[1] * Right.Columns[1].X;
    Result.Y += Left.Elements[1] * Right.Columns[1].Y;
    Result.Z += Left.Elements[1] * Right.Columns[1].Z;
    Result.W += Left.Elements[1] * Right.Columns[1].W;

    Result.X += Left.Elements[2] * Right.Columns[2].X;
    Result.Y += Left.Elements[2] * Right.Columns[2].Y;
    Result.Z += Left.Elements[2] * Right.Columns[2].Z;
    Result.W += Left.Elements[2] * Right.Columns[2].W;

    Result.X += Left.Elements[3] * Right.Columns[3].X;
    Result.Y += Left.Elements[3] * Right.Columns[3].Y;
    Result.Z += Left.Elements[3] * Right.Columns[3].Z;
    Result.W += Left.Elements[3] * Right.Columns[3].W;
#endif

    return Result;
}

/*
 * 2x2 Matrices
 */

COVERAGE(HMM_M2, 1)
static inline HMM_Mat2 HMM_M2(void)
{
    ASSERT_COVERED(HMM_M2);
    HMM_Mat2 Result = {0};
    return Result;
}

COVERAGE(HMM_M2D, 1)
static inline HMM_Mat2 HMM_M2D(float Diagonal)
{
    ASSERT_COVERED(HMM_M2D);

    HMM_Mat2 Result = {0};
    Result.Elements[0][0] = Diagonal;
    Result.Elements[1][1] = Diagonal;

    return Result;
}

COVERAGE(HMM_TransposeM2, 1)
static inline HMM_Mat2 HMM_TransposeM2(HMM_Mat2 Matrix)
{
    ASSERT_COVERED(HMM_TransposeM2);

    HMM_Mat2 Result = Matrix;

    Result.Elements[0][1] = Matrix.Elements[1][0];
    Result.Elements[1][0] = Matrix.Elements[0][1];

    return Result;
}

COVERAGE(HMM_AddM2, 1)
static inline HMM_Mat2 HMM_AddM2(HMM_Mat2 Left, HMM_Mat2 Right)
{
    ASSERT_COVERED(HMM_AddM2);

    HMM_Mat2 Result;

    Result.Elements[0][0] = Left.Elements[0][0] + Right.Elements[0][0];
    Result.Elements[0][1] = Left.Elements[0][1] + Right.Elements[0][1];
    Result.Elements[1][0] = Left.Elements[1][0] + Right.Elements[1][0];
    Result.Elements[1][1] = Left.Elements[1][1] + Right.Elements[1][1];

    return Result;
}

COVERAGE(HMM_SubM2, 1)
static inline HMM_Mat2 HMM_SubM2(HMM_Mat2 Left, HMM_Mat2 Right)
{
    ASSERT_COVERED(HMM_SubM2);

    HMM_Mat2 Result;

    Result.Elements[0][0] = Left.Elements[0][0] - Right.Elements[0][0];
    Result.Elements[0][1] = Left.Elements[0][1] - Right.Elements[0][1];
    Result.Elements[1][0] = Left.Elements[1][0] - Right.Elements[1][0];
    Result.Elements[1][1] = Left.Elements[1][1] - Right.Elements[1][1];

    return Result;
}

COVERAGE(HMM_MulM2V2, 1)
static inline HMM_Vec2 HMM_MulM2V2(HMM_Mat2 Matrix, HMM_Vec2 Vector)
{
    ASSERT_COVERED(HMM_MulM2V2);

    HMM_Vec2 Result;

    Result.X = Vector.Elements[0] * Matrix.Columns[0].X;
    Result.Y = Vector.Elements[0] * Matrix.Columns[0].Y;

    Result.X += Vector.Elements[1] * Matrix.Columns[1].X;
    Result.Y += Vector.Elements[1] * Matrix.Columns[1].Y;

    return Result;
}

COVERAGE(HMM_MulM2, 1)
static inline HMM_Mat2 HMM_MulM2(HMM_Mat2 Left, HMM_Mat2 Right)
{
    ASSERT_COVERED(HMM_MulM2);

    HMM_Mat2 Result;
    Result.Columns[0] = HMM_MulM2V2(Left, Right.Columns[0]);
    Result.Columns[1] = HMM_MulM2V2(Left, Right.Columns[1]);

    return Result;
}

COVERAGE(HMM_MulM2F, 1)
static inline HMM_Mat2 HMM_MulM2F(HMM_Mat2 Matrix, float Scalar)
{
    ASSERT_COVERED(HMM_MulM2F);

    HMM_Mat2 Result;

    Result.Elements[0][0] = Matrix.Elements[0][0] * Scalar;
    Result.Elements[0][1] = Matrix.Elements[0][1] * Scalar;
    Result.Elements[1][0] = Matrix.Elements[1][0] * Scalar;
    Result.Elements[1][1] = Matrix.Elements[1][1] * Scalar;

    return Result;
}

COVERAGE(HMM_DivM2F, 1)
static inline HMM_Mat2 HMM_DivM2F(HMM_Mat2 Matrix, float Scalar)
{
    ASSERT_COVERED(HMM_DivM2F);

    HMM_Mat2 Result;

    Result.Elements[0][0] = Matrix.Elements[0][0] / Scalar;
    Result.Elements[0][1] = Matrix.Elements[0][1] / Scalar;
    Result.Elements[1][0] = Matrix.Elements[1][0] / Scalar;
    Result.Elements[1][1] = Matrix.Elements[1][1] / Scalar;

    return Result;
}

COVERAGE(HMM_DeterminantM2, 1)
static inline float HMM_DeterminantM2(HMM_Mat2 Matrix)
{
    ASSERT_COVERED(HMM_DeterminantM2);
    return Matrix.Elements[0][0]*Matrix.Elements[1][1] - Matrix.Elements[0][1]*Matrix.Elements[1][0];
}


COVERAGE(HMM_InvGeneralM2, 1)
static inline HMM_Mat2 HMM_InvGeneralM2(HMM_Mat2 Matrix)
{
    ASSERT_COVERED(HMM_InvGeneralM2);

    HMM_Mat2 Result;
    float InvDeterminant = 1.0f / HMM_DeterminantM2(Matrix);
    Result.Elements[0][0] = InvDeterminant * +Matrix.Elements[1][1];
    Result.Elements[1][1] = InvDeterminant * +Matrix.Elements[0][0];
    Result.Elements[0][1] = InvDeterminant * -Matrix.Elements[0][1];
    Result.Elements[1][0] = InvDeterminant * -Matrix.Elements[1][0];

    return Result;
}

/*
 * 3x3 Matrices
 */

COVERAGE(HMM_M3, 1)
static inline HMM_Mat3 HMM_M3(void)
{
    ASSERT_COVERED(HMM_M3);
    HMM_Mat3 Result = {0};
    return Result;
}

COVERAGE(HMM_M3D, 1)
static inline HMM_Mat3 HMM_M3D(float Diagonal)
{
    ASSERT_COVERED(HMM_M3D);

    HMM_Mat3 Result = {0};
    Result.Elements[0][0] = Diagonal;
    Result.Elements[1][1] = Diagonal;
    Result.Elements[2][2] = Diagonal;

    return Result;
}

COVERAGE(HMM_TransposeM3, 1)
static inline HMM_Mat3 HMM_TransposeM3(HMM_Mat3 Matrix)
{
    ASSERT_COVERED(HMM_TransposeM3);

    HMM_Mat3 Result = Matrix;

    Result.Elements[0][1] = Matrix.Elements[1][0];
    Result.Elements[0][2] = Matrix.Elements[2][0];
    Result.Elements[1][0] = Matrix.Elements[0][1];
    Result.Elements[1][2] = Matrix.Elements[2][1];
    Result.Elements[2][1] = Matrix.Elements[1][2];
    Result.Elements[2][0] = Matrix.Elements[0][2];

    return Result;
}

COVERAGE(HMM_AddM3, 1)
static inline HMM_Mat3 HMM_AddM3(HMM_Mat3 Left, HMM_Mat3 Right)
{
    ASSERT_COVERED(HMM_AddM3);

    HMM_Mat3 Result;

    Result.Elements[0][0] = Left.Elements[0][0] + Right.Elements[0][0];
    Result.Elements[0][1] = Left.Elements[0][1] + Right.Elements[0][1];
    Result.Elements[0][2] = Left.Elements[0][2] + Right.Elements[0][2];
    Result.Elements[1][0] = Left.Elements[1][0] + Right.Elements[1][0];
    Result.Elements[1][1] = Left.Elements[1][1] + Right.Elements[1][1];
    Result.Elements[1][2] = Left.Elements[1][2] + Right.Elements[1][2];
    Result.Elements[2][0] = Left.Elements[2][0] + Right.Elements[2][0];
    Result.Elements[2][1] = Left.Elements[2][1] + Right.Elements[2][1];
    Result.Elements[2][2] = Left.Elements[2][2] + Right.Elements[2][2];

    return Result;
}

COVERAGE(HMM_SubM3, 1)
static inline HMM_Mat3 HMM_SubM3(HMM_Mat3 Left, HMM_Mat3 Right)
{
    ASSERT_COVERED(HMM_SubM3);

    HMM_Mat3 Result;

    Result.Elements[0][0] = Left.Elements[0][0] - Right.Elements[0][0];
    Result.Elements[0][1] = Left.Elements[0][1] - Right.Elements[0][1];
    Result.Elements[0][2] = Left.Elements[0][2] - Right.Elements[0][2];
    Result.Elements[1][0] = Left.Elements[1][0] - Right.Elements[1][0];
    Result.Elements[1][1] = Left.Elements[1][1] - Right.Elements[1][1];
    Result.Elements[1][2] = Left.Elements[1][2] - Right.Elements[1][2];
    Result.Elements[2][0] = Left.Elements[2][0] - Right.Elements[2][0];
    Result.Elements[2][1] = Left.Elements[2][1] - Right.Elements[2][1];
    Result.Elements[2][2] = Left.Elements[2][2] - Right.Elements[2][2];

    return Result;
}

COVERAGE(HMM_MulM3V3, 1)
static inline HMM_Vec3 HMM_MulM3V3(HMM_Mat3 Matrix, HMM_Vec3 Vector)
{
    ASSERT_COVERED(HMM_MulM3V3);

    HMM_Vec3 Result;

    Result.X = Vector.Elements[0] * Matrix.Columns[0].X;
    Result.Y = Vector.Elements[0] * Matrix.Columns[0].Y;
    Result.Z = Vector.Elements[0] * Matrix.Columns[0].Z;

    Result.X += Vector.Elements[1] * Matrix.Columns[1].X;
    Result.Y += Vector.Elements[1] * Matrix.Columns[1].Y;
    Result.Z += Vector.Elements[1] * Matrix.Columns[1].Z;

    Result.X += Vector.Elements[2] * Matrix.Columns[2].X;
    Result.Y += Vector.Elements[2] * Matrix.Columns[2].Y;
    Result.Z += Vector.Elements[2] * Matrix.Columns[2].Z;

    return Result;
}

COVERAGE(HMM_MulM3, 1)
static inline HMM_Mat3 HMM_MulM3(HMM_Mat3 Left, HMM_Mat3 Right)
{
    ASSERT_COVERED(HMM_MulM3);

    HMM_Mat3 Result;
    Result.Columns[0] = HMM_MulM3V3(Left, Right.Columns[0]);
    Result.Columns[1] = HMM_MulM3V3(Left, Right.Columns[1]);
    Result.Columns[2] = HMM_MulM3V3(Left, Right.Columns[2]);

    return Result;
}

COVERAGE(HMM_MulM3F, 1)
static inline HMM_Mat3 HMM_MulM3F(HMM_Mat3 Matrix, float Scalar)
{
    ASSERT_COVERED(HMM_MulM3F);

    HMM_Mat3 Result;

    Result.Elements[0][0] = Matrix.Elements[0][0] * Scalar;
    Result.Elements[0][1] = Matrix.Elements[0][1] * Scalar;
    Result.Elements[0][2] = Matrix.Elements[0][2] * Scalar;
    Result.Elements[1][0] = Matrix.Elements[1][0] * Scalar;
    Result.Elements[1][1] = Matrix.Elements[1][1] * Scalar;
    Result.Elements[1][2] = Matrix.Elements[1][2] * Scalar;
    Result.Elements[2][0] = Matrix.Elements[2][0] * Scalar;
    Result.Elements[2][1] = Matrix.Elements[2][1] * Scalar;
    Result.Elements[2][2] = Matrix.Elements[2][2] * Scalar;

    return Result;
}

COVERAGE(HMM_DivM3, 1)
static inline HMM_Mat3 HMM_DivM3F(HMM_Mat3 Matrix, float Scalar)
{
    ASSERT_COVERED(HMM_DivM3);

    HMM_Mat3 Result;

    Result.Elements[0][0] = Matrix.Elements[0][0] / Scalar;
    Result.Elements[0][1] = Matrix.Elements[0][1] / Scalar;
    Result.Elements[0][2] = Matrix.Elements[0][2] / Scalar;
    Result.Elements[1][0] = Matrix.Elements[1][0] / Scalar;
    Result.Elements[1][1] = Matrix.Elements[1][1] / Scalar;
    Result.Elements[1][2] = Matrix.Elements[1][2] / Scalar;
    Result.Elements[2][0] = Matrix.Elements[2][0] / Scalar;
    Result.Elements[2][1] = Matrix.Elements[2][1] / Scalar;
    Result.Elements[2][2] = Matrix.Elements[2][2] / Scalar;

    return Result;
}

COVERAGE(HMM_DeterminantM3, 1)
static inline float HMM_DeterminantM3(HMM_Mat3 Matrix)
{
    ASSERT_COVERED(HMM_DeterminantM3);

    HMM_Mat3 Cross;
    Cross.Columns[0] = HMM_Cross(Matrix.Columns[1], Matrix.Columns[2]);
    Cross.Columns[1] = HMM_Cross(Matrix.Columns[2], Matrix.Columns[0]);
    Cross.Columns[2] = HMM_Cross(Matrix.Columns[0], Matrix.Columns[1]);

    return HMM_DotV3(Cross.Columns[2], Matrix.Columns[2]);
}

COVERAGE(HMM_InvGeneralM3, 1)
static inline HMM_Mat3 HMM_InvGeneralM3(HMM_Mat3 Matrix)
{
    ASSERT_COVERED(HMM_InvGeneralM3);

    HMM_Mat3 Cross;
    Cross.Columns[0] = HMM_Cross(Matrix.Columns[1], Matrix.Columns[2]);
    Cross.Columns[1] = HMM_Cross(Matrix.Columns[2], Matrix.Columns[0]);
    Cross.Columns[2] = HMM_Cross(Matrix.Columns[0], Matrix.Columns[1]);

    float InvDeterminant = 1.0f / HMM_DotV3(Cross.Columns[2], Matrix.Columns[2]);

    HMM_Mat3 Result;
    Result.Columns[0] = HMM_MulV3F(Cross.Columns[0], InvDeterminant);
    Result.Columns[1] = HMM_MulV3F(Cross.Columns[1], InvDeterminant);
    Result.Columns[2] = HMM_MulV3F(Cross.Columns[2], InvDeterminant);

    return HMM_TransposeM3(Result);
}

/*
 * 4x4 Matrices
 */

COVERAGE(HMM_M4, 1)
static inline HMM_Mat4 HMM_M4(void)
{
    ASSERT_COVERED(HMM_M4);
    HMM_Mat4 Result = {0};
    return Result;
}

COVERAGE(HMM_M4D, 1)
static inline HMM_Mat4 HMM_M4D(float Diagonal)
{
    ASSERT_COVERED(HMM_M4D);

    HMM_Mat4 Result = {0};
    Result.Elements[0][0] = Diagonal;
    Result.Elements[1][1] = Diagonal;
    Result.Elements[2][2] = Diagonal;
    Result.Elements[3][3] = Diagonal;

    return Result;
}

COVERAGE(HMM_TransposeM4, 1)
static inline HMM_Mat4 HMM_TransposeM4(HMM_Mat4 Matrix)
{
    ASSERT_COVERED(HMM_TransposeM4);

    HMM_Mat4 Result;
#ifdef HANDMADE_MATH__USE_SSE
    Result = Matrix;
    _MM_TRANSPOSE4_PS(Result.Columns[0].SSE, Result.Columns[1].SSE, Result.Columns[2].SSE, Result.Columns[3].SSE);
#elif defined(HANDMADE_MATH__USE_NEON)
    float32x4x4_t Transposed = vld4q_f32((float*)Matrix.Columns);
    Result.Columns[0].NEON = Transposed.val[0];
    Result.Columns[1].NEON = Transposed.val[1];
    Result.Columns[2].NEON = Transposed.val[2];
    Result.Columns[3].NEON = Transposed.val[3];
#else
    Result.Elements[0][0] = Matrix.Elements[0][0];
    Result.Elements[0][1] = Matrix.Elements[1][0];
    Result.Elements[0][2] = Matrix.Elements[2][0];
    Result.Elements[0][3] = Matrix.Elements[3][0];
    Result.Elements[1][0] = Matrix.Elements[0][1];
    Result.Elements[1][1] = Matrix.Elements[1][1];
    Result.Elements[1][2] = Matrix.Elements[2][1];
    Result.Elements[1][3] = Matrix.Elements[3][1];
    Result.Elements[2][0] = Matrix.Elements[0][2];
    Result.Elements[2][1] = Matrix.Elements[1][2];
    Result.Elements[2][2] = Matrix.Elements[2][2];
    Result.Elements[2][3] = Matrix.Elements[3][2];
    Result.Elements[3][0] = Matrix.Elements[0][3];
    Result.Elements[3][1] = Matrix.Elements[1][3];
    Result.Elements[3][2] = Matrix.Elements[2][3];
    Result.Elements[3][3] = Matrix.Elements[3][3];
#endif

    return Result;
}

COVERAGE(HMM_AddM4, 1)
static inline HMM_Mat4 HMM_AddM4(HMM_Mat4 Left, HMM_Mat4 Right)
{
    ASSERT_COVERED(HMM_AddM4);

    HMM_Mat4 Result;

    Result.Columns[0] = HMM_AddV4(Left.Columns[0], Right.Columns[0]);
    Result.Columns[1] = HMM_AddV4(Left.Columns[1], Right.Columns[1]);
    Result.Columns[2] = HMM_AddV4(Left.Columns[2], Right.Columns[2]);
    Result.Columns[3] = HMM_AddV4(Left.Columns[3], Right.Columns[3]);

    return Result;
}

COVERAGE(HMM_SubM4, 1)
static inline HMM_Mat4 HMM_SubM4(HMM_Mat4 Left, HMM_Mat4 Right)
{
    ASSERT_COVERED(HMM_SubM4);

    HMM_Mat4 Result;

    Result.Columns[0] = HMM_SubV4(Left.Columns[0], Right.Columns[0]);
    Result.Columns[1] = HMM_SubV4(Left.Columns[1], Right.Columns[1]);
    Result.Columns[2] = HMM_SubV4(Left.Columns[2], Right.Columns[2]);
    Result.Columns[3] = HMM_SubV4(Left.Columns[3], Right.Columns[3]);

    return Result;
}

COVERAGE(HMM_MulM4, 1)
static inline HMM_Mat4 HMM_MulM4(HMM_Mat4 Left, HMM_Mat4 Right)
{
    ASSERT_COVERED(HMM_MulM4);

    HMM_Mat4 Result;
    Result.Columns[0] = HMM_LinearCombineV4M4(Right.Columns[0], Left);
    Result.Columns[1] = HMM_LinearCombineV4M4(Right.Columns[1], Left);
    Result.Columns[2] = HMM_LinearCombineV4M4(Right.Columns[2], Left);
    Result.Columns[3] = HMM_LinearCombineV4M4(Right.Columns[3], Left);

    return Result;
}

COVERAGE(HMM_MulM4F, 1)
static inline HMM_Mat4 HMM_MulM4F(HMM_Mat4 Matrix, float Scalar)
{
    ASSERT_COVERED(HMM_MulM4F);

    HMM_Mat4 Result;


#ifdef HANDMADE_MATH__USE_SSE
    __m128 SSEScalar = _mm_set1_ps(Scalar);
    Result.Columns[0].SSE = _mm_mul_ps(Matrix.Columns[0].SSE, SSEScalar);
    Result.Columns[1].SSE = _mm_mul_ps(Matrix.Columns[1].SSE, SSEScalar);
    Result.Columns[2].SSE = _mm_mul_ps(Matrix.Columns[2].SSE, SSEScalar);
    Result.Columns[3].SSE = _mm_mul_ps(Matrix.Columns[3].SSE, SSEScalar);
#elif defined(HANDMADE_MATH__USE_NEON)
    Result.Columns[0].NEON = vmulq_n_f32(Matrix.Columns[0].NEON, Scalar);
    Result.Columns[1].NEON = vmulq_n_f32(Matrix.Columns[1].NEON, Scalar);
    Result.Columns[2].NEON = vmulq_n_f32(Matrix.Columns[2].NEON, Scalar);
    Result.Columns[3].NEON = vmulq_n_f32(Matrix.Columns[3].NEON, Scalar);
#else
    Result.Elements[0][0] = Matrix.Elements[0][0] * Scalar;
    Result.Elements[0][1] = Matrix.Elements[0][1] * Scalar;
    Result.Elements[0][2] = Matrix.Elements[0][2] * Scalar;
    Result.Elements[0][3] = Matrix.Elements[0][3] * Scalar;
    Result.Elements[1][0] = Matrix.Elements[1][0] * Scalar;
    Result.Elements[1][1] = Matrix.Elements[1][1] * Scalar;
    Result.Elements[1][2] = Matrix.Elements[1][2] * Scalar;
    Result.Elements[1][3] = Matrix.Elements[1][3] * Scalar;
    Result.Elements[2][0] = Matrix.Elements[2][0] * Scalar;
    Result.Elements[2][1] = Matrix.Elements[2][1] * Scalar;
    Result.Elements[2][2] = Matrix.Elements[2][2] * Scalar;
    Result.Elements[2][3] = Matrix.Elements[2][3] * Scalar;
    Result.Elements[3][0] = Matrix.Elements[3][0] * Scalar;
    Result.Elements[3][1] = Matrix.Elements[3][1] * Scalar;
    Result.Elements[3][2] = Matrix.Elements[3][2] * Scalar;
    Result.Elements[3][3] = Matrix.Elements[3][3] * Scalar;
#endif

    return Result;
}

COVERAGE(HMM_MulM4V4, 1)
static inline HMM_Vec4 HMM_MulM4V4(HMM_Mat4 Matrix, HMM_Vec4 Vector)
{
    ASSERT_COVERED(HMM_MulM4V4);
    return HMM_LinearCombineV4M4(Vector, Matrix);
}

COVERAGE(HMM_DivM4F, 1)
static inline HMM_Mat4 HMM_DivM4F(HMM_Mat4 Matrix, float Scalar)
{
    ASSERT_COVERED(HMM_DivM4F);

    HMM_Mat4 Result;

#ifdef HANDMADE_MATH__USE_SSE
    __m128 SSEScalar = _mm_set1_ps(Scalar);
    Result.Columns[0].SSE = _mm_div_ps(Matrix.Columns[0].SSE, SSEScalar);
    Result.Columns[1].SSE = _mm_div_ps(Matrix.Columns[1].SSE, SSEScalar);
    Result.Columns[2].SSE = _mm_div_ps(Matrix.Columns[2].SSE, SSEScalar);
    Result.Columns[3].SSE = _mm_div_ps(Matrix.Columns[3].SSE, SSEScalar);
#elif defined(HANDMADE_MATH__USE_NEON)
    float32x4_t NEONScalar = vdupq_n_f32(Scalar);
    Result.Columns[0].NEON = vdivq_f32(Matrix.Columns[0].NEON, NEONScalar);
    Result.Columns[1].NEON = vdivq_f32(Matrix.Columns[1].NEON, NEONScalar);
    Result.Columns[2].NEON = vdivq_f32(Matrix.Columns[2].NEON, NEONScalar);
    Result.Columns[3].NEON = vdivq_f32(Matrix.Columns[3].NEON, NEONScalar);
#else
    Result.Elements[0][0] = Matrix.Elements[0][0] / Scalar;
    Result.Elements[0][1] = Matrix.Elements[0][1] / Scalar;
    Result.Elements[0][2] = Matrix.Elements[0][2] / Scalar;
    Result.Elements[0][3] = Matrix.Elements[0][3] / Scalar;
    Result.Elements[1][0] = Matrix.Elements[1][0] / Scalar;
    Result.Elements[1][1] = Matrix.Elements[1][1] / Scalar;
    Result.Elements[1][2] = Matrix.Elements[1][2] / Scalar;
    Result.Elements[1][3] = Matrix.Elements[1][3] / Scalar;
    Result.Elements[2][0] = Matrix.Elements[2][0] / Scalar;
    Result.Elements[2][1] = Matrix.Elements[2][1] / Scalar;
    Result.Elements[2][2] = Matrix.Elements[2][2] / Scalar;
    Result.Elements[2][3] = Matrix.Elements[2][3] / Scalar;
    Result.Elements[3][0] = Matrix.Elements[3][0] / Scalar;
    Result.Elements[3][1] = Matrix.Elements[3][1] / Scalar;
    Result.Elements[3][2] = Matrix.Elements[3][2] / Scalar;
    Result.Elements[3][3] = Matrix.Elements[3][3] / Scalar;
#endif

    return Result;
}

COVERAGE(HMM_DeterminantM4, 1)
static inline float HMM_DeterminantM4(HMM_Mat4 Matrix)
{
    ASSERT_COVERED(HMM_DeterminantM4);

    HMM_Vec3 C01 = HMM_Cross(Matrix.Columns[0].XYZ, Matrix.Columns[1].XYZ);
    HMM_Vec3 C23 = HMM_Cross(Matrix.Columns[2].XYZ, Matrix.Columns[3].XYZ);
    HMM_Vec3 B10 = HMM_SubV3(HMM_MulV3F(Matrix.Columns[0].XYZ, Matrix.Columns[1].W), HMM_MulV3F(Matrix.Columns[1].XYZ, Matrix.Columns[0].W));
    HMM_Vec3 B32 = HMM_SubV3(HMM_MulV3F(Matrix.Columns[2].XYZ, Matrix.Columns[3].W), HMM_MulV3F(Matrix.Columns[3].XYZ, Matrix.Columns[2].W));

    return HMM_DotV3(C01, B32) + HMM_DotV3(C23, B10);
}

COVERAGE(HMM_InvGeneralM4, 1)
// Returns a general-purpose inverse of an HMM_Mat4. Note that special-purpose inverses of many transformations
// are available and will be more efficient.
static inline HMM_Mat4 HMM_InvGeneralM4(HMM_Mat4 Matrix)
{
    ASSERT_COVERED(HMM_InvGeneralM4);

    HMM_Vec3 C01 = HMM_Cross(Matrix.Columns[0].XYZ, Matrix.Columns[1].XYZ);
    HMM_Vec3 C23 = HMM_Cross(Matrix.Columns[2].XYZ, Matrix.Columns[3].XYZ);
    HMM_Vec3 B10 = HMM_SubV3(HMM_MulV3F(Matrix.Columns[0].XYZ, Matrix.Columns[1].W), HMM_MulV3F(Matrix.Columns[1].XYZ, Matrix.Columns[0].W));
    HMM_Vec3 B32 = HMM_SubV3(HMM_MulV3F(Matrix.Columns[2].XYZ, Matrix.Columns[3].W), HMM_MulV3F(Matrix.Columns[3].XYZ, Matrix.Columns[2].W));

    float InvDeterminant = 1.0f / (HMM_DotV3(C01, B32) + HMM_DotV3(C23, B10));
    C01 = HMM_MulV3F(C01, InvDeterminant);
    C23 = HMM_MulV3F(C23, InvDeterminant);
    B10 = HMM_MulV3F(B10, InvDeterminant);
    B32 = HMM_MulV3F(B32, InvDeterminant);

    HMM_Mat4 Result;
    Result.Columns[0] = HMM_V4V(HMM_AddV3(HMM_Cross(Matrix.Columns[1].XYZ, B32), HMM_MulV3F(C23, Matrix.Columns[1].W)), -HMM_DotV3(Matrix.Columns[1].XYZ, C23));
    Result.Columns[1] = HMM_V4V(HMM_SubV3(HMM_Cross(B32, Matrix.Columns[0].XYZ), HMM_MulV3F(C23, Matrix.Columns[0].W)), +HMM_DotV3(Matrix.Columns[0].XYZ, C23));
    Result.Columns[2] = HMM_V4V(HMM_AddV3(HMM_Cross(Matrix.Columns[3].XYZ, B10), HMM_MulV3F(C01, Matrix.Columns[3].W)), -HMM_DotV3(Matrix.Columns[3].XYZ, C01));
    Result.Columns[3] = HMM_V4V(HMM_SubV3(HMM_Cross(B10, Matrix.Columns[2].XYZ), HMM_MulV3F(C01, Matrix.Columns[2].W)), +HMM_DotV3(Matrix.Columns[2].XYZ, C01));

    return HMM_TransposeM4(Result);
}

/*
 * Common graphics transformations
 */

COVERAGE(HMM_Orthographic_RH_NO, 1)
// Produces a right-handed orthographic projection matrix with Z ranging from -1 to 1 (the GL convention).
// Left, Right, Bottom, and Top specify the coordinates of their respective clipping planes.
// Near and Far specify the distances to the near and far clipping planes.
static inline HMM_Mat4 HMM_Orthographic_RH_NO(float Left, float Right, float Bottom, float Top, float Near, float Far)
{
    ASSERT_COVERED(HMM_Orthographic_RH_NO);

    HMM_Mat4 Result = {0};

    Result.Elements[0][0] = 2.0f / (Right - Left);
    Result.Elements[1][1] = 2.0f / (Top - Bottom);
    Result.Elements[2][2] = 2.0f / (Near - Far);
    Result.Elements[3][3] = 1.0f;

    Result.Elements[3][0] = (Left + Right) / (Left - Right);
    Result.Elements[3][1] = (Bottom + Top) / (Bottom - Top);
    Result.Elements[3][2] = (Near + Far) / (Near - Far);

    return Result;
}

COVERAGE(HMM_Orthographic_RH_ZO, 1)
// Produces a right-handed orthographic projection matrix with Z ranging from 0 to 1 (the DirectX convention).
// Left, Right, Bottom, and Top specify the coordinates of their respective clipping planes.
// Near and Far specify the distances to the near and far clipping planes.
static inline HMM_Mat4 HMM_Orthographic_RH_ZO(float Left, float Right, float Bottom, float Top, float Near, float Far)
{
    ASSERT_COVERED(HMM_Orthographic_RH_ZO);

    HMM_Mat4 Result = {0};

    Result.Elements[0][0] = 2.0f / (Right - Left);
    Result.Elements[1][1] = 2.0f / (Top - Bottom);
    Result.Elements[2][2] = 1.0f / (Near - Far);
    Result.Elements[3][3] = 1.0f;

    Result.Elements[3][0] = (Left + Right) / (Left - Right);
    Result.Elements[3][1] = (Bottom + Top) / (Bottom - Top);
    Result.Elements[3][2] = (Near) / (Near - Far);

    return Result;
}

COVERAGE(HMM_Orthographic_LH_NO, 1)
// Produces a left-handed orthographic projection matrix with Z ranging from -1 to 1 (the GL convention).
// Left, Right, Bottom, and Top specify the coordinates of their respective clipping planes.
// Near and Far specify the distances to the near and far clipping planes.
static inline HMM_Mat4 HMM_Orthographic_LH_NO(float Left, float Right, float Bottom, float Top, float Near, float Far)
{
    ASSERT_COVERED(HMM_Orthographic_LH_NO);

    HMM_Mat4 Result = HMM_Orthographic_RH_NO(Left, Right, Bottom, Top, Near, Far);
    Result.Elements[2][2] = -Result.Elements[2][2];

    return Result;
}

COVERAGE(HMM_Orthographic_LH_ZO, 1)
// Produces a left-handed orthographic projection matrix with Z ranging from 0 to 1 (the DirectX convention).
// Left, Right, Bottom, and Top specify the coordinates of their respective clipping planes.
// Near and Far specify the distances to the near and far clipping planes.
static inline HMM_Mat4 HMM_Orthographic_LH_ZO(float Left, float Right, float Bottom, float Top, float Near, float Far)
{
    ASSERT_COVERED(HMM_Orthographic_LH_ZO);

    HMM_Mat4 Result = HMM_Orthographic_RH_ZO(Left, Right, Bottom, Top, Near, Far);
    Result.Elements[2][2] = -Result.Elements[2][2];

    return Result;
}

COVERAGE(HMM_InvOrthographic, 1)
// Returns an inverse for the given orthographic projection matrix. Works for all orthographic
// projection matrices, regardless of handedness or NDC convention.
static inline HMM_Mat4 HMM_InvOrthographic(HMM_Mat4 OrthoMatrix)
{
    ASSERT_COVERED(HMM_InvOrthographic);

    HMM_Mat4 Result = {0};
    Result.Elements[0][0] = 1.0f / OrthoMatrix.Elements[0][0];
    Result.Elements[1][1] = 1.0f / OrthoMatrix.Elements[1][1];
    Result.Elements[2][2] = 1.0f / OrthoMatrix.Elements[2][2];
    Result.Elements[3][3] = 1.0f;

    Result.Elements[3][0] = -OrthoMatrix.Elements[3][0] * Result.Elements[0][0];
    Result.Elements[3][1] = -OrthoMatrix.Elements[3][1] * Result.Elements[1][1];
    Result.Elements[3][2] = -OrthoMatrix.Elements[3][2] * Result.Elements[2][2];

    return Result;
}

COVERAGE(HMM_Perspective_RH_NO, 1)
static inline HMM_Mat4 HMM_Perspective_RH_NO(float FOV, float AspectRatio, float Near, float Far)
{
    ASSERT_COVERED(HMM_Perspective_RH_NO);

    HMM_Mat4 Result = {0};

    // See https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/gluPerspective.xml

    float Cotangent = 1.0f / HMM_TanF(FOV / 2.0f);
    Result.Elements[0][0] = Cotangent / AspectRatio;
    Result.Elements[1][1] = Cotangent;
    Result.Elements[2][3] = -1.0f;

    Result.Elements[2][2] = (Near + Far) / (Near - Far);
    Result.Elements[3][2] = (2.0f * Near * Far) / (Near - Far);

    return Result;
}

COVERAGE(HMM_Perspective_RH_ZO, 1)
static inline HMM_Mat4 HMM_Perspective_RH_ZO(float FOV, float AspectRatio, float Near, float Far)
{
    ASSERT_COVERED(HMM_Perspective_RH_ZO);

    HMM_Mat4 Result = {0};

    // See https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/gluPerspective.xml

    float Cotangent = 1.0f / HMM_TanF(FOV / 2.0f);
    Result.Elements[0][0] = Cotangent / AspectRatio;
    Result.Elements[1][1] = Cotangent;
    Result.Elements[2][3] = -1.0f;

    Result.Elements[2][2] = (Far) / (Near - Far);
    Result.Elements[3][2] = (Near * Far) / (Near - Far);

    return Result;
}

COVERAGE(HMM_Perspective_LH_NO, 1)
static inline HMM_Mat4 HMM_Perspective_LH_NO(float FOV, float AspectRatio, float Near, float Far)
{
    ASSERT_COVERED(HMM_Perspective_LH_NO);

    HMM_Mat4 Result = HMM_Perspective_RH_NO(FOV, AspectRatio, Near, Far);
    Result.Elements[2][2] = -Result.Elements[2][2];
    Result.Elements[2][3] = -Result.Elements[2][3];

    return Result;
}

COVERAGE(HMM_Perspective_LH_ZO, 1)
static inline HMM_Mat4 HMM_Perspective_LH_ZO(float FOV, float AspectRatio, float Near, float Far)
{
    ASSERT_COVERED(HMM_Perspective_LH_ZO);

    HMM_Mat4 Result = HMM_Perspective_RH_ZO(FOV, AspectRatio, Near, Far);
    Result.Elements[2][2] = -Result.Elements[2][2];
    Result.Elements[2][3] = -Result.Elements[2][3];

    return Result;
}

COVERAGE(HMM_InvPerspective_RH, 1)
static inline HMM_Mat4 HMM_InvPerspective_RH(HMM_Mat4 PerspectiveMatrix)
{
    ASSERT_COVERED(HMM_InvPerspective_RH);

    HMM_Mat4 Result = {0};
    Result.Elements[0][0] = 1.0f / PerspectiveMatrix.Elements[0][0];
    Result.Elements[1][1] = 1.0f / PerspectiveMatrix.Elements[1][1];
    Result.Elements[2][2] = 0.0f;

    Result.Elements[2][3] = 1.0f / PerspectiveMatrix.Elements[3][2];
    Result.Elements[3][3] = PerspectiveMatrix.Elements[2][2] * Result.Elements[2][3];
    Result.Elements[3][2] = PerspectiveMatrix.Elements[2][3];

    return Result;
}

COVERAGE(HMM_InvPerspective_LH, 1)
static inline HMM_Mat4 HMM_InvPerspective_LH(HMM_Mat4 PerspectiveMatrix)
{
    ASSERT_COVERED(HMM_InvPerspective_LH);

    HMM_Mat4 Result = {0};
    Result.Elements[0][0] = 1.0f / PerspectiveMatrix.Elements[0][0];
    Result.Elements[1][1] = 1.0f / PerspectiveMatrix.Elements[1][1];
    Result.Elements[2][2] = 0.0f;

    Result.Elements[2][3] = 1.0f / PerspectiveMatrix.Elements[3][2];
    Result.Elements[3][3] = PerspectiveMatrix.Elements[2][2] * -Result.Elements[2][3];
    Result.Elements[3][2] = PerspectiveMatrix.Elements[2][3];

    return Result;
}

COVERAGE(HMM_Translate, 1)
static inline HMM_Mat4 HMM_Translate(HMM_Vec3 Translation)
{
    ASSERT_COVERED(HMM_Translate);

    HMM_Mat4 Result = HMM_M4D(1.0f);
    Result.Elements[3][0] = Translation.X;
    Result.Elements[3][1] = Translation.Y;
    Result.Elements[3][2] = Translation.Z;

    return Result;
}

COVERAGE(HMM_InvTranslate, 1)
static inline HMM_Mat4 HMM_InvTranslate(HMM_Mat4 TranslationMatrix)
{
    ASSERT_COVERED(HMM_InvTranslate);

    HMM_Mat4 Result = TranslationMatrix;
    Result.Elements[3][0] = -Result.Elements[3][0];
    Result.Elements[3][1] = -Result.Elements[3][1];
    Result.Elements[3][2] = -Result.Elements[3][2];

    return Result;
}

COVERAGE(HMM_Rotate_RH, 1)
static inline HMM_Mat4 HMM_Rotate_RH(float Angle, HMM_Vec3 Axis)
{
    ASSERT_COVERED(HMM_Rotate_RH);

    HMM_Mat4 Result = HMM_M4D(1.0f);

    Axis = HMM_NormV3(Axis);

    float SinTheta = HMM_SinF(Angle);
    float CosTheta = HMM_CosF(Angle);
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

    return Result;
}

COVERAGE(HMM_Rotate_LH, 1)
static inline HMM_Mat4 HMM_Rotate_LH(float Angle, HMM_Vec3 Axis)
{
    ASSERT_COVERED(HMM_Rotate_LH);
    /* NOTE(lcf): Matrix will be inverse/transpose of RH. */
    return HMM_Rotate_RH(-Angle, Axis);
}

COVERAGE(HMM_InvRotate, 1)
static inline HMM_Mat4 HMM_InvRotate(HMM_Mat4 RotationMatrix)
{
    ASSERT_COVERED(HMM_InvRotate);
    return HMM_TransposeM4(RotationMatrix);
}

COVERAGE(HMM_Scale, 1)
static inline HMM_Mat4 HMM_Scale(HMM_Vec3 Scale)
{
    ASSERT_COVERED(HMM_Scale);

    HMM_Mat4 Result = HMM_M4D(1.0f);
    Result.Elements[0][0] = Scale.X;
    Result.Elements[1][1] = Scale.Y;
    Result.Elements[2][2] = Scale.Z;

    return Result;
}

COVERAGE(HMM_InvScale, 1)
static inline HMM_Mat4 HMM_InvScale(HMM_Mat4 ScaleMatrix)
{
    ASSERT_COVERED(HMM_InvScale);

    HMM_Mat4 Result = ScaleMatrix;
    Result.Elements[0][0] = 1.0f / Result.Elements[0][0];
    Result.Elements[1][1] = 1.0f / Result.Elements[1][1];
    Result.Elements[2][2] = 1.0f / Result.Elements[2][2];

    return Result;
}

static inline HMM_Mat4 _HMM_LookAt(HMM_Vec3 F,  HMM_Vec3 S, HMM_Vec3 U,  HMM_Vec3 Eye)
{
    HMM_Mat4 Result;

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

    Result.Elements[3][0] = -HMM_DotV3(S, Eye);
    Result.Elements[3][1] = -HMM_DotV3(U, Eye);
    Result.Elements[3][2] = HMM_DotV3(F, Eye);
    Result.Elements[3][3] = 1.0f;

    return Result;
}

COVERAGE(HMM_LookAt_RH, 1)
static inline HMM_Mat4 HMM_LookAt_RH(HMM_Vec3 Eye, HMM_Vec3 Center, HMM_Vec3 Up)
{
    ASSERT_COVERED(HMM_LookAt_RH);

    HMM_Vec3 F = HMM_NormV3(HMM_SubV3(Center, Eye));
    HMM_Vec3 S = HMM_NormV3(HMM_Cross(F, Up));
    HMM_Vec3 U = HMM_Cross(S, F);

    return _HMM_LookAt(F, S, U, Eye);
}

COVERAGE(HMM_LookAt_LH, 1)
static inline HMM_Mat4 HMM_LookAt_LH(HMM_Vec3 Eye, HMM_Vec3 Center, HMM_Vec3 Up)
{
    ASSERT_COVERED(HMM_LookAt_LH);

    HMM_Vec3 F = HMM_NormV3(HMM_SubV3(Eye, Center));
    HMM_Vec3 S = HMM_NormV3(HMM_Cross(F, Up));
    HMM_Vec3 U = HMM_Cross(S, F);

    return _HMM_LookAt(F, S, U, Eye);
}

COVERAGE(HMM_InvLookAt, 1)
static inline HMM_Mat4 HMM_InvLookAt(HMM_Mat4 Matrix)
{
    ASSERT_COVERED(HMM_InvLookAt);
    HMM_Mat4 Result;

    HMM_Mat3 Rotation = {0};
    Rotation.Columns[0] = Matrix.Columns[0].XYZ;
    Rotation.Columns[1] = Matrix.Columns[1].XYZ;
    Rotation.Columns[2] = Matrix.Columns[2].XYZ;
    Rotation = HMM_TransposeM3(Rotation);

    Result.Columns[0] = HMM_V4V(Rotation.Columns[0], 0.0f);
    Result.Columns[1] = HMM_V4V(Rotation.Columns[1], 0.0f);
    Result.Columns[2] = HMM_V4V(Rotation.Columns[2], 0.0f);
    Result.Columns[3] = HMM_MulV4F(Matrix.Columns[3], -1.0f);
    Result.Elements[3][0] = -1.0f * Matrix.Elements[3][0] /
        (Rotation.Elements[0][0] + Rotation.Elements[0][1] + Rotation.Elements[0][2]);
    Result.Elements[3][1] = -1.0f * Matrix.Elements[3][1] /
        (Rotation.Elements[1][0] + Rotation.Elements[1][1] + Rotation.Elements[1][2]);
    Result.Elements[3][2] = -1.0f * Matrix.Elements[3][2] /
        (Rotation.Elements[2][0] + Rotation.Elements[2][1] + Rotation.Elements[2][2]);
    Result.Elements[3][3] = 1.0f;

    return Result;
}

/*
 * Quaternion operations
 */

COVERAGE(HMM_Q, 1)
static inline HMM_Quat HMM_Q(float X, float Y, float Z, float W)
{
    ASSERT_COVERED(HMM_Q);

    HMM_Quat Result;

#ifdef HANDMADE_MATH__USE_SSE
    Result.SSE = _mm_setr_ps(X, Y, Z, W);
#elif defined(HANDMADE_MATH__USE_NEON)
    float32x4_t v = { X, Y, Z, W };
    Result.NEON = v;
#else
    Result.X = X;
    Result.Y = Y;
    Result.Z = Z;
    Result.W = W;
#endif

    return Result;
}

COVERAGE(HMM_QV4, 1)
static inline HMM_Quat HMM_QV4(HMM_Vec4 Vector)
{
    ASSERT_COVERED(HMM_QV4);

    HMM_Quat Result;

#ifdef HANDMADE_MATH__USE_SSE
    Result.SSE = Vector.SSE;
#elif defined(HANDMADE_MATH__USE_NEON)
    Result.NEON = Vector.NEON;
#else
    Result.X = Vector.X;
    Result.Y = Vector.Y;
    Result.Z = Vector.Z;
    Result.W = Vector.W;
#endif

    return Result;
}

COVERAGE(HMM_AddQ, 1)
static inline HMM_Quat HMM_AddQ(HMM_Quat Left, HMM_Quat Right)
{
    ASSERT_COVERED(HMM_AddQ);

    HMM_Quat Result;

#ifdef HANDMADE_MATH__USE_SSE
    Result.SSE = _mm_add_ps(Left.SSE, Right.SSE);
#elif defined(HANDMADE_MATH__USE_NEON)
    Result.NEON = vaddq_f32(Left.NEON, Right.NEON);
#else

    Result.X = Left.X + Right.X;
    Result.Y = Left.Y + Right.Y;
    Result.Z = Left.Z + Right.Z;
    Result.W = Left.W + Right.W;
#endif

    return Result;
}

COVERAGE(HMM_SubQ, 1)
static inline HMM_Quat HMM_SubQ(HMM_Quat Left, HMM_Quat Right)
{
    ASSERT_COVERED(HMM_SubQ);

    HMM_Quat Result;

#ifdef HANDMADE_MATH__USE_SSE
    Result.SSE = _mm_sub_ps(Left.SSE, Right.SSE);
#elif defined(HANDMADE_MATH__USE_NEON)
    Result.NEON = vsubq_f32(Left.NEON, Right.NEON);
#else
    Result.X = Left.X - Right.X;
    Result.Y = Left.Y - Right.Y;
    Result.Z = Left.Z - Right.Z;
    Result.W = Left.W - Right.W;
#endif

    return Result;
}

COVERAGE(HMM_MulQ, 1)
static inline HMM_Quat HMM_MulQ(HMM_Quat Left, HMM_Quat Right)
{
    ASSERT_COVERED(HMM_MulQ);

    HMM_Quat Result;

#ifdef HANDMADE_MATH__USE_SSE
    __m128 SSEResultOne = _mm_xor_ps(_mm_shuffle_ps(Left.SSE, Left.SSE, _MM_SHUFFLE(0, 0, 0, 0)), _mm_setr_ps(0.f, -0.f, 0.f, -0.f));
    __m128 SSEResultTwo = _mm_shuffle_ps(Right.SSE, Right.SSE, _MM_SHUFFLE(0, 1, 2, 3));
    __m128 SSEResultThree = _mm_mul_ps(SSEResultTwo, SSEResultOne);

    SSEResultOne = _mm_xor_ps(_mm_shuffle_ps(Left.SSE, Left.SSE, _MM_SHUFFLE(1, 1, 1, 1)) , _mm_setr_ps(0.f, 0.f, -0.f, -0.f));
    SSEResultTwo = _mm_shuffle_ps(Right.SSE, Right.SSE, _MM_SHUFFLE(1, 0, 3, 2));
    SSEResultThree = _mm_add_ps(SSEResultThree, _mm_mul_ps(SSEResultTwo, SSEResultOne));

    SSEResultOne = _mm_xor_ps(_mm_shuffle_ps(Left.SSE, Left.SSE, _MM_SHUFFLE(2, 2, 2, 2)), _mm_setr_ps(-0.f, 0.f, 0.f, -0.f));
    SSEResultTwo = _mm_shuffle_ps(Right.SSE, Right.SSE, _MM_SHUFFLE(2, 3, 0, 1));
    SSEResultThree = _mm_add_ps(SSEResultThree, _mm_mul_ps(SSEResultTwo, SSEResultOne));

    SSEResultOne = _mm_shuffle_ps(Left.SSE, Left.SSE, _MM_SHUFFLE(3, 3, 3, 3));
    SSEResultTwo = _mm_shuffle_ps(Right.SSE, Right.SSE, _MM_SHUFFLE(3, 2, 1, 0));
    Result.SSE = _mm_add_ps(SSEResultThree, _mm_mul_ps(SSEResultTwo, SSEResultOne));
#elif defined(HANDMADE_MATH__USE_NEON)
    float32x4_t Right1032 = vrev64q_f32(Right.NEON);
    float32x4_t Right3210 = vcombine_f32(vget_high_f32(Right1032), vget_low_f32(Right1032));
    float32x4_t Right2301 = vrev64q_f32(Right3210);

    float32x4_t FirstSign = {1.0f, -1.0f, 1.0f, -1.0f};
    Result.NEON = vmulq_f32(Right3210, vmulq_f32(vdupq_laneq_f32(Left.NEON, 0), FirstSign));
    float32x4_t SecondSign = {1.0f, 1.0f, -1.0f, -1.0f};
    Result.NEON = vfmaq_f32(Result.NEON, Right2301, vmulq_f32(vdupq_laneq_f32(Left.NEON, 1), SecondSign));
    float32x4_t ThirdSign = {-1.0f, 1.0f, 1.0f, -1.0f};
    Result.NEON = vfmaq_f32(Result.NEON, Right1032, vmulq_f32(vdupq_laneq_f32(Left.NEON, 2), ThirdSign));
    Result.NEON = vfmaq_laneq_f32(Result.NEON, Right.NEON, Left.NEON, 3);

#else
    Result.X =  Right.Elements[3] * +Left.Elements[0];
    Result.Y =  Right.Elements[2] * -Left.Elements[0];
    Result.Z =  Right.Elements[1] * +Left.Elements[0];
    Result.W =  Right.Elements[0] * -Left.Elements[0];

    Result.X += Right.Elements[2] * +Left.Elements[1];
    Result.Y += Right.Elements[3] * +Left.Elements[1];
    Result.Z += Right.Elements[0] * -Left.Elements[1];
    Result.W += Right.Elements[1] * -Left.Elements[1];

    Result.X += Right.Elements[1] * -Left.Elements[2];
    Result.Y += Right.Elements[0] * +Left.Elements[2];
    Result.Z += Right.Elements[3] * +Left.Elements[2];
    Result.W += Right.Elements[2] * -Left.Elements[2];

    Result.X += Right.Elements[0] * +Left.Elements[3];
    Result.Y += Right.Elements[1] * +Left.Elements[3];
    Result.Z += Right.Elements[2] * +Left.Elements[3];
    Result.W += Right.Elements[3] * +Left.Elements[3];
#endif

    return Result;
}

COVERAGE(HMM_MulQF, 1)
static inline HMM_Quat HMM_MulQF(HMM_Quat Left, float Multiplicative)
{
    ASSERT_COVERED(HMM_MulQF);

    HMM_Quat Result;

#ifdef HANDMADE_MATH__USE_SSE
    __m128 Scalar = _mm_set1_ps(Multiplicative);
    Result.SSE = _mm_mul_ps(Left.SSE, Scalar);
#elif defined(HANDMADE_MATH__USE_NEON)
    Result.NEON = vmulq_n_f32(Left.NEON, Multiplicative);
#else
    Result.X = Left.X * Multiplicative;
    Result.Y = Left.Y * Multiplicative;
    Result.Z = Left.Z * Multiplicative;
    Result.W = Left.W * Multiplicative;
#endif

    return Result;
}

COVERAGE(HMM_DivQF, 1)
static inline HMM_Quat HMM_DivQF(HMM_Quat Left, float Divnd)
{
    ASSERT_COVERED(HMM_DivQF);

    HMM_Quat Result;

#ifdef HANDMADE_MATH__USE_SSE
    __m128 Scalar = _mm_set1_ps(Divnd);
    Result.SSE = _mm_div_ps(Left.SSE, Scalar);
#elif defined(HANDMADE_MATH__USE_NEON)
    float32x4_t Scalar = vdupq_n_f32(Divnd);
    Result.NEON = vdivq_f32(Left.NEON, Scalar);
#else
    Result.X = Left.X / Divnd;
    Result.Y = Left.Y / Divnd;
    Result.Z = Left.Z / Divnd;
    Result.W = Left.W / Divnd;
#endif

    return Result;
}

COVERAGE(HMM_DotQ, 1)
static inline float HMM_DotQ(HMM_Quat Left, HMM_Quat Right)
{
    ASSERT_COVERED(HMM_DotQ);

    float Result;

#ifdef HANDMADE_MATH__USE_SSE
    __m128 SSEResultOne = _mm_mul_ps(Left.SSE, Right.SSE);
    __m128 SSEResultTwo = _mm_shuffle_ps(SSEResultOne, SSEResultOne, _MM_SHUFFLE(2, 3, 0, 1));
    SSEResultOne = _mm_add_ps(SSEResultOne, SSEResultTwo);
    SSEResultTwo = _mm_shuffle_ps(SSEResultOne, SSEResultOne, _MM_SHUFFLE(0, 1, 2, 3));
    SSEResultOne = _mm_add_ps(SSEResultOne, SSEResultTwo);
    _mm_store_ss(&Result, SSEResultOne);
#elif defined(HANDMADE_MATH__USE_NEON)
    float32x4_t NEONMultiplyResult = vmulq_f32(Left.NEON, Right.NEON);
    float32x4_t NEONHalfAdd = vpaddq_f32(NEONMultiplyResult, NEONMultiplyResult);
    float32x4_t NEONFullAdd = vpaddq_f32(NEONHalfAdd, NEONHalfAdd);
    Result = vgetq_lane_f32(NEONFullAdd, 0);
#else
    Result = ((Left.X * Right.X) + (Left.Z * Right.Z)) + ((Left.Y * Right.Y) + (Left.W * Right.W));
#endif

    return Result;
}

COVERAGE(HMM_InvQ, 1)
static inline HMM_Quat HMM_InvQ(HMM_Quat Left)
{
    ASSERT_COVERED(HMM_InvQ);

    HMM_Quat Result;
    Result.X = -Left.X;
    Result.Y = -Left.Y;
    Result.Z = -Left.Z;
    Result.W = Left.W;

    return HMM_DivQF(Result, (HMM_DotQ(Left, Left)));
}

COVERAGE(HMM_NormQ, 1)
static inline HMM_Quat HMM_NormQ(HMM_Quat Quat)
{
    ASSERT_COVERED(HMM_NormQ);

    /* NOTE(lcf): Take advantage of SSE implementation in HMM_NormV4 */
    HMM_Vec4 Vec = {Quat.X, Quat.Y, Quat.Z, Quat.W};
    Vec = HMM_NormV4(Vec);
    HMM_Quat Result = {Vec.X, Vec.Y, Vec.Z, Vec.W};

    return Result;
}

static inline HMM_Quat _HMM_MixQ(HMM_Quat Left, float MixLeft, HMM_Quat Right, float MixRight) {
    HMM_Quat Result;

#ifdef HANDMADE_MATH__USE_SSE
    __m128 ScalarLeft = _mm_set1_ps(MixLeft);
    __m128 ScalarRight = _mm_set1_ps(MixRight);
    __m128 SSEResultOne = _mm_mul_ps(Left.SSE, ScalarLeft);
    __m128 SSEResultTwo = _mm_mul_ps(Right.SSE, ScalarRight);
    Result.SSE = _mm_add_ps(SSEResultOne, SSEResultTwo);
#elif defined(HANDMADE_MATH__USE_NEON)
    float32x4_t ScaledLeft = vmulq_n_f32(Left.NEON, MixLeft);
    float32x4_t ScaledRight = vmulq_n_f32(Right.NEON, MixRight);
    Result.NEON = vaddq_f32(ScaledLeft, ScaledRight);
#else
    Result.X = Left.X*MixLeft + Right.X*MixRight;
    Result.Y = Left.Y*MixLeft + Right.Y*MixRight;
    Result.Z = Left.Z*MixLeft + Right.Z*MixRight;
    Result.W = Left.W*MixLeft + Right.W*MixRight;
#endif

    return Result;
}

COVERAGE(HMM_NLerp, 1)
static inline HMM_Quat HMM_NLerp(HMM_Quat Left, float Time, HMM_Quat Right)
{
    ASSERT_COVERED(HMM_NLerp);

    HMM_Quat Result = _HMM_MixQ(Left, 1.0f-Time, Right, Time);
    Result = HMM_NormQ(Result);

    return Result;
}

COVERAGE(HMM_SLerp, 1)
static inline HMM_Quat HMM_SLerp(HMM_Quat Left, float Time, HMM_Quat Right)
{
    ASSERT_COVERED(HMM_SLerp);

    HMM_Quat Result;

    float Cos_Theta = HMM_DotQ(Left, Right);

    if (Cos_Theta < 0.0f) { /* NOTE(lcf): Take shortest path on Hyper-sphere */
        Cos_Theta = -Cos_Theta;
        Right = HMM_Q(-Right.X, -Right.Y, -Right.Z, -Right.W);
    }

    /* NOTE(lcf): Use Normalized Linear interpolation when vectors are roughly not L.I. */
    if (Cos_Theta > 0.9995f) {
        Result = HMM_NLerp(Left, Time, Right);
    } else {
        float Angle = HMM_ACosF(Cos_Theta);
        float MixLeft = HMM_SinF((1.0f - Time) * Angle);
        float MixRight = HMM_SinF(Time * Angle);

        Result = _HMM_MixQ(Left, MixLeft, Right, MixRight);
        Result = HMM_NormQ(Result);
    }

    return Result;
}

COVERAGE(HMM_QToM4, 1)
static inline HMM_Mat4 HMM_QToM4(HMM_Quat Left)
{
    ASSERT_COVERED(HMM_QToM4);

    HMM_Mat4 Result;

    HMM_Quat NormalizedQ = HMM_NormQ(Left);

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

    return Result;
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
COVERAGE(HMM_M4ToQ_RH, 4)
static inline HMM_Quat HMM_M4ToQ_RH(HMM_Mat4 M)
{
    float T;
    HMM_Quat Q;

    if (M.Elements[2][2] < 0.0f) {
        if (M.Elements[0][0] > M.Elements[1][1]) {
            ASSERT_COVERED(HMM_M4ToQ_RH);

            T = 1 + M.Elements[0][0] - M.Elements[1][1] - M.Elements[2][2];
            Q = HMM_Q(
                T,
                M.Elements[0][1] + M.Elements[1][0],
                M.Elements[2][0] + M.Elements[0][2],
                M.Elements[1][2] - M.Elements[2][1]
            );
        } else {
            ASSERT_COVERED(HMM_M4ToQ_RH);

            T = 1 - M.Elements[0][0] + M.Elements[1][1] - M.Elements[2][2];
            Q = HMM_Q(
                M.Elements[0][1] + M.Elements[1][0],
                T,
                M.Elements[1][2] + M.Elements[2][1],
                M.Elements[2][0] - M.Elements[0][2]
            );
        }
    } else {
        if (M.Elements[0][0] < -M.Elements[1][1]) {
            ASSERT_COVERED(HMM_M4ToQ_RH);

            T = 1 - M.Elements[0][0] - M.Elements[1][1] + M.Elements[2][2];
            Q = HMM_Q(
                M.Elements[2][0] + M.Elements[0][2],
                M.Elements[1][2] + M.Elements[2][1],
                T,
                M.Elements[0][1] - M.Elements[1][0]
            );
        } else {
            ASSERT_COVERED(HMM_M4ToQ_RH);

            T = 1 + M.Elements[0][0] + M.Elements[1][1] + M.Elements[2][2];
            Q = HMM_Q(
                M.Elements[1][2] - M.Elements[2][1],
                M.Elements[2][0] - M.Elements[0][2],
                M.Elements[0][1] - M.Elements[1][0],
                T
            );
        }
    }

    Q = HMM_MulQF(Q, 0.5f / HMM_SqrtF(T));

    return Q;
}

COVERAGE(HMM_M4ToQ_LH, 4)
static inline HMM_Quat HMM_M4ToQ_LH(HMM_Mat4 M)
{
    float T;
    HMM_Quat Q;

    if (M.Elements[2][2] < 0.0f) {
        if (M.Elements[0][0] > M.Elements[1][1]) {
            ASSERT_COVERED(HMM_M4ToQ_LH);

            T = 1 + M.Elements[0][0] - M.Elements[1][1] - M.Elements[2][2];
            Q = HMM_Q(
                T,
                M.Elements[0][1] + M.Elements[1][0],
                M.Elements[2][0] + M.Elements[0][2],
                M.Elements[2][1] - M.Elements[1][2]
            );
        } else {
            ASSERT_COVERED(HMM_M4ToQ_LH);

            T = 1 - M.Elements[0][0] + M.Elements[1][1] - M.Elements[2][2];
            Q = HMM_Q(
                M.Elements[0][1] + M.Elements[1][0],
                T,
                M.Elements[1][2] + M.Elements[2][1],
                M.Elements[0][2] - M.Elements[2][0]
            );
        }
    } else {
        if (M.Elements[0][0] < -M.Elements[1][1]) {
            ASSERT_COVERED(HMM_M4ToQ_LH);

            T = 1 - M.Elements[0][0] - M.Elements[1][1] + M.Elements[2][2];
            Q = HMM_Q(
                M.Elements[2][0] + M.Elements[0][2],
                M.Elements[1][2] + M.Elements[2][1],
                T,
                M.Elements[1][0] - M.Elements[0][1]
            );
        } else {
            ASSERT_COVERED(HMM_M4ToQ_LH);

            T = 1 + M.Elements[0][0] + M.Elements[1][1] + M.Elements[2][2];
            Q = HMM_Q(
                M.Elements[2][1] - M.Elements[1][2],
                M.Elements[0][2] - M.Elements[2][0],
                M.Elements[1][0] - M.Elements[0][2],
                T
            );
        }
    }

    Q = HMM_MulQF(Q, 0.5f / HMM_SqrtF(T));

    return Q;
}


COVERAGE(HMM_QFromAxisAngle_RH, 1)
static inline HMM_Quat HMM_QFromAxisAngle_RH(HMM_Vec3 Axis, float Angle)
{
    ASSERT_COVERED(HMM_QFromAxisAngle_RH);

    HMM_Quat Result;

    HMM_Vec3 AxisNormalized = HMM_NormV3(Axis);
    float SineOfRotation = HMM_SinF(Angle / 2.0f);

    Result.XYZ = HMM_MulV3F(AxisNormalized, SineOfRotation);
    Result.W = HMM_CosF(Angle / 2.0f);

    return Result;
}

COVERAGE(HMM_QFromAxisAngle_LH, 1)
static inline HMM_Quat HMM_QFromAxisAngle_LH(HMM_Vec3 Axis, float Angle)
{
    ASSERT_COVERED(HMM_QFromAxisAngle_LH);

    return HMM_QFromAxisAngle_RH(Axis, -Angle);
}

COVERAGE(HMM_QFromNormPair, 1)
static inline HMM_Quat HMM_QFromNormPair(HMM_Vec3 Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_QFromNormPair);

    HMM_Quat Result;

    Result.XYZ = HMM_Cross(Left, Right);
    Result.W = 1.0f + HMM_DotV3(Left, Right);

    return HMM_NormQ(Result);
}

COVERAGE(HMM_QFromVecPair, 1)
static inline HMM_Quat HMM_QFromVecPair(HMM_Vec3 Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_QFromVecPair);

    return HMM_QFromNormPair(HMM_NormV3(Left), HMM_NormV3(Right));
}

COVERAGE(HMM_RotateV2, 1)
static inline HMM_Vec2 HMM_RotateV2(HMM_Vec2 V, float Angle)
{
    ASSERT_COVERED(HMM_RotateV2)

    float sinA = HMM_SinF(Angle);
    float cosA = HMM_CosF(Angle);

    return HMM_V2(V.X * cosA - V.Y * sinA, V.X * sinA + V.Y * cosA);
}

// implementation from
// https://blog.molecular-matters.com/2013/05/24/a-faster-quaternion-vector-multiplication/
COVERAGE(HMM_RotateV3Q, 1)
static inline HMM_Vec3 HMM_RotateV3Q(HMM_Vec3 V, HMM_Quat Q)
{
    ASSERT_COVERED(HMM_RotateV3Q);

    HMM_Vec3 t = HMM_MulV3F(HMM_Cross(Q.XYZ, V), 2);
    return HMM_AddV3(V, HMM_AddV3(HMM_MulV3F(t, Q.W), HMM_Cross(Q.XYZ, t)));
}

COVERAGE(HMM_RotateV3AxisAngle_LH, 1)
static inline HMM_Vec3 HMM_RotateV3AxisAngle_LH(HMM_Vec3 V, HMM_Vec3 Axis, float Angle) {
    ASSERT_COVERED(HMM_RotateV3AxisAngle_LH);

    return HMM_RotateV3Q(V, HMM_QFromAxisAngle_LH(Axis, Angle));
}

COVERAGE(HMM_RotateV3AxisAngle_RH, 1)
static inline HMM_Vec3 HMM_RotateV3AxisAngle_RH(HMM_Vec3 V, HMM_Vec3 Axis, float Angle) {
    ASSERT_COVERED(HMM_RotateV3AxisAngle_RH);

    return HMM_RotateV3Q(V, HMM_QFromAxisAngle_RH(Axis, Angle));
}


#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

COVERAGE(HMM_LenV2CPP, 1)
static inline float HMM_Len(HMM_Vec2 A)
{
    ASSERT_COVERED(HMM_LenV2CPP);
    return HMM_LenV2(A);
}

COVERAGE(HMM_LenV3CPP, 1)
static inline float HMM_Len(HMM_Vec3 A)
{
    ASSERT_COVERED(HMM_LenV3CPP);
    return HMM_LenV3(A);
}

COVERAGE(HMM_LenV4CPP, 1)
static inline float HMM_Len(HMM_Vec4 A)
{
    ASSERT_COVERED(HMM_LenV4CPP);
    return HMM_LenV4(A);
}

COVERAGE(HMM_LenSqrV2CPP, 1)
static inline float HMM_LenSqr(HMM_Vec2 A)
{
    ASSERT_COVERED(HMM_LenSqrV2CPP);
    return HMM_LenSqrV2(A);
}

COVERAGE(HMM_LenSqrV3CPP, 1)
static inline float HMM_LenSqr(HMM_Vec3 A)
{
    ASSERT_COVERED(HMM_LenSqrV3CPP);
    return HMM_LenSqrV3(A);
}

COVERAGE(HMM_LenSqrV4CPP, 1)
static inline float HMM_LenSqr(HMM_Vec4 A)
{
    ASSERT_COVERED(HMM_LenSqrV4CPP);
    return HMM_LenSqrV4(A);
}

COVERAGE(HMM_NormV2CPP, 1)
static inline HMM_Vec2 HMM_Norm(HMM_Vec2 A)
{
    ASSERT_COVERED(HMM_NormV2CPP);
    return HMM_NormV2(A);
}

COVERAGE(HMM_NormV3CPP, 1)
static inline HMM_Vec3 HMM_Norm(HMM_Vec3 A)
{
    ASSERT_COVERED(HMM_NormV3CPP);
    return HMM_NormV3(A);
}

COVERAGE(HMM_NormV4CPP, 1)
static inline HMM_Vec4 HMM_Norm(HMM_Vec4 A)
{
    ASSERT_COVERED(HMM_NormV4CPP);
    return HMM_NormV4(A);
}

COVERAGE(HMM_NormQCPP, 1)
static inline HMM_Quat HMM_Norm(HMM_Quat A)
{
    ASSERT_COVERED(HMM_NormQCPP);
    return HMM_NormQ(A);
}

COVERAGE(HMM_DotV2CPP, 1)
static inline float HMM_Dot(HMM_Vec2 Left, HMM_Vec2 VecTwo)
{
    ASSERT_COVERED(HMM_DotV2CPP);
    return HMM_DotV2(Left, VecTwo);
}

COVERAGE(HMM_DotV3CPP, 1)
static inline float HMM_Dot(HMM_Vec3 Left, HMM_Vec3 VecTwo)
{
    ASSERT_COVERED(HMM_DotV3CPP);
    return HMM_DotV3(Left, VecTwo);
}

COVERAGE(HMM_DotV4CPP, 1)
static inline float HMM_Dot(HMM_Vec4 Left, HMM_Vec4 VecTwo)
{
    ASSERT_COVERED(HMM_DotV4CPP);
    return HMM_DotV4(Left, VecTwo);
}

COVERAGE(HMM_LerpV2CPP, 1)
static inline HMM_Vec2 HMM_Lerp(HMM_Vec2 Left, float Time, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_LerpV2CPP);
    return HMM_LerpV2(Left, Time, Right);
}

COVERAGE(HMM_LerpV3CPP, 1)
static inline HMM_Vec3 HMM_Lerp(HMM_Vec3 Left, float Time, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_LerpV3CPP);
    return HMM_LerpV3(Left, Time, Right);
}

COVERAGE(HMM_LerpV4CPP, 1)
static inline HMM_Vec4 HMM_Lerp(HMM_Vec4 Left, float Time, HMM_Vec4 Right)
{
    ASSERT_COVERED(HMM_LerpV4CPP);
    return HMM_LerpV4(Left, Time, Right);
}

COVERAGE(HMM_TransposeM2CPP, 1)
static inline HMM_Mat2 HMM_Transpose(HMM_Mat2 Matrix)
{
    ASSERT_COVERED(HMM_TransposeM2CPP);
    return HMM_TransposeM2(Matrix);
}

COVERAGE(HMM_TransposeM3CPP, 1)
static inline HMM_Mat3 HMM_Transpose(HMM_Mat3 Matrix)
{
    ASSERT_COVERED(HMM_TransposeM3CPP);
    return HMM_TransposeM3(Matrix);
}

COVERAGE(HMM_TransposeM4CPP, 1)
static inline HMM_Mat4 HMM_Transpose(HMM_Mat4 Matrix)
{
    ASSERT_COVERED(HMM_TransposeM4CPP);
    return HMM_TransposeM4(Matrix);
}

COVERAGE(HMM_DeterminantM2CPP, 1)
static inline float HMM_Determinant(HMM_Mat2 Matrix)
{
    ASSERT_COVERED(HMM_DeterminantM2CPP);
    return HMM_DeterminantM2(Matrix);
}

COVERAGE(HMM_DeterminantM3CPP, 1)
static inline float HMM_Determinant(HMM_Mat3 Matrix)
{
    ASSERT_COVERED(HMM_DeterminantM3CPP);
    return HMM_DeterminantM3(Matrix);
}

COVERAGE(HMM_DeterminantM4CPP, 1)
static inline float HMM_Determinant(HMM_Mat4 Matrix)
{
    ASSERT_COVERED(HMM_DeterminantM4CPP);
    return HMM_DeterminantM4(Matrix);
}

COVERAGE(HMM_InvGeneralM2CPP, 1)
static inline HMM_Mat2 HMM_InvGeneral(HMM_Mat2 Matrix)
{
    ASSERT_COVERED(HMM_InvGeneralM2CPP);
    return HMM_InvGeneralM2(Matrix);
}

COVERAGE(HMM_InvGeneralM3CPP, 1)
static inline HMM_Mat3 HMM_InvGeneral(HMM_Mat3 Matrix)
{
    ASSERT_COVERED(HMM_InvGeneralM3CPP);
    return HMM_InvGeneralM3(Matrix);
}

COVERAGE(HMM_InvGeneralM4CPP, 1)
static inline HMM_Mat4 HMM_InvGeneral(HMM_Mat4 Matrix)
{
    ASSERT_COVERED(HMM_InvGeneralM4CPP);
    return HMM_InvGeneralM4(Matrix);
}

COVERAGE(HMM_DotQCPP, 1)
static inline float HMM_Dot(HMM_Quat QuatOne, HMM_Quat QuatTwo)
{
    ASSERT_COVERED(HMM_DotQCPP);
    return HMM_DotQ(QuatOne, QuatTwo);
}

COVERAGE(HMM_AddV2CPP, 1)
static inline HMM_Vec2 HMM_Add(HMM_Vec2 Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_AddV2CPP);
    return HMM_AddV2(Left, Right);
}

COVERAGE(HMM_AddV3CPP, 1)
static inline HMM_Vec3 HMM_Add(HMM_Vec3 Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_AddV3CPP);
    return HMM_AddV3(Left, Right);
}

COVERAGE(HMM_AddV4CPP, 1)
static inline HMM_Vec4 HMM_Add(HMM_Vec4 Left, HMM_Vec4 Right)
{
    ASSERT_COVERED(HMM_AddV4CPP);
    return HMM_AddV4(Left, Right);
}

COVERAGE(HMM_AddM2CPP, 1)
static inline HMM_Mat2 HMM_Add(HMM_Mat2 Left, HMM_Mat2 Right)
{
    ASSERT_COVERED(HMM_AddM2CPP);
    return HMM_AddM2(Left, Right);
}

COVERAGE(HMM_AddM3CPP, 1)
static inline HMM_Mat3 HMM_Add(HMM_Mat3 Left, HMM_Mat3 Right)
{
    ASSERT_COVERED(HMM_AddM3CPP);
    return HMM_AddM3(Left, Right);
}

COVERAGE(HMM_AddM4CPP, 1)
static inline HMM_Mat4 HMM_Add(HMM_Mat4 Left, HMM_Mat4 Right)
{
    ASSERT_COVERED(HMM_AddM4CPP);
    return HMM_AddM4(Left, Right);
}

COVERAGE(HMM_AddQCPP, 1)
static inline HMM_Quat HMM_Add(HMM_Quat Left, HMM_Quat Right)
{
    ASSERT_COVERED(HMM_AddQCPP);
    return HMM_AddQ(Left, Right);
}

COVERAGE(HMM_SubV2CPP, 1)
static inline HMM_Vec2 HMM_Sub(HMM_Vec2 Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_SubV2CPP);
    return HMM_SubV2(Left, Right);
}

COVERAGE(HMM_SubV3CPP, 1)
static inline HMM_Vec3 HMM_Sub(HMM_Vec3 Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_SubV3CPP);
    return HMM_SubV3(Left, Right);
}

COVERAGE(HMM_SubV4CPP, 1)
static inline HMM_Vec4 HMM_Sub(HMM_Vec4 Left, HMM_Vec4 Right)
{
    ASSERT_COVERED(HMM_SubV4CPP);
    return HMM_SubV4(Left, Right);
}

COVERAGE(HMM_SubM2CPP, 1)
static inline HMM_Mat2 HMM_Sub(HMM_Mat2 Left, HMM_Mat2 Right)
{
    ASSERT_COVERED(HMM_SubM2CPP);
    return HMM_SubM2(Left, Right);
}

COVERAGE(HMM_SubM3CPP, 1)
static inline HMM_Mat3 HMM_Sub(HMM_Mat3 Left, HMM_Mat3 Right)
{
    ASSERT_COVERED(HMM_SubM3CPP);
    return HMM_SubM3(Left, Right);
}

COVERAGE(HMM_SubM4CPP, 1)
static inline HMM_Mat4 HMM_Sub(HMM_Mat4 Left, HMM_Mat4 Right)
{
    ASSERT_COVERED(HMM_SubM4CPP);
    return HMM_SubM4(Left, Right);
}

COVERAGE(HMM_SubQCPP, 1)
static inline HMM_Quat HMM_Sub(HMM_Quat Left, HMM_Quat Right)
{
    ASSERT_COVERED(HMM_SubQCPP);
    return HMM_SubQ(Left, Right);
}

COVERAGE(HMM_MulV2CPP, 1)
static inline HMM_Vec2 HMM_Mul(HMM_Vec2 Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_MulV2CPP);
    return HMM_MulV2(Left, Right);
}

COVERAGE(HMM_MulV2FCPP, 1)
static inline HMM_Vec2 HMM_Mul(HMM_Vec2 Left, float Right)
{
    ASSERT_COVERED(HMM_MulV2FCPP);
    return HMM_MulV2F(Left, Right);
}

COVERAGE(HMM_MulV3CPP, 1)
static inline HMM_Vec3 HMM_Mul(HMM_Vec3 Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_MulV3CPP);
    return HMM_MulV3(Left, Right);
}

COVERAGE(HMM_MulV3FCPP, 1)
static inline HMM_Vec3 HMM_Mul(HMM_Vec3 Left, float Right)
{
    ASSERT_COVERED(HMM_MulV3FCPP);
    return HMM_MulV3F(Left, Right);
}

COVERAGE(HMM_MulV4CPP, 1)
static inline HMM_Vec4 HMM_Mul(HMM_Vec4 Left, HMM_Vec4 Right)
{
    ASSERT_COVERED(HMM_MulV4CPP);
    return HMM_MulV4(Left, Right);
}

COVERAGE(HMM_MulV4FCPP, 1)
static inline HMM_Vec4 HMM_Mul(HMM_Vec4 Left, float Right)
{
    ASSERT_COVERED(HMM_MulV4FCPP);
    return HMM_MulV4F(Left, Right);
}

COVERAGE(HMM_MulM2CPP, 1)
static inline HMM_Mat2 HMM_Mul(HMM_Mat2 Left, HMM_Mat2 Right)
{
    ASSERT_COVERED(HMM_MulM2CPP);
    return HMM_MulM2(Left, Right);
}

COVERAGE(HMM_MulM3CPP, 1)
static inline HMM_Mat3 HMM_Mul(HMM_Mat3 Left, HMM_Mat3 Right)
{
    ASSERT_COVERED(HMM_MulM3CPP);
    return HMM_MulM3(Left, Right);
}

COVERAGE(HMM_MulM4CPP, 1)
static inline HMM_Mat4 HMM_Mul(HMM_Mat4 Left, HMM_Mat4 Right)
{
    ASSERT_COVERED(HMM_MulM4CPP);
    return HMM_MulM4(Left, Right);
}

COVERAGE(HMM_MulM2FCPP, 1)
static inline HMM_Mat2 HMM_Mul(HMM_Mat2 Left, float Right)
{
    ASSERT_COVERED(HMM_MulM2FCPP);
    return HMM_MulM2F(Left, Right);
}

COVERAGE(HMM_MulM3FCPP, 1)
static inline HMM_Mat3 HMM_Mul(HMM_Mat3 Left, float Right)
{
    ASSERT_COVERED(HMM_MulM3FCPP);
    return HMM_MulM3F(Left, Right);
}

COVERAGE(HMM_MulM4FCPP, 1)
static inline HMM_Mat4 HMM_Mul(HMM_Mat4 Left, float Right)
{
    ASSERT_COVERED(HMM_MulM4FCPP);
    return HMM_MulM4F(Left, Right);
}

COVERAGE(HMM_MulM2V2CPP, 1)
static inline HMM_Vec2 HMM_Mul(HMM_Mat2 Matrix, HMM_Vec2 Vector)
{
    ASSERT_COVERED(HMM_MulM2V2CPP);
    return HMM_MulM2V2(Matrix, Vector);
}

COVERAGE(HMM_MulM3V3CPP, 1)
static inline HMM_Vec3 HMM_Mul(HMM_Mat3 Matrix, HMM_Vec3 Vector)
{
    ASSERT_COVERED(HMM_MulM3V3CPP);
    return HMM_MulM3V3(Matrix, Vector);
}

COVERAGE(HMM_MulM4V4CPP, 1)
static inline HMM_Vec4 HMM_Mul(HMM_Mat4 Matrix, HMM_Vec4 Vector)
{
    ASSERT_COVERED(HMM_MulM4V4CPP);
    return HMM_MulM4V4(Matrix, Vector);
}

COVERAGE(HMM_MulQCPP, 1)
static inline HMM_Quat HMM_Mul(HMM_Quat Left, HMM_Quat Right)
{
    ASSERT_COVERED(HMM_MulQCPP);
    return HMM_MulQ(Left, Right);
}

COVERAGE(HMM_MulQFCPP, 1)
static inline HMM_Quat HMM_Mul(HMM_Quat Left, float Right)
{
    ASSERT_COVERED(HMM_MulQFCPP);
    return HMM_MulQF(Left, Right);
}

COVERAGE(HMM_DivV2CPP, 1)
static inline HMM_Vec2 HMM_Div(HMM_Vec2 Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_DivV2CPP);
    return HMM_DivV2(Left, Right);
}

COVERAGE(HMM_DivV2FCPP, 1)
static inline HMM_Vec2 HMM_Div(HMM_Vec2 Left, float Right)
{
    ASSERT_COVERED(HMM_DivV2FCPP);
    return HMM_DivV2F(Left, Right);
}

COVERAGE(HMM_DivV3CPP, 1)
static inline HMM_Vec3 HMM_Div(HMM_Vec3 Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_DivV3CPP);
    return HMM_DivV3(Left, Right);
}

COVERAGE(HMM_DivV3FCPP, 1)
static inline HMM_Vec3 HMM_Div(HMM_Vec3 Left, float Right)
{
    ASSERT_COVERED(HMM_DivV3FCPP);
    return HMM_DivV3F(Left, Right);
}

COVERAGE(HMM_DivV4CPP, 1)
static inline HMM_Vec4 HMM_Div(HMM_Vec4 Left, HMM_Vec4 Right)
{
    ASSERT_COVERED(HMM_DivV4CPP);
    return HMM_DivV4(Left, Right);
}

COVERAGE(HMM_DivV4FCPP, 1)
static inline HMM_Vec4 HMM_Div(HMM_Vec4 Left, float Right)
{
    ASSERT_COVERED(HMM_DivV4FCPP);
    return HMM_DivV4F(Left, Right);
}

COVERAGE(HMM_DivM2FCPP, 1)
static inline HMM_Mat2 HMM_Div(HMM_Mat2 Left, float Right)
{
    ASSERT_COVERED(HMM_DivM2FCPP);
    return HMM_DivM2F(Left, Right);
}

COVERAGE(HMM_DivM3FCPP, 1)
static inline HMM_Mat3 HMM_Div(HMM_Mat3 Left, float Right)
{
    ASSERT_COVERED(HMM_DivM3FCPP);
    return HMM_DivM3F(Left, Right);
}

COVERAGE(HMM_DivM4FCPP, 1)
static inline HMM_Mat4 HMM_Div(HMM_Mat4 Left, float Right)
{
    ASSERT_COVERED(HMM_DivM4FCPP);
    return HMM_DivM4F(Left, Right);
}

COVERAGE(HMM_DivQFCPP, 1)
static inline HMM_Quat HMM_Div(HMM_Quat Left, float Right)
{
    ASSERT_COVERED(HMM_DivQFCPP);
    return HMM_DivQF(Left, Right);
}

COVERAGE(HMM_EqV2CPP, 1)
static inline HMM_Bool HMM_Eq(HMM_Vec2 Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_EqV2CPP);
    return HMM_EqV2(Left, Right);
}

COVERAGE(HMM_EqV3CPP, 1)
static inline HMM_Bool HMM_Eq(HMM_Vec3 Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_EqV3CPP);
    return HMM_EqV3(Left, Right);
}

COVERAGE(HMM_EqV4CPP, 1)
static inline HMM_Bool HMM_Eq(HMM_Vec4 Left, HMM_Vec4 Right)
{
    ASSERT_COVERED(HMM_EqV4CPP);
    return HMM_EqV4(Left, Right);
}

COVERAGE(HMM_AddV2Op, 1)
static inline HMM_Vec2 operator+(HMM_Vec2 Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_AddV2Op);
    return HMM_AddV2(Left, Right);
}

COVERAGE(HMM_AddV3Op, 1)
static inline HMM_Vec3 operator+(HMM_Vec3 Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_AddV3Op);
    return HMM_AddV3(Left, Right);
}

COVERAGE(HMM_AddV4Op, 1)
static inline HMM_Vec4 operator+(HMM_Vec4 Left, HMM_Vec4 Right)
{
    ASSERT_COVERED(HMM_AddV4Op);
    return HMM_AddV4(Left, Right);
}

COVERAGE(HMM_AddM2Op, 1)
static inline HMM_Mat2 operator+(HMM_Mat2 Left, HMM_Mat2 Right)
{
    ASSERT_COVERED(HMM_AddM2Op);
    return HMM_AddM2(Left, Right);
}

COVERAGE(HMM_AddM3Op, 1)
static inline HMM_Mat3 operator+(HMM_Mat3 Left, HMM_Mat3 Right)
{
    ASSERT_COVERED(HMM_AddM3Op);
    return HMM_AddM3(Left, Right);
}

COVERAGE(HMM_AddM4Op, 1)
static inline HMM_Mat4 operator+(HMM_Mat4 Left, HMM_Mat4 Right)
{
    ASSERT_COVERED(HMM_AddM4Op);
    return HMM_AddM4(Left, Right);
}

COVERAGE(HMM_AddQOp, 1)
static inline HMM_Quat operator+(HMM_Quat Left, HMM_Quat Right)
{
    ASSERT_COVERED(HMM_AddQOp);
    return HMM_AddQ(Left, Right);
}

COVERAGE(HMM_SubV2Op, 1)
static inline HMM_Vec2 operator-(HMM_Vec2 Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_SubV2Op);
    return HMM_SubV2(Left, Right);
}

COVERAGE(HMM_SubV3Op, 1)
static inline HMM_Vec3 operator-(HMM_Vec3 Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_SubV3Op);
    return HMM_SubV3(Left, Right);
}

COVERAGE(HMM_SubV4Op, 1)
static inline HMM_Vec4 operator-(HMM_Vec4 Left, HMM_Vec4 Right)
{
    ASSERT_COVERED(HMM_SubV4Op);
    return HMM_SubV4(Left, Right);
}

COVERAGE(HMM_SubM2Op, 1)
static inline HMM_Mat2 operator-(HMM_Mat2 Left, HMM_Mat2 Right)
{
    ASSERT_COVERED(HMM_SubM2Op);
    return HMM_SubM2(Left, Right);
}

COVERAGE(HMM_SubM3Op, 1)
static inline HMM_Mat3 operator-(HMM_Mat3 Left, HMM_Mat3 Right)
{
    ASSERT_COVERED(HMM_SubM3Op);
    return HMM_SubM3(Left, Right);
}

COVERAGE(HMM_SubM4Op, 1)
static inline HMM_Mat4 operator-(HMM_Mat4 Left, HMM_Mat4 Right)
{
    ASSERT_COVERED(HMM_SubM4Op);
    return HMM_SubM4(Left, Right);
}

COVERAGE(HMM_SubQOp, 1)
static inline HMM_Quat operator-(HMM_Quat Left, HMM_Quat Right)
{
    ASSERT_COVERED(HMM_SubQOp);
    return HMM_SubQ(Left, Right);
}

COVERAGE(HMM_MulV2Op, 1)
static inline HMM_Vec2 operator*(HMM_Vec2 Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_MulV2Op);
    return HMM_MulV2(Left, Right);
}

COVERAGE(HMM_MulV3Op, 1)
static inline HMM_Vec3 operator*(HMM_Vec3 Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_MulV3Op);
    return HMM_MulV3(Left, Right);
}

COVERAGE(HMM_MulV4Op, 1)
static inline HMM_Vec4 operator*(HMM_Vec4 Left, HMM_Vec4 Right)
{
    ASSERT_COVERED(HMM_MulV4Op);
    return HMM_MulV4(Left, Right);
}

COVERAGE(HMM_MulM2Op, 1)
static inline HMM_Mat2 operator*(HMM_Mat2 Left, HMM_Mat2 Right)
{
    ASSERT_COVERED(HMM_MulM2Op);
    return HMM_MulM2(Left, Right);
}

COVERAGE(HMM_MulM3Op, 1)
static inline HMM_Mat3 operator*(HMM_Mat3 Left, HMM_Mat3 Right)
{
    ASSERT_COVERED(HMM_MulM3Op);
    return HMM_MulM3(Left, Right);
}

COVERAGE(HMM_MulM4Op, 1)
static inline HMM_Mat4 operator*(HMM_Mat4 Left, HMM_Mat4 Right)
{
    ASSERT_COVERED(HMM_MulM4Op);
    return HMM_MulM4(Left, Right);
}

COVERAGE(HMM_MulQOp, 1)
static inline HMM_Quat operator*(HMM_Quat Left, HMM_Quat Right)
{
    ASSERT_COVERED(HMM_MulQOp);
    return HMM_MulQ(Left, Right);
}

COVERAGE(HMM_MulV2FOp, 1)
static inline HMM_Vec2 operator*(HMM_Vec2 Left, float Right)
{
    ASSERT_COVERED(HMM_MulV2FOp);
    return HMM_MulV2F(Left, Right);
}

COVERAGE(HMM_MulV3FOp, 1)
static inline HMM_Vec3 operator*(HMM_Vec3 Left, float Right)
{
    ASSERT_COVERED(HMM_MulV3FOp);
    return HMM_MulV3F(Left, Right);
}

COVERAGE(HMM_MulV4FOp, 1)
static inline HMM_Vec4 operator*(HMM_Vec4 Left, float Right)
{
    ASSERT_COVERED(HMM_MulV4FOp);
    return HMM_MulV4F(Left, Right);
}

COVERAGE(HMM_MulM2FOp, 1)
static inline HMM_Mat2 operator*(HMM_Mat2 Left, float Right)
{
    ASSERT_COVERED(HMM_MulM2FOp);
    return HMM_MulM2F(Left, Right);
}

COVERAGE(HMM_MulM3FOp, 1)
static inline HMM_Mat3 operator*(HMM_Mat3 Left, float Right)
{
    ASSERT_COVERED(HMM_MulM3FOp);
    return HMM_MulM3F(Left, Right);
}

COVERAGE(HMM_MulM4FOp, 1)
static inline HMM_Mat4 operator*(HMM_Mat4 Left, float Right)
{
    ASSERT_COVERED(HMM_MulM4FOp);
    return HMM_MulM4F(Left, Right);
}

COVERAGE(HMM_MulQFOp, 1)
static inline HMM_Quat operator*(HMM_Quat Left, float Right)
{
    ASSERT_COVERED(HMM_MulQFOp);
    return HMM_MulQF(Left, Right);
}

COVERAGE(HMM_MulV2FOpLeft, 1)
static inline HMM_Vec2 operator*(float Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_MulV2FOpLeft);
    return HMM_MulV2F(Right, Left);
}

COVERAGE(HMM_MulV3FOpLeft, 1)
static inline HMM_Vec3 operator*(float Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_MulV3FOpLeft);
    return HMM_MulV3F(Right, Left);
}

COVERAGE(HMM_MulV4FOpLeft, 1)
static inline HMM_Vec4 operator*(float Left, HMM_Vec4 Right)
{
    ASSERT_COVERED(HMM_MulV4FOpLeft);
    return HMM_MulV4F(Right, Left);
}

COVERAGE(HMM_MulM2FOpLeft, 1)
static inline HMM_Mat2 operator*(float Left, HMM_Mat2 Right)
{
    ASSERT_COVERED(HMM_MulM2FOpLeft);
    return HMM_MulM2F(Right, Left);
}

COVERAGE(HMM_MulM3FOpLeft, 1)
static inline HMM_Mat3 operator*(float Left, HMM_Mat3 Right)
{
    ASSERT_COVERED(HMM_MulM3FOpLeft);
    return HMM_MulM3F(Right, Left);
}

COVERAGE(HMM_MulM4FOpLeft, 1)
static inline HMM_Mat4 operator*(float Left, HMM_Mat4 Right)
{
    ASSERT_COVERED(HMM_MulM4FOpLeft);
    return HMM_MulM4F(Right, Left);
}

COVERAGE(HMM_MulQFOpLeft, 1)
static inline HMM_Quat operator*(float Left, HMM_Quat Right)
{
    ASSERT_COVERED(HMM_MulQFOpLeft);
    return HMM_MulQF(Right, Left);
}

COVERAGE(HMM_MulM2V2Op, 1)
static inline HMM_Vec2 operator*(HMM_Mat2 Matrix, HMM_Vec2 Vector)
{
    ASSERT_COVERED(HMM_MulM2V2Op);
    return HMM_MulM2V2(Matrix, Vector);
}

COVERAGE(HMM_MulM3V3Op, 1)
static inline HMM_Vec3 operator*(HMM_Mat3 Matrix, HMM_Vec3 Vector)
{
    ASSERT_COVERED(HMM_MulM3V3Op);
    return HMM_MulM3V3(Matrix, Vector);
}

COVERAGE(HMM_MulM4V4Op, 1)
static inline HMM_Vec4 operator*(HMM_Mat4 Matrix, HMM_Vec4 Vector)
{
    ASSERT_COVERED(HMM_MulM4V4Op);
    return HMM_MulM4V4(Matrix, Vector);
}

COVERAGE(HMM_DivV2Op, 1)
static inline HMM_Vec2 operator/(HMM_Vec2 Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_DivV2Op);
    return HMM_DivV2(Left, Right);
}

COVERAGE(HMM_DivV3Op, 1)
static inline HMM_Vec3 operator/(HMM_Vec3 Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_DivV3Op);
    return HMM_DivV3(Left, Right);
}

COVERAGE(HMM_DivV4Op, 1)
static inline HMM_Vec4 operator/(HMM_Vec4 Left, HMM_Vec4 Right)
{
    ASSERT_COVERED(HMM_DivV4Op);
    return HMM_DivV4(Left, Right);
}

COVERAGE(HMM_DivV2FOp, 1)
static inline HMM_Vec2 operator/(HMM_Vec2 Left, float Right)
{
    ASSERT_COVERED(HMM_DivV2FOp);
    return HMM_DivV2F(Left, Right);
}

COVERAGE(HMM_DivV3FOp, 1)
static inline HMM_Vec3 operator/(HMM_Vec3 Left, float Right)
{
    ASSERT_COVERED(HMM_DivV3FOp);
    return HMM_DivV3F(Left, Right);
}

COVERAGE(HMM_DivV4FOp, 1)
static inline HMM_Vec4 operator/(HMM_Vec4 Left, float Right)
{
    ASSERT_COVERED(HMM_DivV4FOp);
    return HMM_DivV4F(Left, Right);
}

COVERAGE(HMM_DivM4FOp, 1)
static inline HMM_Mat4 operator/(HMM_Mat4 Left, float Right)
{
    ASSERT_COVERED(HMM_DivM4FOp);
    return HMM_DivM4F(Left, Right);
}

COVERAGE(HMM_DivM3FOp, 1)
static inline HMM_Mat3 operator/(HMM_Mat3 Left, float Right)
{
    ASSERT_COVERED(HMM_DivM3FOp);
    return HMM_DivM3F(Left, Right);
}

COVERAGE(HMM_DivM2FOp, 1)
static inline HMM_Mat2 operator/(HMM_Mat2 Left, float Right)
{
    ASSERT_COVERED(HMM_DivM2FOp);
    return HMM_DivM2F(Left, Right);
}

COVERAGE(HMM_DivQFOp, 1)
static inline HMM_Quat operator/(HMM_Quat Left, float Right)
{
    ASSERT_COVERED(HMM_DivQFOp);
    return HMM_DivQF(Left, Right);
}

COVERAGE(HMM_AddV2Assign, 1)
static inline HMM_Vec2 &operator+=(HMM_Vec2 &Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_AddV2Assign);
    return Left = Left + Right;
}

COVERAGE(HMM_AddV3Assign, 1)
static inline HMM_Vec3 &operator+=(HMM_Vec3 &Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_AddV3Assign);
    return Left = Left + Right;
}

COVERAGE(HMM_AddV4Assign, 1)
static inline HMM_Vec4 &operator+=(HMM_Vec4 &Left, HMM_Vec4 Right)
{
    ASSERT_COVERED(HMM_AddV4Assign);
    return Left = Left + Right;
}

COVERAGE(HMM_AddM2Assign, 1)
static inline HMM_Mat2 &operator+=(HMM_Mat2 &Left, HMM_Mat2 Right)
{
    ASSERT_COVERED(HMM_AddM2Assign);
    return Left = Left + Right;
}

COVERAGE(HMM_AddM3Assign, 1)
static inline HMM_Mat3 &operator+=(HMM_Mat3 &Left, HMM_Mat3 Right)
{
    ASSERT_COVERED(HMM_AddM3Assign);
    return Left = Left + Right;
}

COVERAGE(HMM_AddM4Assign, 1)
static inline HMM_Mat4 &operator+=(HMM_Mat4 &Left, HMM_Mat4 Right)
{
    ASSERT_COVERED(HMM_AddM4Assign);
    return Left = Left + Right;
}

COVERAGE(HMM_AddQAssign, 1)
static inline HMM_Quat &operator+=(HMM_Quat &Left, HMM_Quat Right)
{
    ASSERT_COVERED(HMM_AddQAssign);
    return Left = Left + Right;
}

COVERAGE(HMM_SubV2Assign, 1)
static inline HMM_Vec2 &operator-=(HMM_Vec2 &Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_SubV2Assign);
    return Left = Left - Right;
}

COVERAGE(HMM_SubV3Assign, 1)
static inline HMM_Vec3 &operator-=(HMM_Vec3 &Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_SubV3Assign);
    return Left = Left - Right;
}

COVERAGE(HMM_SubV4Assign, 1)
static inline HMM_Vec4 &operator-=(HMM_Vec4 &Left, HMM_Vec4 Right)
{
    ASSERT_COVERED(HMM_SubV4Assign);
    return Left = Left - Right;
}

COVERAGE(HMM_SubM2Assign, 1)
static inline HMM_Mat2 &operator-=(HMM_Mat2 &Left, HMM_Mat2 Right)
{
    ASSERT_COVERED(HMM_SubM2Assign);
    return Left = Left - Right;
}

COVERAGE(HMM_SubM3Assign, 1)
static inline HMM_Mat3 &operator-=(HMM_Mat3 &Left, HMM_Mat3 Right)
{
    ASSERT_COVERED(HMM_SubM3Assign);
    return Left = Left - Right;
}

COVERAGE(HMM_SubM4Assign, 1)
static inline HMM_Mat4 &operator-=(HMM_Mat4 &Left, HMM_Mat4 Right)
{
    ASSERT_COVERED(HMM_SubM4Assign);
    return Left = Left - Right;
}

COVERAGE(HMM_SubQAssign, 1)
static inline HMM_Quat &operator-=(HMM_Quat &Left, HMM_Quat Right)
{
    ASSERT_COVERED(HMM_SubQAssign);
    return Left = Left - Right;
}

COVERAGE(HMM_MulV2Assign, 1)
static inline HMM_Vec2 &operator*=(HMM_Vec2 &Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_MulV2Assign);
    return Left = Left * Right;
}

COVERAGE(HMM_MulV3Assign, 1)
static inline HMM_Vec3 &operator*=(HMM_Vec3 &Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_MulV3Assign);
    return Left = Left * Right;
}

COVERAGE(HMM_MulV4Assign, 1)
static inline HMM_Vec4 &operator*=(HMM_Vec4 &Left, HMM_Vec4 Right)
{
    ASSERT_COVERED(HMM_MulV4Assign);
    return Left = Left * Right;
}

COVERAGE(HMM_MulV2FAssign, 1)
static inline HMM_Vec2 &operator*=(HMM_Vec2 &Left, float Right)
{
    ASSERT_COVERED(HMM_MulV2FAssign);
    return Left = Left * Right;
}

COVERAGE(HMM_MulV3FAssign, 1)
static inline HMM_Vec3 &operator*=(HMM_Vec3 &Left, float Right)
{
    ASSERT_COVERED(HMM_MulV3FAssign);
    return Left = Left * Right;
}

COVERAGE(HMM_MulV4FAssign, 1)
static inline HMM_Vec4 &operator*=(HMM_Vec4 &Left, float Right)
{
    ASSERT_COVERED(HMM_MulV4FAssign);
    return Left = Left * Right;
}

COVERAGE(HMM_MulM2FAssign, 1)
static inline HMM_Mat2 &operator*=(HMM_Mat2 &Left, float Right)
{
    ASSERT_COVERED(HMM_MulM2FAssign);
    return Left = Left * Right;
}

COVERAGE(HMM_MulM3FAssign, 1)
static inline HMM_Mat3 &operator*=(HMM_Mat3 &Left, float Right)
{
    ASSERT_COVERED(HMM_MulM3FAssign);
    return Left = Left * Right;
}

COVERAGE(HMM_MulM4FAssign, 1)
static inline HMM_Mat4 &operator*=(HMM_Mat4 &Left, float Right)
{
    ASSERT_COVERED(HMM_MulM4FAssign);
    return Left = Left * Right;
}

COVERAGE(HMM_MulQFAssign, 1)
static inline HMM_Quat &operator*=(HMM_Quat &Left, float Right)
{
    ASSERT_COVERED(HMM_MulQFAssign);
    return Left = Left * Right;
}

COVERAGE(HMM_DivV2Assign, 1)
static inline HMM_Vec2 &operator/=(HMM_Vec2 &Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_DivV2Assign);
    return Left = Left / Right;
}

COVERAGE(HMM_DivV3Assign, 1)
static inline HMM_Vec3 &operator/=(HMM_Vec3 &Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_DivV3Assign);
    return Left = Left / Right;
}

COVERAGE(HMM_DivV4Assign, 1)
static inline HMM_Vec4 &operator/=(HMM_Vec4 &Left, HMM_Vec4 Right)
{
    ASSERT_COVERED(HMM_DivV4Assign);
    return Left = Left / Right;
}

COVERAGE(HMM_DivV2FAssign, 1)
static inline HMM_Vec2 &operator/=(HMM_Vec2 &Left, float Right)
{
    ASSERT_COVERED(HMM_DivV2FAssign);
    return Left = Left / Right;
}

COVERAGE(HMM_DivV3FAssign, 1)
static inline HMM_Vec3 &operator/=(HMM_Vec3 &Left, float Right)
{
    ASSERT_COVERED(HMM_DivV3FAssign);
    return Left = Left / Right;
}

COVERAGE(HMM_DivV4FAssign, 1)
static inline HMM_Vec4 &operator/=(HMM_Vec4 &Left, float Right)
{
    ASSERT_COVERED(HMM_DivV4FAssign);
    return Left = Left / Right;
}

COVERAGE(HMM_DivM4FAssign, 1)
static inline HMM_Mat4 &operator/=(HMM_Mat4 &Left, float Right)
{
    ASSERT_COVERED(HMM_DivM4FAssign);
    return Left = Left / Right;
}

COVERAGE(HMM_DivQFAssign, 1)
static inline HMM_Quat &operator/=(HMM_Quat &Left, float Right)
{
    ASSERT_COVERED(HMM_DivQFAssign);
    return Left = Left / Right;
}

COVERAGE(HMM_EqV2Op, 1)
static inline HMM_Bool operator==(HMM_Vec2 Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_EqV2Op);
    return HMM_EqV2(Left, Right);
}

COVERAGE(HMM_EqV3Op, 1)
static inline HMM_Bool operator==(HMM_Vec3 Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_EqV3Op);
    return HMM_EqV3(Left, Right);
}

COVERAGE(HMM_EqV4Op, 1)
static inline HMM_Bool operator==(HMM_Vec4 Left, HMM_Vec4 Right)
{
    ASSERT_COVERED(HMM_EqV4Op);
    return HMM_EqV4(Left, Right);
}

COVERAGE(HMM_EqV2OpNot, 1)
static inline HMM_Bool operator!=(HMM_Vec2 Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_EqV2OpNot);
    return !HMM_EqV2(Left, Right);
}

COVERAGE(HMM_EqV3OpNot, 1)
static inline HMM_Bool operator!=(HMM_Vec3 Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_EqV3OpNot);
    return !HMM_EqV3(Left, Right);
}

COVERAGE(HMM_EqV4OpNot, 1)
static inline HMM_Bool operator!=(HMM_Vec4 Left, HMM_Vec4 Right)
{
    ASSERT_COVERED(HMM_EqV4OpNot);
    return !HMM_EqV4(Left, Right);
}

COVERAGE(HMM_UnaryMinusV2, 1)
static inline HMM_Vec2 operator-(HMM_Vec2 In)
{
    ASSERT_COVERED(HMM_UnaryMinusV2);

    HMM_Vec2 Result;
    Result.X = -In.X;
    Result.Y = -In.Y;

    return Result;
}

COVERAGE(HMM_UnaryMinusV3, 1)
static inline HMM_Vec3 operator-(HMM_Vec3 In)
{
    ASSERT_COVERED(HMM_UnaryMinusV3);

    HMM_Vec3 Result;
    Result.X = -In.X;
    Result.Y = -In.Y;
    Result.Z = -In.Z;

    return Result;
}

COVERAGE(HMM_UnaryMinusV4, 1)
static inline HMM_Vec4 operator-(HMM_Vec4 In)
{
    ASSERT_COVERED(HMM_UnaryMinusV4);

    HMM_Vec4 Result;
#if HANDMADE_MATH__USE_SSE
    Result.SSE = _mm_xor_ps(In.SSE, _mm_set1_ps(-0.0f));
#elif defined(HANDMADE_MATH__USE_NEON)
    float32x4_t Zero = vdupq_n_f32(0.0f);
    Result.NEON = vsubq_f32(Zero, In.NEON);
#else
    Result.X = -In.X;
    Result.Y = -In.Y;
    Result.Z = -In.Z;
    Result.W = -In.W;
#endif

    return Result;
}

#endif /* __cplusplus*/

#ifdef HANDMADE_MATH__USE_C11_GENERICS
#define HMM_Add(A, B) _Generic((A), \
        HMM_Vec2: HMM_AddV2, \
        HMM_Vec3: HMM_AddV3, \
        HMM_Vec4: HMM_AddV4, \
        HMM_Mat2: HMM_AddM2, \
        HMM_Mat3: HMM_AddM3, \
        HMM_Mat4: HMM_AddM4, \
        HMM_Quat: HMM_AddQ \
)(A, B)

#define HMM_Sub(A, B) _Generic((A), \
        HMM_Vec2: HMM_SubV2, \
        HMM_Vec3: HMM_SubV3, \
        HMM_Vec4: HMM_SubV4, \
        HMM_Mat2: HMM_SubM2, \
        HMM_Mat3: HMM_SubM3, \
        HMM_Mat4: HMM_SubM4, \
        HMM_Quat: HMM_SubQ \
)(A, B)

#define HMM_Mul(A, B) _Generic((B), \
     float: _Generic((A), \
        HMM_Vec2: HMM_MulV2F, \
        HMM_Vec3: HMM_MulV3F, \
        HMM_Vec4: HMM_MulV4F, \
        HMM_Mat2: HMM_MulM2F, \
        HMM_Mat3: HMM_MulM3F, \
        HMM_Mat4: HMM_MulM4F, \
        HMM_Quat: HMM_MulQF \
     ), \
     HMM_Mat2: HMM_MulM2, \
     HMM_Mat3: HMM_MulM3, \
     HMM_Mat4: HMM_MulM4, \
     HMM_Quat: HMM_MulQ, \
     default: _Generic((A), \
        HMM_Vec2: HMM_MulV2, \
        HMM_Vec3: HMM_MulV3, \
        HMM_Vec4: HMM_MulV4, \
        HMM_Mat2: HMM_MulM2V2, \
        HMM_Mat3: HMM_MulM3V3, \
        HMM_Mat4: HMM_MulM4V4 \
    ) \
)(A, B)

#define HMM_Div(A, B) _Generic((B), \
     float: _Generic((A), \
        HMM_Mat2: HMM_DivM2F, \
        HMM_Mat3: HMM_DivM3F, \
        HMM_Mat4: HMM_DivM4F, \
        HMM_Vec2: HMM_DivV2F, \
        HMM_Vec3: HMM_DivV3F, \
        HMM_Vec4: HMM_DivV4F, \
        HMM_Quat: HMM_DivQF  \
     ), \
     HMM_Mat2: HMM_DivM2, \
     HMM_Mat3: HMM_DivM3, \
     HMM_Mat4: HMM_DivM4, \
     HMM_Quat: HMM_DivQ, \
     default: _Generic((A), \
        HMM_Vec2: HMM_DivV2, \
        HMM_Vec3: HMM_DivV3, \
        HMM_Vec4: HMM_DivV4  \
    ) \
)(A, B)

#define HMM_Len(A) _Generic((A), \
        HMM_Vec2: HMM_LenV2, \
        HMM_Vec3: HMM_LenV3, \
        HMM_Vec4: HMM_LenV4  \
)(A)

#define HMM_LenSqr(A) _Generic((A), \
        HMM_Vec2: HMM_LenSqrV2, \
        HMM_Vec3: HMM_LenSqrV3, \
        HMM_Vec4: HMM_LenSqrV4  \
)(A)

#define HMM_Norm(A) _Generic((A), \
        HMM_Vec2: HMM_NormV2, \
        HMM_Vec3: HMM_NormV3, \
        HMM_Vec4: HMM_NormV4  \
)(A)

#define HMM_Dot(A, B) _Generic((A), \
        HMM_Vec2: HMM_DotV2, \
        HMM_Vec3: HMM_DotV3, \
        HMM_Vec4: HMM_DotV4  \
)(A, B)

#define HMM_Lerp(A, T, B) _Generic((A), \
        float: HMM_Lerp, \
        HMM_Vec2: HMM_LerpV2, \
        HMM_Vec3: HMM_LerpV3, \
        HMM_Vec4: HMM_LerpV4 \
)(A, T, B)

#define HMM_Eq(A, B) _Generic((A), \
        HMM_Vec2: HMM_EqV2, \
        HMM_Vec3: HMM_EqV3, \
        HMM_Vec4: HMM_EqV4  \
)(A, B)

#define HMM_Transpose(M) _Generic((M), \
        HMM_Mat2: HMM_TransposeM2, \
        HMM_Mat3: HMM_TransposeM3, \
        HMM_Mat4: HMM_TransposeM4  \
)(M)

#define HMM_Determinant(M) _Generic((M), \
        HMM_Mat2: HMM_DeterminantM2, \
        HMM_Mat3: HMM_DeterminantM3, \
        HMM_Mat4: HMM_DeterminantM4  \
)(M)

#define HMM_InvGeneral(M) _Generic((M), \
        HMM_Mat2: HMM_InvGeneralM2, \
        HMM_Mat3: HMM_InvGeneralM3, \
        HMM_Mat4: HMM_InvGeneralM4  \
)(M)

#endif

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif

#endif /* HANDMADE_MATH_H */
