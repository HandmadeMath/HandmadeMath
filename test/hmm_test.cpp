
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

    EXPECT_FLOAT_EQ(v2.Elements[0], 1.0f);
    EXPECT_FLOAT_EQ(v2.Elements[1], 2.0f);

    EXPECT_FLOAT_EQ(v2i.Elements[0], 1.0f);
    EXPECT_FLOAT_EQ(v2i.Elements[1], 2.0f);

    //
    // Test vec3
    //
    hmm_vec3 v3 = HMM_Vec3(1.0f, 2.0f, 3.0f);
    hmm_vec3 v3i = HMM_Vec3i(1, 2, 3);

    EXPECT_FLOAT_EQ(v3.Elements[0], 1.0f);
    EXPECT_FLOAT_EQ(v3.Elements[1], 2.0f);
    EXPECT_FLOAT_EQ(v3.Elements[2], 3.0f);

    EXPECT_FLOAT_EQ(v3i.Elements[0], 1.0f);
    EXPECT_FLOAT_EQ(v3i.Elements[1], 2.0f);
    EXPECT_FLOAT_EQ(v3i.Elements[2], 3.0f);

    //
    // Test vec4
    //
    hmm_vec4 v4 = HMM_Vec4(1.0f, 2.0f, 3.0f, 4.0f);
    hmm_vec4 v4i = HMM_Vec4i(1, 2, 3, 4);
    hmm_vec4 v4v = HMM_Vec4v(v3, 4.0f);

    EXPECT_FLOAT_EQ(v4.Elements[0], 1.0f);
    EXPECT_FLOAT_EQ(v4.Elements[1], 2.0f);
    EXPECT_FLOAT_EQ(v4.Elements[2], 3.0f);
    EXPECT_FLOAT_EQ(v4.Elements[3], 4.0f);

    EXPECT_FLOAT_EQ(v4i.Elements[0], 1.0f);
    EXPECT_FLOAT_EQ(v4i.Elements[1], 2.0f);
    EXPECT_FLOAT_EQ(v4i.Elements[2], 3.0f);
    EXPECT_FLOAT_EQ(v4i.Elements[3], 4.0f);

    EXPECT_FLOAT_EQ(v4v.Elements[0], 1.0f);
    EXPECT_FLOAT_EQ(v4v.Elements[1], 2.0f);
    EXPECT_FLOAT_EQ(v4v.Elements[2], 3.0f);
    EXPECT_FLOAT_EQ(v4v.Elements[3], 4.0f);
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
