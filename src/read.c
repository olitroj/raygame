#include "read.h"

const unsigned char* read_string(const unsigned char** ptr, const unsigned char* end_ptr) {
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

int read_byte(const unsigned char** ptr, const unsigned char* end_ptr, unsigned char* byte) {
    if (*ptr > end_ptr)
        return -1;
    *byte = *(*ptr)++;
    return 0;
}

int read_word(const unsigned char** ptr, const unsigned char* end_ptr, unsigned short* word) {
    if (*ptr + 1 > end_ptr)
        return -1;
    *word = *(unsigned short*)(*ptr);
    *ptr += 2;
    return 0;
}

int read_int(const unsigned char** ptr, const unsigned char* end_ptr, unsigned int* integer) {
    if (*ptr + 3 > end_ptr)
        return -1;
    *integer = *(unsigned int*)(*ptr);
    *ptr += 4;
    return 0;
}