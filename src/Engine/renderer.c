/**
 * \file
 * \brief Renderer implementation
 */
#include "renderer.h"

#include "camera.h"
#include "coordinate_system_transformations.h"
#include "object.h"

#include "Base/coordinates.h"
#include "LinearAlgebra/Matrix.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * \brief Renderer
 */
struct REND_Renderer
{
    struct MAT_Matrix *frame_buffer; /**< The frame buffer, i.e. pixels in the frame */
    /**
     * The z buffer, keeps track of the closest position for each pixel. This is used to handle
     * occlusion as it keeps track of which objects are in front of other objects.
     */
    struct MAT_Matrix *z_buffer;
    struct MAT_Matrix *camera_matrix; /**< The camera matrix/calibration */
};

/**
 * \brief Reset the frame buffer
 *
 * \param[in,out] frame_buffer The frame buffer
 */
static void reset_frame_buffer(
    struct MAT_Matrix *const frame_buffer)
{
    MAT_set_all_elements(frame_buffer, (double)' ');
}

/**
 * \brief Reset the z buffer
 *
 * \param[in,out] z_buffer The z buffer
 */
static void reset_z_buffer(
    struct MAT_Matrix *const z_buffer)
{
    MAT_set_all_elements(z_buffer, INFINITY);
}

/**
 * \brief Draw the frame to the screen
 *
 * \param[in] frame_buffer The frame buffer
 */
static void draw_frame(
    const struct MAT_Matrix *const frame_buffer)
{
    printf("\x1b[H");

    for (int y = 0; y < frame_buffer->rows; ++y)
    {
        for (int x = 0; x < frame_buffer->cols; ++x)
        {
            putchar((char)MAT_get_element(frame_buffer, y, x));
        }
        putchar('\n');
    }
}

/**
 * \brief Render a single pixel given a world coordinate.
 *
 * \param[in,out] renderer The renderer
 * \param[in] world_coordinate The world coordinate
 * \param[in] color The color of the pixel
 */
static void render_pixel(
    struct REND_Renderer *const renderer,
    const struct COORD_Coordinate3D *const world_coordinate,
    const char color)
{
    assert(renderer->frame_buffer->rows == renderer->z_buffer->rows);
    assert(renderer->frame_buffer->cols == renderer->z_buffer->cols);

    const double distance = world_coordinate->z;

    if (distance > 0.0)
    {
        struct COORD_Coordinate2D image_coordinate;
        CST_world_coordinate_to_image_coordinate(world_coordinate, renderer->camera_matrix, &image_coordinate);

        const int x = (int)round(image_coordinate.x);
        const int y = (int)round(image_coordinate.y);

        if ((y >= 0) && (y < renderer->frame_buffer->rows) && (x >= 0) && (x < renderer->frame_buffer->cols))
        {
            if (distance < MAT_get_element(renderer->z_buffer, y, x))
            {
                MAT_set_element(renderer->frame_buffer, y, x, (double)color);
                MAT_set_element(renderer->z_buffer, y, x, distance);
            }
        }
    }
}

/**
 * \brief Render an entire object
 *
 * \param[in,out] renderer The renderer
 * \param[in] object The object to render
 * \param[in] position The world position of the object
 */
static void render_object(
    struct REND_Renderer *const renderer,
    const struct OBJ_Object *const object,
    const struct COORD_Coordinate3D *const position)
{
    for (int i = 0; i < object->length; ++i)
    {
        const struct COORD_Coordinate3D *const object_position = &object->coordinates[i];
        struct COORD_Coordinate3D world_position;
        COORD_Coordinate3D_add(object_position, position, &world_position);

        render_pixel(renderer, &world_position, 'X');
    }
}

struct REND_Renderer * REND_create(
    const struct CAM_CameraParameters *const calibration,
    const int screen_width,
    const int screen_height)
{
    struct REND_Renderer *const renderer = calloc(1, sizeof(*renderer));

    renderer->frame_buffer = MAT_alloc(screen_height, screen_width);
    renderer->z_buffer = MAT_alloc(screen_height, screen_width);
    renderer->camera_matrix = CAM_get_camera_matrix(calibration);

    return renderer;
}

void REND_render(
    struct REND_Renderer *const renderer,
    const struct REND_Objects *const objects)
{
    reset_frame_buffer(renderer->frame_buffer);
    reset_z_buffer(renderer->z_buffer);

    for (int i = 0; i < objects->length; ++i)
    {
        const struct REND_ObjectWithPosition *const object_with_position = &objects->objects[i];

        render_object(renderer, object_with_position->object, &object_with_position->position);
    }

    draw_frame(renderer->frame_buffer);
}

void REND_destroy(
    struct REND_Renderer *const renderer)
{
    MAT_free(renderer->camera_matrix);
    MAT_free(renderer->z_buffer);
    MAT_free(renderer->frame_buffer);
    free(renderer);
}
