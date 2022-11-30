/**
 * \file
 * \brief Camera implementation
 */
#include <Base/coordinates.h>
#include <Engine/camera.h>
#include <Engine/coordinate_system_transformations.h>
#include <LinearAlgebra/matrix.h>

static struct MAT_Matrix * get_intrinsic_camera_matrix(
    const struct CAM_IntrinsicParameters *const calibration)
{
    struct MAT_Matrix *const matrix = MAT_alloc(3, 4);

    const double fx = calibration->focal_length_x;
    const double fy = calibration->focal_length_y;
    const double cx = calibration->optical_center.x;
    const double cy = calibration->optical_center.y;

    MAT_set_element(matrix, 0, 0, fx);
    MAT_set_element(matrix, 0, 1, 0.0);
    MAT_set_element(matrix, 0, 2, cx);
    MAT_set_element(matrix, 0, 3, 0.0);

    MAT_set_element(matrix, 1, 0, 0.0);
    MAT_set_element(matrix, 1, 1, -fy);
    MAT_set_element(matrix, 1, 2, cy);
    MAT_set_element(matrix, 1, 3, 0.0);

    MAT_set_element(matrix, 2, 0, 0.0);
    MAT_set_element(matrix, 2, 1, 0.0);
    MAT_set_element(matrix, 2, 2, 1.0);
    MAT_set_element(matrix, 2, 3, 0.0);

    return matrix;
}

static struct MAT_Matrix * get_extrinsic_camera_matrix(
    const struct CAM_ExtrinsicParameters *const calibration)
{
    /*
     * The extrinsic parameters specifies the camera translation and rotation in world coordinates.
     * The camera position and rotation in the world can then be described with the following
     * 4x4 matrix.
     *     [R | t]
     *     [0 | 1]
     * However, the extrinsic camera matrix shall describe how to world is transformed relative to
     * the camera. This matrix is the inverse of the previous matrix.
     *     [R_transpose | R_transpose * -t]
     *     [     0      |        1        ]
     */
    struct MAT_Matrix *const rotation_matrix = CST_get_extrinsic_rotation_matrix(&calibration->rotation);

    MAT_transpose_square(rotation_matrix); /* The inverse is equal to the transpose of a rotation matrix. */

    struct COORD_Coordinate3D translation;
    CST_linear_transformation(&calibration->translation, rotation_matrix, &translation);

    struct MAT_Matrix *const matrix = MAT_alloc(4, 4);

    MAT_set_element(matrix, 0, 0, MAT_get_element(rotation_matrix, 0, 0));
    MAT_set_element(matrix, 0, 1, MAT_get_element(rotation_matrix, 0, 1));
    MAT_set_element(matrix, 0, 2, MAT_get_element(rotation_matrix, 0, 2));
    MAT_set_element(matrix, 1, 0, MAT_get_element(rotation_matrix, 1, 0));
    MAT_set_element(matrix, 1, 1, MAT_get_element(rotation_matrix, 1, 1));
    MAT_set_element(matrix, 1, 2, MAT_get_element(rotation_matrix, 1, 2));
    MAT_set_element(matrix, 2, 0, MAT_get_element(rotation_matrix, 2, 0));
    MAT_set_element(matrix, 2, 1, MAT_get_element(rotation_matrix, 2, 1));
    MAT_set_element(matrix, 2, 2, MAT_get_element(rotation_matrix, 2, 2));

    MAT_set_element(matrix, 0, 3, -translation.x);
    MAT_set_element(matrix, 1, 3, -translation.y);
    MAT_set_element(matrix, 2, 3, -translation.z);

    MAT_set_element(matrix, 3, 0, 0.0);
    MAT_set_element(matrix, 3, 1, 0.0);
    MAT_set_element(matrix, 3, 2, 0.0);
    MAT_set_element(matrix, 3, 3, 1.0);

    MAT_free(rotation_matrix);

    return matrix;
}

void CAM_get_camera_calibration(
    const double pixel_size_x,
    const double pixel_size_y,
    const double focal_length,
    const struct COORD_Coordinate2D *const optical_center,
    const struct COORD_Coordinate3D *const translation,
    const struct CST_Rotation3D *const rotation,
    struct CAM_CameraParameters *const calibration)
{
    const double focal_length_in_um = focal_length * 1000.0;

    calibration->intrinsic.focal_length_x = focal_length_in_um / pixel_size_x;
    calibration->intrinsic.focal_length_y = focal_length_in_um / pixel_size_y;
    calibration->intrinsic.optical_center = *optical_center;

    calibration->extrinsic.translation = *translation;
    calibration->extrinsic.rotation = *rotation;
}

struct MAT_Matrix * CAM_get_camera_matrix(
    const struct CAM_CameraParameters *const calibration)
{
    struct MAT_Matrix *const intrinsic_matrix = get_intrinsic_camera_matrix(&calibration->intrinsic);
    struct MAT_Matrix *const extrinsic_matrix = get_extrinsic_camera_matrix(&calibration->extrinsic);
    struct MAT_Matrix *const camera_matrix = MAT_alloc(3, 4);

    MAT_matrix_matrix_multiplication(intrinsic_matrix, extrinsic_matrix, camera_matrix);

    MAT_free(extrinsic_matrix);
    MAT_free(intrinsic_matrix);

    return camera_matrix;
}
