#include "../HandmadeTest.h"

TEST(Projection, Orthographic)
{
    {
        HMM_Mat4 projection = HMM_Orthographic_N0_RH(-10.0f, 10.0f, -5.0f, 5.0f, 1.0f, 10.0f);
        HMM_Vec4 original = HMM_V4(5.0f, 5.0f, -1.0f, 1.0);
        HMM_Vec4 projected = HMM_MulM4V4(projection, original);

        EXPECT_FLOAT_EQ(projected.X, 0.5f);
        EXPECT_FLOAT_EQ(projected.Y, 1.0f);
        EXPECT_FLOAT_EQ(projected.Z, -1.0f);
        EXPECT_FLOAT_EQ(projected.W, 1.0f);

        /* Z0 */
        projection = HMM_Orthographic_Z0_RH(-10.0f, 10.0f, -5.0f, 5.0f, 1.0f, -10.0f);
        projected = HMM_MulM4V4(projection, original);
        EXPECT_FLOAT_EQ(projected.Z, 0.0f);
    }
    {
        HMM_Mat4 projection = HMM_Orthographic_N0_LH(-10.0f, 10.0f, -5.0f, 5.0f, 1.0f, -10.0f);
        HMM_Vec4 original = HMM_V4(5.0f, 5.0f, 1.0f, 1.0);
        HMM_Vec4 projected = HMM_MulM4V4(projection, original);
        
        EXPECT_FLOAT_EQ(projected.X, 0.5f);
        EXPECT_FLOAT_EQ(projected.Y, 1.0f);
        EXPECT_FLOAT_EQ(projected.Z, -1.0f);
        EXPECT_FLOAT_EQ(projected.W, 1.0f);

        /* Z0 */
        projection = HMM_Orthographic_Z0_LH(-10.0f, 10.0f, -5.0f, 5.0f, 1.0f, -10.0f);
        projected = HMM_MulM4V4(projection, original);
        EXPECT_FLOAT_EQ(projected.Z, 0.0f);
    }
}

TEST(Projection, Perspective)
{
    {
        HMM_Mat4 projection = HMM_Perspective_N0_RH(HMM_AngleDeg(90.0f), 2.0f, 1.0f, 15.0f);
        HMM_Vec4 original = HMM_V4(5.0f, 5.0f, -1.0f, 1.0f);
        HMM_Vec4 projected = HMM_MulM4V4(projection, original);
        EXPECT_FLOAT_EQ(projected.X, 2.5f);
        EXPECT_FLOAT_EQ(projected.Y, 5.0f);
        EXPECT_FLOAT_EQ(projected.Z, -1.0f);
        EXPECT_FLOAT_EQ(projected.W, 1.0f);

        /* Z0 */
        projection = HMM_Perspective_Z0_RH(HMM_AngleDeg(90.0f), 2.0f, 1.0f, 15.0f);
        projected = HMM_MulM4V4(projection, original);
        EXPECT_FLOAT_EQ(projected.Z, 0.0f);
    }
    
    {
        HMM_Mat4 projection = HMM_Perspective_N0_LH(HMM_AngleDeg(90.0f), 2.0f, 1.0f, 15.0f);
        HMM_Vec4 original = HMM_V4(5.0f, 5.0f, 1.0f, 1.0f);
        HMM_Vec4 projected = HMM_MulM4V4(projection, original);
        EXPECT_FLOAT_EQ(projected.X, 2.5f);
        EXPECT_FLOAT_EQ(projected.Y, 5.0f);
        EXPECT_FLOAT_EQ(projected.Z, -1.0f);
        EXPECT_FLOAT_EQ(projected.W, 1.0f);
        
        /* Z0 */
        projection = HMM_Perspective_Z0_LH(HMM_AngleDeg(90.0f), 2.0f, 1.0f, 15.0f);
        projected = HMM_MulM4V4(projection, original);
        EXPECT_FLOAT_EQ(projected.Z, 0.0f);
    }
}
