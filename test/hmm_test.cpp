
#define HANDMADE_MATH_CPP_MODE
#include "../HandmadeMath.h"

#include "gtest/gtest.h"


TEST(ScalarMath, Trigonometry)
{
    // We have to be a little looser with our equality constraint
    // because of floating-point precision issues.
    const float trigAbsError = 0.0001f;

    EXPECT_NEAR(HMM_SinF(0.0f), 0.0f, trigAbsError);
    EXPECT_NEAR(HMM_SinF(HMM_PI32 / 2), 1.0f, trigAbsError);
    EXPECT_NEAR(HMM_SinF(HMM_PI32), 0.0f, trigAbsError);
    EXPECT_NEAR(HMM_SinF(3 * HMM_PI32 / 2), -1.0f, trigAbsError);
    EXPECT_NEAR(HMM_SinF(-HMM_PI32 / 2), -1.0f, trigAbsError);

    EXPECT_NEAR(HMM_CosF(0.0f), 1.0f, trigAbsError);
    EXPECT_NEAR(HMM_CosF(HMM_PI32 / 2), 0.0f, trigAbsError);
    EXPECT_NEAR(HMM_CosF(HMM_PI32), -1.0f, trigAbsError);
    EXPECT_NEAR(HMM_CosF(3 * HMM_PI32 / 2), 0.0f, trigAbsError);
    EXPECT_NEAR(HMM_CosF(-HMM_PI32), -1.0f, trigAbsError);

    EXPECT_NEAR(HMM_TanF(0.0f), 0.0f, trigAbsError);
    EXPECT_NEAR(HMM_TanF(HMM_PI32 / 4), 1.0f, trigAbsError);
    EXPECT_NEAR(HMM_TanF(3 * HMM_PI32 / 4), -1.0f, trigAbsError);
    EXPECT_NEAR(HMM_TanF(HMM_PI32), 0.0f, trigAbsError);
    EXPECT_NEAR(HMM_TanF(-HMM_PI32 / 4), -1.0f, trigAbsError);

    // This isn't the most rigorous because we're really just sanity-
    // checking that things work by default.
}

TEST(ScalarMath, SqrtF)
{
    EXPECT_FLOAT_EQ(HMM_SqrtF(16.0f), 4.0f);
}

TEST(ScalarMath, ToRadians)
{
    EXPECT_FLOAT_EQ(HMM_ToRadians(0.0f), 0);
    EXPECT_FLOAT_EQ(HMM_ToRadians(180.0f), HMM_PI32);
    EXPECT_FLOAT_EQ(HMM_ToRadians(-180.0f), -HMM_PI32);
}

TEST(ScalarMath, SquareRoot)
{
    // EXPECT_FLOAT_EQ(HMM_SquareRoot(16.0f), 4.0f);
    FAIL() << "Bad header, function not defined. See commented line above.";
}

TEST(ScalarMath, FastInverseSquareRoot)
{
    // EXPECT_FLOAT_EQ(HMM_FastInverseSquareRoot(4.0f), 0.5f); // linker error, no function body
    FAIL() << "Bad header, function not defined. See commented line above.";
}

TEST(ScalarMath, Power)
{
    EXPECT_FLOAT_EQ(HMM_Power(2.0f, 0), 1.0f);
    EXPECT_FLOAT_EQ(HMM_Power(2.0f, 4), 16.0f);
    EXPECT_FLOAT_EQ(HMM_Power(2.0f, -2), 0.25f);
}

TEST(ScalarMath, Clamp)
{
    EXPECT_FLOAT_EQ(HMM_Clamp(-2.0f, 0.0f, 2.0f), 0.0f);
    EXPECT_FLOAT_EQ(HMM_Clamp(-2.0f, -3.0f, 2.0f), -2.0f);
    EXPECT_FLOAT_EQ(HMM_Clamp(-2.0f, 3.0f, 2.0f), 2.0f);
}

TEST(Initialization, Vectors)
{
    //
    // Test vec2
    // 
    hmm_vec2 v2 = HMM_Vec2(1.0f, 2.0f);
    hmm_vec2 v2i = HMM_Vec2(1, 2);

    EXPECT_FLOAT_EQ(v2.X, 1.0f);
    EXPECT_FLOAT_EQ(v2.Y, 2.0f);

    EXPECT_FLOAT_EQ(v2i.X, 1.0f);
    EXPECT_FLOAT_EQ(v2i.Y, 2.0f);

    //
    // Test vec3
    //
    hmm_vec3 v3 = HMM_Vec3(1.0f, 2.0f, 3.0f);
    hmm_vec3 v3i = HMM_Vec3i(1, 2, 3);

    EXPECT_FLOAT_EQ(v3.X, 1.0f);
    EXPECT_FLOAT_EQ(v3.Y, 2.0f);
    EXPECT_FLOAT_EQ(v3.Z, 3.0f);

    EXPECT_FLOAT_EQ(v3i.X, 1.0f);
    EXPECT_FLOAT_EQ(v3i.Y, 2.0f);
    EXPECT_FLOAT_EQ(v3i.Z, 3.0f);

    //
    // Test vec4
    //
    hmm_vec4 v4 = HMM_Vec4(1.0f, 2.0f, 3.0f, 4.0f);
    hmm_vec4 v4i = HMM_Vec4i(1, 2, 3, 4);
    hmm_vec4 v4v = HMM_Vec4v(v3, 4.0f);

    EXPECT_FLOAT_EQ(v4.X, 1.0f);
    EXPECT_FLOAT_EQ(v4.Y, 2.0f);
    EXPECT_FLOAT_EQ(v4.Z, 3.0f);
    EXPECT_FLOAT_EQ(v4.W, 4.0f);

    EXPECT_FLOAT_EQ(v4i.X, 1.0f);
    EXPECT_FLOAT_EQ(v4i.Y, 2.0f);
    EXPECT_FLOAT_EQ(v4i.Z, 3.0f);
    EXPECT_FLOAT_EQ(v4i.W, 4.0f);

    EXPECT_FLOAT_EQ(v4v.X, 1.0f);
    EXPECT_FLOAT_EQ(v4v.Y, 2.0f);
    EXPECT_FLOAT_EQ(v4v.Z, 3.0f);
    EXPECT_FLOAT_EQ(v4v.W, 4.0f);
}

TEST(Initialization, MatrixEmpty)
{
    hmm_mat4 m4 = HMM_Mat4();
    for (int Column = 0; Column < 4; ++Column)
    {
        for (int Row = 0; Row < 4; ++Row)
        {
            EXPECT_FLOAT_EQ(m4.Elements[Column][Row], 0) << "At column " << Column << ", row " << Row;
        }
    }
}

TEST(Initialization, MatrixDiagonal)
{
    hmm_mat4 m4d = HMM_Mat4d(1.0f);
    for (int Column = 0; Column < 4; ++Column)
    {
        for (int Row = 0; Row < 4; ++Row)
        {
            if (Column == Row) {
                EXPECT_FLOAT_EQ(m4d.Elements[Column][Row], 1.0f) << "At column " << Column << ", row " << Row;
            } else {
                EXPECT_FLOAT_EQ(m4d.Elements[Column][Row], 0) << "At column " << Column << ", row " << Row;
            }
        }
    }
}

