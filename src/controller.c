#include "controller.h"

#define ACCELERATION_TIME   .1f     // Time it takes to accelerate to max speed
#define MAX_MASS            50.f    // Mass where movement stops
#define SPRITE_JUMP_STRENGTH    1000.f  // Magnitude of upwards jump force

#include "raylib.h"

void control_player(Sprite* plr, float gravity) {
    float max_speed = -plr->mass + MAX_MASS;

    plr->force.y += plr->mass * gravity;

    if (IsKeyPressed(KEY_W) && plr->grounded)
        plr->impulse.y -= SPRITE_JUMP_STRENGTH;
    if (IsKeyDown(KEY_A) && plr->velocity.x > -max_speed)
        plr->force.x -= plr->mass * max_speed / ACCELERATION_TIME;
    if (IsKeyDown(KEY_D) && plr->velocity.x < max_speed)
        plr->force.x += plr->mass * max_speed / ACCELERATION_TIME;

    if (IsKeyPressed(KEY_Q)) {
        plr->impulse.x -= 700.f;
        plr->impulse.y -= 500.f;
    }
    if (IsKeyPressed(KEY_E)) {
        plr->impulse.x += 700.f;
        plr->impulse.y -= 500.f;
    }

    if (IsKeyPressed(KEY_UP))
        plr->mass += 1.f;
    if (IsKeyPressed(KEY_DOWN) && plr->mass > 1.f)
        plr->mass -= 1.f;

    // Flag doesn't get set when max speed reached (because force stops being applied), need to artificially set it here
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_D))
        plr->horizontal_force = 1;
}