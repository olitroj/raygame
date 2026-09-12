#ifndef CAMERA
#define CAMERA

#include "raylib.h"
#include "sprite.h"

typedef struct camera_s {
    Vector2* target;
    float lerp_speed;
    Camera2D cam_obj;
} MyCam;

void set_target_camera(MyCam* cam, Vector2 target);
void set_persistent_target_camera(MyCam* cam, Vector2* target, float lerp_speed);
void update_camera(MyCam* cam);

#endif