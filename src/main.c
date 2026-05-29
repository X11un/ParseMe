#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>   
#include <stdlib.h>
#include "parser.h"


int main(int argc, char *argv[]) {
    if (argc < 2 ){
        printf("Usage: ./ParseMe <filename>\n");
        return 1;
     }
    
    // FILE I/O: Open the configuration file in read-only mode
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        printf("Error: File not found");
        return 1;
    }

    // MEMORY: Allocate a 4KB buffer (aligned with Linux page size for performance)
    char *buffer = malloc(4096  * sizeof(char));
    if (buffer == NULL) {
        printf("Error: Memory allocation failed\n");
        close(fd);
        return 1;
    }

    // STREAMING: Read the file content into the buffer
    int bytesRead = read(fd, buffer, 4095);
    if (bytesRead > 0) {
        buffer[bytesRead] = '\0';
        parseBuffer(buffer);
}

    // CLEANUP: Safely release system resources and memory before exiting
    close(fd);
    free(buffer);
    return 0;
}