/**
 * \file
 * \brief Renderer interface
 */
#ifndef GAME_RENDERER_H
#define GAME_RENDERER_H

#include "Base/coordinates.h"

struct CAM_CameraParameters;

struct REND_Renderer;

/**
 * \brief Object with corresponding position in the world
 */
struct REND_ObjectWithPosition
{
    const struct OBJ_Object *const object; /**< Arbitrary object */
    struct COORD_Coordinate3D position; /**< The position of the object ion the world */
};

/**
 * \brief A collection of objects with corresponding world positions
 */
struct REND_Objects
{
    struct REND_ObjectWithPosition *objects; /**< Objects in the world */
    int length; /**< Number of objects in the collection */
};

/**
 * \brief Create a renderer
 *
 * \param[in] calibration The camera parameters/calibration
 * \param[in] screen_width The screen width
 * \param[in] screen_height The screen height
 *
 * \return Renderer
 */
struct REND_Renderer * REND_create(
    const struct CAM_CameraParameters *calibration,
    int screen_width,
    int screen_height);

/**
 * \brief Destroy a renderer
 *
 * \param[in] renderer The renderer to destroy, do not use it anymore
 */
void REND_destroy(
    struct REND_Renderer *renderer);

/**
 * \brief Render a model
 *
 * \param[in,out] renderer The renderer
 * \param[in] objects The objects with corresponding world positions to render
 */
void REND_render(
    struct REND_Renderer *renderer,
    const struct REND_Objects *objects);

#endif /* GAME_RENDERER_H */
