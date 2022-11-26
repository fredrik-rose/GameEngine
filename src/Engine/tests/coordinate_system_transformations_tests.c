#include "coordinate_system_transformations.h"

#include "Base/common.h"
#include "Base/coordinates.h"
#include "Engine/camera.h"
#include "LinearAlgebra/matrix.h"
#include "TestFramework/test_framework.h"

int TF_test_case_status;

static const double granularity = 1e-5;

static void test_CST_linear_transformation(void)
{
    double transformation_matrix_data[] = {
        1.0, 0.0, 0.0,
        0.0, 2.0, 0.0,
        0.0, 0.0, 3.0,
    };
    struct MAT_Matrix transformation_matrix = {
        .rows = 3,
        .cols = 3,
        .data = &transformation_matrix_data[0]
    };

    const struct COORD_Coordinate3D coordinate = {
        .x = 4.0,
        .y = 5.0,
        .z = 6.0
    };

    const struct COORD_Coordinate3D expected_coordinate = {
        .x = 4.0 * 1.0,
        .y = 5.0 * 2.0,
        .z = 6.0 * 3.0
    };

    struct COORD_Coordinate3D transformed_coordinate = {
        .x = 0.0,
        .y = 0.0,
        .z = 0.0
    };

    CST_linear_transformation(&coordinate, &transformation_matrix, &transformed_coordinate);

    TF_assert_double_eq(transformed_coordinate.x, expected_coordinate.x, granularity);
    TF_assert_double_eq(transformed_coordinate.y, expected_coordinate.y, granularity);
    TF_assert_double_eq(transformed_coordinate.z, expected_coordinate.z, granularity);
}

static void test_CST_world_coordinate_to_image_coordinate(void)
{
    const double pixel_size_x = 1.0;
    const double pixel_size_y = 2.0;
    const double focal_length = 30.0;
    const struct COORD_Coordinate2D optical_center = {
        .x = 400,
        .y = 500
    };
    struct COORD_Coordinate3D camera_translation = {
        .x = 0.0,
        .y = 0.0,
        .z = 0.0
    };
    struct CST_Rotation3D camera_rotation = {
        .pitch = 0.0,
        .yaw = 0.0,
        .roll = 0.0
    };
    struct CAM_CameraParameters calibration;

    CAM_get_camera_calibration(
        pixel_size_x,
        pixel_size_y,
        focal_length,
        &optical_center,
        &camera_translation,
        &camera_rotation,
        &calibration);

    struct MAT_Matrix *const camera_matrix = CAM_get_camera_matrix(&calibration);

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

    MAT_free(camera_matrix);
}

int main(int argc, char *argv[])
{
    UNUSED(argc);
    UNUSED(argv);

    TF_test_case test_cases[] = {
        test_CST_linear_transformation,
        test_CST_world_coordinate_to_image_coordinate,
    };

    return TF_run_suite(test_cases, LENGTH(test_cases));
}
