#ifndef _ZIP_HEADER_
#include <stdlib.h>
#include <stdbool.h>

enum ZIP_SIGNATURE {ZIP_EMPTY = 0, ZIP_REGULAR, NO_ZIP};

typedef struct zip ZIP;

ZIP *init_zip(const char *text, size_t size);

enum ZIP_SIGNATURE sign(ZIP *z);

void destroy(ZIP *z);

#endif