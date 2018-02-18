/*
  HandmadeTest.h

  This is Handmade Math's test framework. It is fully compatible with both C
  and C++, although it requires some compiler-specific features.

  The basic way of creating a test is using the TEST macro, which registers a
  single test to be run:

     TEST(MyCategory, MyTestName) {
        // test code, including asserts/expects
     }

  The main function of your test code should then call hmt_run_all_tests and
  return the result:

     int main() {
        return hmt_run_all_tests();
     }

  =============================================================================

  If Handmade Test's macros are conflicting with existing macros in your
  project, you may define HMT_SAFE_MACROS before you include HandmadeTest.h.
  You may then prefix each macro with HMT_. For example, you may use HMT_TEST
  instead of TEST and HMT_EXPECT_TRUE instead of EXPECT_TRUE.

 */

#ifndef HANDMADETEST_H
#define HANDMADETEST_H

#include <float.h>
#include <stdio.h>
#include <string.h>

#include "initializer.h"

#define HMT_RESET "\033[0m"
#define HMT_RED   "\033[31m"
#define HMT_GREEN "\033[32m"

#define HMT_INITIAL_ARRAY_SIZE 1024

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

int hmt_num_categories = 0;
int hmt_category_capacity = HMT_INITIAL_ARRAY_SIZE;
hmt_category* categories = 0;

hmt_category _hmt_new_category(const char* name) {
    hmt_category cat = {
        .name = name,
        .num_tests = 0,
        .tests_capacity = HMT_INITIAL_ARRAY_SIZE,
        .tests = (hmt_test*) malloc(HMT_INITIAL_ARRAY_SIZE * sizeof(hmt_test))
    };

    return cat;
}

hmt_test _hmt_new_test(const char* name, hmt_test_func func) {
    hmt_test test = {
        .name = name,
        .func = func
    };

    return test;
}

int hmt_register_test(const char* category, const char* name, hmt_test_func func) {
    // initialize categories array if not initialized
    if (!categories) {
        categories = (hmt_category*) malloc(hmt_category_capacity * sizeof(hmt_category));
    }

    // Find the matching category, if possible
    int cat_index;
    for (cat_index = 0; cat_index < hmt_num_categories; cat_index++) {
        if (strcmp(categories[cat_index].name, category) == 0) {
            break;
        }
    }

    // Expand the array of categories if necessary
    if (cat_index >= hmt_category_capacity) {
        // TODO: If/when we ever split HandmadeTest off into its own package,
        // we should start with a smaller initial capacity and dynamically expand.
    }

    // Add a new category if necessary
    if (cat_index >= hmt_num_categories) {
        categories[cat_index] = _hmt_new_category(category);
        hmt_num_categories++;
    }

    hmt_category* cat = &categories[cat_index];

    // Add the test to the category
    if (cat->num_tests >= cat->tests_capacity) {
        // TODO: If/when we ever split HandmadeTest off into its own package,
        // we should start with a smaller initial capacity and dynamically expand.
    }
    cat->tests[cat->num_tests] = _hmt_new_test(name, func);
    cat->num_tests++;

    return 0;
}

int hmt_run_all_tests() {
    int count_alltests = 0;
    int count_allfailedtests = 0; // failed test cases
    int count_allfailures = 0; // failed asserts

    for (int i = 0; i < hmt_num_categories; i++) {
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
                printf("\n      " HMT_RED "(%d/%d passed)" HMT_RESET, result.count_cases - result.count_failures, result.count_cases);
                printf("\n");
            } else {
                printf(HMT_GREEN " [PASS] (%d/%d passed) \n" HMT_RESET, result.count_cases - result.count_failures, result.count_cases);
            }
        }

        count_alltests += cat.num_tests;
        count_allfailedtests += count_catfailedtests;
        count_allfailures += count_catfailures;

        printf("%d/%d tests passed, %d failures\n", cat.num_tests - count_catfailedtests, cat.num_tests, count_catfailures);
    }

    if (count_allfailedtests > 0) {
        printf(HMT_RED);
    } else {
        printf(HMT_GREEN);
    }
    printf("\n%d/%d tests passed overall, %d failures\n" HMT_RESET, count_alltests - count_allfailedtests, count_alltests, count_allfailures);

    printf("\n");

    return (count_allfailedtests > 0);
}

