#include "../HandmadeTest.h"

TEST(Division, Vec2Vec2)
{
    HMM_Vec2 v2_1 = HMM_V2(1.0f, 3.0f);
    HMM_Vec2 v2_2 = HMM_V2(2.0f, 4.0f);

    {
        HMM_Vec2 result = HMM_DivV2(v2_1, v2_2);
        EXPECT_FLOAT_EQ(result.X, 0.5f);
        EXPECT_FLOAT_EQ(result.Y, 0.75f);
    }
#ifdef __cplusplus
    {
        HMM_Vec2 result = HMM_Div(v2_1, v2_2);
        EXPECT_FLOAT_EQ(result.X, 0.5f);
        EXPECT_FLOAT_EQ(result.Y, 0.75f);
    }
    {
        HMM_Vec2 result = v2_1 / v2_2;
        EXPECT_FLOAT_EQ(result.X, 0.5f);
        EXPECT_FLOAT_EQ(result.Y, 0.75f);
    }

    v2_1 /= v2_2;
    EXPECT_FLOAT_EQ(v2_1.X, 0.5f);
    EXPECT_FLOAT_EQ(v2_1.Y, 0.75f);
#endif
}

TEST(Division, Vec2Scalar)
{
    HMM_Vec2 v2 = HMM_V2(1.0f, 2.0f);
    float s = 2;

    {
        HMM_Vec2 result = HMM_DivV2F(v2, s);
        EXPECT_FLOAT_EQ(result.X, 0.5f);
        EXPECT_FLOAT_EQ(result.Y, 1.0f);
    }
#ifdef __cplusplus
    {
        HMM_Vec2 result = HMM_Div(v2, s);
        EXPECT_FLOAT_EQ(result.X, 0.5f);
        EXPECT_FLOAT_EQ(result.Y, 1.0f);
    }
    {
        HMM_Vec2 result = v2 / s;
        EXPECT_FLOAT_EQ(result.X, 0.5f);
        EXPECT_FLOAT_EQ(result.Y, 1.0f);
    }

    v2 /= s;
    EXPECT_FLOAT_EQ(v2.X, 0.5f);
    EXPECT_FLOAT_EQ(v2.Y, 1.0f);
#endif
}

TEST(Division, Vec3Vec3)
{
    HMM_Vec3 v3_1 = HMM_V3(1.0f, 3.0f, 5.0f);
    HMM_Vec3 v3_2 = HMM_V3(2.0f, 4.0f, 0.5f);

    {
        HMM_Vec3 result = HMM_DivV3(v3_1, v3_2);
        EXPECT_FLOAT_EQ(result.X, 0.5f);
        EXPECT_FLOAT_EQ(result.Y, 0.75f);
        EXPECT_FLOAT_EQ(result.Z, 10.0f);
    }
#ifdef __cplusplus
    {
        HMM_Vec3 result = HMM_Div(v3_1, v3_2);
        EXPECT_FLOAT_EQ(result.X, 0.5f);
        EXPECT_FLOAT_EQ(result.Y, 0.75f);
        EXPECT_FLOAT_EQ(result.Z, 10.0f);
    }
    {
        HMM_Vec3 result = v3_1 / v3_2;
        EXPECT_FLOAT_EQ(result.X, 0.5f);
        EXPECT_FLOAT_EQ(result.Y, 0.75f);
        EXPECT_FLOAT_EQ(result.Z, 10.0f);
    }

    v3_1 /= v3_2;
    EXPECT_FLOAT_EQ(v3_1.X, 0.5f);
    EXPECT_FLOAT_EQ(v3_1.Y, 0.75f);
    EXPECT_FLOAT_EQ(v3_1.Z, 10.0f);
#endif
}

TEST(Division, Vec3Scalar)
{
    HMM_Vec3 v3 = HMM_V3(1.0f, 2.0f, 3.0f);
    float s = 2;

    {
        HMM_Vec3 result = HMM_DivV3F(v3, s);
        EXPECT_FLOAT_EQ(result.X, 0.5f);
        EXPECT_FLOAT_EQ(result.Y, 1.0f);
        EXPECT_FLOAT_EQ(result.Z, 1.5f);
    }
#ifdef __cplusplus
    {
        HMM_Vec3 result = HMM_Div(v3, s);
        EXPECT_FLOAT_EQ(result.X, 0.5f);
        EXPECT_FLOAT_EQ(result.Y, 1.0f);
        EXPECT_FLOAT_EQ(result.Z, 1.5f);
    }
    {
        HMM_Vec3 result = v3 / s;
        EXPECT_FLOAT_EQ(result.X, 0.5f);
        EXPECT_FLOAT_EQ(result.Y, 1.0f);
        EXPECT_FLOAT_EQ(result.Z, 1.5f);
    }

    v3 /= s;
    EXPECT_FLOAT_EQ(v3.X, 0.5f);
    EXPECT_FLOAT_EQ(v3.Y, 1.0f);
    EXPECT_FLOAT_EQ(v3.Z, 1.5f);
#endif
}

