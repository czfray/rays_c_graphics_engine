#include <rcge/rcge_io.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* read_file_all(char* path, int buffer_size)
{
    FILE* file = fopen(path, "r");
    if (file == NULL) {printf("[RCGE IO] File \"%s\" failed to open: fopen failed.\n", path); return NULL;}

    char* result = (char*) malloc(1);
    int resultLen = 0;
    if (result == NULL) {printf("[RCGE IO] File \"%s\" failed to load: malloc failed.\n", path); return NULL;}

    char buffer[buffer_size];
    while (fgets(buffer, sizeof(buffer), file)) 
    {
        int bufferLen = strlen(buffer);
        result = (char*) realloc(result, resultLen + bufferLen + 1);
        if (result == NULL) 
        {
            printf("[RCGE IO] File \"%s\" failed to load: realloc failed.\n", path);
            free(result);
            return NULL;
        }
        strcpy(result + resultLen, buffer);
        resultLen += bufferLen;
    }
    printf("[RCGE IO] File \"%s\" all lines read.\n", path);
    fclose(file);
    return result;
}