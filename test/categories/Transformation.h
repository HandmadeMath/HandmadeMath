#include "../HandmadeTest.h"

TEST(Transformations, Translate)
{
    HMM_Mat4 translate = HMM_Translate(HMM_V3(1.0f, -3.0f, 6.0f));

    HMM_Vec3 original = HMM_V3(1.0f, 2.0f, 3.0f);
    HMM_Vec4 translated = HMM_MulM4V4(translate, HMM_V4V(original, 1));

    EXPECT_NEAR(translated.X, 2.0f, 0.001f);
    EXPECT_NEAR(translated.Y, -1.0f, 0.001f);
    EXPECT_NEAR(translated.Z, 9.0f, 0.001f);
    EXPECT_NEAR(translated.W, 1.0f, 0.001f);
}

TEST(Transformations, Rotate)
{
    HMM_Vec3 original = HMM_V3(1.0f, 1.0f, 1.0f);

    HMM_Mat4 rotateX = HMM_Rotate_RH(HMM_AngleDeg(90.0f), HMM_V3(1, 0, 0));
    HMM_Vec4 rotatedX = HMM_MulM4V4(rotateX, HMM_V4V(original, 1));
    EXPECT_NEAR(rotatedX.X, 1.0f, 0.001f);
    EXPECT_NEAR(rotatedX.Y, -1.0f, 0.001f);
    EXPECT_NEAR(rotatedX.Z, 1.0f, 0.001f);
    EXPECT_NEAR(rotatedX.W, 1.0f, 0.001f);

    HMM_Mat4 rotateY = HMM_Rotate_RH(HMM_AngleDeg(90.0f), HMM_V3(0, 1, 0));
    HMM_Vec4 rotatedY = HMM_MulM4V4(rotateY, HMM_V4V(original, 1));
    EXPECT_NEAR(rotatedY.X, 1.0f, 0.001f);
    EXPECT_NEAR(rotatedY.Y, 1.0f, 0.001f);
    EXPECT_NEAR(rotatedY.Z, -1.0f, 0.001f);
    EXPECT_NEAR(rotatedY.W, 1.0f, 0.001f);

    HMM_Mat4 rotateZ = HMM_Rotate_RH(HMM_AngleDeg(90.0f), HMM_V3(0, 0, 1));
    HMM_Vec4 rotatedZ = HMM_MulM4V4(rotateZ, HMM_V4V(original, 1));
    EXPECT_NEAR(rotatedZ.X, -1.0f, 0.001f);
    EXPECT_NEAR(rotatedZ.Y, 1.0f, 0.001f);
    EXPECT_NEAR(rotatedZ.Z, 1.0f, 0.001f);
    EXPECT_NEAR(rotatedZ.W, 1.0f, 0.001f);

    HMM_Mat4 rotateZLH = HMM_Rotate_LH(HMM_AngleDeg(90.0f), HMM_V3(0, 0, 1));
    HMM_Vec4 rotatedZLH = HMM_MulM4V4(rotateZLH, HMM_V4V(original, 1));
    EXPECT_NEAR(rotatedZLH.X, 1.0f, 0.001f);
    EXPECT_NEAR(rotatedZLH.Y, -1.0f, 0.001f);
    EXPECT_NEAR(rotatedZLH.Z, 1.0f, 0.001f);
    EXPECT_NEAR(rotatedZLH.W, 1.0f, 0.001f);
}

TEST(Transformations, Scale)
{
    HMM_Mat4 scale = HMM_Scale(HMM_V3(2.0f, -3.0f, 0.5f));

    HMM_Vec3 original = HMM_V3(1.0f, 2.0f, 3.0f);
    HMM_Vec4 scaled = HMM_MulM4V4(scale, HMM_V4V(original, 1));

    EXPECT_NEAR(scaled.X, 2.0f, 0.001f);
    EXPECT_NEAR(scaled.Y, -6.0f, 0.001f);
    EXPECT_NEAR(scaled.Z, 1.5f, 0.001f);
    EXPECT_NEAR(scaled.W, 1.0f, 0.001f);
}