TEST(Division, Vec4Vec4)
{
    HMM_Vec4 v4_1 = HMM_V4(1.0f, 3.0f, 5.0f, 1.0f);
    HMM_Vec4 v4_2 = HMM_V4(2.0f, 4.0f, 0.5f, 4.0f);

    {
        HMM_Vec4 result = HMM_DivV4(v4_1, v4_2);
        EXPECT_FLOAT_EQ(result.X, 0.5f);
        EXPECT_FLOAT_EQ(result.Y, 0.75f);
        EXPECT_FLOAT_EQ(result.Z, 10.0f);
        EXPECT_FLOAT_EQ(result.W, 0.25f);
    }
#ifdef __cplusplus
    {
        HMM_Vec4 result = HMM_Div(v4_1, v4_2);
        EXPECT_FLOAT_EQ(result.X, 0.5f);
        EXPECT_FLOAT_EQ(result.Y, 0.75f);
        EXPECT_FLOAT_EQ(result.Z, 10.0f);
        EXPECT_FLOAT_EQ(result.W, 0.25f);
    }
    {
        HMM_Vec4 result = v4_1 / v4_2;
        EXPECT_FLOAT_EQ(result.X, 0.5f);
        EXPECT_FLOAT_EQ(result.Y, 0.75f);
        EXPECT_FLOAT_EQ(result.Z, 10.0f);
        EXPECT_FLOAT_EQ(result.W, 0.25f);
    }

    v4_1 /= v4_2;
    EXPECT_FLOAT_EQ(v4_1.X, 0.5f);
    EXPECT_FLOAT_EQ(v4_1.Y, 0.75f);
    EXPECT_FLOAT_EQ(v4_1.Z, 10.0f);
    EXPECT_FLOAT_EQ(v4_1.W, 0.25f);
#endif
}

TEST(Division, Vec4Scalar)
{
    HMM_Vec4 v4 = HMM_V4(1.0f, 2.0f, 3.0f, 4.0f);
    float s = 2;

    {
        HMM_Vec4 result = HMM_DivV4F(v4, s);
        EXPECT_FLOAT_EQ(result.X, 0.5f);
        EXPECT_FLOAT_EQ(result.Y, 1.0f);
        EXPECT_FLOAT_EQ(result.Z, 1.5f);
        EXPECT_FLOAT_EQ(result.W, 2.0f);
    }
#ifdef __cplusplus
    {
        HMM_Vec4 result = HMM_Div(v4, s);
        EXPECT_FLOAT_EQ(result.X, 0.5f);
        EXPECT_FLOAT_EQ(result.Y, 1.0f);
        EXPECT_FLOAT_EQ(result.Z, 1.5f);
        EXPECT_FLOAT_EQ(result.W, 2.0f);
    }
    {
        HMM_Vec4 result = v4 / s;
        EXPECT_FLOAT_EQ(result.X, 0.5f);
        EXPECT_FLOAT_EQ(result.Y, 1.0f);
        EXPECT_FLOAT_EQ(result.Z, 1.5f);
        EXPECT_FLOAT_EQ(result.W, 2.0f);
    }

    v4 /= s;
    EXPECT_FLOAT_EQ(v4.X, 0.5f);
    EXPECT_FLOAT_EQ(v4.Y, 1.0f);
    EXPECT_FLOAT_EQ(v4.Z, 1.5f);
    EXPECT_FLOAT_EQ(v4.W, 2.0f);
#endif
}

TEST(Division, Mat4Scalar)
{
    HMM_Mat4 m4 = HMM_M4(); // will have 1 - 16
    float s = 2;

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

    // Test the results
    {
        HMM_Mat4 result = HMM_DivM4f(m4, s);
        EXPECT_FLOAT_EQ(result.Elements[0][0], 0.5f);
        EXPECT_FLOAT_EQ(result.Elements[0][1], 1.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][2], 1.5f);
        EXPECT_FLOAT_EQ(result.Elements[0][3], 2.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][0], 2.5f);
        EXPECT_FLOAT_EQ(result.Elements[1][1], 3.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][2], 3.5f);
        EXPECT_FLOAT_EQ(result.Elements[1][3], 4.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][0], 4.5f);
        EXPECT_FLOAT_EQ(result.Elements[2][1], 5.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][2], 5.5f);
        EXPECT_FLOAT_EQ(result.Elements[2][3], 6.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][0], 6.5f);
        EXPECT_FLOAT_EQ(result.Elements[3][1], 7.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][2], 7.5f);
        EXPECT_FLOAT_EQ(result.Elements[3][3], 8.0f);
    }
