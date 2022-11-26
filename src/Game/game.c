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

#include <math.h>

/* Compensate for the difference in width and height for terminal characters by setting different
 * pixel size in the x and y direction. */
#define PIXEL_SIZE_X (9.0)
#define PIXEL_SIZE_Y (20.0)
#define FOCAL_LENGTH (1.0)
#define SCREEN_WIDTH (100)
#define SCREEN_HEIGHT (50)

enum
{
    SPHERE,
    TORUS,
    NUMBER_OF_OBJECTS
};

void GAME_run(
    const double fps,
    const int steps)
{
    const struct COORD_Coordinate2D optical_center = {
        .x = SCREEN_WIDTH / 2.0,
        .y = SCREEN_HEIGHT / 2.0
    };

    struct COORD_Coordinate3D camera_translation = {
        .x = 0.0,
        .y = 0.0,
        .z = 0.0
    };

    struct CST_Rotation3D camera_rotation = {
        .pitch = 0.0,
        .yaw = 0.0,
        .roll = 0.0
    };

    struct CAM_CameraParameters calibration;
    CAM_get_camera_calibration(
        PIXEL_SIZE_X,
        PIXEL_SIZE_Y,
        FOCAL_LENGTH,
        &optical_center,
        &camera_translation,
        &camera_rotation,
        &calibration);

    const struct COORD_Coordinate3D light_source = {
        .x = -1.0,
        .y = 1.0,
        .z = 1.0
    };

    struct OBJ_Object *const sphere = SPHERE_create(0.2);

    struct OBJ_Object *const torus = TORUS_create(0.15, 0.4);

    const struct COORD_Coordinate3D initial_position = {
        .x = 0.0,
        .y = 0.0,
        .z = 3.0
    };

    const struct CST_Rotation3D initial_rotation = {
        .pitch = 0.0,
        .yaw = 0.0,
        .roll = 0.0
    };

    const double circle_angular_velocity = 1.2 / fps;

    const struct CST_Rotation3D torus_angular_velocity = {
        .pitch = 0.8 / fps,
        .yaw = 0.4 / fps,
        .roll = 0.0 / fps
    };

    struct REND_ObjectWithPosition objects[NUMBER_OF_OBJECTS];

    objects[SPHERE].object = sphere;
    objects[SPHERE].position = initial_position;
    objects[SPHERE].rotation = initial_rotation;

    objects[TORUS].object = torus;
    objects[TORUS].position = initial_position;
    objects[TORUS].rotation = initial_rotation;

    struct REND_Objects model = {
        .objects = &objects[0],
        .length = LENGTH(objects)
    };

    struct REND_Renderer *const renderer = REND_create(&calibration, SCREEN_WIDTH, SCREEN_HEIGHT, fps);

    const double sphere_path_radius = 1.0;
    double sphere_path_radius_angle = 0.0;

    for (int i = 0; i < steps; ++i)
    {
        model.objects[SPHERE].position.x = initial_position.x + (sphere_path_radius * cos(sphere_path_radius_angle));
        model.objects[SPHERE].position.y = initial_position.y;
        model.objects[SPHERE].position.z = initial_position.z + (sphere_path_radius * sin(sphere_path_radius_angle));

        REND_render(renderer, &light_source, &model);

        model.objects[TORUS].rotation.pitch += torus_angular_velocity.pitch;
        model.objects[TORUS].rotation.yaw += torus_angular_velocity.yaw;
        model.objects[TORUS].rotation.roll += torus_angular_velocity.roll;
        sphere_path_radius_angle += circle_angular_velocity;
    }

    TORUS_free(torus);
    SPHERE_free(sphere);
    REND_destroy(renderer);
}
