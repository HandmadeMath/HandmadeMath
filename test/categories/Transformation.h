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

#ifdef HANDMADE_MATH_USE_DEGREES
    float angle = 90.0f;
#else
    float angle = HMM_ToRadians(90.0f);
#endif

    hmm_mat4 rotateX = HMM_Rotate(angle, HMM_Vec3(1, 0, 0));
    hmm_vec4 rotatedX = HMM_MultiplyMat4ByVec4(rotateX, HMM_Vec4v(original, 1));
    EXPECT_FLOAT_EQ(rotatedX.X, 1.0f);
    EXPECT_FLOAT_EQ(rotatedX.Y, -1.0f);
    EXPECT_FLOAT_EQ(rotatedX.Z, 1.0f);
    EXPECT_FLOAT_EQ(rotatedX.W, 1.0f);

    hmm_mat4 rotateY = HMM_Rotate(angle, HMM_Vec3(0, 1, 0));
    hmm_vec4 rotatedY = HMM_MultiplyMat4ByVec4(rotateY, HMM_Vec4v(original, 1));
    EXPECT_FLOAT_EQ(rotatedY.X, 1.0f);
    EXPECT_FLOAT_EQ(rotatedY.Y, 1.0f);
    EXPECT_FLOAT_EQ(rotatedY.Z, -1.0f);
    EXPECT_FLOAT_EQ(rotatedY.W, 1.0f);

    hmm_mat4 rotateZ = HMM_Rotate(angle, HMM_Vec3(0, 0, 1));
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

TEST(Transformations, LookAt)
{
    const float abs_error = 0.0001f;

    hmm_mat4 result = HMM_LookAt(HMM_Vec3(1.0f, 0.0f, 0.0f), HMM_Vec3(0.0f, 2.0f, 1.0f), HMM_Vec3(2.0f, 1.0f, 1.0f));

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
