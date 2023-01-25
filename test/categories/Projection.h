#include "../HandmadeTest.h"

TEST(Projection, Orthographic)
{
    {
        HMM_Mat4 projection = HMM_Orthographic_RH(-10.0f, 10.0f, -5.0f, 5.0f, 0.0f, -10.0f);

        HMM_Vec3 original = HMM_V3(5.0f, 5.0f, -5.0f);
        HMM_Vec4 projected = HMM_MulM4V4(projection, HMM_V4V(original, 1));

        EXPECT_FLOAT_EQ(projected.X, 0.5f);
        EXPECT_FLOAT_EQ(projected.Y, 1.0f);
        EXPECT_FLOAT_EQ(projected.Z, -2.0f);
        EXPECT_FLOAT_EQ(projected.W, 1.0f);
    }
    {
        HMM_Mat4 projection = HMM_Orthographic_LH(-10.0f, 10.0f, -5.0f, 5.0f, 0.0f, 10.0f);

        HMM_Vec3 original = HMM_V3(5.0f, 5.0f, -5.0f);
        HMM_Vec4 projected = HMM_MulM4V4(projection, HMM_V4V(original, 1));

        EXPECT_FLOAT_EQ(projected.X, 0.5f);
        EXPECT_FLOAT_EQ(projected.Y, 1.0f);
        EXPECT_FLOAT_EQ(projected.Z, -2.0f);
        EXPECT_FLOAT_EQ(projected.W, 1.0f);
    }
}

TEST(Projection, Perspective)
{
    {
        HMM_Mat4 projection = HMM_Perspective_RH(HMM_AngleDeg(90.0f), 2.0f, 5.0f, 15.0f);
        HMM_Vec3 original = HMM_V3(5.0f, 5.0f, -15.0f);
        HMM_Vec4 projected = HMM_MulM4V4(projection, HMM_V4V(original, 1));
        EXPECT_FLOAT_EQ(projected.X, 2.5f);
        EXPECT_FLOAT_EQ(projected.Y, 5.0f);
        EXPECT_FLOAT_EQ(projected.Z, 15.0f);
        EXPECT_FLOAT_EQ(projected.W, 15.0f);
    }
    {
        HMM_Mat4 projection = HMM_Perspective_LH(HMM_AngleDeg(90.0f), 2.0f, 5.0f, 15.0f);
        HMM_Vec3 original = HMM_V3(5.0f, 5.0f, 15.0f);
        HMM_Vec4 projected = HMM_MulM4V4(projection, HMM_V4V(original, 1));
        EXPECT_FLOAT_EQ(projected.X, 2.5f);
        EXPECT_FLOAT_EQ(projected.Y, 5.0f);
        EXPECT_FLOAT_EQ(projected.Z, 15.0f);
        EXPECT_FLOAT_EQ(projected.W, 15.0f);
    }
}
