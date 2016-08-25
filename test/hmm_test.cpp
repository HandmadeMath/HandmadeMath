
#define HANDMADE_MATH_CPP_MODE
#include "../HandmadeMath.h"

#include "gtest/gtest.h"


TEST(Initialization, Vectors)
{
    //
    // Test vec2
    // 
    hmm_vec2 v2 = HMM_Vec2(1.0f, 2.0f);
    hmm_vec2 v2i = HMM_Vec2(1, 2);

    EXPECT_FLOAT_EQ(v2.Elements[0], 1.0f);
    EXPECT_FLOAT_EQ(v2.Elements[1], 2.0f);

    EXPECT_FLOAT_EQ(v2i.Elements[0], 1.0f);
    EXPECT_FLOAT_EQ(v2i.Elements[1], 2.0f);

    //
    // Test vec3
    //
    hmm_vec3 v3 = HMM_Vec3(1.0f, 2.0f, 3.0f);
    hmm_vec3 v3i = HMM_Vec3i(1, 2, 3);

    EXPECT_FLOAT_EQ(v3.Elements[0], 1.0f);
    EXPECT_FLOAT_EQ(v3.Elements[1], 2.0f);
    EXPECT_FLOAT_EQ(v3.Elements[2], 3.0f);

    EXPECT_FLOAT_EQ(v3i.Elements[0], 1.0f);
    EXPECT_FLOAT_EQ(v3i.Elements[1], 2.0f);
    EXPECT_FLOAT_EQ(v3i.Elements[2], 3.0f);

    //
    // Test vec4
    //
    hmm_vec4 v4 = HMM_Vec4(1.0f, 2.0f, 3.0f, 4.0f);
    hmm_vec4 v4i = HMM_Vec4i(1, 2, 3, 4);

    EXPECT_FLOAT_EQ(v4.Elements[0], 1.0f);
    EXPECT_FLOAT_EQ(v4.Elements[1], 2.0f);
    EXPECT_FLOAT_EQ(v4.Elements[2], 3.0f);
    EXPECT_FLOAT_EQ(v4.Elements[3], 4.0f);

    EXPECT_FLOAT_EQ(v4i.Elements[0], 1.0f);
    EXPECT_FLOAT_EQ(v4i.Elements[1], 2.0f);
    EXPECT_FLOAT_EQ(v4i.Elements[2], 3.0f);
    EXPECT_FLOAT_EQ(v4i.Elements[3], 4.0f);
}