TEST(VectorOps, Inner)
{
    hmm_vec3 v1 = HMM_Vec3(1.0f, 2.0f, 3.0f);
    hmm_vec3 v2 = HMM_Vec3(4.0f, 5.0f, 6.0f);

    EXPECT_FLOAT_EQ(HMM_Inner(v1, v2), 32.0f);
}

TEST(VectorOps, LengthSquareRoot)
{
    hmm_vec3 v = HMM_Vec3(1.0f, -2.0f, 3.0f);

    EXPECT_FLOAT_EQ(HMM_LengthSquareRoot(v), 14.0f);
}

TEST(VectorOps, Length)
{
    hmm_vec3 v = HMM_Vec3(2.0f, -3.0f, 6.0f);

    EXPECT_FLOAT_EQ(HMM_Length(v), 7.0f);
}

TEST(VectorOps, Normalize)
{
    hmm_vec3 v = HMM_Vec3(1.0f, -2.0f, 3.0f);

    hmm_vec3 result = HMM_Normalize(v);

    EXPECT_FLOAT_EQ(HMM_Length(result), 1.0f);
    EXPECT_LT(result.Y, 0);
}

TEST(VectorOps, Cross)
{
    hmm_vec3 v1 = HMM_Vec3(1.0f, 2.0f, 3.0f);
    hmm_vec3 v2 = HMM_Vec3(4.0f, 5.0f, 6.0f);

    hmm_vec3 result = HMM_Cross(v1, v2);

    EXPECT_FLOAT_EQ(result.X, -3.0f);
    EXPECT_FLOAT_EQ(result.Y, 6.0f);
    EXPECT_FLOAT_EQ(result.Z, -3.0f);
}

TEST(VectorOps, Dot)
{
    hmm_vec3 v1 = HMM_Vec3(1.0f, 2.0f, 3.0f);
    hmm_vec3 v2 = HMM_Vec3(4.0f, 5.0f, 6.0f);

    EXPECT_FLOAT_EQ(HMM_Inner(v1, v2), 32.0f);
}

TEST(Addition, Vec2)
{
    hmm_vec2 v2_1 = HMM_Vec2(1.0f, 2.0f);
    hmm_vec2 v2_2 = HMM_Vec2(3.0f, 4.0f);

    {
        hmm_vec2 result = HMM_AddVec2(v2_1, v2_2);
        EXPECT_FLOAT_EQ(result.X, 4.0f);
        EXPECT_FLOAT_EQ(result.Y, 6.0f);
    }
    {
        hmm_vec2 result = HMM_Add(v2_1, v2_2);
        EXPECT_FLOAT_EQ(result.X, 4.0f);
        EXPECT_FLOAT_EQ(result.Y, 6.0f);
    }
    {
        hmm_vec2 result = v2_1 + v2_2;
        EXPECT_FLOAT_EQ(result.X, 4.0f);
        EXPECT_FLOAT_EQ(result.Y, 6.0f);
    }    

    v2_1 += v2_2;
    EXPECT_FLOAT_EQ(v2_1.X, 4.0f);
    EXPECT_FLOAT_EQ(v2_1.Y, 6.0f);
}

TEST(Addition, Vec3)
{
    hmm_vec3 v3_1 = HMM_Vec3(1.0f, 2.0f, 3.0f);
    hmm_vec3 v3_2 = HMM_Vec3(4.0f, 5.0f, 6.0f);

    {
        hmm_vec3 result = HMM_AddVec3(v3_1, v3_2);
        EXPECT_FLOAT_EQ(result.X, 5.0f);
        EXPECT_FLOAT_EQ(result.Y, 7.0f);
        EXPECT_FLOAT_EQ(result.Z, 9.0f);    
    }
    {
        hmm_vec3 result = HMM_Add(v3_1, v3_2);
        EXPECT_FLOAT_EQ(result.X, 5.0f);
        EXPECT_FLOAT_EQ(result.Y, 7.0f);
        EXPECT_FLOAT_EQ(result.Z, 9.0f);
    }
    {
        hmm_vec3 result = v3_1 + v3_2;
        EXPECT_FLOAT_EQ(result.X, 5.0f);
        EXPECT_FLOAT_EQ(result.Y, 7.0f);
        EXPECT_FLOAT_EQ(result.Z, 9.0f);
    }

    v3_1 += v3_2;
    EXPECT_FLOAT_EQ(v3_1.X, 5.0f);
    EXPECT_FLOAT_EQ(v3_1.Y, 7.0f);
    EXPECT_FLOAT_EQ(v3_1.Z, 9.0f);
}

TEST(Addition, Vec4)
{
    hmm_vec4 v4_1 = HMM_Vec4(1.0f, 2.0f, 3.0f, 4.0f);
    hmm_vec4 v4_2 = HMM_Vec4(5.0f, 6.0f, 7.0f, 8.0f);
    
    {
        hmm_vec4 result = HMM_AddVec4(v4_1, v4_2);
        EXPECT_FLOAT_EQ(result.X, 6.0f);
        EXPECT_FLOAT_EQ(result.Y, 8.0f);
        EXPECT_FLOAT_EQ(result.Z, 10.0f);
        EXPECT_FLOAT_EQ(result.W, 12.0f);
    }
    {
        hmm_vec4 result = HMM_Add(v4_1, v4_2);
        EXPECT_FLOAT_EQ(result.X, 6.0f);
        EXPECT_FLOAT_EQ(result.Y, 8.0f);
        EXPECT_FLOAT_EQ(result.Z, 10.0f);
        EXPECT_FLOAT_EQ(result.W, 12.0f);
    }
    {
        hmm_vec4 result = v4_1 + v4_2;
        EXPECT_FLOAT_EQ(result.X, 6.0f);
        EXPECT_FLOAT_EQ(result.Y, 8.0f);
        EXPECT_FLOAT_EQ(result.Z, 10.0f);
        EXPECT_FLOAT_EQ(result.W, 12.0f);
    }

    v4_1 += v4_2;
    EXPECT_FLOAT_EQ(v4_1.X, 6.0f);
    EXPECT_FLOAT_EQ(v4_1.Y, 8.0f);
    EXPECT_FLOAT_EQ(v4_1.Z, 10.0f);
    EXPECT_FLOAT_EQ(v4_1.W, 12.0f);
}

