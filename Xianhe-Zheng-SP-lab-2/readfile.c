#include "readfile.h"
#include <stdio.h>

static FILE* file = NULL;

int open_file(const char* filename) {
    file = fopen(filename, "r");
    if (file == NULL) {
        return -1; // File opening failed
    }
    return 0; // Success
}

int read_int(int* value) {
    if (fscanf(file, "%d", value) == 1) {
        return 0; // Success
    }
    return -1; // EOF or error
}

int read_string(char* string) {
    if (fscanf(file, "%63s", string) == 1) { // Reads up to 63 characters + '\0'
        return 0; // Success
    }
    return -1; // EOF or error
}

void close_file() {
    if (file != NULL) {
        fclose(file);
        file = NULL;
    }
}
