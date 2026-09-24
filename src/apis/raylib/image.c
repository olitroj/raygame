#include "../image.h"

#include <raylib.h>

struct image_handle_s { Image img; };
struct texture_handle_s { Texture2D tex; };

void create_image(ImageHandle* handle, const unsigned char* ptr, unsigned int size) {
    handle->img = LoadImageFromMemory(".png", ptr, size);
}

void resize_image(ImageHandle* handle, unsigned int width, unsigned int height) {
    ImageResize(&(handle->img), width, height);
}

void mirror_image(ImageHandle* handle, int flip) {
    if (flip == 0) {
        ImageFlipHorizontal(&(handle->img));
        ImageFlipVertical(&(handle->img));
    } else if (flip < 0)
        ImageFlipVertical(&(handle->img));
    else
        ImageFlipHorizontal(&(handle->img));
}

void create_texture_from_image(ImageHandle* handle, TextureHandle* texture) {
    texture->tex = LoadTextureFromImage(handle->img);
    UnloadImage(handle->img);
}

void draw_texture(TextureHandle* texture, int pos_x, int pos_y) {
    DrawTexture(texture->tex, pos_x, pos_y, WHITE);
}