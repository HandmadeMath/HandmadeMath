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

// TODO(zak): Make some sort of documentation for this and a way to remove it
#include <math.h>

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

#define Pi32 3.14159265359f
    
typedef union vec2
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
} vec2;

typedef union vec3
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
        vec2 XY;
        float Ignored0_;
    };
    
    struct
    {
        float Ignored1_;
        vec2 YZ;
    };
    
    struct
    {
        vec2 UV;
        float Ignored2_;
    };
    
    struct
    {
        float Ignored3_;
        vec2 VW;
    };

    float Elements[3];
} vec3;

typedef union vec4
{
    struct
    {
        union
        {
            vec3 XYZ;
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
            vec3 RGB;
            struct
            {
                float R, G, B;
            };
        };
        
        float A;        
    };
    
    struct
    {
        vec2 XY;
        float Ignored0_;
        float Ignored1_;
    };
    
    struct
    {
        float Ignored2_;
        vec2 YZ;
        float Ignored3_;
    };
    
    struct
    {
        float Ignored4_;
        float Ignored5_;
        vec2 ZW;
    };
    
    float Elements[4];
} vec4;

typedef union mat4
{
    float Elements[4][4];
} mat4;

HMMDEF HINLINE float Power(float Base, int Exponent);
    
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

HMMDEF mat4 Mat4(void);
HMMDEF mat4 Mat4d(float Diagonal);
HMMDEF mat4 MultiplyMat4(mat4 Left, mat4 Right);

HMMDEF mat4 Orthographic(float Left, float Right, float Bottom, float Top, float Near, float Far);
HMMDEF mat4 Pespective(float FOV, float AspectRatio, float Near, float Far);
HMMDEF mat4 Translate(vec3 Translation);
HMMDEF mat4 Rotate(float Angle, vec3 Axis);
HMMDEF mat4 Scale(vec3 Scale);

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
HMMDEF HINLINE mat4 Multiply(mat4 Left, mat4 Right);
    
HMMDEF HINLINE vec2 Divide(int X, int Y);
HMMDEF HINLINE vec3 Divide(int X, int Y, int Z);
HMMDEF HINLINE vec4 Divide(int X, int Y, int Z, int W);    

HMMDEF vec2 operator+(vec2 Left, vec2 Right);
HMMDEF vec3 operator+(vec3 Left, vec3 Right);
HMMDEF vec4 operator+(vec4 Left, vec4 Right);

HMMDEF vec2 operator-(vec2 Left, vec2 Right);
HMMDEF vec3 operator-(vec3 Left, vec3 Right);
HMMDEF vec4 operator-(vec4 Left, vec4 Right);

HMMDEF vec2 operator*(vec2 Left, vec2 Right);
HMMDEF vec3 operator*(vec3 Left, vec3 Right);
HMMDEF vec4 operator*(vec4 Left, vec4 Right);
HMMDEF mat4 operator*(mat4 Left, mat4 Right);
HMMDEF vec3 operator*(vec3 Left, float Right);

HMMDEF vec2 operator/(vec2 Left, vec2 Right);
HMMDEF vec3 operator/(vec3 Left, vec3 Right);
HMMDEF vec4 operator/(vec4 Left, vec4 Right);


#endif /* HANDMADE_MATH_CPP */

#endif /* HANDMADE_MATH_H */

#ifdef HANDMADE_MATH_IMPLEMENTATION

HMMDEF HINLINE float
ToRadians(float Degrees)
{
    float Result = Degrees * (Pi32 / 180.0f);

    return(Result);
}

HMMDEF HINLINE float
Inner(vec3 A, vec3 B)
{
    float Result = A.X*B.X + A.Y*B.Y + A.Z*B.Z;

    return(Result);
}

HMMDEF HINLINE float
SquareRoot(float Float)
{
    float Result = sqrtf(Float);

    return(Result);
}

HMMDEF HINLINE float
LengthSq(vec3 A)
{
    float Result = Inner(A, A);

    return(Result);
}

HMMDEF HINLINE float
Length(vec3 A)
{
    float Result = SquareRoot(LengthSq(A));
    return(Result);
}

HMMDEF HINLINE float
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

HMMDEF HINLINE float
Lerp(float A, float Time, float B)
{
    float Result = (1.0f - Time) * A + Time * B;

    return(Result);
}

HMMDEF HINLINE float
Clamp(float Min, float Value, float Max)
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

    return(Result);
}

HMMDEF HINLINE vec3
Normalize(vec3 A)
{
    vec3 Result = A * (1.0f / Length(A));

    return(Result);
}

HMMDEF HINLINE vec2
V2(float X, float Y)
{
    vec2 Result;

    Result.X = X;
    Result.Y = Y;

    return(Result);
}

