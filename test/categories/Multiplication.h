#include "../HandmadeTest.h"

TEST(Multiplication, Vec2Vec2)
{
    HMM_Vec2 v2_1 = HMM_V2(1.0f, 2.0f);
    HMM_Vec2 v2_2 = HMM_V2(3.0f, 4.0f);

    {
        HMM_Vec2 result = HMM_MulV2(v2_1, v2_2);
        EXPECT_FLOAT_EQ(result.X, 3.0f);
        EXPECT_FLOAT_EQ(result.Y, 8.0f);
    }
#if HANDMADE_MATH__USE_C11_GENERICS || defined(__cplusplus)
    {
        HMM_Vec2 result = HMM_Mul(v2_1, v2_2);
        EXPECT_FLOAT_EQ(result.X, 3.0f);
        EXPECT_FLOAT_EQ(result.Y, 8.0f);
    }
#endif
#ifdef __cplusplus
    {
        HMM_Vec2 result = v2_1 * v2_2;
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
    HMM_Vec2 v2 = HMM_V2(1.0f, 2.0f);
    float s = 3.0f;

    {
        HMM_Vec2 result = HMM_MulV2F(v2, s);
        EXPECT_FLOAT_EQ(result.X, 3.0f);
        EXPECT_FLOAT_EQ(result.Y, 6.0f);
    }
#if HANDMADE_MATH__USE_C11_GENERICS || defined(__cplusplus)
    {
        HMM_Vec2 result = HMM_Mul(v2, s);
        EXPECT_FLOAT_EQ(result.X, 3.0f);
        EXPECT_FLOAT_EQ(result.Y, 6.0f);
    }
#endif
#ifdef __cplusplus
    {
        HMM_Vec2 result = v2 * s;
        EXPECT_FLOAT_EQ(result.X, 3.0f);
        EXPECT_FLOAT_EQ(result.Y, 6.0f);
    }
    {
        HMM_Vec2 result = s * v2;
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
    HMM_Vec3 v3_1 = HMM_V3(1.0f, 2.0f, 3.0f);
    HMM_Vec3 v3_2 = HMM_V3(4.0f, 5.0f, 6.0f);

    {
        HMM_Vec3 result = HMM_MulV3(v3_1, v3_2);
        EXPECT_FLOAT_EQ(result.X, 4.0f);
        EXPECT_FLOAT_EQ(result.Y, 10.0f);
        EXPECT_FLOAT_EQ(result.Z, 18.0f);
    }
#if HANDMADE_MATH__USE_C11_GENERICS || defined(__cplusplus)
    {
        HMM_Vec3 result = HMM_Mul(v3_1, v3_2);
        EXPECT_FLOAT_EQ(result.X, 4.0f);
        EXPECT_FLOAT_EQ(result.Y, 10.0f);
        EXPECT_FLOAT_EQ(result.Z, 18.0f);
    }
#endif
#ifdef __cplusplus
    {
        HMM_Vec3 result = v3_1 * v3_2;
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
    HMM_Vec3 v3 = HMM_V3(1.0f, 2.0f, 3.0f);
    float s = 3.0f;

    {
        HMM_Vec3 result = HMM_MulV3F(v3, s);
        EXPECT_FLOAT_EQ(result.X, 3.0f);
        EXPECT_FLOAT_EQ(result.Y, 6.0f);
        EXPECT_FLOAT_EQ(result.Z, 9.0f);
    }
#if HANDMADE_MATH__USE_C11_GENERICS || defined(__cplusplus)
    {
        HMM_Vec3 result = HMM_Mul(v3, s);
        EXPECT_FLOAT_EQ(result.X, 3.0f);
        EXPECT_FLOAT_EQ(result.Y, 6.0f);
        EXPECT_FLOAT_EQ(result.Z, 9.0f);
    }
#endif
#ifdef __cplusplus
    {
        HMM_Vec3 result = v3 * s;
        EXPECT_FLOAT_EQ(result.X, 3.0f);
        EXPECT_FLOAT_EQ(result.Y, 6.0f);
        EXPECT_FLOAT_EQ(result.Z, 9.0f);
    }
    {
        HMM_Vec3 result = s * v3;
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
    HMM_Vec4 v4_1 = HMM_V4(1.0f, 2.0f, 3.0f, 4.0f);
    HMM_Vec4 v4_2 = HMM_V4(5.0f, 6.0f, 7.0f, 8.0f);

    {
        HMM_Vec4 result = HMM_MulV4(v4_1, v4_2);
        EXPECT_FLOAT_EQ(result.X, 5.0f);
        EXPECT_FLOAT_EQ(result.Y, 12.0f);
        EXPECT_FLOAT_EQ(result.Z, 21.0f);
        EXPECT_FLOAT_EQ(result.W, 32.0f);
    }
#if HANDMADE_MATH__USE_C11_GENERICS || defined(__cplusplus)
    {
        HMM_Vec4 result = HMM_Mul(v4_1, v4_2);
        EXPECT_FLOAT_EQ(result.X, 5.0f);
        EXPECT_FLOAT_EQ(result.Y, 12.0f);
        EXPECT_FLOAT_EQ(result.Z, 21.0f);
        EXPECT_FLOAT_EQ(result.W, 32.0f);
    }
#endif
#ifdef __cplusplus
    {
        HMM_Vec4 result = v4_1 * v4_2;
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
    HMM_Vec4 v4 = HMM_V4(1.0f, 2.0f, 3.0f, 4.0f);
    float s = 3.0f;

    {
        HMM_Vec4 result = HMM_MulV4F(v4, s);
        EXPECT_FLOAT_EQ(result.X, 3.0f);
        EXPECT_FLOAT_EQ(result.Y, 6.0f);
        EXPECT_FLOAT_EQ(result.Z, 9.0f);
        EXPECT_FLOAT_EQ(result.W, 12.0f);
    }
#if HANDMADE_MATH__USE_C11_GENERICS || defined(__cplusplus)
    {
        HMM_Vec4 result = HMM_Mul(v4, s);
        EXPECT_FLOAT_EQ(result.X, 3.0f);
        EXPECT_FLOAT_EQ(result.Y, 6.0f);
        EXPECT_FLOAT_EQ(result.Z, 9.0f);
        EXPECT_FLOAT_EQ(result.W, 12.0f);
    }
#endif
#ifdef __cplusplus
    {
        HMM_Vec4 result = v4 * s;
        EXPECT_FLOAT_EQ(result.X, 3.0f);
        EXPECT_FLOAT_EQ(result.Y, 6.0f);
        EXPECT_FLOAT_EQ(result.Z, 9.0f);
        EXPECT_FLOAT_EQ(result.W, 12.0f);
    }
    {
        HMM_Vec4 result = s * v4;
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

TEST(Multiplication, Mat2Mat2) {
    HMM_Mat2 a = HMM_M2();
    HMM_Mat2 b = HMM_M2();

    int counter = 1;
    for (int Column = 0; Column < 2; Column++) {
        for (int Row = 0; Row < 2; Row++) {
            a.Elements[Column][Row] = counter++;
        }
    }
    
    for (int Column = 0; Column < 2; Column++) {
        for (int Row = 0; Row < 2; Row++) {
            b.Elements[Column][Row] = counter++;
        }
    }

    {
        HMM_Mat2 result = HMM_MulM2(a,b);
        EXPECT_FLOAT_EQ(result.Elements[0][0], 23.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][1], 34.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][0], 31.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][1], 46.0f);        
    }

#if HANDMADE_MATH__USE_C11_GENERICS || defined(__cplusplus)
    {
        HMM_Mat2 result = HMM_Mul(a,b);
        EXPECT_FLOAT_EQ(result.Elements[0][0], 23.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][1], 34.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][0], 31.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][1], 46.0f);
    }
#endif

#ifdef __cplusplus
    {
        HMM_Mat2 result = a * b;
        EXPECT_FLOAT_EQ(result.Elements[0][0], 23.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][1], 34.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][0], 31.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][1], 46.0f);        
    }
