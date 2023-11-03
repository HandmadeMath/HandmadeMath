/*
  HandmadeTest.h

  This is Handmade Math's test framework. It is fully compatible with both C
  and C++, although it requires some compiler-specific features.

  To use Handmade Test, you must #define HANDMADE_TEST_IMPLEMENTATION in
  exactly one C or C++ file that includes the header, like this:

    #define HANDMADE_TEST_IMPLEMENTATION
    #include "HandmadeTest.h"

  The basic way of creating a test is using the TEST macro, which registers a
  single test to be run:

    TEST(MyCategory, MyTestName) {
        // test code, including asserts/expects
    }

  Handmade Test also provides macros you can use to check the coverage of
  important parts of your code. Define a coverage case by using the COVERAGE
  macro outside the function you wish to test, providing both a name and the
  number of asserts you expect to see covered over the course of your test.
  Then use the ASSERT_COVERED macro in every part of the function you wish to
  check coverage on. For example:

    COVERAGE(MyCoverageCase, 3)
    void MyFunction(int a, int b) {
        if (a > b) {
            ASSERT_COVERED(MyCoverageCase);
            return 10;
        } else if (a < b) {
            ASSERT_COVERED(MyCoverageCase);
            return -10;
        }

        ASSERT_COVERED(MyCoverageCase);
        return 0;
    }

  The main function of your test code should then call hmt_run_all_tests (and
  optionally hmt_check_all_coverage) and return the result:

    int main() {
        return hmt_run_all_tests() || hmt_check_all_coverage();
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

#define HMT_ARRAY_SIZE 1024

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
    hmt_test* tests;
} hmt_category;

typedef struct hmt_covercase_struct {
    const char* name;
    int expected_asserts;
    int actual_asserts;
    int* asserted_lines;
} hmt_covercase;

hmt_category _hmt_new_category(const char* name);
hmt_test _hmt_new_test(const char* name, hmt_test_func func);
hmt_covercase _hmt_new_covercase(const char* name, int expected);
void _hmt_register_test(const char* category, const char* name, hmt_test_func func);
void _hmt_register_covercase(const char* name, const char* expected_asserts);
void _hmt_count_cover(const char* name, int line);

#define _HMT_TEST_FUNCNAME(category, name) _hmt_test_ ## category ## _ ## name
#define _HMT_TEST_FUNCNAME_INIT(category, name) _hmt_test_ ## category ## _ ## name ## _init
#define _HMT_COVERCASE_FUNCNAME_INIT(name) _hmt_covercase_ ## name ## _init

#define HMT_TEST(category, name) \
void _HMT_TEST_FUNCNAME(category, name)(hmt_testresult* _result); \
INITIALIZER(_HMT_TEST_FUNCNAME_INIT(category, name)) { \
    _hmt_register_test(#category, #name, _HMT_TEST_FUNCNAME(category, name)); \
} \
void _HMT_TEST_FUNCNAME(category, name)(hmt_testresult* _result)

#define _HMT_CASE_START() \
    _result->count_cases++;

#define _HMT_CASE_FAIL() \
    _result->count_failures++; \
    printf("\n      - " HMT_RED "[FAIL] (line %d) " HMT_RESET, __LINE__);

#define HMT_COVERAGE(name, num_asserts) \
INITIALIZER(_HMT_COVERCASE_FUNCNAME_INIT(name)) { \
    _hmt_register_covercase(#name, #num_asserts); \
} \

#define HMT_ASSERT_COVERED(name) \
{ \
    _hmt_count_cover(#name, __LINE__); \
} \

/*
 * Asserts and expects
 */
#define HMT_EXPECT_TRUE(_actual) { \
    _HMT_CASE_START(); \
    if (!(_actual)) { \
        _HMT_CASE_FAIL(); \
        printf("Expected true but got something false"); \
    } \
} \

#define HMT_EXPECT_FALSE(_actual) { \
    _HMT_CASE_START(); \
    if (_actual) { \
        _HMT_CASE_FAIL(); \
        printf("Expected false but got something true"); \
    } \
} \

#define HMT_EXPECT_FLOAT_EQ_MSG(_actual, _expected, _msg) { \
    _HMT_CASE_START(); \
    float actual = (_actual); \
    float diff = actual - (_expected); \
    if (diff < -FLT_EPSILON || FLT_EPSILON < diff) { \
        _HMT_CASE_FAIL(); \
        if ((_msg)[0] == 0) { \
            printf("Expected %f, got %f (error: %.9g)", (_expected), actual, diff); \
        } else { \
            printf("%s: Expected %f, got %f (error: %.9g)", (_msg), (_expected), actual, diff); \
        } \
    } \
}
#define HMT_EXPECT_FLOAT_EQ(_actual, _expected) HMT_EXPECT_FLOAT_EQ_MSG(_actual, _expected, "");

