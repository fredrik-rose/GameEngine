/**
 * \file
 * \brief Game implementation
 */
#include "game.h"

#include "Base/common.h"
#include "Base/coordinates.h"
#include "Engine/camera.h"
#include "Engine/coordinate_system_transformations.h"
#include "Engine/renderer.h"
#include "Objects/sphere.h"
#include "Objects/torus.h"

/* Compensate for the difference in width and height for terminal characters by setting different
 * pixel size in the x and y direction. */
#define PIXEL_SIZE_X (9.0)
#define PIXEL_SIZE_Y (20.0)
#define FOCAL_LENGTH (1.0)
#define SCREEN_WIDTH (100)
#define SCREEN_HEIGHT (50)

void GAME_run(void)
{
    const struct COORD_Coordinate2D optical_center = {
        .x = SCREEN_WIDTH / 2.0,
        .y = SCREEN_HEIGHT / 2.0
    };

    struct CAM_CameraParameters calibration;
    CAM_get_camera_calibration(
        PIXEL_SIZE_X,
        PIXEL_SIZE_Y,
        FOCAL_LENGTH,
        &optical_center,
        &calibration);

    const struct COORD_Coordinate3D light_source = {
        .x = -1.0,
        .y = 1.0,
        .z = 1.0
    };

    struct OBJ_Object *const sphere = SPHERE_create(1.0);
    const struct COORD_Coordinate3D sphere_position = {
        .x = 0.0,
        .y = 0.0,
        .z = 3.0
    };
    const struct CST_Rotation3D sphere_rotation = {
        .pitch = 0.0,
        .yaw = 0.0,
        .roll = 0.0
    };

    struct REND_ObjectWithPosition objects[] = {
        {
            .object = sphere,
            .position = sphere_position,
            .rotation = sphere_rotation
        }
    };
    struct REND_Objects model = {
        .objects = &objects[0],
        .length = LENGTH(objects)
    };

    struct REND_Renderer *const renderer = REND_create(&calibration, SCREEN_WIDTH, SCREEN_HEIGHT);

    REND_render(renderer, &light_source, &model);

    SPHERE_free(sphere);
    REND_destroy(renderer);
}
