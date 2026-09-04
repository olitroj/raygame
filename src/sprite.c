#include "sprite.h"

#include "globals.h"

#define COLLISION_OFFSET    0.0001f     // Small offset from colliding tile so sprite doesn't get stuck in wall

static void apply_friction(Sprite* spr, int tile_friction);

// Applies a force (on every frame) over some time, updates resulting velocity
void apply_force_sprite(Sprite* spr, Vector2 force) {
    spr->velocity.x += force.x / spr->mass * PHYSICS_FIXED_STEP_TIME;
    spr->velocity.y += force.y / spr->mass * PHYSICS_FIXED_STEP_TIME;
    if (force.x)
        spr->horizontal_force = 1;
}

// Applies an instantanious (single frame) force to the sprite, updates resulting velocity
void apply_impulse_sprite(Sprite* spr, Vector2 force) {
    spr->velocity.x += force.x / spr->mass;
    spr->velocity.y += force.y / spr->mass;
    if (force.x)
        spr->horizontal_force = 1;
}

// Updates sprite position based on current velocity. Corrects position for collision and friction
void update_sprite(Sprite* spr, Level* level, Tilemap* tilemap) {
    unsigned int tile_size = level->tile_size;

    float future_x = spr->position.x + spr->velocity.x * tile_size * PHYSICS_FIXED_STEP_TIME;
    float future_y = spr->position.y + spr->velocity.y * tile_size * PHYSICS_FIXED_STEP_TIME;

    float spr_hwidth = spr->size.x / 2.f;
    float spr_hheight = spr->size.y / 2.f;

    TileProps* tileprops = tilemap->tile_props;
            
    // Checks left and right edges with future x values for collision tiles
    int left_tile = (int)(future_x - spr_hwidth) / tile_size;
    int right_tile = (int)(future_x + spr_hwidth) / tile_size;
    int top_tile = (int)(spr->position.y - spr_hheight) / tile_size;
    int bottom_tile = (int)(spr->position.y + spr_hheight) / tile_size;
    for (int y = top_tile; y <= bottom_tile; y++) {
        if (tileprops[level->tiles[left_tile + level->width*y]].solid) {
            future_x = (left_tile+1)*tile_size + spr_hwidth + COLLISION_OFFSET;
            spr->velocity.x = 0.f;
            break;
        }
        else if (tileprops[level->tiles[right_tile + level->width*y]].solid) {
            future_x = right_tile*tile_size - spr_hwidth - COLLISION_OFFSET;
            spr->velocity.x = 0.f;
            break;
        }
    }

    // Checks top and bottom edges with future y values for collision tiles
    spr->grounded = 0;
    left_tile = (int)(spr->position.x - spr_hwidth) / tile_size;
    right_tile = (int)(spr->position.x + spr_hwidth) / tile_size;
    top_tile = (int)(future_y - spr_hheight) / tile_size;
    bottom_tile = (int)(future_y + spr_hheight) / tile_size;
    for (int x = left_tile; x <= right_tile; x++) {
        if (tileprops[level->tiles[x + level->width*top_tile]].solid) {
            future_y = (top_tile+1)*tile_size + spr_hheight + COLLISION_OFFSET;
            spr->velocity.y = 0.f;
            break;
        }
        else if (tileprops[level->tiles[x + level->width*bottom_tile]].solid) {
            future_y = bottom_tile*tile_size - spr_hheight - COLLISION_OFFSET;
            spr->velocity.y = 0.f;
            spr->grounded = 1;
            
            if (!spr->horizontal_force) {
                int tile_friction = tileprops[level->tiles[x + level->width*bottom_tile]].friction;
                apply_friction(spr, tile_friction);
            }
            break;
        }
    }

    spr->position.x = future_x;
    spr->position.y = future_y;
    spr->horizontal_force = 0;
}

void draw_sprite(Sprite* spr) {
    Rectangle rec = {
        spr->position.x - spr->size.x/2.f,
        spr->position.y - spr->size.y/2.f,
        spr->size.x,
        spr->size.y
    };
    DrawRectangleRec(rec, GREEN);
}

void focus_camera_sprite(Sprite* spr, Camera2D* cam) {
    cam->target = (Vector2){ spr->position.x, spr->position.y };
    cam->offset = (Vector2){ GetScreenWidth() * 0.5f, GetScreenHeight() * 0.7f };
    cam->rotation = 0.f;
    cam->zoom = 1.f;
}


static void apply_friction(Sprite* spr, int tile_friction) {
    float fric_coeff = tile_friction * spr->velocity.x * PHYSICS_FIXED_STEP_TIME;
    if (spr->velocity.x > 0.f)
        spr->velocity.x -= (spr->velocity.x > fric_coeff) ? fric_coeff : 0.f;
    else if (spr->velocity.x < 0.f)
        spr->velocity.x -= (spr->velocity.x < -fric_coeff) ? fric_coeff : 0.f;
}