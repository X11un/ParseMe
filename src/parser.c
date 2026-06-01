#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "crypto.h"
#include "storage.h"

int parseBuffer(char *buffer) {
    char *lineStart = buffer;

    // Loop : Line for Line
    while (lineStart != NULL && *lineStart != '\0') {
        char *lineEnd = lineStart;
        while (*lineEnd != '\n' && *lineEnd != '\0') {
            lineEnd++;
        }

        char *nextLine = NULL;
        if (*lineEnd == '\n') {
            nextLine = lineEnd + 1;
            *lineEnd = '\0';
        } else {
            break;
        }

        // Find separator and process email
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

    // LeftOver at the end of the chunk
    if (lineStart && *lineStart != '\0') {
        int leftOver = strlen(lineStart);
        memmove(buffer, lineStart, leftOver);
        return leftOver;
    } 
    
    return 0;
}