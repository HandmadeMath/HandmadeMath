/*
  HandmadeMath.h v0.1

  This is a single header file with a bunch of useful functions for 
  basic game math operations.
  ==========================================================================
  You MUST

     #define HANDMADE_MATH_IMPLEMENTATION
  
  in EXACTLY one C or C++ file that includes this header, BEFORE the
  include, like this:
     
     #define HANDMADE_MATH_IMPLEMENTATION
     #include "HandmadeMade.h"

  All other files should just #include "HandmadeMath.h" without the #define.
  ==========================================================================
  
  For overloaded, and operator overloaded versions of the base C functions.
  You MUST

  #define HANDMADE_MATH_CPP_MODE

  in EXACTLY one C or C++ file that includes this header, BEFORE the
  include, like this:
    
     #define HANDMADE_MATH_IMPLEMENTATION
     #define HANDMADE_MATH_CPP_MODE
     #include "HandmadeMade.h"

  All other files should just #include "HandmadeMath.h" without the #define.
  ==========================================================================
  
  LICENSE

  This software is in the public domain. Where that dedication is not
  recognized, you are granted a perpetual, irrevocable license to copy,
  distribute, and modify this file as you see fit.

  CREDITS

  Written by Zakary Strange (zak@strangedev.net)

  Functionality:
   Matt Mascarenhas (@miblo_)


  Fixes:
   Jeroen van Rijn (@J_vanRijn)
*/

#ifndef HANDMADE_MATH_H
#define HANDMADE_MATH_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef HANDMADEMATH_STATIC
#define HMMDEF static
#else
#define HMMDEF extern
#endif

#if _MSC_VER && !__INTEL_COMPILER
#define HINLINE __inline 
#else
#define HINLINE inline
#endif
    
typedef union vec2
{
    struct
    {
        float x, y;
    };
    
    struct
    {
        float u, v;
    };
    
    struct
    {
        float left, right;
    };

    float Elements[2];
} vec2;

typedef union vec3
{
    struct
    {
        float x, y, z;
    };
    
    struct
    {
        float u, v, w;
    };
    
    struct
    {
        float r, g, b;
    };
    
    struct
    {
        vec2 xy;
        float Ignored0_;
    };
    
    struct
    {
        float Ignored1_;
        vec2 yz;
    };
    
    struct
    {
        vec2 uv;
        float Ignored2_;
    };
    
    struct
    {
        float Ignored3_;
        vec2 vw;
    };

    float Elements[3];
} vec3;

typedef union vec4
{
    struct
    {
        union
        {
            vec3 xyz;
            struct
            {
                float x, y, z;
            };
        };
        
        float w;        
    };
    struct
    {
        union
        {
            vec3 rgb;
            struct
            {
                float r, g, b;
            };
        };
        
        float a;        
    };
    
    struct
    {
        vec2 xy;
        float Ignored0_;
        float Ignored1_;
    };
    
    struct
    {
        float Ignored2_;
        vec2 yz;
        float Ignored3_;
    };
    
    struct
    {
        float Ignored4_;
        float Ignored5_;
        vec2 zw;
    };
    
    float E[4];
} vec4;

HMMDEF HINLINE vec2 V2i(int X, int Y);
HMMDEF HINLINE vec2 V2(float X, float Y);
HMMDEF HINLINE vec3 V3(float X, float Y, float Z);
HMMDEF HINLINE vec3 V3i(int X, int Y, int Z);
HMMDEF HINLINE vec4 V4(float X, float Y, float Z, float W);
HMMDEF HINLINE vec4 V4i(int X, int Y, int Z, int W);

HMMDEF HINLINE vec2 AddV2(vec2 Left, vec2 Right);
HMMDEF HINLINE vec3 AddV3(vec3 Left, vec3 Right);
HMMDEF HINLINE vec4 AddV4(vec4 Left, vec4 Right);

HMMDEF HINLINE vec2 SubtractV2(vec2 Left, vec2 Right);
HMMDEF HINLINE vec3 SubtractV3(vec3 Left, vec3 Right);
HMMDEF HINLINE vec4 SubtractV4(vec4 Left, vec4 Right);

HMMDEF HINLINE vec2 MultiplyV2(vec2 Left, vec2 Right);
HMMDEF HINLINE vec3 MultiplyV3(vec3 Left, vec3 Right);
HMMDEF HINLINE vec4 MultiplyV4(vec4 Left, vec4 Right);

HMMDEF HINLINE vec2 DivideV2(vec2 Left, vec2 Right);
HMMDEF HINLINE vec3 DivideV3(vec3 Left, vec3 Right);
HMMDEF HINLINE vec4 DivideV4(vec4 Left, vec4 Right);

HMMDEF HINLINE float Power(float Base, int Exponent);
    
#ifdef __cplusplus
}
#endif

#ifdef HANDMADE_MATH_CPP_MODE

HMMDEF HINLINE vec2 Add(int X, int Y);
HMMDEF HINLINE vec3 Add(int X, int Y, int Z);
HMMDEF HINLINE vec4 Add(int X, int Y, int Z, int W);

