#include "../HandmadeTest.h"

TEST(InvMatrix, Transpose)
{
    {
        HMM_Mat2 Matrix = {
            1.0f, 3.0f,
            2.0f, 4.0f,
        };
        HMM_Mat2 Expect = {
            1.0f, 2.0f,
            3.0f, 4.0f,
        };

        {
            HMM_Mat2 result = HMM_TransposeM2(Matrix);
            EXPECT_FLOAT_EQ(result.Elements[0][0], Expect.Elements[0][0]);
            EXPECT_FLOAT_EQ(result.Elements[0][1], Expect.Elements[0][1]);
            EXPECT_FLOAT_EQ(result.Elements[1][0], Expect.Elements[1][0]);
            EXPECT_FLOAT_EQ(result.Elements[1][1], Expect.Elements[1][1]);
        }
#ifdef __cplusplus
        {
            HMM_Mat2 result = HMM_Transpose(Matrix);
            EXPECT_FLOAT_EQ(result.Elements[0][0], Expect.Elements[0][0]);
            EXPECT_FLOAT_EQ(result.Elements[0][1], Expect.Elements[0][1]);
            EXPECT_FLOAT_EQ(result.Elements[1][0], Expect.Elements[1][0]);
            EXPECT_FLOAT_EQ(result.Elements[1][1], Expect.Elements[1][1]);
        }
#endif
    }

    {
        HMM_Mat3 Matrix = {
            1.0f, 4.0f, 7.0f,
            2.0f, 5.0f, 8.0f,
            3.0f, 6.0f, 9.0f,
        };
        HMM_Mat3 Expect = {
            1.0f, 2.0f, 3.0f,
            4.0f, 5.0f, 6.0f,
            7.0f, 8.0f, 9.0f
        };

        {
            HMM_Mat3 result = HMM_TransposeM3(Matrix);
            EXPECT_FLOAT_EQ(result.Elements[0][0], Expect.Elements[0][0]);
            EXPECT_FLOAT_EQ(result.Elements[0][1], Expect.Elements[0][1]);
            EXPECT_FLOAT_EQ(result.Elements[0][2], Expect.Elements[0][2]);
            EXPECT_FLOAT_EQ(result.Elements[1][0], Expect.Elements[1][0]);
            EXPECT_FLOAT_EQ(result.Elements[1][1], Expect.Elements[1][1]);
            EXPECT_FLOAT_EQ(result.Elements[1][2], Expect.Elements[1][2]);
            EXPECT_FLOAT_EQ(result.Elements[2][0], Expect.Elements[2][0]);
            EXPECT_FLOAT_EQ(result.Elements[2][1], Expect.Elements[2][1]);
            EXPECT_FLOAT_EQ(result.Elements[2][2], Expect.Elements[2][2]);
        }
#ifdef __cplusplus
        {
            HMM_Mat3 result = HMM_Transpose(Matrix);
            EXPECT_FLOAT_EQ(result.Elements[0][0], Expect.Elements[0][0]);
            EXPECT_FLOAT_EQ(result.Elements[0][1], Expect.Elements[0][1]);
            EXPECT_FLOAT_EQ(result.Elements[0][2], Expect.Elements[0][2]);
            EXPECT_FLOAT_EQ(result.Elements[1][0], Expect.Elements[1][0]);
            EXPECT_FLOAT_EQ(result.Elements[1][1], Expect.Elements[1][1]);
            EXPECT_FLOAT_EQ(result.Elements[1][2], Expect.Elements[1][2]);
            EXPECT_FLOAT_EQ(result.Elements[2][0], Expect.Elements[2][0]);
            EXPECT_FLOAT_EQ(result.Elements[2][1], Expect.Elements[2][1]);
            EXPECT_FLOAT_EQ(result.Elements[2][2], Expect.Elements[2][2]);
        }
#endif
    }
    {
        HMM_Mat4 Matrix = {
            1.0f, 5.0f,  9.0f, 13.0f,
            2.0f, 6.0f, 10.0f, 14.0f, 
            3.0f, 7.0f, 11.0f, 15.0f,
            4.0f, 8.0f, 12.0f, 16.0f
        };
        HMM_Mat4 Expect = {
            1.0f, 2.0f, 3.0f, 4.0f,
            5.0f, 6.0f, 7.0f, 8.0f,
            9.0f, 10.0f, 11.0f, 12.0f,
            13.0f, 14.0f, 15.0f, 16.0f,
        };
        {
            HMM_Mat4 result = HMM_TransposeM4(Matrix);
            EXPECT_FLOAT_EQ(result.Elements[0][0], Expect.Elements[0][0]);
            EXPECT_FLOAT_EQ(result.Elements[0][1], Expect.Elements[0][1]);
            EXPECT_FLOAT_EQ(result.Elements[0][2], Expect.Elements[0][2]);
            EXPECT_FLOAT_EQ(result.Elements[1][0], Expect.Elements[1][0]);
            EXPECT_FLOAT_EQ(result.Elements[1][1], Expect.Elements[1][1]);
            EXPECT_FLOAT_EQ(result.Elements[1][2], Expect.Elements[1][2]);
            EXPECT_FLOAT_EQ(result.Elements[2][0], Expect.Elements[2][0]);
            EXPECT_FLOAT_EQ(result.Elements[2][1], Expect.Elements[2][1]);
            EXPECT_FLOAT_EQ(result.Elements[2][2], Expect.Elements[2][2]);
        }
#ifdef __cplusplus
        {
            HMM_Mat4 result = HMM_Transpose(Matrix);
            EXPECT_FLOAT_EQ(result.Elements[0][0], Expect.Elements[0][0]);
            EXPECT_FLOAT_EQ(result.Elements[0][1], Expect.Elements[0][1]);
            EXPECT_FLOAT_EQ(result.Elements[0][2], Expect.Elements[0][2]);
            EXPECT_FLOAT_EQ(result.Elements[1][0], Expect.Elements[1][0]);
            EXPECT_FLOAT_EQ(result.Elements[1][1], Expect.Elements[1][1]);
            EXPECT_FLOAT_EQ(result.Elements[1][2], Expect.Elements[1][2]);
            EXPECT_FLOAT_EQ(result.Elements[2][0], Expect.Elements[2][0]);
            EXPECT_FLOAT_EQ(result.Elements[2][1], Expect.Elements[2][1]);
            EXPECT_FLOAT_EQ(result.Elements[2][2], Expect.Elements[2][2]);
        }
#endif
    }

}

