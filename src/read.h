#ifndef READ
#define READ

const unsigned char* read_string(const unsigned char** ptr, const unsigned char* end_ptr);
int read_byte(const unsigned char** ptr, const unsigned char* end_ptr, unsigned char* byte);
int read_word(const unsigned char** ptr, const unsigned char* end_ptr, unsigned short* word);
int read_int(const unsigned char** ptr, const unsigned char* end_ptr, unsigned int* integer);

#endif