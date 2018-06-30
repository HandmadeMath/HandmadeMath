#include "../HandmadeTest.h"

TEST(QuaternionOps, Inverse)
{
    hmm_quaternion q1 = HMM_Quaternion(1.0f, 2.0f, 3.0f, 4.0f);
    hmm_quaternion inverse = HMM_InverseQuaternion(q1);

    hmm_quaternion result = HMM_MultiplyQuaternion(q1, inverse);

    EXPECT_FLOAT_EQ(result.X, 0.0f);
    EXPECT_FLOAT_EQ(result.Y, 0.0f);
    EXPECT_FLOAT_EQ(result.Z, 0.0f);
    EXPECT_FLOAT_EQ(result.W, 1.0f);
}

TEST(QuaternionOps, Dot)
{
    hmm_quaternion q1 = HMM_Quaternion(1.0f, 2.0f, 3.0f, 4.0f);
    hmm_quaternion q2 = HMM_Quaternion(5.0f, 6.0f, 7.0f, 8.0f);

    {
        float result = HMM_DotQuaternion(q1, q2);
        EXPECT_FLOAT_EQ(result, 70.0f);
    }
#ifdef __cplusplus
    {
        float result = HMM_Dot(q1, q2);
        EXPECT_FLOAT_EQ(result, 70.0f);
    }
#endif
}

TEST(QuaternionOps, Normalize)
{
    hmm_quaternion q = HMM_Quaternion(1.0f, 2.0f, 3.0f, 4.0f);

    {
        hmm_quaternion result = HMM_NormalizeQuaternion(q);
        EXPECT_FLOAT_EQ(result.X, 0.1825741858f);
        EXPECT_FLOAT_EQ(result.Y, 0.3651483717f);
        EXPECT_FLOAT_EQ(result.Z, 0.5477225575f);
        EXPECT_FLOAT_EQ(result.W, 0.7302967433f);
    }
#ifdef __cplusplus
    {
        hmm_quaternion result = HMM_Normalize(q);
        EXPECT_FLOAT_EQ(result.X, 0.1825741858f);
        EXPECT_FLOAT_EQ(result.Y, 0.3651483717f);
        EXPECT_FLOAT_EQ(result.Z, 0.5477225575f);
        EXPECT_FLOAT_EQ(result.W, 0.7302967433f);
    }
#endif
}

TEST(QuaternionOps, NLerp)
{
    hmm_quaternion from = HMM_Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
    hmm_quaternion to = HMM_Quaternion(0.5f, 0.5f, -0.5f, 0.5f);

    hmm_quaternion result = HMM_NLerp(from, 0.5f, to);
    EXPECT_FLOAT_EQ(result.X, 0.28867513f);
    EXPECT_FLOAT_EQ(result.Y, 0.28867513f);
    EXPECT_FLOAT_EQ(result.Z, -0.28867513f);
    EXPECT_FLOAT_EQ(result.W, 0.86602540f);
}

TEST(QuaternionOps, Slerp)
{
    hmm_quaternion from = HMM_Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
    hmm_quaternion to = HMM_Quaternion(0.5f, 0.5f, -0.5f, 0.5f);

    hmm_quaternion result = HMM_Slerp(from, 0.5f, to);
    EXPECT_FLOAT_EQ(result.X, 0.28867513f);
    EXPECT_FLOAT_EQ(result.Y, 0.28867513f);
    EXPECT_FLOAT_EQ(result.Z, -0.28867513f);
    EXPECT_FLOAT_EQ(result.W, 0.86602540f);
}

TEST(QuaternionOps, ToMat4)
{
    const float abs_error = 0.0001f;

    {
        // Identity quaternion
        hmm_quaternion rot = HMM_Quaternion(0.0f, 0.0f, 0.0f, 1.0f);

        hmm_mat4 result = HMM_QuaternionToMat4(rot);

        EXPECT_NEAR(result.Elements[0][0], 1.0f, abs_error);
        EXPECT_NEAR(result.Elements[0][1], 0.0f, abs_error);
        EXPECT_NEAR(result.Elements[0][2], 0.0f, abs_error);
        EXPECT_NEAR(result.Elements[0][3], 0.0f, abs_error);

        EXPECT_NEAR(result.Elements[1][0], 0.0f, abs_error);
        EXPECT_NEAR(result.Elements[1][1], 1.0f, abs_error);
        EXPECT_NEAR(result.Elements[1][2], 0.0f, abs_error);
        EXPECT_NEAR(result.Elements[1][3], 0.0f, abs_error);

        EXPECT_NEAR(result.Elements[2][0], 0.0f, abs_error);
        EXPECT_NEAR(result.Elements[2][1], 0.0f, abs_error);
        EXPECT_NEAR(result.Elements[2][2], 1.0f, abs_error);
        EXPECT_NEAR(result.Elements[2][3], 0.0f, abs_error);

        EXPECT_NEAR(result.Elements[3][0], 0.0f, abs_error);
        EXPECT_NEAR(result.Elements[3][1], 0.0f, abs_error);
        EXPECT_NEAR(result.Elements[3][2], 0.0f, abs_error);
        EXPECT_NEAR(result.Elements[3][3], 1.0f, abs_error);
    }

    {
        // Straightforward 90 degree rotation
        hmm_quaternion rot = HMM_Quaternion(0.707107f, 0.0f, 0.0f, 0.707107f);

        hmm_mat4 result = HMM_QuaternionToMat4(rot);

        EXPECT_NEAR(result.Elements[0][0], 1.0f, abs_error);
        EXPECT_NEAR(result.Elements[0][1], 0.0f, abs_error);
        EXPECT_NEAR(result.Elements[0][2], 0.0f, abs_error);
        EXPECT_NEAR(result.Elements[0][3], 0.0f, abs_error);

        EXPECT_NEAR(result.Elements[1][0], 0.0f, abs_error);
        EXPECT_NEAR(result.Elements[1][1], 0.0f, abs_error);
        EXPECT_NEAR(result.Elements[1][2], 1.0f, abs_error);
        EXPECT_NEAR(result.Elements[1][3], 0.0f, abs_error);

        EXPECT_NEAR(result.Elements[2][0], 0.0f, abs_error);
        EXPECT_NEAR(result.Elements[2][1], -1.0f, abs_error);
        EXPECT_NEAR(result.Elements[2][2], 0.0f, abs_error);
        EXPECT_NEAR(result.Elements[2][3], 0.0f, abs_error);

        EXPECT_NEAR(result.Elements[3][0], 0.0f, abs_error);
        EXPECT_NEAR(result.Elements[3][1], 0.0f, abs_error);
        EXPECT_NEAR(result.Elements[3][2], 0.0f, abs_error);
        EXPECT_NEAR(result.Elements[3][3], 1.0f, abs_error);
    }
}

TEST(QuaternionOps, FromAxisAngle)
{
    hmm_vec3 axis = HMM_Vec3(1.0f, 0.0f, 0.0f);
    float angle = HMM_PI32 / 2.0f;

    hmm_quaternion result = HMM_QuaternionFromAxisAngle(axis, angle);
    EXPECT_NEAR(result.X, 0.707107f, FLT_EPSILON * 2);
    EXPECT_FLOAT_EQ(result.Y, 0.0f);
    EXPECT_FLOAT_EQ(result.Z, 0.0f);
    EXPECT_NEAR(result.W, 0.707107f, FLT_EPSILON * 2);
}