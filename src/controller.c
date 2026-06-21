#include "raylib.h"

#include "defs.h"

// TODO: Maybe make SPRIE_ACCEL_TIME dependent on the gravity
void control_player(Sprite* plr) {
    Vector2 move_dir = {0};
    float max_speed = get_max_speed_sprite(plr->mass);

    if (IsKeyDown(KEY_W) && plr->grounded)
        apply_impulse_sprite(plr, (Vector2){0.f, -SPRITE_JUMP_STRENGTH});
    if (IsKeyDown(KEY_A) && plr->velocity.x > -max_speed)
        move_dir.x -= plr->mass * max_speed / SPRITE_ACCEL_TIME;
    if (IsKeyDown(KEY_D) && plr->velocity.x < max_speed)
        move_dir.x += plr->mass * max_speed / SPRITE_ACCEL_TIME;

    if (IsKeyPressed(KEY_Q))
        apply_impulse_sprite(plr, (Vector2){-700.f, -500.f});
    if (IsKeyPressed(KEY_E))
        apply_impulse_sprite(plr, (Vector2){700.f, -500.f});

    if (IsKeyPressed(KEY_UP))
        plr->mass += 1.f;
    if (IsKeyPressed(KEY_DOWN) && plr->mass > 1.f)
        plr->mass -= 1.f;
        
    apply_force_sprite(plr, move_dir);
}