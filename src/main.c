#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/utils.h"
#include "../include/search_engine.h"
#include "../include/colors.h"



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

    printHeader(); // Show once at program start

    while (1) {
        int choice;
        char word[100];

        printf(BLUE "\nOptions:\n" RESET);
        printf("  1. " GREEN "Search a word\n" RESET);
        printf("  2. " YELLOW "Show full index\n" RESET);
        printf("  3. " CYAN "Export index to file\n" RESET);
        printf("  4. " RED "Exit\n" RESET);
        printf(MAGENTA "Enter your choice: " RESET);

        if (scanf("%d", &choice) != 1) {
            printf(RED "Invalid input! Please enter numbers only.\n" RESET);
            fflush(stdin);
            continue;
        }

        // Clear leftover newline from scanf
        getchar();

        switch (choice) {

            case 1:
                printf(MAGENTA "Enter a word to search: " RESET);
                if (fgets(word, sizeof(word), stdin) == NULL) break;
                word[strcspn(word, "\n")] = '\0';
                if (strlen(word) == 0) {
                    printf(RED "Please enter a valid word.\n" RESET);
                    break;
                }
                searchWord(word);
                break;

            case 2:
                showFullIndex();
                break;

            case 3:
                exportIndex("index_output.txt");
                break;

            case 4:
                printf(CYAN "\nThank you for using Mini Search Engine.\n" RESET);
                printf("Have a great day! 🌿\n\n");

                freeTrie(root);
                return 0;

            default:
                printf(RED "Invalid choice! Please try again.\n" RESET);
                break;
        }
    }
}
