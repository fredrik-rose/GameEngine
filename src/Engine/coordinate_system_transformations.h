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

#endif /* ENGINE_COORDINATESYSTEMTRANSFORMATIONS_H */