TEST(InvMatrix, InvGeneral)
{
    {
        HMM_Mat4 Matrix = {
            12.0f, 2.0f, 1.0f, 1.0f,
            0.0f, 0.0f, 1.0f, 1.0f,
            0.0f, 1.0f, 5.0f, 1.0f,
            11.0f, 1.0f, 0.0f, 10.0f
        };

        HMM_Mat4 Expect = HMM_M4D(1.0);
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

#ifdef __cplusplus
        Inverse = HMM_InvGeneral(Matrix);
        Result = HMM_Mul(Matrix, Inverse);
        
        Det = HMM_Determinant(Matrix);
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
#endif
    }

    {
        HMM_Mat3 Matrix = {
            12.0f, 2.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 1.0f, 5.0f
        };

        HMM_Mat3 Expect = HMM_M3D(1.0);
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

#ifdef __cplusplus
        Inverse = HMM_InvGeneral(Matrix);
        Result = HMM_Mul(Matrix, Inverse);
        Det = HMM_Determinant(Matrix);
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
#endif
    }

    {
        HMM_Mat2 Matrix = {
            12.0f, 2.0f, 
             1.0f, 5.0f
        };

        HMM_Mat2 Expect = HMM_M2D(1.0);
        HMM_Mat2 Inverse = HMM_InvGeneralM2(Matrix);
        HMM_Mat2 Result = HMM_MulM2(Matrix, Inverse);
        
        float Det = HMM_DeterminantM2(Matrix);
        EXPECT_FLOAT_EQ(Det, 58.0f);

        EXPECT_FLOAT_EQ(Result.Elements[0][0], Expect.Elements[0][0]);
        EXPECT_FLOAT_EQ(Result.Elements[0][1], Expect.Elements[0][1]);
        EXPECT_FLOAT_EQ(Result.Elements[1][0], Expect.Elements[1][0]);
        EXPECT_FLOAT_EQ(Result.Elements[1][1], Expect.Elements[1][1]);

#ifdef __cplusplus
        Inverse = HMM_InvGeneral(Matrix);
        Result = HMM_Mul(Matrix, Inverse);
        Det = HMM_Determinant(Matrix);
        EXPECT_FLOAT_EQ(Det, 58.0f);

        EXPECT_FLOAT_EQ(Result.Elements[0][0], Expect.Elements[0][0]);
        EXPECT_FLOAT_EQ(Result.Elements[0][1], Expect.Elements[0][1]);
        EXPECT_FLOAT_EQ(Result.Elements[1][0], Expect.Elements[1][0]);
        EXPECT_FLOAT_EQ(Result.Elements[1][1], Expect.Elements[1][1]);
#endif
    }    
}

