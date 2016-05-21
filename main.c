#define HANDMADE_MATH_IMPLEMENTATION
#include "HandmadeMath.h"

int
main(void)
{
    hmm_mat4 MatrixOne = HMM_Mat4d(1.0f);
    hmm_mat4 MatrixTwo = HMM_Mat4d(4.0f);

    hmm_mat4 MatrixResult = HMM_MultiplyMat4(MatrixOne, MatrixTwo);
    
    hmm_v2 VecOne = HMM_Vec2(1.0f, 1.0f);
    hmm_v2 VecTwo = HMM_Vec2(3.0f, 3.0f);

    hmm_v2 Result = HMM_AddVec2(VecOne, VecTwo);

    return(0);
}
