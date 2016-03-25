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
     #include "HandmadeMath.h"

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
#define HMM_PI 3.14159265358979323846

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
HMMDEF HINLINE float Clamp(float Min, float Value, float Max);
HMMDEF HINLINE vec3 Normalize(vec3 A);
HMMDEF HINLINE vec3 Cross(vec3 VecOne, vec3 VecTwo);
HMMDEF HINLINE float Dot(vec3 VecOne, vec3 VecTwo);

HMMDEF HINLINE vec2 Vec2i(int X, int Y);
HMMDEF HINLINE vec2 Vec2(float X, float Y);
HMMDEF HINLINE vec3 Vec3(float X, float Y, float Z);
HMMDEF HINLINE vec3 Vec3i(int X, int Y, int Z);
HMMDEF HINLINE vec4 Vec4(float X, float Y, float Z, float W);
HMMDEF HINLINE vec4 Vec4i(int X, int Y, int Z, int W);

HMMDEF HINLINE vec2 AddVec2(vec2 Left, vec2 Right);
HMMDEF HINLINE vec3 AddVec3(vec3 Left, vec3 Right);
HMMDEF HINLINE vec4 AddVec4(vec4 Left, vec4 Right);

HMMDEF HINLINE vec2 SubtractVec2(vec2 Left, vec2 Right);
HMMDEF HINLINE vec3 SubtractVec3(vec3 Left, vec3 Right);
HMMDEF HINLINE vec4 SubtractVec4(vec4 Left, vec4 Right);

HMMDEF HINLINE vec2 MultiplyVec2(vec2 Left, vec2 Right);
HMMDEF HINLINE vec3 MultiplyVec3(vec3 Left, vec3 Right);
HMMDEF HINLINE vec4 MultiplyVec4(vec4 Left, vec4 Right);

HMMDEF HINLINE vec2 DivideVec2(vec2 Left, vec2 Right);
HMMDEF HINLINE vec3 DivideVec3(vec3 Left, vec3 Right);
HMMDEF HINLINE vec4 DivideVec4(vec4 Left, vec4 Right);

HMMDEF mat4 Mat4(void);
HMMDEF mat4 Mat4d(float Diagonal);
HMMDEF mat4 MultiplyMat4(mat4 Left, mat4 Right);

HMMDEF mat4 Orthographic(float Left, float Right, float Bottom, float Top, float Near, float Far);
HMMDEF mat4 Perspective(float FOV, float AspectRatio, float Near, float Far);
HMMDEF mat4 Translate(vec3 Translation);
HMMDEF mat4 Rotate(float Angle, vec3 Axis);
HMMDEF mat4 Scale(vec3 Scale);

HMMDEF mat4 LookAt(vec3 Eye, vec3 Center, vec3 Up);

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

HMMDEF HINLINE vec3
Cross(vec3 VecOne, vec3 VecTwo)
{
    vec3 Result;

    Result.X = (VecOne.Y * VecTwo.Z) - (VecOne.Z * VecTwo.Y);
    Result.Y = (VecOne.Z * VecTwo.X) - (VecOne.X * VecTwo.Z);
    Result.Z = (VecOne.X * VecTwo.Y) - (VecOne.Y * VecTwo.X);

    return(Result);
}

HMMDEF HINLINE float
Dot(vec3 VecOne, vec3 VecTwo)
{
    float Result = 0;

    Result = (VecOne.X * VecTwo.X) +
             (VecOne.Y * VecTwo.Y) +
             (VecOne.Z * VecTwo.Z);

    return(Result);
}

HMMDEF HINLINE vec2
Vec2(float X, float Y)
{
    vec2 Result;

    Result.X = X;
    Result.Y = Y;

    return(Result);
}

HMMDEF HINLINE vec2
Vec2i(int X, int Y)
{
    vec2 Result;

    Result.X = (float)X;
    Result.Y = (float)Y;

    return(Result);
}

