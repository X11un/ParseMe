#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "crypto.h"
#include "storage.h"

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

        char *lineStart = buffer;

        // Parse chunk line by line
        while (lineStart != NULL && *lineStart != '\0') {
            char *lineEnd = lineStart;
            while (*lineEnd != '\n' && *lineEnd != '\0') {
                lineEnd++;
            }

            char *nextLine = NULL;
            if (*lineEnd == '\n') {
                nextLine = lineEnd + 1;
                *lineEnd = '\0';
            }

            char *colonPtr = lineStart;
            while (*colonPtr != ':' && *colonPtr != '\0') {
                colonPtr++;
            }

            if (*colonPtr == ':') {
                *colonPtr = '\0';
                char *email = colonPtr + 1;
                char hashHex[65];
                computeSha256(email, hashHex);
                saveHashDisk(hashHex, "Success");
            }
            lineStart = nextLine;
        }

        // Handle leftover data at chunk boundary
        if (lineStart && *lineStart != '\0') {
            leftOver = strlen(lineStart);
            memmove(buffer, lineStart, leftOver);
        } else {
            leftOver = 0;
        }
    }

    close(fdIn);
    printf("Processing complete! Check your folders.\n");
    return 0;
}