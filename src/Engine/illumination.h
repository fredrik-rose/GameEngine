/**
 * \file
 * \brief Illumination interface
 */
#ifndef GAME_ILLUMINATION_H
#define GAME_ILLUMINATION_H

struct COORD_Coordinate3D;

/*!
 * \brief Calculate the illumination of a surface based on the light direction and the surface normal
 *
 * \param[in] light_source The position of the light
 * \param[in] surface_position The position of the surface to illuminate
 * \param[in] surface_normal The normal vector of the surface to illuminate
 *
 * \return The illumination in range [0, 1], 0 represents no illumination and 1 represents full illumination
 */
double ILL_get_illumination(
    const struct COORD_Coordinate3D *light_source,
    const struct COORD_Coordinate3D *surface_position,
    const struct COORD_Coordinate3D *surface_normal);

#endif /* GAME_ILLUMINATION_H */
