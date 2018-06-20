#include "../HandmadeTest.h"

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

TEST(MatrixOps, ToQuaternion)
{
    hmm_mat4 rotateY = {
        0.0f, 0.0f, -1.0f, 0.0f, // first column (X)
        0.0f, 1.0f, 0.0f, 0.0f, // second column (Y)
        1.0f, 0.0f, 0.0f, 0.0f, // third column (Z)
        0.0f, 0.0f, 0.0f, 1.0f
    };
    
    hmm_quaternion expected = HMM_QuaternionFromAxisAngle(HMM_Vec3(0.0f, 1.0f, 0.0f), HMM_ToRadians(90.0f));
    hmm_quaternion actualResult = HMM_Mat4ToQuaternion(rotateY);

    printf("%f %f %f %f\n", expected.X, expected.Y, expected.Z, expected.W);

    EXPECT_FLOAT_EQ(actualResult.X, expected.X);
    EXPECT_FLOAT_EQ(actualResult.Y, expected.Y);
    EXPECT_FLOAT_EQ(actualResult.Z, expected.Z);
    EXPECT_FLOAT_EQ(actualResult.W, expected.W);
}
