#ifndef TILEMAP
#define TILEMAP

#include "raylib.h"

typedef struct tile_props_s {
    float friction;
    unsigned char solid;
    Texture2D texture;
} TileProps;

typedef struct tilemap_s {
    unsigned char id;
    TileProps tile_props[256];
} Tilemap;

int load_tilemap(Tilemap* tilemap, const unsigned char* ptr, const unsigned char* end_ptr);
// int load_tilemap_from_file(Tilemap* tilemap, const char* file_name);
// void free_tilemap_from_file(Tilemap* level);
int load_tilemap_from_bin(Tilemap* tilemap, int tilemap_id);

#endif