#ifndef FILEIO_H
#define FILEIO_H
#include <stdio.h>

typedef unsigned char BYTE;

FILE* openFile(const char* fileName, const char* fileMode);
int readFile(FILE* filePtr, BYTE* data, int bytesToRead);
int writeFile(FILE* filePtr, BYTE* data, int bytesToWrite);

#endif // !FILEIO_H

