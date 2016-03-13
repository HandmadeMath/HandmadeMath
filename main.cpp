#define HANDMADE_MATH_IMPLEMENTATION
#define HANDMADE_MATH_CPP_MODE
#include "HandmadeMath.h"

#include <stdio.h>
#include <conio.h>

int
main(int ArgC, char **ArgV)
{
    vec2 TestVector1 = V2(50.0f, 36.0f);
    vec2 TestVector2 = V2(5.0f, 6.0f);

    vec2 Result = TestVector1 - TestVector2;
    
    _getch();
    return(0);
}
