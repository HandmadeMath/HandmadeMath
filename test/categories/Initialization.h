#include "../HandmadeTest.h"

TEST(Initialization, Vectors)
{
    //
    // Test vec2
    //
    hmm_vec2 v2 = HMM_Vec2(1.0f, 2.0f);
    hmm_vec2 v2i = HMM_Vec2i(1, 2);

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
#ifdef __cplusplus
    EXPECT_FLOAT_EQ(v2i[0], 1.0f);
    EXPECT_FLOAT_EQ(v2i[1], 2.0f);
#endif

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
#ifdef __cplusplus
    EXPECT_FLOAT_EQ(v3[0], 1.0f);
    EXPECT_FLOAT_EQ(v3[1], 2.0f);
    EXPECT_FLOAT_EQ(v3[2], 3.0f);
#endif

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
#ifdef __cplusplus
    EXPECT_FLOAT_EQ(v3i[0], 1.0f);
    EXPECT_FLOAT_EQ(v3i[1], 2.0f);
    EXPECT_FLOAT_EQ(v3i[2], 3.0f);
#endif

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
#ifdef __cplusplus
    EXPECT_FLOAT_EQ(v4[0], 1.0f);
    EXPECT_FLOAT_EQ(v4[1], 2.0f);
    EXPECT_FLOAT_EQ(v4[2], 3.0f);
    EXPECT_FLOAT_EQ(v4[3], 4.0f);
#endif

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
#ifdef __cplusplus
    EXPECT_FLOAT_EQ(v4i[0], 1.0f);
    EXPECT_FLOAT_EQ(v4i[1], 2.0f);
    EXPECT_FLOAT_EQ(v4i[2], 3.0f);
    EXPECT_FLOAT_EQ(v4i[3], 4.0f);
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
    hmm_mat4 m4 = HMM_Mat4();
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

TEST(Initialization, Quaternion)
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
