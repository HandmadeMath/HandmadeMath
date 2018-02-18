#include "../HandmadeTest.h"

TEST(Multiplication, Vec2Vec2)
{
    hmm_vec2 v2_1 = HMM_Vec2(1.0f, 2.0f);
    hmm_vec2 v2_2 = HMM_Vec2(3.0f, 4.0f);

    {
        hmm_vec2 result = HMM_MultiplyVec2(v2_1, v2_2);
        EXPECT_FLOAT_EQ(result.X, 3.0f);
        EXPECT_FLOAT_EQ(result.Y, 8.0f);
    }
#ifdef __cplusplus
    {
        hmm_vec2 result = HMM_Multiply(v2_1, v2_2);
        EXPECT_FLOAT_EQ(result.X, 3.0f);
        EXPECT_FLOAT_EQ(result.Y, 8.0f);
    }
    {
        hmm_vec2 result = v2_1 * v2_2;
        EXPECT_FLOAT_EQ(result.X, 3.0f);
        EXPECT_FLOAT_EQ(result.Y, 8.0f);
    }

    v2_1 *= v2_2;
    EXPECT_FLOAT_EQ(v2_1.X, 3.0f);
    EXPECT_FLOAT_EQ(v2_1.Y, 8.0f);
#endif
}

TEST(Multiplication, Vec2Scalar)
{
    hmm_vec2 v2 = HMM_Vec2(1.0f, 2.0f);
    float s = 3.0f;

    {
        hmm_vec2 result = HMM_MultiplyVec2f(v2, s);
        EXPECT_FLOAT_EQ(result.X, 3.0f);
        EXPECT_FLOAT_EQ(result.Y, 6.0f);
    }
#ifdef __cplusplus
    {
        hmm_vec2 result = HMM_Multiply(v2, s);
        EXPECT_FLOAT_EQ(result.X, 3.0f);
        EXPECT_FLOAT_EQ(result.Y, 6.0f);
    }
    {
        hmm_vec2 result = v2 * s;
        EXPECT_FLOAT_EQ(result.X, 3.0f);
        EXPECT_FLOAT_EQ(result.Y, 6.0f);
    }
    {
        hmm_vec2 result = s * v2;
        EXPECT_FLOAT_EQ(result.X, 3.0f);
        EXPECT_FLOAT_EQ(result.Y, 6.0f);
    }

    v2 *= s;
    EXPECT_FLOAT_EQ(v2.X, 3.0f);
    EXPECT_FLOAT_EQ(v2.Y, 6.0f);
#endif
}

TEST(Multiplication, Vec3Vec3)
{
    hmm_vec3 v3_1 = HMM_Vec3(1.0f, 2.0f, 3.0f);
    hmm_vec3 v3_2 = HMM_Vec3(4.0f, 5.0f, 6.0f);

    {
        hmm_vec3 result = HMM_MultiplyVec3(v3_1, v3_2);
        EXPECT_FLOAT_EQ(result.X, 4.0f);
        EXPECT_FLOAT_EQ(result.Y, 10.0f);
        EXPECT_FLOAT_EQ(result.Z, 18.0f);
    }
#ifdef __cplusplus
    {
        hmm_vec3 result = HMM_Multiply(v3_1, v3_2);
        EXPECT_FLOAT_EQ(result.X, 4.0f);
        EXPECT_FLOAT_EQ(result.Y, 10.0f);
        EXPECT_FLOAT_EQ(result.Z, 18.0f);
    }
    {
        hmm_vec3 result = v3_1 * v3_2;
        EXPECT_FLOAT_EQ(result.X, 4.0f);
        EXPECT_FLOAT_EQ(result.Y, 10.0f);
        EXPECT_FLOAT_EQ(result.Z, 18.0f);
    }

    v3_1 *= v3_2;
    EXPECT_FLOAT_EQ(v3_1.X, 4.0f);
    EXPECT_FLOAT_EQ(v3_1.Y, 10.0f);
    EXPECT_FLOAT_EQ(v3_1.Z, 18.0f);
#endif
}

