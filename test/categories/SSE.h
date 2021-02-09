#include "../HandmadeTest.h"

#ifdef HANDMADE_MATH__USE_SSE

TEST(SSE, LinearCombine)
{
    hmm_mat4 MatrixOne = HMM_Mat4d(2.0f);
    hmm_mat4 MatrixTwo = HMM_Mat4d(4.0f);
    hmm_mat4 Result;

    Result.Vectors[0] = HMM_LinearCombineSSE(MatrixOne.Vectors[0], MatrixTwo);
    Result.Vectors[1] = HMM_LinearCombineSSE(MatrixOne.Vectors[1], MatrixTwo);
    Result.Vectors[2] = HMM_LinearCombineSSE(MatrixOne.Vectors[2], MatrixTwo);
    Result.Vectors[3] = HMM_LinearCombineSSE(MatrixOne.Vectors[3], MatrixTwo);

    {
        EXPECT_FLOAT_EQ(Result.Elements[0][0], 8.0f);
        EXPECT_FLOAT_EQ(Result.Elements[0][1], 0.0f);
        EXPECT_FLOAT_EQ(Result.Elements[0][2], 0.0f);
        EXPECT_FLOAT_EQ(Result.Elements[0][3], 0.0f);

        EXPECT_FLOAT_EQ(Result.Elements[1][0], 0.0f);
        EXPECT_FLOAT_EQ(Result.Elements[1][1], 8.0f);
        EXPECT_FLOAT_EQ(Result.Elements[1][2], 0.0f);
        EXPECT_FLOAT_EQ(Result.Elements[1][3], 0.0f);

        EXPECT_FLOAT_EQ(Result.Elements[2][0], 0.0f);
        EXPECT_FLOAT_EQ(Result.Elements[2][1], 0.0f);
        EXPECT_FLOAT_EQ(Result.Elements[2][2], 8.0f);
        EXPECT_FLOAT_EQ(Result.Elements[2][3], 0.0f);

        EXPECT_FLOAT_EQ(Result.Elements[3][0], 0.0f);
        EXPECT_FLOAT_EQ(Result.Elements[3][1], 0.0f);
        EXPECT_FLOAT_EQ(Result.Elements[3][2], 0.0f);
        EXPECT_FLOAT_EQ(Result.Elements[3][3], 8.0f);
    }
}

#endif
