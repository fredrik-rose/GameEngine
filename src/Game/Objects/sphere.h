/**
 * \file
 * \brief Sphere interface
 */
#ifndef GAME_OBJECTS_SPHERE_H
#define GAME_OBJECTS_SPHERE_H

struct OBJ_Object;

/**
 * \brief Creates a sphere object
 *
 * The caller must free the object using SPHERE_free() when it is no longer used
 *
 * \param[in] radius The radius of the sphere
 *
 * \return Sphere
 */
struct OBJ_Object * SPHERE_create(
    double radius);

/**
 * \brief Free a sphere
 *
 * \param[in,out] sphere The sphere to free (do not use it anymore)
 */
void SPHERE_free(
    struct OBJ_Object *sphere);

#endif /* GAME_OBJECTS_SPHERE_H */