#define _HMT_TEST_FUNCNAME(category, name) category ## _ ## name
#define _HMT_TEST_FUNCNAME_INIT(category, name) category ## _ ## name ## _init

#define HMT_TEST(category, name) \
void _HMT_TEST_FUNCNAME(category, name)(hmt_testresult* _result); \
INITIALIZER(_HMT_TEST_FUNCNAME_INIT(category, name)) { \
    hmt_register_test(#category, #name, _HMT_TEST_FUNCNAME(category, name)); \
} \
void _HMT_TEST_FUNCNAME(category, name)(hmt_testresult* _result)

#define _HMT_CASE_START() \
    _result->count_cases++;

#define _HMT_CASE_FAIL() \
    _result->count_failures++; \
    printf("\n      - " HMT_RED "[FAIL] (%d) " HMT_RESET, __LINE__);

/*
 * Asserts and expects
 */
#define HMT_EXPECT_TRUE(_actual) do { \
    _HMT_CASE_START(); \
    if (!(_actual)) { \
        _HMT_CASE_FAIL(); \
        printf("Expected true but got something false"); \
    } \
} while (0)

#define HMT_EXPECT_FALSE(_actual) do { \
    _HMT_CASE_START(); \
    if (_actual) { \
        _HMT_CASE_FAIL(); \
        printf("Expected false but got something true"); \
    } \
} while (0)

#define HMT_EXPECT_FLOAT_EQ(_actual, _expected) do { \
    _HMT_CASE_START(); \
    float actual = (_actual); \
    float diff = actual - (_expected); \
    if (diff < -FLT_EPSILON || FLT_EPSILON < diff) { \
        _HMT_CASE_FAIL(); \
        printf("Expected %f, got %f", (_expected), actual); \
    } \
} while (0)

#define HMT_EXPECT_NEAR(_actual, _expected, _epsilon) do { \
    _HMT_CASE_START(); \
    float actual = (_actual); \
    float diff = actual - (_expected); \
    if (diff < -(_epsilon) || (_epsilon) < diff) { \
        _HMT_CASE_FAIL(); \
        printf("Expected %f, got %f", (_expected), actual); \
    } \
} while (0)

#define HMT_EXPECT_LT(_actual, _expected) do { \
    _HMT_CASE_START(); \
    if ((_actual) >= (_expected)) { \
        _HMT_CASE_FAIL(); \
        printf("Expected %f to be less than %f", (_actual), (_expected)); \
    } \
} while (0)

#define HMT_EXPECT_GT(_actual, _expected) do { \
    _HMT_CASE_START(); \
    if ((_actual) <= (_expected)) { \
        _HMT_CASE_FAIL(); \
        printf("Expected %f to be greater than %f", (_actual), (_expected)); \
    } \
} while (0)

#ifndef HMT_SAFE_MACROS
// Friendly defines
#define TEST(category, name) HMT_TEST(category, name)
#define EXPECT_TRUE(_actual) HMT_EXPECT_TRUE(_actual)
#define EXPECT_FALSE(_actual) HMT_EXPECT_FALSE(_actual)
#define EXPECT_FLOAT_EQ(_actual, _expected) HMT_EXPECT_FLOAT_EQ(_actual, _expected)
#define EXPECT_NEAR(_actual, _expected, _epsilon) HMT_EXPECT_NEAR(_actual, _expected, _epsilon)
#define EXPECT_LT(_actual, _expected) HMT_EXPECT_LT(_actual, _expected)
#define EXPECT_GT(_actual, _expected) HMT_EXPECT_GT(_actual, _expected)
#endif // HMT_SAFE_MACROS

#endif // HANDMADETEST_H
