#include "../HandmadeTest.h"

TEST(VectorOps, LengthSquared)
{
    hmm_vec2 v2 = HMM_Vec2(1.0f, -2.0f);
    hmm_vec3 v3 = HMM_Vec3(1.0f, -2.0f, 3.0f); 
    hmm_vec4 v4 = HMM_Vec4(1.0f, -2.0f, 3.0f, 1.0f);

    EXPECT_FLOAT_EQ(HMM_LengthSquaredVec2(v2), 5.0f);
    EXPECT_FLOAT_EQ(HMM_LengthSquaredVec3(v3), 14.0f);
    EXPECT_FLOAT_EQ(HMM_LengthSquaredVec4(v4), 15.0f);

#ifdef __cplusplus
    EXPECT_FLOAT_EQ(HMM_LengthSquared(v2), 5.0f);
    EXPECT_FLOAT_EQ(HMM_LengthSquared(v3), 14.0f);
    EXPECT_FLOAT_EQ(HMM_LengthSquared(v4), 15.0f);
#endif
}

TEST(VectorOps, Length)
{
    hmm_vec2 v2 = HMM_Vec2(1.0f, -9.0f);
    hmm_vec3 v3 = HMM_Vec3(2.0f, -3.0f, 6.0f);
    hmm_vec4 v4 = HMM_Vec4(2.0f, -3.0f, 6.0f, 12.0f);

    EXPECT_FLOAT_EQ(HMM_LengthVec2(v2), 9.0553856f);
    EXPECT_FLOAT_EQ(HMM_LengthVec3(v3), 7.0f);
    EXPECT_FLOAT_EQ(HMM_LengthVec4(v4), 13.892444f);

#ifdef __cplusplus
    EXPECT_FLOAT_EQ(HMM_Length(v2), 9.0553856f);
    EXPECT_FLOAT_EQ(HMM_Length(v3), 7.0f);
    EXPECT_FLOAT_EQ(HMM_Length(v4), 13.892444f);
#endif
}

TEST(VectorOps, Normalize)
{
    hmm_vec2 v2 = HMM_Vec2(1.0f, -2.0f);
    hmm_vec3 v3 = HMM_Vec3(1.0f, -2.0f, 3.0f); 
    hmm_vec4 v4 = HMM_Vec4(1.0f, -2.0f, 3.0f, -1.0f);

    {
        hmm_vec2 result = HMM_NormalizeVec2(v2);
        EXPECT_FLOAT_EQ(HMM_LengthVec2(result), 1.0f);
        EXPECT_GT(result.X, 0.0f);
        EXPECT_LT(result.Y, 0.0f);
    }
    {
        hmm_vec3 result = HMM_NormalizeVec3(v3);
        EXPECT_FLOAT_EQ(HMM_LengthVec3(result), 1.0f);
        EXPECT_GT(result.X, 0.0f);
        EXPECT_LT(result.Y, 0.0f);
        EXPECT_GT(result.Z, 0.0f);
    }
    {
        hmm_vec4 result = HMM_NormalizeVec4(v4);
        EXPECT_FLOAT_EQ(HMM_LengthVec4(result), 1.0f);
        EXPECT_GT(result.X, 0.0f);
        EXPECT_LT(result.Y, 0.0f);
        EXPECT_GT(result.Z, 0.0f);
        EXPECT_LT(result.W, 0.0f);
    }

#ifdef __cplusplus
    {
        hmm_vec2 result = HMM_Normalize(v2);
        EXPECT_FLOAT_EQ(HMM_LengthVec2(result), 1.0f);
        EXPECT_GT(result.X, 0.0f);
        EXPECT_LT(result.Y, 0.0f);
    }
    {
        hmm_vec3 result = HMM_Normalize(v3);
        EXPECT_FLOAT_EQ(HMM_LengthVec3(result), 1.0f);
        EXPECT_GT(result.X, 0.0f);
        EXPECT_LT(result.Y, 0.0f);
        EXPECT_GT(result.Z, 0.0f);
    }
    {
        hmm_vec4 result = HMM_Normalize(v4);
        EXPECT_FLOAT_EQ(HMM_LengthVec4(result), 1.0f);
        EXPECT_GT(result.X, 0.0f);
        EXPECT_LT(result.Y, 0.0f);
        EXPECT_GT(result.Z, 0.0f);
        EXPECT_LT(result.W, 0.0f);
    }
#endif
}

