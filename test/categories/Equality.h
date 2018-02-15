#include "../HandmadeTest.h"

TEST(Equality, Vec2)
{
    hmm_vec2 a = HMM_Vec2(1.0f, 2.0f);
    hmm_vec2 b = HMM_Vec2(1.0f, 2.0f);
    hmm_vec2 c = HMM_Vec2(3.0f, 4.0f);

    EXPECT_TRUE(HMM_EqualsVec2(a, b));
    EXPECT_FALSE(HMM_EqualsVec2(a, c));

#ifdef __cplusplus
    EXPECT_TRUE(HMM_Equals(a, b));
    EXPECT_FALSE(HMM_Equals(a, c));

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
#endif
}

TEST(Equality, Vec3)
{
    hmm_vec3 a = HMM_Vec3(1.0f, 2.0f, 3.0f);
    hmm_vec3 b = HMM_Vec3(1.0f, 2.0f, 3.0f);
    hmm_vec3 c = HMM_Vec3(4.0f, 5.0f, 6.0f);

    EXPECT_TRUE(HMM_EqualsVec3(a, b));
    EXPECT_FALSE(HMM_EqualsVec3(a, c));

#ifdef __cplusplus
    EXPECT_TRUE(HMM_Equals(a, b));
    EXPECT_FALSE(HMM_Equals(a, c));

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
#endif
}

TEST(Equality, Vec4)
{
    hmm_vec4 a = HMM_Vec4(1.0f, 2.0f, 3.0f, 4.0f);
    hmm_vec4 b = HMM_Vec4(1.0f, 2.0f, 3.0f, 4.0f);
    hmm_vec4 c = HMM_Vec4(5.0f, 6.0f, 7.0f, 8.0f);

    EXPECT_TRUE(HMM_EqualsVec4(a, b));
    EXPECT_FALSE(HMM_EqualsVec4(a, c));

#ifdef __cplusplus
    EXPECT_TRUE(HMM_Equals(a, b));
    EXPECT_FALSE(HMM_Equals(a, c));

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
#endif
}