HMMDEF HINLINE vec2
V2i(int X, int Y)
{
    vec2 Result;

    Result.X = (float)X;
    Result.Y = (float)Y;

    return(Result);
}
    
HMMDEF HINLINE vec3
V3(float X, float Y, float Z)
{
    vec3 Result;

    Result.X = X;
    Result.Y = Y;
    Result.Z = Z;

    return(Result);
}

HMMDEF HINLINE vec3
V3i(int X, int Y, int Z)
{
    vec3 Result;

    Result.X = (float)X;
    Result.Y = (float)Y;
    Result.Z = (float)Z;
    
    return(Result);
}
    
HMMDEF HINLINE vec4
V4(float X, float Y, float Z, float W)
{
    vec4 Result;

    Result.X = X;
    Result.Y = Y;
    Result.Z = Z;
    Result.W = W;

    return(Result);
}

HMMDEF HINLINE vec4
V4i(int X, int Y, int Z, int W)
{
    vec4 Result;

    Result.X = (float)X;
    Result.Y = (float)Y;
    Result.Z = (float)Z;
    Result.W = (float)W;
    
    return(Result);
}    

HMMDEF HINLINE vec2
AddV2(vec2 Left, vec2 Right)
{
    vec2 Result;

    Result.X = Left.X + Right.X;
    Result.Y = Left.Y + Right.Y;

    return(Result);
}

HMMDEF HINLINE vec3
AddV3(vec3 Left, vec3 Right)
{
    vec3 Result;

    Result.X = Left.X + Right.X;
    Result.Y = Left.Y + Right.Y;
    Result.Z = Left.Z + Right.Z;

    return(Result);    
}

HMMDEF HINLINE vec4
AddV4(vec4 Left, vec4 Right)
{
    vec4 Result;

    Result.X = Left.X + Right.X;
    Result.Y = Left.Y + Right.Y;
    Result.Z = Left.Z + Right.Z;
    Result.W = Left.W + Right.W;

    return(Result);    
}

HMMDEF HINLINE vec2
SubtractV2(vec2 Left, vec2 Right)
{
    vec2 Result;

    Result.X = Left.X - Right.X;
    Result.Y = Left.Y - Right.Y;

    return(Result);
}

HMMDEF HINLINE vec3
SubtractV3(vec3 Left, vec3 Right)
{
    vec3 Result;

    Result.X = Left.X - Right.X;
    Result.Y = Left.Y - Right.Y;
    Result.Z = Left.Z - Right.Z;

    return(Result);    
}

HMMDEF HINLINE vec4
SubtractV4(vec4 Left, vec4 Right)
{
    vec4 Result;

    Result.X = Left.X - Right.X;
    Result.Y = Left.Y - Right.Y;
    Result.Z = Left.Z - Right.Z;
    Result.W = Left.W - Right.W;

    return(Result);    
}

HMMDEF HINLINE vec2
MultiplyV2(vec2 Left, vec2 Right)
{
    vec2 Result;

    Result.X = Left.X * Right.X;
    Result.Y = Left.Y * Right.Y;

    return(Result);
}

HMMDEF HINLINE vec3
MultiplyV3(vec3 Left, vec3 Right)
{
    vec3 Result;

    Result.X = Left.Z * Right.X;
    Result.Y = Left.Y * Right.Y;
    Result.Z = Left.Z * Right.Z;

    return(Result);    
}

HMMDEF HINLINE vec4
MultiplyV4(vec4 Left, vec4 Right)
{
    vec4 Result;

    Result.X = Left.X * Right.X;
    Result.Y = Left.Y * Right.Y;
    Result.Z = Left.Z * Right.Z;
    Result.W = Left.W * Right.W;

    return(Result);    
}

HMMDEF HINLINE vec2
DivideV2(vec2 Left, vec2 Right)
{
    vec2 Result;

    Result.X = Left.X / Right.X;
    Result.Y = Left.Y / Right.Y;

    return(Result);
}

HMMDEF HINLINE vec3
DivideV3(vec3 Left, vec3 Right)
{
    vec3 Result;

    Result.X = Left.X / Right.X;
    Result.Y = Left.Y / Right.Y;
    Result.Z = Left.Z / Right.Z;

    return(Result);    
}

HMMDEF HINLINE vec4
DivideV4(vec4 Left, vec4 Right)
{
    vec4 Result;

    Result.X = Left.X / Right.X;
    Result.Y = Left.Y / Right.Y;
    Result.Z = Left.Z / Right.Z;
    Result.W = Left.W / Right.W;

    return(Result);    
}
\
HMMDEF mat4 Mat4()
{
    mat4 Result;
    
    for(int Rows = 0;
        Rows < 4;
        ++Rows)
    {
        for(int Columns = 0;
            Columns < 4;
            ++Columns)
        {
            Result.Elements[Rows][Columns] = 0.0f;
        }
    }

    return(Result);
}

