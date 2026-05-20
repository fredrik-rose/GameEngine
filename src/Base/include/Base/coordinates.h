/**
 * \file
 * \brief Coordinates interface
 */
#ifndef BASE_COORDINATES_H
#define BASE_COORDINATES_H

struct COORD_Coordinate2D
{
    double x;
    double y;
};

struct COORD_Coordinate3D
{
    double x;
    double y;
    double z;
};

/**
 * \brief Add two 3D coordinates
 *
 * \param[in] a The first coordinate
 * \param[in] b The second coordinate
 * \param[out] output The sum
 */
void COORD_Coordinate3D_add(
    const struct COORD_Coordinate3D *a,
    const struct COORD_Coordinate3D *b,
    struct COORD_Coordinate3D *output);

/**
 * \brief Subtract two 3D coordinates
 *
 * \param[in] a The first coordinate
 * \param[in] b The second coordinate
 * \param[out] output The difference, a - b
 */
void COORD_Coordinate3D_sub(
    const struct COORD_Coordinate3D *a,
    const struct COORD_Coordinate3D *b,
    struct COORD_Coordinate3D *output);

#endif /* BASE_COORDINATES_H */