TEST(Transformations, LookAt)
{
    const float abs_error = 0.001f;

    {
        HMM_Mat4 result = HMM_LookAt_RH(HMM_V3(1.0f, 0.0f, 0.0f), HMM_V3(0.0f, 2.0f, 1.0f), HMM_V3(2.0f, 1.0f, 1.0f));

        EXPECT_NEAR(result.Elements[0][0], 0.169031f, abs_error);
        EXPECT_NEAR(result.Elements[0][1], 0.897085f, abs_error);
        EXPECT_NEAR(result.Elements[0][2], 0.408248f, abs_error);
        EXPECT_NEAR(result.Elements[0][3], 0.0f, abs_error);
        EXPECT_NEAR(result.Elements[1][0], 0.507093f, abs_error);
        EXPECT_NEAR(result.Elements[1][1], 0.276026f, abs_error);
        EXPECT_NEAR(result.Elements[1][2], -0.816497f, abs_error);
        EXPECT_NEAR(result.Elements[1][3], 0.0f, abs_error);
        EXPECT_NEAR(result.Elements[2][0], -0.845154f, abs_error);
        EXPECT_NEAR(result.Elements[2][1], 0.345033f, abs_error);
        EXPECT_NEAR(result.Elements[2][2], -0.408248f, abs_error);
        EXPECT_NEAR(result.Elements[2][3], 0.0f, abs_error);
        EXPECT_NEAR(result.Elements[3][0], -0.169031f, abs_error);
        EXPECT_NEAR(result.Elements[3][1], -0.897085f, abs_error);
        EXPECT_NEAR(result.Elements[3][2], -0.408248f, abs_error);
        EXPECT_NEAR(result.Elements[3][3], 1.0f, abs_error);
    }
    {    
        HMM_Mat4 result = HMM_LookAt_LH(HMM_V3(1.0f, 0.0f, 0.0f), HMM_V3(0.0f, 2.0f, 1.0f), HMM_V3(2.0f, 1.0f, 1.0f));

        EXPECT_NEAR(result.Elements[0][0], -0.169031f, abs_error);
        EXPECT_NEAR(result.Elements[0][1], 0.897085f, abs_error);
        EXPECT_NEAR(result.Elements[0][2], -0.408248f, abs_error);
        EXPECT_NEAR(result.Elements[0][3], 0.0f, abs_error);
        EXPECT_NEAR(result.Elements[1][0], -0.507093f, abs_error);
        EXPECT_NEAR(result.Elements[1][1], 0.276026f, abs_error);
        EXPECT_NEAR(result.Elements[1][2], 0.816497f, abs_error);
        EXPECT_NEAR(result.Elements[1][3], 0.0f, abs_error);
        EXPECT_NEAR(result.Elements[2][0], 0.845154f, abs_error);
        EXPECT_NEAR(result.Elements[2][1], 0.345033f, abs_error);
        EXPECT_NEAR(result.Elements[2][2], 0.408248f, abs_error);
        EXPECT_NEAR(result.Elements[2][3], 0.0f, abs_error);
        EXPECT_NEAR(result.Elements[3][0], 0.169031f, abs_error);
        EXPECT_NEAR(result.Elements[3][1], -0.897085f, abs_error);
        EXPECT_NEAR(result.Elements[3][2], 0.408248f, abs_error);
        EXPECT_NEAR(result.Elements[3][3], 1.0f, abs_error);
    }
}

TEST(Transformations, RotateV2)
{
    HMM_Vec2 v2 = HMM_V2(1, 2);

    float epsilon = 0.000001f;
    {
        HMM_Vec2 res = HMM_RotateV2(v2, HMM_AngleDeg(90));
        EXPECT_NEAR(res.X, -2.0f, epsilon);
        EXPECT_NEAR(res.Y, 1.0f, epsilon);
    }
    {
        HMM_Vec2 res = HMM_RotateV2(v2, HMM_AngleDeg(180));
        EXPECT_NEAR(res.X, -1.0f, epsilon);
        EXPECT_NEAR(res.Y, -2.0f, epsilon);
    }
    {
        HMM_Vec2 res = HMM_RotateV2(v2, HMM_AngleDeg(270));
        EXPECT_NEAR(res.X, 2.0f, epsilon);
        EXPECT_NEAR(res.Y, -1.0f, epsilon);
    }
    {
        HMM_Vec2 res = HMM_RotateV2(v2, HMM_AngleDeg(360));
        EXPECT_NEAR(res.X, 1.0f, epsilon);
        EXPECT_NEAR(res.Y, 2.0f, epsilon);
    }
}
