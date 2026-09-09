#include "raylib.h"

#include "level.h"
#include "tilemap.h"
#include "sprite.h"
#include "controller.h"

#include "globals.h"

// Debug
#include <stdio.h>
#include <time.h>
#define NANOS_IN_PHYSICS_STEP PHYSICS_FIXED_STEP_TIME * 100000000

int main(void)
{
    InitWindow(800, 450, "Demo");

    Level l = {0};
    load_level_from_bin(&l, 0);
    printf("LEVEL: %d Tilemap ID: %d\nName: (%s) Size: (%d %d) Start: (%d %d) Gravity: %f Tile size: %d\n", l.level_id, l.tilemap_id, l.name, l.width, l.height, l.start_x, l.start_y, l.gravity, l.tile_size);

    Tilemap t = {0};
    load_tilemap_from_bin(&t, l.tilemap_id);

    Sprite plr = {
        13.f,
        (Vector2){50.f, 50.f},
        (Vector2){l.start_x * l.tile_size, l.start_y * l.tile_size},
    };
    Camera2D cam = {0};

    float accumulator = 0.f;
    struct timespec physics_start = {0}, physics_end = {0};

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_F11))
            ToggleBorderlessWindowed();

        // Player input (get sprite force and impulse)
        control_player(&plr, l.gravity);

        // Fixed-step physics (60Hz)
        // Performs however many steps fit in the time it took to render last frame
        // Consumes impulse on the first step, consumes force after all steps
        accumulator += GetFrameTime();
        while (accumulator > PHYSICS_FIXED_STEP_TIME) {
            timespec_get(&physics_start, TIME_UTC);

            update_sprite(&plr, &l, &t);
            plr.impulse = (Vector2){0};
            accumulator -= PHYSICS_FIXED_STEP_TIME;

            timespec_get(&physics_end, TIME_UTC);
        }
        plr.force = (Vector2){0};

        long physics_step_time = physics_end.tv_nsec - physics_start.tv_nsec;

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
            sprintf(buf, "Physics time: %ld ns", physics_step_time);
            Color physics_time_color = GREEN;
            if (physics_step_time > NANOS_IN_PHYSICS_STEP * .8f) {
                physics_time_color = YELLOW;
            } else if (physics_step_time > NANOS_IN_PHYSICS_STEP) {
                physics_time_color = RED;
            }
            DrawText(buf, 10, 130, 20, physics_time_color);
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