TEST(Multiplication, Vec3Scalar)
{
    hmm_vec3 v3 = HMM_Vec3(1.0f, 2.0f, 3.0f);
    float s = 3.0f;

    {
        hmm_vec3 result = HMM_MultiplyVec3f(v3, s);
        EXPECT_FLOAT_EQ(result.X, 3.0f);
        EXPECT_FLOAT_EQ(result.Y, 6.0f);
        EXPECT_FLOAT_EQ(result.Z, 9.0f);
    }
#ifdef __cplusplus
    {
        hmm_vec3 result = HMM_Multiply(v3, s);
        EXPECT_FLOAT_EQ(result.X, 3.0f);
        EXPECT_FLOAT_EQ(result.Y, 6.0f);
        EXPECT_FLOAT_EQ(result.Z, 9.0f);
    }
    {
        hmm_vec3 result = v3 * s;
        EXPECT_FLOAT_EQ(result.X, 3.0f);
        EXPECT_FLOAT_EQ(result.Y, 6.0f);
        EXPECT_FLOAT_EQ(result.Z, 9.0f);
    }
    {
        hmm_vec3 result = s * v3;
        EXPECT_FLOAT_EQ(result.X, 3.0f);
        EXPECT_FLOAT_EQ(result.Y, 6.0f);
        EXPECT_FLOAT_EQ(result.Z, 9.0f);
    }

    v3 *= s;
    EXPECT_FLOAT_EQ(v3.X, 3.0f);
    EXPECT_FLOAT_EQ(v3.Y, 6.0f);
    EXPECT_FLOAT_EQ(v3.Z, 9.0f);
#endif
}

TEST(Multiplication, Vec4Vec4)
{
    hmm_vec4 v4_1 = HMM_Vec4(1.0f, 2.0f, 3.0f, 4.0f);
    hmm_vec4 v4_2 = HMM_Vec4(5.0f, 6.0f, 7.0f, 8.0f);

    {
        hmm_vec4 result = HMM_MultiplyVec4(v4_1, v4_2);
        EXPECT_FLOAT_EQ(result.X, 5.0f);
        EXPECT_FLOAT_EQ(result.Y, 12.0f);
        EXPECT_FLOAT_EQ(result.Z, 21.0f);
        EXPECT_FLOAT_EQ(result.W, 32.0f);
    }
#ifdef __cplusplus
    {
        hmm_vec4 result = HMM_Multiply(v4_1, v4_2);
        EXPECT_FLOAT_EQ(result.X, 5.0f);
        EXPECT_FLOAT_EQ(result.Y, 12.0f);
        EXPECT_FLOAT_EQ(result.Z, 21.0f);
        EXPECT_FLOAT_EQ(result.W, 32.0f);
    }
    {
        hmm_vec4 result = v4_1 * v4_2;
        EXPECT_FLOAT_EQ(result.X, 5.0f);
        EXPECT_FLOAT_EQ(result.Y, 12.0f);
        EXPECT_FLOAT_EQ(result.Z, 21.0f);
        EXPECT_FLOAT_EQ(result.W, 32.0f);
    }

    v4_1 *= v4_2;
    EXPECT_FLOAT_EQ(v4_1.X, 5.0f);
    EXPECT_FLOAT_EQ(v4_1.Y, 12.0f);
    EXPECT_FLOAT_EQ(v4_1.Z, 21.0f);
    EXPECT_FLOAT_EQ(v4_1.W, 32.0f);
#endif
}

