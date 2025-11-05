#include "../include/utils.h"

// Standard C Library Includes
#include <ctype.h>    // for isalpha, tolower
#include <string.h>   // for strcmp, strtok
#include <stdlib.h>   // for exit, NULL
#include <dirent.h>   // for directory handling (Linux/macOS compatible)

// --- Stop Word List ---
const char* stopWords[] = {
    "the", "a", "an", "is", "was", "are", "were", "and", "or", "but", 
    "of", "to", "in", "on", "at", "for", "with", "it", "its", "by",
    "be", "as", "from", "that", "this", "which", "will", "i", "my", "you", 
    "your", "he", "she", "him", "her", "we", "our", "they", "their"
};
const int numStopWords = sizeof(stopWords) / sizeof(stopWords[0]);

/**
 * @brief Checks if a word is on the predefined list of stop words.
 */
bool isStopWord(const char *word) {
    if (!word || *word == '\0') return true; // Treat empty strings as stop words
    for (int i = 0; i < numStopWords; i++) {
        if (strcmp(word, stopWords[i]) == 0) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Cleans a word (lowercase, trims punctuation).
 */
char* cleanWord(char *word) {
    if (!word || *word == '\0') return word;

    int len = strlen(word);
    
    // 1. Convert to lowercase and remove internal non-alphabetic characters
    int write_index = 0;
    for (int i = 0; i < len; i++) {
        // Only keep alphabetic characters
        if (isalpha((unsigned char)word[i])) {
            word[write_index++] = (char)tolower((unsigned char)word[i]);
        }
        // Special case: allow single quote for possessives/contractions, 
        // but it will be handled by simple trimming later. 
        // For simplicity, we only focus on alphabetic characters as per task.
    }
    word[write_index] = '\0'; // Null-terminate the cleaned word

    // 2. Simple trimming for any remaining non-alphabetic characters (redundant after step 1, 
    // but useful if we allowed internal dashes/apostrophes)
    // Find the new length
    len = strlen(word);
    if (len == 0) return word;

    // Trim trailing non-alphabetic characters (shouldn't happen here, but safe)
    while (len > 0 && !isalpha((unsigned char)word[len - 1])) {
        word[--len] = '\0';
    }

    // Trim leading non-alphabetic characters
    int start = 0;
    while (start < len && !isalpha((unsigned char)word[start])) {
        start++;
    }

    // Shift the remaining word to the beginning of the buffer
    if (start > 0) {
        memmove(word, word + start, len - start + 1); // +1 for null terminator
    }
    
    return word;
}

// --- Placeholder for Member 2's Indexing Function (for compilation/testing) ---
// In the final project, this should be defined by Member 2 and prototyped in index.h
void indexWord(const char *word, const char *fileName) {
    // This is the data passing step.
    // Replace the printf with the actual function call later.
    printf("-> INDEXED: [%s] from file: %s\n", word, fileName);
}

// Continuation of src/utils.c

/**
 * @brief Handles reading and tokenizing the contents of a single file.
 */
void processFile(const char *fileName, const char *shortName) {
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL) {
        // Error Handling: Cannot open file
        fprintf(stderr, "Error: Could not open file: %s\n", fileName);
        return;
    }

    char lineBuffer[MAX_LINE_BUFFER_SIZE];
    
    // Read the file line by line
    while (fgets(lineBuffer, sizeof(lineBuffer), fp) != NULL) {
        
        // Tokenization: Split the line into words using common delimiters
        // Delimiters include space, tab, newline, carriage return, simple punctuation 
        char *token = strtok(lineBuffer, " \t\n\r,.;:\"?!()[]{}"); 

        while (token != NULL) {
            // 1. Clean the word (lowercase and trim punctuation)
            char *cleaned = cleanWord(token);

            // 2. Check if the word is valid (not empty) and not a stop word
            if (*cleaned != '\0' && !isStopWord(cleaned)) {
                // 3. Data Passing to Member 2
                indexWord(cleaned, shortName); 
            }
            
            // Get the next token
            token = strtok(NULL, " \t\n\r,.;:\"?!()[]{}"); 
        }
    }

    // Safe File Close
    fclose(fp);
}


/**
 * @brief Reads all .txt files from the specified folder path (Entry Point).
 */
void readFiles(const char *folderPath) {
    DIR *dir;
    struct dirent *entry;

    // Error Handling: Invalid folder path
    if ((dir = opendir(folderPath)) == NULL) {
        fprintf(stderr, "Error: Cannot open directory: %s\n", folderPath);
        return;
    }

    printf("--- Starting File Processing for: %s ---\n", folderPath);

    // Read directory contents
    while ((entry = readdir(dir)) != NULL) {
        
        // Skip hidden files, current dir (.), and parent dir (..)
        if (entry->d_name[0] == '.') {
            continue;
        }

        // Check for .txt extension
        int name_len = strlen(entry->d_name);
        if (name_len > 4 && strcmp(entry->d_name + name_len - 4, ".txt") == 0) {
            
            // Construct the full file path
            char fullPath[MAX_FILE_NAME_LENGTH];
            // Ensure path doesn't exceed buffer size
            if (snprintf(fullPath, sizeof(fullPath), "%s/%s", folderPath, entry->d_name) >= sizeof(fullPath)) {
                fprintf(stderr, "Warning: Full path too long for buffer: %s/%s\n", folderPath, entry->d_name);
                continue;
            }
            
            // Call the processor function
            processFile(fullPath, entry->d_name);
        }
    }

    closedir(dir);
    printf("--- File Processing Complete ---\n");
}