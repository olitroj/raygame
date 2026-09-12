#include "raylib.h"

#include "level.h"
#include "tilemap.h"
#include "sprite.h"
#include "controller.h"
#include "camera.h"

#include "globals.h"

int main(void)
{
    InitWindow(800, 450, "Demo");

    Level l = {0};
    load_level_from_bin(&l, 0);
    Tilemap t = {0};
    load_tilemap_from_bin(&t, l.tilemap_id);
    Sprite plr = {0};
    create_sprite(&plr, 13.f, 50.f, 50.f, l.start_x * l.tile_size, l.start_y * l.tile_size);
    MyCam cam = {0};
    set_persistent_target_camera(&cam, &(plr.position), 20.f);

    float accumulator = 0.f;

    char freecam = 0;
    char falling = 0;

    //SetTargetFPS(20);

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_F11))
            ToggleBorderlessWindowed();
        if (IsKeyPressed(KEY_V)) {
            freecam = !freecam;
            if (!freecam && !falling)
                set_persistent_target_camera(&cam, &(plr.position), 20.f);
        }

        if (plr.position.y < (l.height + 15) * l.tile_size) {
            if (!freecam)
                control_player(&plr);
        } else if (!falling) {
            set_target_camera(&cam, cam.cam_obj.target);
            falling = 1;
        } 
        if (freecam)
            control_freecam(&cam);

        apply_force_sprite(&plr, (Vector2){ 0.f, plr.mass * l.gravity });

        // Fixed-step physics (60Hz)
        // Performs however many steps fit in the time it took to render last frame
        // Consumes impulse on the first step, consumes force after all steps
        accumulator += GetFrameTime();
        while (accumulator > PHYSICS_FIXED_STEP_TIME) {
            //TIME_START(physics);

            update_sprite(&plr, &l, &t);
            plr.impulse = (Vector2){0};
            accumulator -= PHYSICS_FIXED_STEP_TIME;

            //TIME_END(physics);
        }
        plr.force = (Vector2){0};

        // Rendering
        update_camera(&cam);
        BeginDrawing();
            ClearBackground(RAYWHITE);

            BeginMode2D(cam.cam_obj);
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
#include "camera.c"