TEST(VectorOps, NormalizeZero)
{
    hmm_vec2 v2 = HMM_Vec2(0.0f, 0.0f);
    hmm_vec3 v3 = HMM_Vec3(0.0f, 0.0f, 0.0f);
    hmm_vec4 v4 = HMM_Vec4(0.0f, 0.0f, 0.0f, 0.0f);

    {
        hmm_vec2 result = HMM_NormalizeVec2(v2);
        EXPECT_FLOAT_EQ(result.X, 0.0f);
        EXPECT_FLOAT_EQ(result.Y, 0.0f);
    }
    {
        hmm_vec3 result = HMM_NormalizeVec3(v3);
        EXPECT_FLOAT_EQ(result.X, 0.0f);
        EXPECT_FLOAT_EQ(result.Y, 0.0f);
        EXPECT_FLOAT_EQ(result.Z, 0.0f);
    }
    {
        hmm_vec4 result = HMM_NormalizeVec4(v4);
        EXPECT_FLOAT_EQ(result.X, 0.0f);
        EXPECT_FLOAT_EQ(result.Y, 0.0f);
        EXPECT_FLOAT_EQ(result.Z, 0.0f);
        EXPECT_FLOAT_EQ(result.W, 0.0f);
    }

#ifdef __cplusplus
    {
        hmm_vec2 result = HMM_Normalize(v2);
        EXPECT_FLOAT_EQ(result.X, 0.0f);
        EXPECT_FLOAT_EQ(result.Y, 0.0f);
    }
    {
        hmm_vec3 result = HMM_Normalize(v3);
        EXPECT_FLOAT_EQ(result.X, 0.0f);
        EXPECT_FLOAT_EQ(result.Y, 0.0f);
        EXPECT_FLOAT_EQ(result.Z, 0.0f);
    }
    {
        hmm_vec4 result = HMM_Normalize(v4);
        EXPECT_FLOAT_EQ(result.X, 0.0f);
        EXPECT_FLOAT_EQ(result.Y, 0.0f);
        EXPECT_FLOAT_EQ(result.Z, 0.0f);
        EXPECT_FLOAT_EQ(result.W, 0.0f);
    }
#endif
}

TEST(VectorOps, FastNormalize)
{
    hmm_vec2 v2 = HMM_Vec2(1.0f, -2.0f);
    hmm_vec3 v3 = HMM_Vec3(1.0f, -2.0f, 3.0f);
    hmm_vec4 v4 = HMM_Vec4(1.0f, -2.0f, 3.0f, -1.0f);

    {
        hmm_vec2 result = HMM_FastNormalizeVec2(v2);
        EXPECT_NEAR(HMM_LengthVec2(result), 1.0f, 0.001f);
        EXPECT_GT(result.X, 0.0f);
        EXPECT_LT(result.Y, 0.0f);
    }
    {
        hmm_vec3 result = HMM_FastNormalizeVec3(v3);
        EXPECT_NEAR(HMM_LengthVec3(result), 1.0f, 0.001f);
        EXPECT_GT(result.X, 0.0f);
        EXPECT_LT(result.Y, 0.0f);
        EXPECT_GT(result.Z, 0.0f);
    }
    {
        hmm_vec4 result = HMM_FastNormalizeVec4(v4);
        EXPECT_NEAR(HMM_LengthVec4(result), 1.0f, 0.001f);
        EXPECT_GT(result.X, 0.0f);
        EXPECT_LT(result.Y, 0.0f);
        EXPECT_GT(result.Z, 0.0f);
        EXPECT_LT(result.W, 0.0f);
    }

#ifdef __cplusplus
    {
        hmm_vec2 result = HMM_FastNormalize(v2);
        EXPECT_NEAR(HMM_LengthVec2(result), 1.0f, 0.001f);
        EXPECT_GT(result.X, 0.0f);
        EXPECT_LT(result.Y, 0.0f);
    }
    {
        hmm_vec3 result = HMM_FastNormalize(v3);
        EXPECT_NEAR(HMM_LengthVec3(result), 1.0f, 0.001f);
        EXPECT_GT(result.X, 0.0f);
        EXPECT_LT(result.Y, 0.0f);
        EXPECT_GT(result.Z, 0.0f);
    }
    {
        hmm_vec4 result = HMM_FastNormalize(v4);
        EXPECT_NEAR(HMM_LengthVec4(result), 1.0f, 0.001f);
        EXPECT_GT(result.X, 0.0f);
        EXPECT_LT(result.Y, 0.0f);
        EXPECT_GT(result.Z, 0.0f);
        EXPECT_LT(result.W, 0.0f);
    }
#endif
}

