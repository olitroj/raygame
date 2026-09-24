#ifndef APIS_IMAGE
#define APIS_IMAGE

typedef struct image_handle_s ImageHandle;
typedef struct texture_handle_s TextureHandle;

void create_image(ImageHandle* handle, const unsigned char* ptr, unsigned int size);
void resize_image(ImageHandle* handle, unsigned int width, unsigned int height);
void mirror_image(ImageHandle* handle, int flip);
void create_texture_from_image(ImageHandle* handle, TextureHandle* texture);
void draw_texture(TextureHandle* texture, int pos_x, int pos_y);

#endif