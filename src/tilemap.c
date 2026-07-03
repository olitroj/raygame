#include "tilemap.h"

#include "defs.h"
#include "util.h"

extern const unsigned char _binary_assets_t_summer_start[];
extern const unsigned char _binary_assets_t_summer_end[];

int load_tilemap(Tilemap* tilemap, const unsigned char* ptr, const unsigned char* end_ptr) {
    Tilemap t = {0};

    unsigned char byte = 0;
    if (read_byte(&ptr, end_ptr, &byte) == -1 || byte != 0xA0)
        return -1;
    if (read_byte(&ptr, end_ptr, &byte) == -1 || byte != 0x44)
        return -1;
    if (read_byte(&ptr, end_ptr, &(t.id)) == -1)
        return -1;

    for (int i = 0; i < 256; i++) {
        if (read_byte(&ptr, end_ptr, &(t.tile_props[i].friction)) == -1)
            return -1;
        if (read_byte(&ptr, end_ptr, &(t.tile_props[i].solid)) == -1)
            return -1;

        unsigned char image_type = 0;
        if (read_byte(&ptr, end_ptr, &image_type) == -1)
            return -1;
        uint32_t image_size = 0;
        if (read_uint32(&ptr, end_ptr, &image_size) == -1)
            return -1;

        const char* type;
        switch (image_type) {
            case 1: type = ".png"; break;
            default: type = ".bmp";
        }

        Image img = LoadImageFromMemory(type, ptr, image_size);
        t.tile_props[i].texture = LoadTextureFromImage(img);
        ptr += image_size;
        if (ptr > end_ptr)
            break;
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
        case 0: return load_tilemap(tilemap, _binary_assets_t_summer_start, _binary_assets_t_summer_end-1);
        default: return -1;
    }
}