#include "../HandmadeTest.h"

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

TEST(ScalarMath, SquareRoot)
{
    EXPECT_FLOAT_EQ(HMM_SqrtF(16.0f), 4.0f);
}

TEST(ScalarMath, RSquareRootF)
{
    EXPECT_NEAR(HMM_InvSqrtF(10.0f), 0.31616211f, 0.0001f);
}

TEST(ScalarMath, Lerp)
{
    EXPECT_FLOAT_EQ(HMM_Lerp(-2.0f, 0.0f, 2.0f), -2.0f);
    EXPECT_FLOAT_EQ(HMM_Lerp(-2.0f, 0.5f, 2.0f), 0.0f);
    EXPECT_FLOAT_EQ(HMM_Lerp(-2.0f, 1.0f, 2.0f), 2.0f);
}

TEST(ScalarMath, Clamp)
{
    EXPECT_FLOAT_EQ(HMM_Clamp(-2.0f, 0.0f, 2.0f), 0.0f);
    EXPECT_FLOAT_EQ(HMM_Clamp(-2.0f, -3.0f, 2.0f), -2.0f);
    EXPECT_FLOAT_EQ(HMM_Clamp(-2.0f, 3.0f, 2.0f), 2.0f);
}
