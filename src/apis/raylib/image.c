#include <raylib.h>

#include "../image.h"

#define DEREF(var, type) (*(type *)var)

void create_image(ImageHandle handle, unsigned char* ptr, unsigned int size) {
    DEREF(handle, Image) = LoadImageFromMemory(".png", ptr, size);
}

void resize_image(ImageHandle handle, unsigned int width, unsigned int height) {
    ImageResize(handle, width, height);
}

void mirror_image(ImageHandle handle, int flip) {
    if (flip == 0) {
        ImageFlipHorizontal(handle);
        ImageFlipVertical(handle);
    } else if (flip < 0)
        ImageFlipVertical(handle);
    else
        ImageFlipHorizontal(handle);
}

void create_texture_from_image(ImageHandle handle, TextureHandle texture) {
    DEREF(texture, Texture2D) = LoadTextureFromImage(DEREF(handle, Image));
    UnloadImage(DEREF(handle, Image));
}