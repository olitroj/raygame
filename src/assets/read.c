#include "read.h"

const unsigned char* string_read(const unsigned char** ptr, const unsigned char* end_ptr) {
    const unsigned char* start = *ptr;
    while (*ptr <= end_ptr) {
        if (**ptr == '\0') {
            (*ptr)++;
            return start;
        } else if (*ptr == end_ptr)
            break;
        (*ptr)++;
    }
    return NULL;
}

int byte_read(const unsigned char** ptr, const unsigned char* end_ptr, unsigned char* byte) {
    if (*ptr > end_ptr)
        return -1;
    *byte = *(*ptr)++;
    return 0;
}

int word_read(const unsigned char** ptr, const unsigned char* end_ptr, unsigned short* word) {
    if (*ptr + 1 > end_ptr)
        return -1;
    *word = *(unsigned short*)(*ptr);
    *ptr += 2;
    return 0;
}

int int_read(const unsigned char** ptr, const unsigned char* end_ptr, unsigned int* integer) {
    if (*ptr + 3 > end_ptr)
        return -1;
    *integer = *(unsigned int*)(*ptr);
    *ptr += 4;
    return 0;
}