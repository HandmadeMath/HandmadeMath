#define HANDMADE_MATH_IMPLEMENTATION
#define HANDMADE_MATH_CPP_MODE
#include "HandmadeMath.h"

int
main(void)
{
    hmm_mat4 MatrixOne = HMM_Mat4d(1.0f);
    hmm_mat4 MatrixTwo = HMM_Mat4d(4.0f);

    hmm_mat4 ResultMatrix = MatrixOne * MatrixTwo;

    hmm_mat4 OrthographicMatrix = HMM_Orthographic(-1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 1.0f);
    hmm_mat4 PrespectiveMatrix = HMM_Perspective(45.0f, 16/9, 0.0f, 100.0f);

    hmm_mat4 TranslationMatrix = HMM_Translate(HMM_Vec3(1.0f, 0.0f, 0.0f));
    hmm_mat4 RotationMatrix = HMM_Rotate(45.0f, HMM_Vec3(1, 0, 0));

    hmm_mat4 LookAtMatrix = HMM_LookAt(HMM_Vec3(0, 1, 0), HMM_Vec3(0, 0, 0), HMM_Vec3(1, 0, 0));

    hmm_mat4 ScaleMatrix = HMM_Scale(HMM_Vec3(1.0f, 0.0f, 0.0f));

    float SquareRootResult = HMM_SquareRoot(36);
    
    return(0);
}
