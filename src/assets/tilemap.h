#ifndef ASSETS_TILEMAP
#define ASSETS_TILEMAP

#include "../apis/apis.h"

typedef struct tile_props_s {
    float friction;
    unsigned char solid;
    TextureHandle texture;
} TileProps;

typedef struct tilemap_s {
    TileProps tile_props[256];
} Tilemap;

int load_from_bin_tilemap(Tilemap* tilemap, int tilemap_id, unsigned int tile_size);

#endif