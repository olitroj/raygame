#ifndef SPRITE
#define SPRITE

#include "level.h"
#include "tilemap.h"
#include "raylib.h"

typedef struct sprite_s {
    Vector2 position;
    Vector2 size;
    float mass;
    Vector2 velocity;
    bool grounded;
} Sprite;

void apply_force_sprite(Sprite* spr, Vector2 force);
void apply_impulse_sprite(Sprite* spr, Vector2 force);
void update_sprite(Sprite* spr, Level* level, Tilemap* tilemap);
void draw_sprite(Sprite* spr);
void focus_camera_sprite(Sprite* spr, Camera2D* cam);

#endif