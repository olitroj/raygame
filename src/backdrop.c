#include "backdrop.h"

#include "read.h"

extern const unsigned char _binary_assets_b_sunny_start[];
extern const unsigned char _binary_assets_b_sunny_end[];

static int load_backdrop(Backdrop* backdrop, const unsigned char* ptr, const unsigned char* end_ptr);

static inline float get_backdrop_width(Backdrop* backdrop) {
    return backdrop->layers[0].texture.width;
}

static inline float get_backdrop_height(Backdrop* backdrop) {
    return backdrop->layers[0].texture.height;
}

int load_backdrop_from_bin(Backdrop* backdrop, int backdrop_id) {
    if (backdrop == NULL)
        return -1;

    switch (backdrop_id) {
        case 0: return load_backdrop(backdrop, _binary_assets_b_sunny_start, _binary_assets_b_sunny_end-1);
        default: return -1;
    }
}

void scale_backdrop(Backdrop* backdrop, float level_size_x, float level_size_y, int monitor) {
    int m_width = GetMonitorWidth(monitor), m_height = GetMonitorHeight(monitor);
    int b_width = get_backdrop_width(backdrop), b_height = get_backdrop_height(backdrop);

    // Integer division rounded up
    int scale_width = (m_width + (b_width - 1)) / b_width;
    int scale_height = (m_height + (b_height - 1)) / b_height;
    int scale = (scale_width > scale_height ? scale_width : scale_height) + 1;

    backdrop->scale = scale;
    backdrop->origin_x = (level_size_x - b_width * backdrop->scale) / 2.f;
    backdrop->origin_y = (level_size_y - b_height * backdrop->scale) / 2.f;

    float max_parallax_x = (level_size_x + m_width/2.f - b_width*scale - backdrop->origin_x) / (level_size_x - level_size_x/2.f);
    for (int i = 0; i < MAX_BACKDROP_LAYERS; i++) {
        backdrop->layers[i].scaled_parallax = 1.f + (backdrop->layers[i].parallax / 255.f) * (max_parallax_x - 1.f);
    }
}

#define BACKDROP_MOVEMENT   .99f

void draw_backdrop(Backdrop* backdrop, float cam_from_level_center_x, float cam_from_level_center_y) {
    if (backdrop == NULL)
        return;
    
    for (int i = 0; i < MAX_BACKDROP_LAYERS; i++) {
        Texture2D layer = backdrop->layers[i].texture;
        unsigned char parallax = backdrop->layers[i].parallax;
        unsigned char scale = backdrop->scale;

        Vector2 position = {
            backdrop->origin_x + cam_from_level_center_x * backdrop->layers[i].scaled_parallax,//(-parallax + 255) / 255.f,
            backdrop->origin_y + cam_from_level_center_y * BACKDROP_MOVEMENT//(-parallax + 255) / 255.f
        };
        DrawTextureEx(layer, position, 0.f, scale, WHITE);
    }
}


static int load_backdrop(Backdrop* backdrop, const unsigned char* ptr, const unsigned char* end_ptr) {
    if (backdrop == NULL)
        return -1;

    unsigned char byte = 0;
    if (read_byte(&ptr, end_ptr, &byte) == -1 || byte != 0xA0)
        return -1;
    if (read_byte(&ptr, end_ptr, &byte) == -1 || byte != 0x45)
        return -1;

    for (int i = 0; i < MAX_BACKDROP_LAYERS; i++) {
        if (read_byte(&ptr, end_ptr, &(backdrop->layers[i].parallax)) == -1)
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

        Texture2D tex = LoadTextureFromImage(LoadImageFromMemory(type, ptr, image_size));
        if (i != 0 && (backdrop->layers[i-1].texture.width != tex.width || backdrop->layers[i-1].texture.height != tex.height))
            return -1;
        backdrop->layers[i].texture = tex;

        ptr += image_size;
        if (ptr > end_ptr)
            break;
    }

    return 0;
}