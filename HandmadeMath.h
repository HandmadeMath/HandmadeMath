/*
  HandmadeMath.h v2.0.0

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

  To use HandmadeMath without the CRT, you MUST

     #define HMM_PROVIDE_MATH_FUNCTIONS

  Provide your own implementations of SinF, CosF, ACosF, ExpF, and LogF
  in EXACTLY one C or C++ file that includes this header,
  BEFORE the include, like this (assuming your functions take radians):

     #define HMM_PROVIDE_MATH_FUNCTIONS
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
   Logan Forman (@dev_dwarf)

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

#ifndef HANDMADE_MATH_C11_GENERICS
/* By default enable _Generic macros if available */
#if (!defined(__cplusplus) && defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L)
#define HANDMADE_MATH_C11_GENERICS
#endif
#endif /* #ifndef HANDMADE_MATH_C11_GENERICS */


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
#include <math.h>
/* Conversion function to the unit the trig functions need angles in.
   Define as one of HMM_ToRadians, HMM_ToDegrees, or HMM_ToTurns. */
#define HMM_ANGLE_USER_TO_INTERNAL(a) (HMM_ToRadians(a))
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

#if !defined(HMM_ANGLE_USER_TO_INTERNAL)
#define HMM_ANGLE_USER_TO_INTERNAL(a) (a)
#define HMM_ANGLE_INTERNAL_TO_USER(a) (a)
#endif
    
#define HMM_SINF sinf
#define HMM_COSF cosf
#define HMM_TANF tanf
#define HMM_SQRTF sqrtf
#define HMM_EXPF expf
#define HMM_LOGF logf
#define HMM_ACOSF acosf
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
    inline float &operator[](const int &Index)
    {
        return Elements[Index];
    }
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

typedef union HMM_Mat2
{
    float Elements[2][2];
    HMM_Vec2 Columns[2];

#ifdef __cplusplus
    inline HMM_Vec2 operator[](const int &Index)
    {
        HMM_Vec2 Result;
        float* Column = Elements[Index];
        
        Result.Elements[0] = Column[0];
        Result.Elements[1] = Column[1];

        return (Result);
    }
#endif
} HMM_Mat2;
    
typedef union HMM_Mat3
{
    float Elements[3][3];
    HMM_Vec3 Columns[3];

#ifdef __cplusplus
    inline HMM_Vec3 operator[](const int &Index)
    {
        HMM_Vec3 Result;
        float* Column = Elements[Index];
        
        Result.Elements[0] = Column[0];
        Result.Elements[1] = Column[1];
        Result.Elements[2] = Column[2];

        return (Result);
    }
#endif
} HMM_Mat3;

typedef union HMM_Mat4
{
    float Elements[4][4];

    HMM_Vec4 Columns[4];

#ifdef HANDMADE_MATH__USE_SSE
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

        return (Result);
    }
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
    __m128 InternalElementsSSE;
#endif
} HMM_Quat;

typedef signed int HMM_Bool;

/*
 * Angle unit conversion functions
 */
HMM_INLINE float HMM_ToRad(float Angle)
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

HMM_INLINE float HMM_ToDeg(float Angle)
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

HMM_INLINE float HMM_ToTurn(float Angle)
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
HMM_INLINE float HMM_SinF(float Angle)
{
    ASSERT_COVERED(HMM_SinF);

    float Result = HMM_SINF(HMM_ANGLE_USER_TO_INTERNAL(Angle));

    return (Result);
}

COVERAGE(HMM_CosF, 1)
HMM_INLINE float HMM_CosF(float Angle)
{
    ASSERT_COVERED(HMM_CosF);

    float Result = HMM_COSF(HMM_ANGLE_USER_TO_INTERNAL(Angle));

    return (Result);
}

COVERAGE(HMM_ACosF, 1)
HMM_INLINE float HMM_ACosF(float Angle)
{
    ASSERT_COVERED(HMM_ACosF);

    float Result = HMM_ANGLE_INTERNAL_TO_USER(HMM_ACOSF(Angle));

    return (Result);
}

COVERAGE(HMM_TanF, 1)
HMM_INLINE float HMM_TanF(float Angle)
{
    ASSERT_COVERED(HMM_TanF);
    float Result = HMM_TANF(HMM_ANGLE_USER_TO_INTERNAL(Angle));
    return (Result);
}

COVERAGE(HMM_ExpF, 1)
HMM_INLINE float HMM_ExpF(float Float)
{
    ASSERT_COVERED(HMM_ExpF);

    float Result = HMM_EXPF(Float);

    return (Result);
}

COVERAGE(HMM_LogF, 1)
HMM_INLINE float HMM_LogF(float Float)
{
    ASSERT_COVERED(HMM_LogF);

    float Result = HMM_LOGF(Float);

    return (Result);
}

COVERAGE(HMM_SqrtF, 1)
HMM_INLINE float HMM_SqrtF(float Float)
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
HMM_INLINE float HMM_InvSqrtF(float Float)
{
    ASSERT_COVERED(HMM_InvSqrtF);

    float Result;

#ifdef HANDMADE_MATH__USE_SSE
    __m128 In = _mm_set_ss(Float);
    __m128 Out = _mm_rsqrt_ss(In);
    Result = _mm_cvtss_f32(Out);
#else
    Result = 1.0f/HMM_SqrtF(Float);
#endif

    return(Result);
}

COVERAGE(HMM_Power, 2)
HMM_INLINE float HMM_Power(float Base, int Exponent)
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
HMM_INLINE float HMM_PowerF(float Base, float Exponent)
{
    ASSERT_COVERED(HMM_PowerF);

    float Result = HMM_EXPF(Exponent * HMM_LOGF(Base));

    return (Result);
}


/*
 * Utility functions
 */

COVERAGE(HMM_Lerp, 1)
HMM_INLINE float HMM_Lerp(float A, float Time, float B)
{
    ASSERT_COVERED(HMM_Lerp);

    float Result = (1.0f - Time) * A + Time * B;

    return (Result);
}

COVERAGE(HMM_Clamp, 1)
HMM_INLINE float HMM_Clamp(float Min, float Value, float Max)
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
HMM_INLINE HMM_Vec2 HMM_V2(float X, float Y)
{
    ASSERT_COVERED(HMM_V2);

    HMM_Vec2 Result;

    Result.X = X;
    Result.Y = Y;

    return (Result);
}

COVERAGE(HMM_V2I, 1)
HMM_INLINE HMM_Vec2 HMM_V2I(int X, int Y)
{
    ASSERT_COVERED(HMM_V2I);

    HMM_Vec2 Result;

    Result.X = (float)X;
    Result.Y = (float)Y;

    return (Result);
}

COVERAGE(HMM_V3, 1)
HMM_INLINE HMM_Vec3 HMM_V3(float X, float Y, float Z)
{
    ASSERT_COVERED(HMM_V3);

    HMM_Vec3 Result;

    Result.X = X;
    Result.Y = Y;
    Result.Z = Z;

    return (Result);
}

COVERAGE(HMM_V3I, 1)
HMM_INLINE HMM_Vec3 HMM_V3I(int X, int Y, int Z)
{
    ASSERT_COVERED(HMM_V3I);

    HMM_Vec3 Result;

    Result.X = (float)X;
    Result.Y = (float)Y;
    Result.Z = (float)Z;

    return (Result);
}

COVERAGE(HMM_V4, 1)
HMM_INLINE HMM_Vec4 HMM_V4(float X, float Y, float Z, float W)
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
HMM_INLINE HMM_Vec4 HMM_V4I(int X, int Y, int Z, int W)
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
HMM_INLINE HMM_Vec4 HMM_V4V(HMM_Vec3 Vector, float W)
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
HMM_INLINE HMM_Vec2 HMM_AddV2(HMM_Vec2 Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_AddV2);

    HMM_Vec2 Result;

    Result.X = Left.X + Right.X;
    Result.Y = Left.Y + Right.Y;

    return (Result);
}

COVERAGE(HMM_AddV3, 1)
HMM_INLINE HMM_Vec3 HMM_AddV3(HMM_Vec3 Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_AddV3);

    HMM_Vec3 Result;

    Result.X = Left.X + Right.X;
    Result.Y = Left.Y + Right.Y;
    Result.Z = Left.Z + Right.Z;

    return (Result);
}

COVERAGE(HMM_AddV4, 1)
HMM_INLINE HMM_Vec4 HMM_AddV4(HMM_Vec4 Left, HMM_Vec4 Right)
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
HMM_INLINE HMM_Vec2 HMM_SubV2(HMM_Vec2 Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_SubV2);

    HMM_Vec2 Result;

    Result.X = Left.X - Right.X;
    Result.Y = Left.Y - Right.Y;

    return (Result);
}

COVERAGE(HMM_SubV3, 1)
HMM_INLINE HMM_Vec3 HMM_SubV3(HMM_Vec3 Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_SubV3);

    HMM_Vec3 Result;

    Result.X = Left.X - Right.X;
    Result.Y = Left.Y - Right.Y;
    Result.Z = Left.Z - Right.Z;

    return (Result);
}

COVERAGE(HMM_SubV4, 1)
HMM_INLINE HMM_Vec4 HMM_SubV4(HMM_Vec4 Left, HMM_Vec4 Right)
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
HMM_INLINE HMM_Vec2 HMM_MulV2(HMM_Vec2 Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_MulV2);

    HMM_Vec2 Result;

    Result.X = Left.X * Right.X;
    Result.Y = Left.Y * Right.Y;

    return (Result);
}

COVERAGE(HMM_MulV2F, 1)
HMM_INLINE HMM_Vec2 HMM_MulV2F(HMM_Vec2 Left, float Right)
{
    ASSERT_COVERED(HMM_MulV2F);

    HMM_Vec2 Result;

    Result.X = Left.X * Right;
    Result.Y = Left.Y * Right;

    return (Result);
}

COVERAGE(HMM_MulV3, 1)
HMM_INLINE HMM_Vec3 HMM_MulV3(HMM_Vec3 Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_MulV3);

    HMM_Vec3 Result;

    Result.X = Left.X * Right.X;
    Result.Y = Left.Y * Right.Y;
    Result.Z = Left.Z * Right.Z;

    return (Result);
}

COVERAGE(HMM_MulV3F, 1)
HMM_INLINE HMM_Vec3 HMM_MulV3F(HMM_Vec3 Left, float Right)
{
    ASSERT_COVERED(HMM_MulV3F);

    HMM_Vec3 Result;

    Result.X = Left.X * Right;
    Result.Y = Left.Y * Right;
    Result.Z = Left.Z * Right;

    return (Result);
}

COVERAGE(HMM_MulV4, 1)
HMM_INLINE HMM_Vec4 HMM_MulV4(HMM_Vec4 Left, HMM_Vec4 Right)
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
HMM_INLINE HMM_Vec4 HMM_MulV4F(HMM_Vec4 Left, float Right)
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
HMM_INLINE HMM_Vec2 HMM_DivV2(HMM_Vec2 Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_DivV2);

    HMM_Vec2 Result;

    Result.X = Left.X / Right.X;
    Result.Y = Left.Y / Right.Y;

    return (Result);
}

COVERAGE(HMM_DivV2F, 1)
HMM_INLINE HMM_Vec2 HMM_DivV2F(HMM_Vec2 Left, float Right)
{
    ASSERT_COVERED(HMM_DivV2F);

    HMM_Vec2 Result;

    Result.X = Left.X / Right;
    Result.Y = Left.Y / Right;

    return (Result);
}

