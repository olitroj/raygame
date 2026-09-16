#ifndef BACKDROP
#define BACKDROP

#include "raylib.h"

#define MAX_BACKDROP_LAYERS 4

typedef struct backdrop_layer_s {
    Texture2D texture;
    unsigned char parallax;
    float scaled_parallax;
} BackdropLayer;

typedef struct backdrop_s {
    float origin_x, origin_y;
    unsigned char scale;
    BackdropLayer layers[MAX_BACKDROP_LAYERS];
} Backdrop;

static inline float get_backdrop_width(Backdrop* backdrop);
static inline float get_backdrop_height(Backdrop* backdrop);
int load_backdrop_from_bin(Backdrop* backdrop, int backdrop_id);
// int load_backdrop_from_file(Texture2D* backdrop, const char* file_name);
// void free_backdrop_from_file(Texture2D* level);
void scale_backdrop(Backdrop* backdrop, float level_size_x, float level_size_y, int monitor);
void draw_backdrop(Backdrop* backdrop, float cam_from_level_center_x, float cam_from_level_center_y);

#endif