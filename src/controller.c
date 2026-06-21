#include "raylib.h"

#include "defs.h"

void control_player(Sprite* plr) {
    Vector2 move_dir = {0};
    if (IsKeyDown(KEY_W) && plr->grounded)
        apply_impulse_sprite(plr, (Vector2){0.f, -SPRITE_JUMP_STRENGTH});
    if (IsKeyDown(KEY_A))
        move_dir.x -= plr->mass * get_max_speed_sprite(plr) / SPRITE_ACCEL_TIME;
    if (IsKeyDown(KEY_D))
        move_dir.x += plr->mass * get_max_speed_sprite(plr) / SPRITE_ACCEL_TIME;
    if (IsKeyPressed(KEY_Q))
        apply_impulse_sprite(plr, (Vector2){-1000.f, -100.f});
    if (IsKeyPressed(KEY_E))
        apply_impulse_sprite(plr, (Vector2){1000.f, -100.f});
    if (IsKeyPressed(KEY_UP) && plr->mass < SPRITE_MAX_MASS)
        plr->mass += 5.f;
    if (IsKeyPressed(KEY_DOWN) && plr->mass > 5.f)
        plr->mass -= 5.f;
    apply_force_sprite(plr, move_dir);
}