COVERAGE(HMM_DivV3, 1)
HMM_INLINE HMM_Vec3 HMM_DivV3(HMM_Vec3 Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_DivV3);

    HMM_Vec3 Result;

    Result.X = Left.X / Right.X;
    Result.Y = Left.Y / Right.Y;
    Result.Z = Left.Z / Right.Z;

    return (Result);
}

COVERAGE(HMM_DivV3F, 1)
HMM_INLINE HMM_Vec3 HMM_DivV3F(HMM_Vec3 Left, float Right)
{
    ASSERT_COVERED(HMM_DivV3F);

    HMM_Vec3 Result;

    Result.X = Left.X / Right;
    Result.Y = Left.Y / Right;
    Result.Z = Left.Z / Right;

    return (Result);
}

COVERAGE(HMM_DivV4, 1)
HMM_INLINE HMM_Vec4 HMM_DivV4(HMM_Vec4 Left, HMM_Vec4 Right)
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
HMM_INLINE HMM_Vec4 HMM_DivV4F(HMM_Vec4 Left, float Right)
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
HMM_INLINE HMM_Bool HMM_EqV2(HMM_Vec2 Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_EqV2);

    HMM_Bool Result = (Left.X == Right.X && Left.Y == Right.Y);

    return (Result);
}

COVERAGE(HMM_EqV3, 1)
HMM_INLINE HMM_Bool HMM_EqV3(HMM_Vec3 Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_EqV3);

    HMM_Bool Result = (Left.X == Right.X && Left.Y == Right.Y && Left.Z == Right.Z);

    return (Result);
}

COVERAGE(HMM_EqV4, 1)
HMM_INLINE HMM_Bool HMM_EqV4(HMM_Vec4 Left, HMM_Vec4 Right)
{
    ASSERT_COVERED(HMM_EqV4);

    HMM_Bool Result = (Left.X == Right.X && Left.Y == Right.Y && Left.Z == Right.Z && Left.W == Right.W);

    return (Result);
}

COVERAGE(HMM_DotV2, 1)
HMM_INLINE float HMM_DotV2(HMM_Vec2 Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_DotV2);

    float Result = (Left.X * Right.X) + (Left.Y * Right.Y);

    return (Result);
}

COVERAGE(HMM_DotV3, 1)
HMM_INLINE float HMM_DotV3(HMM_Vec3 Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_DotV3);

    float Result = (Left.X * Right.X) + (Left.Y * Right.Y) + (Left.Z * Right.Z);

    return (Result);
}

COVERAGE(HMM_DotV4, 1)
HMM_INLINE float HMM_DotV4(HMM_Vec4 Left, HMM_Vec4 Right)
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
HMM_INLINE HMM_Vec3 HMM_Cross(HMM_Vec3 Left, HMM_Vec3 Right)
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
HMM_INLINE float HMM_LenSqrV2(HMM_Vec2 A)
{
    ASSERT_COVERED(HMM_LenSqrV2);

    float Result = HMM_DotV2(A, A);

    return (Result);
}

COVERAGE(HMM_LenSqrV3, 1)
HMM_INLINE float HMM_LenSqrV3(HMM_Vec3 A)
{
    ASSERT_COVERED(HMM_LenSqrV3);

    float Result = HMM_DotV3(A, A);

    return (Result);
}

COVERAGE(HMM_LenSqrV4, 1)
HMM_INLINE float HMM_LenSqrV4(HMM_Vec4 A)
{
    ASSERT_COVERED(HMM_LenSqrV4);

    float Result = HMM_DotV4(A, A);

    return (Result);
}

COVERAGE(HMM_LenV2, 1)
HMM_INLINE float HMM_LenV2(HMM_Vec2 A)
{
    ASSERT_COVERED(HMM_LenV2);

    float Result = HMM_SqrtF(HMM_LenSqrV2(A));

    return (Result);
}

COVERAGE(HMM_LenV3, 1)
HMM_INLINE float HMM_LenV3(HMM_Vec3 A)
{
    ASSERT_COVERED(HMM_LenV3);

    float Result = HMM_SqrtF(HMM_LenSqrV3(A));

    return (Result);
}

COVERAGE(HMM_LenV4, 1)
HMM_INLINE float HMM_LenV4(HMM_Vec4 A)
{
    ASSERT_COVERED(HMM_LenV4);

    float Result = HMM_SqrtF(HMM_LenSqrV4(A));

    return(Result);
}

COVERAGE(HMM_NormV2, 1)
HMM_INLINE HMM_Vec2 HMM_NormV2(HMM_Vec2 A)
{
    ASSERT_COVERED(HMM_NormV2);

    return HMM_MulV2F(A, HMM_InvSqrtF(HMM_DotV2(A, A)));
}

COVERAGE(HMM_NormV3, 1)
HMM_INLINE HMM_Vec3 HMM_NormV3(HMM_Vec3 A)
{
    ASSERT_COVERED(HMM_NormV3);

    return HMM_MulV3F(A, HMM_InvSqrtF(HMM_DotV3(A, A)));
}

COVERAGE(HMM_NormV4, 1)
HMM_INLINE HMM_Vec4 HMM_NormV4(HMM_Vec4 A)
{
    ASSERT_COVERED(HMM_NormV4);

    return HMM_MulV4F(A, HMM_InvSqrtF(HMM_DotV4(A, A)));
}


/*
 * SSE stuff
 */

COVERAGE(HMM_LinearCombineV4M4, 1)
HMM_INLINE HMM_Vec4 HMM_LinearCombineV4M4(HMM_Vec4 Left, HMM_Mat4 Right)
{
    ASSERT_COVERED(HMM_LinearCombineV4M4);

    HMM_Vec4 Result;
#ifdef HANDMADE_MATH__USE_SSE
    Result.InternalElementsSSE = _mm_mul_ps(_mm_shuffle_ps(Left.InternalElementsSSE, Left.InternalElementsSSE, 0x00), Right.Columns[0].InternalElementsSSE);
    Result.InternalElementsSSE = _mm_add_ps(Result.InternalElementsSSE, _mm_mul_ps(_mm_shuffle_ps(Left.InternalElementsSSE, Left.InternalElementsSSE, 0x55), Right.Columns[1].InternalElementsSSE));
    Result.InternalElementsSSE = _mm_add_ps(Result.InternalElementsSSE, _mm_mul_ps(_mm_shuffle_ps(Left.InternalElementsSSE, Left.InternalElementsSSE, 0xaa), Right.Columns[2].InternalElementsSSE));
    Result.InternalElementsSSE = _mm_add_ps(Result.InternalElementsSSE, _mm_mul_ps(_mm_shuffle_ps(Left.InternalElementsSSE, Left.InternalElementsSSE, 0xff), Right.Columns[3].InternalElementsSSE));
#else
    int Columns, Rows;
    for(Rows = 0; Rows < 4; ++Rows)
    {
            float Sum = 0;
            for(Columns = 0; Columns < 4; ++Columns)
            {
                Sum += Left.Elements[Columns]*Right.Elements[Columns][Rows];
            }
            Result.Elements[Rows] = Sum;
    }
#endif

    return (Result);
}

/*
 * 4x4 Matrices
 */

COVERAGE(HMM_M4, 1)
HMM_INLINE HMM_Mat4 HMM_M4(void)
{
    ASSERT_COVERED(HMM_M4);

    HMM_Mat4 Result = {0};

    return (Result);
}

COVERAGE(HMM_M4D, 1)
HMM_INLINE HMM_Mat4 HMM_M4D(float Diagonal)
{
    ASSERT_COVERED(HMM_M4D);

    HMM_Mat4 Result = HMM_M4();

    Result.Elements[0][0] = Diagonal;
    Result.Elements[1][1] = Diagonal;
    Result.Elements[2][2] = Diagonal;
    Result.Elements[3][3] = Diagonal;

    return (Result);
}

