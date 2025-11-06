#include "../include/search_engine.h"
#include <string.h>
#include <ctype.h>
#include "../include/colors.h"


extern TrieNode *root;

// Print the header for the search engine
void printHeader() {
    printf(CYAN "\n==============================================\n" RESET);
    printf(MAGENTA "             MINI SEARCH ENGINE\n" RESET);
    printf(CYAN "==============================================\n" RESET);
}

// Sort the file list by frequency (descending)
void sortResults(FileNode **head) {
    if (!head || !*head) return;

    FileNode *i, *j;
    for (i = *head; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (j->frequency > i->frequency) {
                // Swap frequency
                int tempFreq = i->frequency;
                i->frequency = j->frequency;
                j->frequency = tempFreq;

                // Swap file names
                char tempName[256];
                strcpy(tempName, i->fileName);
                strcpy(i->fileName, j->fileName);
                strcpy(j->fileName, tempName);
            }
        }
    }
}


void searchWord(const char *word) {
    if (!word || strlen(word) == 0) {
        printf(RED "Error: Empty search query.\n" RESET);
        return;
    }

    TrieNode *curr = root;
    for (int i = 0; word[i]; i++) {
        char c = tolower(word[i]);  // Case-insensitive
        if (c < 'a' || c > 'z') continue;
        int idx = c - 'a';
        if (!curr->children[idx]) {
            printf(RED "\nNo results found for '%s'.\n\n" RESET, word);
            return;
        }
        curr = curr->children[idx];
    }

    if (!curr->isEndOfWord || !curr->fileList) {
        printf(RED "\nNo results found for '%s'.\n\n" RESET, word);
        return;
    }

    // Sort results by frequency
    sortResults(&(curr->fileList));

    // Print search results with highlighted word
    FileNode *f = curr->fileList;
    printf(CYAN "-----------------------------------\n" RESET);
    printf(YELLOW "Results for '%s':\n" RESET, word);
    int idx = 1;
    size_t wordLen = strlen(word);

    while (f) {
        char *fileName = f->fileName;
        printf(GREEN "%2d. " RESET, idx++);

        // Print the file name with highlighted search word
        for (int i = 0; fileName[i];) {
            int match = 1;
            for (size_t j = 0; j < wordLen; j++) {
                if (tolower(fileName[i + j]) != tolower(word[j])) {
                    match = 0;
                    break;
                }
            }

            if (match) {
                // Highlight the matched part
                printf(MAGENTA "%.*s" RESET, (int)wordLen, fileName + i);
                i += wordLen;
            } else {
                printf("%c", fileName[i]);
                i++;
            }
        }

        // Print frequency
        printf("  " MAGENTA "(%d matches)\n" RESET, f->frequency);
        f = f->next;
    }
    printf(CYAN "-----------------------------------\n\n" RESET);

}