#define HMT_EXPECT_NEAR_MSG(_actual, _expected, _epsilon, _msg) { \
    _HMT_CASE_START(); \
    float actual = (_actual); \
    float diff = actual - (_expected); \
    if (diff < -(_epsilon) || (_epsilon) < diff) { \
        _HMT_CASE_FAIL(); \
        if ((_msg)[0] == 0) { \
            printf("Expected %f, got %f", (_expected), actual); \
        } else { \
            printf("%s: Expected %f, got %f", (_msg), (_expected), actual); \
        } \
    } \
}
#define HMT_EXPECT_NEAR(_actual, _expected, _epsilon) HMT_EXPECT_NEAR_MSG(_actual, _expected, _epsilon, "");

#define HMT_EXPECT_LT(_actual, _expected) { \
    _HMT_CASE_START(); \
    if ((_actual) >= (_expected)) { \
        _HMT_CASE_FAIL(); \
        printf("Expected %f to be less than %f", (_actual), (_expected)); \
    } \
} \

#define HMT_EXPECT_GT(_actual, _expected) { \
    _HMT_CASE_START(); \
    if ((_actual) <= (_expected)) { \
        _HMT_CASE_FAIL(); \
        printf("Expected %f to be greater than %f", (_actual), (_expected)); \
    } \
} \

#ifndef HMT_SAFE_MACROS
// Friendly defines
#define TEST(category, name) HMT_TEST(category, name)
#define COVERAGE(name, expected_asserts) HMT_COVERAGE(name, expected_asserts)
#define ASSERT_COVERED(name) HMT_ASSERT_COVERED(name)
#define EXPECT_TRUE(_actual) HMT_EXPECT_TRUE(_actual)
#define EXPECT_FALSE(_actual) HMT_EXPECT_FALSE(_actual)
#define EXPECT_FLOAT_EQ(_actual, _expected) HMT_EXPECT_FLOAT_EQ(_actual, _expected)
#define EXPECT_V4_EQ(_actual, _expected) \
    HMT_EXPECT_FLOAT_EQ_MSG(_actual.X, _expected.X, "incorrect X"); \
    HMT_EXPECT_FLOAT_EQ_MSG(_actual.Y, _expected.Y, "incorrect Y"); \
    HMT_EXPECT_FLOAT_EQ_MSG(_actual.Z, _expected.Z, "incorrect Z"); \
    HMT_EXPECT_FLOAT_EQ_MSG(_actual.W, _expected.W, "incorrect W");
#define EXPECT_M4_EQ(_actual, _expected) \
    HMT_EXPECT_FLOAT_EQ_MSG(_actual.Elements[0][0], _expected.Elements[0][0], "incorrect [0][0]"); \
    HMT_EXPECT_FLOAT_EQ_MSG(_actual.Elements[0][1], _expected.Elements[0][1], "incorrect [0][1]"); \
    HMT_EXPECT_FLOAT_EQ_MSG(_actual.Elements[0][2], _expected.Elements[0][2], "incorrect [0][2]"); \
    HMT_EXPECT_FLOAT_EQ_MSG(_actual.Elements[0][3], _expected.Elements[0][3], "incorrect [0][3]"); \
    HMT_EXPECT_FLOAT_EQ_MSG(_actual.Elements[1][0], _expected.Elements[1][0], "incorrect [1][0]"); \
    HMT_EXPECT_FLOAT_EQ_MSG(_actual.Elements[1][1], _expected.Elements[1][1], "incorrect [1][1]"); \
    HMT_EXPECT_FLOAT_EQ_MSG(_actual.Elements[1][2], _expected.Elements[1][2], "incorrect [1][2]"); \
    HMT_EXPECT_FLOAT_EQ_MSG(_actual.Elements[1][3], _expected.Elements[1][3], "incorrect [1][3]"); \
    HMT_EXPECT_FLOAT_EQ_MSG(_actual.Elements[2][0], _expected.Elements[2][0], "incorrect [2][0]"); \
    HMT_EXPECT_FLOAT_EQ_MSG(_actual.Elements[2][1], _expected.Elements[2][1], "incorrect [2][1]"); \
    HMT_EXPECT_FLOAT_EQ_MSG(_actual.Elements[2][2], _expected.Elements[2][2], "incorrect [2][2]"); \
    HMT_EXPECT_FLOAT_EQ_MSG(_actual.Elements[2][3], _expected.Elements[2][3], "incorrect [2][3]"); \
    HMT_EXPECT_FLOAT_EQ_MSG(_actual.Elements[3][0], _expected.Elements[3][0], "incorrect [3][0]"); \
    HMT_EXPECT_FLOAT_EQ_MSG(_actual.Elements[3][1], _expected.Elements[3][1], "incorrect [3][1]"); \
    HMT_EXPECT_FLOAT_EQ_MSG(_actual.Elements[3][2], _expected.Elements[3][2], "incorrect [3][2]"); \
    HMT_EXPECT_FLOAT_EQ_MSG(_actual.Elements[3][3], _expected.Elements[3][3], "incorrect [3][3]");
