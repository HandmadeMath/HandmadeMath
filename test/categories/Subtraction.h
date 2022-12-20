#include "../HandmadeTest.h"

TEST(Subtraction, Vec2)
{
    HMM_Vec2 v2_1 = HMM_V2(1.0f, 2.0f);
    HMM_Vec2 v2_2 = HMM_V2(3.0f, 4.0f);

    {
        HMM_Vec2 result = HMM_SubV2(v2_1, v2_2);
        EXPECT_FLOAT_EQ(result.X, -2.0f);
        EXPECT_FLOAT_EQ(result.Y, -2.0f);
    }
#ifdef __cplusplus
    {
        HMM_Vec2 result = HMM_Sub(v2_1, v2_2);
        EXPECT_FLOAT_EQ(result.X, -2.0f);
        EXPECT_FLOAT_EQ(result.Y, -2.0f);
    }
    {
        HMM_Vec2 result = v2_1 - v2_2;
        EXPECT_FLOAT_EQ(result.X, -2.0f);
        EXPECT_FLOAT_EQ(result.Y, -2.0f);
    }

    v2_1 -= v2_2;
    EXPECT_FLOAT_EQ(v2_1.X, -2.0f);
    EXPECT_FLOAT_EQ(v2_1.Y, -2.0f);
#endif
}

TEST(Subtraction, Vec3)
{
    HMM_Vec3 v3_1 = HMM_V3(1.0f, 2.0f, 3.0f);
    HMM_Vec3 v3_2 = HMM_V3(4.0f, 5.0f, 6.0f);

    {
        HMM_Vec3 result = HMM_SubV3(v3_1, v3_2);
        EXPECT_FLOAT_EQ(result.X, -3.0f);
        EXPECT_FLOAT_EQ(result.Y, -3.0f);
        EXPECT_FLOAT_EQ(result.Z, -3.0f);
    }
#ifdef __cplusplus
    {
        HMM_Vec3 result = HMM_Sub(v3_1, v3_2);
        EXPECT_FLOAT_EQ(result.X, -3.0f);
        EXPECT_FLOAT_EQ(result.Y, -3.0f);
        EXPECT_FLOAT_EQ(result.Z, -3.0f);
    }
    {
        HMM_Vec3 result = v3_1 - v3_2;
        EXPECT_FLOAT_EQ(result.X, -3.0f);
        EXPECT_FLOAT_EQ(result.Y, -3.0f);
        EXPECT_FLOAT_EQ(result.Z, -3.0f);
    }

    v3_1 -= v3_2;
    EXPECT_FLOAT_EQ(v3_1.X, -3.0f);
    EXPECT_FLOAT_EQ(v3_1.Y, -3.0f);
    EXPECT_FLOAT_EQ(v3_1.Z, -3.0f);
#endif
}

TEST(Subtraction, Vec4)
{
    HMM_Vec4 v4_1 = HMM_V4(1.0f, 2.0f, 3.0f, 4.0f);
    HMM_Vec4 v4_2 = HMM_V4(5.0f, 6.0f, 7.0f, 8.0f);

    {
        HMM_Vec4 result = HMM_SubV4(v4_1, v4_2);
        EXPECT_FLOAT_EQ(result.X, -4.0f);
        EXPECT_FLOAT_EQ(result.Y, -4.0f);
        EXPECT_FLOAT_EQ(result.Z, -4.0f);
        EXPECT_FLOAT_EQ(result.W, -4.0f);
    }
#ifdef __cplusplus
    {
        HMM_Vec4 result = HMM_Sub(v4_1, v4_2);
        EXPECT_FLOAT_EQ(result.X, -4.0f);
        EXPECT_FLOAT_EQ(result.Y, -4.0f);
        EXPECT_FLOAT_EQ(result.Z, -4.0f);
        EXPECT_FLOAT_EQ(result.W, -4.0f);
    }
    {
        HMM_Vec4 result = v4_1 - v4_2;
        EXPECT_FLOAT_EQ(result.X, -4.0f);
        EXPECT_FLOAT_EQ(result.Y, -4.0f);
        EXPECT_FLOAT_EQ(result.Z, -4.0f);
        EXPECT_FLOAT_EQ(result.W, -4.0f);
    }

    v4_1 -= v4_2;
    EXPECT_FLOAT_EQ(v4_1.X, -4.0f);
    EXPECT_FLOAT_EQ(v4_1.Y, -4.0f);
    EXPECT_FLOAT_EQ(v4_1.Z, -4.0f);
    EXPECT_FLOAT_EQ(v4_1.W, -4.0f);
#endif
}