TEST(Addition, Mat4)
{
    hmm_mat4 m4_1 = HMM_Mat4(); // will have 1 - 16
    hmm_mat4 m4_2 = HMM_Mat4(); // will have 17 - 32

    // Fill the matrices
    int Counter = 1;
    for (int Column = 0; Column < 4; ++Column)
    {
        for (int Row = 0; Row < 4; ++Row)
        {
            m4_1.Elements[Column][Row] = Counter;
            ++Counter;
        }
    }
    for (int Column = 0; Column < 4; ++Column)
    {
        for (int Row = 0; Row < 4; ++Row)
        {
            m4_2.Elements[Column][Row] = Counter;
            ++Counter;
        }
    }

    // Test the results
    {
        hmm_mat4 result = HMM_AddMat4(m4_1, m4_2);
        float Expected = 18.0f;
        for (int Column = 0; Column < 4; ++Column)
        {
            for (int Row = 0; Row < 4; ++Row)
            {
                EXPECT_FLOAT_EQ(result.Elements[Column][Row], Expected) << "At column " << Column << ", row " << Row;
                Expected += 2.0f;
            }
        }
    }
    {
        hmm_mat4 result = HMM_Add(m4_1, m4_2);
        float Expected = 18.0f;
        for (int Column = 0; Column < 4; ++Column)
        {
            for (int Row = 0; Row < 4; ++Row)
            {
                EXPECT_FLOAT_EQ(result.Elements[Column][Row], Expected) << "At column " << Column << ", row " << Row;
                Expected += 2.0f;
            }
        }
    }
    {
        hmm_mat4 result = m4_1 + m4_2;
        float Expected = 18.0f;
        for (int Column = 0; Column < 4; ++Column)
        {
            for (int Row = 0; Row < 4; ++Row)
            {
                EXPECT_FLOAT_EQ(result.Elements[Column][Row], Expected) << "At column " << Column << ", row " << Row;
                Expected += 2.0f;
            }
        }
    }

    m4_1 += m4_2;
    float Expected = 18.0f;
    for (int Column = 0; Column < 4; ++Column)
    {
        for (int Row = 0; Row < 4; ++Row)
        {
            EXPECT_FLOAT_EQ(m4_1.Elements[Column][Row], Expected) << "At column " << Column << ", row " << Row;
            Expected += 2.0f;
        }
    }
}

TEST(Subtraction, Vec2)
{
    hmm_vec2 v2_1 = HMM_Vec2(1.0f, 2.0f);
    hmm_vec2 v2_2 = HMM_Vec2(3.0f, 4.0f);

    {
        hmm_vec2 result = HMM_SubtractVec2(v2_1, v2_2);
        EXPECT_FLOAT_EQ(result.X, -2.0f);
        EXPECT_FLOAT_EQ(result.Y, -2.0f);
    }
    {
        hmm_vec2 result = HMM_Subtract(v2_1, v2_2);
        EXPECT_FLOAT_EQ(result.X, -2.0f);
        EXPECT_FLOAT_EQ(result.Y, -2.0f);
    }
    {
        hmm_vec2 result = v2_1 - v2_2;
        EXPECT_FLOAT_EQ(result.X, -2.0f);
        EXPECT_FLOAT_EQ(result.Y, -2.0f);
    }

    v2_1 -= v2_2;
    EXPECT_FLOAT_EQ(v2_1.X, -2.0f);
    EXPECT_FLOAT_EQ(v2_1.Y, -2.0f);
}

TEST(Subtraction, Vec3)
{
    hmm_vec3 v3_1 = HMM_Vec3(1.0f, 2.0f, 3.0f);
    hmm_vec3 v3_2 = HMM_Vec3(4.0f, 5.0f, 6.0f);

    {
        hmm_vec3 result = HMM_SubtractVec3(v3_1, v3_2);
        EXPECT_FLOAT_EQ(result.X, -3.0f);
        EXPECT_FLOAT_EQ(result.Y, -3.0f);
        EXPECT_FLOAT_EQ(result.Z, -3.0f);
    }
    {
        hmm_vec3 result = HMM_Subtract(v3_1, v3_2);
        EXPECT_FLOAT_EQ(result.X, -3.0f);
        EXPECT_FLOAT_EQ(result.Y, -3.0f);
        EXPECT_FLOAT_EQ(result.Z, -3.0f);
    }
    {
        hmm_vec3 result = v3_1 - v3_2;
        EXPECT_FLOAT_EQ(result.X, -3.0f);
        EXPECT_FLOAT_EQ(result.Y, -3.0f);
        EXPECT_FLOAT_EQ(result.Z, -3.0f);
    }

    v3_1 -= v3_2;
    EXPECT_FLOAT_EQ(v3_1.X, -3.0f);
    EXPECT_FLOAT_EQ(v3_1.Y, -3.0f);
    EXPECT_FLOAT_EQ(v3_1.Z, -3.0f);
}

TEST(Subtraction, Vec4)
{
    hmm_vec4 v4_1 = HMM_Vec4(1.0f, 2.0f, 3.0f, 4.0f);
    hmm_vec4 v4_2 = HMM_Vec4(5.0f, 6.0f, 7.0f, 8.0f);

    {
        hmm_vec4 result = HMM_SubtractVec4(v4_1, v4_2);
        EXPECT_FLOAT_EQ(result.X, -4.0f);
        EXPECT_FLOAT_EQ(result.Y, -4.0f);
        EXPECT_FLOAT_EQ(result.Z, -4.0f);
        EXPECT_FLOAT_EQ(result.W, -4.0f);
    }
    {
        hmm_vec4 result = HMM_Subtract(v4_1, v4_2);
        EXPECT_FLOAT_EQ(result.X, -4.0f);
        EXPECT_FLOAT_EQ(result.Y, -4.0f);
        EXPECT_FLOAT_EQ(result.Z, -4.0f);
        EXPECT_FLOAT_EQ(result.W, -4.0f);
    }
    {
        hmm_vec4 result = v4_1 - v4_2;
        EXPECT_FLOAT_EQ(result.X, -4.0f);
        EXPECT_FLOAT_EQ(result.Y, -4.0f);
        EXPECT_FLOAT_EQ(result.Z, -4.0f);
        EXPECT_FLOAT_EQ(result.W, -4.0f);
    }

    v4_1 -= v4_2;
    EXPECT_FLOAT_EQ(v4_1.X, -4.0f);
    EXPECT_FLOAT_EQ(v4_1.Y, -4.0f);
    EXPECT_FLOAT_EQ(v4_1.Z, -4.0f);
    EXPECT_FLOAT_EQ(v4_1.W, -4.0f);
}

