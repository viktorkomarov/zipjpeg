#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>

int main()
{
    int fd = open("files/zipjpeg.jpg", O_RDONLY);
    if (fd == -1) {
        return EXIT_FAILURE;
    }

    
}