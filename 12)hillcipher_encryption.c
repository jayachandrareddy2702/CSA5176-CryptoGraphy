#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 2

// Function to convert a character to its corresponding numeric value (A=0, B=1, ..., Z=25)
int charToNum(char ch) {
    return toupper(ch) - 'A';
}

// Function to convert a numeric value to its corresponding character (0=A, 1=B, ..., 25=Z)
char numToChar(int num) {
    return num + 'A';
}

// Function to encrypt a 2-letter block using the Hill cipher
void encryptBlock(int key[SIZE][SIZE], int plaintext[SIZE], int ciphertext[SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        ciphertext[i] = 0;
        for (int j = 0; j < SIZE; j++) {
            ciphertext[i] += key[i][j] * plaintext[j];
        }
        ciphertext[i] = ciphertext[i] % 26; // Ensure the result is in range 0-25
    }
}

// Function to prepare the plaintext message
void prepareMessage(const char *message, char *prepared) {
    int index = 0;
    for (int i = 0; message[i] != '\0'; i++) {
        if (isalpha(message[i])) {
            prepared[index++] = toupper(message[i]);
        }
    }
    // If the length is odd, append 'X' to make it even
    if (index % 2 != 0) {
        prepared[index++] = 'X';
    }
    prepared[index] = '\0'; // Null-terminate the string
}

int main() {
    // Key matrix
    int key[SIZE][SIZE] = {
        {9, 4},
        {5, 7}
    };

    // Input message to encrypt
    char message[] = "meet me at the usual place at ten rather than eight oclock";
    char prepared[100];
    int len, plaintext[SIZE], ciphertext[SIZE];

    // Prepare the message
    prepareMessage(message, prepared);
    len = strlen(prepared);

    // Encrypt the message in blocks of 2 letters
    printf("Ciphertext: ");
    for (int i = 0; i < len; i += 2) {
        // Convert 2 characters into their numeric values
        plaintext[0] = charToNum(prepared[i]);
        plaintext[1] = charToNum(prepared[i + 1]);

        // Encrypt the block
        encryptBlock(key, plaintext, ciphertext);

        // Convert the encrypted numbers back to characters
        printf("%c%c", numToChar(ciphertext[0]), numToChar(ciphertext[1]));
    }
    printf("\n");

    return 0;
}
