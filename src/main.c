#include "raylib.h"

#include "level.h"
#include "tilemap.h"
#include "sprite.h"
#include "controller.h"

#include "globals.h"

int main(void)
{
    InitWindow(800, 450, "Demo");

    Level l = {0};
    load_level_from_bin(&l, 0);
    LOG("LEVEL: %d Tilemap ID: %d\nName: (%s) Size: (%d %d) Start: (%d %d) Gravity: %f Tile size: %d\n", l.level_id, l.tilemap_id, l.name, l.width, l.height, l.start_x, l.start_y, l.gravity, l.tile_size);

    Tilemap t = {0};
    load_tilemap_from_bin(&t, l.tilemap_id);

    Sprite plr = {
        13.f,
        (Vector2){50.f, 50.f},
        (Vector2){l.start_x * l.tile_size, l.start_y * l.tile_size},
    };
    Camera2D cam = {0};

    float accumulator = 0.f;

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
            TIME_START(physics);

            update_sprite(&plr, &l, &t);
            plr.impulse = (Vector2){0};
            accumulator -= PHYSICS_FIXED_STEP_TIME;

            TIME_END(physics);
        }
        plr.force = (Vector2){0};

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
            DrawText(TextFormat("Mass: %2.1f", plr.mass), 10, 70, 20, RED);
            DrawText(TextFormat("Velocity: %2.1f %2.1f", plr.velocity.x, plr.velocity.y), 10, 100, 20, RED);
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