TEST(Subtraction, Mat4)
{
    hmm_mat4 m4_1 = HMM_Mat4(); // will have 1 - 16
    hmm_mat4 m4_2 = HMM_Mat4(); // will have 17 - 32

    // Fill the matrices
    int Counter = 1;
    for (int Column = 0; Column < 4; ++Column)
    {
        for (int Row = 0; Row < 4; ++Row)
        {
            m4_1.Elements[Column][Row] = Counter;
            ++Counter;
        }
    }
    for (int Column = 0; Column < 4; ++Column)
    {
        for (int Row = 0; Row < 4; ++Row)
        {
            m4_2.Elements[Column][Row] = Counter;
            ++Counter;
        }
    }

    // Test the results
    {
        hmm_mat4 result = HMM_SubtractMat4(m4_1, m4_2);
        for (int Column = 0; Column < 4; ++Column)
        {
            for (int Row = 0; Row < 4; ++Row)
            {
                EXPECT_FLOAT_EQ(result.Elements[Column][Row], -16.0f) << "At column " << Column << ", row " << Row;
            }
        }
    }
    {
        hmm_mat4 result = HMM_Subtract(m4_1, m4_2);
        for (int Column = 0; Column < 4; ++Column)
        {
            for (int Row = 0; Row < 4; ++Row)
            {
                EXPECT_FLOAT_EQ(result.Elements[Column][Row], -16.0f) << "At column " << Column << ", row " << Row;
            }
        }
    }
    {
        hmm_mat4 result = m4_1 - m4_2;
        for (int Column = 0; Column < 4; ++Column)
        {
            for (int Row = 0; Row < 4; ++Row)
            {
                EXPECT_FLOAT_EQ(result.Elements[Column][Row], -16.0f) << "At column " << Column << ", row " << Row;
            }
        }
    }

    m4_1 -= m4_2;
    for (int Column = 0; Column < 4; ++Column)
    {
        for (int Row = 0; Row < 4; ++Row)
        {
            EXPECT_FLOAT_EQ(m4_1.Elements[Column][Row], -16.0f) << "At column " << Column << ", row " << Row;
        }
    }
}

TEST(Multiplication, Vec2Vec2)
{
    hmm_vec2 v2_1 = HMM_Vec2(1.0f, 2.0f);
    hmm_vec2 v2_2 = HMM_Vec2(3.0f, 4.0f);

    {
        hmm_vec2 result = HMM_MultiplyVec2(v2_1, v2_2);
        EXPECT_FLOAT_EQ(result.X, 3.0f);
        EXPECT_FLOAT_EQ(result.Y, 8.0f);
    }
    {
        hmm_vec2 result = HMM_Multiply(v2_1, v2_2);
        EXPECT_FLOAT_EQ(result.X, 3.0f);
        EXPECT_FLOAT_EQ(result.Y, 8.0f);
    }
    {
        hmm_vec2 result = v2_1 * v2_2;
        EXPECT_FLOAT_EQ(result.X, 3.0f);
        EXPECT_FLOAT_EQ(result.Y, 8.0f);
    }

    v2_1 *= v2_2;
    EXPECT_FLOAT_EQ(v2_1.X, 3.0f);
    EXPECT_FLOAT_EQ(v2_1.Y, 8.0f);
}

TEST(Multiplication, Vec2Scalar)
{
    hmm_vec2 v2 = HMM_Vec2(1.0f, 2.0f);
    float s = 3.0f;

    {
        hmm_vec2 result = HMM_MultiplyVec2f(v2, s);
        EXPECT_FLOAT_EQ(result.X, 3.0f);
        EXPECT_FLOAT_EQ(result.Y, 6.0f);
    }
    {
        hmm_vec2 result = HMM_Multiply(v2, s);
        EXPECT_FLOAT_EQ(result.X, 3.0f);
        EXPECT_FLOAT_EQ(result.Y, 6.0f);
    }
    {
        hmm_vec2 result = v2 * s;
        EXPECT_FLOAT_EQ(result.X, 3.0f);
        EXPECT_FLOAT_EQ(result.Y, 6.0f);
    }
    {
        hmm_vec2 result = s * v2;
        EXPECT_FLOAT_EQ(result.X, 3.0f);
        EXPECT_FLOAT_EQ(result.Y, 6.0f);
    }

    v2 *= s;
    EXPECT_FLOAT_EQ(v2.X, 3.0f);
    EXPECT_FLOAT_EQ(v2.Y, 6.0f);
}

TEST(Multiplication, Vec3Vec3)
{
    hmm_vec3 v3_1 = HMM_Vec3(1.0f, 2.0f, 3.0f);
    hmm_vec3 v3_2 = HMM_Vec3(4.0f, 5.0f, 6.0f);

    {
        hmm_vec3 result = HMM_MultiplyVec3(v3_1, v3_2);
        EXPECT_FLOAT_EQ(result.X, 4.0f);
        EXPECT_FLOAT_EQ(result.Y, 10.0f);
        EXPECT_FLOAT_EQ(result.Z, 18.0f);
    }
    {
        hmm_vec3 result = HMM_Multiply(v3_1, v3_2);
        EXPECT_FLOAT_EQ(result.X, 4.0f);
        EXPECT_FLOAT_EQ(result.Y, 10.0f);
        EXPECT_FLOAT_EQ(result.Z, 18.0f);
    }
    {
        hmm_vec3 result = v3_1 * v3_2;
        EXPECT_FLOAT_EQ(result.X, 4.0f);
        EXPECT_FLOAT_EQ(result.Y, 10.0f);
        EXPECT_FLOAT_EQ(result.Z, 18.0f);
    }

    v3_1 *= v3_2;
    EXPECT_FLOAT_EQ(v3_1.X, 4.0f);
    EXPECT_FLOAT_EQ(v3_1.Y, 10.0f);
    EXPECT_FLOAT_EQ(v3_1.Z, 18.0f);
}

TEST(Multiplication, Vec3Scalar)
{
    hmm_vec3 v3 = HMM_Vec3(1.0f, 2.0f, 3.0f);
    float s = 3.0f;

    {
        hmm_vec3 result = HMM_MultiplyVec3f(v3, s);
        EXPECT_FLOAT_EQ(result.X, 3.0f);
        EXPECT_FLOAT_EQ(result.Y, 6.0f);
        EXPECT_FLOAT_EQ(result.Z, 9.0f);
    }
    {
        hmm_vec3 result = HMM_Multiply(v3, s);
        EXPECT_FLOAT_EQ(result.X, 3.0f);
        EXPECT_FLOAT_EQ(result.Y, 6.0f);
        EXPECT_FLOAT_EQ(result.Z, 9.0f);
    }
    {
        hmm_vec3 result = v3 * s;
        EXPECT_FLOAT_EQ(result.X, 3.0f);
        EXPECT_FLOAT_EQ(result.Y, 6.0f);
        EXPECT_FLOAT_EQ(result.Z, 9.0f);
    }
    {
        hmm_vec3 result = s * v3;
        EXPECT_FLOAT_EQ(result.X, 3.0f);
        EXPECT_FLOAT_EQ(result.Y, 6.0f);
        EXPECT_FLOAT_EQ(result.Z, 9.0f);
    }

    v3 *= s;
    EXPECT_FLOAT_EQ(v3.X, 3.0f);
    EXPECT_FLOAT_EQ(v3.Y, 6.0f);
    EXPECT_FLOAT_EQ(v3.Z, 9.0f);
}

