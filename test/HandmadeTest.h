#ifndef HANDMADETEST_H
#define HANDMADETEST_H

#include <float.h>
#include <stdio.h>

int hmt_count_tests = 0;
int hmt_count_failedtests = 0;
int hmt_count_failures = 0;

#define RESET "\033[0m"
#define RED   "\033[31m"
#define GREEN "\033[32m"

#define CATEGORY_BEGIN(name) { \
    int count_categorytests = 0; \
    int count_categoryfailedtests = 0; \
    int count_categoryfailures = 0; \
    printf("\n" #name ":\n");
#define CATEGORY_END(name) \
    hmt_count_tests += count_categorytests; \
    hmt_count_failedtests += count_categoryfailedtests; \
    hmt_count_failures += count_categoryfailures; \
    printf("%d/%d tests passed, %d failures\n", count_categorytests - count_categoryfailedtests, count_categorytests, count_categoryfailures); \
}

#define TEST_BEGIN(name) { \
    int count_testcases = 0, count_testfailures = 0; \
    count_categorytests++; \
    printf("    " #name ":");
#define TEST_END() \
    count_categoryfailures += count_testfailures; \
    if (count_testfailures > 0) { \
        count_categoryfailedtests++; \
        printf("\n      " RED "(%d/%d passed)" RESET, count_testcases - count_testfailures, count_testcases); \
        printf("\n"); \
    } else { \
        printf(GREEN " [PASS] (%d/%d passed) \n" RESET, count_testcases - count_testfailures, count_testcases); \
    } \
}

#define CASE_START() \
    count_testcases++;

#define CASE_FAIL() \
    count_testfailures++; \
    printf("\n      - " RED "[FAIL] (%d) " RESET, __LINE__);

/*
 * Asserts and expects
 */
#define EXPECT_TRUE(_actual) do { \
    CASE_START(); \
    if (!(_actual)) { \
        CASE_FAIL(); \
        printf("Expected true but got something false"); \
    } \
} while (0)

#define EXPECT_FALSE(_actual) do { \
    CASE_START(); \
    if (_actual) { \
        CASE_FAIL(); \
        printf("Expected false but got something true"); \
    } \
} while (0)

#define EXPECT_FLOAT_EQ(_actual, _expected) do { \
    CASE_START(); \
    float actual = (_actual); \
    float diff = actual - (_expected); \
    if (diff < -FLT_EPSILON || FLT_EPSILON < diff) { \
        CASE_FAIL(); \
        printf("Expected %f, got %f", (_expected), actual); \
    } \
} while (0)

#define EXPECT_NEAR(_actual, _expected, _epsilon) do { \
    CASE_START(); \
    float actual = (_actual); \
    float diff = actual - (_expected); \
    if (diff < -(_epsilon) || (_epsilon) < diff) { \
        CASE_FAIL(); \
        printf("Expected %f, got %f", (_expected), actual); \
    } \
} while (0)

#define EXPECT_LT(_actual, _expected) do { \
    CASE_START(); \
    if ((_actual) >= (_expected)) { \
        CASE_FAIL(); \
        printf("Expected %f to be less than %f", (_actual), (_expected)); \
    } \
} while (0)

#define EXPECT_GT(_actual, _expected) do { \
    CASE_START(); \
    if ((_actual) <= (_expected)) { \
        CASE_FAIL(); \
        printf("Expected %f to be greater than %f", (_actual), (_expected)); \
    } \
} while (0)

#endif
