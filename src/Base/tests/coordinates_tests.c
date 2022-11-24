#include "../coordinates.h"

#include "Base/common.h"
#include "TestFramework/test_framework.h"

int TF_test_case_status;

static const double granularity = 1e-5;

static void test_COORD_Coordinate3D_add(void)
{
    const struct COORD_Coordinate3D a = {
        .x = 1.0,
        .y = 2.0,
        .z = 3.0
    };
    const struct COORD_Coordinate3D b = {
        .x = 4.0,
        .y = 5.0,
        .z = 6.0
    };
    const struct COORD_Coordinate3D expected_output = {
        .x = 1.0 + 4.0,
        .y = 2.0 + 5.0,
        .z = 3.0 + 6.0
    };
    struct COORD_Coordinate3D output = {
        .x = 0.0,
        .y = 0.0,
        .z = 0.0
    };

    COORD_Coordinate3D_add(&a, &b, &output);

    TF_assert_double_eq(output.x, expected_output.x, granularity);
    TF_assert_double_eq(output.y, expected_output.y, granularity);
    TF_assert_double_eq(output.z, expected_output.z, granularity);
}

static void test_COORD_Coordinate3D_sub(void)
{
    const struct COORD_Coordinate3D a = {
        .x = 1.0,
        .y = 2.0,
        .z = 3.0
    };
    const struct COORD_Coordinate3D b = {
        .x = 4.0,
        .y = 5.0,
        .z = 6.0
    };
    const struct COORD_Coordinate3D expected_output = {
        .x = 1.0 - 4.0,
        .y = 2.0 - 5.0,
        .z = 3.0 - 6.0
    };
    struct COORD_Coordinate3D output = {
        .x = 0.0,
        .y = 0.0,
        .z = 0.0
    };

    COORD_Coordinate3D_sub(&a, &b, &output);

    TF_assert_double_eq(output.x, expected_output.x, granularity);
    TF_assert_double_eq(output.y, expected_output.y, granularity);
    TF_assert_double_eq(output.z, expected_output.z, granularity);
}

int main(int argc, char *argv[])
{
    UNUSED(argc);
    UNUSED(argv);

    TF_test_case test_cases[] = {
        test_COORD_Coordinate3D_add,
        test_COORD_Coordinate3D_sub,
    };

    return TF_run_suite(test_cases, LENGTH(test_cases));
}
