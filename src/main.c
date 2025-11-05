#include "../include/utils.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    // Check if the user provided a folder path
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <path_to_data_folder>\n", argv[0]);
        fprintf(stderr, "Example: %s data/\n", argv[0]);
        return 1;
    }

    // Call your main entry point function
    readFiles(argv[1]);

    return 0;
}