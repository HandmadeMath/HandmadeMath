#include "../HandmadeTest.h"

TEST(Initialization, Vectors)
{
    //
    // Test vec2
    //
    HMM_Vec2 v2 = HMM_V2(1.0f, 2.0f);

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
#ifdef __cplusplus
    EXPECT_FLOAT_EQ(v2[0], 1.0f);
    EXPECT_FLOAT_EQ(v2[1], 2.0f);
#endif

    //
    // Test vec3
    //
    HMM_Vec3 v3 = HMM_V3(1.0f, 2.0f, 3.0f);

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
#ifdef __cplusplus
    EXPECT_FLOAT_EQ(v3[0], 1.0f);
    EXPECT_FLOAT_EQ(v3[1], 2.0f);
    EXPECT_FLOAT_EQ(v3[2], 3.0f);
#endif

    //
    // Test vec4
    //
    HMM_Vec4 v4 = HMM_V4(1.0f, 2.0f, 3.0f, 4.0f);
    HMM_Vec4 v4v = HMM_V4V(v3, 4.0f);

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
#ifdef __cplusplus
    EXPECT_FLOAT_EQ(v4[0], 1.0f);
    EXPECT_FLOAT_EQ(v4[1], 2.0f);
    EXPECT_FLOAT_EQ(v4[2], 3.0f);
    EXPECT_FLOAT_EQ(v4[3], 4.0f);
#endif

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
#ifdef __cplusplus
    EXPECT_FLOAT_EQ(v4v[0], 1.0f);
    EXPECT_FLOAT_EQ(v4v[1], 2.0f);
    EXPECT_FLOAT_EQ(v4v[2], 3.0f);
    EXPECT_FLOAT_EQ(v4v[3], 4.0f);
#endif
}

TEST(Initialization, MatrixEmpty)
{
    //
    // Test mat2
    //
    HMM_Mat2 m2 = HMM_M2();
    for (int Column = 0; Column < 2; ++Column)
    {
        for (int Row = 0; Row < 2; ++Row)
        {
            EXPECT_FLOAT_EQ(m2.Elements[Column][Row], 0.0f);
#ifdef __cplusplus
            EXPECT_FLOAT_EQ(m2[Column][Row], 0.0f);
#endif
        }
    }

    //
    // Test mat3
    //
    HMM_Mat3 m3 = HMM_M3();
    for (int Column = 0; Column < 3; ++Column)
    {
        for (int Row = 0; Row < 3; ++Row)
        {
            EXPECT_FLOAT_EQ(m3.Elements[Column][Row], 0.0f);
#ifdef __cplusplus
            EXPECT_FLOAT_EQ(m3[Column][Row], 0.0f);
#endif
        }
    }

    //
    // Test mat4
    //
    HMM_Mat4 m4 = HMM_M4();
    for (int Column = 0; Column < 4; ++Column)
    {
        for (int Row = 0; Row < 4; ++Row)
        {
            EXPECT_FLOAT_EQ(m4.Elements[Column][Row], 0.0f);
#ifdef __cplusplus
            EXPECT_FLOAT_EQ(m4[Column][Row], 0.0f);
#endif
        }
    }
}