HMMDEF HINLINE vec2 Subtract(int X, int Y);
HMMDEF HINLINE vec3 Subtract(int X, int Y, int Z);
HMMDEF HINLINE vec4 Subtract(int X, int Y, int Z, int W);

HMMDEF HINLINE vec2 Multiply(int X, int Y);
HMMDEF HINLINE vec3 Multiply(int X, int Y, int Z);
HMMDEF HINLINE vec4 Multiply(int X, int Y, int Z, int W);
    
HMMDEF HINLINE vec2 Divide(int X, int Y);
HMMDEF HINLINE vec3 Divide(int X, int Y, int Z);
HMMDEF HINLINE vec4 Divide(int X, int Y, int Z, int W);    

vec2 operator+(vec2 Left, vec2 Right);
vec3 operator+(vec3 Left, vec3 Right);
vec4 operator+(vec4 Left, vec4 Right);

vec2 operator-(vec2 Left, vec2 Right);
vec3 operator-(vec3 Left, vec3 Right);
vec4 operator-(vec4 Left, vec4 Right);

vec2 operator*(vec2 Left, vec2 Right);
vec3 operator*(vec3 Left, vec3 Right);
vec4 operator*(vec4 Left, vec4 Right);

vec2 operator/(vec2 Left, vec2 Right);
vec3 operator/(vec3 Left, vec3 Right);
vec4 operator/(vec4 Left, vec4 Right);

#endif /* HANDMADE_MATH_CPP */

#endif /* HANDMADE_MATH_H */

#ifdef HANDMADE_MATH_IMPLEMENTATION

HINLINE vec2
V2(float X, float Y)
{
    vec2 Result = {0};

    Result.x = X;
    Result.y = Y;

    return(Result);
}


HINLINE vec2
V2i(int X, int Y)
{
    vec2 Result = {0};

    Result.x = (float)X;
    Result.y = (float)Y;

    return(Result);
}
    
HINLINE vec3
V3(float X, float Y, float Z)
{
    vec3 Result = {0};

    Result.x = X;
    Result.y = Y;
    Result.z = Z;

    return(Result);
}

HINLINE vec3
V3i(int X, int Y, int Z)
{
    vec3 Result = {0};

    Result.x = (float)X;
    Result.y = (float)Y;
    Result.z = (float)Z;
    
    return(Result);
}
    
HINLINE vec4
V4(float X, float Y, float Z, float W)
{
    vec4 Result = {0};

    Result.x = X;
    Result.y = Y;
    Result.z = Z;
    Result.w = W;

    return(Result);
}

HINLINE vec4
V4i(int X, int Y, int Z, int W)
{
    vec4 Result = {0};

    Result.x = (float)X;
    Result.y = (float)Y;
    Result.z = (float)Z;
    Result.w = (float)W;
    
    return(Result);
}    

HINLINE vec2
AddV2(vec2 Left, vec2 Right)
{
    vec2 Result;

    Result.x = Left.x + Right.x;
    Result.y = Left.y + Right.y;

    return(Result);
}

HINLINE vec3
AddV3(vec3 Left, vec3 Right)
{
    vec3 Result;

    Result.x = Left.x + Right.x;
    Result.y = Left.y + Right.y;
    Result.z = Left.z + Right.z;

    return(Result);    
}

HINLINE vec4
AddV4(vec4 Left, vec4 Right)
{
    vec4 Result;

    Result.x = Left.x + Right.x;
    Result.y = Left.y + Right.y;
    Result.z = Left.z + Right.z;
    Result.w = Left.w + Right.w;

    return(Result);    
}

HINLINE vec2
SubtractV2(vec2 Left, vec2 Right)
{
    vec2 Result;

    Result.x = Left.x - Right.x;
    Result.y = Left.y - Right.y;

    return(Result);
}

HINLINE vec3
SubtractV3(vec3 Left, vec3 Right)
{
    vec3 Result;

    Result.x = Left.x - Right.x;
    Result.y = Left.y - Right.y;
    Result.z = Left.z - Right.z;

    return(Result);    
}

HINLINE vec4
SubtractV4(vec4 Left, vec4 Right)
{
    vec4 Result;

    Result.x = Left.x - Right.x;
    Result.y = Left.y - Right.y;
    Result.z = Left.z - Right.z;
    Result.w = Left.w - Right.w;

    return(Result);    
}

HINLINE vec2
MultiplyV2(vec2 Left, vec2 Right)
{
    vec2 Result;

    Result.x = Left.x * Right.x;
    Result.y = Left.y * Right.y;

    return(Result);
}

HINLINE vec3
MultiplyV3(vec3 Left, vec3 Right)
{
    vec3 Result;

    Result.x = Left.x * Right.x;
    Result.y = Left.y * Right.y;
    Result.z = Left.z * Right.z;

    return(Result);    
}

