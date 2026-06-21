#ifndef DEFS
#define DEFS

#define TILE_SIZE 30
#define NULL_TILE ' '

#define SPRITE_SPEED                3.0f        // General factor for sprite speed
#define SPRITE_JUMP_STRENGTH        1000.f      // Magnitude of upwards jump force
#define SPRITE_MAX_MASS             25.f        // Mass at which a sprite can't move
#define SPRITE_ACCEL_TIME           0.1f        // Time it takes for sprite to reach max speed
#define SPRITE_COLLISION_OFFSET     0.0001f     // Small offset from colliding tile so sprite doesn't get stuck in wall

#endif