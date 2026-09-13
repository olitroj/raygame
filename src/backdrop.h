#ifndef BACKDROP
#define BACKDROP

#include "raylib.h"

#include "sprite.h"

// typedef struct backdrop_s {
//     Vector2 position;
//     Texture2D texture;
// } Backdrop;

int load_backdrop(Texture2D* backdrop, const unsigned char* ptr, const unsigned char* end_ptr);
// int load_backdrop_from_file(Texture2D* backdrop, const char* file_name);
// void free_backdrop_from_file(Texture2D* level);
int load_backdrop_from_bin(Texture2D* backdrop, int backdrop_id);
void draw_backdrop(Texture2D* backdrop, Vector2 level_center, Vector2 cam_pos);

#endif