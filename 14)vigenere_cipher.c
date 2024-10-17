#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to convert a character to its corresponding numeric value
int charToNumeric(char c) {
    return tolower(c) - 'a';
}

// Function to convert a numeric value back to a character
char numericToChar(int n) {
    return 'a' + (n % 26);
}

// Function to encrypt the plaintext using the key stream
void vigenereEncrypt(char *plaintext, int *key, char *ciphertext) {
    int len = strlen(plaintext);
    for (int i = 0; i < len; i++) {
        if (isalpha(plaintext[i])) {
            int p = charToNumeric(plaintext[i]);
            int k = key[i];
            ciphertext[i] = numericToChar(p + k);
        } else {
            ciphertext[i] = plaintext[i];  // Preserve spaces or non-letters
        }
    }
    ciphertext[len] = '\0';
}

// Function to decrypt the ciphertext using the key stream
void vigenereDecrypt(char *ciphertext, int *key, char *plaintext) {
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i++) {
        if (isalpha(ciphertext[i])) {
            int c = charToNumeric(ciphertext[i]);
            int k = key[i];
            plaintext[i] = numericToChar(c - k);
        } else {
            plaintext[i] = ciphertext[i];  // Preserve spaces or non-letters
        }
    }
    plaintext[len] = '\0';
}

int main() {
    // Part (a): Encrypt the plaintext with the given key stream
    char plaintext[] = "sendmoremoney";
    int keyStream[] = {9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9};
    char ciphertext[100];

    printf("Part (a) - Encryption:\n");
    printf("Plaintext: %s\n", plaintext);

    vigenereEncrypt(plaintext, keyStream, ciphertext);
    printf("Ciphertext: %s\n\n", ciphertext);

    // Part (b): Decrypt the ciphertext to produce "cashnotneeded"
    char targetPlaintext[] = "cashnotneeded";
    int decryptionKey[] = {25, 4, 22, 3, 22, 15, 19, 5, 19, 21, 12, 8, 4};
    char decryptedText[100];

    printf("Part (b) - Decryption:\n");
    printf("Ciphertext: %s\n", ciphertext);

    vigenereDecrypt(ciphertext, decryptionKey, decryptedText);
    printf("Decrypted Text: %s\n", decryptedText);

    return 0;
}
