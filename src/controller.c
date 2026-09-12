#include "controller.h"

#include "raylib.h"

#define SPRITE_JUMP_STRENGTH    1000.f  // Magnitude of upwards jump force

void control_player(Sprite* plr) {
    Vector2 movement = {0};
    Vector2 impulse = {0};

    if (IsKeyPressed(KEY_W) && plr->grounded)
        impulse.y -= SPRITE_JUMP_STRENGTH;
    if (IsKeyDown(KEY_A))
        movement.x -= 1;
    if (IsKeyDown(KEY_D))
        movement.x += 1;

    if (IsKeyPressed(KEY_Q)) {
        impulse.x -= 700.f;
        impulse.y -= 500.f;
    }
    if (IsKeyPressed(KEY_E)) {
        impulse.x += 700.f;
        impulse.y -= 500.f;
    }

    if (IsKeyPressed(KEY_UP))
        plr->mass += 1.f;
    if (IsKeyPressed(KEY_DOWN) && plr->mass > 1.f)
        plr->mass -= 1.f;

    apply_movement_sprite(plr, movement);
    apply_impulse_sprite(plr, impulse);
}

#define FREECAM_SPEED   2000.f

void control_freecam(MyCam* cam) {
    Vector2 movement = cam->cam_obj.target;

    if (IsKeyDown(KEY_W))
        movement.y -= FREECAM_SPEED * GetFrameTime();
    if (IsKeyDown(KEY_A))
        movement.x -= FREECAM_SPEED * GetFrameTime();
    if (IsKeyDown(KEY_S))
        movement.y += FREECAM_SPEED * GetFrameTime();
    if (IsKeyDown(KEY_D))
        movement.x += FREECAM_SPEED * GetFrameTime();

    set_target_camera(cam, movement);
}