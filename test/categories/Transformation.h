#include "../HandmadeTest.h"

TEST(Transformations, Translate)
{
    hmm_mat4 translate = HMM_Translate(HMM_Vec3(1.0f, -3.0f, 6.0f));

    hmm_vec3 original = HMM_Vec3(1.0f, 2.0f, 3.0f);
    hmm_vec4 translated = HMM_MultiplyMat4ByVec4(translate, HMM_Vec4v(original, 1));

    EXPECT_FLOAT_EQ(translated.X, 2.0f);
    EXPECT_FLOAT_EQ(translated.Y, -1.0f);
    EXPECT_FLOAT_EQ(translated.Z, 9.0f);
    EXPECT_FLOAT_EQ(translated.W, 1.0f);
}

TEST(Transformations, Rotate)
{
    hmm_vec3 original = HMM_Vec3(1.0f, 1.0f, 1.0f);

    hmm_mat4 rotateX = HMM_Rotate(90, HMM_Vec3(1, 0, 0));
    hmm_vec4 rotatedX = HMM_MultiplyMat4ByVec4(rotateX, HMM_Vec4v(original, 1));
    EXPECT_FLOAT_EQ(rotatedX.X, 1.0f);
    EXPECT_FLOAT_EQ(rotatedX.Y, -1.0f);
    EXPECT_FLOAT_EQ(rotatedX.Z, 1.0f);
    EXPECT_FLOAT_EQ(rotatedX.W, 1.0f);

    hmm_mat4 rotateY = HMM_Rotate(90, HMM_Vec3(0, 1, 0));
    hmm_vec4 rotatedY = HMM_MultiplyMat4ByVec4(rotateY, HMM_Vec4v(original, 1));
    EXPECT_FLOAT_EQ(rotatedY.X, 1.0f);
    EXPECT_FLOAT_EQ(rotatedY.Y, 1.0f);
    EXPECT_FLOAT_EQ(rotatedY.Z, -1.0f);
    EXPECT_FLOAT_EQ(rotatedY.W, 1.0f);

    hmm_mat4 rotateZ = HMM_Rotate(90, HMM_Vec3(0, 0, 1));
    hmm_vec4 rotatedZ = HMM_MultiplyMat4ByVec4(rotateZ, HMM_Vec4v(original, 1));
    EXPECT_FLOAT_EQ(rotatedZ.X, -1.0f);
    EXPECT_FLOAT_EQ(rotatedZ.Y, 1.0f);
    EXPECT_FLOAT_EQ(rotatedZ.Z, 1.0f);
    EXPECT_FLOAT_EQ(rotatedZ.W, 1.0f);
}

TEST(Transformations, Scale)
{
    hmm_mat4 scale = HMM_Scale(HMM_Vec3(2.0f, -3.0f, 0.5f));

    hmm_vec3 original = HMM_Vec3(1.0f, 2.0f, 3.0f);
    hmm_vec4 scaled = HMM_MultiplyMat4ByVec4(scale, HMM_Vec4v(original, 1));

    EXPECT_FLOAT_EQ(scaled.X, 2.0f);
    EXPECT_FLOAT_EQ(scaled.Y, -6.0f);
    EXPECT_FLOAT_EQ(scaled.Z, 1.5f);
    EXPECT_FLOAT_EQ(scaled.W, 1.0f);
}
