#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/utils.h"
#include "../include/search_engine.h"
#include "../include/index.h"

extern TrieNode *root;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <data_directory>\n", argv[0]);
        return 1;
    }

    printf("\n--- Starting File Processing for: %s ---\n", argv[1]);
    readFiles(argv[1]);
    printf("--- File Processing Complete ---\n");
    printf("\n--- Indexing Complete ---\n");

    while (1) {
        int choice;
        char word[100];

        printf("\nOptions:\n");
        printf("1. Search a word\n");
        printf("2. Show full index\n");
        printf("3. Export index to file\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter a word to search: ");
                scanf("%s", word);
                searchWord(word);
                break;

            case 2:
                showFullIndex();
                break;

            case 3:
                exportIndex("index_output.txt");
                break;

            case 4:
                printf("Exiting search engine. Goodbye!\n");
                freeTrie(root);
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
                break;
        }
    }
}
