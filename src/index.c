#include "../include/index.h"
#include "../include/colors.h"



TrieNode *root = NULL;

TrieNode* createNode() {
    TrieNode *node = (TrieNode*)malloc(sizeof(TrieNode));
    node->isEndOfWord = false;
    node->fileList = NULL;
    for (int i = 0; i < 26; i++) node->children[i] = NULL;
    return node;
}

FileNode* addFile(FileNode *head, const char *fileName) {
    FileNode *temp = head;
    while (temp) {
        if (strcmp(temp->fileName, fileName) == 0) {
            temp->frequency++;
            return head;
        }
        temp = temp->next;
    }
    FileNode *newFile = (FileNode*)malloc(sizeof(FileNode));
    strcpy(newFile->fileName, fileName);
    newFile->frequency = 1;
    newFile->next = head;
    return newFile;
}

void indexWord(const char *word, const char *fileName) {
    if (!root) root = createNode();
    TrieNode *curr = root;
    for (int i = 0; word[i]; i++) {
        char c = word[i];
        if (c < 'a' || c > 'z') continue;
        int idx = c - 'a';
        if (!curr->children[idx]) curr->children[idx] = createNode();
        curr = curr->children[idx];
    }
    curr->isEndOfWord = true;
    curr->fileList = addFile(curr->fileList, fileName);
}

void displayIndex(TrieNode *node, char *buffer, int depth) {
    if (!node) return;
    if (node->isEndOfWord) {
        buffer[depth] = '\0';
        printf("%s -> ", buffer);
        FileNode *f = node->fileList;
        while (f) {
            printf("[%s:%d] ", f->fileName, f->frequency);
            f = f->next;
        }
        printf("\n");
    }
    for (int i = 0; i < 26; i++) {
        if (node->children[i]) {
            buffer[depth] = 'a' + i;
            displayIndex(node->children[i], buffer, depth + 1);
        }
    }
}

void freeTrie(TrieNode *node) {
    if (!node) return;
    for (int i = 0; i < 26; i++) freeTrie(node->children[i]);
    FileNode *temp = node->fileList;
    while (temp) {
        FileNode *next = temp->next;
        free(temp);
        temp = next;
    }
    free(node);
}

void saveIndexToFile(TrieNode *node, FILE *fp, char *buffer, int depth) {
    if (!node) return;
    if (node->isEndOfWord) {
        buffer[depth] = '\0';
        fprintf(fp, "%s -> ", buffer);
        FileNode *f = node->fileList;
        while (f) {
            fprintf(fp, "[%s:%d] ", f->fileName, f->frequency);
            f = f->next;
        }
        fprintf(fp, "\n");
    }
    for (int i = 0; i < 26; i++) {
        if (node->children[i]) {
            buffer[depth] = 'a' + i;
            saveIndexToFile(node->children[i], fp, buffer, depth + 1);
        }
    }
}

void exportIndex(const char *filePath) {
    FILE *fp = fopen(filePath, "w");
    if (!fp) {
        fprintf(stderr, "Error: Cannot write index to %s\n", filePath);
        return;
    }
    char buffer[100];
    saveIndexToFile(root, fp, buffer, 0);
    fclose(fp);
    printf(GREEN "Index successfully exported to %s\n" RESET, filePath);

}

void showFullIndex() {
    if (!root) {
        printf(RED "Index is empty.\n" RESET);
        return;
    }
    char buffer[100];
    printf("\n" CYAN "---------- FULL INDEX ----------\n" RESET);
    displayIndex(root, buffer, 0);
    printf(CYAN "--------------------------------\n\n" RESET);
}