HMMDEF HINLINE vec3
Vec3(float X, float Y, float Z)
{
    vec3 Result;

    Result.X = X;
    Result.Y = Y;
    Result.Z = Z;

    return(Result);
}

HMMDEF HINLINE vec3
Vec3i(int X, int Y, int Z)
{
    vec3 Result;

    Result.X = (float)X;
    Result.Y = (float)Y;
    Result.Z = (float)Z;

    return(Result);
}

HMMDEF HINLINE vec4
Vec4(float X, float Y, float Z, float W)
{
    vec4 Result;

    Result.X = X;
    Result.Y = Y;
    Result.Z = Z;
    Result.W = W;

    return(Result);
}

HMMDEF HINLINE vec4
Vec4i(int X, int Y, int Z, int W)
{
    vec4 Result;

    Result.X = (float)X;
    Result.Y = (float)Y;
    Result.Z = (float)Z;
    Result.W = (float)W;

    return(Result);
}    

HMMDEF HINLINE vec2
AddVec2(vec2 Left, vec2 Right)
{
    vec2 Result;

    Result.X = Left.X + Right.X;
    Result.Y = Left.Y + Right.Y;

    return(Result);
}

HMMDEF HINLINE vec3
AddVec3(vec3 Left, vec3 Right)
{
    vec3 Result;

    Result.X = Left.X + Right.X;
    Result.Y = Left.Y + Right.Y;
    Result.Z = Left.Z + Right.Z;

    return(Result);    
}

HMMDEF HINLINE vec4
AddVec4(vec4 Left, vec4 Right)
{
    vec4 Result;

    Result.X = Left.X + Right.X;
    Result.Y = Left.Y + Right.Y;
    Result.Z = Left.Z + Right.Z;
    Result.W = Left.W + Right.W;

    return(Result);    
}

HMMDEF HINLINE vec2
SubtractVec2(vec2 Left, vec2 Right)
{
    vec2 Result;

    Result.X = Left.X - Right.X;
    Result.Y = Left.Y - Right.Y;

    return(Result);
}

HMMDEF HINLINE vec3
SubtractVec3(vec3 Left, vec3 Right)
{
    vec3 Result;

    Result.X = Left.X - Right.X;
    Result.Y = Left.Y - Right.Y;
    Result.Z = Left.Z - Right.Z;

    return(Result);    
}

HMMDEF HINLINE vec4
SubtractVec4(vec4 Left, vec4 Right)
{
    vec4 Result;

    Result.X = Left.X - Right.X;
    Result.Y = Left.Y - Right.Y;
    Result.Z = Left.Z - Right.Z;
    Result.W = Left.W - Right.W;

    return(Result);    
}

HMMDEF HINLINE vec2
MultiplyVec2(vec2 Left, vec2 Right)
{
    vec2 Result;

    Result.X = Left.X * Right.X;
    Result.Y = Left.Y * Right.Y;

    return(Result);
}

HMMDEF HINLINE vec3
MultiplyVec3(vec3 Left, vec3 Right)
{
    vec3 Result;

    Result.X = Left.Z * Right.X;
    Result.Y = Left.Y * Right.Y;
    Result.Z = Left.Z * Right.Z;

    return(Result);    
}

HMMDEF HINLINE vec4
MultiplyVec4(vec4 Left, vec4 Right)
{
    vec4 Result;

    Result.X = Left.X * Right.X;
    Result.Y = Left.Y * Right.Y;
    Result.Z = Left.Z * Right.Z;
    Result.W = Left.W * Right.W;

    return(Result);    
}

HMMDEF HINLINE vec2
DivideVec2(vec2 Left, vec2 Right)
{
    vec2 Result;

    Result.X = Left.X / Right.X;
    Result.Y = Left.Y / Right.Y;

    return(Result);
}

HMMDEF HINLINE vec3
DivideVec3(vec3 Left, vec3 Right)
{
    vec3 Result;

    Result.X = Left.X / Right.X;
    Result.Y = Left.Y / Right.Y;
    Result.Z = Left.Z / Right.Z;

    return(Result);    
}