TEST(Multiplication, Vec4Scalar)
{
    hmm_vec4 v4 = HMM_Vec4(1.0f, 2.0f, 3.0f, 4.0f);
    float s = 3.0f;

    {
        hmm_vec4 result = HMM_MultiplyVec4f(v4, s);
        EXPECT_FLOAT_EQ(result.X, 3.0f);
        EXPECT_FLOAT_EQ(result.Y, 6.0f);
        EXPECT_FLOAT_EQ(result.Z, 9.0f);
        EXPECT_FLOAT_EQ(result.W, 12.0f);
    }
#ifdef __cplusplus
    {
        hmm_vec4 result = HMM_Multiply(v4, s);
        EXPECT_FLOAT_EQ(result.X, 3.0f);
        EXPECT_FLOAT_EQ(result.Y, 6.0f);
        EXPECT_FLOAT_EQ(result.Z, 9.0f);
        EXPECT_FLOAT_EQ(result.W, 12.0f);
    }
    {
        hmm_vec4 result = v4 * s;
        EXPECT_FLOAT_EQ(result.X, 3.0f);
        EXPECT_FLOAT_EQ(result.Y, 6.0f);
        EXPECT_FLOAT_EQ(result.Z, 9.0f);
        EXPECT_FLOAT_EQ(result.W, 12.0f);
    }
    {
        hmm_vec4 result = s * v4;
        EXPECT_FLOAT_EQ(result.X, 3.0f);
        EXPECT_FLOAT_EQ(result.Y, 6.0f);
        EXPECT_FLOAT_EQ(result.Z, 9.0f);
        EXPECT_FLOAT_EQ(result.W, 12.0f);
    }

    v4 *= s;
    EXPECT_FLOAT_EQ(v4.X, 3.0f);
    EXPECT_FLOAT_EQ(v4.Y, 6.0f);
    EXPECT_FLOAT_EQ(v4.Z, 9.0f);
#endif
}

TEST(Multiplication, Mat4Mat4)
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
        hmm_mat4 result = HMM_MultiplyMat4(m4_1, m4_2);
        EXPECT_FLOAT_EQ(result.Elements[0][0], 538.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][1], 612.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][2], 686.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][3], 760.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][0], 650.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][1], 740.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][2], 830.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][3], 920.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][0], 762.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][1], 868.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][2], 974.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][3], 1080.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][0], 874.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][1], 996.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][2], 1118.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][3], 1240.0f);
    }
#ifdef __cplusplus
    {
        hmm_mat4 result = HMM_Multiply(m4_1, m4_2);
        EXPECT_FLOAT_EQ(result.Elements[0][0], 538.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][1], 612.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][2], 686.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][3], 760.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][0], 650.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][1], 740.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][2], 830.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][3], 920.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][0], 762.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][1], 868.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][2], 974.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][3], 1080.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][0], 874.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][1], 996.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][2], 1118.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][3], 1240.0f);
    }
    {
        hmm_mat4 result = m4_1 * m4_2;
        EXPECT_FLOAT_EQ(result.Elements[0][0], 538.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][1], 612.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][2], 686.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][3], 760.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][0], 650.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][1], 740.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][2], 830.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][3], 920.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][0], 762.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][1], 868.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][2], 974.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][3], 1080.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][0], 874.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][1], 996.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][2], 1118.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][3], 1240.0f);
    }

    // At the time I wrote this, I intentionally omitted
    // the *= operator for matrices because matrix
    // multiplication is not commutative. (bvisness)
#endif
}

TEST(Multiplication, Mat4Scalar)
{
    hmm_mat4 m4 = HMM_Mat4(); // will have 1 - 16
    float s = 3;

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
        hmm_mat4 result = HMM_MultiplyMat4f(m4, s);
        EXPECT_FLOAT_EQ(result.Elements[0][0], 3.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][1], 6.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][2], 9.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][3], 12.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][0], 15.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][1], 18.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][2], 21.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][3], 24.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][0], 27.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][1], 30.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][2], 33.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][3], 36.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][0], 39.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][1], 42.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][2], 45.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][3], 48.0f);
    }
