#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

// Function to remove duplicate characters from the keyword
void remove_duplicates(char *str) {
    int index = 0;
    int present[256] = {0};  // Track characters that have already appeared

    for (int i = 0; str[i] != '\0'; i++) {
        if (!present[(int)str[i]]) {
            str[index++] = str[i];
            present[(int)str[i]] = 1;
        }
    }
    str[index] = '\0';
}

// Function to generate the cipher alphabet
void generate_cipher(char *keyword, char *cipher) {
    int used[ALPHABET_SIZE] = {0};  // Track used letters
    int i, j, len = strlen(keyword);
    
    // Add keyword to the cipher and mark letters as used
    for (i = 0; i < len; i++) {
        cipher[i] = toupper(keyword[i]);
        used[cipher[i] - 'A'] = 1;  // Mark this letter as used
    }

    // Append the remaining letters of the alphabet
    for (j = 0; j < ALPHABET_SIZE; j++) {
        if (!used[j]) {
            cipher[i++] = 'A' + j;
        }
    }
    cipher[i] = '\0';  // Null-terminate the cipher string
}

int main() {
    char keyword[100], cipher[ALPHABET_SIZE + 1];
    
    // Input the keyword
    printf("Enter the keyword: ");
    scanf("%s", keyword);

    // Remove duplicate characters from the keyword
    remove_duplicates(keyword);

    // Generate the cipher alphabet
    generate_cipher(keyword, cipher);

    // Output the cipher
    printf("Plain:  abcdefghijklmnopqrstuvwxyz\n");
    printf("Cipher: %s\n", cipher);

    return 0;
}
