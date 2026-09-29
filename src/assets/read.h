#ifndef ASSETS_READ
#define ASSETS_READ

const unsigned char* string_read(const unsigned char** ptr, const unsigned char* end_ptr);
int byte_read(const unsigned char** ptr, const unsigned char* end_ptr, unsigned char* byte);
int word_read(const unsigned char** ptr, const unsigned char* end_ptr, unsigned short* word);
int int_read(const unsigned char** ptr, const unsigned char* end_ptr, unsigned int* integer);

#endif