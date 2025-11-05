#ifndef UTILS_H
#define UTILS_H

// --- Includes ---
#include <stdbool.h> 
#include <stdio.h>   

// --- Constants ---
#define MAX_WORD_LENGTH 50
#define MAX_FILE_NAME_LENGTH 256
#define MAX_LINE_BUFFER_SIZE 1024

void readFiles(const char *folderPath);
bool isStopWord(const char *word);
char* cleanWord(char *word);

void processFile(const char *fileName, const char *shortName);

void indexWord(const char *word, const char *fileName); 

#endif 