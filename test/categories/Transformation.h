#include "../HandmadeTest.h"

TEST(Transformations, Translate)
{
    HMM_Mat4 translate = HMM_Translate(HMM_V3(1.0f, -3.0f, 6.0f));

    HMM_Vec3 original = HMM_V3(1.0f, 2.0f, 3.0f);
    HMM_Vec4 translated = HMM_MulM4ByV4(translate, HMM_V4V(original, 1));

    EXPECT_FLOAT_EQ(translated.X, 2.0f);
    EXPECT_FLOAT_EQ(translated.Y, -1.0f);
    EXPECT_FLOAT_EQ(translated.Z, 9.0f);
    EXPECT_FLOAT_EQ(translated.W, 1.0f);
}

TEST(Transformations, Rotate)
{
    HMM_Vec3 original = HMM_V3(1.0f, 1.0f, 1.0f);

    HMM_Mat4 rotateX = HMM_Rotate(HMM_AngleDeg(90.0f), HMM_V3(1, 0, 0));
    HMM_Vec4 rotatedX = HMM_MulM4ByV4(rotateX, HMM_V4V(original, 1));
    EXPECT_FLOAT_EQ(rotatedX.X, 1.0f);
    EXPECT_FLOAT_EQ(rotatedX.Y, -1.0f);
    EXPECT_FLOAT_EQ(rotatedX.Z, 1.0f);
    EXPECT_FLOAT_EQ(rotatedX.W, 1.0f);

    HMM_Mat4 rotateY = HMM_Rotate(HMM_AngleDeg(90.0f), HMM_V3(0, 1, 0));
    HMM_Vec4 rotatedY = HMM_MulM4ByV4(rotateY, HMM_V4V(original, 1));
    EXPECT_FLOAT_EQ(rotatedY.X, 1.0f);
    EXPECT_FLOAT_EQ(rotatedY.Y, 1.0f);
    EXPECT_FLOAT_EQ(rotatedY.Z, -1.0f);
    EXPECT_FLOAT_EQ(rotatedY.W, 1.0f);

    HMM_Mat4 rotateZ = HMM_Rotate(HMM_AngleDeg(90.0f), HMM_V3(0, 0, 1));
    HMM_Vec4 rotatedZ = HMM_MulM4ByV4(rotateZ, HMM_V4V(original, 1));
    EXPECT_FLOAT_EQ(rotatedZ.X, -1.0f);
    EXPECT_FLOAT_EQ(rotatedZ.Y, 1.0f);
    EXPECT_FLOAT_EQ(rotatedZ.Z, 1.0f);
    EXPECT_FLOAT_EQ(rotatedZ.W, 1.0f);
}

TEST(Transformations, Scale)
{
    HMM_Mat4 scale = HMM_Scale(HMM_V3(2.0f, -3.0f, 0.5f));

    HMM_Vec3 original = HMM_V3(1.0f, 2.0f, 3.0f);
    HMM_Vec4 scaled = HMM_MulM4ByV4(scale, HMM_V4V(original, 1));

    EXPECT_FLOAT_EQ(scaled.X, 2.0f);
    EXPECT_FLOAT_EQ(scaled.Y, -6.0f);
    EXPECT_FLOAT_EQ(scaled.Z, 1.5f);
    EXPECT_FLOAT_EQ(scaled.W, 1.0f);
}

TEST(Transformations, LookAt)
{
    const float abs_error = 0.0001f;

    HMM_Mat4 result = HMM_LookAt(HMM_V3(1.0f, 0.0f, 0.0f), HMM_V3(0.0f, 2.0f, 1.0f), HMM_V3(2.0f, 1.0f, 1.0f));

    EXPECT_NEAR(result.Elements[0][0], 0.169031f, abs_error);
    EXPECT_NEAR(result.Elements[0][1], 0.897085f, abs_error);
    EXPECT_NEAR(result.Elements[0][2], 0.408248f, abs_error);
    EXPECT_FLOAT_EQ(result.Elements[0][3], 0.0f);
    EXPECT_NEAR(result.Elements[1][0], 0.507093f, abs_error);
    EXPECT_NEAR(result.Elements[1][1], 0.276026f, abs_error);
    EXPECT_NEAR(result.Elements[1][2], -0.816497f, abs_error);
    EXPECT_FLOAT_EQ(result.Elements[1][3], 0.0f);
    EXPECT_NEAR(result.Elements[2][0], -0.845154f, abs_error);
    EXPECT_NEAR(result.Elements[2][1], 0.345033f, abs_error);
    EXPECT_NEAR(result.Elements[2][2], -0.408248f, abs_error);
    EXPECT_FLOAT_EQ(result.Elements[2][3], 0.0f);
    EXPECT_NEAR(result.Elements[3][0], -0.169031f, abs_error);
    EXPECT_NEAR(result.Elements[3][1], -0.897085f, abs_error);
    EXPECT_NEAR(result.Elements[3][2], -0.408248f, abs_error);
    EXPECT_FLOAT_EQ(result.Elements[3][3], 1.0f);
}
