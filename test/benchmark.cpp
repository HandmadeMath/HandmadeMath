
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "glm/glm/glm.hpp"

#define HANDMADE_MATH_IMPLEMENTATION
// #define HANDMADE_MATH_NO_SSE
#include "../HandmadeMath.h"

#define BILLION 1000000000L

#define NUM_CASES 5

long benchmark_vec4_add()
{
    struct timespec start, end;

    srand(1);

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    for (int i = 0; i < 100000000; i++) {
        hmm_vec4 a = HMM_Vec4(rand(), rand(), rand(), rand());
        hmm_vec4 b = HMM_Vec4(rand(), rand(), rand(), rand());

        hmm_vec4 result = HMM_AddVec4(a, b);
    }
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);

    return BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
}

long benchmark_vec4_add_glm()
{
    struct timespec start, end;

    srand(1);

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    for (int i = 0; i < 100000000; i++) {
        glm::vec4 a(rand(), rand(), rand(), rand());
        glm::vec4 b(rand(), rand(), rand(), rand());

        glm::vec4 result = a + b;
    }
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);

    return BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
}

long benchmark_matrix_transpose()
{
    struct timespec start, end;

    srand(1);

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    for (int i = 0; i < 100000000; i++) {
        hmm_mat4 a;
        for (int column = 0; column < 4; column++) {
            for (int row = 0; row < 4; row++) {
                a.Elements[column][row] = rand();
            }
        }

        hmm_mat4 result = HMM_Transpose(a);
        // hmm_mat4 result = a;
    }
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);

    return BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
}

long benchmark_matrix_transpose_glm()
{
    struct timespec start, end;

    srand(1);

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    for (int i = 0; i < 100000000; i++) {
        glm::mat4 a;
        for (int column = 0; column < 4; column++) {
            for (int row = 0; row < 4; row++) {
                a[column][row] = rand();
            }
        }

        glm::mat4 result = glm::transpose(a);
        // glm::mat4 result = a;
    }
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);

    return BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
}

long benchmark_matrix_multiply()
{
    struct timespec start, end;

    srand(1);

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    for (int i = 0; i < 100000000; i++) {
        hmm_mat4 a, b;
        for (int column = 0; column < 4; column++) {
            for (int row = 0; row < 4; row++) {
                a.Elements[column][row] = rand();
                b.Elements[column][row] = rand();
            }
        }

        hmm_mat4 result = HMM_MultiplyMat4(a, b);
    }
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
    // clock_gettime(CLOCK_MONOTONIC_RAW, &end);

    return BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
}

long benchmark_matrix_multiply_glm()
{
    struct timespec start, end;

    srand(1);

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    for (int i = 0; i < 100000000; i++) {
        glm::mat4 a, b;
        for (int column = 0; column < 4; column++) {
            for (int row = 0; row < 4; row++) {
                a[column][row] = rand();
                b[column][row] = rand();
            }
        }

        glm::mat4 result = a * b;
    }
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);

    return BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
}

int main_add_hmm()
// int main()
{
    long total = 0;
    for (int i = 0; i < NUM_CASES; i++) {
        long result = benchmark_vec4_add();
        total += result;

        printf("DURATION: %ld (%f seconds)\n", result, result / (float) BILLION);
    }

    printf("AVERAGE: %ld (%f seconds)\n", total / NUM_CASES, total / (float) NUM_CASES / BILLION);
}

int main_add_glm()
// int main()
{
    long total = 0;
    for (int i = 0; i < NUM_CASES; i++) {
        long result = benchmark_vec4_add_glm();
        total += result;

        printf("DURATION: %ld (%f seconds)\n", result, result / (float) BILLION);
    }

    printf("AVERAGE: %ld (%f seconds)\n", total / NUM_CASES, total / (float) NUM_CASES / BILLION);
}

int main_transpose_hmm()
// int main()
{
    long total = 0;
    for (int i = 0; i < NUM_CASES; i++) {
        long result = benchmark_matrix_transpose();
        total += result;

        printf("DURATION: %ld (%f seconds)\n", result, result / (float) BILLION);
    }

    printf("AVERAGE: %ld (%f seconds)\n", total / NUM_CASES, total / (float) NUM_CASES / BILLION);
}

int main_transpose_glm()
// int main()
{
    long total = 0;
    for (int i = 0; i < NUM_CASES; i++) {
        long result = benchmark_matrix_transpose_glm();
        total += result;

        printf("DURATION: %ld (%f seconds)\n", result, result / (float) BILLION);
    }

    printf("AVERAGE: %ld (%f seconds)\n", total / NUM_CASES, total / (float) NUM_CASES / BILLION);
}

// int main_multiply_hmm()
int main()
{
    long total = 0;
    for (int i = 0; i < NUM_CASES; i++) {
        long result = benchmark_matrix_multiply();
        total += result;

        printf("DURATION: %ld (%f seconds)\n", result, result / (float) BILLION);
    }

    printf("AVERAGE: %ld (%f seconds)\n", total / NUM_CASES, total / (float) NUM_CASES / BILLION);
}

int main_multiply_glm()
// int main()
{
    long total = 0;
    for (int i = 0; i < NUM_CASES; i++) {
        long result = benchmark_matrix_multiply_glm();
        total += result;

        printf("DURATION: %ld (%f seconds)\n", result, result / (float) BILLION);
    }

    printf("AVERAGE: %ld (%f seconds)\n", total / NUM_CASES, total / (float) NUM_CASES / BILLION);
}
