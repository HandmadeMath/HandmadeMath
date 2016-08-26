
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