#endif
}

TEST(Multiplication, Mat2Scalar) {
    HMM_Mat2 m = HMM_M2();
    float s = 10.0f;

    int counter = 1;
    for (int Column = 0; Column < 2; Column++) {
        for (int Row = 0; Row < 2; Row++) {
            m.Elements[Column][Row] = counter++;
        }
    }

    {
        HMM_Mat2 result = HMM_MulM2F(m, s);
        EXPECT_FLOAT_EQ(result.Elements[0][0], 10.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][1], 20.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][0], 30.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][1], 40.0f);
    }
#if HANDMADE_MATH__USE_C11_GENERICS || defined(__cplusplus)
    {
        HMM_Mat2 result = HMM_Mul(m, s);
        EXPECT_FLOAT_EQ(result.Elements[0][0], 10.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][1], 20.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][0], 30.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][1], 40.0f);
    }
#endif
#ifdef __cplusplus
    {
        HMM_Mat2 result = m * s;
        EXPECT_FLOAT_EQ(result.Elements[0][0], 10.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][1], 20.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][0], 30.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][1], 40.0f);
    }
    {
        HMM_Mat2 result = s * m;
        EXPECT_FLOAT_EQ(result.Elements[0][0], 10.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][1], 20.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][0], 30.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][1], 40.0f);
    }
    m *= s;
    EXPECT_FLOAT_EQ(m.Elements[0][0], 10.0f);
    EXPECT_FLOAT_EQ(m.Elements[0][1], 20.0f);
    EXPECT_FLOAT_EQ(m.Elements[1][0], 30.0f);
    EXPECT_FLOAT_EQ(m.Elements[1][1], 40.0f);