COVERAGE(HMM_TransposeM4, 1)
HMM_INLINE HMM_Mat4 HMM_TransposeM4(HMM_Mat4 Matrix)
{
    ASSERT_COVERED(HMM_TransposeM4);

    HMM_Mat4 Result = Matrix;

#ifdef HANDMADE_MATH__USE_SSE
    _MM_TRANSPOSE4_PS(Result.Columns[0].InternalElementsSSE, Result.Columns[1].InternalElementsSSE, Result.Columns[2].InternalElementsSSE, Result.Columns[3].InternalElementsSSE);
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
HMM_INLINE HMM_Mat4 HMM_AddM4(HMM_Mat4 Left, HMM_Mat4 Right)
{
    ASSERT_COVERED(HMM_AddM4);

    HMM_Mat4 Result;

#ifdef HANDMADE_MATH__USE_SSE
    Result.Columns[0].InternalElementsSSE = _mm_add_ps(Left.Columns[0].InternalElementsSSE, Right.Columns[0].InternalElementsSSE);
    Result.Columns[1].InternalElementsSSE = _mm_add_ps(Left.Columns[1].InternalElementsSSE, Right.Columns[1].InternalElementsSSE);
    Result.Columns[2].InternalElementsSSE = _mm_add_ps(Left.Columns[2].InternalElementsSSE, Right.Columns[2].InternalElementsSSE);
    Result.Columns[3].InternalElementsSSE = _mm_add_ps(Left.Columns[3].InternalElementsSSE, Right.Columns[3].InternalElementsSSE);
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
HMM_INLINE HMM_Mat4 HMM_SubM4(HMM_Mat4 Left, HMM_Mat4 Right)
{
    ASSERT_COVERED(HMM_SubM4);

    HMM_Mat4 Result;

#ifdef HANDMADE_MATH__USE_SSE
    Result.Columns[0].InternalElementsSSE = _mm_sub_ps(Left.Columns[0].InternalElementsSSE, Right.Columns[0].InternalElementsSSE);
    Result.Columns[1].InternalElementsSSE = _mm_sub_ps(Left.Columns[1].InternalElementsSSE, Right.Columns[1].InternalElementsSSE);
    Result.Columns[2].InternalElementsSSE = _mm_sub_ps(Left.Columns[2].InternalElementsSSE, Right.Columns[2].InternalElementsSSE);
    Result.Columns[3].InternalElementsSSE = _mm_sub_ps(Left.Columns[3].InternalElementsSSE, Right.Columns[3].InternalElementsSSE);
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
HMM_INLINE HMM_Mat4 HMM_MulM4(HMM_Mat4 Left, HMM_Mat4 Right)
{
    ASSERT_COVERED(HMM_MulM4);

    HMM_Mat4 Result;

    Result.Columns[0] = HMM_LinearCombineV4M4(Right.Columns[0], Left);
    Result.Columns[1] = HMM_LinearCombineV4M4(Right.Columns[1], Left);
    Result.Columns[2] = HMM_LinearCombineV4M4(Right.Columns[2], Left);
    Result.Columns[3] = HMM_LinearCombineV4M4(Right.Columns[3], Left);

    return (Result);
}


COVERAGE(HMM_MulM4F, 1)
HMM_INLINE HMM_Mat4 HMM_MulM4F(HMM_Mat4 Matrix, float Scalar)
{
    ASSERT_COVERED(HMM_MulM4F);

    HMM_Mat4 Result;

#ifdef HANDMADE_MATH__USE_SSE
    __m128 SSEScalar = _mm_set1_ps(Scalar);
    Result.Columns[0].InternalElementsSSE = _mm_mul_ps(Matrix.Columns[0].InternalElementsSSE, SSEScalar);
    Result.Columns[1].InternalElementsSSE = _mm_mul_ps(Matrix.Columns[1].InternalElementsSSE, SSEScalar);
    Result.Columns[2].InternalElementsSSE = _mm_mul_ps(Matrix.Columns[2].InternalElementsSSE, SSEScalar);
    Result.Columns[3].InternalElementsSSE = _mm_mul_ps(Matrix.Columns[3].InternalElementsSSE, SSEScalar);
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

COVERAGE(HMM_MulM4V4, 1)
HMM_INLINE HMM_Vec4 HMM_MulM4V4(HMM_Mat4 Matrix, HMM_Vec4 Vector)
{
    ASSERT_COVERED(HMM_MulM4V4);

    HMM_Vec4 Result;

    Result = HMM_LinearCombineV4M4(Vector, Matrix);

    return (Result);
}


COVERAGE(HMM_DivM4F, 1)
HMM_INLINE HMM_Mat4 HMM_DivM4F(HMM_Mat4 Matrix, float Scalar)
{
    ASSERT_COVERED(HMM_DivM4F);

    HMM_Mat4 Result;

#ifdef HANDMADE_MATH__USE_SSE
    __m128 SSEScalar = _mm_set1_ps(Scalar);
    Result.Columns[0].InternalElementsSSE = _mm_div_ps(Matrix.Columns[0].InternalElementsSSE, SSEScalar);
    Result.Columns[1].InternalElementsSSE = _mm_div_ps(Matrix.Columns[1].InternalElementsSSE, SSEScalar);
    Result.Columns[2].InternalElementsSSE = _mm_div_ps(Matrix.Columns[2].InternalElementsSSE, SSEScalar);
    Result.Columns[3].InternalElementsSSE = _mm_div_ps(Matrix.Columns[3].InternalElementsSSE, SSEScalar);
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

COVERAGE(HMM_DeterminantM4, 1)
HMM_INLINE float HMM_DeterminantM4(HMM_Mat4 Matrix) 
{
    ASSERT_COVERED(HMM_DeterminantM4);
    float Result;

    HMM_Vec3 C01 = HMM_Cross(Matrix.Columns[0].XYZ, Matrix.Columns[1].XYZ);
    HMM_Vec3 C23 = HMM_Cross(Matrix.Columns[2].XYZ, Matrix.Columns[3].XYZ);
    HMM_Vec3 B10 = HMM_SubV3(HMM_MulV3F(Matrix.Columns[0].XYZ, Matrix.Columns[1].W), HMM_MulV3F(Matrix.Columns[1].XYZ,Matrix.Columns[0].W));
    HMM_Vec3 B32 = HMM_SubV3(HMM_MulV3F(Matrix.Columns[2].XYZ, Matrix.Columns[3].W), HMM_MulV3F(Matrix.Columns[3].XYZ, Matrix.Columns[2].W));
    
    Result = HMM_DotV3(C01,B32) + HMM_DotV3(C23,B10);

    return (Result);
}

COVERAGE(HMM_InvGeneralM4, 1);
HMM_INLINE HMM_Mat4 HMM_InvGeneralM4(HMM_Mat4 Matrix) 
{
    ASSERT_COVERED(HMM_InvGeneralM4);
    HMM_Mat4 Result;

    HMM_Vec3 C01 = HMM_Cross(Matrix.Columns[0].XYZ, Matrix.Columns[1].XYZ);
    HMM_Vec3 C23 = HMM_Cross(Matrix.Columns[2].XYZ, Matrix.Columns[3].XYZ);
    HMM_Vec3 B10 = HMM_SubV3(HMM_MulV3F(Matrix.Columns[0].XYZ, Matrix.Columns[1].W), HMM_MulV3F(Matrix.Columns[1].XYZ,Matrix.Columns[0].W));
    HMM_Vec3 B32 = HMM_SubV3(HMM_MulV3F(Matrix.Columns[2].XYZ, Matrix.Columns[3].W), HMM_MulV3F(Matrix.Columns[3].XYZ, Matrix.Columns[2].W));
    
    float InvDeterminant = 1.0f / (HMM_DotV3(C01,B32) + HMM_DotV3(C23,B10));
    C01 = HMM_MulV3F(C01, InvDeterminant);
    C23 = HMM_MulV3F(C23, InvDeterminant);
    B10 = HMM_MulV3F(B10, InvDeterminant);
    B32 = HMM_MulV3F(B32, InvDeterminant);

    Result.Columns[0] = HMM_V4V(HMM_AddV3(HMM_Cross(Matrix.Columns[1].XYZ, B32), HMM_MulV3F(C23, Matrix.Columns[1].W)), -HMM_DotV3(Matrix.Columns[1].XYZ, C23));
    Result.Columns[1] = HMM_V4V(HMM_SubV3(HMM_Cross(B32, Matrix.Columns[0].XYZ), HMM_MulV3F(C23, Matrix.Columns[0].W)), +HMM_DotV3(Matrix.Columns[0].XYZ, C23));
    Result.Columns[2] = HMM_V4V(HMM_AddV3(HMM_Cross(Matrix.Columns[3].XYZ, B10), HMM_MulV3F(C01, Matrix.Columns[3].W)), -HMM_DotV3(Matrix.Columns[3].XYZ, C01));
    Result.Columns[3] = HMM_V4V(HMM_SubV3(HMM_Cross(B10, Matrix.Columns[2].XYZ), HMM_MulV3F(C01, Matrix.Columns[2].W)), +HMM_DotV3(Matrix.Columns[2].XYZ, C01));
        
    return HMM_TransposeM4(Result);
}

/*
 * 3x3 Matrices
 */

HMM_INLINE HMM_Mat3 HMM_M3(void)
{
    HMM_Mat3 Result = {0};

    return (Result);
}

HMM_INLINE HMM_Mat3 HMM_M3D(float Diagonal)
{
    HMM_Mat3 Result = HMM_M3();

    Result.Elements[0][0] = Diagonal;
    Result.Elements[1][1] = Diagonal;
    Result.Elements[2][2] = Diagonal;

    return (Result);
}

HMM_INLINE HMM_Mat3 HMM_TransposeM3(HMM_Mat3 Matrix)
{
    HMM_Mat3 Result = Matrix;

    int Columns;
    for(Columns = 0; Columns < 3; ++Columns)
    {
        int Rows;
        for(Rows = 0; Rows < 3; ++Rows)
        {
            Result.Elements[Rows][Columns] = Matrix.Elements[Columns][Rows];
        }
    }
    
    return (Result);
}

HMM_INLINE HMM_Mat3 HMM_AddM3(HMM_Mat3 Left, HMM_Mat3 Right)
{
    HMM_Mat3 Result;
    int Columns;
    for(Columns = 0; Columns < 3; ++Columns)
    {
        int Rows;
        for(Rows = 0; Rows < 3; ++Rows)
        {
            Result.Elements[Columns][Rows] = Left.Elements[Columns][Rows] + Right.Elements[Columns][Rows];
        }
    }

   
    return (Result);    
}

HMM_INLINE HMM_Mat3 HMM_SubM3(HMM_Mat3 Left, HMM_Mat3 Right)
{
    HMM_Mat3 Result;
    int Columns;
    for(Columns = 0; Columns < 3; ++Columns)
    {
        int Rows;
        for(Rows = 0; Rows < 3; ++Rows)
        {
            Result.Elements[Columns][Rows] = Left.Elements[Columns][Rows] - Right.Elements[Columns][Rows];
        }
    }
    return (Result);
}

HMM_INLINE HMM_Vec3 HMM_MulM3V3(HMM_Mat3 Matrix, HMM_Vec3 Vector)
{
    HMM_Vec3 Result = {0};
    int Columns, Rows;
    for(Rows = 0; Rows < 3; ++Rows)
    {
        float Sum = 0.0f;
        for(Columns = 0; Columns < 3; ++Columns)
        {
            Sum += Matrix.Elements[Columns][Rows] * Vector.Elements[Columns];
        }
        Result.Elements[Rows] = Sum;
    }
    return (Result);    
}

HMM_INLINE HMM_Mat3 HMM_MulM3(HMM_Mat3 Left, HMM_Mat3 Right)
{
    HMM_Mat3 Result;

    Result.Columns[0] = HMM_MulM3V3(Left, Right.Columns[0]);
    Result.Columns[1] = HMM_MulM3V3(Left, Right.Columns[1]);
    Result.Columns[2] = HMM_MulM3V3(Left, Right.Columns[2]);

    return (Result);    
}

HMM_INLINE HMM_Mat3 HMM_MulM3F(HMM_Mat3 Matrix, float Scalar)
{
    HMM_Mat3 Result;
    int Columns;
    for(Columns = 0; Columns < 3; ++Columns)
    {
        int Rows;
        for(Rows = 0; Rows < 3; ++Rows)
        {
            Result.Elements[Columns][Rows] = Matrix.Elements[Columns][Rows] * Scalar;
        }
    }
    return (Result);            
}

HMM_INLINE HMM_Mat3 HMM_DivM3F(HMM_Mat3 Matrix, float Scalar)
{
    HMM_Mat3 Result;
    int Columns;
    for(Columns = 0; Columns < 3; ++Columns)
    {
        int Rows;
        for(Rows = 0; Rows < 3; ++Rows)
        {
            Result.Elements[Columns][Rows] = Matrix.Elements[Columns][Rows] / Scalar;
        }
    }
    return (Result);                    
}

COVERAGE(HMM_DeterminantM3, 1)
HMM_INLINE float HMM_DeterminantM3(HMM_Mat3 Matrix) 
{
    ASSERT_COVERED(HMM_DeterminantM3);
    float Result;

    HMM_Mat3 Cross;
    Cross.Columns[0] = HMM_Cross(Matrix.Columns[1], Matrix.Columns[2]);
    Cross.Columns[1] = HMM_Cross(Matrix.Columns[2], Matrix.Columns[0]);
    Cross.Columns[2] = HMM_Cross(Matrix.Columns[0], Matrix.Columns[1]);

    Result = HMM_DotV3(Cross.Columns[2], Matrix.Columns[2]);

    return (Result);
}

COVERAGE(HMM_InvGeneralM3, 1);
HMM_INLINE HMM_Mat3 HMM_InvGeneralM3(HMM_Mat3 Matrix) 
{
    ASSERT_COVERED(HMM_InvGeneralM3);
    HMM_Mat3 Result;

    HMM_Mat3 Cross;
    Cross.Columns[0] = HMM_Cross(Matrix.Columns[1], Matrix.Columns[2]);
    Cross.Columns[1] = HMM_Cross(Matrix.Columns[2], Matrix.Columns[0]);
    Cross.Columns[2] = HMM_Cross(Matrix.Columns[0], Matrix.Columns[1]);

    float InvDeterminant = 1.0f / HMM_DotV3(Cross.Columns[2], Matrix.Columns[2]);

    Result.Columns[0] = HMM_MulV3F(Cross.Columns[0], InvDeterminant);
    Result.Columns[1] = HMM_MulV3F(Cross.Columns[1], InvDeterminant);
    Result.Columns[2] = HMM_MulV3F(Cross.Columns[2], InvDeterminant);

    return HMM_TransposeM3(Result);
}

/*
 * 2x2 Matrices
 */

HMM_INLINE HMM_Mat2 HMM_M2(void)
{
    HMM_Mat2 Result = {0};

    return (Result);
}

HMM_INLINE HMM_Mat2 HMM_M2D(float Diagonal)
{
    HMM_Mat2 Result = HMM_M2();

    Result.Elements[0][0] = Diagonal;
    Result.Elements[1][1] = Diagonal;

    return (Result);
}

HMM_INLINE HMM_Mat2 HMM_TransposeM2(HMM_Mat2 Matrix)
{
    HMM_Mat2 Result = Matrix;

    int Columns, Rows;
    for(Columns = 0; Columns < 2; ++Columns)
    {
        for(Rows = 0; Rows < 2; ++Rows)
        {
            Result.Elements[Rows][Columns] = Matrix.Elements[Columns][Rows];
        }
    }
    
    return (Result);
}

HMM_INLINE HMM_Mat2 HMM_AddM2(HMM_Mat2 Left, HMM_Mat2 Right)
{
    HMM_Mat2 Result;
    int Columns;
    for(Columns = 0; Columns < 2; ++Columns)
    {
        int Rows;
        for(Rows = 0; Rows < 2; ++Rows)
        {
            Result.Elements[Columns][Rows] = Left.Elements[Columns][Rows] + Right.Elements[Columns][Rows];
        }
    }

   
    return (Result);    
}

HMM_INLINE HMM_Mat2 HMM_SubM2(HMM_Mat2 Left, HMM_Mat2 Right)
{
    HMM_Mat2 Result;
    int Columns;
    for(Columns = 0; Columns < 2; ++Columns)
    {
        int Rows;
        for(Rows = 0; Rows < 2; ++Rows)
        {
            Result.Elements[Columns][Rows] = Left.Elements[Columns][Rows] - Right.Elements[Columns][Rows];
        }
    }
    return (Result);
}

HMM_INLINE HMM_Vec2 HMM_MulM2V2(HMM_Mat2 Matrix, HMM_Vec2 Vector)
{
    HMM_Vec2 Result;
    int Columns, Rows;
    for(Rows = 0; Rows < 2; ++Rows)
    {
        float Sum = 0.0f;
        for(Columns = 0; Columns < 2; ++Columns)
        {
             Sum += Matrix.Elements[Columns][Rows] * Vector.Elements[Columns];
        }
        Result.Elements[Rows] = Sum;
    }
    return (Result);    
}

HMM_INLINE HMM_Mat2 HMM_MulM2(HMM_Mat2 Left, HMM_Mat2 Right)
{
    HMM_Mat2 Result;

    Result.Columns[0] = HMM_MulM2V2(Left, Right.Columns[0]);
    Result.Columns[1] = HMM_MulM2V2(Left, Right.Columns[1]);

    return (Result);    
}

HMM_INLINE HMM_Mat2 HMM_MulM2F(HMM_Mat2 Matrix, float Scalar)
{
    HMM_Mat2 Result;
    int Columns;
    for(Columns = 0; Columns < 2; ++Columns)
    {
        int Rows;
        for(Rows = 0; Rows < 2; ++Rows)
        {
            Result.Elements[Columns][Rows] = Matrix.Elements[Columns][Rows] * Scalar;
        }
    }
    return (Result);            
}

HMM_INLINE HMM_Mat2 HMM_DivM2F(HMM_Mat2 Matrix, float Scalar)
{
    HMM_Mat2 Result;
    int Columns;
    for(Columns = 0; Columns < 2; ++Columns)
    {
        int Rows;
        for(Rows = 0; Rows < 2; ++Rows)
        {
            Result.Elements[Columns][Rows] = Matrix.Elements[Columns][Rows] / Scalar;
        }
    }
    return (Result);                    
}

COVERAGE(HMM_DeterminantM2, 1)
HMM_INLINE float HMM_DeterminantM2(HMM_Mat2 Matrix) 
{
    ASSERT_COVERED(HMM_DeterminantM2);
    float Result;

    Result =  Matrix.Elements[0][0]*Matrix.Elements[1][1] - Matrix.Elements[0][1]*Matrix.Elements[1][0];

    return (Result);
}


COVERAGE(HMM_InvGeneralM2, 1);
HMM_INLINE HMM_Mat2 HMM_InvGeneralM2(HMM_Mat2 Matrix) 
{
    ASSERT_COVERED(HMM_InvGeneralM2);
    HMM_Mat2 Result;

    float InvDeterminant = 1.0f / HMM_DeterminantM2(Matrix);
    Result.Elements[0][0] = InvDeterminant * +Matrix.Elements[1][1];
    Result.Elements[1][1] = InvDeterminant * +Matrix.Elements[0][0];
    Result.Elements[0][1] = InvDeterminant * -Matrix.Elements[0][1];
    Result.Elements[1][0] = InvDeterminant * -Matrix.Elements[1][0];

    return (Result);
}

/*
 * Common graphics transformations
 */

COVERAGE(HMM_Orthographic_RH, 1)
HMM_INLINE HMM_Mat4 HMM_Orthographic_RH(float Left, float Right, float Bottom, float Top, float Near, float Far)
{
    ASSERT_COVERED(HMM_Orthographic_RH);

    HMM_Mat4 Result = HMM_M4();

    Result.Elements[0][0] = 2.0f / (Right - Left);
    Result.Elements[1][1] = 2.0f / (Top - Bottom);
    Result.Elements[2][2] = 2.0f / (Near - Far);
    Result.Elements[3][3] = 1.0f;

    Result.Elements[3][0] = (Left + Right) / (Left - Right);
    Result.Elements[3][1] = (Bottom + Top) / (Bottom - Top);
    Result.Elements[3][2] = (Far + Near) / (Near - Far);

    return (Result);
}

COVERAGE(HMM_Orthographic_LH, 1)
HMM_INLINE HMM_Mat4 HMM_Orthographic_LH(float Left, float Right, float Bottom, float Top, float Near, float Far)
{
    ASSERT_COVERED(HMM_Orthographic_LH);

    HMM_Mat4 Result = HMM_Orthographic_RH(Left, Right, Bottom, Top, Near, Far);
    Result.Elements[2][2] = -Result.Elements[2][2];
    
    return (Result);
}

COVERAGE(HMM_InvOrthographic, 1) 
HMM_INLINE HMM_Mat4 HMM_InvOrthographic(HMM_Mat4 OrthoMatrix)
{
    ASSERT_COVERED(HMM_InvOrthographic);
    HMM_Mat4 Result = HMM_M4();

    Result.Elements[0][0] = 1.0f / OrthoMatrix.Elements[0][0];
    Result.Elements[1][1] = 1.0f / OrthoMatrix.Elements[1][1];
    Result.Elements[2][2] = 1.0f / OrthoMatrix.Elements[2][2];
    Result.Elements[3][3] = 1.0f;
    
    Result.Elements[3][0] = -OrthoMatrix.Elements[3][0] * Result.Elements[0][0];
    Result.Elements[3][1] = -OrthoMatrix.Elements[3][1] * Result.Elements[1][1];
    Result.Elements[3][2] = -OrthoMatrix.Elements[3][2] * Result.Elements[2][2];

    return (Result);
}

COVERAGE(HMM_Perspective_RH, 1)
HMM_INLINE HMM_Mat4 HMM_Perspective_RH(float FOV, float AspectRatio, float Near, float Far)
{
    ASSERT_COVERED(HMM_Perspective_RH);

    HMM_Mat4 Result = HMM_M4();

    // See https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/gluPerspective.xml

    float Cotangent = 1.0f / HMM_TanF(FOV / 2.0);
    
    Result.Elements[0][0] = Cotangent / AspectRatio;
    Result.Elements[1][1] = Cotangent;
    Result.Elements[2][2] = (Near + Far) / (Near - Far);

    Result.Elements[2][3] = -1.0f;
    Result.Elements[3][2] = (2.0f * Near * Far) / (Near - Far);

    return (Result);
}

COVERAGE(HMM_Perspective_LH, 1)
HMM_INLINE HMM_Mat4 HMM_Perspective_LH(float FOV, float AspectRatio, float Near, float Far)
{ 
    ASSERT_COVERED(HMM_Perspective_LH);

    HMM_Mat4 Result = HMM_Perspective_RH(FOV, AspectRatio, Near, Far);
    Result.Elements[2][3] = +1.0f;
  
    return (Result);
}

COVERAGE(HMM_InvPerspective, 1)
HMM_INLINE HMM_Mat4 HMM_InvPerspective(HMM_Mat4 PerspectiveMatrix) 
{
    ASSERT_COVERED(HMM_InvPerspective);

    HMM_Mat4 Result = HMM_M4();
    Result.Elements[0][0] = 1.0f / PerspectiveMatrix.Elements[0][0];
    Result.Elements[1][1] = 1.0f / PerspectiveMatrix.Elements[1][1];
    Result.Elements[2][2] = 0.0f;

    Result.Elements[2][3] = 1.0f / PerspectiveMatrix.Elements[3][2];
    Result.Elements[3][3] = PerspectiveMatrix.Elements[2][2] * Result.Elements[2][3];
    Result.Elements[3][2] = PerspectiveMatrix.Elements[2][3];

    return (Result);
}

COVERAGE(HMM_Translate, 1)
HMM_INLINE HMM_Mat4 HMM_Translate(HMM_Vec3 Translation)
{
    ASSERT_COVERED(HMM_Translate);

    HMM_Mat4 Result = HMM_M4D(1.0f);

    Result.Elements[3][0] = Translation.X;
    Result.Elements[3][1] = Translation.Y;
    Result.Elements[3][2] = Translation.Z;

    return (Result);
}

COVERAGE(HMM_InvTranslate, 1)
HMM_INLINE HMM_Mat4 HMM_InvTranslate(HMM_Mat4 TranslationMatrix)
{
    ASSERT_COVERED(HMM_InvTranslate);

    HMM_Mat4 Result = TranslationMatrix;

    Result.Elements[3][0] = -Result.Elements[3][0];
    Result.Elements[3][1] = -Result.Elements[3][1];
    Result.Elements[3][2] = -Result.Elements[3][2];

    return (Result);
}

COVERAGE(HMM_Rotate_RH, 1)
HMM_INLINE HMM_Mat4 HMM_Rotate_RH(float Angle, HMM_Vec3 Axis)
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

    return (Result);
}


COVERAGE(HMM_Rotate_LH, 1)
HMM_INLINE HMM_Mat4 HMM_Rotate_LH(float Angle, HMM_Vec3 Axis)
{
    ASSERT_COVERED(HMM_Rotate_LH);

    /* NOTE(lcf): Matrix will be inverse/transpose of RH. */
    return HMM_Rotate_RH(-Angle, Axis);
}

COVERAGE(HMM_InvRotate, 1)
HMM_INLINE HMM_Mat4 HMM_InvRotate(HMM_Mat4 RotationMatrix)
{
    ASSERT_COVERED(HMM_InvRotate);

    return HMM_TransposeM4(RotationMatrix);
}

COVERAGE(HMM_Scale, 1)
HMM_INLINE HMM_Mat4 HMM_Scale(HMM_Vec3 Scale)
{
    ASSERT_COVERED(HMM_Scale);

    HMM_Mat4 Result = HMM_M4D(1.0f);

    Result.Elements[0][0] = Scale.X;
    Result.Elements[1][1] = Scale.Y;
    Result.Elements[2][2] = Scale.Z;

    return (Result);
}

COVERAGE(HMM_InvScale, 1)
HMM_INLINE HMM_Mat4 HMM_InvScale(HMM_Mat4 ScaleMatrix) 
{
    ASSERT_COVERED(HMM_InvScale);

    HMM_Mat4 Result = ScaleMatrix;

    Result.Elements[0][0] = 1.0f / Result.Elements[0][0];
    Result.Elements[1][1] = 1.0f / Result.Elements[1][1];
    Result.Elements[2][2] = 1.0f / Result.Elements[2][2];

    return (Result);    
}


HMM_INLINE HMM_Mat4 _HMM_LookAt(HMM_Vec3 F,  HMM_Vec3 S, HMM_Vec3 U,  HMM_Vec3 Eye)
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

    return (Result);
}

COVERAGE(HMM_LookAt_RH, 1)
HMM_INLINE HMM_Mat4 HMM_LookAt_RH(HMM_Vec3 Eye, HMM_Vec3 Center, HMM_Vec3 Up)
{
    ASSERT_COVERED(HMM_LookAt_RH);

    HMM_Vec3 F = HMM_NormV3(HMM_SubV3(Center, Eye));
    HMM_Vec3 S = HMM_NormV3(HMM_Cross(F, Up));
    HMM_Vec3 U = HMM_Cross(S, F);

    return _HMM_LookAt(F, S, U, Eye);
}

COVERAGE(HMM_LookAt_LH, 1)
HMM_INLINE HMM_Mat4 HMM_LookAt_LH(HMM_Vec3 Eye, HMM_Vec3 Center, HMM_Vec3 Up)
{
    ASSERT_COVERED(HMM_LookAt_LH);

    HMM_Vec3 F = HMM_NormV3(HMM_SubV3(Eye, Center));
    HMM_Vec3 S = HMM_NormV3(HMM_Cross(F, Up));
    HMM_Vec3 U = HMM_Cross(S, F);

    return _HMM_LookAt(F, S, U, Eye);
}

COVERAGE(HMM_InvLookAt, 1)
HMM_INLINE HMM_Mat4 HMM_InvLookAt(HMM_Mat4 Matrix)
{
    ASSERT_COVERED(HMM_InvLookAt);
    HMM_Mat4 Result;

    HMM_Mat3 Rotation = HMM_M3();
    Rotation.Columns[0] = Matrix.Columns[0].XYZ;
    Rotation.Columns[1] = Matrix.Columns[1].XYZ;
    Rotation.Columns[2] = Matrix.Columns[2].XYZ;
    Rotation = HMM_TransposeM3(Rotation);

    Result.Columns[0] = HMM_V4V(Rotation.Columns[0], 0.0f);
    Result.Columns[1] = HMM_V4V(Rotation.Columns[1], 0.0f);
    Result.Columns[2] = HMM_V4V(Rotation.Columns[2], 0.0f);
    Result.Columns[3] = HMM_MulV4F(Matrix.Columns[3], -1.0f);
    Result.Elements[3][0] = -1.0 * Matrix.Elements[3][0] /
        (Rotation.Elements[0][0] + Rotation.Elements[0][1] + Rotation.Elements[0][2]);
    Result.Elements[3][1] = -1.0 * Matrix.Elements[3][1] /
        (Rotation.Elements[1][0] + Rotation.Elements[1][1] + Rotation.Elements[1][2]);
    Result.Elements[3][2] = -1.0 * Matrix.Elements[3][2] /
        (Rotation.Elements[2][0] + Rotation.Elements[2][1] + Rotation.Elements[2][2]);
    Result.Elements[3][3] = 1.0;

    return (Result);
}

/*
 * Quaternion operations
 */

COVERAGE(HMM_Q, 1)
HMM_INLINE HMM_Quat HMM_Q(float X, float Y, float Z, float W)
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
HMM_INLINE HMM_Quat HMM_QV4(HMM_Vec4 Vector)
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
HMM_INLINE HMM_Quat HMM_AddQ(HMM_Quat Left, HMM_Quat Right)
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
HMM_INLINE HMM_Quat HMM_SubQ(HMM_Quat Left, HMM_Quat Right)
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
HMM_INLINE HMM_Quat HMM_MulQ(HMM_Quat Left, HMM_Quat Right)
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
HMM_INLINE HMM_Quat HMM_MulQF(HMM_Quat Left, float Multiplicative)
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
HMM_INLINE HMM_Quat HMM_DivQF(HMM_Quat Left, float Divnd)
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
HMM_INLINE float HMM_DotQ(HMM_Quat Left, HMM_Quat Right)
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
HMM_INLINE HMM_Quat HMM_InvQ(HMM_Quat Left)
{
    ASSERT_COVERED(HMM_InvQ);
    
    HMM_Quat Result;

    Result.X = -Left.X;
    Result.Y = -Left.Y;
    Result.Z = -Left.Z;
    Result.W = Left.W;

    Result = HMM_DivQF(Result, (HMM_DotQ(Left, Left)));

    return (Result);
}


COVERAGE(HMM_NormQ, 1)
HMM_INLINE HMM_Quat HMM_NormQ(HMM_Quat Quat)
{
    ASSERT_COVERED(HMM_NormQ);

    /* NOTE(lcf): Take advantage of SSE implementation in HMM_NormV4 */
    HMM_Vec4 Vec = {Quat.X, Quat.Y, Quat.Z, Quat.W};
    Vec = HMM_NormV4(Vec);
    HMM_Quat Result = {Vec.X, Vec.Y, Vec.Z, Vec.W};

    return (Result);
}

HMM_INLINE HMM_Quat HMM_MixQ(HMM_Quat Left, float MixLeft, HMM_Quat Right, float MixRight) {
    HMM_Quat Result;
#ifdef HANDMADE_MATH__USE_SSE
    __m128 ScalarLeft = _mm_set1_ps(MixLeft);
    __m128 ScalarRight = _mm_set1_ps(MixRight);
    __m128 SSEResultOne = _mm_mul_ps(Left.InternalElementsSSE, ScalarLeft);
    __m128 SSEResultTwo = _mm_mul_ps(Right.InternalElementsSSE, ScalarRight);
    Result.InternalElementsSSE = _mm_add_ps(SSEResultOne, SSEResultTwo);
#else
    Result.X = Left.X*MixLeft + Right.X*MixRight;
    Result.Y = Left.Y*MixLeft + Right.Y*MixRight;
    Result.Z = Left.Z*MixLeft + Right.Z*MixRight;
    Result.W = Left.W*MixLeft + Right.W*MixRight;
#endif
    return (Result);
}

COVERAGE(HMM_NLerp, 1)
HMM_INLINE HMM_Quat HMM_NLerp(HMM_Quat Left, float Time, HMM_Quat Right)
{
    ASSERT_COVERED(HMM_NLerp);

    HMM_Quat Result = HMM_MixQ(Left, 1.0-Time, Right, Time);
    Result = HMM_NormQ(Result);

    return (Result);
}

COVERAGE(HMM_SLerp, 1)
HMM_INLINE HMM_Quat HMM_SLerp(HMM_Quat Left, float Time, HMM_Quat Right)
{
    ASSERT_COVERED(HMM_SLerp);

    HMM_Quat Result;

    float Cos_Theta = HMM_DotQ(Left, Right);

    if (Cos_Theta < 0.0) { /* NOTE(lcf): Take shortest path on Hyper-sphere */
        Cos_Theta = -Cos_Theta;
        Right = HMM_Q(-Right.X, -Right.Y, -Right.Z, -Right.W);
    }
    
    /* Use Normalized Linear interpolation when vectors are roughly not L.I. */
    if (Cos_Theta > 0.9995) {
        Result = HMM_NLerp(Left, Time, Right);
    } else {
        float Angle = HMM_ACosF(Cos_Theta);
        float MixLeft = HMM_SinF((1.0f - Time) * Angle);
        float MixRight = HMM_SinF(Time * Angle);

        Result = HMM_MixQ(Left, MixLeft, Right, MixRight);
        Result = HMM_NormQ(Result);

        /* /\* NOTE(lcf): Exactly accurate to above to within floating point accuracy on
         current tests. *\/ */
        /* float ca = Cos_Theta; */
        /* float d = HMM_ABS(ca); */
        /* float t = Time; */
        /* float A = 1.0904f + d * (-3.2452f + d * (3.55645f - d * 1.43519f)); */
        /* float B = 0.848013f + d * (-1.06021f + d * 0.215638f); */
        /* float k = A * (t - 0.5f) * (t - 0.5f) + B; */
        /* float ot = t + t * (t - 0.5f) * (t - 1) * k; */
        /* Result = HMM_NLerp(Left, ca > 0 ? ot : -ot, Right); */

        /* NOTE(lcf): what I came up with.
           REF: desmos.com/calculator/8kfumvumrx
           REF: desmos.com/calculator/myh0kjk5gs */
        /* float D = (1.0f-Cos_Theta*Cos_Theta)/6.0f; */
        /* float tr = Time; */
        /* float tl = 1-Time; */
        /* float mr = tr - tr*tr*tr*D; */
        /* float ml = tl - tl*tl*tl*D; */
        /* Result = HMM_MixQ(Left, ml, Right, mr); */
        /* Result = HMM_NormQ(Result); */
    }
    
    return (Result);
}

COVERAGE(HMM_QToM4, 1)
HMM_INLINE HMM_Mat4 HMM_QToM4(HMM_Quat Left)
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
COVERAGE(HMM_M4ToQ_RH, 4)
HMM_INLINE HMM_Quat HMM_M4ToQ_RH(HMM_Mat4 M)
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
HMM_INLINE HMM_Quat HMM_M4ToQ_LH(HMM_Mat4 M)
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
HMM_INLINE HMM_Quat HMM_QFromAxisAngle_RH(HMM_Vec3 Axis, float AngleOfRotation)
{
    ASSERT_COVERED(HMM_QFromAxisAngle_RH);

    HMM_Quat Result;

    HMM_Vec3 AxisNormalized = HMM_NormV3(Axis);
    float SineOfRotation = HMM_SinF(AngleOfRotation / 2.0f);

    Result.XYZ = HMM_MulV3F(AxisNormalized, SineOfRotation);
    Result.W = HMM_CosF(AngleOfRotation / 2.0f);

    return (Result);
}

COVERAGE(HMM_QFromAxisAngle_LH, 1)
HMM_INLINE HMM_Quat HMM_QFromAxisAngle_LH(HMM_Vec3 Axis, float AngleOfRotation)
{
    ASSERT_COVERED(HMM_QFromAxisAngle_LH);

    return HMM_QFromAxisAngle_RH(Axis, -AngleOfRotation);
}


#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

COVERAGE(HMM_LenV2CPP, 1)
HMM_INLINE float HMM_Len(HMM_Vec2 A)
{
    ASSERT_COVERED(HMM_LenV2CPP);

    float Result = HMM_LenV2(A);
    return (Result);
}

COVERAGE(HMM_LenV3CPP, 1)
HMM_INLINE float HMM_Len(HMM_Vec3 A)
{
    ASSERT_COVERED(HMM_LenV3CPP);

    float Result = HMM_LenV3(A);

    return (Result);
}

COVERAGE(HMM_LenV4CPP, 1)
HMM_INLINE float HMM_Len(HMM_Vec4 A)
{
    ASSERT_COVERED(HMM_LenV4CPP);

    float Result = HMM_LenV4(A);

    return (Result);
}

COVERAGE(HMM_LenSqrV2CPP, 1)
HMM_INLINE float HMM_LenSqr(HMM_Vec2 A)
{
    ASSERT_COVERED(HMM_LenSqrV2CPP);

    float Result = HMM_LenSqrV2(A);

    return (Result);
}

COVERAGE(HMM_LenSqrV3CPP, 1)
HMM_INLINE float HMM_LenSqr(HMM_Vec3 A)
{
    ASSERT_COVERED(HMM_LenSqrV3CPP);

    float Result = HMM_LenSqrV3(A);

    return (Result);
}

COVERAGE(HMM_LenSqrV4CPP, 1)
HMM_INLINE float HMM_LenSqr(HMM_Vec4 A)
{
    ASSERT_COVERED(HMM_LenSqrV4CPP);

    float Result = HMM_LenSqrV4(A);

    return (Result);
}

COVERAGE(HMM_NormV2CPP, 1)
HMM_INLINE HMM_Vec2 HMM_Norm(HMM_Vec2 A)
{
    ASSERT_COVERED(HMM_NormV2CPP);

    HMM_Vec2 Result = HMM_NormV2(A);

    return (Result);
}

COVERAGE(HMM_NormV3CPP, 1)
HMM_INLINE HMM_Vec3 HMM_Norm(HMM_Vec3 A)
{
    ASSERT_COVERED(HMM_NormV3CPP);

    HMM_Vec3 Result = HMM_NormV3(A);

    return (Result);
}

COVERAGE(HMM_NormV4CPP, 1)
HMM_INLINE HMM_Vec4 HMM_Norm(HMM_Vec4 A)
{
    ASSERT_COVERED(HMM_NormV4CPP);

    HMM_Vec4 Result = HMM_NormV4(A);

    return (Result);
}

COVERAGE(HMM_NormQCPP, 1)
HMM_INLINE HMM_Quat HMM_Norm(HMM_Quat A)
{
    ASSERT_COVERED(HMM_NormQCPP);

    HMM_Quat Result = HMM_NormQ(A);

    return (Result);
}

COVERAGE(HMM_DotV2CPP, 1)
HMM_INLINE float HMM_Dot(HMM_Vec2 Left, HMM_Vec2 VecTwo)
{
    ASSERT_COVERED(HMM_DotV2CPP);

    float Result = HMM_DotV2(Left, VecTwo);

    return (Result);
}

COVERAGE(HMM_DotV3CPP, 1)
HMM_INLINE float HMM_Dot(HMM_Vec3 Left, HMM_Vec3 VecTwo)
{
    ASSERT_COVERED(HMM_DotV3CPP);

    float Result = HMM_DotV3(Left, VecTwo);

    return (Result);
}

COVERAGE(HMM_DotV4CPP, 1)
HMM_INLINE float HMM_Dot(HMM_Vec4 Left, HMM_Vec4 VecTwo)
{
    ASSERT_COVERED(HMM_DotV4CPP);

    float Result = HMM_DotV4(Left, VecTwo);

    return (Result);
}

HMM_INLINE HMM_Mat2 HMM_Transpose(HMM_Mat2 Matrix)
{
    HMM_Mat2 Result = HMM_TransposeM2(Matrix);
    return (Result);
}

HMM_INLINE HMM_Mat3 HMM_Transpose(HMM_Mat3 Matrix)
{
    HMM_Mat3 Result = HMM_TransposeM3(Matrix);
    return (Result);
}

HMM_INLINE HMM_Mat4 HMM_Transpose(HMM_Mat4 Matrix)
{
    HMM_Mat4 Result = HMM_TransposeM4(Matrix);
    return (Result);
}

HMM_INLINE float HMM_Determinant(HMM_Mat2 Matrix)
{
    float Result = HMM_DeterminantM2(Matrix);
    return (Result);
}

HMM_INLINE float HMM_Determinant(HMM_Mat3 Matrix)
{
    float Result = HMM_DeterminantM3(Matrix);
    return (Result);
}

HMM_INLINE float HMM_Determinant(HMM_Mat4 Matrix)
{
    float Result = HMM_DeterminantM4(Matrix);
    return (Result);
}

HMM_INLINE HMM_Mat2 HMM_InvGeneral(HMM_Mat2 Matrix)
{
    HMM_Mat2 Result = HMM_InvGeneralM2(Matrix);
    return (Result);
}

HMM_INLINE HMM_Mat3 HMM_InvGeneral(HMM_Mat3 Matrix)
{
    HMM_Mat3 Result = HMM_InvGeneralM3(Matrix);
    return (Result);
}

HMM_INLINE HMM_Mat4 HMM_InvGeneral(HMM_Mat4 Matrix)
{
    HMM_Mat4 Result = HMM_InvGeneralM4(Matrix);
    return (Result);
}

COVERAGE(HMM_DotQCPP, 1)
HMM_INLINE float HMM_Dot(HMM_Quat QuatOne, HMM_Quat QuatTwo)
{
    ASSERT_COVERED(HMM_DotQCPP);

    float Result = HMM_DotQ(QuatOne, QuatTwo);

    return (Result);
}

COVERAGE(HMM_AddV2CPP, 1)
HMM_INLINE HMM_Vec2 HMM_Add(HMM_Vec2 Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_AddV2CPP);

    HMM_Vec2 Result = HMM_AddV2(Left, Right);

    return (Result);
}

COVERAGE(HMM_AddV3CPP, 1)
HMM_INLINE HMM_Vec3 HMM_Add(HMM_Vec3 Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_AddV3CPP);

    HMM_Vec3 Result = HMM_AddV3(Left, Right);

    return (Result);
}

COVERAGE(HMM_AddV4CPP, 1)
HMM_INLINE HMM_Vec4 HMM_Add(HMM_Vec4 Left, HMM_Vec4 Right)
{
    ASSERT_COVERED(HMM_AddV4CPP);

    HMM_Vec4 Result = HMM_AddV4(Left, Right);

    return (Result);
}

HMM_INLINE HMM_Mat2 HMM_Add(HMM_Mat2 Left, HMM_Mat2 Right)
{
    HMM_Mat2 Result = HMM_AddM2(Left, Right);
    return (Result);
}

HMM_INLINE HMM_Mat3 HMM_Add(HMM_Mat3 Left, HMM_Mat3 Right)
{
    HMM_Mat3 Result = HMM_AddM3(Left, Right);
    return (Result);
}

COVERAGE(HMM_AddM4CPP, 1)
HMM_INLINE HMM_Mat4 HMM_Add(HMM_Mat4 Left, HMM_Mat4 Right)
{
    ASSERT_COVERED(HMM_AddM4CPP);

    HMM_Mat4 Result = HMM_AddM4(Left, Right);

    return (Result);
}

COVERAGE(HMM_AddQCPP, 1)
HMM_INLINE HMM_Quat HMM_Add(HMM_Quat Left, HMM_Quat Right)
{
    ASSERT_COVERED(HMM_AddQCPP);

    HMM_Quat Result = HMM_AddQ(Left, Right);

    return (Result);
}

COVERAGE(HMM_SubV2CPP, 1)
HMM_INLINE HMM_Vec2 HMM_Sub(HMM_Vec2 Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_SubV2CPP);

    HMM_Vec2 Result = HMM_SubV2(Left, Right);

    return (Result);
}

