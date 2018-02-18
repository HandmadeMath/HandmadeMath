#ifndef HANDMADETEST_H
#define HANDMADETEST_H

#include <float.h>
#include <stdio.h>
#include <string.h>

#include "initializer.h"

#define RESET "\033[0m"
#define RED   "\033[31m"
#define GREEN "\033[32m"

#define INITIAL_ARRAY_SIZE 1024

typedef struct hmt_testresult_struct {
    int count_cases;
    int count_failures;
} hmt_testresult;

typedef void (*hmt_test_func)(hmt_testresult*);

typedef struct hmt_test_struct {
    const char* name;
    hmt_test_func func;
} hmt_test;

typedef struct hmt_category_struct {
    const char* name;
    int num_tests;
    int tests_capacity;
    hmt_test* tests;
} hmt_category;

int num_categories = 0;
int category_capacity = INITIAL_ARRAY_SIZE;
hmt_category* categories = 0;

void print_category(hmt_category c) {
    printf("Name: %s\n", c.name);
    printf("Number of tests: %d\n", c.num_tests);
    printf("Tests capacity: %d\n", c.tests_capacity);
    printf("Tests: %p\n", c.tests);
}

void print_test(hmt_test t) {
    printf("Name: %s\n", t.name);
    printf("Func: %p\n", t.func);
}

hmt_category new_category(const char* name) {
    hmt_category cat = {
        .name = name,
        .num_tests = 0,
        .tests_capacity = INITIAL_ARRAY_SIZE,
        .tests = (hmt_test*) malloc(INITIAL_ARRAY_SIZE * sizeof(hmt_test))
    };

    return cat;
}

hmt_test new_test(const char* name, hmt_test_func func) {
    hmt_test test = {
        .name = name,
        .func = func
    };

    return test;
}

int hmt_register_test(const char* category, const char* name, hmt_test_func func) {
    // initialize categories array if not initialized
    if (!categories) {
        categories = (hmt_category*) malloc(category_capacity * sizeof(hmt_category));
    }

    // Find the matching category, if possible
    int cat_index;
    for (cat_index = 0; cat_index < num_categories; cat_index++) {
        if (strcmp(categories[cat_index].name, category) == 0) {
            break;
        }
    }

    // Expand the array of categories if necessary
    if (cat_index >= category_capacity) {
        // TODO: If/when we ever split HandmadeTest off into its own package,
        // we should start with a smaller initial capacity and dynamically expand.
    }

    // Add a new category if necessary
    if (cat_index >= num_categories) {
        categories[cat_index] = new_category(category);
        num_categories++;
    }

    hmt_category* cat = &categories[cat_index];

    // Add the test to the category
    if (cat->num_tests >= cat->tests_capacity) {
        // TODO: If/when we ever split HandmadeTest off into its own package,
        // we should start with a smaller initial capacity and dynamically expand.
    }
    cat->tests[cat->num_tests] = new_test(name, func);
    cat->num_tests++;

    return 0;
}

int hmt_run_all_tests() {
    int count_alltests = 0;
    int count_allfailedtests = 0; // failed test cases
    int count_allfailures = 0; // failed asserts

    for (int i = 0; i < num_categories; i++) {
        hmt_category cat = categories[i];
        int count_catfailedtests = 0; 
        int count_catfailures = 0;

        printf("\n%s:\n", cat.name);

        for (int j = 0; j < cat.num_tests; j++) {
            hmt_test test = cat.tests[j];

            printf("    %s:", test.name);

            hmt_testresult result = {
                .count_cases = 0,
                .count_failures = 0
            };
            test.func(&result);

            count_catfailures += result.count_failures;

            if (result.count_failures > 0) {
                count_catfailedtests++;
                printf("\n      " RED "(%d/%d passed)" RESET, result.count_cases - result.count_failures, result.count_cases);
                printf("\n");
            } else {
                printf(GREEN " [PASS] (%d/%d passed) \n" RESET, result.count_cases - result.count_failures, result.count_cases);
            }
        }

        count_alltests += cat.num_tests;
        count_allfailedtests += count_catfailedtests;
        count_allfailures += count_catfailures;

        printf("%d/%d tests passed, %d failures\n", cat.num_tests - count_catfailedtests, cat.num_tests, count_catfailures);
    }

    if (count_allfailedtests > 0) {
        printf(RED);
    } else {
        printf(GREEN);
    }
    printf("\n%d/%d tests passed overall, %d failures\n" RESET, count_alltests - count_allfailedtests, count_alltests, count_allfailures);

    printf("\n");

    return (count_allfailedtests > 0);
}

#define _TEST_FUNCNAME(category, name) category ## _ ## name
#define _TEST_FUNCNAME_INIT(category, name) category ## _ ## name ## _init

#define TEST(category, name) \
void _TEST_FUNCNAME(category, name)(hmt_testresult* _result); \
INITIALIZER(_TEST_FUNCNAME_INIT(category, name)) { \
    hmt_register_test(#category, #name, _TEST_FUNCNAME(category, name)); \
} \
void _TEST_FUNCNAME(category, name)(hmt_testresult* _result)

#define CASE_START() \
    _result->count_cases++;

#define CASE_FAIL() \
    _result->count_failures++; \
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

#endif // HANDMADETEST_H
