#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "parser.h"

int main(int argc, char **argv) {

    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Open input file
    int fdIn = open(argv[1], O_RDONLY);
    if (fdIn < 0) {
        printf("Error: Cannot open file %s\n", argv[1]);
        return 1;
    }

    char buffer[4096];
    int leftOver = 0;
    int bytesRead;

    // Stream file in 4KB chunks
    while ((bytesRead = read(fdIn, buffer + leftOver, 4095 - leftOver)) > 0) {
        int totalBytes = bytesRead + leftOver;
        buffer[totalBytes] = '\0';

        leftOver = parseBuffer(buffer);
    }

    close(fdIn);
    printf("Processing complete! Check your folders.\n");
    return 0;
}