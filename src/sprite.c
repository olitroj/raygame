#include "sprite.h"

#include "globals.h"

#define COLLISION_OFFSET    0.0001f     // Small offset from colliding tile so sprite doesn't get stuck in wall
#define STEP_COUNT          2

static void apply_friction_sprite(Sprite* spr, float tile_friction);
static void apply_force_sprite(Sprite* spr);
static void apply_impulse_sprite(Sprite* spr);
static int collision_step_x_sprite(Sprite* spr, Level* level, Tilemap* tilemap, float future_x);
static int collision_step_y_sprite(Sprite* spr, Level* level, Tilemap* tilemap, float future_y);

void update_sprite(Sprite* spr, Level* level, Tilemap* tilemap) {
    apply_impulse_sprite(spr);
    apply_force_sprite(spr);

    unsigned int tile_size = level->tile_size;
    float future_x = spr->position.x + spr->velocity.x * tile_size * PHYSICS_FIXED_STEP_TIME;
    float future_y = spr->position.y + spr->velocity.y * tile_size * PHYSICS_FIXED_STEP_TIME;
    float future_step_x = (future_x - spr->position.x) / STEP_COUNT;
    float future_step_y = (future_y - spr->position.y) / STEP_COUNT;
    
    int collision_x = 0, collision_y = 0;
    for (int i = 0; i < STEP_COUNT; i++) {
        if (collision_x && collision_y)
            break;
        if (!collision_x)
            collision_x = collision_step_x_sprite(spr, level, tilemap, spr->position.x + future_step_x);
        if (!collision_y)
            collision_y = collision_step_y_sprite(spr, level, tilemap, spr->position.y + future_step_y);
    }

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


static void apply_friction_sprite(Sprite* spr, float tile_friction) {
    float fric_coeff = tile_friction * spr->velocity.x * PHYSICS_FIXED_STEP_TIME;
    if (spr->velocity.x > 0.f)
        spr->velocity.x -= (spr->velocity.x > fric_coeff) ? fric_coeff : 0.f;
    else if (spr->velocity.x < 0.f)
        spr->velocity.x -= (spr->velocity.x < -fric_coeff) ? fric_coeff : 0.f;
}

static void apply_force_sprite(Sprite* spr) {
    spr->velocity.x += spr->force.x / spr->mass * PHYSICS_FIXED_STEP_TIME;
    spr->velocity.y += spr->force.y / spr->mass * PHYSICS_FIXED_STEP_TIME;
    if (spr->force.x)
        spr->horizontal_force = 1;
}

static void apply_impulse_sprite(Sprite* spr) {
    spr->velocity.x += spr->impulse.x / spr->mass;
    spr->velocity.y += spr->impulse.y / spr->mass;
    if (spr->impulse.x)
        spr->horizontal_force = 1;
}

static int collision_step_x_sprite(Sprite* spr, Level* level, Tilemap* tilemap, float future_x) {
    int collision_detected = 0;
    unsigned int tile_size = level->tile_size;
    TileProps* tileprops = tilemap->tile_props;

    float spr_hwidth = spr->size.x / 2.f;
    float spr_hheight = spr->size.y / 2.f;
            
    // Checks left and right edges with future x values for collision tiles
    int left_tile = (int)(future_x - spr_hwidth) / tile_size;
    int right_tile = (int)(future_x + spr_hwidth) / tile_size;
    int top_tile = (int)(spr->position.y - spr_hheight) / tile_size;
    int bottom_tile = (int)(spr->position.y + spr_hheight) / tile_size;
    for (int y = top_tile; y <= bottom_tile; y++) {
        if (tileprops[level->tiles[left_tile + level->width*y]].solid) {
            future_x = (left_tile+1)*tile_size + spr_hwidth + COLLISION_OFFSET;
            spr->velocity.x = 0.f;
            collision_detected = 1;
            break;
        }
        else if (tileprops[level->tiles[right_tile + level->width*y]].solid) {
            future_x = right_tile*tile_size - spr_hwidth - COLLISION_OFFSET;
            spr->velocity.x = 0.f;
            collision_detected = 1;
            break;
        }
    }
    spr->position.x = future_x;
    return collision_detected;
}

static int collision_step_y_sprite(Sprite* spr, Level* level, Tilemap* tilemap, float future_y) {
    int collision_detected = 0;
    unsigned int tile_size = level->tile_size;
    TileProps* tileprops = tilemap->tile_props;

    float spr_hwidth = spr->size.x / 2.f;
    float spr_hheight = spr->size.y / 2.f;
            
    // Checks top and bottom edges with future y values for collision tiles
    int left_tile = (int)(spr->position.x - spr_hwidth) / tile_size;
    int right_tile = (int)(spr->position.x + spr_hwidth) / tile_size;
    int top_tile = (int)(future_y - spr_hheight) / tile_size;
    int bottom_tile = (int)(future_y + spr_hheight) / tile_size;
    spr->grounded = 0;
    for (int x = left_tile; x <= right_tile; x++) {
        if (tileprops[level->tiles[x + level->width*top_tile]].solid) {
            future_y = (top_tile+1)*tile_size + spr_hheight + COLLISION_OFFSET;
            spr->velocity.y = 0.f;
            collision_detected = 1;
            break;
        }
        else if (tileprops[level->tiles[x + level->width*bottom_tile]].solid) {
            future_y = bottom_tile*tile_size - spr_hheight - COLLISION_OFFSET;
            spr->velocity.y = 0.f;
            collision_detected = 1;
            spr->grounded = 1;
            if (!spr->horizontal_force) {
                float tile_friction = tileprops[level->tiles[x + level->width*bottom_tile]].friction;
                apply_friction_sprite(spr, tile_friction);
            }
            break;
        }
    }
    spr->position.y = future_y;
    return collision_detected;
}