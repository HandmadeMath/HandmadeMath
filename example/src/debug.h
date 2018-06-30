#include <stdio.h>

#ifndef DEBUG_H
#define DEBUG_H

#include "HandmadeMath.h"

void printVec3(hmm_vec3 v) {
    printf("%f\t%f\t%f\n", v.X, v.Y, v.Z);
}

void printVec4(hmm_vec4 v) {
    printf("%f\t%f\t%f\t%f\n", v.X, v.Y, v.Z, v.W);
}

void printQuaternion(hmm_quaternion q) {
    printf("%f\t%f\t%f\t%f\n", q.X, q.Y, q.Z, q.W);
}

void printMat4(hmm_mat4 m) {
    for (int r = 0; r < 4; r++) {
        printf("| %f\t%f\t%f\t%f |\n", m[0][r], m[1][r], m[2][r], m[3][r]);
    }
}

#endif
