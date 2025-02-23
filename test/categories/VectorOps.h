#include "../HandmadeTest.h"

TEST(VectorOps, LengthSquared)
{
    HMM_Vec2 v2 = HMM_V2(1.0f, -2.0f);
    HMM_Vec3 v3 = HMM_V3(1.0f, -2.0f, 3.0f);
    HMM_Vec4 v4 = HMM_V4(1.0f, -2.0f, 3.0f, 1.0f);

    EXPECT_FLOAT_EQ(HMM_LenSqrV2(v2), 5.0f);
    EXPECT_FLOAT_EQ(HMM_LenSqrV3(v3), 14.0f);
    EXPECT_FLOAT_EQ(HMM_LenSqrV4(v4), 15.0f);

#if HANDMADE_MATH__USE_C11_GENERICS || defined(__cplusplus)
    EXPECT_FLOAT_EQ(HMM_LenSqr(v2), 5.0f);
    EXPECT_FLOAT_EQ(HMM_LenSqr(v3), 14.0f);
    EXPECT_FLOAT_EQ(HMM_LenSqr(v4), 15.0f);
#endif
}

TEST(VectorOps, Length)
{
    HMM_Vec2 v2 = HMM_V2(1.0f, -9.0f);
    HMM_Vec3 v3 = HMM_V3(2.0f, -3.0f, 6.0f);
    HMM_Vec4 v4 = HMM_V4(2.0f, -3.0f, 6.0f, 12.0f);

    EXPECT_FLOAT_EQ(HMM_LenV2(v2), 9.0553856f);
    EXPECT_FLOAT_EQ(HMM_LenV3(v3), 7.0f);
    EXPECT_FLOAT_EQ(HMM_LenV4(v4), 13.892444f);

#if HANDMADE_MATH__USE_C11_GENERICS || defined(__cplusplus)
    EXPECT_FLOAT_EQ(HMM_Len(v2), 9.0553856f);
    EXPECT_FLOAT_EQ(HMM_Len(v3), 7.0f);
    EXPECT_FLOAT_EQ(HMM_Len(v4), 13.892444f);
#endif
}

TEST(VectorOps, Normalize)
{
    HMM_Vec2 v2 = HMM_V2(1.0f, -2.0f);
    HMM_Vec3 v3 = HMM_V3(1.0f, -2.0f, 3.0f);
    HMM_Vec4 v4 = HMM_V4(1.0f, -2.0f, 3.0f, -1.0f);

    {
        HMM_Vec2 result = HMM_NormV2(v2);
        EXPECT_NEAR(HMM_LenV2(result), 1.0f, 0.001f);
        EXPECT_GT(result.X, 0.0f);
        EXPECT_LT(result.Y, 0.0f);
    }
    {
        HMM_Vec3 result = HMM_NormV3(v3);
        EXPECT_NEAR(HMM_LenV3(result), 1.0f, 0.001f);
        EXPECT_GT(result.X, 0.0f);
        EXPECT_LT(result.Y, 0.0f);
        EXPECT_GT(result.Z, 0.0f);
    }
    {
        HMM_Vec4 result = HMM_NormV4(v4);
        EXPECT_NEAR(HMM_LenV4(result), 1.0f, 0.001f);
        EXPECT_GT(result.X, 0.0f);
        EXPECT_LT(result.Y, 0.0f);
        EXPECT_GT(result.Z, 0.0f);
        EXPECT_LT(result.W, 0.0f);
    }

#if HANDMADE_MATH__USE_C11_GENERICS || defined(__cplusplus)
    {
        HMM_Vec2 result = HMM_Norm(v2);
        EXPECT_NEAR(HMM_LenV2(result), 1.0f, 0.001f);
        EXPECT_GT(result.X, 0.0f);
        EXPECT_LT(result.Y, 0.0f);
    }
    {
        HMM_Vec3 result = HMM_Norm(v3);
        EXPECT_NEAR(HMM_LenV3(result), 1.0f, 0.001f);
        EXPECT_GT(result.X, 0.0f);
        EXPECT_LT(result.Y, 0.0f);
        EXPECT_GT(result.Z, 0.0f);
    }
    {
        HMM_Vec4 result = HMM_Norm(v4);
        EXPECT_NEAR(HMM_LenV4(result), 1.0f, 0.001f);
        EXPECT_GT(result.X, 0.0f);
        EXPECT_LT(result.Y, 0.0f);
        EXPECT_GT(result.Z, 0.0f);
        EXPECT_LT(result.W, 0.0f);
    }
#endif
}

