#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include "zip.h"

int main(int argc, char **argv)
{
    if (argc != 2) {
        printf("usage: %s zipjpeg\n", argv[0]);
        return EXIT_FAILURE;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("can't open file");
        return EXIT_FAILURE;
    }
    
    int code;
    struct stat buff;
    if ((code = fstat(fd, &buff)) == -1) {
        perror("can't stat file");
        return EXIT_FAILURE;
    }

    char *text = mmap(NULL, buff.st_size, PROT_READ, MAP_SHARED, fd, 0);
    if(text == MAP_FAILED) {
        perror("can't mmap file");
        return EXIT_FAILURE;
    }

    ZIP *zip = init_zip(text, buff.st_size);
    if (zip) {
        enum ZIP_SIGNATURE signature = sign(zip);
        switch (signature)
        {
        case ZIP_EMPTY:
            printf("empty zip\n");
            break;
        case ZIP_REGULAR:
            printf("zip regular\n");
            break;
        case NO_ZIP:
            printf("no zip\n");
            break;
        }
        destroy(zip);
        return EXIT_SUCCESS;
    }
    perror("can't build zip");
    return EXIT_FAILURE;
}