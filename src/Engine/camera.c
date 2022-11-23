/**
 * \file
 * \brief Camera implementation
 */
#include "camera.h"

#include "Base/coordinates.h"
#include "LinearAlgebra/matrix.h"

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

void CAM_get_camera_calibration(
    const double pixel_size_x,
    const double pixel_size_y,
    const double focal_length,
    const struct COORD_Coordinate2D *const optical_center,
    struct CAM_CameraParameters *const calibration)
{
    const double focal_length_in_um = focal_length * 1000.0;

    calibration->intrinsic.focal_length_x = focal_length_in_um / pixel_size_x;
    calibration->intrinsic.focal_length_y = focal_length_in_um / pixel_size_y;
    calibration->intrinsic.optical_center = *optical_center;
}

struct MAT_Matrix * CAM_get_camera_matrix(
    const struct CAM_CameraParameters *const calibration)
{
    return get_intrinsic_camera_matrix(&calibration->intrinsic);
}
