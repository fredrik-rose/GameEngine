#include "../illumination.h"

#include "Base/common.h"
#include "Base/coordinates.h"
#include "TestFramework/test_framework.h"

int TF_test_case_status;

static const double granularity = 1e-5;

static void test_ILL_get_illumination_full_light(void)
{
    const struct COORD_Coordinate3D surface_position = {
        .x = 0.0,
        .y = -1.0,
        .z = 1.0
    };
    const struct COORD_Coordinate3D light_source = {
        .x = 0.0,
        .y = -10.0,
        .z = 10.0
    };
    const struct COORD_Coordinate3D surface_normal = {
        .x = 0.0,
        .y = -0.5,
        .z = 0.5
    };

    const double illumination = ILL_get_illumination(&light_source, &surface_position, &surface_normal);

    TF_assert_double_eq(illumination, 1.0, granularity);
}

static void test_ILL_get_illumination_no_light(void)
{
    const struct COORD_Coordinate3D surface_position = {
        .x = 2.0,
        .y = -1.0,
        .z = 1.0
    };
    const struct COORD_Coordinate3D light_source = {
        .x = 20.0,
        .y = -10.0,
        .z = 10.0
    };
    const struct COORD_Coordinate3D surface_normal = {
        .x = -1.0,
        .y = 0.5,
        .z = -0.5
    };

    const double illumination = ILL_get_illumination(&light_source, &surface_position, &surface_normal);

    TF_assert_double_eq(illumination, 0.0, granularity);
}

static void test_ILL_get_illumination_half_light(void)
{
    const struct COORD_Coordinate3D surface_position = {
        .x = 0.5,
        .y = 1.0,
        .z = -1.0
    };
    const struct COORD_Coordinate3D light_source = {
        .x = 5.0,
        .y = 10.0,
        .z = -10.0
    };
    const struct COORD_Coordinate3D surface_normal = {
        .x = 1.0,
        .y = 2.0,
        .z = 2.5
    };

    const double illumination = ILL_get_illumination(&light_source, &surface_position, &surface_normal);

    TF_assert_double_eq(illumination, 0.5, granularity);
}

int main(int argc, char *argv[])
{
    UNUSED(argc);
    UNUSED(argv);

    TF_test_case test_cases[] = {
        test_ILL_get_illumination_full_light,
        test_ILL_get_illumination_no_light,
        test_ILL_get_illumination_half_light,
    };

    return TF_run_suite(test_cases, LENGTH(test_cases));
}