#endif
}

TEST(Multiplication, Mat2Vec2) {
    HMM_Mat2 m = HMM_M2();
    HMM_Vec2 v = HMM_V2(0.0f, 0.0f);

    int counter = 1;
    for (int Column = 0; Column < 2; Column++) {
        for (int Row = 0; Row < 2; Row++) {
            m.Elements[Column][Row] = counter++;
        }
    }

    for (int Row = 0; Row < 2; Row++) {
        v.Elements[Row] = counter++;
    }

    {
        HMM_Vec2 result = HMM_MulM2V2(m, v);
        EXPECT_FLOAT_EQ(result.Elements[0], 23.0f);
        EXPECT_FLOAT_EQ(result.Elements[1], 34.0f);
    }

#if HANDMADE_MATH__USE_C11_GENERICS || defined(__cplusplus)
    {
        HMM_Vec2 result = HMM_Mul(m, v);
        EXPECT_FLOAT_EQ(result.Elements[0], 23.0f);
        EXPECT_FLOAT_EQ(result.Elements[1], 34.0f);
    }
#endif

#ifdef __cplusplus
    {
        HMM_Vec2 result = m * v;
        EXPECT_FLOAT_EQ(result.Elements[0], 23.0f);
        EXPECT_FLOAT_EQ(result.Elements[1], 34.0f);
    }
#endif
}
 
TEST(Multiplication, Mat3Mat3) 
{
    HMM_Mat3 a = HMM_M3();
    HMM_Mat3 b = HMM_M3();

    int counter = 1;
    for (int Column = 0; Column < 3; Column++) {
        for (int Row = 0; Row < 3; Row++) {
            a.Elements[Column][Row] = counter++;
        }
    }
    
    for (int Column = 0; Column < 3; Column++) {
        for (int Row = 0; Row < 3; Row++) {
            b.Elements[Column][Row] = counter++;
        }
    }

    {
        HMM_Mat3 result = HMM_MulM3(a,b);
        EXPECT_FLOAT_EQ(result.Elements[0][0], 138.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][1], 171.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][2], 204.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][0], 174.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][1], 216.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][2], 258.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][0], 210.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][1], 261.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][2], 312.0f);
    }

#if HANDMADE_MATH__USE_C11_GENERICS || defined(__cplusplus)
    {
        HMM_Mat3 result = HMM_Mul(a,b);
        EXPECT_FLOAT_EQ(result.Elements[0][0], 138.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][1], 171.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][2], 204.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][0], 174.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][1], 216.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][2], 258.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][0], 210.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][1], 261.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][2], 312.0f);
    }
#endif

#ifdef __cplusplus
    {
        HMM_Mat3 result = a * b;
        EXPECT_FLOAT_EQ(result.Elements[0][0], 138.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][1], 171.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][2], 204.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][0], 174.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][1], 216.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][2], 258.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][0], 210.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][1], 261.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][2], 312.0f);
    }
#endif
}

