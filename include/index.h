#ifndef INDEX_H
#define INDEX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_WORD_LENGTH 50
#define MAX_FILES 100

typedef struct FileNode {
    char fileName[256];
    int frequency;
    struct FileNode *next;
} FileNode;

typedef struct TrieNode {
    struct TrieNode *children[26];
    bool isEndOfWord;
    FileNode *fileList;
} TrieNode;

TrieNode* createNode();
void indexWord(const char *word, const char *fileName);
FileNode* addFile(FileNode *head, const char *fileName);
void displayIndex(TrieNode *root, char *buffer, int depth);
void freeTrie(TrieNode *root);

#endif