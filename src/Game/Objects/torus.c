/**
 * \file
 * \brief Torus implementation
 */
#include "torus.h"

#include "Base/coordinates.h"
#include "Engine/coordinate_system_transformations.h"
#include "Engine/object.h"
#include "LinearAlgebra/matrix.h"
#include "LinearAlgebra/vector.h"

#include <assert.h>
#include <math.h>
#include <stdlib.h>

#define RESOLUTION (0.02) /* Radians */

struct OBJ_Object * TORUS_create(
    const double inner_radius,
    const double outer_radius)
{
    assert(outer_radius > inner_radius); // LCOV_EXCL_LINE

    const double step_size = (2.0 * M_PI) / RESOLUTION;
    const int steps = (int)step_size;
    struct OBJ_Object *const torus = calloc(1, sizeof(*torus));
    struct VEC_Vector *const coordinate_vector = VEC_alloc(3);
    struct VEC_Vector *const surface_normal_vector = VEC_alloc(3);

    assert(fabs((steps * RESOLUTION) - (2.0 * M_PI)) < (2 * RESOLUTION)); // LCOV_EXCL_LINE

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

            const struct COORD_Coordinate3D coordinate = {
                .x = outer_radius + (inner_radius * cos(beta)),
                .y = inner_radius * sin(beta),
                .z = 0.0
            };

            const struct COORD_Coordinate3D surface_normal = {
                .x = cos(beta),
                .y = sin(beta),
                .z = 0.0
            };

            assert(index < torus->length); // LCOV_EXCL_LINE

            CST_linear_transformation(&coordinate, rotation_matrix, &torus->coordinates[index]);
            CST_linear_transformation(&surface_normal, rotation_matrix, &torus->surface_normals[index]);

            ++index;
        }

        MAT_free(rotation_matrix);
    }

    assert(index == torus->length); // LCOV_EXCL_LINE

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
