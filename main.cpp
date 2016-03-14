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

    vec2 ResultVector = TestVector1 - TestVector2;


    mat4 MatrixZero = Mat4();
    mat4 Matrix1 = Mat4d(5.0f);

    mat4 Matrix2 = Mat4d(2.0f);

    mat4 ResultMatrix = MultiplyMat4(Matrix1, Matrix2);

    mat4 ResultMatrix2 = Matrix1 * Matrix2;
    _getch();
    return(0);
}
