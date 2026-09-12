#include "camera.h"

void set_target_camera(MyCam* cam, Vector2 target) {
    cam->cam_obj.target = target;
    cam->target = NULL;
    cam->cam_obj.rotation = 0.f;
    cam->cam_obj.zoom = 1.f;
}

void set_persistent_target_camera(MyCam* cam, Vector2* target, float lerp_speed) {
    cam->target = target;
    cam->lerp_speed = lerp_speed;
    cam->cam_obj.rotation = 0.f;
    cam->cam_obj.zoom = 1.f;
}

#define CAMERA_MIN_LAG      1.f // How far away before camera snaps onto target

void update_camera(MyCam* cam) {
    cam->cam_obj.offset = (Vector2){ GetScreenWidth() * 0.5f, GetScreenHeight() * 0.5f };
    if (cam->target != NULL) {
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