COVERAGE(HMM_SubV3CPP, 1)
HMM_INLINE HMM_Vec3 HMM_Sub(HMM_Vec3 Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_SubV3CPP);

    HMM_Vec3 Result = HMM_SubV3(Left, Right);

    return (Result);
}

COVERAGE(HMM_SubV4CPP, 1)
HMM_INLINE HMM_Vec4 HMM_Sub(HMM_Vec4 Left, HMM_Vec4 Right)
{
    ASSERT_COVERED(HMM_SubV4CPP);

    HMM_Vec4 Result = HMM_SubV4(Left, Right);

    return (Result);
}

HMM_INLINE HMM_Mat2 HMM_Sub(HMM_Mat2 Left, HMM_Mat2 Right)
{
    HMM_Mat2 Result = HMM_SubM2(Left, Right);
    return (Result);
}

HMM_INLINE HMM_Mat3 HMM_Sub(HMM_Mat3 Left, HMM_Mat3 Right)
{
    HMM_Mat3 Result = HMM_SubM3(Left, Right);
    return (Result);
}

COVERAGE(HMM_SubM4CPP, 1)
HMM_INLINE HMM_Mat4 HMM_Sub(HMM_Mat4 Left, HMM_Mat4 Right)
{
    ASSERT_COVERED(HMM_SubM4CPP);

    HMM_Mat4 Result = HMM_SubM4(Left, Right);

    return (Result);
}

