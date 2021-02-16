#include <stdio.h>
#include <stdlib.h>
#include "zip.h"

#define SIGNATURE_LEN 4

struct zip
{
    enum ZIP_SIGNATURE signature;
    const char *text;
    size_t offset;
    size_t size_text;
};

// macro ?
int step(int current, int next) {
    if (current == next - 1) {
        return next;
    }

    return 0;
}

int empty_sign_step(int current, unsigned char byte)
{
    switch (byte)
    {
    case 0x50:
        return step(current, 1);
    case 0x4b:
        return step(current, 2);
    case 0x05:
        return step(current, 3);
    case 0x06:
        return step(current, 4);
    default:
        return 0;
    }
}

int regular_sign_step(int current, unsigned char byte)
{
    switch (byte)
    {
    case 0x50:
        return step(current, 1);
    case 0x4b:
        return step(current, 2);
    case 0x03:
        return step(current, 3);
    case 0x04:
        return step(current, 4);
    default:
        return 0;
    }
}


size_t analyze_signature(ZIP z)
{
    int signatures_match[2] = {0,0};
    int match = 0;

    z->signature = NO_ZIP;
    size_t offset = 0;
    for(;offset < z->size_text; offset++)
    {
        signatures_match[ZIP_EMPTY] = empty_sign_step(signatures_match[ZIP_EMPTY], z->text[offset]);
        signatures_match[ZIP_REGULAR] = regular_sign_step(signatures_match[ZIP_REGULAR], z->text[offset]);

        if (signatures_match[ZIP_EMPTY] == SIGNATURE_LEN) {
            z->signature = ZIP_EMPTY;
            break;
        } 

        if (signatures_match[ZIP_REGULAR] == SIGNATURE_LEN) {
            z->signature = ZIP_REGULAR;
            break;
        }
    }
    
    if (z->signature != NO_ZIP) {
        return offset - SIGNATURE_LEN;
    }

    return 0;
}

ZIP init_zip(const char *text, size_t size)
{  
    ZIP z = malloc(sizeof(struct zip));
    if(!z) {
        return z;
    }

    z->text = text;
    z->size_text = size; 
    z->offset = analyze_signature(z);
    return z;
}
