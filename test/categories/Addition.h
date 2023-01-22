#include "../HandmadeTest.h"

TEST(Addition, Vec2)
{
    HMM_Vec2 v2_1 = HMM_V2(1.0f, 2.0f);
    HMM_Vec2 v2_2 = HMM_V2(3.0f, 4.0f);

    {
        HMM_Vec2 result = HMM_AddV2(v2_1, v2_2);
        EXPECT_FLOAT_EQ(result.X, 4.0f);
        EXPECT_FLOAT_EQ(result.Y, 6.0f);
    }
#ifdef __cplusplus
    {
        HMM_Vec2 result = HMM_Add(v2_1, v2_2);
        EXPECT_FLOAT_EQ(result.X, 4.0f);
        EXPECT_FLOAT_EQ(result.Y, 6.0f);
    }
    {
        HMM_Vec2 result = v2_1 + v2_2;
        EXPECT_FLOAT_EQ(result.X, 4.0f);
        EXPECT_FLOAT_EQ(result.Y, 6.0f);
    }

    v2_1 += v2_2;
    EXPECT_FLOAT_EQ(v2_1.X, 4.0f);
    EXPECT_FLOAT_EQ(v2_1.Y, 6.0f);
#endif
}

TEST(Addition, Vec3)
{
    HMM_Vec3 v3_1 = HMM_V3(1.0f, 2.0f, 3.0f);
    HMM_Vec3 v3_2 = HMM_V3(4.0f, 5.0f, 6.0f);

    {
        HMM_Vec3 result = HMM_AddV3(v3_1, v3_2);
        EXPECT_FLOAT_EQ(result.X, 5.0f);
        EXPECT_FLOAT_EQ(result.Y, 7.0f);
        EXPECT_FLOAT_EQ(result.Z, 9.0f);
    }
#ifdef __cplusplus
    {
        HMM_Vec3 result = HMM_Add(v3_1, v3_2);
        EXPECT_FLOAT_EQ(result.X, 5.0f);
        EXPECT_FLOAT_EQ(result.Y, 7.0f);
        EXPECT_FLOAT_EQ(result.Z, 9.0f);
    }
    {
        HMM_Vec3 result = v3_1 + v3_2;
        EXPECT_FLOAT_EQ(result.X, 5.0f);
        EXPECT_FLOAT_EQ(result.Y, 7.0f);
        EXPECT_FLOAT_EQ(result.Z, 9.0f);
    }

    v3_1 += v3_2;
    EXPECT_FLOAT_EQ(v3_1.X, 5.0f);
    EXPECT_FLOAT_EQ(v3_1.Y, 7.0f);
    EXPECT_FLOAT_EQ(v3_1.Z, 9.0f);
#endif
}

TEST(Addition, Vec4)
{
    HMM_Vec4 v4_1 = HMM_V4(1.0f, 2.0f, 3.0f, 4.0f);
    HMM_Vec4 v4_2 = HMM_V4(5.0f, 6.0f, 7.0f, 8.0f);

    {
        HMM_Vec4 result = HMM_AddV4(v4_1, v4_2);
        EXPECT_FLOAT_EQ(result.X, 6.0f);
        EXPECT_FLOAT_EQ(result.Y, 8.0f);
        EXPECT_FLOAT_EQ(result.Z, 10.0f);
        EXPECT_FLOAT_EQ(result.W, 12.0f);
    }
#ifdef __cplusplus
    {
        HMM_Vec4 result = HMM_Add(v4_1, v4_2);
        EXPECT_FLOAT_EQ(result.X, 6.0f);
        EXPECT_FLOAT_EQ(result.Y, 8.0f);
        EXPECT_FLOAT_EQ(result.Z, 10.0f);
        EXPECT_FLOAT_EQ(result.W, 12.0f);
    }
    {
        HMM_Vec4 result = v4_1 + v4_2;
        EXPECT_FLOAT_EQ(result.X, 6.0f);
        EXPECT_FLOAT_EQ(result.Y, 8.0f);
        EXPECT_FLOAT_EQ(result.Z, 10.0f);
        EXPECT_FLOAT_EQ(result.W, 12.0f);
    }

    v4_1 += v4_2;
    EXPECT_FLOAT_EQ(v4_1.X, 6.0f);
    EXPECT_FLOAT_EQ(v4_1.Y, 8.0f);
    EXPECT_FLOAT_EQ(v4_1.Z, 10.0f);
    EXPECT_FLOAT_EQ(v4_1.W, 12.0f);
#endif
}

