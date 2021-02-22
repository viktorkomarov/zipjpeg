#ifndef _ZIP_HEADER_
#include <stdlib.h>
#include <stdbool.h>

typedef struct zip zip;

zip *init_zip(const char *text, size_t size);

bool is_zip(zip *z);

void destroy(zip *z);

void print_files(zip *z);

#endif