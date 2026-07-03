#ifndef UTIL
#define UTIL

#include <stdint.h>

const unsigned char* read_string(const unsigned char** ptr, const unsigned char* end_ptr);
int read_integer_from_ascii(const unsigned char** ptr, const unsigned char* end_ptr, int* value);
int read_byte(const unsigned char** ptr, const unsigned char* end_ptr, unsigned char* byte);
int read_uint32(const unsigned char** ptr, const unsigned char* end_ptr, uint32_t* integer);

#endif