TEST(Multiplication, Mat3Scalar) {
    HMM_Mat3 m = HMM_M3();
    float s = 10.0f;

    int counter = 1;
    for (int Column = 0; Column < 3; Column++) {
        for (int Row = 0; Row < 3; Row++) {
            m.Elements[Column][Row] = counter++;
        }
    }

    {
        HMM_Mat3 result = HMM_MulM3F(m, s);
        EXPECT_FLOAT_EQ(result.Elements[0][0], 10.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][1], 20.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][2], 30.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][0], 40.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][1], 50.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][2], 60.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][0], 70.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][1], 80.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][2], 90.0f);
    }
#if HANDMADE_MATH__USE_C11_GENERICS || defined(__cplusplus)
    {
        HMM_Mat3 result = HMM_Mul(m, s);
        EXPECT_FLOAT_EQ(result.Elements[0][0], 10.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][1], 20.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][2], 30.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][0], 40.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][1], 50.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][2], 60.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][0], 70.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][1], 80.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][2], 90.0f);
    }
#endif
#ifdef __cplusplus
    {
        HMM_Mat3 result = m * s;
        EXPECT_FLOAT_EQ(result.Elements[0][0], 10.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][1], 20.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][2], 30.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][0], 40.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][1], 50.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][2], 60.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][0], 70.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][1], 80.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][2], 90.0f);
    }
    {
        HMM_Mat3 result = s * m;
        EXPECT_FLOAT_EQ(result.Elements[0][0], 10.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][1], 20.0f);
        EXPECT_FLOAT_EQ(result.Elements[0][2], 30.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][0], 40.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][1], 50.0f);
        EXPECT_FLOAT_EQ(result.Elements[1][2], 60.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][0], 70.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][1], 80.0f);
        EXPECT_FLOAT_EQ(result.Elements[2][2], 90.0f);
    }
    m *= s;
    EXPECT_FLOAT_EQ(m.Elements[0][0], 10.0f);
    EXPECT_FLOAT_EQ(m.Elements[0][1], 20.0f);
    EXPECT_FLOAT_EQ(m.Elements[0][2], 30.0f);
    EXPECT_FLOAT_EQ(m.Elements[1][0], 40.0f);
    EXPECT_FLOAT_EQ(m.Elements[1][1], 50.0f);
    EXPECT_FLOAT_EQ(m.Elements[1][2], 60.0f);
    EXPECT_FLOAT_EQ(m.Elements[2][0], 70.0f);
    EXPECT_FLOAT_EQ(m.Elements[2][1], 80.0f);
    EXPECT_FLOAT_EQ(m.Elements[2][2], 90.0f);
#endif
}

TEST(Multiplication, Mat3Vec3) {
    HMM_Mat3 m = HMM_M3();
    HMM_Vec3 v = HMM_V3(0.0f, 0.0f, 0.0f);

    int counter = 1;
    for (int Column = 0; Column < 3; Column++) {
        for (int Row = 0; Row < 3; Row++) {
            m.Elements[Column][Row] = counter++;
        }
    }

    for (int Row = 0; Row < 3; Row++) {
        v.Elements[Row] = counter++;
    }

    {
        HMM_Vec3 result = HMM_MulM3V3(m, v);
        EXPECT_FLOAT_EQ(result.Elements[0], 138.0f);
        EXPECT_FLOAT_EQ(result.Elements[1], 171.0f);
        EXPECT_FLOAT_EQ(result.Elements[2], 204.0f);
    }
#if HANDMADE_MATH__USE_C11_GENERICS || defined(__cplusplus)
    {
        HMM_Vec3 result = HMM_Mul(m, v);
        EXPECT_FLOAT_EQ(result.Elements[0], 138.0f);
        EXPECT_FLOAT_EQ(result.Elements[1], 171.0f);
        EXPECT_FLOAT_EQ(result.Elements[2], 204.0f);
    }
#endif
#ifdef __cplusplus
    {
        HMM_Vec3 result = m * v;
        EXPECT_FLOAT_EQ(result.Elements[0], 138.0f);
        EXPECT_FLOAT_EQ(result.Elements[1], 171.0f);
        EXPECT_FLOAT_EQ(result.Elements[2], 204.0f);
    }
#endif
}