TEST(VectorOps, NormalizeZero)
{
    HMM_Vec2 v2 = HMM_V2(0.0f, 0.0f);
    HMM_Vec3 v3 = HMM_V3(0.0f, 0.0f, 0.0f);
    HMM_Vec4 v4 = HMM_V4(0.0f, 0.0f, 0.0f, 0.0f);

    {
        HMM_Vec2 result = HMM_NormV2(v2);
        EXPECT_FLOAT_EQ(result.X, 0.0f);
        EXPECT_FLOAT_EQ(result.Y, 0.0f);
    }
    {
        HMM_Vec3 result = HMM_NormV3(v3);
        EXPECT_FLOAT_EQ(result.X, 0.0f);
        EXPECT_FLOAT_EQ(result.Y, 0.0f);
        EXPECT_FLOAT_EQ(result.Z, 0.0f);
    }
    {
        HMM_Vec4 result = HMM_NormV4(v4);
        EXPECT_FLOAT_EQ(result.X, 0.0f);
        EXPECT_FLOAT_EQ(result.Y, 0.0f);
        EXPECT_FLOAT_EQ(result.Z, 0.0f);
        EXPECT_FLOAT_EQ(result.W, 0.0f);
    }

#if HANDMADE_MATH__USE_C11_GENERICS || defined(__cplusplus)
    {
        HMM_Vec2 result = HMM_Norm(v2);
        EXPECT_FLOAT_EQ(result.X, 0.0f);
        EXPECT_FLOAT_EQ(result.Y, 0.0f);
    }
    {
        HMM_Vec3 result = HMM_Norm(v3);
        EXPECT_FLOAT_EQ(result.X, 0.0f);
        EXPECT_FLOAT_EQ(result.Y, 0.0f);
        EXPECT_FLOAT_EQ(result.Z, 0.0f);
    }
    {
        HMM_Vec4 result = HMM_Norm(v4);
        EXPECT_FLOAT_EQ(result.X, 0.0f);
        EXPECT_FLOAT_EQ(result.Y, 0.0f);
        EXPECT_FLOAT_EQ(result.Z, 0.0f);
        EXPECT_FLOAT_EQ(result.W, 0.0f);
    }
#endif
}

TEST(VectorOps, Cross)
{
    HMM_Vec3 v1 = HMM_V3(1.0f, 2.0f, 3.0f);
    HMM_Vec3 v2 = HMM_V3(4.0f, 5.0f, 6.0f);

    HMM_Vec3 result = HMM_Cross(v1, v2);

    EXPECT_FLOAT_EQ(result.X, -3.0f);
    EXPECT_FLOAT_EQ(result.Y, 6.0f);
    EXPECT_FLOAT_EQ(result.Z, -3.0f);
}

TEST(VectorOps, DotVec2)
{
    HMM_Vec2 v1 = HMM_V2(1.0f, 2.0f);
    HMM_Vec2 v2 = HMM_V2(3.0f, 4.0f);

    EXPECT_FLOAT_EQ(HMM_DotV2(v1, v2), 11.0f);
#if HANDMADE_MATH__USE_C11_GENERICS || defined(__cplusplus)
    EXPECT_FLOAT_EQ(HMM_Dot(v1, v2), 11.0f);
#endif
}

TEST(VectorOps, DotVec3)
{
    HMM_Vec3 v1 = HMM_V3(1.0f, 2.0f, 3.0f);
    HMM_Vec3 v2 = HMM_V3(4.0f, 5.0f, 6.0f);

    EXPECT_FLOAT_EQ(HMM_DotV3(v1, v2), 32.0f);
#if HANDMADE_MATH__USE_C11_GENERICS || defined(__cplusplus)
    EXPECT_FLOAT_EQ(HMM_Dot(v1, v2), 32.0f);
#endif
}