HMMDEF mat4
Mat4d(float Diagonal)
{
    mat4 Result;
    
    for(int Rows = 0;
        Rows < 4;
        ++Rows)
    {
        for(int Columns = 0;
            Columns < 4;
            ++Columns)
        {
            Result.Elements[Rows][Columns] = 0.0f;
        }
    }

    Result.Elements[0][0] = Diagonal;
    Result.Elements[1][1] = Diagonal;
    Result.Elements[2][2] = Diagonal;
    Result.Elements[3][3] = Diagonal;

    return(Result);
}

HMMDEF mat4
MultiplyMat4(mat4 Left, mat4 Right)
{
    mat4 Result = Mat4();
    
    for(int Rows = 0;
        Rows < 4;
        ++Rows)
    {
        for(int Columns = 0;
            Columns < 4;
            ++Columns)
        {
            Result.Elements[Rows][Columns] = Left.Elements[Rows][Columns] * Right.Elements[Rows][Columns];
        }
    }

    return(Result);
}

HMMDEF mat4
Orthographic(float Left, float Right, float Bottom, float Top, float Near, float Far)
{
    mat4 Result = Mat4d(1.0f);

    Result.Elements[0][0] = 2.0f / (Right - Left);
    Result.Elements[1][1] = 2.0f / (Top - Bottom);
    Result.Elements[2][2] = 2.0f / (Near - Far);

    Result.Elements[0][3] = (Left + Right) / (Left - Right);
    Result.Elements[1][3] = (Bottom + Top) / (Bottom - Top);
    Result.Elements[2][3] = (Far + Near) / (Far - Near);

    return(Result);
}

HMMDEF mat4
Pespective(float FOV, float AspectRatio, float Near, float Far)
{
    mat4 Result = Mat4d(1.0f);

    Result.Elements[0][0] = 1.0f / tan(ToRadians(0.5f * FOV));
    Result.Elements[1][1] = (1.0f / tan(ToRadians(0.5f * FOV))) / AspectRatio;
    Result.Elements[2][2] = (Near + Far) / (Near - Far);
    Result.Elements[3][2] = -1.0f;
    Result.Elements[2][3] = (2.0f * Near * Far) / (Near - Far);

    return(Result);
}

HMMDEF mat4
Translate(vec3 Translation)
{
    mat4 Result = Mat4d(1.0f);

    Result.Elements[0][3] = Translation.X;
    Result.Elements[1][3] = Translation.Y;
    Result.Elements[2][3] = Translation.Z;
    
    return(Result);
}

HMMDEF mat4
Rotate(float Angle, vec3 Axis)
{
    mat4 Result = Mat4d(1.0f);

    Result.Elements[0][0] = Axis.Z * (1.0f - cos(ToRadians(Angle))) + cos(ToRadians(Angle));
    Result.Elements[1][0] = Axis.Y * Axis.X * (1.0f - cos(ToRadians(Angle))) + Axis.Z * (sin(ToRadians(Angle)));
    Result.Elements[2][0] = Axis.X * Axis.Z * (1.0f - cos(ToRadians(Angle))) - Axis.Y * (sin(ToRadians(Angle)));

    Result.Elements[0][1] = Axis.X * Axis.Y * (1.0f - cos(ToRadians(Angle))) - Axis.Z * (sin(ToRadians(Angle)));
    Result.Elements[1][1] = Axis.Y * (1.0f - cos(ToRadians(Angle))) + (cos(ToRadians(Angle)));
    Result.Elements[2][1] = Axis.Y * Axis.Z * (1.0f - cos(ToRadians(Angle))) + Axis.X * (sin(ToRadians(Angle)));

    Result.Elements[0][2] = Axis.X * Axis.Z * (1.0f - cos(ToRadians(Angle))) + Axis.Y * (sin(ToRadians(Angle)));
    Result.Elements[1][2] = Axis.Y * Axis.Z * (1.0f - cos(ToRadians(Angle))) - Axis.X * (sin(ToRadians(Angle)));
    Result.Elements[2][2] = Axis.Z * (1.0f - cos(ToRadians(Angle))) * (cos(ToRadians(Angle)));

    return(Result);
}

HMMDEF mat4
Scale(vec3 Scale)
{
    mat4 Result = Mat4d(1.0f);

    Result.Elements[0][0] = Scale.X;
    Result.Elements[1][1] = Scale.Y;
    Result.Elements[2][2] = Scale.Z;
    
    return(Result);
}

#ifdef HANDMADE_MATH_CPP_MODE