TEST(Multiplication, Vec4Vec4)
{
    hmm_vec4 v4_1 = HMM_Vec4(1.0f, 2.0f, 3.0f, 4.0f);
    hmm_vec4 v4_2 = HMM_Vec4(5.0f, 6.0f, 7.0f, 8.0f);

    {
        hmm_vec4 result = HMM_MultiplyVec4(v4_1, v4_2);
        EXPECT_FLOAT_EQ(result.X, 5.0f);
        EXPECT_FLOAT_EQ(result.Y, 12.0f);
        EXPECT_FLOAT_EQ(result.Z, 21.0f);
        EXPECT_FLOAT_EQ(result.W, 32.0f);
    }
    {
        hmm_vec4 result = HMM_Multiply(v4_1, v4_2);
        EXPECT_FLOAT_EQ(result.X, 5.0f);
        EXPECT_FLOAT_EQ(result.Y, 12.0f);
        EXPECT_FLOAT_EQ(result.Z, 21.0f);
        EXPECT_FLOAT_EQ(result.W, 32.0f);
    }
    {
        hmm_vec4 result = v4_1 * v4_2;
        EXPECT_FLOAT_EQ(result.X, 5.0f);
        EXPECT_FLOAT_EQ(result.Y, 12.0f);
        EXPECT_FLOAT_EQ(result.Z, 21.0f);
        EXPECT_FLOAT_EQ(result.W, 32.0f);
    }

    v4_1 *= v4_2;
    EXPECT_FLOAT_EQ(v4_1.X, 5.0f);
    EXPECT_FLOAT_EQ(v4_1.Y, 12.0f);
    EXPECT_FLOAT_EQ(v4_1.Z, 21.0f);
    EXPECT_FLOAT_EQ(v4_1.W, 32.0f);
}

TEST(Multiplication, Vec4Scalar)
{
    hmm_vec4 v4 = HMM_Vec4(1.0f, 2.0f, 3.0f, 4.0f);
    float s = 3.0f;

    {
        hmm_vec4 result = HMM_MultiplyVec4f(v4, s);
        EXPECT_FLOAT_EQ(result.X, 3.0f);
        EXPECT_FLOAT_EQ(result.Y, 6.0f);
        EXPECT_FLOAT_EQ(result.Z, 9.0f);
        EXPECT_FLOAT_EQ(result.W, 12.0f);
    }
    {
        hmm_vec4 result = HMM_Multiply(v4, s);
        EXPECT_FLOAT_EQ(result.X, 3.0f);
        EXPECT_FLOAT_EQ(result.Y, 6.0f);
        EXPECT_FLOAT_EQ(result.Z, 9.0f);
        EXPECT_FLOAT_EQ(result.W, 12.0f);
    }
    {
        hmm_vec4 result = v4 * s;
        EXPECT_FLOAT_EQ(result.X, 3.0f);
        EXPECT_FLOAT_EQ(result.Y, 6.0f);
        EXPECT_FLOAT_EQ(result.Z, 9.0f);
        EXPECT_FLOAT_EQ(result.W, 12.0f);
    }
    {
        hmm_vec4 result = s * v4;
        EXPECT_FLOAT_EQ(result.X, 3.0f);
        EXPECT_FLOAT_EQ(result.Y, 6.0f);
        EXPECT_FLOAT_EQ(result.Z, 9.0f);
        EXPECT_FLOAT_EQ(result.W, 12.0f);
    }

    v4 *= s;
    EXPECT_FLOAT_EQ(v4.X, 3.0f);
    EXPECT_FLOAT_EQ(v4.Y, 6.0f);
    EXPECT_FLOAT_EQ(v4.Z, 9.0f);
}

TEST(Multiplication, Mat4Mat4)
{
    hmm_mat4 m4_1 = HMM_Mat4(); // will have 1 - 16
    hmm_mat4 m4_2 = HMM_Mat4(); // will have 17 - 32

    // Fill the matrices
    int Counter = 1;
    for (int Column = 0; Column < 4; ++Column)
    {
        for (int Row = 0; Row < 4; ++Row)
        {
            m4_1.Elements[Column][Row] = Counter;
            ++Counter;
        }
    }
    for (int Column = 0; Column < 4; ++Column)
    {
        for (int Row = 0; Row < 4; ++Row)
        {
            m4_2.Elements[Column][Row] = Counter;
            ++Counter;
        }
    }

    // Test the results
    {
        hmm_mat4 result = HMM_MultiplyMat4(m4_1, m4_2);
        EXPECT_FLOAT_EQ(result.Elements[0][0], 538.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][1], 612.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][2], 686.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][3], 760.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][0], 650.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][1], 740.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][2], 830.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][3], 920.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][0], 762.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][1], 868.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][2], 974.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][3], 1080.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][0], 874.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][1], 996.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][2], 1118.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][3], 1240.0f);
    }
    {
        hmm_mat4 result = HMM_Multiply(m4_1, m4_2);
        EXPECT_FLOAT_EQ(result.Elements[0][0], 538.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][1], 612.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][2], 686.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][3], 760.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][0], 650.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][1], 740.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][2], 830.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][3], 920.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][0], 762.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][1], 868.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][2], 974.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][3], 1080.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][0], 874.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][1], 996.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][2], 1118.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][3], 1240.0f);
    }
    {
        hmm_mat4 result = m4_1 * m4_2;
        EXPECT_FLOAT_EQ(result.Elements[0][0], 538.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][1], 612.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][2], 686.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][3], 760.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][0], 650.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][1], 740.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][2], 830.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][3], 920.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][0], 762.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][1], 868.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][2], 974.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][3], 1080.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][0], 874.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][1], 996.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][2], 1118.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][3], 1240.0f);
    }

    // At the time I wrote this, I intentionally omitted
    // the *= operator for matrices because matrix
    // multiplication is not commutative. (bvisness)
}

