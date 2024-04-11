#ifndef READFILE_H
#define READFILE_H

// Function to open a file. Returns 0 on success, -1 on failure.
int open_file(const char* filename);

// Function to read an integer from the file. Returns 0 on success, -1 on EOF.
int read_int(int* value);

// Function to read a string from the file. Returns 0 on success, -1 on EOF.
int read_string(char* string);

// Function to close the file.
void close_file();

#endif // READFILE_H
