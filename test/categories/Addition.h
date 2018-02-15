#include "../HandmadeTest.h"

TEST(Addition, Vec2)
{
    hmm_vec2 v2_1 = HMM_Vec2(1.0f, 2.0f);
    hmm_vec2 v2_2 = HMM_Vec2(3.0f, 4.0f);

    {
        hmm_vec2 result = HMM_AddVec2(v2_1, v2_2);
        EXPECT_FLOAT_EQ(result.X, 4.0f);
        EXPECT_FLOAT_EQ(result.Y, 6.0f);
    }
#ifdef __cplusplus
    {
        hmm_vec2 result = HMM_Add(v2_1, v2_2);
        EXPECT_FLOAT_EQ(result.X, 4.0f);
        EXPECT_FLOAT_EQ(result.Y, 6.0f);
    }
    {
        hmm_vec2 result = v2_1 + v2_2;
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
    hmm_vec3 v3_1 = HMM_Vec3(1.0f, 2.0f, 3.0f);
    hmm_vec3 v3_2 = HMM_Vec3(4.0f, 5.0f, 6.0f);

    {
        hmm_vec3 result = HMM_AddVec3(v3_1, v3_2);
        EXPECT_FLOAT_EQ(result.X, 5.0f);
        EXPECT_FLOAT_EQ(result.Y, 7.0f);
        EXPECT_FLOAT_EQ(result.Z, 9.0f);    
    }
#ifdef __cplusplus
    {
        hmm_vec3 result = HMM_Add(v3_1, v3_2);
        EXPECT_FLOAT_EQ(result.X, 5.0f);
        EXPECT_FLOAT_EQ(result.Y, 7.0f);
        EXPECT_FLOAT_EQ(result.Z, 9.0f);
    }
    {
        hmm_vec3 result = v3_1 + v3_2;
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
    hmm_vec4 v4_1 = HMM_Vec4(1.0f, 2.0f, 3.0f, 4.0f);
    hmm_vec4 v4_2 = HMM_Vec4(5.0f, 6.0f, 7.0f, 8.0f);
    
    {
        hmm_vec4 result = HMM_AddVec4(v4_1, v4_2);
        EXPECT_FLOAT_EQ(result.X, 6.0f);
        EXPECT_FLOAT_EQ(result.Y, 8.0f);
        EXPECT_FLOAT_EQ(result.Z, 10.0f);
        EXPECT_FLOAT_EQ(result.W, 12.0f);
    }
#ifdef __cplusplus
    {
        hmm_vec4 result = HMM_Add(v4_1, v4_2);
        EXPECT_FLOAT_EQ(result.X, 6.0f);
        EXPECT_FLOAT_EQ(result.Y, 8.0f);
        EXPECT_FLOAT_EQ(result.Z, 10.0f);
        EXPECT_FLOAT_EQ(result.W, 12.0f);
    }
    {
        hmm_vec4 result = v4_1 + v4_2;
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

TEST(Addition, Mat4)
{
    hmm_mat4 m4_1 = HMM_Mat4(); // will have 1 - 16
    hmm_mat4 m4_2 = HMM_Mat4(); // will have 17 - 32

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
        hmm_mat4 result = HMM_AddMat4(m4_1, m4_2);
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
        hmm_mat4 result = HMM_Add(m4_1, m4_2);
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
        hmm_mat4 result = m4_1 + m4_2;
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
    hmm_quaternion q1 = HMM_Quaternion(1.0f, 2.0f, 3.0f, 4.0f);
    hmm_quaternion q2 = HMM_Quaternion(5.0f, 6.0f, 7.0f, 8.0f);

    {
        hmm_quaternion result = HMM_AddQuaternion(q1, q2);
        EXPECT_FLOAT_EQ(result.X, 6.0f);
        EXPECT_FLOAT_EQ(result.Y, 8.0f);
        EXPECT_FLOAT_EQ(result.Z, 10.0f);
        EXPECT_FLOAT_EQ(result.W, 12.0f);
    }
#ifdef __cplusplus
    {
        hmm_quaternion result = HMM_Add(q1, q2);
        EXPECT_FLOAT_EQ(result.X, 6.0f);
        EXPECT_FLOAT_EQ(result.Y, 8.0f);
        EXPECT_FLOAT_EQ(result.Z, 10.0f);
        EXPECT_FLOAT_EQ(result.W, 12.0f);
    }
    {
        hmm_quaternion result = q1 + q2;
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