TEST(Multiplication, Mat4Scalar)
{
    hmm_mat4 m4 = HMM_Mat4(); // will have 1 - 16
    float s = 3;

    // Fill the matrix
    int Counter = 1;
    for (int Column = 0; Column < 4; ++Column)
    {
        for (int Row = 0; Row < 4; ++Row)
        {
            m4.Elements[Column][Row] = Counter;
            ++Counter;
        }
    }

    // Test the results
    {
        hmm_mat4 result = HMM_MultiplyMat4f(m4, s);
        EXPECT_FLOAT_EQ(result.Elements[0][0], 3.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][1], 6.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][2], 9.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][3], 12.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][0], 15.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][1], 18.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][2], 21.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][3], 24.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][0], 27.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][1], 30.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][2], 33.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][3], 36.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][0], 39.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][1], 42.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][2], 45.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][3], 48.0f);
    }
    {
        hmm_mat4 result = HMM_Multiply(m4, s);
        EXPECT_FLOAT_EQ(result.Elements[0][0], 3.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][1], 6.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][2], 9.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][3], 12.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][0], 15.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][1], 18.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][2], 21.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][3], 24.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][0], 27.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][1], 30.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][2], 33.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][3], 36.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][0], 39.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][1], 42.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][2], 45.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][3], 48.0f);
    }
    {
        hmm_mat4 result = m4 * s;
        EXPECT_FLOAT_EQ(result.Elements[0][0], 3.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][1], 6.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][2], 9.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][3], 12.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][0], 15.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][1], 18.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][2], 21.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][3], 24.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][0], 27.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][1], 30.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][2], 33.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][3], 36.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][0], 39.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][1], 42.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][2], 45.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][3], 48.0f);
    }
    {
        hmm_mat4 result = s * m4;
        EXPECT_FLOAT_EQ(result.Elements[0][0], 3.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][1], 6.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][2], 9.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][3], 12.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][0], 15.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][1], 18.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][2], 21.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][3], 24.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][0], 27.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][1], 30.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][2], 33.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][3], 36.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][0], 39.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][1], 42.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][2], 45.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][3], 48.0f);
    }

    m4 *= s;
    EXPECT_FLOAT_EQ(m4.Elements[0][0], 3.0f);
    EXPECT_FLOAT_EQ(m4.Elements[0][1], 6.0f);
    EXPECT_FLOAT_EQ(m4.Elements[0][2], 9.0f);
    EXPECT_FLOAT_EQ(m4.Elements[0][3], 12.0f);
    EXPECT_FLOAT_EQ(m4.Elements[1][0], 15.0f);
    EXPECT_FLOAT_EQ(m4.Elements[1][1], 18.0f);
    EXPECT_FLOAT_EQ(m4.Elements[1][2], 21.0f);
    EXPECT_FLOAT_EQ(m4.Elements[1][3], 24.0f);
    EXPECT_FLOAT_EQ(m4.Elements[2][0], 27.0f);
    EXPECT_FLOAT_EQ(m4.Elements[2][1], 30.0f);
    EXPECT_FLOAT_EQ(m4.Elements[2][2], 33.0f);
    EXPECT_FLOAT_EQ(m4.Elements[2][3], 36.0f);
    EXPECT_FLOAT_EQ(m4.Elements[3][0], 39.0f);
    EXPECT_FLOAT_EQ(m4.Elements[3][1], 42.0f);
    EXPECT_FLOAT_EQ(m4.Elements[3][2], 45.0f);
    EXPECT_FLOAT_EQ(m4.Elements[3][3], 48.0f);
}

TEST(Multiplication, Mat4Vec4)
{
    hmm_mat4 m4 = HMM_Mat4(); // will have 1 - 16
    hmm_vec4 v4 = HMM_Vec4(1.0f, 2.0f, 3.0f, 4.0f);

    // Fill the matrix
    int Counter = 1;
    for (int Column = 0; Column < 4; ++Column)
    {
        for (int Row = 0; Row < 4; ++Row)
        {
            m4.Elements[Column][Row] = Counter;
            ++Counter;
        }
    }

    // Test the results
    {
        hmm_vec4 result = HMM_MultiplyMat4ByVec4(m4, v4);
        EXPECT_FLOAT_EQ(result.X, 90);
        EXPECT_FLOAT_EQ(result.Y, 100);
        EXPECT_FLOAT_EQ(result.Z, 110);
        EXPECT_FLOAT_EQ(result.W, 120);
    }
    {
        hmm_vec4 result = HMM_Multiply(m4, v4);
        EXPECT_FLOAT_EQ(result.X, 90);
        EXPECT_FLOAT_EQ(result.Y, 100);
        EXPECT_FLOAT_EQ(result.Z, 110);
        EXPECT_FLOAT_EQ(result.W, 120);
    }
    {
        hmm_vec4 result = m4 * v4;
        EXPECT_FLOAT_EQ(result.X, 90);
        EXPECT_FLOAT_EQ(result.Y, 100);
        EXPECT_FLOAT_EQ(result.Z, 110);
        EXPECT_FLOAT_EQ(result.W, 120);
    }

    // *= makes no sense for this particular case.
}

TEST(Division, Vec2Vec2)
{
    hmm_vec2 v2_1 = HMM_Vec2(1.0f, 3.0f);
    hmm_vec2 v2_2 = HMM_Vec2(2.0f, 4.0f);

    {
        hmm_vec2 result = HMM_DivideVec2(v2_1, v2_2);
        EXPECT_FLOAT_EQ(result.X, 0.5f);
        EXPECT_FLOAT_EQ(result.Y, 0.75f);
    }
    {
        hmm_vec2 result = HMM_Divide(v2_1, v2_2);
        EXPECT_FLOAT_EQ(result.X, 0.5f);
        EXPECT_FLOAT_EQ(result.Y, 0.75f);
    }
    {
        hmm_vec2 result = v2_1 / v2_2;
        EXPECT_FLOAT_EQ(result.X, 0.5f);
        EXPECT_FLOAT_EQ(result.Y, 0.75f);
    }

    v2_1 /= v2_2;
    EXPECT_FLOAT_EQ(v2_1.X, 0.5f);
    EXPECT_FLOAT_EQ(v2_1.Y, 0.75f);
}

TEST(Division, Vec2Scalar)
{
    hmm_vec2 v2 = HMM_Vec2(1.0f, 2.0f);
    float s = 2;

    {
        hmm_vec2 result = HMM_DivideVec2f(v2, s);
        EXPECT_FLOAT_EQ(result.X, 0.5f);
        EXPECT_FLOAT_EQ(result.Y, 1.0f);
    }
    {
        hmm_vec2 result = HMM_Divide(v2, s);
        EXPECT_FLOAT_EQ(result.X, 0.5f);
        EXPECT_FLOAT_EQ(result.Y, 1.0f);
    }
    {
        hmm_vec2 result = v2 / s;
        EXPECT_FLOAT_EQ(result.X, 0.5f);
        EXPECT_FLOAT_EQ(result.Y, 1.0f);
    }

    v2 /= s;
    EXPECT_FLOAT_EQ(v2.X, 0.5f);
    EXPECT_FLOAT_EQ(v2.Y, 1.0f);
}

TEST(Division, Vec3Vec3)
{
    hmm_vec3 v3_1 = HMM_Vec3(1.0f, 3.0f, 5.0f);
    hmm_vec3 v3_2 = HMM_Vec3(2.0f, 4.0f, 0.5f);

    {
        hmm_vec3 result = HMM_DivideVec3(v3_1, v3_2);
        EXPECT_FLOAT_EQ(result.X, 0.5f);
        EXPECT_FLOAT_EQ(result.Y, 0.75f);
        EXPECT_FLOAT_EQ(result.Z, 10.0f);
    }
    {
        hmm_vec3 result = HMM_Divide(v3_1, v3_2);
        EXPECT_FLOAT_EQ(result.X, 0.5f);
        EXPECT_FLOAT_EQ(result.Y, 0.75f);
        EXPECT_FLOAT_EQ(result.Z, 10.0f);
    }
    {
        hmm_vec3 result = v3_1 / v3_2;
        EXPECT_FLOAT_EQ(result.X, 0.5f);
        EXPECT_FLOAT_EQ(result.Y, 0.75f);
        EXPECT_FLOAT_EQ(result.Z, 10.0f);
    }

    v3_1 /= v3_2;
    EXPECT_FLOAT_EQ(v3_1.X, 0.5f);
    EXPECT_FLOAT_EQ(v3_1.Y, 0.75f);
    EXPECT_FLOAT_EQ(v3_1.Z, 10.0f);
}

