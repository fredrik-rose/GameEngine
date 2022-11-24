/**
 * \file
 * \brief Illumination implementation
 */
#include "illumination.h"

#include "Base/common.h"
#include "Base/coordinates.h"
#include "Base/math_functions.h"
#include "LinearAlgebra/vector.h"

double ILL_get_illumination(
    const struct COORD_Coordinate3D *const light_source,
    const struct COORD_Coordinate3D *const surface_position,
    const struct COORD_Coordinate3D *const surface_normal)
{
    /* If the surface normal are parallel with the light direction but have opposite direction
     * maximum light will be reflected. Analogously, a surface normal that are parallel with the
     * light direction with the same direction will not reflect (almost) any light at all.
     * Therefore the minus sign. */
    struct COORD_Coordinate3D light_ray;
    COORD_Coordinate3D_sub(surface_position, light_source, &light_ray);

    double light_ray_vector_data[] = {light_ray.x, light_ray.y, light_ray.z};
    struct VEC_Vector light_ray_vector = {
        .length = LENGTH(light_ray_vector_data),
        .data = &light_ray_vector_data[0]
    };

    double surface_normal_vector_data[] = {surface_normal->x, surface_normal->y, surface_normal->z};
    struct VEC_Vector surface_normal_vector = {
        .length = LENGTH(surface_normal_vector_data),
        .data = &surface_normal_vector_data[0]
    };

    VEC_normalize(&light_ray_vector);
    VEC_normalize(&surface_normal_vector);

    const double illumination = -VEC_dot_product(&light_ray_vector, &surface_normal_vector);
    const double normalized_illumination = MATH_clamp((illumination + 1.0) / 2.0, 0.0, 1.0);

    return normalized_illumination;
}
