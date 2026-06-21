#include <stdio.h>
#include "raylib.h"

#include "defs.h"
#include "level.c"
#include "sprite.c"
#include "controller.c"

int main(void)
{
    InitWindow(800, 450, "Demo");

    Level l = {0};
    load_level_from_bin(&l, 0);
    printf("LEVEL: %s Size: (%d %d) Start: (%d %d) Gravity: %f\n", l.name, l.width, l.height, l.start_x, l.start_y, l.gravity);

    Sprite plr = {
        (Vector2){l.start_x * TILE_SIZE, l.start_y * TILE_SIZE},
        (Vector2){50.f, 50.f},
        30.f
    };
    Camera2D cam = {0};

    // TODO: Fix sprites phasing through walls on low FPS
    // SetTargetFPS(20);

    while (!WindowShouldClose())
    {
        apply_force_sprite(&plr, (Vector2){0.f, plr.mass * l.gravity});
        control_player(&plr);
        update_sprite(&plr, &l);

        focus_camera_sprite(&plr, &cam);

        if (IsKeyPressed(KEY_F11))
            ToggleBorderlessWindowed();

        BeginDrawing();
            ClearBackground(RAYWHITE);

            BeginMode2D(cam);
                draw_level(&l);
                draw_sprite(&plr, false);
            EndMode2D();

            DrawFPS(10, 10);
            DrawText(l.name, 10, 40, 20, RED);
            char buf[32] = {0};
            sprintf(buf, "Mass: %2.1f", plr.mass);
            DrawText(buf, 10, 70, 20, RED);
            char buf2[32] = {0};
            sprintf(buf, "Velocity: %2.1f %2.1f", plr.velocity.x, plr.velocity.y);
            DrawText(buf, 10, 100, 20, RED);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}