#define EXPECT_NEAR(_actual, _expected, _epsilon) HMT_EXPECT_NEAR(_actual, _expected, _epsilon)
#define EXPECT_M4_NEAR(_actual, _expected, _epsilon) \
    HMT_EXPECT_NEAR_MSG(_actual.Elements[0][0], _expected.Elements[0][0], _epsilon, "incorrect [0][0]"); \
    HMT_EXPECT_NEAR_MSG(_actual.Elements[0][1], _expected.Elements[0][1], _epsilon, "incorrect [0][1]"); \
    HMT_EXPECT_NEAR_MSG(_actual.Elements[0][2], _expected.Elements[0][2], _epsilon, "incorrect [0][2]"); \
    HMT_EXPECT_NEAR_MSG(_actual.Elements[0][3], _expected.Elements[0][3], _epsilon, "incorrect [0][3]"); \
    HMT_EXPECT_NEAR_MSG(_actual.Elements[1][0], _expected.Elements[1][0], _epsilon, "incorrect [1][0]"); \
    HMT_EXPECT_NEAR_MSG(_actual.Elements[1][1], _expected.Elements[1][1], _epsilon, "incorrect [1][1]"); \
    HMT_EXPECT_NEAR_MSG(_actual.Elements[1][2], _expected.Elements[1][2], _epsilon, "incorrect [1][2]"); \
    HMT_EXPECT_NEAR_MSG(_actual.Elements[1][3], _expected.Elements[1][3], _epsilon, "incorrect [1][3]"); \
    HMT_EXPECT_NEAR_MSG(_actual.Elements[2][0], _expected.Elements[2][0], _epsilon, "incorrect [2][0]"); \
    HMT_EXPECT_NEAR_MSG(_actual.Elements[2][1], _expected.Elements[2][1], _epsilon, "incorrect [2][1]"); \
    HMT_EXPECT_NEAR_MSG(_actual.Elements[2][2], _expected.Elements[2][2], _epsilon, "incorrect [2][2]"); \
    HMT_EXPECT_NEAR_MSG(_actual.Elements[2][3], _expected.Elements[2][3], _epsilon, "incorrect [2][3]"); \
    HMT_EXPECT_NEAR_MSG(_actual.Elements[3][0], _expected.Elements[3][0], _epsilon, "incorrect [3][0]"); \
    HMT_EXPECT_NEAR_MSG(_actual.Elements[3][1], _expected.Elements[3][1], _epsilon, "incorrect [3][1]"); \
    HMT_EXPECT_NEAR_MSG(_actual.Elements[3][2], _expected.Elements[3][2], _epsilon, "incorrect [3][2]"); \
    HMT_EXPECT_NEAR_MSG(_actual.Elements[3][3], _expected.Elements[3][3], _epsilon, "incorrect [3][3]");
#define EXPECT_LT(_actual, _expected) HMT_EXPECT_LT(_actual, _expected)
#define EXPECT_GT(_actual, _expected) HMT_EXPECT_GT(_actual, _expected)
#endif // HMT_SAFE_MACROS

#endif // HANDMADETEST_H

#ifdef HANDMADE_TEST_IMPLEMENTATION

#ifndef HANDMADE_TEST_IMPLEMENTATION_GUARD
#define HANDMADE_TEST_IMPLEMENTATION_GUARD

int _hmt_num_categories = 0;
hmt_category* _hmt_categories = 0;

int _hmt_num_covercases = 0;
hmt_covercase* _hmt_covercases = 0;

int _hmt_num_covererrors = 0;

hmt_category _hmt_new_category(const char* name) {
    hmt_category cat = {
        name, // name
        0, // num_tests
        (hmt_test*) malloc(HMT_ARRAY_SIZE * sizeof(hmt_test)), // tests
    };

    return cat;
}

hmt_test _hmt_new_test(const char* name, hmt_test_func func) {
    hmt_test test = {
        name, // name
        func, // func
    };

    return test;
}