HMMDEF HINLINE vec2
Add(vec2 Left, vec2 Right)
{
    vec2 Result = AddV2(Left, Right);

    return(Result);
}

HMMDEF HINLINE vec3
Add(vec3 Left, vec3 Right)
{
    vec3 Result = AddV3(Left, Right);

    return(Result);
}

HMMDEF HINLINE vec4
Add(vec4 Left, vec4 Right)
{
    vec4 Result = AddV4(Left, Right);

    return(Result);
}

HMMDEF HINLINE vec2
Subtract(vec2 Left, vec2 Right)
{
    vec2 Result = SubtractV2(Left, Right);

    return(Result);
}

HMMDEF HINLINE vec3
Subtract(vec3 Left, vec3 Right)
{
    vec3 Result = SubtractV3(Left, Right);

    return(Result);
}

HMMDEF HINLINE vec4
Subtract(vec4 Left, vec4 Right)
{
    vec4 Result = SubtractV4(Left, Right);

    return(Result);
}

HMMDEF HINLINE vec2
Multiply(vec2 Left, vec2 Right)
{
    vec2 Result = MultiplyV2(Left, Right);

    return(Result);
}

HMMDEF HINLINE vec3
Multiply(vec3 Left, vec3 Right)
{
    vec3 Result = MultiplyV3(Left, Right);

    return(Result);
}
    
HMMDEF HINLINE vec4
Multiply(vec4 Left, vec4 Right)
{
    vec4 Result = MultiplyV4(Left, Right);

    return(Result);
}

HMMDEF HINLINE mat4
Multiply(mat4 Left, mat4 Right)
{
    mat4 Result = MultiplyMat4(Left, Right);

    return(Result);
}

HMMDEF HINLINE vec2
Divide(vec2 Left, vec2 Right)
{
    vec2 Result = DivideV2(Left, Right);
    
    return(Result);
}

HMMDEF HINLINE vec3
Divide(vec3 Left, vec3 Right)
{
    vec3 Result = DivideV3(Left, Right);

    return(Result);
}

HMMDEF HINLINE vec4
Divide(vec4 Left, vec4 Right)
{
    vec4 Result = DivideV4(Left, Right);

    return(Result);
}

HMMDEF HINLINE vec2
operator+(vec2 Left, vec2 Right)
{
    vec2 Result = Add(Left, Right);

    return(Result);
}

HMMDEF HINLINE vec3
operator+(vec3 Left, vec3 Right)
{
    vec3 Result = Add(Left, Right);

    return(Result);
}

HMMDEF HINLINE vec4
operator+(vec4 Left, vec4 Right)
{
    vec4 Result = Add(Left, Right);

    return(Result);
}

HMMDEF HINLINE vec2
operator-(vec2 Left, vec2 Right)
{
    vec2 Result = Subtract(Left, Right);

    return(Result);
}

HMMDEF HINLINE vec3
operator-(vec3 Left, vec3 Right)
{
    vec3 Result = Subtract(Left, Right);

    return(Result);
}

HMMDEF HINLINE vec4
operator-(vec4 Left, vec4 Right)
{
    vec4 Result = Subtract(Left, Right);

    return(Result);
}

HMMDEF HINLINE vec2
operator*(vec2 Left, vec2 Right)
{
    vec2 Result = Multiply(Left, Right);

    return(Result);
}

HMMDEF HINLINE vec3
operator*(vec3 Left, vec3 Right)
{
    vec3 Result = Multiply(Left, Right);

    return(Result);
}

HMMDEF HINLINE vec3
operator*(vec3 Left, float Right)
{
    vec3 Result;

    Result.X = Right * Left.X;
    Result.Y = Right * Left.Y;
    Result.Z = Right * Left.Z;

    return(Result);
}

HMMDEF HINLINE vec4
operator*(vec4 Left, vec4 Right)
{
    vec4 Result = Multiply(Left, Right);

    return(Result);
}

HMMDEF HINLINE mat4
operator*(mat4 Left, mat4 Right)
{
    mat4 Result = Multiply(Left, Right);

    return(Result);
}

HMMDEF HINLINE vec2
operator/(vec2 Left, vec2 Right)
{
    vec2 Result = Divide(Left, Right);

    return(Result);
}

HMMDEF HINLINE vec3
operator/(vec3 Left, vec3 Right)
{
    vec3 Result = Divide(Left, Right);

    return(Result);
}

HMMDEF HINLINE vec4
operator/(vec4 Left, vec4 Right)
{
    vec4 Result = Divide(Left, Right);

    return(Result);
}

#endif /* HANDMADE_MATH_CPP_MODE */

#endif /* HANDMADE_MATH_IMPLEMENTATION */