TEST(VectorOps, FastNormalizeZero)
{
    hmm_vec2 v2 = HMM_Vec2(0.0f, 0.0f);
    hmm_vec3 v3 = HMM_Vec3(0.0f, 0.0f, 0.0f);
    hmm_vec4 v4 = HMM_Vec4(0.0f, 0.0f, 0.0f, 0.0f);

    {
        hmm_vec2 result = HMM_FastNormalizeVec2(v2);
        EXPECT_FLOAT_EQ(result.X, 0.0f);
        EXPECT_FLOAT_EQ(result.Y, 0.0f);
    }
    {
        hmm_vec3 result = HMM_FastNormalizeVec3(v3);
        EXPECT_FLOAT_EQ(result.X, 0.0f);
        EXPECT_FLOAT_EQ(result.Y, 0.0f);
        EXPECT_FLOAT_EQ(result.Z, 0.0f);
    }
    {
        hmm_vec4 result = HMM_FastNormalizeVec4(v4);
        EXPECT_FLOAT_EQ(result.X, 0.0f);
        EXPECT_FLOAT_EQ(result.Y, 0.0f);
        EXPECT_FLOAT_EQ(result.Z, 0.0f);
        EXPECT_FLOAT_EQ(result.W, 0.0f);
    }

#ifdef __cplusplus
    {
        hmm_vec2 result = HMM_FastNormalize(v2);
        EXPECT_FLOAT_EQ(result.X, 0.0f);
        EXPECT_FLOAT_EQ(result.Y, 0.0f);
    }
    {
        hmm_vec3 result = HMM_FastNormalize(v3);
        EXPECT_FLOAT_EQ(result.X, 0.0f);
        EXPECT_FLOAT_EQ(result.Y, 0.0f);
        EXPECT_FLOAT_EQ(result.Z, 0.0f);
    }
    {
        hmm_vec4 result = HMM_FastNormalize(v4);
        EXPECT_FLOAT_EQ(result.X, 0.0f);
        EXPECT_FLOAT_EQ(result.Y, 0.0f);
        EXPECT_FLOAT_EQ(result.Z, 0.0f);
        EXPECT_FLOAT_EQ(result.W, 0.0f);
    }
#endif
}

TEST(VectorOps, Cross)
{
    hmm_vec3 v1 = HMM_Vec3(1.0f, 2.0f, 3.0f);
    hmm_vec3 v2 = HMM_Vec3(4.0f, 5.0f, 6.0f);

    hmm_vec3 result = HMM_Cross(v1, v2);

    EXPECT_FLOAT_EQ(result.X, -3.0f);
    EXPECT_FLOAT_EQ(result.Y, 6.0f);
    EXPECT_FLOAT_EQ(result.Z, -3.0f);
}

TEST(VectorOps, DotVec2)
{
    hmm_vec2 v1 = HMM_Vec2(1.0f, 2.0f);
    hmm_vec2 v2 = HMM_Vec2(3.0f, 4.0f);

    EXPECT_FLOAT_EQ(HMM_DotVec2(v1, v2), 11.0f);
#ifdef __cplusplus
    EXPECT_FLOAT_EQ(HMM_Dot(v1, v2), 11.0f);
#endif
}

TEST(VectorOps, DotVec3)
{
    hmm_vec3 v1 = HMM_Vec3(1.0f, 2.0f, 3.0f);
    hmm_vec3 v2 = HMM_Vec3(4.0f, 5.0f, 6.0f);

    EXPECT_FLOAT_EQ(HMM_DotVec3(v1, v2), 32.0f);
#ifdef __cplusplus
    EXPECT_FLOAT_EQ(HMM_Dot(v1, v2), 32.0f);
#endif
}

TEST(VectorOps, DotVec4)
{
    hmm_vec4 v1 = HMM_Vec4(1.0f, 2.0f, 3.0f, 4.0f);
    hmm_vec4 v2 = HMM_Vec4(5.0f, 6.0f, 7.0f, 8.0f);

    EXPECT_FLOAT_EQ(HMM_DotVec4(v1, v2), 70.0f);
#ifdef __cplusplus
    EXPECT_FLOAT_EQ(HMM_Dot(v1, v2), 70.0f);
#endif
}


/*
 * MatrixOps tests
 */

TEST(MatrixOps, Transpose)
{
    hmm_mat4 m4 = HMM_Mat4(); // will have 1 - 16

    // Fill the matrix
    int Counter = 1;
    for (int Column = 0; Column < 4; ++Column)
    {
        for (int Row = 0; Row < 4; ++Row)
        {
            m4.Elements[Column][Row] = Counter;
            ++Counter;
        }
    }

    // Test the matrix
    hmm_mat4 result = HMM_Transpose(m4);
    EXPECT_FLOAT_EQ(result.Elements[0][0], 1.0f);
    EXPECT_FLOAT_EQ(result.Elements[0][1], 5.0f);
    EXPECT_FLOAT_EQ(result.Elements[0][2], 9.0f);
    EXPECT_FLOAT_EQ(result.Elements[0][3], 13.0f);
    EXPECT_FLOAT_EQ(result.Elements[1][0], 2.0f);
    EXPECT_FLOAT_EQ(result.Elements[1][1], 6.0f);
    EXPECT_FLOAT_EQ(result.Elements[1][2], 10.0f);
    EXPECT_FLOAT_EQ(result.Elements[1][3], 14.0f);
    EXPECT_FLOAT_EQ(result.Elements[2][0], 3.0f);
    EXPECT_FLOAT_EQ(result.Elements[2][1], 7.0f);
    EXPECT_FLOAT_EQ(result.Elements[2][2], 11.0f);
    EXPECT_FLOAT_EQ(result.Elements[2][3], 15.0f);
    EXPECT_FLOAT_EQ(result.Elements[3][0], 4.0f);
    EXPECT_FLOAT_EQ(result.Elements[3][1], 8.0f);
    EXPECT_FLOAT_EQ(result.Elements[3][2], 12.0f);
    EXPECT_FLOAT_EQ(result.Elements[3][3], 16.0f);
}