COVERAGE(HMM_SubQCPP, 1)
HMM_INLINE HMM_Quat HMM_Sub(HMM_Quat Left, HMM_Quat Right)
{
    ASSERT_COVERED(HMM_SubQCPP);

    HMM_Quat Result = HMM_SubQ(Left, Right);

    return (Result);
}

COVERAGE(HMM_MulV2CPP, 1)
HMM_INLINE HMM_Vec2 HMM_Mul(HMM_Vec2 Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_MulV2CPP);

    HMM_Vec2 Result = HMM_MulV2(Left, Right);

    return (Result);
}

COVERAGE(HMM_MulV2FCPP, 1)
HMM_INLINE HMM_Vec2 HMM_Mul(HMM_Vec2 Left, float Right)
{
    ASSERT_COVERED(HMM_MulV2FCPP);

    HMM_Vec2 Result = HMM_MulV2F(Left, Right);

    return (Result);
}

COVERAGE(HMM_MulV3CPP, 1)
HMM_INLINE HMM_Vec3 HMM_Mul(HMM_Vec3 Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_MulV3CPP);

    HMM_Vec3 Result = HMM_MulV3(Left, Right);

    return (Result);
}

COVERAGE(HMM_MulV3FCPP, 1)
HMM_INLINE HMM_Vec3 HMM_Mul(HMM_Vec3 Left, float Right)
{
    ASSERT_COVERED(HMM_MulV3FCPP);

    HMM_Vec3 Result = HMM_MulV3F(Left, Right);

    return (Result);
}

