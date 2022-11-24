/**
 * \file
 * \brief Torus interface
 */
#ifndef GAME_OBJECTS_TORUS_H
#define GAME_OBJECTS_TORUS_H

struct OBJ_Object;

/**
 * \brief Creates a torus object (looks like a donut)
 *
 * The caller must free the object using TORUS_free() when it is no longer used.
 *
 * \param[in] inner_radius The radius of the "tube"
 * \param[in] outer_radius The distance from the center of the torus to the center of the "tube"
 *
 * \return Torus
 */
struct OBJ_Object * TORUS_create(
    double inner_radius,
    double outer_radius);

/**
 * \brief Free a torus
 *
 * \param[in,out] torus The torus to free (do not use it anymore)
 */
void TORUS_free(
    struct OBJ_Object *torus);

#endif /* GAME_OBJECTS_TORUS_H */
