#include "hmm_test.h"

int main()
{
    int tests_failed = hmt_run_all_tests();
    int coverage_failed = hmt_check_all_coverage();

    return tests_failed || coverage_failed;
}
