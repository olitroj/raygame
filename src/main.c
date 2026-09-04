#include "raylib.h"

#include "level.h"
#include "tilemap.h"
#include "sprite.h"
#include "controller.h"

#include "globals.h"

// Debug
#include <stdio.h>
#include <time.h>

int main(void)
{
    InitWindow(800, 450, "Demo");

    Level l = {0};
    load_level_from_bin(&l, 0);
    printf("LEVEL: %d Tilemap ID: %d\nName: (%s) Size: (%d %d) Start: (%d %d) Gravity: %f Tile size: %d\n", l.level_id, l.tilemap_id, l.name, l.width, l.height, l.start_x, l.start_y, l.gravity, l.tile_size);

    Tilemap t = {0};
    load_tilemap_from_bin(&t, l.tilemap_id);

    Sprite plr = {
        (Vector2){l.start_x * l.tile_size, l.start_y * l.tile_size},
        (Vector2){50.f, 50.f},
        13.f
    };
    Camera2D cam = {0};

    // TODO: Fix sprites phasing through walls on low FPS
    // SetTargetFPS(20);

    float accumulator = 0.f;

    struct timespec physics_start = {0}, physics_end = {0};

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_F11))
            ToggleBorderlessWindowed();

        // Player input
        Vector2 plr_force = {0}, plr_impulse = {0};
        control_player(&plr, &plr_force, &plr_impulse);

        // Fixed-step physics (60Hz)
        // Performs however many steps fit in the time it took to render last frame, applies impulse only on the first step
        accumulator += GetFrameTime();
        char first_step = 1;
        while (accumulator > PHYSICS_FIXED_STEP_TIME) {
            timespec_get(&physics_start, TIME_UTC);

            if (first_step) {
                apply_impulse_sprite(&plr, plr_impulse);
                first_step = 0;
            }

            apply_force_sprite(&plr, (Vector2){0.f, plr.mass * l.gravity});
            apply_force_sprite(&plr, plr_force);
            update_sprite(&plr, &l, &t);
            accumulator -= PHYSICS_FIXED_STEP_TIME;

            timespec_get(&physics_end, TIME_UTC);
       }

        // Rendering
        focus_camera_sprite(&plr, &cam);
        BeginDrawing();
            ClearBackground(RAYWHITE);

            BeginMode2D(cam);
                draw_sprite(&plr);
                draw_level(&l, &t);
            EndMode2D();

            DrawFPS(10, 10);
            DrawText(l.name, 10, 40, 20, RED);
            char buf[32] = {0};
            sprintf(buf, "Mass: %2.1f", plr.mass);
            DrawText(buf, 10, 70, 20, RED);
            sprintf(buf, "Velocity: %2.1f %2.1f", plr.velocity.x, plr.velocity.y);
            DrawText(buf, 10, 100, 20, RED);
            sprintf(buf, "Physics time: %ld ns", physics_end.tv_nsec - physics_start.tv_nsec);
            DrawText(buf, 10, 130, 20, RED);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

#include "level.c"
#include "tilemap.c"
#include "sprite.c"
#include "controller.c"
#include "read.c"