#include "../image.h"

#include <raylib.h>

struct image_handle_s { Image img; };
struct texture_handle_s { Texture2D tex; };

int create_image(ImageHandle* handle, const unsigned char* ptr, unsigned int size) {
    if (handle == NULL)
        return -1;
    handle->img = LoadImageFromMemory(".png", ptr, size);
}

int resize_image(ImageHandle* handle, unsigned int width, unsigned int height) {
    if (handle == NULL)
        return -1;
    ImageResize(&(handle->img), width, height);
}

int mirror_image(ImageHandle* handle, int flip) {
    if (handle == NULL)
        return -1;
    if (flip == 0) {
        ImageFlipHorizontal(&(handle->img));
        ImageFlipVertical(&(handle->img));
    } else if (flip < 0)
        ImageFlipVertical(&(handle->img));
    else
        ImageFlipHorizontal(&(handle->img));
}

int create_texture_from_image(ImageHandle* img_handle, TextureHandle* tex_handle) {
    if (!img_handle || !tex_handle)
        return -1;
    tex_handle->tex = LoadTextureFromImage(img_handle->img);
    UnloadImage(img_handle->img);
}

int get_size_texture(TextureHandle* handle, unsigned int* width, unsigned int* height) {
    if (!handle || !width || !height)
        return -1;
    *width = handle->tex.width;
    *height = handle->tex.height;
}

int draw_texture(TextureHandle* handle, int pos_x, int pos_y) {
    if (!handle)
        return -1;
    DrawTexture(handle->tex, pos_x, pos_y, WHITE);
}