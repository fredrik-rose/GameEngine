#include "../vector.h"

#include "Base/common.h"
#include "TestFramework/test_framework.h"

int TF_test_case_status;

static const double granularity = 1e-5;

static void test_VEC_dot_product(void)
{
    const int length = 3;

    struct VEC_Vector *const a = VEC_alloc(length);
    struct VEC_Vector *const b = VEC_alloc(length);

    for (int i = 0; i < length; ++i)
    {
        VEC_set_element(a, i, i);
        VEC_set_element(b, i, i + 1.0);
    }

    const double expected = (0.0 * 1.0) + (1.0 * 2.0) + (2.0 * 3.0);
    const double actual = VEC_dot_product(a, b);

    TF_assert_double_eq(actual, expected, granularity);

    VEC_free(b);
    VEC_free(a);
}

static void test_VEC_normalize(void)
{
    const int length = 3;

    struct VEC_Vector *const vector = VEC_alloc(length);

    for (int i = 0; i < length; ++i)
    {
        VEC_set_element(vector, i, i);
    }

    VEC_normalize(vector);

    const double expected = 1.0;
    const double actual = VEC_norm(vector);

    TF_assert_double_eq(actual, expected, granularity);

    VEC_free(vector);
}

int main(int argc, char *argv[])
{
    UNUSED(argc);
    UNUSED(argv);

    TF_test_case test_cases[] = {
        test_VEC_dot_product,
        test_VEC_normalize,
    };

    return TF_run_suite(test_cases, LENGTH(test_cases));
}