#ifdef __cplusplus
    {
        hmm_mat4 result = HMM_Multiply(m4, s);
        EXPECT_FLOAT_EQ(result.Elements[0][0], 3.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][1], 6.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][2], 9.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][3], 12.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][0], 15.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][1], 18.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][2], 21.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][3], 24.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][0], 27.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][1], 30.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][2], 33.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][3], 36.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][0], 39.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][1], 42.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][2], 45.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][3], 48.0f);
    }
    {
        hmm_mat4 result = m4 * s;
        EXPECT_FLOAT_EQ(result.Elements[0][0], 3.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][1], 6.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][2], 9.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][3], 12.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][0], 15.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][1], 18.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][2], 21.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][3], 24.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][0], 27.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][1], 30.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][2], 33.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][3], 36.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][0], 39.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][1], 42.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][2], 45.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][3], 48.0f);
    }
    {
        hmm_mat4 result = s * m4;
        EXPECT_FLOAT_EQ(result.Elements[0][0], 3.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][1], 6.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][2], 9.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][3], 12.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][0], 15.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][1], 18.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][2], 21.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][3], 24.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][0], 27.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][1], 30.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][2], 33.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][3], 36.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][0], 39.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][1], 42.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][2], 45.0f);
        EXPECT_FLOAT_EQ(result.Elements[3][3], 48.0f);
    }

    m4 *= s;
    EXPECT_FLOAT_EQ(m4.Elements[0][0], 3.0f);
    EXPECT_FLOAT_EQ(m4.Elements[0][1], 6.0f);
    EXPECT_FLOAT_EQ(m4.Elements[0][2], 9.0f);
    EXPECT_FLOAT_EQ(m4.Elements[0][3], 12.0f);
    EXPECT_FLOAT_EQ(m4.Elements[1][0], 15.0f);
    EXPECT_FLOAT_EQ(m4.Elements[1][1], 18.0f);
    EXPECT_FLOAT_EQ(m4.Elements[1][2], 21.0f);
    EXPECT_FLOAT_EQ(m4.Elements[1][3], 24.0f);
    EXPECT_FLOAT_EQ(m4.Elements[2][0], 27.0f);
    EXPECT_FLOAT_EQ(m4.Elements[2][1], 30.0f);
    EXPECT_FLOAT_EQ(m4.Elements[2][2], 33.0f);
    EXPECT_FLOAT_EQ(m4.Elements[2][3], 36.0f);
    EXPECT_FLOAT_EQ(m4.Elements[3][0], 39.0f);
    EXPECT_FLOAT_EQ(m4.Elements[3][1], 42.0f);
    EXPECT_FLOAT_EQ(m4.Elements[3][2], 45.0f);
    EXPECT_FLOAT_EQ(m4.Elements[3][3], 48.0f);
#endif
}

TEST(Multiplication, Mat4Vec4)
{
    hmm_mat4 m4 = HMM_Mat4(); // will have 1 - 16
    hmm_vec4 v4 = HMM_Vec4(1.0f, 2.0f, 3.0f, 4.0f);

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
        hmm_vec4 result = HMM_MultiplyMat4ByVec4(m4, v4);
        EXPECT_FLOAT_EQ(result.X, 90.0f);
        EXPECT_FLOAT_EQ(result.Y, 100.0f);
        EXPECT_FLOAT_EQ(result.Z, 110.0f);
        EXPECT_FLOAT_EQ(result.W, 120.0f);
    }
#ifdef __cplusplus
    {
        hmm_vec4 result = HMM_Multiply(m4, v4);
        EXPECT_FLOAT_EQ(result.X, 90.0f);
        EXPECT_FLOAT_EQ(result.Y, 100.0f);
        EXPECT_FLOAT_EQ(result.Z, 110.0f);
        EXPECT_FLOAT_EQ(result.W, 120.0f);
    }
    {
        hmm_vec4 result = m4 * v4;
        EXPECT_FLOAT_EQ(result.X, 90.0f);
        EXPECT_FLOAT_EQ(result.Y, 100.0f);
        EXPECT_FLOAT_EQ(result.Z, 110.0f);
        EXPECT_FLOAT_EQ(result.W, 120.0f);
    }

    // *= makes no sense for this particular case.
