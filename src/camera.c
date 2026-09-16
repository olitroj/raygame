#include "camera.h"

static inline void set_target_camera(Cam* cam, float target_x, float target_y) {
    cam->cam_obj.target.x = target_x;
    cam->cam_obj.target.y = target_y;
    cam->target = NULL;
}

static inline void set_persistent_target_camera(Cam* cam, Vector2* target, float lerp_speed) {
    cam->target = target;
    cam->lerp_speed = lerp_speed;
}

static inline void set_offset_camera(Cam* cam, float offset_x, float offset_y) {
    cam->cam_obj.offset.x = offset_x;
    cam->cam_obj.offset.y = offset_y;
}

static inline void set_rotation_camera(Cam* cam, float rotation) {
    cam->cam_obj.rotation = rotation;
}

static inline void set_zoom_camera(Cam* cam, float zoom) {
    cam->cam_obj.rotation = zoom;
}

static inline void get_current_position_camera(Cam* cam, float* cam_x, float* cam_y) {
    *cam_x = cam->cam_obj.target.x;
    *cam_y = cam->cam_obj.target.y;
}

#define CAMERA_MIN_LAG      1.f // How far away before camera snaps onto target

void update_camera(Cam* cam) {
    if (cam->target != NULL) {
        if (cam->cam_obj.zoom == 0.f)
            cam->cam_obj.zoom = 1.f;

        if (cam->lerp_speed) {
            float diff_x = cam->target->x - cam->cam_obj.target.x;
            float diff_y = cam->target->y - cam->cam_obj.target.y;
            if (diff_x * diff_x + diff_y * diff_y > CAMERA_MIN_LAG * CAMERA_MIN_LAG) {
                float rate = cam->lerp_speed * GetFrameTime();
                float alpha = rate / (1.f + rate);
                cam->cam_obj.target.x += diff_x * alpha;
                cam->cam_obj.target.y += diff_y * alpha;
            } else
                cam->cam_obj.target = *(cam->target);
        } else
            cam->cam_obj.target = *(cam->target);
    }
}