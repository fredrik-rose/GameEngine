/**
 * \file
 * \brief Torus implementation
 */
#include "torus.h"

#include "Base/common.h"
#include "Base/coordinates.h"
#include "Engine/coordinate_system_transformations.h"
#include "Engine/object.h"
#include "LinearAlgebra/matrix.h"
#include "LinearAlgebra/vector.h"

#include <assert.h>
#include <math.h>
#include <stdlib.h>

#define RESOLUTION (0.01) /* Radians */

struct OBJ_Object * TORUS_create(
    const double inner_radius,
    const double outer_radius)
{
    assert(outer_radius > inner_radius);

    const double step_size = (2.0 * M_PI) / RESOLUTION;
    const int steps = (int)step_size;
    struct OBJ_Object *const torus = calloc(1, sizeof(*torus));
    struct VEC_Vector *const coordinate_vector = VEC_alloc(3);
    struct VEC_Vector *const surface_normal_vector = VEC_alloc(3);

    assert(fabs((steps * RESOLUTION) - (2.0 * M_PI)) < (2 * RESOLUTION));

    torus->length = steps * steps;
    torus->coordinates = calloc((size_t)torus->length, sizeof(*torus->coordinates));
    torus->surface_normals = calloc((size_t)torus->length, sizeof(*torus->surface_normals));

    int index = 0;

    for (int i = 0; i < steps; ++i)
    {
        const double alpha = i * RESOLUTION;
        const struct CST_Rotation3D rotation = {
            .pitch = 0.0,
            .yaw = alpha,
            .roll = 0.0,
        };
        struct MAT_Matrix *const rotation_matrix = CST_get_extrinsic_rotation_matrix(&rotation);

        for (int j = 0; j < steps; ++j)
        {
            const double beta = j * RESOLUTION;

            double circle_coordinate_vector_data[] = {
                outer_radius + (inner_radius * cos(beta)), /* x */
                inner_radius * sin(beta), /* y */
                0.0 /* z */
            };
            struct VEC_Vector circle_coordinate_vector = {
                .length = LENGTH(circle_coordinate_vector_data),
                .data = &circle_coordinate_vector_data[0]
            };

            double circle_surface_normal_vector_data[] = {
                cos(beta), /* x */
                sin(beta), /* y */
                0.0 /* z */
            };
            struct VEC_Vector circle_surface_normal_vector = {
                .length = LENGTH(circle_surface_normal_vector_data),
                .data = &circle_surface_normal_vector_data[0]
            };

            MAT_matrix_vector_multiplication(rotation_matrix, &circle_coordinate_vector, coordinate_vector);
            MAT_matrix_vector_multiplication(rotation_matrix, &circle_surface_normal_vector, surface_normal_vector);

            assert(index < torus->length);

            struct COORD_Coordinate3D *const current_coordinate = &torus->coordinates[index];
            current_coordinate->x = VEC_get_element(coordinate_vector, 0);
            current_coordinate->y = VEC_get_element(coordinate_vector, 1);
            current_coordinate->z = VEC_get_element(coordinate_vector, 2);

            struct COORD_Coordinate3D *const current_surface_normal = &torus->surface_normals[index];
            current_surface_normal->x = VEC_get_element(surface_normal_vector, 0);
            current_surface_normal->y = VEC_get_element(surface_normal_vector, 1);
            current_surface_normal->z = VEC_get_element(surface_normal_vector, 2);

            ++index;
        }

        MAT_free(rotation_matrix);
    }

    assert(index == torus->length);

    VEC_free(surface_normal_vector);
    VEC_free(coordinate_vector);

    return torus;
}

void TORUS_free(
    struct OBJ_Object *const torus)
{
    free(torus->surface_normals);
    free(torus->coordinates);
    free(torus);
}
