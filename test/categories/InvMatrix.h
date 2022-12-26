#include "../HandmadeTest.h"

TEST(InvMatrix, InvGeneral)
{
    {
        HMM_Mat4 Matrix = {
            12.0f, 2.0f, 1.0f, 1.0f,
            0.0f, 0.0f, 1.0f, 1.0f,
            0.0f, 1.0f, 5.0f, 1.0f,
            11.0f, 1.0f, 0.0f, 10.0f
        };

        HMM_Mat4 Expect = HMM_M4d(1.0);
        HMM_Mat4 Inverse = HMM_InvGeneralM4(Matrix);
        HMM_Mat4 Result = HMM_MulM4(Matrix, Inverse);
        
        float Det = HMM_DeterminantM4(Matrix);
        EXPECT_FLOAT_EQ(Det, -80.0f);

        EXPECT_FLOAT_EQ(Result.Elements[0][0], Expect.Elements[0][0]);
        EXPECT_FLOAT_EQ(Result.Elements[0][1], Expect.Elements[0][1]);
        EXPECT_FLOAT_EQ(Result.Elements[0][2], Expect.Elements[0][2]);
        EXPECT_FLOAT_EQ(Result.Elements[0][3], Expect.Elements[0][3]);

        EXPECT_FLOAT_EQ(Result.Elements[1][0], Expect.Elements[1][0]);
        EXPECT_FLOAT_EQ(Result.Elements[1][1], Expect.Elements[1][1]);
        EXPECT_FLOAT_EQ(Result.Elements[1][2], Expect.Elements[1][2]);
        EXPECT_FLOAT_EQ(Result.Elements[1][3], Expect.Elements[1][3]);

        EXPECT_FLOAT_EQ(Result.Elements[2][0], Expect.Elements[2][0]);
        EXPECT_FLOAT_EQ(Result.Elements[2][1], Expect.Elements[2][1]);
        EXPECT_FLOAT_EQ(Result.Elements[2][2], Expect.Elements[2][2]);
        EXPECT_FLOAT_EQ(Result.Elements[2][3], Expect.Elements[2][3]);

        EXPECT_FLOAT_EQ(Result.Elements[3][0], Expect.Elements[3][0]);
        EXPECT_FLOAT_EQ(Result.Elements[3][1], Expect.Elements[3][1]);
        EXPECT_FLOAT_EQ(Result.Elements[3][2], Expect.Elements[3][2]);
        EXPECT_FLOAT_EQ(Result.Elements[3][3], Expect.Elements[3][3]);
    }

    {
        HMM_Mat3 Matrix = {
            12.0f, 2.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 1.0f, 5.0f
        };

        HMM_Mat3 Expect = HMM_M3d(1.0);
        HMM_Mat3 Inverse = HMM_InvGeneralM3(Matrix);
        HMM_Mat3 Result = HMM_MulM3(Matrix, Inverse);
        
        float Det = HMM_DeterminantM3(Matrix);
        EXPECT_FLOAT_EQ(Det, -12.0f);

        EXPECT_FLOAT_EQ(Result.Elements[0][0], Expect.Elements[0][0]);
        EXPECT_FLOAT_EQ(Result.Elements[0][1], Expect.Elements[0][1]);
        EXPECT_FLOAT_EQ(Result.Elements[0][2], Expect.Elements[0][2]);

        EXPECT_FLOAT_EQ(Result.Elements[1][0], Expect.Elements[1][0]);
        EXPECT_FLOAT_EQ(Result.Elements[1][1], Expect.Elements[1][1]);
        EXPECT_FLOAT_EQ(Result.Elements[1][2], Expect.Elements[1][2]);

        EXPECT_FLOAT_EQ(Result.Elements[2][0], Expect.Elements[2][0]);
        EXPECT_FLOAT_EQ(Result.Elements[2][1], Expect.Elements[2][1]);
        EXPECT_FLOAT_EQ(Result.Elements[2][2], Expect.Elements[2][2]);

    }

    
    {
        HMM_Mat2 Matrix = {
            12.0f, 2.0f, 
             1.0f, 5.0f
        };

        HMM_Mat2 Expect = HMM_M2d(1.0);
        HMM_Mat2 Inverse = HMM_InvGeneralM2(Matrix);
        HMM_Mat2 Result = HMM_MulM2(Matrix, Inverse);
        
        float Det = HMM_DeterminantM2(Matrix);
        EXPECT_FLOAT_EQ(Det, 58.0f);

        EXPECT_FLOAT_EQ(Result.Elements[0][0], Expect.Elements[0][0]);
        EXPECT_FLOAT_EQ(Result.Elements[0][1], Expect.Elements[0][1]);

        EXPECT_FLOAT_EQ(Result.Elements[1][0], Expect.Elements[1][0]);
        EXPECT_FLOAT_EQ(Result.Elements[1][1], Expect.Elements[1][1]);

    }    
}

TEST(InvMatrix, Mat4Inverses)
{
    /* TODO */
}