#ifdef __cplusplus
    {
        HMM_Mat4 result = HMM_Div(m4, s);
        EXPECT_FLOAT_EQ(result.Elements[0][0], 0.5f);
        EXPECT_FLOAT_EQ(result.Elements[0][1], 1.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][2], 1.5f);
        EXPECT_FLOAT_EQ(result.Elements[0][3], 2.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][0], 2.5f);
        EXPECT_FLOAT_EQ(result.Elements[1][1], 3.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][2], 3.5f);
        EXPECT_FLOAT_EQ(result.Elements[1][3], 4.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][0], 4.5f);
        EXPECT_FLOAT_EQ(result.Elements[2][1], 5.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][2], 5.5f);
        EXPECT_FLOAT_EQ(result.Elements[2][3], 6.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][0], 6.5f);
        EXPECT_FLOAT_EQ(result.Elements[3][1], 7.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][2], 7.5f);
        EXPECT_FLOAT_EQ(result.Elements[3][3], 8.0f);
    }
    {
        HMM_Mat4 result = m4 / s;
        EXPECT_FLOAT_EQ(result.Elements[0][0], 0.5f);
        EXPECT_FLOAT_EQ(result.Elements[0][1], 1.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][2], 1.5f);
        EXPECT_FLOAT_EQ(result.Elements[0][3], 2.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][0], 2.5f);
        EXPECT_FLOAT_EQ(result.Elements[1][1], 3.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][2], 3.5f);
        EXPECT_FLOAT_EQ(result.Elements[1][3], 4.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][0], 4.5f);
        EXPECT_FLOAT_EQ(result.Elements[2][1], 5.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][2], 5.5f);
        EXPECT_FLOAT_EQ(result.Elements[2][3], 6.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][0], 6.5f);
        EXPECT_FLOAT_EQ(result.Elements[3][1], 7.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][2], 7.5f);
        EXPECT_FLOAT_EQ(result.Elements[3][3], 8.0f);
    }

    m4 /= s;
    EXPECT_FLOAT_EQ(m4.Elements[0][0], 0.5f);
    EXPECT_FLOAT_EQ(m4.Elements[0][1], 1.0f);
    EXPECT_FLOAT_EQ(m4.Elements[0][2], 1.5f);
    EXPECT_FLOAT_EQ(m4.Elements[0][3], 2.0f);
    EXPECT_FLOAT_EQ(m4.Elements[1][0], 2.5f);
    EXPECT_FLOAT_EQ(m4.Elements[1][1], 3.0f);
    EXPECT_FLOAT_EQ(m4.Elements[1][2], 3.5f);
    EXPECT_FLOAT_EQ(m4.Elements[1][3], 4.0f);
    EXPECT_FLOAT_EQ(m4.Elements[2][0], 4.5f);
    EXPECT_FLOAT_EQ(m4.Elements[2][1], 5.0f);
    EXPECT_FLOAT_EQ(m4.Elements[2][2], 5.5f);
    EXPECT_FLOAT_EQ(m4.Elements[2][3], 6.0f);
    EXPECT_FLOAT_EQ(m4.Elements[3][0], 6.5f);
    EXPECT_FLOAT_EQ(m4.Elements[3][1], 7.0f);
    EXPECT_FLOAT_EQ(m4.Elements[3][2], 7.5f);
    EXPECT_FLOAT_EQ(m4.Elements[3][3], 8.0f);
#endif
}

TEST(Division, QuaternionScalar)
{
    HMM_Quat q = HMM_Q(1.0f, 2.0f, 3.0f, 4.0f);
    float f = 2.0f;

    {
        HMM_Quat result = HMM_DivQF(q, f);
        EXPECT_FLOAT_EQ(result.X, 0.5f);
        EXPECT_FLOAT_EQ(result.Y, 1.0f);
        EXPECT_FLOAT_EQ(result.Z, 1.5f);
        EXPECT_FLOAT_EQ(result.W, 2.0f);
    }
#ifdef __cplusplus
    {
        HMM_Quat result = HMM_Div(q, f);
        EXPECT_FLOAT_EQ(result.X, 0.5f);
        EXPECT_FLOAT_EQ(result.Y, 1.0f);
        EXPECT_FLOAT_EQ(result.Z, 1.5f);
        EXPECT_FLOAT_EQ(result.W, 2.0f);
    }
    {
        HMM_Quat result = q / f;
        EXPECT_FLOAT_EQ(result.X, 0.5f);
        EXPECT_FLOAT_EQ(result.Y, 1.0f);
        EXPECT_FLOAT_EQ(result.Z, 1.5f);
        EXPECT_FLOAT_EQ(result.W, 2.0f);
    }

    q /= f;
    EXPECT_FLOAT_EQ(q.X, 0.5f);
    EXPECT_FLOAT_EQ(q.Y, 1.0f);
    EXPECT_FLOAT_EQ(q.Z, 1.5f);
    EXPECT_FLOAT_EQ(q.W, 2.0f);
#endif
}
