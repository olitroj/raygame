#include "tilemap.h"

#include "read.h"
#include "extern.h"

static int load_tilemap(Tilemap* tilemap, unsigned int tile_size, const unsigned char* ptr, const unsigned char* end_ptr);

static int load_tilemap(Tilemap* tilemap, unsigned int tile_size, const unsigned char* ptr, const unsigned char* end_ptr) {
    if (tilemap == NULL)
        return -1;

    Tilemap t = {0};

    unsigned char byte = 0;
    if (read_byte(&ptr, end_ptr, &byte) == -1 || byte != 0xA0)
        return -1;
    if (read_byte(&ptr, end_ptr, &byte) == -1 || byte != 0x44)
        return -1;

    for (int i = 0; i < 256; i++) {
        if (read_byte(&ptr, end_ptr, &byte) == -1)
            return -1;
        t.tile_props[i].friction = (float)byte;
        if (read_byte(&ptr, end_ptr, &(t.tile_props[i].solid)) == -1)
            return -1;

        unsigned char image_type = 0;
        if (read_byte(&ptr, end_ptr, &image_type) == -1)
            return -1;
        unsigned int image_size = 0;
        if (read_int(&ptr, end_ptr, &image_size) == -1)
            return -1;

        const char* type;
        switch (image_type) {
            case 1: type = ".png"; break;
            default: type = ".bmp";
        }

        ImageHandle img;
        create_image(&img, ptr, image_size);
        resize_image(&img, tile_size, tile_size);

        TextureHandle tex;
        create_texture_from_image(&img, &tex);
        t.tile_props[i].texture = tex;
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

int load_tilemap_from_bin(Tilemap* tilemap, int tilemap_id, unsigned int tile_size) {
    if (tilemap == NULL)
        return -1;

    switch (tilemap_id) {
        case 0: return load_tilemap(tilemap, tile_size, _binary_assets_t_summer_start, _binary_assets_t_summer_end-1);
        default: return -1;
    }
}