/*
  HANDMADE_MATH_IMPLEMENTATION:
    This is for the implementation you want this.

  HANDMADE_MATH_CPP_MODE: 
    This will give the function overloaded and operator overloaded version of the functions
*/

#include <conio.h>

#define HANDMADE_MATH_IMPLEMENTATION
#define HANDMADE_MATH_CPP_MODE

#include "HandmadeMath.h"

int
main(int ArgC, char **ArgV)
{
    vec2 VectorOne = V2(6.0f, 8.0f);
    vec2 VectorTwo = V2(3.0f, 2.0f);

    vec2 Result = DivideV2(VectorOne, VectorTwo);

    _getch();
    return(0);
}
