#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include "storage.h"

int saveHashDisk(const char *hashHex, const char *dataWrite) {

    // Create parent directory
    if (mkdir("Hash256", 0755) == -1 && errno != EEXIST) {
        printf("Error: Cannot create parent directory Hash256\n");
        return -1;
    }
    
    // Extract first 2 characters for shard folder
    char folderName[3];
    folderName[0] = hashHex[0];
    folderName[1] = hashHex[1];
    folderName[2] = '\0';

    // Build and create sub-directory path
    char subFolderPath[20];
    snprintf(subFolderPath, sizeof(subFolderPath), "Hash256/%s", folderName);

    if (mkdir(subFolderPath, 0755) == -1 && errno != EEXIST) {
        printf("Error: Cannot create sub-directory %s\n", subFolderPath);
        return -1;
    }

    // Extract remaining hash for file name
    const char *fileName = hashHex + 2;

    // Build final file path (e.g., Hash256/87/924606...)
    char filePath[100];
    snprintf(filePath, sizeof(filePath), "%s/%s", subFolderPath, fileName);

    // Create file and write data
    int fd = open(filePath, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0) {
        printf("Error: Cannot create file %s\n", filePath);
        return -1;
    }

    write(fd, dataWrite, strlen(dataWrite));
    close(fd);
    return 0;
}