#include <stdio.h>
#include <parser.h>


void parseBuffer(char *buffer) {

    char *startLine = buffer;

    // Loop : Line for Line
    while (startLine != NULL && *startLine != '\0') {
            // Search for the current line
            char *endLine = startLine;
            while (*endLine != '\n' && *endLine != '\0') {
                endLine++;
            }

            // Isolate the line + prepare the next one
            char *nextLine = NULL;
            if (*endLine == '\n') {
                nextLine = endLine + 1;
                *endLine = '\0';
            } else {
                nextLine = NULL;  // End file 
            }

            // Loop : Key | Value
            char *ptrSpace = startLine;
            while (*ptrSpace != ' ' && *ptrSpace != '\0') {
                ptrSpace++;
            } if (*ptrSpace == ' ') {
                *ptrSpace = '\0';  // Cut of space
                char *key = startLine;
                char *value = ptrSpace + 1;
                printf("Key: %s | Value: %s\n", key, value);
            }

            startLine = nextLine;   // Next line ..
        }
}