#ifndef CAMERA
#define CAMERA

#include "raylib.h"
#include "sprite.h"

typedef struct camera_s {
    Vector2* target;
    float lerp_speed;
    Camera2D cam_obj;
} Cam;

static inline void set_target_camera(Cam* cam, float target_x, float target_y);
static inline void set_persistent_target_camera(Cam* cam, Vector2* target, float lerp_speed);
static inline void set_offset_camera(Cam* cam, float offset_x, float offset_y);
static inline void set_rotation_camera(Cam* cam, float rotation);
static inline void set_zoom_camera(Cam* cam, float zoom);
static inline void get_current_position_camera(Cam* cam, float* cam_x, float* cam_y);
void update_camera(Cam* cam);

#endif