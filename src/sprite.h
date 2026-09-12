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
    Vector2 movement;

    char grounded;
    char horizontal_force; 
    
} Sprite;

static inline void create_sprite(Sprite* spr, float mass, float pos_x, float pos_y, float width, float height);
static inline void apply_force_sprite(Sprite* spr, Vector2 force);
static inline void apply_impulse_sprite(Sprite* spr, Vector2 impulse);
static inline void apply_movement_sprite(Sprite* spr, Vector2 move_vec);
void update_sprite(Sprite* spr, Level* level, Tilemap* tilemap);
void draw_sprite(Sprite* spr);
void focus_camera_sprite(Sprite* spr, Camera2D* cam);

#endif