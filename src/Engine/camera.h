/**
 * \file
 * \brief Camera interface
 */
#ifndef ENGINE_CAMERA_H
#define ENGINE_CAMERA_H

#include "Base/coordinates.h"

/**
 * \brief Intrinsic camera parameters
 */
struct CAM_IntrinsicParameters
{
    double focal_length_x; /**< The focal length in the x direction of the camera [pixels] */
    double focal_length_y; /**< The focal length in the y direction of the camera [pixels] */
    struct COORD_Coordinate2D optical_center; /**< The optical center (also know as the principal point) [pixels] */
};

/**
 * \brief Camera parameters, also known as calibration parameters
 */
struct CAM_CameraParameters
{
    struct CAM_IntrinsicParameters intrinsic; /**< Intrinsic parameters */
};

/**
 * \brief Gets the camera parameters, also known as calibration parameters
 *
 * \param[in] pixel_size_x The pixel size in the x direction [um]
 * \param[in] pixel_size_y The pixel size in the y direction [um]
 * \param[in] focal_length The focal length [mm]
 * \param[in] optical_center The optical center of the camera [pixels]
 * \param[out] calibration The calibration
 */
void CAM_get_camera_calibration(
    double pixel_size_x,
    double pixel_size_y,
    double focal_length,
    const struct COORD_Coordinate2D *optical_center,
    struct CAM_CameraParameters *calibration);

/**
 * \brief Gets the camera calibration matrix
 *
 * Can be used to convert world coordinates to image coordinates. The caller is responsible for the
 * memory management of the matrix, use MAT_free() when it is not needed anymore.
 *
 * \param[in] calibration The camera calibration
 *
 * \return Camera calibration matrix
 */
struct MAT_Matrix * CAM_get_camera_matrix(
    const struct CAM_CameraParameters *calibration);

#endif /* ENGINE_CAMERA_H */
