/**
 * \file
 * \brief Camera interface
 */
#ifndef ENGINE_CAMERA_H
#define ENGINE_CAMERA_H

#include "coordinate_system_transformations.h"

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
 * \brief Extrinsic camera parameters
 */
struct CAM_ExtrinsicParameters
{
    struct COORD_Coordinate3D translation; /**< The translation of the camera in the world coordinate system [m] */
    struct CST_Rotation3D rotation; /**< The rotation of the camera in the world coordinate system [radians] */
};

/**
 * \brief Camera parameters, also known as calibration parameters
 */
struct CAM_CameraParameters
{
    struct CAM_IntrinsicParameters intrinsic; /**< Intrinsic parameters */
    struct CAM_ExtrinsicParameters extrinsic; /**< Extrinsic parameters */
};

/**
 * \brief Gets the camera parameters, also known as calibration parameters
 *
 * \param[in] pixel_size_x The pixel size in the x direction [um]
 * \param[in] pixel_size_y The pixel size in the y direction [um]
 * \param[in] focal_length The focal length [mm]
 * \param[in] optical_center The optical center of the camera [pixels]
 * \param[in] translation The translation of the camera in the world coordinate system [m]
 * \param[in] rotation The rotation of the camera in the world coordinate system [radians]
 * \param[out] calibration The calibration
 */
void CAM_get_camera_calibration(
    double pixel_size_x,
    double pixel_size_y,
    double focal_length,
    const struct COORD_Coordinate2D *optical_center,
    const struct COORD_Coordinate3D *translation,
    const struct CST_Rotation3D *rotation,
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