COVERAGE(HMM_MulV4CPP, 1)
HMM_INLINE HMM_Vec4 HMM_Mul(HMM_Vec4 Left, HMM_Vec4 Right)
{
    ASSERT_COVERED(HMM_MulV4CPP);

    HMM_Vec4 Result = HMM_MulV4(Left, Right);

    return (Result);
}

COVERAGE(HMM_MulV4FCPP, 1)
HMM_INLINE HMM_Vec4 HMM_Mul(HMM_Vec4 Left, float Right)
{
    ASSERT_COVERED(HMM_MulV4FCPP);

    HMM_Vec4 Result = HMM_MulV4F(Left, Right);

    return (Result);
}

HMM_INLINE HMM_Mat2 HMM_Mul(HMM_Mat2 Left, HMM_Mat2 Right)
{
    HMM_Mat2 Result = HMM_MulM2(Left, Right);
    return (Result);
}

HMM_INLINE HMM_Mat3 HMM_Mul(HMM_Mat3 Left, HMM_Mat3 Right)
{
    HMM_Mat3 Result = HMM_MulM3(Left, Right);
    return (Result);
}

COVERAGE(HMM_MulM4CPP, 1)
HMM_INLINE HMM_Mat4 HMM_Mul(HMM_Mat4 Left, HMM_Mat4 Right)
{
    ASSERT_COVERED(HMM_MulM4CPP);

    HMM_Mat4 Result = HMM_MulM4(Left, Right);

    return (Result);
}

