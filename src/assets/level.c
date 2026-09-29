#include "level.h"

#include "read.h"
#include "extern.h"

#define TILE_AIR    255

static int load_level(Level* level, const unsigned char* ptr, const unsigned char* end_ptr);

static int load_level(Level* level, const unsigned char* ptr, const unsigned char* end_ptr) {
    if (level == NULL)
        return -1;
        
    Level l = {0};
    l.bytes = ptr;

    unsigned char byte = 0;
    if (byte_read(&ptr, end_ptr, &byte) == -1 || byte != 0xA0)
        return -1;
    if (byte_read(&ptr, end_ptr, &byte) == -1 || byte != 0x43)
        return -1;

    if ((l.name = string_read(&ptr, end_ptr)) == NULL)
        return -1;
    if (word_read(&ptr, end_ptr, &(l.start_x)) == -1)
        return -1;
    if (word_read(&ptr, end_ptr, &(l.start_y)) == -1)
        return -1;
        
    unsigned short gravity = 0;
    if (word_read(&ptr, end_ptr, &(gravity)) == -1)
        return -1;
    l.gravity = (float)gravity;

    unsigned char tilemap_id;
    if (byte_read(&ptr, end_ptr, &(tilemap_id)) == -1)
        return -1;
    if (byte_read(&ptr, end_ptr, &(l.tile_size)) == -1)
        return -1;

    if (word_read(&ptr, end_ptr, &(l.width)) == -1)
        return -1;
    if (word_read(&ptr, end_ptr, &(l.height)) == -1)
        return -1;

    int remaining_bytes = end_ptr + 1 - ptr;
    // If there are less remaining bytes than there should be (width*height), fail since drawing would cause tile buffer overflow
    if (l.width * l.height > remaining_bytes)
        return -1;

    l.tiles = ptr;

    if (load_from_bin_tilemap(&(l.tilemap), tilemap_id, l.tile_size))
        return -1;

    *level = l;
    return 0;
}

int load_from_bin_level(Level* level, int level_no) {
    if (level == NULL)
        return -1;

    switch (level_no) {
        case 0: return load_level(level, _binary_assets_l_level0_start, _binary_assets_l_level0_end-1);
        default: return -1;
    }
}

void draw_level(Level* level) {
    if (level == NULL)
        return;

    for (int row = 0; row < level->height; row++) {
        for (int col = 0; col < level->width; col++) {
            unsigned char tile_id = level->tiles[col + row*level->width];
            if (tile_id == TILE_AIR)
                continue;

            TextureHandle texture = level->tilemap.tile_props[tile_id].texture;
            draw_texture(&texture, col*level->tile_size, row*level->tile_size);
        }
    }
}