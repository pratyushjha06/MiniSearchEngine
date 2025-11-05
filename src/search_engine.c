#include "../include/search_engine.h"

extern TrieNode *root;

void searchWord(const char *word) {
    TrieNode *curr = root;
    for (int i = 0; word[i]; i++) {
        char c = word[i];
        if (c < 'a' || c > 'z') continue;
        int idx = c - 'a';
        if (!curr->children[idx]) {
            printf("No results for '%s'\n", word);
            return;
        }
        curr = curr->children[idx];
    }
    if (!curr->isEndOfWord) {
        printf("No results for '%s'\n", word);
        return;
    }

    FileNode *f = curr->fileList;
    printf("Results for '%s':\n", word);
    while (f) {
        printf(" - %s (%d)\n", f->fileName, f->frequency);
        f = f->next;
    }
}
