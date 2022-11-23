/**
 * \file
 * \brief Coordinate system transformations implementation
 */
#include "coordinate_system_transformations.h"

#include "Base/coordinates.h"
#include "LinearAlgebra/matrix.h"
#include "LinearAlgebra/vector.h"

#include <assert.h>

void CST_world_coordinate_to_image_coordinate(
    const struct COORD_Coordinate3D *const world_coordinate,
    const struct MAT_Matrix *const camera_matrix,
    struct COORD_Coordinate2D *const image_coordinate)
{
    struct VEC_Vector *const homogeneous_world_coordinate = VEC_alloc(4);
    VEC_set_element(homogeneous_world_coordinate, 0, world_coordinate->x);
    VEC_set_element(homogeneous_world_coordinate, 1, world_coordinate->y);
    VEC_set_element(homogeneous_world_coordinate, 2, world_coordinate->z);
    VEC_set_element(homogeneous_world_coordinate, 3, 1.0);

    struct VEC_Vector *const homogeneous_image_coordinate = VEC_alloc(3);

    MAT_matrix_vector_multiplication(camera_matrix, homogeneous_world_coordinate, homogeneous_image_coordinate);

    const double z = VEC_get_element(homogeneous_image_coordinate, 2);

    assert(z > 0.0);

    image_coordinate->x = VEC_get_element(homogeneous_image_coordinate, 0) / z;
    image_coordinate->y = VEC_get_element(homogeneous_image_coordinate, 1) / z;

    VEC_free(homogeneous_image_coordinate);
    VEC_free(homogeneous_world_coordinate);
}
