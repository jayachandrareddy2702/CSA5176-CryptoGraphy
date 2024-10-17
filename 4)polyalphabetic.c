#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encrypt(char *plaintext, char *key, char *ciphertext) {
    int textLen = strlen(plaintext);
    int keyLen = strlen(key);
    
    for (int i = 0, j = 0; i < textLen; i++) {
        // Only encrypt alphabetic characters
        if (isalpha(plaintext[i])) {
            // Shift letters based on key
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            ciphertext[i] = (plaintext[i] - base + (tolower(key[j % keyLen]) - 'a')) % 26 + base;
            j++;  // Move to next character in key only if a letter is encrypted
        } else {
            ciphertext[i] = plaintext[i];  // Non-alphabetic characters stay the same
        }
    }
    ciphertext[textLen] = '\0';  // Null-terminate the ciphertext string
}

int main() {
    char plaintext[100], key[100], ciphertext[100];

    // Input plaintext and key
    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';  // Remove newline character from input

    printf("Enter key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';  // Remove newline character from input

    // Encrypt the plaintext
    encrypt(plaintext, key, ciphertext);

    // Output the ciphertext
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}
