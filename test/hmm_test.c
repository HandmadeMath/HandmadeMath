#include "hmm_test.h"

int main()
{
    return hmt_run_all_tests() || hmt_check_all_coverage();
}
