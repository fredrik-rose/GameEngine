/**
 * \file
 * \brief Implementation of a minimalistic unit test framework
 */
#include "test_framework.h"

#include <stdio.h>

int TF_run_suite(
    TF_test_case test_cases[],
    const int number_of_test_cases)
{
    int failed = 0;

    for (int i = 0; i < number_of_test_cases; ++i)
    {
        if (test_cases[i]())
        {
            ++failed;
        }
    }

    if (failed)
    {
        printf("Ran %d tests, %d FAILED\n", number_of_test_cases, failed);
        return -1;
    }

    printf("All %d tests PASSED\n", number_of_test_cases);

    return 0;
}
