#ifndef APIS_IMAGE
#define APIS_IMAGE

typedef void* ImageHandle;
typedef void* TextureHandle;

void create_image(ImageHandle handle, unsigned char* ptr, unsigned int size);
void resize_image(ImageHandle handle, unsigned int width, unsigned int height);
void mirror_image(ImageHandle handle, int flip);
void create_texture_from_image(ImageHandle handle, TextureHandle texture);

#endif