/**
 * \file
 * \brief Interface of a minimalistic unit test framework
 */
#include <math.h>
#include <stdio.h>

/** Assert that a certain expression is true (shall only be used inside a test case function) */
#define TF_assert(expression) \
    do { \
        if (!(expression)) { \
            printf("%s:%d %s FAILED\n%s\n", __FILE__, __LINE__, __func__, #expression); \
            return -1; \
        } \
    } while (0)

/** Assert that two floating point values are equal (shall only be used inside a test case function) */
#define TF_assert_double_eq(a, b, granularity) TF_assert(fabs((a) - (b)) < (granularity))

/** Prototype of a test case */
typedef int (*TF_test_case)(void);

/**
 * \brief Run a test suite (a collection of test cases)
 *
 * \param[int] test_cases The test cases
 * \param[in] number_of_test_cases The number of test cases
 *
 * \return 0 on success a non-zero value otherwise
 */
int TF_run_suite(
    TF_test_case test_cases[],
    int number_of_test_cases);