TEST(InvMatrix, Mat4Inverses)
{
    {
        HMM_Mat4 Matrix = HMM_Orthographic_N0_RH(-160+100, 160+100, -90+200, 90+200, 10, 10000);
        HMM_Mat4 Expect = HMM_M4D(1.0f);
        HMM_Mat4 Inverse = HMM_InvOrthographic(Matrix);
        HMM_Mat4 Result = HMM_MulM4(Matrix, Inverse);
        
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
        HMM_Mat4 Matrix = HMM_Perspective_N0_RH(HMM_AngleDeg(120), 16.0/9.0, 10, 10000);
        HMM_Mat4 Expect = HMM_M4D(1.0f);
        HMM_Mat4 Inverse = HMM_InvPerspective(Matrix);
        HMM_Mat4 Result = HMM_MulM4(Matrix, Inverse);

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
        HMM_Vec3 Eye = {10.0f, 10.0f, 10.0f};
        HMM_Vec3 Center = {100.0f, 200.0f, 30.0f};
        HMM_Vec3 Up = {0.0f, 0.0f, 1.0f};
        HMM_Mat4 Matrix = HMM_LookAt_RH(Eye, Center, Up);
        HMM_Mat4 Expect = HMM_M4D(1.0f);
        HMM_Mat4 Inverse = HMM_InvLookAt(Matrix);
        HMM_Mat4 Result = HMM_MulM4(Matrix, Inverse);

        EXPECT_NEAR(Result.Elements[0][0], Expect.Elements[0][0], 0.001f);
        EXPECT_NEAR(Result.Elements[0][1], Expect.Elements[0][1], 0.001f);
        EXPECT_NEAR(Result.Elements[0][2], Expect.Elements[0][2], 0.001f);
        EXPECT_NEAR(Result.Elements[0][3], Expect.Elements[0][3], 0.001f);

        EXPECT_NEAR(Result.Elements[1][0], Expect.Elements[1][0], 0.001f);
        EXPECT_NEAR(Result.Elements[1][1], Expect.Elements[1][1], 0.001f);
        EXPECT_NEAR(Result.Elements[1][2], Expect.Elements[1][2], 0.001f);
        EXPECT_NEAR(Result.Elements[1][3], Expect.Elements[1][3], 0.001f);

        EXPECT_NEAR(Result.Elements[2][0], Expect.Elements[2][0], 0.001f);
        EXPECT_NEAR(Result.Elements[2][1], Expect.Elements[2][1], 0.001f);
        EXPECT_NEAR(Result.Elements[2][2], Expect.Elements[2][2], 0.001f);
        EXPECT_NEAR(Result.Elements[2][3], Expect.Elements[2][3], 0.001f);

        EXPECT_NEAR(Result.Elements[3][0], Expect.Elements[3][0], 0.001f);
        EXPECT_NEAR(Result.Elements[3][1], Expect.Elements[3][1], 0.001f);
        EXPECT_NEAR(Result.Elements[3][2], Expect.Elements[3][2], 0.001f);
        EXPECT_NEAR(Result.Elements[3][3], Expect.Elements[3][3], 0.001f);        
    }
    {
        HMM_Vec3 Axis = {1.0f, -1.0f, 0.5f};
        HMM_Mat4 Matrix = HMM_Rotate_RH(HMM_AngleDeg(30), HMM_NormV3(Axis));
        HMM_Mat4 Expect = HMM_M4D(1.0f);
        HMM_Mat4 Inverse = HMM_InvRotate(Matrix);
        HMM_Mat4 Result = HMM_MulM4(Matrix, Inverse);

        EXPECT_NEAR(Result.Elements[0][0], Expect.Elements[0][0], 0.001f);
        EXPECT_NEAR(Result.Elements[0][1], Expect.Elements[0][1], 0.001f);
        EXPECT_NEAR(Result.Elements[0][2], Expect.Elements[0][2], 0.001f);
        EXPECT_NEAR(Result.Elements[0][3], Expect.Elements[0][3], 0.001f);

        EXPECT_NEAR(Result.Elements[1][0], Expect.Elements[1][0], 0.001f);
        EXPECT_NEAR(Result.Elements[1][1], Expect.Elements[1][1], 0.001f);
        EXPECT_NEAR(Result.Elements[1][2], Expect.Elements[1][2], 0.001f);
        EXPECT_NEAR(Result.Elements[1][3], Expect.Elements[1][3], 0.001f);

        EXPECT_NEAR(Result.Elements[2][0], Expect.Elements[2][0], 0.001f);
        EXPECT_NEAR(Result.Elements[2][1], Expect.Elements[2][1], 0.001f);
        EXPECT_NEAR(Result.Elements[2][2], Expect.Elements[2][2], 0.001f);
        EXPECT_NEAR(Result.Elements[2][3], Expect.Elements[2][3], 0.001f);

        EXPECT_NEAR(Result.Elements[3][0], Expect.Elements[3][0], 0.001f);
        EXPECT_NEAR(Result.Elements[3][1], Expect.Elements[3][1], 0.001f);
        EXPECT_NEAR(Result.Elements[3][2], Expect.Elements[3][2], 0.001f);
        EXPECT_NEAR(Result.Elements[3][3], Expect.Elements[3][3], 0.001f);        
    }
    {
        HMM_Vec3 Scale  = {1.0f, -1.0f, 0.5f};
        HMM_Mat4 Matrix = HMM_Scale(Scale);
        HMM_Mat4 Expect = HMM_M4D(1.0f);
        HMM_Mat4 Inverse = HMM_InvScale(Matrix);
        HMM_Mat4 Result = HMM_MulM4(Matrix, Inverse);

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
        HMM_Vec3 Move  = {1.0f, -1.0f, 0.5f};
        HMM_Mat4 Matrix = HMM_Translate(Move);
        HMM_Mat4 Expect = HMM_M4D(1.0f);
        HMM_Mat4 Inverse = HMM_InvTranslate(Matrix);
        HMM_Mat4 Result = HMM_MulM4(Matrix, Inverse);

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
}