TEST(Division, Vec3Scalar)
{
    hmm_vec3 v3 = HMM_Vec3(1.0f, 2.0f, 3.0f);
    float s = 2;

    {
        hmm_vec3 result = HMM_DivideVec3f(v3, s);
        EXPECT_FLOAT_EQ(result.X, 0.5f);
        EXPECT_FLOAT_EQ(result.Y, 1.0f);
        EXPECT_FLOAT_EQ(result.Z, 1.5f);
    }
    {
        hmm_vec3 result = HMM_Divide(v3, s);
        EXPECT_FLOAT_EQ(result.X, 0.5f);
        EXPECT_FLOAT_EQ(result.Y, 1.0f);
        EXPECT_FLOAT_EQ(result.Z, 1.5f);
    }
    {
        hmm_vec3 result = v3 / s;
        EXPECT_FLOAT_EQ(result.X, 0.5f);
        EXPECT_FLOAT_EQ(result.Y, 1.0f);
        EXPECT_FLOAT_EQ(result.Z, 1.5f);
    }

    v3 /= s;
    EXPECT_FLOAT_EQ(v3.X, 0.5f);
    EXPECT_FLOAT_EQ(v3.Y, 1.0f);
    EXPECT_FLOAT_EQ(v3.Z, 1.5f);
}

TEST(Division, Vec4Vec4)
{
    hmm_vec4 v4_1 = HMM_Vec4(1.0f, 3.0f, 5.0f, 1.0f);
    hmm_vec4 v4_2 = HMM_Vec4(2.0f, 4.0f, 0.5f, 4.0f);

    {
        hmm_vec4 result = HMM_DivideVec4(v4_1, v4_2);
        EXPECT_FLOAT_EQ(result.X, 0.5f);
        EXPECT_FLOAT_EQ(result.Y, 0.75f);
        EXPECT_FLOAT_EQ(result.Z, 10.0f);
        EXPECT_FLOAT_EQ(result.W, 0.25f);
    }
    {
        hmm_vec4 result = HMM_Divide(v4_1, v4_2);
        EXPECT_FLOAT_EQ(result.X, 0.5f);
        EXPECT_FLOAT_EQ(result.Y, 0.75f);
        EXPECT_FLOAT_EQ(result.Z, 10.0f);
        EXPECT_FLOAT_EQ(result.W, 0.25f);
    }
    {
        hmm_vec4 result = v4_1 / v4_2;
        EXPECT_FLOAT_EQ(result.X, 0.5f);
        EXPECT_FLOAT_EQ(result.Y, 0.75f);
        EXPECT_FLOAT_EQ(result.Z, 10.0f);
        EXPECT_FLOAT_EQ(result.W, 0.25f);
    }

    v4_1 /= v4_2;
    EXPECT_FLOAT_EQ(v4_1.X, 0.5f);
    EXPECT_FLOAT_EQ(v4_1.Y, 0.75f);
    EXPECT_FLOAT_EQ(v4_1.Z, 10.0f);
    EXPECT_FLOAT_EQ(v4_1.W, 0.25f);
}

TEST(Division, Vec4Scalar)
{
    hmm_vec4 v4 = HMM_Vec4(1.0f, 2.0f, 3.0f, 4.0f);
    float s = 2;

    {
        hmm_vec4 result = HMM_DivideVec4f(v4, s);
        EXPECT_FLOAT_EQ(result.X, 0.5f);
        EXPECT_FLOAT_EQ(result.Y, 1.0f);
        EXPECT_FLOAT_EQ(result.Z, 1.5f);
        EXPECT_FLOAT_EQ(result.W, 2.0f);
    }
    {
        hmm_vec4 result = HMM_Divide(v4, s);
        EXPECT_FLOAT_EQ(result.X, 0.5f);
        EXPECT_FLOAT_EQ(result.Y, 1.0f);
        EXPECT_FLOAT_EQ(result.Z, 1.5f);
        EXPECT_FLOAT_EQ(result.W, 2.0f);
    }
    {
        hmm_vec4 result = v4 / s;
        EXPECT_FLOAT_EQ(result.X, 0.5f);
        EXPECT_FLOAT_EQ(result.Y, 1.0f);
        EXPECT_FLOAT_EQ(result.Z, 1.5f);
        EXPECT_FLOAT_EQ(result.W, 2.0f);
    }

    v4 /= s;
    EXPECT_FLOAT_EQ(v4.X, 0.5f);
    EXPECT_FLOAT_EQ(v4.Y, 1.0f);
    EXPECT_FLOAT_EQ(v4.Z, 1.5f);
    EXPECT_FLOAT_EQ(v4.W, 2.0f);
}

TEST(Division, Mat4Scalar)
{
    hmm_mat4 m4 = HMM_Mat4(); // will have 1 - 16
    float s = 2;

    // Fill the matrix
    int Counter = 1;
    for (int Column = 0; Column < 4; ++Column)
    {
        for (int Row = 0; Row < 4; ++Row)
        {
            m4.Elements[Column][Row] = Counter;
            ++Counter;
        }
    }

    // Test the results
    {
        hmm_mat4 result = HMM_DivideMat4f(m4, s);
        EXPECT_FLOAT_EQ(result.Elements[0][0], 0.5f);
        EXPECT_FLOAT_EQ(result.Elements[0][1], 1.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][2], 1.5f);
        EXPECT_FLOAT_EQ(result.Elements[0][3], 2.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][0], 2.5f);
        EXPECT_FLOAT_EQ(result.Elements[1][1], 3.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][2], 3.5f);
        EXPECT_FLOAT_EQ(result.Elements[1][3], 4.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][0], 4.5f);
        EXPECT_FLOAT_EQ(result.Elements[2][1], 5.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][2], 5.5f);
        EXPECT_FLOAT_EQ(result.Elements[2][3], 6.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][0], 6.5f);
        EXPECT_FLOAT_EQ(result.Elements[3][1], 7.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][2], 7.5f);
        EXPECT_FLOAT_EQ(result.Elements[3][3], 8.0f);
    }
    {
        hmm_mat4 result = HMM_Divide(m4, s);
        EXPECT_FLOAT_EQ(result.Elements[0][0], 0.5f);
        EXPECT_FLOAT_EQ(result.Elements[0][1], 1.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][2], 1.5f);
        EXPECT_FLOAT_EQ(result.Elements[0][3], 2.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][0], 2.5f);
        EXPECT_FLOAT_EQ(result.Elements[1][1], 3.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][2], 3.5f);
        EXPECT_FLOAT_EQ(result.Elements[1][3], 4.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][0], 4.5f);
        EXPECT_FLOAT_EQ(result.Elements[2][1], 5.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][2], 5.5f);
        EXPECT_FLOAT_EQ(result.Elements[2][3], 6.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][0], 6.5f);
        EXPECT_FLOAT_EQ(result.Elements[3][1], 7.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][2], 7.5f);
        EXPECT_FLOAT_EQ(result.Elements[3][3], 8.0f);
    }
    {
        hmm_mat4 result = m4 / s;
        EXPECT_FLOAT_EQ(result.Elements[0][0], 0.5f);
        EXPECT_FLOAT_EQ(result.Elements[0][1], 1.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][2], 1.5f);
        EXPECT_FLOAT_EQ(result.Elements[0][3], 2.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][0], 2.5f);
        EXPECT_FLOAT_EQ(result.Elements[1][1], 3.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][2], 3.5f);
        EXPECT_FLOAT_EQ(result.Elements[1][3], 4.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][0], 4.5f);
        EXPECT_FLOAT_EQ(result.Elements[2][1], 5.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][2], 5.5f);
        EXPECT_FLOAT_EQ(result.Elements[2][3], 6.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][0], 6.5f);
        EXPECT_FLOAT_EQ(result.Elements[3][1], 7.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][2], 7.5f);
        EXPECT_FLOAT_EQ(result.Elements[3][3], 8.0f);
    }

    m4 /= s;
    EXPECT_FLOAT_EQ(m4.Elements[0][0], 0.5f);
    EXPECT_FLOAT_EQ(m4.Elements[0][1], 1.0f);
    EXPECT_FLOAT_EQ(m4.Elements[0][2], 1.5f);
    EXPECT_FLOAT_EQ(m4.Elements[0][3], 2.0f);
    EXPECT_FLOAT_EQ(m4.Elements[1][0], 2.5f);
    EXPECT_FLOAT_EQ(m4.Elements[1][1], 3.0f);
    EXPECT_FLOAT_EQ(m4.Elements[1][2], 3.5f);
    EXPECT_FLOAT_EQ(m4.Elements[1][3], 4.0f);
    EXPECT_FLOAT_EQ(m4.Elements[2][0], 4.5f);
    EXPECT_FLOAT_EQ(m4.Elements[2][1], 5.0f);
    EXPECT_FLOAT_EQ(m4.Elements[2][2], 5.5f);
    EXPECT_FLOAT_EQ(m4.Elements[2][3], 6.0f);
    EXPECT_FLOAT_EQ(m4.Elements[3][0], 6.5f);
    EXPECT_FLOAT_EQ(m4.Elements[3][1], 7.0f);
    EXPECT_FLOAT_EQ(m4.Elements[3][2], 7.5f);
    EXPECT_FLOAT_EQ(m4.Elements[3][3], 8.0f);
}