TEST(Multiplication, Mat4Mat4)
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
        HMM_Mat4 result = HMM_MulM4(m4_1, m4_2);
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
#if HANDMADE_MATH__USE_C11_GENERICS || defined(__cplusplus)
    {
        HMM_Mat4 result = HMM_Mul(m4_1, m4_2);
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
#endif
#ifdef __cplusplus
    {
        HMM_Mat4 result = m4_1 * m4_2;
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
    HMM_Mat4 m4 = HMM_M4(); // will have 1 - 16
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
        HMM_Mat4 result = HMM_MulM4F(m4, s);
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
#if HANDMADE_MATH__USE_C11_GENERICS || defined(__cplusplus)
    {
        HMM_Mat4 result = HMM_Mul(m4, s);
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
#endif
#ifdef __cplusplus
    {
        HMM_Mat4 result = m4 * s;
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
        HMM_Mat4 result = s * m4;
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
    HMM_Mat4 m4 = HMM_M4(); // will have 1 - 16
    HMM_Vec4 v4 = HMM_V4(1.0f, 2.0f, 3.0f, 4.0f);

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
        HMM_Vec4 result = HMM_MulM4V4(m4, v4);
        EXPECT_FLOAT_EQ(result.X, 90.0f);
        EXPECT_FLOAT_EQ(result.Y, 100.0f);
        EXPECT_FLOAT_EQ(result.Z, 110.0f);
        EXPECT_FLOAT_EQ(result.W, 120.0f);
    }
#if HANDMADE_MATH__USE_C11_GENERICS || defined(__cplusplus)
    {
        HMM_Vec4 result = HMM_Mul(m4, v4);
        EXPECT_FLOAT_EQ(result.X, 90.0f);
        EXPECT_FLOAT_EQ(result.Y, 100.0f);
        EXPECT_FLOAT_EQ(result.Z, 110.0f);
        EXPECT_FLOAT_EQ(result.W, 120.0f);
    }
#endif
#ifdef __cplusplus
    {
        HMM_Vec4 result = m4 * v4;
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
    HMM_Quat q1 = HMM_Q(1.0f, 2.0f, 3.0f, 4.0f);
    HMM_Quat q2 = HMM_Q(5.0f, 6.0f, 7.0f, 8.0f);

    {
        HMM_Quat result = HMM_MulQ(q1, q2);
        EXPECT_FLOAT_EQ(result.X, 24.0f);
        EXPECT_FLOAT_EQ(result.Y, 48.0f);
        EXPECT_FLOAT_EQ(result.Z, 48.0f);
        EXPECT_FLOAT_EQ(result.W, -6.0f);
    }
#if HANDMADE_MATH__USE_C11_GENERICS || defined(__cplusplus)
    {
        HMM_Quat result = HMM_Mul(q1, q2);
        EXPECT_FLOAT_EQ(result.X, 24.0f);
        EXPECT_FLOAT_EQ(result.Y, 48.0f);
        EXPECT_FLOAT_EQ(result.Z, 48.0f);
        EXPECT_FLOAT_EQ(result.W, -6.0f);
    }
#endif
#ifdef __cplusplus
    {
        HMM_Quat result = q1 * q2;
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
    HMM_Quat q = HMM_Q(1.0f, 2.0f, 3.0f, 4.0f);
    float f = 2.0f;

    {
        HMM_Quat result = HMM_MulQF(q, f);
        EXPECT_FLOAT_EQ(result.X, 2.0f);
        EXPECT_FLOAT_EQ(result.Y, 4.0f);
        EXPECT_FLOAT_EQ(result.Z, 6.0f);
        EXPECT_FLOAT_EQ(result.W, 8.0f);
    }
#if HANDMADE_MATH__USE_C11_GENERICS || defined(__cplusplus)
    {
        HMM_Quat result = HMM_Mul(q, f);
        EXPECT_FLOAT_EQ(result.X, 2.0f);
        EXPECT_FLOAT_EQ(result.Y, 4.0f);
        EXPECT_FLOAT_EQ(result.Z, 6.0f);
        EXPECT_FLOAT_EQ(result.W, 8.0f);
    }
#endif
#ifdef __cplusplus
    {
        HMM_Quat result = q * f;
        EXPECT_FLOAT_EQ(result.X, 2.0f);
        EXPECT_FLOAT_EQ(result.Y, 4.0f);
        EXPECT_FLOAT_EQ(result.Z, 6.0f);
        EXPECT_FLOAT_EQ(result.W, 8.0f);
    }
    {
        HMM_Quat result = f * q;
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
