#include "../HandmadeTest.h"

TEST(Equality, Vec2)
{
    HMM_Vec2 a = HMM_V2(1.0f, 2.0f);
    HMM_Vec2 b = HMM_V2(1.0f, 2.0f);
    HMM_Vec2 c = HMM_V2(3.0f, 4.0f);

    EXPECT_TRUE(HMM_EqV2(a, b));
    EXPECT_FALSE(HMM_EqV2(a, c));

#ifdef __cplusplus
    EXPECT_TRUE(HMM_Eq(a, b));
    EXPECT_FALSE(HMM_Eq(a, c));

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);

    EXPECT_FALSE(a != b);
    EXPECT_TRUE(a != c);
#endif
}

TEST(Equality, Vec3)
{
    HMM_Vec3 a = HMM_V3(1.0f, 2.0f, 3.0f);
    HMM_Vec3 b = HMM_V3(1.0f, 2.0f, 3.0f);
    HMM_Vec3 c = HMM_V3(4.0f, 5.0f, 6.0f);

    EXPECT_TRUE(HMM_EqV3(a, b));
    EXPECT_FALSE(HMM_EqV3(a, c));

#ifdef __cplusplus
    EXPECT_TRUE(HMM_Eq(a, b));
    EXPECT_FALSE(HMM_Eq(a, c));

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);

    EXPECT_FALSE(a != b);
    EXPECT_TRUE(a != c);
#endif
}

TEST(Equality, Vec4)
{
    HMM_Vec4 a = HMM_V4(1.0f, 2.0f, 3.0f, 4.0f);
    HMM_Vec4 b = HMM_V4(1.0f, 2.0f, 3.0f, 4.0f);
    HMM_Vec4 c = HMM_V4(5.0f, 6.0f, 7.0f, 8.0f);

    EXPECT_TRUE(HMM_EqV4(a, b));
    EXPECT_FALSE(HMM_EqV4(a, c));

#ifdef __cplusplus
    EXPECT_TRUE(HMM_Eq(a, b));
    EXPECT_FALSE(HMM_Eq(a, c));

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);

    EXPECT_FALSE(a != b);
    EXPECT_TRUE(a != c);
#endif
}
