#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "fileio.h"


/// <summary>
/// This function will open a file with the specified mode
/// </summary>
/// <param name="fileName">name of the file</param>
/// <param name="fileMode">mode to open the file in (e.g., "r", "w", "rb", "wb").</param>
/// <returns>pointer to the open file</returns>
FILE* openFile(const char* fileName, const char* fileMode)
{
	FILE* filePtr = NULL;
	int iErr = EXIT_SUCCESS;

	filePtr = fopen(fileName, fileMode);
	//Try to open
	if (filePtr != NULL)
	{
		printf("File %s was openned successfully, mode %s\n", fileName, fileMode);
		return filePtr;
	}
	else // failed to open file
	{
		iErr = errno;
		printf("Error accessing the file %s: %s\n", fileName, strerror(iErr));
		return NULL;
	}
}

/// <summary>
/// This function will read a number of bytes from a file, the file will be read into the data buffer
/// </summary>
/// <param name="filePtr">pointer to an open file</param>
/// <param name="data">buffer</param>
/// <param name="bytesToRead">number of bytes to be read</param>
/// <returns>error code</returns>
int readFile(FILE* filePtr, BYTE* data, int bytesToRead)
{
	// Ensure filePtr and data are not NULL
	if (!filePtr || !data) {
		return -1; 
	}

	//read the bytes from the file, we dont allocate to heap and instead put into the buffer
	size_t bytesRead = fread(data, sizeof(BYTE), bytesToRead, filePtr);

	//check the number of bytes that were read
	if (bytesRead < bytesToRead) {
		if (feof(filePtr)) {
			return 2; // End of file reached before expected
		}
		if (ferror(filePtr)) {
			return 1; // Error reading file
		}
	}

	return 0;
}

/// <summary>
/// This function will write a number of bytes into an open file
/// </summary>
/// <param name="filePtr">pointer to the open file</param>
/// <param name="data">pointer to the data to be written</param>
/// <param name="bytesToWrite">number of bytes to be written</param>
/// <returns>error code</returns>
int writeFile(FILE* filePtr, BYTE* data, int bytesToWrite) {
	// Validate parameters
	if (!filePtr || !data) {
		return -1;
	}

	// Write the data to the file
	int writtenBytes = fwrite(data, sizeof(char), bytesToWrite, filePtr);

	// Check for write completion and file errors
	if (writtenBytes != bytesToWrite || ferror(filePtr)) {
		return 1;
	}

	return 0;
}