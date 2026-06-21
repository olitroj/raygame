#include <math.h>
#include "raylib.h"

#include "defs.h"

typedef struct sprite_s {
    Vector2 position;
    Vector2 size;
    float mass;
    Vector2 velocity;
    bool grounded;
} Sprite;

float get_max_speed_sprite(float mass) {
    return SPRITE_SPEED * (-mass + SPRITE_MAX_MASS);
}

void apply_force_sprite(Sprite* spr, Vector2 force) {
    spr->velocity.x += force.x / spr->mass * GetFrameTime();
    spr->velocity.y += force.y / spr->mass * GetFrameTime();
}

void apply_impulse_sprite(Sprite* spr, Vector2 force) {
    spr->velocity.x += force.x / spr->mass;
    spr->velocity.y += force.y / spr->mass;
}

void update_sprite(Sprite* spr, Level* level) {
    float future_x = spr->position.x + spr->velocity.x * TILE_SIZE * GetFrameTime();
    float future_y = spr->position.y + spr->velocity.y * TILE_SIZE * GetFrameTime();
            
    // Checks left and right edges with future x values for collision tiles
    int left_tile = (int)(future_x - spr->size.x/2.f)/TILE_SIZE;
    int right_tile = (int)(future_x + spr->size.x/2.f)/TILE_SIZE;
    int top_tile = (int)(spr->position.y - spr->size.y/2.f)/TILE_SIZE;
    int bottom_tile = (int)(spr->position.y + spr->size.y/2.f)/TILE_SIZE;
    for (int y = top_tile; y <= bottom_tile; y++) {
        if (level->tiles[left_tile + level->width*y] != NULL_TILE) {
            future_x = (left_tile+1)*TILE_SIZE + spr->size.x/2.f + SPRITE_COLLISION_OFFSET;
            spr->velocity.x = 0.f;
            break;
        }
        else if (level->tiles[right_tile + level->width*y] != NULL_TILE) {
            future_x = right_tile*TILE_SIZE - spr->size.x/2.f - SPRITE_COLLISION_OFFSET;
            spr->velocity.x = 0.f;
            break;
        }
    }

    // Checks top and bottom edges with future y values for collision tiles
    spr->grounded = false;
    left_tile = (int)(spr->position.x - spr->size.x/2.f)/TILE_SIZE;
    right_tile = (int)(spr->position.x + spr->size.x/2.f)/TILE_SIZE;
    top_tile = (int)(future_y - spr->size.y/2.f)/TILE_SIZE;
    bottom_tile = (int)(future_y + spr->size.y/2.f)/TILE_SIZE;
    for (int x = left_tile; x <= right_tile; x++) {
        if (level->tiles[x + level->width*top_tile] != NULL_TILE) {
            future_y = (top_tile+1)*TILE_SIZE + spr->size.y/2.f + SPRITE_COLLISION_OFFSET;
            spr->velocity.y = 0.f;
            break;
        }
        else if (level->tiles[x + level->width*bottom_tile] != NULL_TILE) {
            future_y = bottom_tile*TILE_SIZE - spr->size.y/2.f - SPRITE_COLLISION_OFFSET;
            spr->velocity.y = 0.f;
            spr->grounded = true;

            // TODO: Better friction (only applied when player stops moving)
            float fric_coeff = 12.f * spr->velocity.x * GetFrameTime();
            if (spr->velocity.x > 0.f)
                spr->velocity.x -= (spr->velocity.x > fric_coeff) ? fric_coeff : 0.f;
            else if (spr->velocity.x < 0.f)
                spr->velocity.x -= (spr->velocity.x < -fric_coeff) ? fric_coeff : 0.f;
            break;
        }
    }

    spr->position.x = future_x;
    spr->position.y = future_y;
}

void draw_sprite(Sprite* spr, bool draw_bounds) {
    Rectangle rec = {
        spr->position.x - spr->size.x/2.f,
        spr->position.y - spr->size.y/2.f,
        spr->size.x,
        spr->size.y
    };
    DrawRectangleRec(rec, GREEN);
    if (draw_bounds) {
        int left_tile = (int)(spr->position.x - spr->size.x/2.f)/TILE_SIZE;
        int right_tile = (int)(spr->position.x + spr->size.x/2.f)/TILE_SIZE;
        int top_tile = (int)(spr->position.y - spr->size.y/2.f)/TILE_SIZE;
        int bottom_tile = (int)(spr->position.y + spr->size.y/2.f)/TILE_SIZE;
        DrawRectangleLines(left_tile*TILE_SIZE, top_tile*TILE_SIZE, (right_tile-left_tile+1)*TILE_SIZE, (bottom_tile-top_tile+1)*TILE_SIZE, BLUE);
    }
}

void focus_camera_sprite(Sprite* spr, Camera2D* cam) {
    cam->target = (Vector2){ spr->position.x, spr->position.y };
    cam->offset = (Vector2){ GetScreenWidth() * 0.5f, GetScreenHeight() * 0.7f };
    cam->rotation = 0.f;
    cam->zoom = 1.f;
}