TEST(Projection, Orthographic)
{
    hmm_mat4 projection = HMM_Orthographic(-10.0f, 10.0f, -5.0f, 5.0f, 0.0f, -10.0f);

    hmm_vec3 original = HMM_Vec3(5.0f, 5.0f, -5.0f);
    hmm_vec4 projected = projection * HMM_Vec4v(original, 1);

    EXPECT_FLOAT_EQ(projected.X, 0.5f);
    EXPECT_FLOAT_EQ(projected.Y, 1.0f);
    EXPECT_FLOAT_EQ(projected.Z, -2.0f);
    EXPECT_FLOAT_EQ(projected.W, 1.0f);
}

TEST(Projection, Perspective)
{
    hmm_mat4 projection = HMM_Perspective(90.0f, 2.0f, 5.0f, 15.0f);

    {
        hmm_vec3 original = HMM_Vec3(5.0f, 5.0f, -15.0f);
        hmm_vec4 projected = projection * HMM_Vec4v(original, 1);
        EXPECT_FLOAT_EQ(projected.X, 5.0f);
        EXPECT_FLOAT_EQ(projected.Y, 10.0f);
        EXPECT_FLOAT_EQ(projected.Z, 15.0f);
        EXPECT_FLOAT_EQ(projected.W, 15.0f);
    }
    {
        hmm_vec3 original = HMM_Vec3(5.0f, 5.0f, -5.0f);
        hmm_vec4 projected = projection * HMM_Vec4v(original, 1);
        EXPECT_FLOAT_EQ(projected.X, 5.0f);
        EXPECT_FLOAT_EQ(projected.Y, 10.0f);
        EXPECT_FLOAT_EQ(projected.Z, -5.0f);
        EXPECT_FLOAT_EQ(projected.W, 5.0f);
    }
}

TEST(Transformations, Translate)
{
    hmm_mat4 translate = HMM_Translate(HMM_Vec3(1.0f, -3.0f, 6.0f));

    hmm_vec3 original = HMM_Vec3(1.0f, 2.0f, 3.0f);
    hmm_vec4 translated = translate * HMM_Vec4v(original, 1);

    EXPECT_FLOAT_EQ(translated.X, 2.0f);
    EXPECT_FLOAT_EQ(translated.Y, -1.0f);
    EXPECT_FLOAT_EQ(translated.Z, 9.0f);
    EXPECT_FLOAT_EQ(translated.W, 1.0f);
}

TEST(Transformations, Rotate)
{
    hmm_vec3 original = HMM_Vec3(1.0f, 1.0f, 1.0f);

    hmm_mat4 rotateX = HMM_Rotate(90, HMM_Vec3(1, 0, 0));
    hmm_vec4 rotatedX = rotateX * HMM_Vec4v(original, 1);
    EXPECT_FLOAT_EQ(rotatedX.X, 1.0f);
    EXPECT_FLOAT_EQ(rotatedX.Y, -1.0f);
    EXPECT_FLOAT_EQ(rotatedX.Z, 1.0f);
    EXPECT_FLOAT_EQ(rotatedX.W, 1.0f);

    hmm_mat4 rotateY = HMM_Rotate(90, HMM_Vec3(0, 1, 0));
    hmm_vec4 rotatedY = rotateY * HMM_Vec4v(original, 1);
    EXPECT_FLOAT_EQ(rotatedY.X, 1.0f);
    EXPECT_FLOAT_EQ(rotatedY.Y, 1.0f);
    EXPECT_FLOAT_EQ(rotatedY.Z, -1.0f);
    EXPECT_FLOAT_EQ(rotatedY.W, 1.0f);

    hmm_mat4 rotateZ = HMM_Rotate(90, HMM_Vec3(0, 0, 1));
    hmm_vec4 rotatedZ = rotateZ * HMM_Vec4v(original, 1);
    EXPECT_FLOAT_EQ(rotatedZ.X, -1.0f);
    EXPECT_FLOAT_EQ(rotatedZ.Y, 1.0f);
    EXPECT_FLOAT_EQ(rotatedZ.Z, 1.0f);
    EXPECT_FLOAT_EQ(rotatedZ.W, 1.0f);
}

TEST(Transformations, Scale)
{
    hmm_mat4 scale = HMM_Scale(HMM_Vec3(2.0f, -3.0f, 0.5f));

    hmm_vec3 original = HMM_Vec3(1.0f, 2.0f, 3.0f);
    hmm_vec4 scaled = scale * HMM_Vec4v(original, 1);

    EXPECT_FLOAT_EQ(scaled.X, 2.0f);
    EXPECT_FLOAT_EQ(scaled.Y, -6.0f);
    EXPECT_FLOAT_EQ(scaled.Z, 1.5f);
    EXPECT_FLOAT_EQ(scaled.W, 1.0f);
}
