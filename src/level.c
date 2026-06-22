#include "raylib.h"

#include "defs.h"

extern const unsigned char _binary_assets_levels_level0_level_start[];
extern const unsigned char _binary_assets_levels_level0_level_end[];

typedef struct level_s {
    char* name;
    unsigned int width, height;
    unsigned int start_x, start_y;
    float gravity;
    unsigned char* tiles;

    unsigned char* bytes;
} Level;

static unsigned char* get_string(unsigned char** ptr, unsigned char* end_ptr) {
    unsigned char* start = *ptr;
    while (*ptr <= end_ptr) {
        if (**ptr == '\0') {
            (*ptr)++;
            return start;
        } else if (*ptr == end_ptr)
            break;
        (*ptr)++;
    }
    return NULL;
}

static int get_integer(unsigned char** ptr, unsigned char* end_ptr, int* value) {
    while (*ptr <= end_ptr) {
        if (**ptr == '\0') {
            (*ptr)++;
            return 0;
        } else if (*ptr == end_ptr)
            break;
        int digit = **ptr - 48; // ASCII offset
        if (digit > 9 || digit < 0)
            break;
        *value = *value * 10 + digit;
        (*ptr)++;
    }
    return -1;
}

static int load_level(Level* level, unsigned char* ptr, unsigned char* end_ptr) {
    Level l = {0};
    l.bytes = ptr;

    if (end_ptr <= ptr || !(*ptr == 0xA0 && *(ptr+1) == 0x43))
        return -1;

    ptr += 2;

    if ((l.name = get_string(&ptr, end_ptr)) == NULL)
        return -1;
    if (get_integer(&ptr, end_ptr, &(l.width)) == -1)
        return -1;
    if (get_integer(&ptr, end_ptr, &(l.height)) == -1)
        return -1;
    if (get_integer(&ptr, end_ptr, &(l.start_x)) == -1)
        return -1;
    if (get_integer(&ptr, end_ptr, &(l.start_y)) == -1)
        return -1;
        
    int gravity = 0;
    if (get_integer(&ptr, end_ptr, &(gravity)) == -1)
        return -1;
    l.gravity = (float)gravity;

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
    UnloadFileData(level->bytes);
}

int load_level_from_bin(Level* level, int level_no) {
    if (level == NULL)
        return -1;

    switch (level_no) {
        case 0: return load_level(level, _binary_assets_levels_level0_level_start, _binary_assets_levels_level0_level_end-1);
        default: return -1;
    }
}

void draw_level(Level* level) {
    for (int row = 0; row < level->height; row++) {
        for (int col = 0; col < level->width; col++) {
            unsigned char tile_id = level->tiles[col + row*level->width];
            Color c;
            switch (tile_id) {
                case '1': c = RED; break;
                case '2': c = GREEN; break;
                case '3': c = BLUE; break;
                case '4': c = YELLOW; break;
                case '5': c = PINK; break;
                default: continue;
            }

            DrawRectangle(col*TILE_SIZE, row*TILE_SIZE, TILE_SIZE, TILE_SIZE, c);
        }
    }
}