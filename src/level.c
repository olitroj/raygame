#include "level.h"

#include "raylib.h"
#include "defs.h"
#include "read.h"

extern const unsigned char _binary_assets_l_level0_start[];
extern const unsigned char _binary_assets_l_level0_end[];

int load_level(Level* level, const unsigned char* ptr, const unsigned char* end_ptr) {
    Level l = {0};
    l.bytes = ptr;

    unsigned char byte = 0;
    if (read_byte(&ptr, end_ptr, &byte) == -1 || byte != 0xA0)
        return -1;
    if (read_byte(&ptr, end_ptr, &byte) == -1 || byte != 0x43)
        return -1;

    if (read_byte(&ptr, end_ptr, &(l.level_id)) == -1)
        return -1;
    if (read_byte(&ptr, end_ptr, &(l.tilemap_id)) == -1)
        return -1;

    if ((l.name = read_string(&ptr, end_ptr)) == NULL)
        return -1;
    if (read_word(&ptr, end_ptr, &(l.width)) == -1)
        return -1;
    if (read_word(&ptr, end_ptr, &(l.height)) == -1)
        return -1;
    if (read_word(&ptr, end_ptr, &(l.start_x)) == -1)
        return -1;
    if (read_word(&ptr, end_ptr, &(l.start_y)) == -1)
        return -1;
        
    uint16_t gravity = 0;
    if (read_word(&ptr, end_ptr, &(gravity)) == -1)
        return -1;
    l.gravity = (float)gravity;

    if (read_byte(&ptr, end_ptr, &(l.tile_size)) == -1)
        return -1;

    int remaining_bytes = end_ptr + 1 - ptr;
    // If there are less remaining bytes than there should be (width*height), fail since drawing would cause tile buffer overflow
    if (l.width * l.height > remaining_bytes)
        return -1;

    l.tiles = ptr;

    *level = l;
    return 0;
}

int load_level_from_file(Level* level, const char* file_name) {
    if (level == NULL || file_name == NULL)
        return -1;

    int byte_cnt;
    unsigned char* ptr = LoadFileData(file_name, &byte_cnt);
    if (ptr == NULL || byte_cnt == 0)
        return -1;

    return load_level(level, ptr, ptr + byte_cnt - 1);
}

void free_level_from_file(Level* level) {
    UnloadFileData((unsigned char*)level->bytes);
}

int load_level_from_bin(Level* level, int level_no) {
    if (level == NULL)
        return -1;

    switch (level_no) {
        case 0: return load_level(level, _binary_assets_l_level0_start, _binary_assets_l_level0_end-1);
        default: return -1;
    }
}

void draw_level(Level* level, Tilemap* tilemap) {
    if (level == NULL || tilemap == NULL)
        return;

    for (int row = 0; row < level->height; row++) {
        for (int col = 0; col < level->width; col++) {
            unsigned char tile_id = level->tiles[col + row*level->width];
            if (tile_id == TILE_AIR)
                continue;

            Texture2D texture = tilemap->tile_props[tile_id].texture;
            DrawTextureEx(texture, (Vector2){col*level->tile_size, row*level->tile_size}, 0.0f, (float)level->tile_size / (float)texture.width, WHITE);
        }
    }
}