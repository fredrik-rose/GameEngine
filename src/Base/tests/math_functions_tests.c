#include "../math_functions.h"

#include "Base/common.h"
#include "TestFramework/test_framework.h"

int TF_test_case_status;

static const double granularity = 0.0;

static void test_MATH_clamp(void)
{
    const double lower = MATH_clamp(0.0, 1.0, 10.0);
    TF_assert_double_eq(lower, 1.0, granularity);

    const double upper = MATH_clamp(11.0, 1.0, 10.0);
    TF_assert_double_eq(upper, 10.0, granularity);

    const double middle = MATH_clamp(5.0, 1.0, 10.0);
    TF_assert_double_eq(middle, 5.0, granularity);
}

int main(int argc, char *argv[])
{
    UNUSED(argc);
    UNUSED(argv);

    TF_test_case test_cases[] = {
        test_MATH_clamp,
    };

    return TF_run_suite(test_cases, LENGTH(test_cases));
}
