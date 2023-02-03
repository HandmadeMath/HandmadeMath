#include "../HandmadeTest.h"

TEST(Projection, Orthographic)
{
#define ORTHO_BOUNDS -8.0f, 12.0f, 5.0f, 10.0f, 1.0f, 100.0f

    // Right-handed
    {
        // Near and far distances correspond to negative Z, hence the Z coordinates here are negative.
        HMM_Vec4 minCorner = HMM_V4(-8.0f, 5.0f, -1.0f, 1.0);
        HMM_Vec4 maxCorner = HMM_V4(12.0f, 10.0f, -100.0f, 1.0);

        // Z from -1 to 1 (GL convention)
        {
            HMM_Mat4 projection = HMM_Orthographic_RH_NO(ORTHO_BOUNDS);
            EXPECT_V4_EQ(HMM_MulM4V4(projection, minCorner), HMM_V4(-1.0f, -1.0f, -1.0f, 1.0f));
            EXPECT_V4_EQ(HMM_MulM4V4(projection, maxCorner), HMM_V4(1.0f, 1.0f, 1.0f, 1.0f));
        }

        // Z from 0 to 1 (DX convention)
        {
            HMM_Mat4 projection = HMM_Orthographic_RH_ZO(ORTHO_BOUNDS);
            EXPECT_V4_EQ(HMM_MulM4V4(projection, minCorner), HMM_V4(-1.0f, -1.0f, 0.0f, 1.0f));
            EXPECT_V4_EQ(HMM_MulM4V4(projection, maxCorner), HMM_V4(1.0f, 1.0f, 1.0f, 1.0f));
        }
    }

    // Left-handed
    {
        // Near and far distances correspond to positive Z, hence the Z coordinates here are positive.
        HMM_Vec4 minCorner = HMM_V4(-8.0f, 5.0f, 1.0f, 1.0);
        HMM_Vec4 maxCorner = HMM_V4(12.0f, 10.0f, 100.0f, 1.0);

        // Z from -1 to 1 (GL convention)
        {
            HMM_Mat4 projection = HMM_Orthographic_LH_NO(ORTHO_BOUNDS);
            EXPECT_V4_EQ(HMM_MulM4V4(projection, minCorner), HMM_V4(-1.0f, -1.0f, -1.0f, 1.0f));
            EXPECT_V4_EQ(HMM_MulM4V4(projection, maxCorner), HMM_V4(1.0f, 1.0f, 1.0f, 1.0f));
        }

        // Z from 0 to 1 (DX convention)
        {
            HMM_Mat4 projection = HMM_Orthographic_LH_ZO(ORTHO_BOUNDS);
            EXPECT_V4_EQ(HMM_MulM4V4(projection, minCorner), HMM_V4(-1.0f, -1.0f, 0.0f, 1.0f));
            EXPECT_V4_EQ(HMM_MulM4V4(projection, maxCorner), HMM_V4(1.0f, 1.0f, 1.0f, 1.0f));
        }
    }
}

TEST(Projection, Perspective)
{
    // Right-handed
    {
        // Z from -1 to 1 (GL convention)
        {
            HMM_Mat4 projection = HMM_Perspective_RH_NO(HMM_AngleDeg(90.0f), 2.0f, 1.0f, 15.0f);
            HMM_Vec4 original = HMM_V4(5.0f, 5.0f, -1.0f, 1.0f);
            EXPECT_V4_EQ(HMM_MulM4V4(projection, original), HMM_V4(2.5f, 5.0f, -1.0f, 1.0f));
        }

        // Z from 0 to 1 (DX convention)
        {
            HMM_Mat4 projection = HMM_Perspective_RH_ZO(HMM_AngleDeg(90.0f), 2.0f, 1.0f, 15.0f);
            HMM_Vec4 original = HMM_V4(5.0f, 5.0f, -1.0f, 1.0f);
            EXPECT_V4_EQ(HMM_MulM4V4(projection, original), HMM_V4(2.5f, 5.0f, 0.0f, 1.0f));
        }
    }

    // Left-handed
    {
        // Z from -1 to 1 (GL convention)
        {
            HMM_Mat4 projection = HMM_Perspective_LH_NO(HMM_AngleDeg(90.0f), 2.0f, 1.0f, 15.0f);
            HMM_Vec4 original = HMM_V4(5.0f, 5.0f, 1.0f, 1.0f);
            EXPECT_V4_EQ(HMM_MulM4V4(projection, original), HMM_V4(2.5f, 5.0f, -1.0f, 1.0f));
        }

        // Z from 0 to 1 (DX convention)
        {
            HMM_Mat4 projection = HMM_Perspective_LH_ZO(HMM_AngleDeg(90.0f), 2.0f, 1.0f, 15.0f);
            HMM_Vec4 original = HMM_V4(5.0f, 5.0f, 1.0f, 1.0f);
            EXPECT_V4_EQ(HMM_MulM4V4(projection, original), HMM_V4(2.5f, 5.0f, 0.0f, 1.0f));
        }
    }
}