hmt_covercase _hmt_new_covercase(const char* name, int expected) {
    hmt_covercase covercase = {
        name, // name
        expected, // expected_asserts
        0, // actual_asserts
        (int*) malloc(HMT_ARRAY_SIZE * sizeof(int)), // asserted_lines
    };

    return covercase;
}

void _hmt_register_test(const char* category, const char* name, hmt_test_func func) {
    // initialize categories array if not initialized
    if (!_hmt_categories) {
        _hmt_categories = (hmt_category*) malloc(HMT_ARRAY_SIZE * sizeof(hmt_category));
    }

    // Find the matching category, if possible
    int cat_index;
    for (cat_index = 0; cat_index < _hmt_num_categories; cat_index++) {
        if (strcmp(_hmt_categories[cat_index].name, category) == 0) {
            break;
        }
    }

    // Add a new category if necessary
    if (cat_index >= _hmt_num_categories) {
        _hmt_categories[cat_index] = _hmt_new_category(category);
        _hmt_num_categories++;
    }

    hmt_category* cat = &_hmt_categories[cat_index];

    // Add the test to the category
    cat->tests[cat->num_tests] = _hmt_new_test(name, func);
    cat->num_tests++;
}

void _hmt_register_covercase(const char* name, const char* expected_asserts) {
    // initialize cases array if not initialized
    if (!_hmt_covercases) {
        _hmt_covercases = (hmt_covercase*) malloc(HMT_ARRAY_SIZE * sizeof(hmt_covercase));
    }

    // check for existing case with that name, because the macro can run multiple
    // times in different translation units
    for (int i = 0; i < _hmt_num_covercases; i++) {
        if (strcmp(_hmt_covercases[i].name, name) == 0) {
            return;
        }
    }

    _hmt_covercases[_hmt_num_covercases] = _hmt_new_covercase(name, atoi(expected_asserts));
    _hmt_num_covercases++;
}

hmt_covercase* _hmt_find_covercase(const char* name) {
    for (int i = 0; i < _hmt_num_covercases; i++) {
        if (strcmp(_hmt_covercases[i].name, name) == 0) {
            return &_hmt_covercases[i];
        }
    }

    return 0;
}

void _hmt_count_cover(const char* name, int line) {
    hmt_covercase* covercase = _hmt_find_covercase(name);
    if (covercase == 0) {
        printf(HMT_RED "ERROR (line %d): Could not find coverage case with name \"%s\".\n" HMT_RESET, line, name);
        _hmt_num_covererrors++;
        return;
    }

    // see if this line has already been covered
    for (int i = 0; i < covercase->actual_asserts; i++) {
        if (covercase->asserted_lines[i] == line) {
            return;
        }
    }

    covercase->asserted_lines[covercase->actual_asserts] = line;
    covercase->actual_asserts++;
}

int hmt_run_all_tests() {
    int count_alltests = 0;
    int count_allfailedtests = 0; // failed test cases
    int count_allfailures = 0; // failed asserts

    for (int i = 0; i < _hmt_num_categories; i++) {
        hmt_category cat = _hmt_categories[i];
        int count_catfailedtests = 0;
        int count_catfailures = 0;

        printf("\n%s:\n", cat.name);

        for (int j = 0; j < cat.num_tests; j++) {
            hmt_test test = cat.tests[j];

            printf("    %s:", test.name);

            hmt_testresult result = {
                0, // count_cases
                0, // count_failures
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

int hmt_check_all_coverage() {
    printf("Coverage:\n");

    int count_failures = 0;

    for (int i = 0; i < _hmt_num_covercases; i++) {
        hmt_covercase covercase = _hmt_covercases[i];

        if (covercase.expected_asserts != covercase.actual_asserts) {
            count_failures++;
            printf("%s: " HMT_RED "FAIL (expected %d asserts, got %d)\n" HMT_RESET, covercase.name, covercase.expected_asserts, covercase.actual_asserts);
        }
    }

    if (count_failures > 0) {
        printf("\n");
        printf(HMT_RED);
    } else {
        printf(HMT_GREEN);
    }
    printf("%d coverage cases tested, %d failures\n", _hmt_num_covercases, count_failures);
    printf(HMT_RESET);

    printf("\n");

    if (_hmt_num_covererrors > 0) {
        printf(HMT_RED "There were %d other coverage errors; scroll up to see them.\n", _hmt_num_covererrors);
        return 1;
    }

    return (count_failures > 0);
}

#endif // HANDMADE_TEST_IMPLEMENTATION_GUARD
#endif // HANDMADE_TEST_IMPLEMENTATION
