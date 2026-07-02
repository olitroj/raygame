#include "raylib.h"

#include "defs.h"

extern const unsigned char _binary_assets_tilemaps_summer_start[];
extern const unsigned char _binary_assets_tilemaps_summer_end[];

typedef struct tile_props_s {
    unsigned char size;
    unsigned char friction;
    unsigned char solid;
    Texture2D texture;
} TileProps;

typedef struct tilemap_s {
    unsigned char id;
    TileProps tile_props[256];
} Tilemap;

static int load_tilemap(Tilemap* tilemap, const unsigned char* ptr, const unsigned char* end_ptr) {
    Tilemap t = {0};

    unsigned char byte = 0;
    if (read_byte(&ptr, end_ptr, &byte) == -1 || byte != 0xA0)
        return -1;
    if (read_byte(&ptr, end_ptr, &byte) == -1 || byte != 0x44)
        return -1;

    if (read_byte(&ptr, end_ptr, &(t.id)) == -1)
        return -1;
    unsigned char tile_count = 0;
    if (read_byte(&ptr, end_ptr, &tile_count) == -1)
        return -1;

    const unsigned char* color_ptr = ptr + 3*tile_count;

    for (int i = 0; i < tile_count; i++) {
        if (read_byte(&ptr, end_ptr, &(t.tile_props[i].size)) == -1)
            return -1;
        if (read_byte(&ptr, end_ptr, &(t.tile_props[i].friction)) == -1)
            return -1;
        if (read_byte(&ptr, end_ptr, &(t.tile_props[i].solid)) == -1)
            return -1;

        Image image = { (unsigned char*)color_ptr, t.tile_props[i].size, t.tile_props[i].size, 1, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8 };
        Texture2D texture = LoadTextureFromImage(image);
        t.tile_props[i].texture = texture;
        
        color_ptr += t.tile_props[i].size * t.tile_props[i].size * 4;
    }

    *tilemap = t;
    return 0;
}

// int load_tilemap_from_file(Tilemap* tilemap, const char* file_name) {
//     if (tilemap == NULL || file_name == NULL)
//         return -1;

//     int byte_cnt;
//     unsigned char* ptr = LoadFileData(file_name, &byte_cnt);
//     if (ptr == NULL || byte_cnt == 0)
//         return -1;

//     return load_tilemap(tilemap, ptr, ptr + byte_cnt - 1);
// }

// void free_tilemap_from_file(Tilemap* level) {
//     UnloadFileData((unsigned char*)level->bytes);
// }

int load_tilemap_from_bin(Tilemap* tilemap, int tilemap_id) {
    if (tilemap == NULL)
        return -1;

    switch (tilemap_id) {
        case 0: return load_tilemap(tilemap, _binary_assets_tilemaps_summer_start, _binary_assets_tilemaps_summer_end-1);
        default: return -1;
    }
}