TEST(Initialization, MatrixDiagonal)
{
    //
    // Test mat2
    //
    HMM_Mat2 m2d = HMM_M2D(1.0f);
    for (int Column = 0; Column < 2; ++Column)
    {
        for (int Row = 0; Row < 2; ++Row)
        {
            if (Column == Row) {
                EXPECT_FLOAT_EQ(m2d.Elements[Column][Row], 1.0f);
            } else {
                EXPECT_FLOAT_EQ(m2d.Elements[Column][Row], 0.0f);
            }
        }
    }

    //
    // Test mat3
    //
    HMM_Mat3 m3d = HMM_M3D(1.0f);
    for (int Column = 0; Column < 3; ++Column)
    {
        for (int Row = 0; Row < 3; ++Row)
        {
            if (Column == Row) {
                EXPECT_FLOAT_EQ(m3d.Elements[Column][Row], 1.0f);
            } else {
                EXPECT_FLOAT_EQ(m3d.Elements[Column][Row], 0.0f);
            }
        }
    }

    //
    // Test mat4
    //
    HMM_Mat4 m4d = HMM_M4D(1.0f);
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

TEST(Initialization, Quaternion)
{
    HMM_Quat q = HMM_Q(1.0f, 2.0f, 3.0f, 4.0f);

    EXPECT_FLOAT_EQ(q.X, 1.0f);
    EXPECT_FLOAT_EQ(q.Y, 2.0f);
    EXPECT_FLOAT_EQ(q.Z, 3.0f);
    EXPECT_FLOAT_EQ(q.W, 4.0f);

    EXPECT_FLOAT_EQ(q.Elements[0], 1.0f);
    EXPECT_FLOAT_EQ(q.Elements[1], 2.0f);
    EXPECT_FLOAT_EQ(q.Elements[2], 3.0f);
    EXPECT_FLOAT_EQ(q.Elements[3], 4.0f);

    HMM_Vec4 v = HMM_V4(1.0f, 2.0f, 3.0f, 4.0f);
    HMM_Quat qv = HMM_QV4(v);

    EXPECT_FLOAT_EQ(qv.X, 1.0f);
    EXPECT_FLOAT_EQ(qv.Y, 2.0f);
    EXPECT_FLOAT_EQ(qv.Z, 3.0f);
    EXPECT_FLOAT_EQ(qv.W, 4.0f);
}

#ifdef __cplusplus
TEST(Initialization, MatrixOverloads)
{
    // Operator overloads for matrix columns must allow mutation.

    //
    // Test mat2
    //
    HMM_Mat2 m2 = {0};
    m2[0][0] = 1.0f;
    m2[0][1] = 2.0f;
    m2[1][0] = 3.0f;
    m2[1][1] = 4.0f;
    EXPECT_FLOAT_EQ(m2.Elements[0][0], 1.0f);
    EXPECT_FLOAT_EQ(m2.Elements[0][1], 2.0f);
    EXPECT_FLOAT_EQ(m2.Elements[1][0], 3.0f);
    EXPECT_FLOAT_EQ(m2.Elements[1][1], 4.0f);

    //
    // Test mat3
    //
    HMM_Mat3 m3 = {0};
    m3[0][0] = 1.0f;
    m3[0][1] = 2.0f;
    m3[0][2] = 3.0f;
    m3[1][0] = 4.0f;
    m3[1][1] = 5.0f;
    m3[1][2] = 6.0f;
    m3[2][0] = 7.0f;
    m3[2][1] = 8.0f;
    m3[2][2] = 9.0f;
    EXPECT_FLOAT_EQ(m3.Elements[0][0], 1.0f);
    EXPECT_FLOAT_EQ(m3.Elements[0][1], 2.0f);
    EXPECT_FLOAT_EQ(m3.Elements[0][2], 3.0f);
    EXPECT_FLOAT_EQ(m3.Elements[1][0], 4.0f);
    EXPECT_FLOAT_EQ(m3.Elements[1][1], 5.0f);
    EXPECT_FLOAT_EQ(m3.Elements[1][2], 6.0f);
    EXPECT_FLOAT_EQ(m3.Elements[2][0], 7.0f);
    EXPECT_FLOAT_EQ(m3.Elements[2][1], 8.0f);
    EXPECT_FLOAT_EQ(m3.Elements[2][2], 9.0f);

    //
    // Test mat4
    //
    HMM_Mat4 m4 = {0};
    m4[0][0] = 1.0f;
    m4[0][1] = 2.0f;
    m4[0][2] = 3.0f;
    m4[0][3] = 4.0f;
    m4[1][0] = 5.0f;
    m4[1][1] = 6.0f;
    m4[1][2] = 7.0f;
    m4[1][3] = 8.0f;
    m4[2][0] = 9.0f;
    m4[2][1] = 10.0f;
    m4[2][2] = 11.0f;
    m4[2][3] = 12.0f;
    m4[3][0] = 13.0f;
    m4[3][1] = 14.0f;
    m4[3][2] = 15.0f;
    m4[3][3] = 16.0f;
    EXPECT_FLOAT_EQ(m4.Elements[0][0], 1.0f);
    EXPECT_FLOAT_EQ(m4.Elements[0][1], 2.0f);
    EXPECT_FLOAT_EQ(m4.Elements[0][2], 3.0f);
    EXPECT_FLOAT_EQ(m4.Elements[0][3], 4.0f);
    EXPECT_FLOAT_EQ(m4.Elements[1][0], 5.0f);
    EXPECT_FLOAT_EQ(m4.Elements[1][1], 6.0f);
    EXPECT_FLOAT_EQ(m4.Elements[1][2], 7.0f);
    EXPECT_FLOAT_EQ(m4.Elements[1][3], 8.0f);
    EXPECT_FLOAT_EQ(m4.Elements[2][0], 9.0f);
    EXPECT_FLOAT_EQ(m4.Elements[2][1], 10.0f);
    EXPECT_FLOAT_EQ(m4.Elements[2][2], 11.0f);
    EXPECT_FLOAT_EQ(m4.Elements[2][3], 12.0f);
    EXPECT_FLOAT_EQ(m4.Elements[3][0], 13.0f);
    EXPECT_FLOAT_EQ(m4.Elements[3][1], 14.0f);
    EXPECT_FLOAT_EQ(m4.Elements[3][2], 15.0f);
    EXPECT_FLOAT_EQ(m4.Elements[3][3], 16.0f);
}
#endif