TEST(Addition, Mat2)
{
    HMM_Mat2 a = HMM_M2();
    HMM_Mat2 b = HMM_M2();

    int Counter = 1;
    for (int Column = 0; Column < 2; ++Column)
    {
        for (int Row = 0; Row < 2; ++Row)
        {
            a.Elements[Column][Row] = Counter++;
        }
    }
    for (int Column = 0; Column < 2; ++Column)
    {
        for (int Row = 0; Row < 2; ++Row)
        {
            b.Elements[Column][Row] = Counter++;
        }
    }

    {
        HMM_Mat2 result = HMM_AddM2(a, b);
        EXPECT_FLOAT_EQ(result.Elements[0][0], 6.0f); 
        EXPECT_FLOAT_EQ(result.Elements[0][1], 8.0f); 
        EXPECT_FLOAT_EQ(result.Elements[1][0], 10.0f); 
        EXPECT_FLOAT_EQ(result.Elements[1][1], 12.0f); 
    }

#ifdef __cplusplus
    {
        HMM_Mat2 result = HMM_Add(a, b);
        EXPECT_FLOAT_EQ(result.Elements[0][0], 6.0f); 
        EXPECT_FLOAT_EQ(result.Elements[0][1], 8.0f); 
        EXPECT_FLOAT_EQ(result.Elements[1][0], 10.0f); 
        EXPECT_FLOAT_EQ(result.Elements[1][1], 12.0f); 
    }
    {
        HMM_Mat2 result = a + b;
        EXPECT_FLOAT_EQ(result.Elements[0][0], 6.0f); 
        EXPECT_FLOAT_EQ(result.Elements[0][1], 8.0f); 
        EXPECT_FLOAT_EQ(result.Elements[1][0], 10.0f); 
        EXPECT_FLOAT_EQ(result.Elements[1][1], 12.0f); 
    }
    a += b;
    EXPECT_FLOAT_EQ(a.Elements[0][0], 6.0f); 
    EXPECT_FLOAT_EQ(a.Elements[0][1], 8.0f); 
    EXPECT_FLOAT_EQ(a.Elements[1][0], 10.0f); 
    EXPECT_FLOAT_EQ(a.Elements[1][1], 12.0f); 
#endif
}

TEST(Addition, Mat3) 
{
    HMM_Mat3 a = HMM_M3();
    HMM_Mat3 b = HMM_M3();

    int Counter = 1;
    for (int Column = 0; Column < 3; ++Column)
    {
        for (int Row = 0; Row < 3; ++Row)
        {
            a.Elements[Column][Row] = Counter++;
        }
    }
    for (int Column = 0; Column < 3; ++Column)
    {
        for (int Row = 0; Row < 3; ++Row)
        {
            b.Elements[Column][Row] = Counter++;
        }
    }

    {
        HMM_Mat3 result = HMM_AddM3(a, b);
        EXPECT_FLOAT_EQ(result.Elements[0][0], 11.0f); 
        EXPECT_FLOAT_EQ(result.Elements[0][1], 13.0f); 
        EXPECT_FLOAT_EQ(result.Elements[0][2], 15.0f); 
        EXPECT_FLOAT_EQ(result.Elements[1][0], 17.0f); 
        EXPECT_FLOAT_EQ(result.Elements[1][1], 19.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][2], 21.0f); 
        EXPECT_FLOAT_EQ(result.Elements[2][0], 23.0f); 
        EXPECT_FLOAT_EQ(result.Elements[2][1], 25.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][2], 27.0f);   
    }

