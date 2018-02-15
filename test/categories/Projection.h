#include "../HandmadeTest.h"

TEST(Projection, Orthographic)
{
    hmm_mat4 projection = HMM_Orthographic(-10.0f, 10.0f, -5.0f, 5.0f, 0.0f, -10.0f);

    hmm_vec3 original = HMM_Vec3(5.0f, 5.0f, -5.0f);
    hmm_vec4 projected = HMM_MultiplyMat4ByVec4(projection, HMM_Vec4v(original, 1));

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
        hmm_vec4 projected = HMM_MultiplyMat4ByVec4(projection, HMM_Vec4v(original, 1));
        EXPECT_FLOAT_EQ(projected.X, 5.0f);
        EXPECT_FLOAT_EQ(projected.Y, 10.0f);
        EXPECT_FLOAT_EQ(projected.Z, 15.0f);
        EXPECT_FLOAT_EQ(projected.W, 15.0f);
    }
    {
        hmm_vec3 original = HMM_Vec3(5.0f, 5.0f, -5.0f);
        hmm_vec4 projected = HMM_MultiplyMat4ByVec4(projection, HMM_Vec4v(original, 1));
        EXPECT_FLOAT_EQ(projected.X, 5.0f);
        EXPECT_FLOAT_EQ(projected.Y, 10.0f);
        EXPECT_FLOAT_EQ(projected.Z, -5.0f);
        EXPECT_FLOAT_EQ(projected.W, 5.0f);
    }
}
