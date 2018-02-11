
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define HANDMADE_MATH_IMPLEMENTATION
#define HANDMADE_MATH_NO_SSE
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
    }
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);

    return BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
}

int main()
{
    long total = 0;
    for (int i = 0; i < NUM_CASES; i++) {
        long result = benchmark_vec4_add();
        total += result;

        printf("DURATION: %ld (%f seconds)\n", result, result / (float) BILLION);
    }

    printf("AVERAGE: %ld (%f seconds)\n", total / NUM_CASES, total / (float) NUM_CASES / BILLION);
}

int main2()
{
    printf("Sleeping for 10 seconds...\n");
    sleep(10);

    long total = 0;
    for (int i = 0; i < NUM_CASES; i++) {
        long result = benchmark_matrix_transpose();
        total += result;

        printf("DURATION: %ld (%f seconds)\n", result, result / (float) BILLION);
    }

    printf("AVERAGE: %ld (%f seconds)\n", total / NUM_CASES, total / (float) NUM_CASES / BILLION);
}

