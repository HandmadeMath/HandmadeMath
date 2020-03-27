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

    EXPECT_NEAR(HMM_ATanF(0.0f), 0.0f, trigAbsError);
    EXPECT_NEAR(HMM_ATanF(HMM_PI32), 1.2626272557f, trigAbsError);
    EXPECT_NEAR(HMM_ATanF(-HMM_PI32), -1.2626272557f, trigAbsError);

    EXPECT_NEAR(HMM_ATan2F(0.0f, 1.0f), 0.0f, trigAbsError);
    EXPECT_NEAR(HMM_ATan2F(1.0f, 1.0f), HMM_PI32 / 4.0f, trigAbsError);
    EXPECT_NEAR(HMM_ATan2F(1.0f, 0.0f), HMM_PI32 / 2.0f, trigAbsError);

    // This isn't the most rigorous because we're really just sanity-
    // checking that things work by default.
}

TEST(ScalarMath, ToRadians)
{
    EXPECT_FLOAT_EQ(HMM_ToRadians(0.0f), 0.0f);
    EXPECT_FLOAT_EQ(HMM_ToRadians(180.0f), HMM_PI32);
    EXPECT_FLOAT_EQ(HMM_ToRadians(-180.0f), -HMM_PI32);
}

TEST(ScalarMath, ExpF)
{
    EXPECT_NEAR(HMM_ExpF(0.0f), 1.0f, 0.0001f);
    EXPECT_NEAR(HMM_ExpF(1.0f), 2.7182818285f, 0.0001f);
}

TEST(ScalarMath, LogF)
{
    EXPECT_NEAR(HMM_LogF(1.0f), 0.0f, 0.0001f);
    EXPECT_NEAR(HMM_LogF(2.7182818285f), 1.0f, 0.0001f);
}

TEST(ScalarMath, SquareRoot)
{
    EXPECT_FLOAT_EQ(HMM_SquareRootF(16.0f), 4.0f);
}

TEST(ScalarMath, RSquareRootF)
{
    EXPECT_NEAR(HMM_RSquareRootF(10.0f), 0.31616211f, 0.0001f);
}

TEST(ScalarMath, Power)
{
    EXPECT_FLOAT_EQ(HMM_Power(2.0f, 0), 1.0f);
    EXPECT_FLOAT_EQ(HMM_Power(2.0f, 4), 16.0f);
    EXPECT_FLOAT_EQ(HMM_Power(2.0f, -2), 0.25f);
}

TEST(ScalarMath, PowerF)
{
    EXPECT_FLOAT_EQ(HMM_PowerF(2.0f, 0.0f), 1.0f);
    EXPECT_NEAR(HMM_PowerF(2.0f, 4.1f), 17.148376f, 0.0001f);
    EXPECT_NEAR(HMM_PowerF(2.0f, -2.5f), 0.176777f, 0.0001f);
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
