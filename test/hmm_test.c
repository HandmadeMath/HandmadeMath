#include <float.h>

#include "HandmadeTest.h"
#include "../HandmadeMath.h"

int run_tests();

int main()
{
    run_tests();

    if (hmt_count_failedtests > 0) {
        printf(RED);
    } else {
        printf(GREEN);
    }
    printf("\n%d/%d tests passed overall, %d failures\n" RESET, hmt_count_tests - hmt_count_failedtests, hmt_count_tests, hmt_count_failures);

    printf("\n");

    return (hmt_count_failedtests > 0);
}

int run_tests()
{
    CATEGORY_BEGIN(ScalarMath)
    {
        TEST_BEGIN(Trigonometry)
        {
            // We have to be a little looser with our equality constraint
            // because of floating-point precision issues.
            const float trigAbsError = 0.0001f;

            EXPECT_NEAR(HMM_SinF(0.0f), 0.0f, trigAbsError);
            EXPECT_NEAR(HMM_SinF(HMM_PI32 / 2), 1.0f, trigAbsError);
            EXPECT_NEAR(HMM_SinF(HMM_PI32), 0.0f, trigAbsError);
            EXPECT_NEAR(HMM_SinF(3 * HMM_PI32 / 2), -1.0f, trigAbsError);
            EXPECT_NEAR(HMM_SinF(-HMM_PI32 / 2), -1.0f, trigAbsError);

            EXPECT_NEAR(HMM_CosF(0.0f), 1.0f, trigAbsError);
            EXPECT_NEAR(HMM_CosF(HMM_PI32 / 2), 0.0f, trigAbsError);
            EXPECT_NEAR(HMM_CosF(HMM_PI32), -1.0f, trigAbsError);
            EXPECT_NEAR(HMM_CosF(3 * HMM_PI32 / 2), 0.0f, trigAbsError);
            EXPECT_NEAR(HMM_CosF(-HMM_PI32), -1.0f, trigAbsError);

            EXPECT_NEAR(HMM_TanF(0.0f), 0.0f, trigAbsError);
            EXPECT_NEAR(HMM_TanF(HMM_PI32 / 4), 1.0f, trigAbsError);
            EXPECT_NEAR(HMM_TanF(3 * HMM_PI32 / 4), -1.0f, trigAbsError);
            EXPECT_NEAR(HMM_TanF(HMM_PI32), 0.0f, trigAbsError);
            EXPECT_NEAR(HMM_TanF(-HMM_PI32 / 4), -1.0f, trigAbsError);

            // This isn't the most rigorous because we're really just sanity-
            // checking that things work by default.
        }
        TEST_END()

        TEST_BEGIN(ToRadians)
        {
            EXPECT_FLOAT_EQ(HMM_ToRadians(0.0f), 0.0f);
            EXPECT_FLOAT_EQ(HMM_ToRadians(180.0f), HMM_PI32);
            EXPECT_FLOAT_EQ(HMM_ToRadians(-180.0f), -HMM_PI32);
        }
        TEST_END()

        TEST_BEGIN(SquareRoot)
        {
            EXPECT_FLOAT_EQ(HMM_SquareRootF(16.0f), 4.0f);
        }
        TEST_END()

        TEST_BEGIN(RSquareRootF)
        {
            EXPECT_NEAR(HMM_RSquareRootF(10.0f), 0.31616211f, 0.0001f);
        }
        TEST_END()

        TEST_BEGIN(Power)
        {
            EXPECT_FLOAT_EQ(HMM_Power(2.0f, 0), 1.0f);
            EXPECT_FLOAT_EQ(HMM_Power(2.0f, 4), 16.0f);       
            EXPECT_FLOAT_EQ(HMM_Power(2.0f, -2), 0.25f);
        }
        TEST_END()

        TEST_BEGIN(PowerF)
        {
            EXPECT_FLOAT_EQ(HMM_PowerF(2.0f, 0), 1.0f);
            EXPECT_NEAR(HMM_PowerF(2.0f, 4.1), 17.148376f, 0.0001f);
            EXPECT_NEAR(HMM_PowerF(2.0f, -2.5), 0.176777f, 0.0001f);
        }
        TEST_END()

        TEST_BEGIN(Lerp)
        {
            EXPECT_FLOAT_EQ(HMM_Lerp(-2.0f, 0.0f, 2.0f), -2.0f);        
            EXPECT_FLOAT_EQ(HMM_Lerp(-2.0f, 0.5f, 2.0f), 0.0f);        
            EXPECT_FLOAT_EQ(HMM_Lerp(-2.0f, 1.0f, 2.0f), 2.0f);
        }
        TEST_END()

        TEST_BEGIN(Clamp)
        {
            EXPECT_FLOAT_EQ(HMM_Clamp(-2.0f, 0.0f, 2.0f), 0.0f);        
            EXPECT_FLOAT_EQ(HMM_Clamp(-2.0f, -3.0f, 2.0f), -2.0f);        
            EXPECT_FLOAT_EQ(HMM_Clamp(-2.0f, 3.0f, 2.0f), 2.0f);
        }
        TEST_END()
    }
    CATEGORY_END()

    CATEGORY_BEGIN(Initialization)
    {
        TEST_BEGIN(Vectors)
        {
            //
            // Test vec2
            // 
            hmm_vec2 v2 = HMM_Vec2(1.0f, 2.0f);
            hmm_vec2 v2i = HMM_Vec2(1, 2);

            EXPECT_FLOAT_EQ(v2.X, 1.0f);
            EXPECT_FLOAT_EQ(v2.Y, 2.0f);
            EXPECT_FLOAT_EQ(v2.U, 1.0f);
            EXPECT_FLOAT_EQ(v2.V, 2.0f);
            EXPECT_FLOAT_EQ(v2.Left, 1.0f);
            EXPECT_FLOAT_EQ(v2.Right, 2.0f);
            EXPECT_FLOAT_EQ(v2.Width, 1.0f);
            EXPECT_FLOAT_EQ(v2.Height, 2.0f);
            EXPECT_FLOAT_EQ(v2.Elements[0], 1.0f);
            EXPECT_FLOAT_EQ(v2.Elements[1], 2.0f);

            EXPECT_FLOAT_EQ(v2i.X, 1.0f);
            EXPECT_FLOAT_EQ(v2i.Y, 2.0f);
            EXPECT_FLOAT_EQ(v2i.U, 1.0f);
            EXPECT_FLOAT_EQ(v2i.V, 2.0f);
            EXPECT_FLOAT_EQ(v2i.Left, 1.0f);
            EXPECT_FLOAT_EQ(v2i.Right, 2.0f);
            EXPECT_FLOAT_EQ(v2i.Width, 1.0f);
            EXPECT_FLOAT_EQ(v2i.Height, 2.0f);
            EXPECT_FLOAT_EQ(v2i.Elements[0], 1.0f);
            EXPECT_FLOAT_EQ(v2i.Elements[1], 2.0f);

            //
            // Test vec3
            //
            hmm_vec3 v3 = HMM_Vec3(1.0f, 2.0f, 3.0f);
            hmm_vec3 v3i = HMM_Vec3i(1, 2, 3);

            EXPECT_FLOAT_EQ(v3.X, 1.0f);
            EXPECT_FLOAT_EQ(v3.Y, 2.0f);
            EXPECT_FLOAT_EQ(v3.Z, 3.0f);
            EXPECT_FLOAT_EQ(v3.U, 1.0f);
            EXPECT_FLOAT_EQ(v3.V, 2.0f);
            EXPECT_FLOAT_EQ(v3.W, 3.0f);
            EXPECT_FLOAT_EQ(v3.R, 1.0f);
            EXPECT_FLOAT_EQ(v3.G, 2.0f);
            EXPECT_FLOAT_EQ(v3.B, 3.0f);
            EXPECT_FLOAT_EQ(v3.Elements[0], 1.0f);
            EXPECT_FLOAT_EQ(v3.Elements[1], 2.0f);
            EXPECT_FLOAT_EQ(v3.Elements[2], 3.0f);
            EXPECT_FLOAT_EQ(v3.XY.Elements[0], 1.0f);
            EXPECT_FLOAT_EQ(v3.XY.Elements[1], 2.0f);
            EXPECT_FLOAT_EQ(v3.YZ.Elements[0], 2.0f);
            EXPECT_FLOAT_EQ(v3.YZ.Elements[1], 3.0f);
            EXPECT_FLOAT_EQ(v3.UV.Elements[0], 1.0f);
            EXPECT_FLOAT_EQ(v3.UV.Elements[1], 2.0f);
            EXPECT_FLOAT_EQ(v3.VW.Elements[0], 2.0f);
            EXPECT_FLOAT_EQ(v3.VW.Elements[1], 3.0f);

            EXPECT_FLOAT_EQ(v3i.X, 1.0f);
            EXPECT_FLOAT_EQ(v3i.Y, 2.0f);
            EXPECT_FLOAT_EQ(v3i.Z, 3.0f);
            EXPECT_FLOAT_EQ(v3i.U, 1.0f);
            EXPECT_FLOAT_EQ(v3i.V, 2.0f);
            EXPECT_FLOAT_EQ(v3i.W, 3.0f);
            EXPECT_FLOAT_EQ(v3i.R, 1.0f);
            EXPECT_FLOAT_EQ(v3i.G, 2.0f);
            EXPECT_FLOAT_EQ(v3i.B, 3.0f);
            EXPECT_FLOAT_EQ(v3i.Elements[0], 1.0f);
            EXPECT_FLOAT_EQ(v3i.Elements[1], 2.0f);
            EXPECT_FLOAT_EQ(v3i.Elements[2], 3.0f);
            EXPECT_FLOAT_EQ(v3i.XY.Elements[0], 1.0f);
            EXPECT_FLOAT_EQ(v3i.XY.Elements[1], 2.0f);
            EXPECT_FLOAT_EQ(v3i.YZ.Elements[0], 2.0f);
            EXPECT_FLOAT_EQ(v3i.YZ.Elements[1], 3.0f);
            EXPECT_FLOAT_EQ(v3i.UV.Elements[0], 1.0f);
            EXPECT_FLOAT_EQ(v3i.UV.Elements[1], 2.0f);
            EXPECT_FLOAT_EQ(v3i.VW.Elements[0], 2.0f);
            EXPECT_FLOAT_EQ(v3i.VW.Elements[1], 3.0f);

            //
            // Test vec4
            //
            hmm_vec4 v4 = HMM_Vec4(1.0f, 2.0f, 3.0f, 4.0f);
            hmm_vec4 v4i = HMM_Vec4i(1, 2, 3, 4);
            hmm_vec4 v4v = HMM_Vec4v(v3, 4.0f);

            EXPECT_FLOAT_EQ(v4.X, 1.0f);
            EXPECT_FLOAT_EQ(v4.Y, 2.0f);
            EXPECT_FLOAT_EQ(v4.Z, 3.0f);
            EXPECT_FLOAT_EQ(v4.W, 4.0f);
            EXPECT_FLOAT_EQ(v4.R, 1.0f);
            EXPECT_FLOAT_EQ(v4.G, 2.0f);
            EXPECT_FLOAT_EQ(v4.B, 3.0f);
            EXPECT_FLOAT_EQ(v4.A, 4.0f);
            EXPECT_FLOAT_EQ(v4.XY.Elements[0], 1.0f);
            EXPECT_FLOAT_EQ(v4.XY.Elements[1], 2.0f);
            EXPECT_FLOAT_EQ(v4.YZ.Elements[0], 2.0f);
            EXPECT_FLOAT_EQ(v4.YZ.Elements[1], 3.0f);
            EXPECT_FLOAT_EQ(v4.ZW.Elements[0], 3.0f);
            EXPECT_FLOAT_EQ(v4.ZW.Elements[1], 4.0f);
            EXPECT_FLOAT_EQ(v4.XY.Elements[0], 1.0f);
            EXPECT_FLOAT_EQ(v4.XY.Elements[1], 2.0f);
            EXPECT_FLOAT_EQ(v4.XYZ.Elements[0], 1.0f);
            EXPECT_FLOAT_EQ(v4.XYZ.Elements[1], 2.0f);
            EXPECT_FLOAT_EQ(v4.XYZ.Elements[2], 3.0f);
            EXPECT_FLOAT_EQ(v4.RGB.Elements[0], 1.0f);
            EXPECT_FLOAT_EQ(v4.RGB.Elements[1], 2.0f);
            EXPECT_FLOAT_EQ(v4.RGB.Elements[2], 3.0f);

            EXPECT_FLOAT_EQ(v4i.X, 1.0f);
            EXPECT_FLOAT_EQ(v4i.Y, 2.0f);
            EXPECT_FLOAT_EQ(v4i.Z, 3.0f);
            EXPECT_FLOAT_EQ(v4i.W, 4.0f);
            EXPECT_FLOAT_EQ(v4i.R, 1.0f);
            EXPECT_FLOAT_EQ(v4i.G, 2.0f);
            EXPECT_FLOAT_EQ(v4i.B, 3.0f);
            EXPECT_FLOAT_EQ(v4i.A, 4.0f);
            EXPECT_FLOAT_EQ(v4i.XY.Elements[0], 1.0f);
            EXPECT_FLOAT_EQ(v4i.XY.Elements[1], 2.0f);
            EXPECT_FLOAT_EQ(v4i.YZ.Elements[0], 2.0f);
            EXPECT_FLOAT_EQ(v4i.YZ.Elements[1], 3.0f);
            EXPECT_FLOAT_EQ(v4i.ZW.Elements[0], 3.0f);
            EXPECT_FLOAT_EQ(v4i.ZW.Elements[1], 4.0f);
            EXPECT_FLOAT_EQ(v4i.XY.Elements[0], 1.0f);
            EXPECT_FLOAT_EQ(v4i.XY.Elements[1], 2.0f);
            EXPECT_FLOAT_EQ(v4i.XYZ.Elements[0], 1.0f);
            EXPECT_FLOAT_EQ(v4i.XYZ.Elements[1], 2.0f);
            EXPECT_FLOAT_EQ(v4i.XYZ.Elements[2], 3.0f);
            EXPECT_FLOAT_EQ(v4i.RGB.Elements[0], 1.0f);
            EXPECT_FLOAT_EQ(v4i.RGB.Elements[1], 2.0f);
            EXPECT_FLOAT_EQ(v4i.RGB.Elements[2], 3.0f);

            EXPECT_FLOAT_EQ(v4v.X, 1.0f);
            EXPECT_FLOAT_EQ(v4v.Y, 2.0f);
            EXPECT_FLOAT_EQ(v4v.Z, 3.0f);
            EXPECT_FLOAT_EQ(v4v.W, 4.0f);
            EXPECT_FLOAT_EQ(v4v.R, 1.0f);
            EXPECT_FLOAT_EQ(v4v.G, 2.0f);
            EXPECT_FLOAT_EQ(v4v.B, 3.0f);
            EXPECT_FLOAT_EQ(v4v.A, 4.0f);
            EXPECT_FLOAT_EQ(v4v.XY.Elements[0], 1.0f);
            EXPECT_FLOAT_EQ(v4v.XY.Elements[1], 2.0f);
            EXPECT_FLOAT_EQ(v4v.YZ.Elements[0], 2.0f);
            EXPECT_FLOAT_EQ(v4v.YZ.Elements[1], 3.0f);
            EXPECT_FLOAT_EQ(v4v.ZW.Elements[0], 3.0f);
            EXPECT_FLOAT_EQ(v4v.ZW.Elements[1], 4.0f);
            EXPECT_FLOAT_EQ(v4v.XY.Elements[0], 1.0f);
            EXPECT_FLOAT_EQ(v4v.XY.Elements[1], 2.0f);
            EXPECT_FLOAT_EQ(v4v.XYZ.Elements[0], 1.0f);
            EXPECT_FLOAT_EQ(v4v.XYZ.Elements[1], 2.0f);
            EXPECT_FLOAT_EQ(v4v.XYZ.Elements[2], 3.0f);
            EXPECT_FLOAT_EQ(v4v.RGB.Elements[0], 1.0f);
            EXPECT_FLOAT_EQ(v4v.RGB.Elements[1], 2.0f);
            EXPECT_FLOAT_EQ(v4v.RGB.Elements[2], 3.0f);
        }
        TEST_END()

        TEST_BEGIN(MatrixEmpty)
        {
            hmm_mat4 m4 = HMM_Mat4();
            for (int Column = 0; Column < 4; ++Column)
            {
                for (int Row = 0; Row < 4; ++Row)
                {
                    EXPECT_FLOAT_EQ(m4.Elements[Column][Row], 0.0f);
                }
            }
        }
        TEST_END()

        TEST_BEGIN(MatrixDiagonal)
        {
            hmm_mat4 m4d = HMM_Mat4d(1.0f);
            for (int Column = 0; Column < 4; ++Column)
            {
                for (int Row = 0; Row < 4; ++Row)
                {
                    if (Column == Row) {
                        EXPECT_FLOAT_EQ(m4d.Elements[Column][Row], 1.0f);
                    } else {
                        EXPECT_FLOAT_EQ(m4d.Elements[Column][Row], 0.0f);
                    }
                }
            }
        }
        TEST_END()

        TEST_BEGIN(Quaternion)
        {
            hmm_quaternion q = HMM_Quaternion(1.0f, 2.0f, 3.0f, 4.0f);

            EXPECT_FLOAT_EQ(q.X, 1.0f);
            EXPECT_FLOAT_EQ(q.Y, 2.0f);
            EXPECT_FLOAT_EQ(q.Z, 3.0f);
            EXPECT_FLOAT_EQ(q.W, 4.0f);

            EXPECT_FLOAT_EQ(q.Elements[0], 1.0f);
            EXPECT_FLOAT_EQ(q.Elements[1], 2.0f);
            EXPECT_FLOAT_EQ(q.Elements[2], 3.0f);
            EXPECT_FLOAT_EQ(q.Elements[3], 4.0f);

            hmm_vec4 v = HMM_Vec4(1.0f, 2.0f, 3.0f, 4.0f);
            hmm_quaternion qv = HMM_QuaternionV4(v);

            EXPECT_FLOAT_EQ(qv.X, 1.0f);
            EXPECT_FLOAT_EQ(qv.Y, 2.0f);
            EXPECT_FLOAT_EQ(qv.Z, 3.0f);
            EXPECT_FLOAT_EQ(qv.W, 4.0f);
        }
        TEST_END()
    }
    CATEGORY_END()

    CATEGORY_BEGIN(VectorOps)
    {
        TEST_BEGIN(LengthSquared)
        {
            hmm_vec2 v2 = HMM_Vec2(1.0f, -2.0f);
            hmm_vec3 v3 = HMM_Vec3(1.0f, -2.0f, 3.0f); 
            hmm_vec4 v4 = HMM_Vec4(1.0f, -2.0f, 3.0f, 1.0f);

            EXPECT_FLOAT_EQ(HMM_LengthSquaredVec2(v2), 5.0f);
            EXPECT_FLOAT_EQ(HMM_LengthSquaredVec3(v3), 14.0f);
            EXPECT_FLOAT_EQ(HMM_LengthSquaredVec4(v4), 15.0f);

#ifdef HANDMADE_MATH_CPP_MODE
            EXPECT_FLOAT_EQ(HMM_LengthSquared(v2), 5.0f);
            EXPECT_FLOAT_EQ(HMM_LengthSquared(v3), 14.0f);
            EXPECT_FLOAT_EQ(HMM_LengthSquared(v4), 15.0f);
#endif
        }
        TEST_END()

        TEST_BEGIN(Length)
        {
            hmm_vec2 v2 = HMM_Vec2(1.0f, -9.0f);
            hmm_vec3 v3 = HMM_Vec3(2.0f, -3.0f, 6.0f);
            hmm_vec4 v4 = HMM_Vec4(2.0f, -3.0f, 6.0f, 12.0f);

            EXPECT_FLOAT_EQ(HMM_LengthVec2(v2), 9.0553856f);
            EXPECT_FLOAT_EQ(HMM_LengthVec3(v3), 7.0f);
            EXPECT_FLOAT_EQ(HMM_LengthVec4(v4), 13.892444f);

#ifdef HANDMADE_MATH_CPP_MODE
            EXPECT_FLOAT_EQ(HMM_Length(v2), 9.0553856f);
            EXPECT_FLOAT_EQ(HMM_Length(v3), 7.0f);
            EXPECT_FLOAT_EQ(HMM_Length(v4), 13.892444f);
#endif
        }
        TEST_END()

        TEST_BEGIN(Normalize)
        {
            hmm_vec2 v2 = HMM_Vec2(1.0f, -2.0f);
            hmm_vec3 v3 = HMM_Vec3(1.0f, -2.0f, 3.0f); 
            hmm_vec4 v4 = HMM_Vec4(1.0f, -2.0f, 3.0f, -1.0f);

            {
                hmm_vec2 result = HMM_NormalizeVec2(v2);
                EXPECT_FLOAT_EQ(HMM_LengthVec2(result), 1.0f);
                EXPECT_GT(result.X, 0.0f);
                EXPECT_LT(result.Y, 0.0f);
            }
            {
                hmm_vec3 result = HMM_NormalizeVec3(v3);
                EXPECT_FLOAT_EQ(HMM_LengthVec3(result), 1.0f);
                EXPECT_GT(result.X, 0.0f);
                EXPECT_LT(result.Y, 0.0f);
                EXPECT_GT(result.Z, 0.0f);
            }
            {
                hmm_vec4 result = HMM_NormalizeVec4(v4);
                EXPECT_FLOAT_EQ(HMM_LengthVec4(result), 1.0f);
                EXPECT_GT(result.X, 0.0f);
                EXPECT_LT(result.Y, 0.0f);
                EXPECT_GT(result.Z, 0.0f);
                EXPECT_LT(result.W, 0.0f);
            }

#ifdef HANDMADE_MATH_CPP_MODE
            {
                hmm_vec2 result = HMM_Normalize(v2);
                EXPECT_FLOAT_EQ(HMM_LengthVec2(result), 1.0f);
                EXPECT_GT(result.X, 0.0f);
                EXPECT_LT(result.Y, 0.0f);
            }
            {
                hmm_vec3 result = HMM_Normalize(v3);
                EXPECT_FLOAT_EQ(HMM_LengthVec3(result), 1.0f);
                EXPECT_GT(result.X, 0.0f);
                EXPECT_LT(result.Y, 0.0f);
                EXPECT_GT(result.Z, 0.0f);
            }
            {
                hmm_vec4 result = HMM_Normalize(v4);
                EXPECT_FLOAT_EQ(HMM_LengthVec4(result), 1.0f);
                EXPECT_GT(result.X, 0.0f);
                EXPECT_LT(result.Y, 0.0f);
                EXPECT_GT(result.Z, 0.0f);
                EXPECT_LT(result.W, 0.0f);
            }
#endif
        }
        TEST_END()

        TEST_BEGIN(NormalizeZero)
        {
            hmm_vec2 v2 = HMM_Vec2(0.0f, 0.0f);
            hmm_vec3 v3 = HMM_Vec3(0.0f, 0.0f, 0.0f);
            hmm_vec4 v4 = HMM_Vec4(0.0f, 0.0f, 0.0f, 0.0f);

            {
                hmm_vec2 result = HMM_NormalizeVec2(v2);
                EXPECT_FLOAT_EQ(result.X, 0.0f);
                EXPECT_FLOAT_EQ(result.Y, 0.0f);
            }
            {
                hmm_vec3 result = HMM_NormalizeVec3(v3);
                EXPECT_FLOAT_EQ(result.X, 0.0f);
                EXPECT_FLOAT_EQ(result.Y, 0.0f);
                EXPECT_FLOAT_EQ(result.Z, 0.0f);
            }
            {
                hmm_vec4 result = HMM_NormalizeVec4(v4);
                EXPECT_FLOAT_EQ(result.X, 0.0f);
                EXPECT_FLOAT_EQ(result.Y, 0.0f);
                EXPECT_FLOAT_EQ(result.Z, 0.0f);
                EXPECT_FLOAT_EQ(result.W, 0.0f);
            }

#ifdef HANDMADE_MATH_CPP_MODE
            {
                hmm_vec2 result = HMM_Normalize(v2);
                EXPECT_FLOAT_EQ(result.X, 0.0f);
                EXPECT_FLOAT_EQ(result.Y, 0.0f);
            }
            {
                hmm_vec3 result = HMM_Normalize(v3);
                EXPECT_FLOAT_EQ(result.X, 0.0f);
                EXPECT_FLOAT_EQ(result.Y, 0.0f);
                EXPECT_FLOAT_EQ(result.Z, 0.0f);
            }
            {
                hmm_vec4 result = HMM_Normalize(v4);
                EXPECT_FLOAT_EQ(result.X, 0.0f);
                EXPECT_FLOAT_EQ(result.Y, 0.0f);
                EXPECT_FLOAT_EQ(result.Z, 0.0f);
                EXPECT_FLOAT_EQ(result.W, 0.0f);
            }
#endif
        }
        TEST_END()

        TEST_BEGIN(Cross)
        {
            hmm_vec3 v1 = HMM_Vec3(1.0f, 2.0f, 3.0f);
            hmm_vec3 v2 = HMM_Vec3(4.0f, 5.0f, 6.0f);

            hmm_vec3 result = HMM_Cross(v1, v2);

            EXPECT_FLOAT_EQ(result.X, -3.0f);
            EXPECT_FLOAT_EQ(result.Y, 6.0f);
            EXPECT_FLOAT_EQ(result.Z, -3.0f);
        }
        TEST_END()

        TEST_BEGIN(DotVec2)
        {
            hmm_vec2 v1 = HMM_Vec2(1.0f, 2.0f);
            hmm_vec2 v2 = HMM_Vec2(3.0f, 4.0f);

            EXPECT_FLOAT_EQ(HMM_DotVec2(v1, v2), 11.0f);
#ifdef HANDMADE_MATH_CPP_MODE
            EXPECT_FLOAT_EQ(HMM_Dot(v1, v2), 11.0f);
#endif
        }
        TEST_END()

        TEST_BEGIN(DotVec3)
        {
            hmm_vec3 v1 = HMM_Vec3(1.0f, 2.0f, 3.0f);
            hmm_vec3 v2 = HMM_Vec3(4.0f, 5.0f, 6.0f);

            EXPECT_FLOAT_EQ(HMM_DotVec3(v1, v2), 32.0f);
#ifdef HANDMADE_MATH_CPP_MODE
            EXPECT_FLOAT_EQ(HMM_Dot(v1, v2), 32.0f);
#endif
        }
        TEST_END()

        TEST_BEGIN(DotVec4)
        {
            hmm_vec4 v1 = HMM_Vec4(1.0f, 2.0f, 3.0f, 4.0f);
            hmm_vec4 v2 = HMM_Vec4(5.0f, 6.0f, 7.0f, 8.0f);

            EXPECT_FLOAT_EQ(HMM_DotVec4(v1, v2), 70.0f);
#ifdef HANDMADE_MATH_CPP_MODE
            EXPECT_FLOAT_EQ(HMM_Dot(v1, v2), 70.0f);
#endif
        }
        TEST_END()
    }
    CATEGORY_END()

    CATEGORY_BEGIN(MatrixOps)
    {
        TEST_BEGIN(Transpose)
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
        TEST_END()
    }
    CATEGORY_END()

    CATEGORY_BEGIN(QuaternionOps)
    {
        TEST_BEGIN(Inverse)
        {
            hmm_quaternion q1 = HMM_Quaternion(1.0f, 2.0f, 3.0f, 4.0f);
            hmm_quaternion inverse = HMM_InverseQuaternion(q1);

            hmm_quaternion result = HMM_MultiplyQuaternion(q1, inverse);

            EXPECT_FLOAT_EQ(result.X, 0.0f);
            EXPECT_FLOAT_EQ(result.Y, 0.0f);
            EXPECT_FLOAT_EQ(result.Z, 0.0f);
            EXPECT_FLOAT_EQ(result.W, 1.0f);
        }
        TEST_END()

        TEST_BEGIN(Dot)
        {
            hmm_quaternion q1 = HMM_Quaternion(1.0f, 2.0f, 3.0f, 4.0f);
            hmm_quaternion q2 = HMM_Quaternion(5.0f, 6.0f, 7.0f, 8.0f);

            {
                float result = HMM_DotQuaternion(q1, q2);
                EXPECT_FLOAT_EQ(result, 70.0f);
            }
#ifdef HANDMADE_MATH_CPP_MODE
            {
                float result = HMM_Dot(q1, q2);
                EXPECT_FLOAT_EQ(result, 70.0f);
            }
#endif
        }
        TEST_END()

        TEST_BEGIN(Normalize)
        {
            hmm_quaternion q = HMM_Quaternion(1.0f, 2.0f, 3.0f, 4.0f);

            {
                hmm_quaternion result = HMM_NormalizeQuaternion(q);
                EXPECT_FLOAT_EQ(result.X, 0.1825741858f);
                EXPECT_FLOAT_EQ(result.Y, 0.3651483717f);
                EXPECT_FLOAT_EQ(result.Z, 0.5477225575f);
                EXPECT_FLOAT_EQ(result.W, 0.7302967433f);
            }
#ifdef HANDMADE_MATH_CPP_MODE
            {
                hmm_quaternion result = HMM_Normalize(q);
                EXPECT_FLOAT_EQ(result.X, 0.1825741858f);
                EXPECT_FLOAT_EQ(result.Y, 0.3651483717f);
                EXPECT_FLOAT_EQ(result.Z, 0.5477225575f);
                EXPECT_FLOAT_EQ(result.W, 0.7302967433f);
            }
#endif
        }
        TEST_END()

        TEST_BEGIN(NLerp)
        {
            hmm_quaternion from = HMM_Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
            hmm_quaternion to = HMM_Quaternion(0.5f, 0.5f, -0.5f, 0.5f);

            hmm_quaternion result = HMM_NLerp(from, 0.5f, to);
            EXPECT_FLOAT_EQ(result.X, 0.28867513f);
            EXPECT_FLOAT_EQ(result.Y, 0.28867513f);
            EXPECT_FLOAT_EQ(result.Z, -0.28867513f);
            EXPECT_FLOAT_EQ(result.W, 0.86602540f);
        }
        TEST_END()

        TEST_BEGIN(Slerp)
        {
            hmm_quaternion from = HMM_Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
            hmm_quaternion to = HMM_Quaternion(0.5f, 0.5f, -0.5f, 0.5f);

            hmm_quaternion result = HMM_Slerp(from, 0.5f, to);
            EXPECT_FLOAT_EQ(result.X, 0.28867513f);
            EXPECT_FLOAT_EQ(result.Y, 0.28867513f);
            EXPECT_FLOAT_EQ(result.Z, -0.28867513f);
            EXPECT_FLOAT_EQ(result.W, 0.86602540f);
        }
        TEST_END()

        TEST_BEGIN(ToMat4)
        {
            const float abs_error = 0.0001f;

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
        TEST_END()

        TEST_BEGIN(FromAxisAngle)
        {
            hmm_vec3 axis = HMM_Vec3(1.0f, 0.0f, 0.0f);
            float angle = HMM_PI32 / 2.0f;

            hmm_quaternion result = HMM_QuaternionFromAxisAngle(axis, angle);
            EXPECT_NEAR(result.X, 0.707107f, FLT_EPSILON * 2);
            EXPECT_FLOAT_EQ(result.Y, 0.0f);
            EXPECT_FLOAT_EQ(result.Z, 0.0f);
            EXPECT_NEAR(result.W, 0.707107f, FLT_EPSILON * 2);
        }
        TEST_END()
    }
    CATEGORY_END()

    CATEGORY_BEGIN(Addition)
    {
        TEST_BEGIN(Vec2)
        {
            hmm_vec2 v2_1 = HMM_Vec2(1.0f, 2.0f);
            hmm_vec2 v2_2 = HMM_Vec2(3.0f, 4.0f);

            {
                hmm_vec2 result = HMM_AddVec2(v2_1, v2_2);
                EXPECT_FLOAT_EQ(result.X, 4.0f);
                EXPECT_FLOAT_EQ(result.Y, 6.0f);
            }
#ifdef HANDMADE_MATH_CPP_MODE
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
        TEST_END()

        TEST_BEGIN(Vec3)
        {
            hmm_vec3 v3_1 = HMM_Vec3(1.0f, 2.0f, 3.0f);
            hmm_vec3 v3_2 = HMM_Vec3(4.0f, 5.0f, 6.0f);

            {
                hmm_vec3 result = HMM_AddVec3(v3_1, v3_2);
                EXPECT_FLOAT_EQ(result.X, 5.0f);
                EXPECT_FLOAT_EQ(result.Y, 7.0f);
                EXPECT_FLOAT_EQ(result.Z, 9.0f);    
            }
#ifdef HANDMADE_MATH_CPP_MODE
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
        TEST_END()

        TEST_BEGIN(Vec4)
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
#ifdef HANDMADE_MATH_CPP_MODE
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
        TEST_END()

        TEST_BEGIN(Mat4)
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
#ifdef HANDMADE_MATH_CPP_MODE
            {
                hmm_mat4 result = HMM_Add(m4_1, m4_2);
                float Expected = 18.0f;
                for (int Column = 0; Column < 4; ++Column)
                {
                    for (int Row = 0; Row < 4; ++Row)
                    {
                        EXPECT_FLOAT_EQ(result.Elements[Column][Row], Expected) << "At column " << Column << ", row " << Row;
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
                        EXPECT_FLOAT_EQ(result.Elements[Column][Row], Expected) << "At column " << Column << ", row " << Row;
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
                    EXPECT_FLOAT_EQ(m4_1.Elements[Column][Row], Expected) << "At column " << Column << ", row " << Row;
                    Expected += 2.0f;
                }
            }
#endif
        }
        TEST_END()

        TEST_BEGIN(Quaternion)
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
#ifdef HANDMADE_MATH_CPP_MODE
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
        TEST_END()
    }
    CATEGORY_END()

    CATEGORY_BEGIN(Subtraction)
    {
        TEST_BEGIN(Vec2)
        {
            hmm_vec2 v2_1 = HMM_Vec2(1.0f, 2.0f);
            hmm_vec2 v2_2 = HMM_Vec2(3.0f, 4.0f);

            {
                hmm_vec2 result = HMM_SubtractVec2(v2_1, v2_2);
                EXPECT_FLOAT_EQ(result.X, -2.0f);
                EXPECT_FLOAT_EQ(result.Y, -2.0f);
            }
#ifdef HANDMADE_MATH_CPP_MODE
            {
                hmm_vec2 result = HMM_Subtract(v2_1, v2_2);
                EXPECT_FLOAT_EQ(result.X, -2.0f);
                EXPECT_FLOAT_EQ(result.Y, -2.0f);
            }
            {
                hmm_vec2 result = v2_1 - v2_2;
                EXPECT_FLOAT_EQ(result.X, -2.0f);
                EXPECT_FLOAT_EQ(result.Y, -2.0f);
            }

            v2_1 -= v2_2;
            EXPECT_FLOAT_EQ(v2_1.X, -2.0f);
            EXPECT_FLOAT_EQ(v2_1.Y, -2.0f);
#endif
        }
        TEST_END()

        TEST_BEGIN(Vec3)
        {
            hmm_vec3 v3_1 = HMM_Vec3(1.0f, 2.0f, 3.0f);
            hmm_vec3 v3_2 = HMM_Vec3(4.0f, 5.0f, 6.0f);

            {
                hmm_vec3 result = HMM_SubtractVec3(v3_1, v3_2);
                EXPECT_FLOAT_EQ(result.X, -3.0f);
                EXPECT_FLOAT_EQ(result.Y, -3.0f);
                EXPECT_FLOAT_EQ(result.Z, -3.0f);
            }
#ifdef HANDMADE_MATH_CPP_MODE
            {
                hmm_vec3 result = HMM_Subtract(v3_1, v3_2);
                EXPECT_FLOAT_EQ(result.X, -3.0f);
                EXPECT_FLOAT_EQ(result.Y, -3.0f);
                EXPECT_FLOAT_EQ(result.Z, -3.0f);
            }
            {
                hmm_vec3 result = v3_1 - v3_2;
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
        TEST_END()

        TEST_BEGIN(Vec4)
        {
            hmm_vec4 v4_1 = HMM_Vec4(1.0f, 2.0f, 3.0f, 4.0f);
            hmm_vec4 v4_2 = HMM_Vec4(5.0f, 6.0f, 7.0f, 8.0f);

            {
                hmm_vec4 result = HMM_SubtractVec4(v4_1, v4_2);
                EXPECT_FLOAT_EQ(result.X, -4.0f);
                EXPECT_FLOAT_EQ(result.Y, -4.0f);
                EXPECT_FLOAT_EQ(result.Z, -4.0f);
                EXPECT_FLOAT_EQ(result.W, -4.0f);
            }
#ifdef HANDMADE_MATH_CPP_MODE
            {
                hmm_vec4 result = HMM_Subtract(v4_1, v4_2);
                EXPECT_FLOAT_EQ(result.X, -4.0f);
                EXPECT_FLOAT_EQ(result.Y, -4.0f);
                EXPECT_FLOAT_EQ(result.Z, -4.0f);
                EXPECT_FLOAT_EQ(result.W, -4.0f);
            }
            {
                hmm_vec4 result = v4_1 - v4_2;
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
        TEST_END()

        TEST_BEGIN(Mat4)
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
                hmm_mat4 result = HMM_SubtractMat4(m4_1, m4_2);
                for (int Column = 0; Column < 4; ++Column)
                {
                    for (int Row = 0; Row < 4; ++Row)
                    {
                        EXPECT_FLOAT_EQ(result.Elements[Column][Row], -16.0f);
                    }
                }
            }
#ifdef HANDMADE_MATH_CPP_MODE
            {
                hmm_mat4 result = HMM_Subtract(m4_1, m4_2);
                for (int Column = 0; Column < 4; ++Column)
                {
                    for (int Row = 0; Row < 4; ++Row)
                    {
                        EXPECT_FLOAT_EQ(result.Elements[Column][Row], -16.0f) << "At column " << Column << ", row " << Row;
                    }
                }
            }
            {
                hmm_mat4 result = m4_1 - m4_2;
                for (int Column = 0; Column < 4; ++Column)
                {
                    for (int Row = 0; Row < 4; ++Row)
                    {
                        EXPECT_FLOAT_EQ(result.Elements[Column][Row], -16.0f) << "At column " << Column << ", row " << Row;
                    }
                }
            }

            m4_1 -= m4_2;
            for (int Column = 0; Column < 4; ++Column)
            {
                for (int Row = 0; Row < 4; ++Row)
                {
                    EXPECT_FLOAT_EQ(m4_1.Elements[Column][Row], -16.0f) << "At column " << Column << ", row " << Row;
                }
            }
#endif
        }
        TEST_END()

        TEST_BEGIN(Quaternion)
        {
            hmm_quaternion q1 = HMM_Quaternion(1.0f, 2.0f, 3.0f, 4.0f);
            hmm_quaternion q2 = HMM_Quaternion(5.0f, 6.0f, 7.0f, 8.0f);

            {
                hmm_quaternion result = HMM_SubtractQuaternion(q1, q2);
                EXPECT_FLOAT_EQ(result.X, -4.0f);
                EXPECT_FLOAT_EQ(result.Y, -4.0f);
                EXPECT_FLOAT_EQ(result.Z, -4.0f);
                EXPECT_FLOAT_EQ(result.W, -4.0f);
            }
#ifdef HANDMADE_MATH_CPP_MODE
            {
                hmm_quaternion result = HMM_Subtract(q1, q2);
                EXPECT_FLOAT_EQ(result.X, -4.0f);
                EXPECT_FLOAT_EQ(result.Y, -4.0f);
                EXPECT_FLOAT_EQ(result.Z, -4.0f);
                EXPECT_FLOAT_EQ(result.W, -4.0f);
            }
            {
                hmm_quaternion result = q1 - q2;
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
        TEST_END()
    }
    CATEGORY_END()

    CATEGORY_BEGIN(Multiplication)
    {
        TEST_BEGIN(Vec2Vec2)
        {
            hmm_vec2 v2_1 = HMM_Vec2(1.0f, 2.0f);
            hmm_vec2 v2_2 = HMM_Vec2(3.0f, 4.0f);

            {
                hmm_vec2 result = HMM_MultiplyVec2(v2_1, v2_2);
                EXPECT_FLOAT_EQ(result.X, 3.0f);
                EXPECT_FLOAT_EQ(result.Y, 8.0f);
            }
#ifdef HANDMADE_MATH_CPP_MODE
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
        TEST_END()

        TEST_BEGIN(Vec2Scalar)
        {
            hmm_vec2 v2 = HMM_Vec2(1.0f, 2.0f);
            float s = 3.0f;

            {
                hmm_vec2 result = HMM_MultiplyVec2f(v2, s);
                EXPECT_FLOAT_EQ(result.X, 3.0f);
                EXPECT_FLOAT_EQ(result.Y, 6.0f);
            }
#ifdef HANDMADE_MATH_CPP_MODE
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
        TEST_END()

        TEST_BEGIN(Vec3Vec3)
        {
            hmm_vec3 v3_1 = HMM_Vec3(1.0f, 2.0f, 3.0f);
            hmm_vec3 v3_2 = HMM_Vec3(4.0f, 5.0f, 6.0f);

            {
                hmm_vec3 result = HMM_MultiplyVec3(v3_1, v3_2);
                EXPECT_FLOAT_EQ(result.X, 4.0f);
                EXPECT_FLOAT_EQ(result.Y, 10.0f);
                EXPECT_FLOAT_EQ(result.Z, 18.0f);
            }
#ifdef HANDMADE_MATH_CPP_MODE
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
        TEST_END()

        TEST_BEGIN(Vec3Scalar)
        {
            hmm_vec3 v3 = HMM_Vec3(1.0f, 2.0f, 3.0f);
            float s = 3.0f;

            {
                hmm_vec3 result = HMM_MultiplyVec3f(v3, s);
                EXPECT_FLOAT_EQ(result.X, 3.0f);
                EXPECT_FLOAT_EQ(result.Y, 6.0f);
                EXPECT_FLOAT_EQ(result.Z, 9.0f);
            }
#ifdef HANDMADE_MATH_CPP_MODE
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
        TEST_END()

        TEST_BEGIN(Vec4Vec4)
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
#ifdef HANDMADE_MATH_CPP_MODE
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
        TEST_END()

        TEST_BEGIN(Vec4Scalar)
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
#ifdef HANDMADE_MATH_CPP_MODE
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
        TEST_END()

        TEST_BEGIN(Mat4Mat4)
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
#ifdef HANDMADE_MATH_CPP_MODE
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
        TEST_END()

        TEST_BEGIN(Mat4Scalar)
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
#ifdef HANDMADE_MATH_CPP_MODE
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
        TEST_END()

        TEST_BEGIN(Mat4Vec4)
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
#ifdef HANDMADE_MATH_CPP_MODE
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
        TEST_END()

        TEST_BEGIN(QuaternionQuaternion)
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
#ifdef HANDMADE_MATH_CPP_MODE
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
        TEST_END()

        TEST_BEGIN(QuaternionScalar)
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
#ifdef HANDMADE_MATH_CPP_MODE
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
        TEST_END()
    }
    CATEGORY_END()

    CATEGORY_BEGIN(Division)
    {
        TEST_BEGIN(Vec2Vec2)
        {
            hmm_vec2 v2_1 = HMM_Vec2(1.0f, 3.0f);
            hmm_vec2 v2_2 = HMM_Vec2(2.0f, 4.0f);

            {
                hmm_vec2 result = HMM_DivideVec2(v2_1, v2_2);
                EXPECT_FLOAT_EQ(result.X, 0.5f);
                EXPECT_FLOAT_EQ(result.Y, 0.75f);
            }
#ifdef HANDMADE_MATH_CPP_MODE
            {
                hmm_vec2 result = HMM_Divide(v2_1, v2_2);
                EXPECT_FLOAT_EQ(result.X, 0.5f);
                EXPECT_FLOAT_EQ(result.Y, 0.75f);
            }
            {
                hmm_vec2 result = v2_1 / v2_2;
                EXPECT_FLOAT_EQ(result.X, 0.5f);
                EXPECT_FLOAT_EQ(result.Y, 0.75f);
            }

            v2_1 /= v2_2;
            EXPECT_FLOAT_EQ(v2_1.X, 0.5f);
            EXPECT_FLOAT_EQ(v2_1.Y, 0.75f);
#endif
        }
        TEST_END()

        TEST_BEGIN(Vec2Scalar)
        {
            hmm_vec2 v2 = HMM_Vec2(1.0f, 2.0f);
            float s = 2;

            {
                hmm_vec2 result = HMM_DivideVec2f(v2, s);
                EXPECT_FLOAT_EQ(result.X, 0.5f);
                EXPECT_FLOAT_EQ(result.Y, 1.0f);
            }
#ifdef HANDMADE_MATH_CPP_MODE
            {
                hmm_vec2 result = HMM_Divide(v2, s);
                EXPECT_FLOAT_EQ(result.X, 0.5f);
                EXPECT_FLOAT_EQ(result.Y, 1.0f);
            }
            {
                hmm_vec2 result = v2 / s;
                EXPECT_FLOAT_EQ(result.X, 0.5f);
                EXPECT_FLOAT_EQ(result.Y, 1.0f);
            }

            v2 /= s;
            EXPECT_FLOAT_EQ(v2.X, 0.5f);
            EXPECT_FLOAT_EQ(v2.Y, 1.0f);
#endif
        }
        TEST_END()

        TEST_BEGIN(Vec3Vec3)
        {
            hmm_vec3 v3_1 = HMM_Vec3(1.0f, 3.0f, 5.0f);
            hmm_vec3 v3_2 = HMM_Vec3(2.0f, 4.0f, 0.5f);

            {
                hmm_vec3 result = HMM_DivideVec3(v3_1, v3_2);
                EXPECT_FLOAT_EQ(result.X, 0.5f);
                EXPECT_FLOAT_EQ(result.Y, 0.75f);
                EXPECT_FLOAT_EQ(result.Z, 10.0f);
            }
#ifdef HANDMADE_MATH_CPP_MODE
            {
                hmm_vec3 result = HMM_Divide(v3_1, v3_2);
                EXPECT_FLOAT_EQ(result.X, 0.5f);
                EXPECT_FLOAT_EQ(result.Y, 0.75f);
                EXPECT_FLOAT_EQ(result.Z, 10.0f);
            }
            {
                hmm_vec3 result = v3_1 / v3_2;
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
        TEST_END()

        TEST_BEGIN(Vec3Scalar)
        {
            hmm_vec3 v3 = HMM_Vec3(1.0f, 2.0f, 3.0f);
            float s = 2;

            {
                hmm_vec3 result = HMM_DivideVec3f(v3, s);
                EXPECT_FLOAT_EQ(result.X, 0.5f);
                EXPECT_FLOAT_EQ(result.Y, 1.0f);
                EXPECT_FLOAT_EQ(result.Z, 1.5f);
            }
#ifdef HANDMADE_MATH_CPP_MODE
            {
                hmm_vec3 result = HMM_Divide(v3, s);
                EXPECT_FLOAT_EQ(result.X, 0.5f);
                EXPECT_FLOAT_EQ(result.Y, 1.0f);
                EXPECT_FLOAT_EQ(result.Z, 1.5f);
            }
            {
                hmm_vec3 result = v3 / s;
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
        TEST_END()

        TEST_BEGIN(Vec4Vec4)
        {
            hmm_vec4 v4_1 = HMM_Vec4(1.0f, 3.0f, 5.0f, 1.0f);
            hmm_vec4 v4_2 = HMM_Vec4(2.0f, 4.0f, 0.5f, 4.0f);

            {
                hmm_vec4 result = HMM_DivideVec4(v4_1, v4_2);
                EXPECT_FLOAT_EQ(result.X, 0.5f);
                EXPECT_FLOAT_EQ(result.Y, 0.75f);
                EXPECT_FLOAT_EQ(result.Z, 10.0f);
                EXPECT_FLOAT_EQ(result.W, 0.25f);
            }
#ifdef HANDMADE_MATH_CPP_MODE
            {
                hmm_vec4 result = HMM_Divide(v4_1, v4_2);
                EXPECT_FLOAT_EQ(result.X, 0.5f);
                EXPECT_FLOAT_EQ(result.Y, 0.75f);
                EXPECT_FLOAT_EQ(result.Z, 10.0f);
                EXPECT_FLOAT_EQ(result.W, 0.25f);
            }
            {
                hmm_vec4 result = v4_1 / v4_2;
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
        TEST_END()

        TEST_BEGIN(Vec4Scalar)
        {
            hmm_vec4 v4 = HMM_Vec4(1.0f, 2.0f, 3.0f, 4.0f);
            float s = 2;

            {
                hmm_vec4 result = HMM_DivideVec4f(v4, s);
                EXPECT_FLOAT_EQ(result.X, 0.5f);
                EXPECT_FLOAT_EQ(result.Y, 1.0f);
                EXPECT_FLOAT_EQ(result.Z, 1.5f);
                EXPECT_FLOAT_EQ(result.W, 2.0f);
            }
#ifdef HANDMADE_MATH_CPP_MODE
            {
                hmm_vec4 result = HMM_Divide(v4, s);
                EXPECT_FLOAT_EQ(result.X, 0.5f);
                EXPECT_FLOAT_EQ(result.Y, 1.0f);
                EXPECT_FLOAT_EQ(result.Z, 1.5f);
                EXPECT_FLOAT_EQ(result.W, 2.0f);
            }
            {
                hmm_vec4 result = v4 / s;
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
        TEST_END()

        TEST_BEGIN(Mat4Scalar)
        {
            hmm_mat4 m4 = HMM_Mat4(); // will have 1 - 16
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
                hmm_mat4 result = HMM_DivideMat4f(m4, s);
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
#ifdef HANDMADE_MATH_CPP_MODE
            {
                hmm_mat4 result = HMM_Divide(m4, s);
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
                hmm_mat4 result = m4 / s;
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
        TEST_END()

        TEST_BEGIN(QuaternionScalar)
        {
            hmm_quaternion q = HMM_Quaternion(1.0f, 2.0f, 3.0f, 4.0f);
            float f = 2.0f;

            {
                hmm_quaternion result = HMM_DivideQuaternionF(q, f);
                EXPECT_FLOAT_EQ(result.X, 0.5f);
                EXPECT_FLOAT_EQ(result.Y, 1.0f);
                EXPECT_FLOAT_EQ(result.Z, 1.5f);
                EXPECT_FLOAT_EQ(result.W, 2.0f);
            }
#ifdef HANDMADE_MATH_CPP_MODE
            {
                hmm_quaternion result = HMM_Divide(q, f);
                EXPECT_FLOAT_EQ(result.X, 0.5f);
                EXPECT_FLOAT_EQ(result.Y, 1.0f);
                EXPECT_FLOAT_EQ(result.Z, 1.5f);
                EXPECT_FLOAT_EQ(result.W, 2.0f);
            }
            {
                hmm_quaternion result = q / f;
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
        TEST_END()
    }
    CATEGORY_END()

    CATEGORY_BEGIN(Projection)
    {
        TEST_BEGIN(Orthographic)
        {
            hmm_mat4 projection = HMM_Orthographic(-10.0f, 10.0f, -5.0f, 5.0f, 0.0f, -10.0f);

            hmm_vec3 original = HMM_Vec3(5.0f, 5.0f, -5.0f);
            hmm_vec4 projected = HMM_MultiplyMat4ByVec4(projection, HMM_Vec4v(original, 1));

            EXPECT_FLOAT_EQ(projected.X, 0.5f);
            EXPECT_FLOAT_EQ(projected.Y, 1.0f);
            EXPECT_FLOAT_EQ(projected.Z, -2.0f);
            EXPECT_FLOAT_EQ(projected.W, 1.0f);
        }
        TEST_END()

        TEST_BEGIN(Perspective)
        {
            hmm_mat4 projection = HMM_Perspective(90.0f, 2.0f, 5.0f, 15.0f);

            {
                hmm_vec3 original = HMM_Vec3(5.0f, 5.0f, -15.0f);
                hmm_vec4 projected = HMM_MultiplyMat4ByVec4(projection, HMM_Vec4v(original, 1));
                EXPECT_FLOAT_EQ(projected.X, 5.0f);
                EXPECT_FLOAT_EQ(projected.Y, 10.0f);
                EXPECT_FLOAT_EQ(projected.Z, 15.0f);
                EXPECT_FLOAT_EQ(projected.W, 15.0f);
            }
            {
                hmm_vec3 original = HMM_Vec3(5.0f, 5.0f, -5.0f);
                hmm_vec4 projected = HMM_MultiplyMat4ByVec4(projection, HMM_Vec4v(original, 1));
                EXPECT_FLOAT_EQ(projected.X, 5.0f);
                EXPECT_FLOAT_EQ(projected.Y, 10.0f);
                EXPECT_FLOAT_EQ(projected.Z, -5.0f);
                EXPECT_FLOAT_EQ(projected.W, 5.0f);
            }
        }
        TEST_END()
    }
    CATEGORY_END()

    CATEGORY_BEGIN(Transformations)
    {
        TEST_BEGIN(Translate)
        {
            hmm_mat4 translate = HMM_Translate(HMM_Vec3(1.0f, -3.0f, 6.0f));

            hmm_vec3 original = HMM_Vec3(1.0f, 2.0f, 3.0f);
            hmm_vec4 translated = HMM_MultiplyMat4ByVec4(translate, HMM_Vec4v(original, 1));

            EXPECT_FLOAT_EQ(translated.X, 2.0f);
            EXPECT_FLOAT_EQ(translated.Y, -1.0f);
            EXPECT_FLOAT_EQ(translated.Z, 9.0f);
            EXPECT_FLOAT_EQ(translated.W, 1.0f);
        }
        TEST_END()

        TEST_BEGIN(Rotate)
        {
            hmm_vec3 original = HMM_Vec3(1.0f, 1.0f, 1.0f);

            hmm_mat4 rotateX = HMM_Rotate(90, HMM_Vec3(1, 0, 0));
            hmm_vec4 rotatedX = HMM_MultiplyMat4ByVec4(rotateX, HMM_Vec4v(original, 1));
            EXPECT_FLOAT_EQ(rotatedX.X, 1.0f);
            EXPECT_FLOAT_EQ(rotatedX.Y, -1.0f);
            EXPECT_FLOAT_EQ(rotatedX.Z, 1.0f);
            EXPECT_FLOAT_EQ(rotatedX.W, 1.0f);

            hmm_mat4 rotateY = HMM_Rotate(90, HMM_Vec3(0, 1, 0));
            hmm_vec4 rotatedY = HMM_MultiplyMat4ByVec4(rotateY, HMM_Vec4v(original, 1));
            EXPECT_FLOAT_EQ(rotatedY.X, 1.0f);
            EXPECT_FLOAT_EQ(rotatedY.Y, 1.0f);
            EXPECT_FLOAT_EQ(rotatedY.Z, -1.0f);
            EXPECT_FLOAT_EQ(rotatedY.W, 1.0f);

            hmm_mat4 rotateZ = HMM_Rotate(90, HMM_Vec3(0, 0, 1));
            hmm_vec4 rotatedZ = HMM_MultiplyMat4ByVec4(rotateZ, HMM_Vec4v(original, 1));
            EXPECT_FLOAT_EQ(rotatedZ.X, -1.0f);
            EXPECT_FLOAT_EQ(rotatedZ.Y, 1.0f);
            EXPECT_FLOAT_EQ(rotatedZ.Z, 1.0f);
            EXPECT_FLOAT_EQ(rotatedZ.W, 1.0f);
        }
        TEST_END()

        TEST_BEGIN(Scale)
        {
            hmm_mat4 scale = HMM_Scale(HMM_Vec3(2.0f, -3.0f, 0.5f));

            hmm_vec3 original = HMM_Vec3(1.0f, 2.0f, 3.0f);
            hmm_vec4 scaled = HMM_MultiplyMat4ByVec4(scale, HMM_Vec4v(original, 1));

            EXPECT_FLOAT_EQ(scaled.X, 2.0f);
            EXPECT_FLOAT_EQ(scaled.Y, -6.0f);
            EXPECT_FLOAT_EQ(scaled.Z, 1.5f);
            EXPECT_FLOAT_EQ(scaled.W, 1.0f);
        }
        TEST_END()
    }
    CATEGORY_END()

#ifdef HANDMADE_MATH__USE_SSE
    CATEGORY_BEGIN(SSE)
    {
        TEST_BEGIN(LinearCombine)
        {
            hmm_mat4 MatrixOne = HMM_Mat4d(2.0f);
            hmm_mat4 MatrixTwo = HMM_Mat4d(4.0f);
            hmm_mat4 Result;
            
            Result.Rows[0] = HMM_LinearCombineSSE(MatrixOne.Rows[0], MatrixTwo);
            Result.Rows[1] = HMM_LinearCombineSSE(MatrixOne.Rows[1], MatrixTwo);
            Result.Rows[2] = HMM_LinearCombineSSE(MatrixOne.Rows[2], MatrixTwo);
            Result.Rows[3] = HMM_LinearCombineSSE(MatrixOne.Rows[3], MatrixTwo);
            
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
        TEST_END()
    }
    CATEGORY_END()
#endif   
    return 0;
}
