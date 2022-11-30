/**
 * \file
 * \brief Renderer implementation
 */
#include "frame_synchronizer.h"
#include "illumination.h"

#include <Base/common.h>
#include <Base/coordinates.h>
#include <Base/math_functions.h>
#include <Engine/camera.h>
#include <Engine/coordinate_system_transformations.h>
#include <Engine/object.h>
#include <Engine/renderer.h>
#include <LinearAlgebra/Matrix.h>

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
    /**
     * The frame synchronizer, makes sure a certain frame rate is achieved
     */
    struct SYNC_Frame_Synchronizer *frame_synchronizer;
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
 * \brief Converts an illumination level to a certain pixel "color"
 *
 * \param[in] illumination The illumination level [0, 1]
 *
 * \return Pixel color
 */
static char convert_illumination_to_pixel_color(
    const double illumination)
{
    static const char illumination_levels[] = {'.', ',', '-', '~', ':', ';', '=', '!', '*', '#', '$', '@'};
    const int lenght = LENGTH(illumination_levels);
    const double luminance_index = (illumination * lenght);
    const int clamped_luminance_index = (int)MATH_clamp(luminance_index, 0, lenght - 1);
    const char color = illumination_levels[clamped_luminance_index];

    return color;
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
    assert(renderer->frame_buffer->rows == renderer->z_buffer->rows); // LCOV_EXCL_LINE
    assert(renderer->frame_buffer->cols == renderer->z_buffer->cols); // LCOV_EXCL_LINE

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
    const struct COORD_Coordinate3D *const light_source,
    const struct OBJ_Object *const object,
    const struct COORD_Coordinate3D *const position,
    const struct CST_Rotation3D *const rotation)
{
    struct MAT_Matrix *const rotation_matrix = CST_get_extrinsic_rotation_matrix(rotation);

    for (int i = 0; i < object->length; ++i)
    {
        struct COORD_Coordinate3D world_position;
        CST_affine_transformation(&object->coordinates[i], rotation_matrix, position, &world_position);

        struct COORD_Coordinate3D surface_normal;
        CST_linear_transformation(&object->surface_normals[i], rotation_matrix, &surface_normal);

        const double illumination = ILL_get_illumination(light_source, &world_position, &surface_normal);
        const char color = convert_illumination_to_pixel_color(illumination);

        render_pixel(renderer, &world_position, color);
    }

    MAT_free(rotation_matrix);
}

struct REND_Renderer * REND_create(
    const struct CAM_CameraParameters *const calibration,
    const int screen_width,
    const int screen_height,
    const double fps)
{
    struct REND_Renderer *const renderer = calloc(1, sizeof(*renderer));

    renderer->frame_buffer = MAT_alloc(screen_height, screen_width);
    renderer->z_buffer = MAT_alloc(screen_height, screen_width);
    renderer->camera_matrix = CAM_get_camera_matrix(calibration);
    renderer->frame_synchronizer = SYNC_create(fps);

    return renderer;
}

void REND_render(
    struct REND_Renderer *const renderer,
    const struct COORD_Coordinate3D *const light_source,
    const struct REND_Objects *const objects)
{
    reset_frame_buffer(renderer->frame_buffer);
    reset_z_buffer(renderer->z_buffer);

    for (int i = 0; i < objects->length; ++i)
    {
        const struct REND_ObjectWithPosition *const object_with_position = &objects->objects[i];

        render_object(
            renderer,
            light_source,
            object_with_position->object,
            &object_with_position->position,
            &object_with_position->rotation);
    }

    SYNC_sync(renderer->frame_synchronizer);

    draw_frame(renderer->frame_buffer);
}

void REND_destroy(
    struct REND_Renderer *const renderer)
{
    SYNC_destroy(renderer->frame_synchronizer);
    MAT_free(renderer->camera_matrix);
    MAT_free(renderer->z_buffer);
    MAT_free(renderer->frame_buffer);
    free(renderer);
}
