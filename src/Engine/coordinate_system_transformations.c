/**
 * \file
 * \brief Coordinate system transformations implementation
 */
#include "coordinate_system_transformations.h"

#include "Base/common.h"
#include "Base/coordinates.h"
#include "LinearAlgebra/matrix.h"
#include "LinearAlgebra/vector.h"

#include <assert.h>
#include <math.h>

void CST_linear_transformation(
    const struct COORD_Coordinate3D *coordinate,
    const struct MAT_Matrix *transformation_matrix,
    struct COORD_Coordinate3D *transformed_coordinate)
{
    double coordinate_vector_data[] = {
        coordinate->x,
        coordinate->y,
        coordinate->z
    };
    struct VEC_Vector coordinate_vector = {
        .length = LENGTH(coordinate_vector_data),
        .data = &coordinate_vector_data[0]
    };

    double transformed_coordinate_vector_data[LENGTH(coordinate_vector_data)] = {0.0};
    struct VEC_Vector transformed_coordinate_vector = {
        .length = LENGTH(transformed_coordinate_vector_data),
        .data = &transformed_coordinate_vector_data[0]
    };

    MAT_matrix_vector_multiplication(transformation_matrix, &coordinate_vector, &transformed_coordinate_vector);

    transformed_coordinate->x = VEC_get_element(&transformed_coordinate_vector, 0);
    transformed_coordinate->y = VEC_get_element(&transformed_coordinate_vector, 1);
    transformed_coordinate->z = VEC_get_element(&transformed_coordinate_vector, 2);
}

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

struct MAT_Matrix * CST_get_extrinsic_rotation_matrix(
    const struct CST_Rotation3D *const rotation)
{
    const double a = rotation->pitch; /* x */
    const double b = rotation->yaw; /* y */
    const double g = rotation->roll; /* z */

    double pitch_data[3][3] = {
        {1.0,    0.0,     0.0},
        {0.0, cos(a), -sin(a)},
        {0.0, sin(a),  cos(a)},
    };

    double yaw_data[3][3] = {
        {cos(b),  0.0, sin(b)},
        {   0.0,  1.0,    0.0},
        {-sin(b), 0.0, cos(b)},
    };

    double roll_data[3][3] = {
        {cos(g), -sin(g), 0.0},
        {sin(g),  cos(g), 0.0},
        {   0.0,     0.0, 1.0},
    };

    const struct MAT_Matrix yaw = {
        .rows = 3,
        .cols = 3,
        .data = &yaw_data[0][0],
    };

    const struct MAT_Matrix pitch = {
        .rows = 3,
        .cols = 3,
        .data = &pitch_data[0][0],
    };

    const struct MAT_Matrix roll = {
        .rows = 3,
        .cols = 3,
        .data = &roll_data[0][0],
    };

    struct MAT_Matrix *const temp = MAT_alloc(3, 3);
    struct MAT_Matrix *const output = MAT_alloc(3, 3);

    MAT_matrix_matrix_multiplication(&roll, &yaw, temp);
    MAT_matrix_matrix_multiplication(temp, &pitch, output);

    MAT_free(temp);

    return output;
}
