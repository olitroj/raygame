#ifndef LEVEL
#define LEVEL

#include "tilemap.h"

typedef struct level_s {
    const char* name;
    unsigned int width, height;
    unsigned int start_x, start_y;
    float gravity;
    unsigned char tilemap_id;
    const unsigned char* tiles;

    const unsigned char* bytes;
} Level;

int load_level(Level* level, const unsigned char* ptr, const unsigned char* end_ptr);
int load_level_from_file(Level* level, const char* file_name);
void free_level_from_file(Level* level);
int load_level_from_bin(Level* level, int level_no);
void draw_level(Level* level, Tilemap* tilemap);

#endif