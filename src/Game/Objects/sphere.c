/**
 * \file
 * \brief Sphere implementation
 */
#include "sphere.h"

#include "Base/coordinates.h"
#include "Engine/object.h"

#include <assert.h>
#include <math.h>
#include <stdlib.h>

#define RESOLUTION (0.01) /* Radians */

struct OBJ_Object * SPHERE_create(
    const double radius)
{
    const double step_size = (2.0 * M_PI) / RESOLUTION;
    const int steps = (int)step_size;
    struct OBJ_Object *const sphere = calloc(1, sizeof(*sphere));

    assert(fabs((steps * RESOLUTION) - (2.0 * M_PI)) < (2 * RESOLUTION));

    sphere->length = steps * steps;
    sphere->coordinates = calloc((size_t)sphere->length, sizeof(*sphere->coordinates));

    int index = 0;

    for (int i = 0; i < steps; ++i)
    {
        const double fi = i * RESOLUTION;

        for (int j = 0; j < steps; ++j)
        {
            const double theta = j * RESOLUTION;
            const struct COORD_Coordinate3D coordinate = {
                .x = radius * sin(fi) * cos(theta),
                .y = radius * sin(fi) * sin(theta),
                .z = radius * cos(fi)
            };

            assert(index < sphere->length);

            sphere->coordinates[index] = coordinate;

            ++index;
        }
    }

    assert(index == sphere->length);

    return sphere;
}

void SPHERE_free(
    struct OBJ_Object *const sphere)
{
    free(sphere->coordinates);
    free(sphere);
}
