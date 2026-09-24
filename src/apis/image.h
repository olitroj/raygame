#ifndef APIS_IMAGE
#define APIS_IMAGE

typedef struct image_handle_s ImageHandle;
typedef struct texture_handle_s TextureHandle;

int create_image(ImageHandle* handle, const unsigned char* ptr, unsigned int size);
int resize_image(ImageHandle* handle, unsigned int width, unsigned int height);
int mirror_image(ImageHandle* handle, int flip);

int create_texture_from_image(ImageHandle* img_handle, TextureHandle* tex_handle);
int get_size_texture(TextureHandle* handle, unsigned int* width, unsigned int* height);
int draw_texture(TextureHandle* handle, int pos_x, int pos_y);

#endif