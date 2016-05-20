#define HANDMADE_MATH_IMPLEMENTATION
#include "HandmadeMath.h"

int
main(void)
{
    v2 VecOne = Vec2(1.0f, 1.0f);
    v2 VecTwo = Vec2(3.0f, 3.0f);

    v2 Result = AddVec2(VecOne, VecTwo);
}
