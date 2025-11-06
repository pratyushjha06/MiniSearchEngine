#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include "colors.h"
#include "index.h"

void printHeader();
void searchWord(const char *word);
void showFullIndex();
void exportIndex(const char *filePath);

#endif

