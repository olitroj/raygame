#include "controller.h"

#define ACCELERATION_TIME   .1f     // Time it takes to accelerate to max speed
#define MAX_MASS            50.f    // Mass where movement stops
#define SPRITE_JUMP_STRENGTH    1000.f  // Magnitude of upwards jump force

#include "raylib.h"

// Maximum speed is a simple linear decreasing function with a zero at max mass
float get_max_speed(float mass) {
    return -mass + MAX_MASS;
}

// TODO: Maybe make SPRIE_ACCEL_TIME dependent on the gravity
void control_player(Sprite* plr) {
    Vector2 move_dir = {0};
    float max_speed = get_max_speed(plr->mass);

    if (IsKeyDown(KEY_W) && plr->grounded)
        apply_impulse_sprite(plr, (Vector2){0.f, -SPRITE_JUMP_STRENGTH});
    if (IsKeyDown(KEY_A) && plr->velocity.x > -max_speed)
        move_dir.x -= plr->mass * max_speed / ACCELERATION_TIME;
    if (IsKeyDown(KEY_D) && plr->velocity.x < max_speed)
        move_dir.x += plr->mass * max_speed / ACCELERATION_TIME;

    if (IsKeyPressed(KEY_Q))
        apply_impulse_sprite(plr, (Vector2){-700.f, -500.f});
    if (IsKeyPressed(KEY_E))
        apply_impulse_sprite(plr, (Vector2){700.f, -500.f});

    if (IsKeyPressed(KEY_UP))
        plr->mass += 1.f;
    if (IsKeyPressed(KEY_DOWN) && plr->mass > 1.f)
        plr->mass -= 1.f;
        
    if (move_dir.x || move_dir.y)
        apply_force_sprite(plr, move_dir);

    // Flag doesn't get set when max speed reached, need to artificially set it here
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_D))
        plr->horizontal_force = 1;
}