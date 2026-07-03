#include "sprite.h"

#include "defs.h"

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

void update_sprite(Sprite* spr, Level* level, Tilemap* tilemap) {
    unsigned int tile_size = level->tile_size;

    float future_x = spr->position.x + spr->velocity.x * tile_size * GetFrameTime();
    float future_y = spr->position.y + spr->velocity.y * tile_size * GetFrameTime();

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
            future_x = (left_tile+1)*tile_size + spr_hwidth + SPRITE_COLLISION_OFFSET;
            spr->velocity.x = 0.f;
            break;
        }
        else if (tileprops[level->tiles[right_tile + level->width*y]].solid) {
            future_x = right_tile*tile_size - spr_hwidth - SPRITE_COLLISION_OFFSET;
            spr->velocity.x = 0.f;
            break;
        }
    }

    // Checks top and bottom edges with future y values for collision tiles
    spr->grounded = false;
    left_tile = (int)(spr->position.x - spr_hwidth) / tile_size;
    right_tile = (int)(spr->position.x + spr_hwidth) / tile_size;
    top_tile = (int)(future_y - spr_hheight) / tile_size;
    bottom_tile = (int)(future_y + spr_hheight) / tile_size;
    for (int x = left_tile; x <= right_tile; x++) {
        if (tileprops[level->tiles[x + level->width*top_tile]].solid) {
            future_y = (top_tile+1)*tile_size + spr_hheight + SPRITE_COLLISION_OFFSET;
            spr->velocity.y = 0.f;
            break;
        }
        else if (tileprops[level->tiles[x + level->width*bottom_tile]].solid) {
            future_y = bottom_tile*tile_size - spr_hheight - SPRITE_COLLISION_OFFSET;
            spr->velocity.y = 0.f;
            spr->grounded = true;

            // TODO: Better friction (only applied when player stops moving)
            float fric_coeff = tileprops[level->tiles[x + level->width*bottom_tile]].friction * spr->velocity.x * GetFrameTime();
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