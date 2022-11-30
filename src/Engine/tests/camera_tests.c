#include <Base/common.h>
#include <Base/coordinates.h>
#include <Engine/camera.h>
#include <Engine/coordinate_system_transformations.h>
#include <LinearAlgebra/matrix.h>
#include <TestFramework/test_framework.h>

int TF_test_case_status;

static const double granularity = 1e-5;

static void test_extrinsic_camera_matrix(void)
{
    /*
     * The camera matrix transforms a world coordinate to a camera coordinate. When creating the
     * camera matrix the input is the camera position and rotation in world coordinates. The
     * transformation matrix with the camera position and rotation in world coordinates multiplied
     * with the camera matrix should thus yield the identity matrix.
     */

    /* Make sure the intrinsic matrix is an identity matrix. */
    const double pixel_size_x = 1.0;
    const double pixel_size_y = -1.0; /* Use minus as a hack to make the intrinsic camera matrix an identity matrix. */
    const double focal_length = 1.0 / 1000.0;
    const struct COORD_Coordinate2D optical_center = {
        .x = 0,
        .y = 0
    };
    struct COORD_Coordinate3D camera_translation = {
        .x = 1.0,
        .y = 2.0,
        .z = 3.0
    };
    struct CST_Rotation3D camera_rotation = {
        .pitch = 4.0,
        .yaw = 5.0,
        .roll = 6.0
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
    struct MAT_Matrix *const extended_camera_matrix = MAT_alloc(4, 4);

    /* Copy rotation part from the camera matrix. */
    MAT_set_element(extended_camera_matrix, 0, 0, MAT_get_element(camera_matrix, 0, 0));
    MAT_set_element(extended_camera_matrix, 0, 1, MAT_get_element(camera_matrix, 0, 1));
    MAT_set_element(extended_camera_matrix, 0, 2, MAT_get_element(camera_matrix, 0, 2));
    MAT_set_element(extended_camera_matrix, 1, 0, MAT_get_element(camera_matrix, 1, 0));
    MAT_set_element(extended_camera_matrix, 1, 1, MAT_get_element(camera_matrix, 1, 1));
    MAT_set_element(extended_camera_matrix, 1, 2, MAT_get_element(camera_matrix, 1, 2));
    MAT_set_element(extended_camera_matrix, 2, 0, MAT_get_element(camera_matrix, 2, 0));
    MAT_set_element(extended_camera_matrix, 2, 1, MAT_get_element(camera_matrix, 2, 1));
    MAT_set_element(extended_camera_matrix, 2, 2, MAT_get_element(camera_matrix, 2, 2));

    /* Copy translation part from the camera matrix. */
    MAT_set_element(extended_camera_matrix, 0, 3, MAT_get_element(camera_matrix, 0, 3));
    MAT_set_element(extended_camera_matrix, 1, 3, MAT_get_element(camera_matrix, 1, 3));
    MAT_set_element(extended_camera_matrix, 2, 3, MAT_get_element(camera_matrix, 2, 3));

    /* Extension row. */
    MAT_set_element(extended_camera_matrix, 3, 0, 0.0);
    MAT_set_element(extended_camera_matrix, 3, 1, 0.0);
    MAT_set_element(extended_camera_matrix, 3, 2, 0.0);
    MAT_set_element(extended_camera_matrix, 3, 3, 1.0);

    struct MAT_Matrix *const rotation_matrix = CST_get_extrinsic_rotation_matrix(&camera_rotation);
    struct MAT_Matrix *const matrix = MAT_alloc(4, 4);

    /* Copy rotation part from the rotation matrix. */
    MAT_set_element(matrix, 0, 0, MAT_get_element(rotation_matrix, 0, 0));
    MAT_set_element(matrix, 0, 1, MAT_get_element(rotation_matrix, 0, 1));
    MAT_set_element(matrix, 0, 2, MAT_get_element(rotation_matrix, 0, 2));
    MAT_set_element(matrix, 1, 0, MAT_get_element(rotation_matrix, 1, 0));
    MAT_set_element(matrix, 1, 1, MAT_get_element(rotation_matrix, 1, 1));
    MAT_set_element(matrix, 1, 2, MAT_get_element(rotation_matrix, 1, 2));
    MAT_set_element(matrix, 2, 0, MAT_get_element(rotation_matrix, 2, 0));
    MAT_set_element(matrix, 2, 1, MAT_get_element(rotation_matrix, 2, 1));
    MAT_set_element(matrix, 2, 2, MAT_get_element(rotation_matrix, 2, 2));

    /* Copy translation part from the camera translation. */
    MAT_set_element(matrix, 0, 3, camera_translation.x);
    MAT_set_element(matrix, 1, 3, camera_translation.y);
    MAT_set_element(matrix, 2, 3, camera_translation.z);

    /* Extension row. */
    MAT_set_element(matrix, 3, 0, 0.0);
    MAT_set_element(matrix, 3, 1, 0.0);
    MAT_set_element(matrix, 3, 2, 0.0);
    MAT_set_element(matrix, 3, 3, 1.0);

    struct MAT_Matrix *const expected_identity_matrix = MAT_alloc(4, 4);

    MAT_matrix_matrix_multiplication(matrix, extended_camera_matrix, expected_identity_matrix);

    TF_assert_double_eq(MAT_get_element(expected_identity_matrix, 0, 0), 1.0, granularity);
    TF_assert_double_eq(MAT_get_element(expected_identity_matrix, 0, 1), 0.0, granularity);
    TF_assert_double_eq(MAT_get_element(expected_identity_matrix, 0, 2), 0.0, granularity);
    TF_assert_double_eq(MAT_get_element(expected_identity_matrix, 0, 3), 0.0, granularity);

    TF_assert_double_eq(MAT_get_element(expected_identity_matrix, 1, 0), 0.0, granularity);
    TF_assert_double_eq(MAT_get_element(expected_identity_matrix, 1, 1), 1.0, granularity);
    TF_assert_double_eq(MAT_get_element(expected_identity_matrix, 1, 2), 0.0, granularity);
    TF_assert_double_eq(MAT_get_element(expected_identity_matrix, 1, 3), 0.0, granularity);

    TF_assert_double_eq(MAT_get_element(expected_identity_matrix, 2, 0), 0.0, granularity);
    TF_assert_double_eq(MAT_get_element(expected_identity_matrix, 2, 1), 0.0, granularity);
    TF_assert_double_eq(MAT_get_element(expected_identity_matrix, 2, 2), 1.0, granularity);
    TF_assert_double_eq(MAT_get_element(expected_identity_matrix, 2, 3), 0.0, granularity);

    TF_assert_double_eq(MAT_get_element(expected_identity_matrix, 3, 0), 0.0, granularity);
    TF_assert_double_eq(MAT_get_element(expected_identity_matrix, 3, 1), 0.0, granularity);
    TF_assert_double_eq(MAT_get_element(expected_identity_matrix, 3, 2), 0.0, granularity);
    TF_assert_double_eq(MAT_get_element(expected_identity_matrix, 3, 3), 1.0, granularity);

    MAT_free(expected_identity_matrix);
    MAT_free(matrix);
    MAT_free(rotation_matrix);
    MAT_free(extended_camera_matrix);
    MAT_free(camera_matrix);
}

int main(int argc, char *argv[])
{
    UNUSED(argc);
    UNUSED(argv);

    TF_test_case test_cases[] = {
        test_extrinsic_camera_matrix,
    };

    return TF_run_suite(test_cases, LENGTH(test_cases));
}
