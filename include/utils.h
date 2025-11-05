#ifndef UTILS_H
#define UTILS_H

// --- Includes ---
#include <stdbool.h> // For bool type
#include <stdio.h>   // For FILE operations

// --- Constants ---
#define MAX_WORD_LENGTH 50
#define MAX_FILE_NAME_LENGTH 256
#define MAX_LINE_BUFFER_SIZE 1024

// --- Member 1 (Your) Function Prototypes ---
void readFiles(const char *folderPath);
bool isStopWord(const char *word);
char* cleanWord(char *word);

// Internal helper function (optional, but good practice)
void processFile(const char *fileName, const char *shortName);

// --- Interface to Member 2 (Indexing) ---
// Define a placeholder for the indexing function you will call.
// This assumes Member 2 provides an 'index.h' header.
void indexWord(const char *word, const char *fileName); 

#endif // UTILS_H