TEST(Subtraction, Mat4)
{
    HMM_Mat4 m4_1 = HMM_M4(); // will have 1 - 16
    HMM_Mat4 m4_2 = HMM_M4(); // will have 17 - 32

    // Fill the matrices
    int Counter = 1;
    for (int Column = 0; Column < 4; ++Column)
    {
        for (int Row = 0; Row < 4; ++Row)
        {
            m4_1.Elements[Column][Row] = Counter;
            ++Counter;
        }
    }
    for (int Column = 0; Column < 4; ++Column)
    {
        for (int Row = 0; Row < 4; ++Row)
        {
            m4_2.Elements[Column][Row] = Counter;
            ++Counter;
        }
    }

    // Test the results
    {
        HMM_Mat4 result = HMM_SubM4(m4_1, m4_2);
        for (int Column = 0; Column < 4; ++Column)
        {
            for (int Row = 0; Row < 4; ++Row)
            {
                EXPECT_FLOAT_EQ(result.Elements[Column][Row], -16.0f);
            }
        }
    }
#ifdef __cplusplus
    {
        HMM_Mat4 result = HMM_Sub(m4_1, m4_2);
        for (int Column = 0; Column < 4; ++Column)
        {
            for (int Row = 0; Row < 4; ++Row)
            {
                EXPECT_FLOAT_EQ(result.Elements[Column][Row], -16.0f);
            }
        }
    }
    {
        HMM_Mat4 result = m4_1 - m4_2;
        for (int Column = 0; Column < 4; ++Column)
        {
            for (int Row = 0; Row < 4; ++Row)
            {
                EXPECT_FLOAT_EQ(result.Elements[Column][Row], -16.0f);
            }
        }
    }

    m4_1 -= m4_2;
    for (int Column = 0; Column < 4; ++Column)
    {
        for (int Row = 0; Row < 4; ++Row)
        {
            EXPECT_FLOAT_EQ(m4_1.Elements[Column][Row], -16.0f);
        }
    }
#endif
}

TEST(Subtraction, Quaternion)
{
    HMM_Quat q1 = HMM_Q(1.0f, 2.0f, 3.0f, 4.0f);
    HMM_Quat q2 = HMM_Q(5.0f, 6.0f, 7.0f, 8.0f);

    {
        HMM_Quat result = HMM_SubQ(q1, q2);
        EXPECT_FLOAT_EQ(result.X, -4.0f);
        EXPECT_FLOAT_EQ(result.Y, -4.0f);
        EXPECT_FLOAT_EQ(result.Z, -4.0f);
        EXPECT_FLOAT_EQ(result.W, -4.0f);
    }
#ifdef __cplusplus
    {
        HMM_Quat result = HMM_Sub(q1, q2);
        EXPECT_FLOAT_EQ(result.X, -4.0f);
        EXPECT_FLOAT_EQ(result.Y, -4.0f);
        EXPECT_FLOAT_EQ(result.Z, -4.0f);
        EXPECT_FLOAT_EQ(result.W, -4.0f);
    }
    {
        HMM_Quat result = q1 - q2;
        EXPECT_FLOAT_EQ(result.X, -4.0f);
        EXPECT_FLOAT_EQ(result.Y, -4.0f);
        EXPECT_FLOAT_EQ(result.Z, -4.0f);
        EXPECT_FLOAT_EQ(result.W, -4.0f);
    }

    q1 -= q2;
    EXPECT_FLOAT_EQ(q1.X, -4.0f);
    EXPECT_FLOAT_EQ(q1.Y, -4.0f);
    EXPECT_FLOAT_EQ(q1.Z, -4.0f);
    EXPECT_FLOAT_EQ(q1.W, -4.0f);
#endif
}

#ifdef __cplusplus
TEST(UnaryMinus, Vec2)
{
    HMM_Vec2 VectorOne = {1.0f, 2.0f};
    HMM_Vec2 Result = -VectorOne;
    EXPECT_FLOAT_EQ(Result.X, -1.0f);
    EXPECT_FLOAT_EQ(Result.Y, -2.0f);
}

TEST(UnaryMinus, Vec3)
{
    HMM_Vec3 VectorOne = {1.0f, 2.0f, 3.0f};
    HMM_Vec3 Result = -VectorOne;
    EXPECT_FLOAT_EQ(Result.X, -1.0f);
    EXPECT_FLOAT_EQ(Result.Y, -2.0f);
    EXPECT_FLOAT_EQ(Result.Z, -3.0f);
}

TEST(UnaryMinus, Vec4)
{
    HMM_Vec4 VectorOne = {1.0f, 2.0f, 3.0f, 4.0f};
    HMM_Vec4 Result = -VectorOne;
    EXPECT_FLOAT_EQ(Result.X, -1.0f);
    EXPECT_FLOAT_EQ(Result.Y, -2.0f);
    EXPECT_FLOAT_EQ(Result.Z, -3.0f);
    EXPECT_FLOAT_EQ(Result.W, -4.0f);
}
#endif
