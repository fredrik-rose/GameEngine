/**
 * \file
 * \brief Coordinates implementation
 */
#include "coordinates.h"

void COORD_Coordinate3D_add(
    const struct COORD_Coordinate3D *const a,
    const struct COORD_Coordinate3D *const b,
    struct COORD_Coordinate3D *const output)
{
    output->x = a->x + b->x;
    output->y = a->y + b->y;
    output->z = a->z + b->z;
}

void COORD_Coordinate3D_sub(
    const struct COORD_Coordinate3D *const a,
    const struct COORD_Coordinate3D *const b,
    struct COORD_Coordinate3D *const output)
{
    output->x = a->x - b->x;
    output->y = a->y - b->y;
    output->z = a->z - b->z;
}
