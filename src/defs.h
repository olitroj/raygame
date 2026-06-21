#ifndef DEFS
#define DEFS

#define TILE_SIZE   30
#define NULL_TILE   ' '

#define SPRITE_MAX_MASS             50.f        // Maximum sprite mass, stops moving at this point
#define SPRITE_JUMP_STRENGTH        150.f       // Magnitude of upwards jump force
#define SPRITE_ACCEL_TIME           .1f         // Time it takes for sprite to reach max speed
#define SPRITE_IMPULSE_MASS_FACTOR  .3f         // Decreases mass influence when applying impulse
#define SPRITE_COLLISION_OFFSET     0.0001f     // Small offset from colliding tile so sprite doesn't get stuck in wall

#endif