#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "zip.h"

#define SIGNATURE_LEN 4
#define SIGNATURE 0x504b0304
#define MAX_FILES 1024

struct zip
{
    const char *text;
    size_t size_text;

    size_t offsets[MAX_FILES];
    size_t count_files;
};

static int32_t read32(const char *bytes) {
    int32_t num = 0;
    num |= (int)bytes[0] << 24;
    num |= (int)bytes[1] << 16;
    num |= (int)bytes[2] << 8;
    num |= (int)bytes[3];

    return num;
}

static void mark_possible_files(zip *z)
{
    size_t i = 0;
    while (i + 4 < z->size_text) 
    {
        int32_t signature = read32(&z->text[i]);
        if (signature == SIGNATURE) {
            z->offsets[z->count_files++] = i;
            i += 4;
        } else {
            i++;
        }
    }
}

zip *init_zip(const char *text, size_t size)
{  
    zip *z = malloc(sizeof(struct zip));
    if(!z) {
        return z;
    }

    z->text = text;
    z->size_text = size; 
    mark_possible_files(z);
    return z;
}

void destroy(zip *z)
{
    free(z);
}

bool is_zip(zip *z)
{
    return z->count_files != 0;
}

void print_files(zip *z)
{
    for(size_t i = 0; i < z->count_files; i++)
    {
        size_t offset = z->offsets[i] + 30;
        printf("File: %s\n", &z->text[offset]);
    }
}