#include "../coordinate_system_transformations.h"

#include "Base/common.h"
#include "Base/coordinates.h"
#include "Engine/camera.h"
#include "TestFramework/test_framework.h"

int TF_test_case_status;

static const double granularity = 1e-5;

static void test_CST_world_coordinate_to_image_coordinate(void)
{
    const double pixel_size_x = 1.0;
    const double pixel_size_y = 2.0;
    const double focal_length = 30.0;
    const struct COORD_Coordinate2D optical_center = {
        .x = 400,
        .y = 500
    };
    struct CAM_CameraParameters calibration;

    CAM_get_camera_calibration(
        pixel_size_x,
        pixel_size_y,
        focal_length,
        &optical_center,
        &calibration);

    const struct MAT_Matrix *const camera_matrix = CAM_get_camera_matrix(&calibration);

    const struct COORD_Coordinate3D world_coordinate = {
        .x = 6.0,
        .y = 7.0,
        .z = 8.0
    };

    struct COORD_Coordinate2D image_coordinate = {
        .x = 0.0,
        .y = 0.0
    };

    CST_world_coordinate_to_image_coordinate(&world_coordinate, camera_matrix, &image_coordinate);

    const struct COORD_Coordinate2D expected_image_coordinate = {
        .x = (calibration.intrinsic.focal_length_x * (world_coordinate.x / world_coordinate.z)) + optical_center.x,
        .y = (-calibration.intrinsic.focal_length_y * (world_coordinate.y / world_coordinate.z)) + optical_center.y
    };

    TF_assert_double_eq(image_coordinate.x, expected_image_coordinate.x, granularity);
    TF_assert_double_eq(image_coordinate.y, expected_image_coordinate.y, granularity);
}

int main(int argc, char *argv[])
{
    UNUSED(argc);
    UNUSED(argv);

    TF_test_case test_cases[] = {
        test_CST_world_coordinate_to_image_coordinate,
    };

    return TF_run_suite(test_cases, LENGTH(test_cases));
}
