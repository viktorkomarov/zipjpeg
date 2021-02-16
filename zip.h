#ifndef _ZIP_HEADER
#include <stdlib.h>

enum ZIP_SIGNATURE {ZIP_EMPTY = 0, ZIP_REGULAR, NO_ZIP};

typedef struct zip *ZIP;

ZIP init_zip(const char *text, size_t size);

#endif