TEST(VectorOps, DotVec4)
{
    HMM_Vec4 v1 = HMM_V4(1.0f, 2.0f, 3.0f, 4.0f);
    HMM_Vec4 v2 = HMM_V4(5.0f, 6.0f, 7.0f, 8.0f);

    EXPECT_FLOAT_EQ(HMM_DotV4(v1, v2), 70.0f);
#if HANDMADE_MATH__USE_C11_GENERICS || defined(__cplusplus)
    EXPECT_FLOAT_EQ(HMM_Dot(v1, v2), 70.0f);
#endif
}

TEST(VectorOps, LerpV2)
{
    HMM_Vec2 v1 = HMM_V2(1.0f, 0.0f);
    HMM_Vec2 v2 = HMM_V2(0.0f, 1.0f);

    {
        HMM_Vec2 result = HMM_LerpV2(v1, 0.5, v2);
        EXPECT_FLOAT_EQ(result.X, 0.5f);
        EXPECT_FLOAT_EQ(result.Y, 0.5f);
    }
#if HANDMADE_MATH__USE_C11_GENERICS || defined(__cplusplus)
    {
        HMM_Vec2 result = HMM_Lerp(v1, 0.5, v2);
        EXPECT_FLOAT_EQ(result.X, 0.5f);
        EXPECT_FLOAT_EQ(result.Y, 0.5f);
    }
#endif
}

TEST(VectorOps, LerpV3)
{
    HMM_Vec3 v1 = HMM_V3(1.0f, 1.0f, 0.0f);
    HMM_Vec3 v2 = HMM_V3(0.0f, 1.0f, 1.0f);

    {
        HMM_Vec3 result = HMM_LerpV3(v1, 0.5, v2);
        EXPECT_FLOAT_EQ(result.X, 0.5f);
        EXPECT_FLOAT_EQ(result.Y, 1.0f);
        EXPECT_FLOAT_EQ(result.Z, 0.5f);
    }
#if HANDMADE_MATH__USE_C11_GENERICS || defined(__cplusplus)
    {
        HMM_Vec3 result = HMM_Lerp(v1, 0.5, v2);
        EXPECT_FLOAT_EQ(result.X, 0.5f);
        EXPECT_FLOAT_EQ(result.Y, 1.0f);
        EXPECT_FLOAT_EQ(result.Z, 0.5f);
    }
#endif
}

TEST(VectorOps, LerpV4)
{
    HMM_Vec4 v1 = HMM_V4(1.0f, 1.0f, 0.0f, 1.0f);
    HMM_Vec4 v2 = HMM_V4(0.0f, 1.0f, 1.0f, 1.0f);

    {
        HMM_Vec4 result = HMM_LerpV4(v1, 0.5, v2);
        EXPECT_FLOAT_EQ(result.X, 0.5f);
        EXPECT_FLOAT_EQ(result.Y, 1.0f);
        EXPECT_FLOAT_EQ(result.Z, 0.5f);
        EXPECT_FLOAT_EQ(result.W, 1.0f);
    }
#if HANDMADE_MATH__USE_C11_GENERICS || defined(__cplusplus)
    {
        HMM_Vec4 result = HMM_Lerp(v1, 0.5, v2);
        EXPECT_FLOAT_EQ(result.X, 0.5f);
        EXPECT_FLOAT_EQ(result.Y, 1.0f);
        EXPECT_FLOAT_EQ(result.Z, 0.5f);
        EXPECT_FLOAT_EQ(result.W, 1.0f);
    }
#endif
}

/*
 * MatrixOps tests
 */

TEST(MatrixOps, TransposeM4)
{
    HMM_Mat4 m4 = HMM_M4(); // will have 1 - 16

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
    HMM_Mat4 result = HMM_TransposeM4(m4);
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
