#include "util.h"

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

int read_integer_from_ascii(const unsigned char** ptr, const unsigned char* end_ptr, int* value) {
    while (*ptr <= end_ptr) {
        if (**ptr == '\0') {
            (*ptr)++;
            return 0;
        } else if (*ptr == end_ptr)
            break;
        int digit = **ptr - 48; // ASCII offset
        if (digit > 9 || digit < 0)
            break;
        *value = *value * 10 + digit;
        (*ptr)++;
    }
    return -1;
}

int read_byte(const unsigned char** ptr, const unsigned char* end_ptr, unsigned char* byte) {
    if (*ptr > end_ptr)
        return -1;
    *byte = *(*ptr)++;
    return 0;
}

int read_word(const unsigned char** ptr, const unsigned char* end_ptr, uint16_t* word) {
    if (*ptr + 1 > end_ptr)
        return -1;
    *word = *(uint16_t*)(*ptr);
    *ptr += 2;
    return 0;
}

int read_int(const unsigned char** ptr, const unsigned char* end_ptr, uint32_t* integer) {
    if (*ptr + 3 > end_ptr)
        return -1;
    *integer = *(uint32_t*)(*ptr);
    *ptr += 4;
    return 0;
}