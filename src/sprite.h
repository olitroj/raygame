#ifndef SPRITE
#define SPRITE

#include "level.h"
#include "tilemap.h"
#include "raylib.h"

typedef struct sprite_s {
    float mass;
    Vector2 size;
    Vector2 position;
    Vector2 velocity;

    Vector2 force;
    Vector2 impulse;

    char grounded;
    char horizontal_force; 
    
} Sprite;

void update_sprite(Sprite* spr, Level* level, Tilemap* tilemap);
void draw_sprite(Sprite* spr);
void focus_camera_sprite(Sprite* spr, Camera2D* cam);

#endif