#ifdef __cplusplus
    {
        HMM_Mat3 result = HMM_Add(a, b);
        EXPECT_FLOAT_EQ(result.Elements[0][0], 11.0f); 
        EXPECT_FLOAT_EQ(result.Elements[0][1], 13.0f); 
        EXPECT_FLOAT_EQ(result.Elements[0][2], 15.0f); 
        EXPECT_FLOAT_EQ(result.Elements[1][0], 17.0f); 
        EXPECT_FLOAT_EQ(result.Elements[1][1], 19.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][2], 21.0f); 
        EXPECT_FLOAT_EQ(result.Elements[2][0], 23.0f); 
        EXPECT_FLOAT_EQ(result.Elements[2][1], 25.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][2], 27.0f);   
    }
    {
        HMM_Mat3 result = a + b;
        EXPECT_FLOAT_EQ(result.Elements[0][0], 11.0f); 
        EXPECT_FLOAT_EQ(result.Elements[0][1], 13.0f); 
        EXPECT_FLOAT_EQ(result.Elements[0][2], 15.0f); 
        EXPECT_FLOAT_EQ(result.Elements[1][0], 17.0f); 
        EXPECT_FLOAT_EQ(result.Elements[1][1], 19.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][2], 21.0f); 
        EXPECT_FLOAT_EQ(result.Elements[2][0], 23.0f); 
        EXPECT_FLOAT_EQ(result.Elements[2][1], 25.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][2], 27.0f);   
    }
    a += b;
    EXPECT_FLOAT_EQ(a.Elements[0][0], 11.0f); 
    EXPECT_FLOAT_EQ(a.Elements[0][1], 13.0f); 
    EXPECT_FLOAT_EQ(a.Elements[0][2], 15.0f); 
    EXPECT_FLOAT_EQ(a.Elements[1][0], 17.0f); 
    EXPECT_FLOAT_EQ(a.Elements[1][1], 19.0f);
    EXPECT_FLOAT_EQ(a.Elements[1][2], 21.0f); 
    EXPECT_FLOAT_EQ(a.Elements[2][0], 23.0f); 
    EXPECT_FLOAT_EQ(a.Elements[2][1], 25.0f);
    EXPECT_FLOAT_EQ(a.Elements[2][2], 27.0f);   
#endif  
}

TEST(Addition, Mat4)
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
        HMM_Mat4 result = HMM_AddM4(m4_1, m4_2);
        float Expected = 18.0f;
        for (int Column = 0; Column < 4; ++Column)
        {
            for (int Row = 0; Row < 4; ++Row)
            {
                EXPECT_FLOAT_EQ(result.Elements[Column][Row], Expected);
                Expected += 2.0f;
            }
        }
    }
#ifdef __cplusplus
    {
        HMM_Mat4 result = HMM_Add(m4_1, m4_2);
        float Expected = 18.0f;
        for (int Column = 0; Column < 4; ++Column)
        {
            for (int Row = 0; Row < 4; ++Row)
            {
                EXPECT_FLOAT_EQ(result.Elements[Column][Row], Expected);
                Expected += 2.0f;
            }
        }
    }
    {
        HMM_Mat4 result = m4_1 + m4_2;
        float Expected = 18.0f;
        for (int Column = 0; Column < 4; ++Column)
        {
            for (int Row = 0; Row < 4; ++Row)
            {
                EXPECT_FLOAT_EQ(result.Elements[Column][Row], Expected);
                Expected += 2.0f;
            }
        }
    }

    m4_1 += m4_2;
    float Expected = 18.0f;
    for (int Column = 0; Column < 4; ++Column)
    {
        for (int Row = 0; Row < 4; ++Row)
        {
            EXPECT_FLOAT_EQ(m4_1.Elements[Column][Row], Expected);
            Expected += 2.0f;
        }
    }
#endif
}

TEST(Addition, Quaternion)
{
    HMM_Quat q1 = HMM_Q(1.0f, 2.0f, 3.0f, 4.0f);
    HMM_Quat q2 = HMM_Q(5.0f, 6.0f, 7.0f, 8.0f);

    {
        HMM_Quat result = HMM_AddQ(q1, q2);
        EXPECT_FLOAT_EQ(result.X, 6.0f);
        EXPECT_FLOAT_EQ(result.Y, 8.0f);
        EXPECT_FLOAT_EQ(result.Z, 10.0f);
        EXPECT_FLOAT_EQ(result.W, 12.0f);
    }
#ifdef __cplusplus
    {
        HMM_Quat result = HMM_Add(q1, q2);
        EXPECT_FLOAT_EQ(result.X, 6.0f);
        EXPECT_FLOAT_EQ(result.Y, 8.0f);
        EXPECT_FLOAT_EQ(result.Z, 10.0f);
        EXPECT_FLOAT_EQ(result.W, 12.0f);
    }
    {
        HMM_Quat result = q1 + q2;
        EXPECT_FLOAT_EQ(result.X, 6.0f);
        EXPECT_FLOAT_EQ(result.Y, 8.0f);
        EXPECT_FLOAT_EQ(result.Z, 10.0f);
        EXPECT_FLOAT_EQ(result.W, 12.0f);
    }

    q1 += q2;
    EXPECT_FLOAT_EQ(q1.X, 6.0f);
    EXPECT_FLOAT_EQ(q1.Y, 8.0f);
    EXPECT_FLOAT_EQ(q1.Z, 10.0f);
    EXPECT_FLOAT_EQ(q1.W, 12.0f);
#endif
}