HINLINE vec4
MultiplyV4(vec4 Left, vec4 Right)
{
    vec4 Result;

    Result.x = Left.x * Right.x;
    Result.y = Left.y * Right.y;
    Result.z = Left.z * Right.z;
    Result.w = Left.w * Right.w;

    return(Result);    
}

HINLINE vec2
DivideV2(vec2 Left, vec2 Right)
{
    vec2 Result;

    Result.x = Left.x / Right.x;
    Result.y = Left.y / Right.y;

    return(Result);
}

HINLINE vec3
DivideV3(vec3 Left, vec3 Right)
{
    vec3 Result;

    Result.x = Left.x / Right.x;
    Result.y = Left.y / Right.y;
    Result.z = Left.z / Right.z;

    return(Result);    
}

HINLINE vec4
DivideV4(vec4 Left, vec4 Right)
{
    vec4 Result;

    Result.x = Left.x / Right.x;
    Result.y = Left.y / Right.y;
    Result.z = Left.z / Right.z;
    Result.w = Left.w / Right.w;

    return(Result);    
}

HINLINE float
Power(float Base, int Exponent)
{
    float Result = 1;
    if (Exponent > 0)
    {
        for (int i = 0; i < Exponent; ++i)
        {
            Result *= Base;
        }
    }
    else
    {
        for (int i = 0; i > Exponent; --i)
        {
            Result /= Base;
        }
    }
    return (Result);
}

#ifdef HANDMADE_MATH_CPP_MODE

HINLINE vec2
Add(vec2 Left, vec2 Right)
{
    vec2 Result = AddV2(Left, Right);

    return(Result);
}

HINLINE vec3
Add(vec3 Left, vec3 Right)
{
    vec3 Result = AddV3(Left, Right);

    return(Result);
}

HINLINE vec4
Add(vec4 Left, vec4 Right)
{
    vec4 Result = AddV4(Left, Right);

    return(Result);
}

HINLINE vec2
Subtract(vec2 Left, vec2 Right)
{
    vec2 Result = SubtractV2(Left, Right);

    return(Result);
}

HINLINE vec3
Subtract(vec3 Left, vec3 Right)
{
    vec3 Result = SubtractV3(Left, Right);

    return(Result);
}

HINLINE vec4
Subtract(vec4 Left, vec4 Right)
{
    vec4 Result = SubtractV4(Left, Right);

    return(Result);
}

HINLINE vec2
Multiply(vec2 Left, vec2 Right)
{
    vec2 Result = MultiplyV2(Left, Right);

    return(Result);
}

HINLINE vec3
Multiply(vec3 Left, vec3 Right)
{
    vec3 Result = MultiplyV3(Left, Right);

    return(Result);
}
    
HINLINE vec4
Multiply(vec4 Left, vec4 Right)
{
    vec4 Result = MultiplyV4(Left, Right);

    return(Result);
}
    
HINLINE vec2
Divide(vec2 Left, vec2 Right)
{
    vec2 Result = DivideV2(Left, Right);
    
    return(Result);
}

HINLINE vec3
Divide(vec3 Left, vec3 Right)
{
    vec3 Result = DivideV3(Left, Right);

    return(Result);
}

HINLINE vec4
Divide(vec4 Left, vec4 Right)
{
    vec4 Result = DivideV4(Left, Right);

    return(Result);
}

vec2 operator+(vec2 Left, vec2 Right)
{
    vec2 Result = Add(Left, Right);

    return(Result);
}

vec3 operator+(vec3 Left, vec3 Right)
{
    vec3 Result = Add(Left, Right);

    return(Result);
}

vec4 operator+(vec4 Left, vec4 Right)
{
    vec4 Result = Add(Left, Right);

    return(Result);
}

vec2 operator-(vec2 Left, vec2 Right)
{
    vec2 Result = Subtract(Left, Right);

    return(Result);
}

vec3 operator-(vec3 Left, vec3 Right)
{
    vec3 Result = Subtract(Left, Right);

    return(Result);
}

vec4 operator-(vec4 Left, vec4 Right)
{
    vec4 Result = Subtract(Left, Right);

    return(Result);
}

vec2 operator*(vec2 Left, vec2 Right)
{
    vec2 Result = Multiply(Left, Right);

    return(Result);
}

vec3 operator*(vec3 Left, vec3 Right)
{
    vec3 Result = Multiply(Left, Right);

    return(Result);
}

vec4 operator*(vec4 Left, vec4 Right)
{
    vec4 Result = Multiply(Left, Right);

    return(Result);
}

vec2 operator/(vec2 Left, vec2 Right)
{
    vec2 Result = Divide(Left, Right);

    return(Result);
}

vec3 operator/(vec3 Left, vec3 Right)
{
    vec3 Result = Divide(Left, Right);

    return(Result);
}

vec4 operator/(vec4 Left, vec4 Right)
{
    vec4 Result = Divide(Left, Right);

    return(Result);
}

#endif /* HANDMADE_MATH_CPP_MODE */

#endif /* HANDMADE_MATH_IMPLEMENTATION */


