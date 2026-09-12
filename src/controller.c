#include "controller.h"

#define SPRITE_JUMP_STRENGTH    1000.f  // Magnitude of upwards jump force

void control_player(Sprite* plr) {
    float movement_x = 0.f;

    if (IsKeyPressed(KEY_W) && plr->grounded)
        plr->impulse.y -= SPRITE_JUMP_STRENGTH;
    if (IsKeyDown(KEY_A))
        movement_x -= 1;
    if (IsKeyDown(KEY_D))
        movement_x += 1;

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

    plr->movement.x = movement_x;
}