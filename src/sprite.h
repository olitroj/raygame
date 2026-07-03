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

float get_max_speed_sprite(float mass);
void apply_force_sprite(Sprite* spr, Vector2 force);
void apply_impulse_sprite(Sprite* spr, Vector2 force);
void update_sprite(Sprite* spr, Level* level, Tilemap* tilemap);
void draw_sprite(Sprite* spr, bool draw_bounds);
void focus_camera_sprite(Sprite* spr, Camera2D* cam);

#endif