#endif
}

TEST(Multiplication, QuaternionQuaternion)
{
    hmm_quaternion q1 = HMM_Quaternion(1.0f, 2.0f, 3.0f, 4.0f);
    hmm_quaternion q2 = HMM_Quaternion(5.0f, 6.0f, 7.0f, 8.0f);

    {
        hmm_quaternion result = HMM_MultiplyQuaternion(q1, q2);
        EXPECT_FLOAT_EQ(result.X, 24.0f);
        EXPECT_FLOAT_EQ(result.Y, 48.0f);
        EXPECT_FLOAT_EQ(result.Z, 48.0f);
        EXPECT_FLOAT_EQ(result.W, -6.0f);
    }
#ifdef __cplusplus
    {
        hmm_quaternion result = HMM_Multiply(q1, q2);
        EXPECT_FLOAT_EQ(result.X, 24.0f);
        EXPECT_FLOAT_EQ(result.Y, 48.0f);
        EXPECT_FLOAT_EQ(result.Z, 48.0f);
        EXPECT_FLOAT_EQ(result.W, -6.0f);
    }
    {
        hmm_quaternion result = q1 * q2;
        EXPECT_FLOAT_EQ(result.X, 24.0f);
        EXPECT_FLOAT_EQ(result.Y, 48.0f);
        EXPECT_FLOAT_EQ(result.Z, 48.0f);
        EXPECT_FLOAT_EQ(result.W, -6.0f);
    }

    // Like with matrices, we're not implementing the *=
    // operator for quaternions because quaternion multiplication
    // is not commutative.
#endif
}

TEST(Multiplication, QuaternionScalar)
{
    hmm_quaternion q = HMM_Quaternion(1.0f, 2.0f, 3.0f, 4.0f);
    float f = 2.0f;

    {
        hmm_quaternion result = HMM_MultiplyQuaternionF(q, f);
        EXPECT_FLOAT_EQ(result.X, 2.0f);
        EXPECT_FLOAT_EQ(result.Y, 4.0f);
        EXPECT_FLOAT_EQ(result.Z, 6.0f);
        EXPECT_FLOAT_EQ(result.W, 8.0f);
    }
#ifdef __cplusplus
    {
        hmm_quaternion result = HMM_Multiply(q, f);
        EXPECT_FLOAT_EQ(result.X, 2.0f);
        EXPECT_FLOAT_EQ(result.Y, 4.0f);
        EXPECT_FLOAT_EQ(result.Z, 6.0f);
        EXPECT_FLOAT_EQ(result.W, 8.0f);
    }
    {
        hmm_quaternion result = q * f;
        EXPECT_FLOAT_EQ(result.X, 2.0f);
        EXPECT_FLOAT_EQ(result.Y, 4.0f);
        EXPECT_FLOAT_EQ(result.Z, 6.0f);
        EXPECT_FLOAT_EQ(result.W, 8.0f);
    }
    {
        hmm_quaternion result = f * q;
        EXPECT_FLOAT_EQ(result.X, 2.0f);
        EXPECT_FLOAT_EQ(result.Y, 4.0f);
        EXPECT_FLOAT_EQ(result.Z, 6.0f);
        EXPECT_FLOAT_EQ(result.W, 8.0f);
    }

    q *= f;
    EXPECT_FLOAT_EQ(q.X, 2.0f);
    EXPECT_FLOAT_EQ(q.Y, 4.0f);
    EXPECT_FLOAT_EQ(q.Z, 6.0f);
    EXPECT_FLOAT_EQ(q.W, 8.0f);
#endif
}
