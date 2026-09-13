#include "backdrop.h"

#include "read.h"
#include "globals.h"

extern const unsigned char _binary_assets_b_sunny_start[];
extern const unsigned char _binary_assets_b_sunny_end[];

int load_backdrop(Texture2D* backdrop, const unsigned char* ptr, const unsigned char* end_ptr) {
    if (backdrop == NULL)
        return -1;

    unsigned char byte = 0;
    int image_size = 0;
    if (read_byte(&ptr, end_ptr, &byte) == -1 || byte != 0xA0)
        return -1;
    if (read_byte(&ptr, end_ptr, &byte) == -1 || byte != 0x45)
        return -1;
    if (read_int(&ptr, end_ptr, &image_size) == -1)
        return -1;

    Image img = LoadImageFromMemory(".png", ptr, image_size);
    *backdrop = LoadTextureFromImage(img);
    return 0;
}

int load_backdrop_from_bin(Texture2D* backdrop, int backdrop_id) {
    if (backdrop == NULL)
        return -1;

    switch (backdrop_id) {
        case 0: return load_backdrop(backdrop, _binary_assets_b_sunny_start, _binary_assets_b_sunny_end-1);
        default: return -1;
    }
}

#define BACKDROP_SCALE      5
#define BACKDROP_MOVEMENT   0.99f

void draw_backdrop(Texture2D* backdrop, Vector2 level_center, Vector2 cam_pos) {
    if (backdrop == NULL)
        return;
    
    // 1. Centers the backdrop to the center of the level
    // 2. Adds player movement parallax
    Vector2 position = {
        (level_center.x - backdrop->width * BACKDROP_SCALE / 2.f) + (cam_pos.x - level_center.x) * BACKDROP_MOVEMENT,
        (level_center.y - backdrop->height * BACKDROP_SCALE / 2.f) + (cam_pos.y - level_center.y) * BACKDROP_MOVEMENT
    };
    DrawTextureEx(*backdrop, position, 0.f, BACKDROP_SCALE, WHITE);
}