HMMDEF HINLINE vec4
DivideVec4(vec4 Left, vec4 Right)
{
    vec4 Result;

    Result.X = Left.X / Right.X;
    Result.Y = Left.Y / Right.Y;
    Result.Z = Left.Z / Right.Z;
    Result.W = Left.W / Right.W;

    return(Result);    
}

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
            float Sum = 0;
            for(int CurrentMatrice = 0;
                CurrentMatrice < 4;
                ++CurrentMatrice)
            {
                Sum += Right.Elements[Rows][CurrentMatrice] * Left.Elements[CurrentMatrice][Columns];
            }

            Result.Elements[Columns][Rows] = Sum;
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
Perspective(float FOV, float AspectRatio, float Near, float Far)
{
    mat4 Result = Mat4d(1.0f);

    Result.Elements[0][0] = 1.0f / (AspectRatio  * tan(FOV / 2.0f));
    Result.Elements[1][1] = 1.0f / tan(FOV / 2.0f);
    Result.Elements[2][3] = -1.0f;
    Result.Elements[2][2] = -(Far + Near) / (Far - Near);
    Result.Elements[3][2] = -(2.0f * Far * Near) / (Far - Near);
    Result.Elements[3][3] = 0.0f;

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
LookAt(vec3 Eye, vec3 Center, vec3 Up)
{
    mat4 Result = {};

    vec3 F = Normalize(Center - Eye);
    vec3 S = Normalize(Cross(F, Up));
    vec3 U = Cross(S, F);

    Result.Elements[0][0] = S.X;
    Result.Elements[0][1] = U.X;
    Result.Elements[0][2] = -F.X;

    Result.Elements[1][0] = S.Y;
    Result.Elements[1][1] = U.Y;
    Result.Elements[1][2] = -F.Y;

    Result.Elements[2][0] = S.Z;
    Result.Elements[2][1] = U.Z;
    Result.Elements[2][2] = -F.Z;

    Result.Elements[3][0] = -Dot(S, Eye);
    Result.Elements[3][1] = -Dot(U, Eye);
    Result.Elements[3][2] = Dot(F, Eye);
    Result.Elements[3][3] = 1.0f;

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
    vec2 Result = AddVec2(Left, Right);

    return(Result);
}

HMMDEF HINLINE vec3
Add(vec3 Left, vec3 Right)
{
    vec3 Result = AddVec3(Left, Right);

    return(Result);
}

HMMDEF HINLINE vec4
Add(vec4 Left, vec4 Right)
{
    vec4 Result = AddVec4(Left, Right);

    return(Result);
}

HMMDEF HINLINE vec2
Subtract(vec2 Left, vec2 Right)
{
    vec2 Result = SubtractVec2(Left, Right);

    return(Result);
}

HMMDEF HINLINE vec3
Subtract(vec3 Left, vec3 Right)
{
    vec3 Result = SubtractVec3(Left, Right);

    return(Result);
}

HMMDEF HINLINE vec4
Subtract(vec4 Left, vec4 Right)
{
    vec4 Result = SubtractVec4(Left, Right);

    return(Result);
}

HMMDEF HINLINE vec2
Multiply(vec2 Left, vec2 Right)
{
    vec2 Result = MultiplyVec2(Left, Right);

    return(Result);
}

HMMDEF HINLINE vec3
Multiply(vec3 Left, vec3 Right)
{
    vec3 Result = MultiplyVec3(Left, Right);

    return(Result);
}

HMMDEF HINLINE vec4
Multiply(vec4 Left, vec4 Right)
{
    vec4 Result = MultiplyVec4(Left, Right);

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
    vec2 Result = DivideVec2(Left, Right);

    return(Result);
}

HMMDEF HINLINE vec3
Divide(vec3 Left, vec3 Right)
{
    vec3 Result = DivideVec3(Left, Right);

    return(Result);
}

HMMDEF HINLINE vec4
Divide(vec4 Left, vec4 Right)
{
    vec4 Result = DivideVec4(Left, Right);

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