COVERAGE(HMM_MulM4FCPP, 1)
HMM_INLINE HMM_Mat4 HMM_Mul(HMM_Mat4 Left, float Right)
{
    ASSERT_COVERED(HMM_MulM4FCPP);

    HMM_Mat4 Result = HMM_MulM4F(Left, Right);

    return (Result);
}

HMM_INLINE HMM_Vec2 HMM_Mul(HMM_Mat2 Matrix, HMM_Vec2 Vector)
{
    HMM_Vec2 Result = HMM_MulM2V2(Matrix, Vector);
    return (Result);
}

HMM_INLINE HMM_Vec3 HMM_Mul(HMM_Mat3 Matrix, HMM_Vec3 Vector)
{
    HMM_Vec3 Result = HMM_MulM3V3(Matrix, Vector);
    return (Result);
}

COVERAGE(HMM_MulM4V4CPP, 1)
HMM_INLINE HMM_Vec4 HMM_Mul(HMM_Mat4 Matrix, HMM_Vec4 Vector)
{
    ASSERT_COVERED(HMM_MulM4V4CPP);

    HMM_Vec4 Result = HMM_MulM4V4(Matrix, Vector);

    return (Result);
}

COVERAGE(HMM_MulQCPP, 1)
HMM_INLINE HMM_Quat HMM_Mul(HMM_Quat Left, HMM_Quat Right)
{
    ASSERT_COVERED(HMM_MulQCPP);

    HMM_Quat Result = HMM_MulQ(Left, Right);

    return (Result);
}

COVERAGE(HMM_MulQFCPP, 1)
HMM_INLINE HMM_Quat HMM_Mul(HMM_Quat Left, float Right)
{
    ASSERT_COVERED(HMM_MulQFCPP);

    HMM_Quat Result = HMM_MulQF(Left, Right);

    return (Result);
}

COVERAGE(HMM_DivV2CPP, 1)
HMM_INLINE HMM_Vec2 HMM_Div(HMM_Vec2 Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_DivV2CPP);

    HMM_Vec2 Result = HMM_DivV2(Left, Right);

    return (Result);
}

COVERAGE(HMM_DivV2FCPP, 1)
HMM_INLINE HMM_Vec2 HMM_Div(HMM_Vec2 Left, float Right)
{
    ASSERT_COVERED(HMM_DivV2FCPP);

    HMM_Vec2 Result = HMM_DivV2F(Left, Right);

    return (Result);
}

COVERAGE(HMM_DivV3CPP, 1)
HMM_INLINE HMM_Vec3 HMM_Div(HMM_Vec3 Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_DivV3CPP);

    HMM_Vec3 Result = HMM_DivV3(Left, Right);

    return (Result);
}

COVERAGE(HMM_DivV3FCPP, 1)
HMM_INLINE HMM_Vec3 HMM_Div(HMM_Vec3 Left, float Right)
{
    ASSERT_COVERED(HMM_DivV3FCPP);

    HMM_Vec3 Result = HMM_DivV3F(Left, Right);

    return (Result);
}

COVERAGE(HMM_DivV4CPP, 1)
HMM_INLINE HMM_Vec4 HMM_Div(HMM_Vec4 Left, HMM_Vec4 Right)
{
    ASSERT_COVERED(HMM_DivV4CPP);

    HMM_Vec4 Result = HMM_DivV4(Left, Right);

    return (Result);
}

COVERAGE(HMM_DivV4FCPP, 1)
HMM_INLINE HMM_Vec4 HMM_Div(HMM_Vec4 Left, float Right)
{
    ASSERT_COVERED(HMM_DivV4FCPP);

    HMM_Vec4 Result = HMM_DivV4F(Left, Right);

    return (Result);
}

HMM_INLINE HMM_Mat2 HMM_Div(HMM_Mat2 Left, float Right)
{
    HMM_Mat2 Result = HMM_DivM2F(Left, Right);
    return (Result);
}

HMM_INLINE HMM_Mat3 HMM_Div(HMM_Mat3 Left, float Right)
{
    HMM_Mat3 Result = HMM_DivM3F(Left, Right);
    return (Result);
}

COVERAGE(HMM_DivM4FCPP, 1)
HMM_INLINE HMM_Mat4 HMM_Div(HMM_Mat4 Left, float Right)
{
    ASSERT_COVERED(HMM_DivM4FCPP);

    HMM_Mat4 Result = HMM_DivM4F(Left, Right);

    return (Result);
}

COVERAGE(HMM_DivQFCPP, 1)
HMM_INLINE HMM_Quat HMM_Div(HMM_Quat Left, float Right)
{
    ASSERT_COVERED(HMM_DivQFCPP);

    HMM_Quat Result = HMM_DivQF(Left, Right);

    return (Result);
}

COVERAGE(HMM_EqV2CPP, 1)
HMM_INLINE HMM_Bool HMM_Eq(HMM_Vec2 Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_EqV2CPP);

    HMM_Bool Result = HMM_EqV2(Left, Right);

    return (Result);
}

COVERAGE(HMM_EqV3CPP, 1)
HMM_INLINE HMM_Bool HMM_Eq(HMM_Vec3 Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_EqV3CPP);

    HMM_Bool Result = HMM_EqV3(Left, Right);

    return (Result);
}

COVERAGE(HMM_EqV4CPP, 1)
HMM_INLINE HMM_Bool HMM_Eq(HMM_Vec4 Left, HMM_Vec4 Right)
{
    ASSERT_COVERED(HMM_EqV4CPP);

    HMM_Bool Result = HMM_EqV4(Left, Right);

    return (Result);
}

COVERAGE(HMM_AddV2Op, 1)
HMM_INLINE HMM_Vec2 operator+(HMM_Vec2 Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_AddV2Op);

    HMM_Vec2 Result = HMM_AddV2(Left, Right);

    return (Result);
}

COVERAGE(HMM_AddV3Op, 1)
HMM_INLINE HMM_Vec3 operator+(HMM_Vec3 Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_AddV3Op);

    HMM_Vec3 Result = HMM_AddV3(Left, Right);

    return (Result);
}

COVERAGE(HMM_AddV4Op, 1)
HMM_INLINE HMM_Vec4 operator+(HMM_Vec4 Left, HMM_Vec4 Right)
{
    ASSERT_COVERED(HMM_AddV4Op);

    HMM_Vec4 Result = HMM_AddV4(Left, Right);

    return (Result);
}

HMM_INLINE HMM_Mat2 operator+(HMM_Mat2 Left, HMM_Mat2 Right)
{
    HMM_Mat2 Result = HMM_AddM2(Left, Right);
    return (Result);
}

HMM_INLINE HMM_Mat3 operator+(HMM_Mat3 Left, HMM_Mat3 Right)
{
    HMM_Mat3 Result = HMM_AddM3(Left, Right);
    return (Result);
}

COVERAGE(HMM_AddM4Op, 1)
HMM_INLINE HMM_Mat4 operator+(HMM_Mat4 Left, HMM_Mat4 Right)
{
    ASSERT_COVERED(HMM_AddM4Op);

    HMM_Mat4 Result = HMM_AddM4(Left, Right);

    return (Result);
}

COVERAGE(HMM_AddQOp, 1)
HMM_INLINE HMM_Quat operator+(HMM_Quat Left, HMM_Quat Right)
{
    ASSERT_COVERED(HMM_AddQOp);

    HMM_Quat Result = HMM_AddQ(Left, Right);

    return (Result);
}

COVERAGE(HMM_SubV2Op, 1)
HMM_INLINE HMM_Vec2 operator-(HMM_Vec2 Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_SubV2Op);

    HMM_Vec2 Result = HMM_SubV2(Left, Right);

    return (Result);
}

COVERAGE(HMM_SubV3Op, 1)
HMM_INLINE HMM_Vec3 operator-(HMM_Vec3 Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_SubV3Op);

    HMM_Vec3 Result = HMM_SubV3(Left, Right);

    return (Result);
}

COVERAGE(HMM_SubV4Op, 1)
HMM_INLINE HMM_Vec4 operator-(HMM_Vec4 Left, HMM_Vec4 Right)
{
    ASSERT_COVERED(HMM_SubV4Op);

    HMM_Vec4 Result = HMM_SubV4(Left, Right);

    return (Result);
}

HMM_INLINE HMM_Mat2 operator-(HMM_Mat2 Left, HMM_Mat2 Right)
{
    HMM_Mat2 Result = HMM_SubM2(Left, Right);
    return (Result);
}

HMM_INLINE HMM_Mat3 operator-(HMM_Mat3 Left, HMM_Mat3 Right)
{
    HMM_Mat3 Result = HMM_SubM3(Left, Right);
    return (Result);
}

COVERAGE(HMM_SubM4Op, 1)
HMM_INLINE HMM_Mat4 operator-(HMM_Mat4 Left, HMM_Mat4 Right)
{
    ASSERT_COVERED(HMM_SubM4Op);

    HMM_Mat4 Result = HMM_SubM4(Left, Right);

    return (Result);
}

COVERAGE(HMM_SubQOp, 1)
HMM_INLINE HMM_Quat operator-(HMM_Quat Left, HMM_Quat Right)
{
    ASSERT_COVERED(HMM_SubQOp);

    HMM_Quat Result = HMM_SubQ(Left, Right);

    return (Result);
}

COVERAGE(HMM_MulV2Op, 1)
HMM_INLINE HMM_Vec2 operator*(HMM_Vec2 Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_MulV2Op);

    HMM_Vec2 Result = HMM_MulV2(Left, Right);

    return (Result);
}

COVERAGE(HMM_MulV3Op, 1)
HMM_INLINE HMM_Vec3 operator*(HMM_Vec3 Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_MulV3Op);

    HMM_Vec3 Result = HMM_MulV3(Left, Right);

    return (Result);
}

COVERAGE(HMM_MulV4Op, 1)
HMM_INLINE HMM_Vec4 operator*(HMM_Vec4 Left, HMM_Vec4 Right)
{
    ASSERT_COVERED(HMM_MulV4Op);

    HMM_Vec4 Result = HMM_MulV4(Left, Right);

    return (Result);
}

COVERAGE(HMM_MulM4Op, 1)
HMM_INLINE HMM_Mat4 operator*(HMM_Mat4 Left, HMM_Mat4 Right)
{
    ASSERT_COVERED(HMM_MulM4Op);

    HMM_Mat4 Result = HMM_MulM4(Left, Right);

    return (Result);
}

COVERAGE(HMM_MulQOp, 1)
HMM_INLINE HMM_Quat operator*(HMM_Quat Left, HMM_Quat Right)
{
    ASSERT_COVERED(HMM_MulQOp);

    HMM_Quat Result = HMM_MulQ(Left, Right);

    return (Result);
}

