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

TEST(VectorOps, Cross)
{
    {
        // Normal cross
        hmm_vec3 v1 = HMM_Vec3(1.0f, 2.0f, 3.0f);
        hmm_vec3 v2 = HMM_Vec3(4.0f, 5.0f, 6.0f);

        hmm_vec3 result = HMM_Cross(v1, v2);

        EXPECT_FLOAT_EQ(result.X, -3.0f);
        EXPECT_FLOAT_EQ(result.Y, 6.0f);
        EXPECT_FLOAT_EQ(result.Z, -3.0f);
    }

    {
        // Vector with itself
        hmm_vec3 v = HMM_Vec3(1.0f, 2.0f, 3.0f);

        hmm_vec3 result = HMM_Cross(v, v);

        EXPECT_FLOAT_EQ(result.X, 0.0f);
        EXPECT_FLOAT_EQ(result.Y, 0.0f);
        EXPECT_FLOAT_EQ(result.Z, 0.0f);
    }
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
