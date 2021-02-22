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

    zip *z = init_zip(text, buff.st_size);
    if (z) {
        if (is_zip(z)) {
            printf("zip was found...\n");
            print_files(z);
        } else {
            printf("zip wasn't found\n");
        }
        destroy(z);
        return EXIT_SUCCESS;
    }
    perror("can't build zip");
    return EXIT_FAILURE;
}