COVERAGE(HMM_MulV2FOp, 1)
HMM_INLINE HMM_Vec2 operator*(HMM_Vec2 Left, float Right)
{
    ASSERT_COVERED(HMM_MulV2FOp);

    HMM_Vec2 Result = HMM_MulV2F(Left, Right);

    return (Result);
}

COVERAGE(HMM_MulV3FOp, 1)
HMM_INLINE HMM_Vec3 operator*(HMM_Vec3 Left, float Right)
{
    ASSERT_COVERED(HMM_MulV3FOp);

    HMM_Vec3 Result = HMM_MulV3F(Left, Right);

    return (Result);
}

COVERAGE(HMM_MulV4FOp, 1)
HMM_INLINE HMM_Vec4 operator*(HMM_Vec4 Left, float Right)
{
    ASSERT_COVERED(HMM_MulV4FOp);

    HMM_Vec4 Result = HMM_MulV4F(Left, Right);

    return (Result);
}

HMM_INLINE HMM_Mat2 operator*(HMM_Mat2 Left, float Right)
{
    HMM_Mat2 Result = HMM_MulM2F(Left, Right);
    return (Result);
}

HMM_INLINE HMM_Mat3 operator*(HMM_Mat3 Left, float Right)
{
    HMM_Mat3 Result = HMM_MulM3F(Left, Right);
    return (Result);
}

COVERAGE(HMM_MulM4FOp, 1)
HMM_INLINE HMM_Mat4 operator*(HMM_Mat4 Left, float Right)
{
    ASSERT_COVERED(HMM_MulM4FOp);

    HMM_Mat4 Result = HMM_MulM4F(Left, Right);

    return (Result);
}

COVERAGE(HMM_MulQFOp, 1)
HMM_INLINE HMM_Quat operator*(HMM_Quat Left, float Right)
{
    ASSERT_COVERED(HMM_MulQFOp);

    HMM_Quat Result = HMM_MulQF(Left, Right);

    return (Result);
}

COVERAGE(HMM_MulV2FOpLeft, 1)
HMM_INLINE HMM_Vec2 operator*(float Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_MulV2FOpLeft);

    HMM_Vec2 Result = HMM_MulV2F(Right, Left);

    return (Result);
}

COVERAGE(HMM_MulV3FOpLeft, 1)
HMM_INLINE HMM_Vec3 operator*(float Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_MulV3FOpLeft);

    HMM_Vec3 Result = HMM_MulV3F(Right, Left);

    return (Result);
}

COVERAGE(HMM_MulV4FOpLeft, 1)
HMM_INLINE HMM_Vec4 operator*(float Left, HMM_Vec4 Right)
{
    ASSERT_COVERED(HMM_MulV4FOpLeft);

    HMM_Vec4 Result = HMM_MulV4F(Right, Left);

    return (Result);
}


HMM_INLINE HMM_Mat2 operator*(float Left, HMM_Mat2 Right)
{
    HMM_Mat2 Result = HMM_MulM2F(Right, Left);
    return (Result);
}

HMM_INLINE HMM_Mat3 operator*(float Left, HMM_Mat3 Right)
{
    HMM_Mat3 Result = HMM_MulM3F(Right, Left);
    return (Result);
}

COVERAGE(HMM_MulM4FOpLeft, 1)
HMM_INLINE HMM_Mat4 operator*(float Left, HMM_Mat4 Right)
{
    ASSERT_COVERED(HMM_MulM4FOpLeft);

    HMM_Mat4 Result = HMM_MulM4F(Right, Left);

    return (Result);
}

COVERAGE(HMM_MulQFOpLeft, 1)
HMM_INLINE HMM_Quat operator*(float Left, HMM_Quat Right)
{
    ASSERT_COVERED(HMM_MulQFOpLeft);

    HMM_Quat Result = HMM_MulQF(Right, Left);

    return (Result);
}

COVERAGE(HMM_MulM4V4Op, 1)
HMM_INLINE HMM_Vec4 operator*(HMM_Mat4 Matrix, HMM_Vec4 Vector)
{
    ASSERT_COVERED(HMM_MulM4V4Op);

    HMM_Vec4 Result = HMM_MulM4V4(Matrix, Vector);

    return (Result);
}

COVERAGE(HMM_DivV2Op, 1)
HMM_INLINE HMM_Vec2 operator/(HMM_Vec2 Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_DivV2Op);

    HMM_Vec2 Result = HMM_DivV2(Left, Right);

    return (Result);
}

COVERAGE(HMM_DivV3Op, 1)
HMM_INLINE HMM_Vec3 operator/(HMM_Vec3 Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_DivV3Op);

    HMM_Vec3 Result = HMM_DivV3(Left, Right);

    return (Result);
}

COVERAGE(HMM_DivV4Op, 1)
HMM_INLINE HMM_Vec4 operator/(HMM_Vec4 Left, HMM_Vec4 Right)
{
    ASSERT_COVERED(HMM_DivV4Op);

    HMM_Vec4 Result = HMM_DivV4(Left, Right);

    return (Result);
}

COVERAGE(HMM_DivV2FOp, 1)
HMM_INLINE HMM_Vec2 operator/(HMM_Vec2 Left, float Right)
{
    ASSERT_COVERED(HMM_DivV2FOp);

    HMM_Vec2 Result = HMM_DivV2F(Left, Right);

    return (Result);
}

COVERAGE(HMM_DivV3FOp, 1)
HMM_INLINE HMM_Vec3 operator/(HMM_Vec3 Left, float Right)
{
    ASSERT_COVERED(HMM_DivV3FOp);

    HMM_Vec3 Result = HMM_DivV3F(Left, Right);

    return (Result);
}

COVERAGE(HMM_DivV4FOp, 1)
HMM_INLINE HMM_Vec4 operator/(HMM_Vec4 Left, float Right)
{
    ASSERT_COVERED(HMM_DivV4FOp);

    HMM_Vec4 Result = HMM_DivV4F(Left, Right);

    return (Result);
}

COVERAGE(HMM_DivM4FOp, 1)
HMM_INLINE HMM_Mat4 operator/(HMM_Mat4 Left, float Right)
{
    ASSERT_COVERED(HMM_DivM4FOp);

    HMM_Mat4 Result = HMM_DivM4F(Left, Right);

    return (Result);
}

COVERAGE(HMM_DivQFOp, 1)
HMM_INLINE HMM_Quat operator/(HMM_Quat Left, float Right)
{
    ASSERT_COVERED(HMM_DivQFOp);

    HMM_Quat Result = HMM_DivQF(Left, Right);

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


HMM_INLINE HMM_Mat2 &operator+=(HMM_Mat2 &Left, HMM_Mat2 Right)
{
    return (Left = Left + Right);
}

HMM_INLINE HMM_Mat3 &operator+=(HMM_Mat3 &Left, HMM_Mat3 Right)
{
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

HMM_INLINE HMM_Mat2 &operator*=(HMM_Mat2 &Left, float Right)
{
    return (Left = Left * Right);
}

HMM_INLINE HMM_Mat3 &operator*=(HMM_Mat3 &Left, float Right)
{
    return (Left = Left * Right);
}

COVERAGE(HMM_MulM4FAssign, 1)
HMM_INLINE HMM_Mat4 &operator*=(HMM_Mat4 &Left, float Right)
{
    ASSERT_COVERED(HMM_MulM4FAssign);

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

COVERAGE(HMM_DivM4FAssign, 1)
HMM_INLINE HMM_Mat4 &operator/=(HMM_Mat4 &Left, float Right)
{
    ASSERT_COVERED(HMM_DivM4FAssign);

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

    return HMM_EqV2(Left, Right);
}

COVERAGE(HMM_EqV3Op, 1)
HMM_INLINE HMM_Bool operator==(HMM_Vec3 Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_EqV3Op);

    return HMM_EqV3(Left, Right);
}

COVERAGE(HMM_EqV4Op, 1)
HMM_INLINE HMM_Bool operator==(HMM_Vec4 Left, HMM_Vec4 Right)
{
    ASSERT_COVERED(HMM_EqV4Op);

    return HMM_EqV4(Left, Right);
}

COVERAGE(HMM_EqV2OpNot, 1)
HMM_INLINE HMM_Bool operator!=(HMM_Vec2 Left, HMM_Vec2 Right)
{
    ASSERT_COVERED(HMM_EqV2OpNot);

    return !HMM_EqV2(Left, Right);
}

COVERAGE(HMM_EqV3OpNot, 1)
HMM_INLINE HMM_Bool operator!=(HMM_Vec3 Left, HMM_Vec3 Right)
{
    ASSERT_COVERED(HMM_EqV3OpNot);

    return !HMM_EqV3(Left, Right);
}

COVERAGE(HMM_EqV4OpNot, 1)
HMM_INLINE HMM_Bool operator!=(HMM_Vec4 Left, HMM_Vec4 Right)
{
    ASSERT_COVERED(HMM_EqV4OpNot);

    return !HMM_EqV4(Left, Right);
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

#endif /* __cplusplus*/

#ifdef HANDMADE_MATH_C11_GENERICS
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
        HMM_Quat: HMM_DivQF, \
     ), \
     HMM_Mat2: HMM_DivM2, \
     HMM_Mat3: HMM_DivM3, \
     HMM_Mat4: HMM_DivM4, \
     HMM_Quat: HMM_DivQ, \
     default: _Generic((A), \
        HMM_Vec2: HMM_DivV2, \
        HMM_Vec3: HMM_DivV3, \
        HMM_Vec4: HMM_DivV4, \
    ) \
)(A, B)

#define HMM_Len(A) _Generic((A), \
        HMM_Vec2: HMM_LenV2, \
        HMM_Vec3: HMM_LenV3, \
        HMM_Vec4: HMM_LenV4, \
)(A)

#define HMM_LenSqr(A) _Generic((A), \
        HMM_Vec2: HMM_LenSqrV2, \
        HMM_Vec3: HMM_LenSqrV3, \
        HMM_Vec4: HMM_LenSqrV4, \
)(A)

#define HMM_Norm(A) _Generic((A), \
        HMM_Vec2: HMM_NormV2, \
        HMM_Vec3: HMM_NormV3, \
        HMM_Vec4: HMM_NormV4, \
)(A)

#define HMM_Dot(A) _Generic((A), \
        HMM_Vec2: HMM_DotV2, \
        HMM_Vec3: HMM_DotV3, \
        HMM_Vec4: HMM_DotV4, \
)(A)

#define HMM_Eq(A) _Generic((A), \
        HMM_Vec2: HMM_EqV2, \
        HMM_Vec3: HMM_EqV3, \
        HMM_Vec4: HMM_EqV4, \
)(A)

#define HMM_Transpose(M) _Generic((M), \
        HMM_Mat2: HMM_TransposeM2, \
        HMM_Mat3: HMM_TransposeM3, \
        HMM_Mat4: HMM_TransposeM4, \
)(M)

#define HMM_Determinant(M) _Generic((M), \
        HMM_Mat2: HMM_DeterminantM2, \
        HMM_Mat3: HMM_DeterminantM3, \
        HMM_Mat4: HMM_DeterminantM4, \
)(M)

#define HMM_InvGeneral(M) _Generic((M), \
        HMM_Mat2: HMM_InvGeneralM2, \
        HMM_Mat3: HMM_InvGeneralM3, \
        HMM_Mat4: HMM_InvGeneralM4, \
)(M)

#endif

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif

#endif /* HANDMADE_MATH_H */



