/**
 * \file
 * \brief Coordinate system transformations interface
 */
#ifndef ENGINE_COORDINATESYSTEMTRANSFORMATIONS_H
#define ENGINE_COORDINATESYSTEMTRANSFORMATIONS_H

struct COORD_Coordinate2D;
struct COORD_Coordinate3D;
struct MAT_Matrix;

/**
 * \brief 3D rotation
 */
struct CST_Rotation3D
{
    double pitch; /* Rotation around the x-axis */
    double yaw; /* Rotation around the y-axis */
    double roll; /* Rotation around the z-axis */
};

/**
 * \brief Performs a linear transformation of a coordinate
 *
 * \param[in] coordinate The coordinate
 * \param[in] transformation_matrix The 3x3 transformation matrix
 * \param[out] transformed_coordinate The linearly transformed coordinate
 */
void CST_linear_transformation(
    const struct COORD_Coordinate3D *coordinate,
    const struct MAT_Matrix *transformation_matrix,
    struct COORD_Coordinate3D *transformed_coordinate);

/**
 * \brief Convert a world coordinate to an image coordinate.
 *
 * \param[in] world_coordinate The world coordinate
 * \param[in] camera_matrix The camera matrix
 * \param[out] image_coordinate The image coordinate
 */
void CST_world_coordinate_to_image_coordinate(
    const struct COORD_Coordinate3D *world_coordinate,
    const struct MAT_Matrix *camera_matrix,
    struct COORD_Coordinate2D *image_coordinate);

/**
 * \brief Creates a rotation matrix for a given rotation
 *
 * The caller is responsible for the memory management of the matrix, use MAT_free() when it is
 * not needed anymore.
 *
 * \param[in] rotation The rotation
 *
 * \return Rotation matrix
 */
struct MAT_Matrix * CST_get_extrinsic_rotation_matrix(
    const struct CST_Rotation3D *rotation);

#endif /* ENGINE_COORDINATESYSTEMTRANSFORMATIONS_H */
