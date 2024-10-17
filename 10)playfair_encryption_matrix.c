#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

// Predefined Playfair matrix
char matrix[SIZE][SIZE] = {
    {'M', 'F', 'H', 'I', 'K'},
    {'U', 'N', 'O', 'P', 'Q'},
    {'Z', 'V', 'W', 'X', 'Y'},
    {'E', 'L', 'A', 'R', 'G'},
    {'D', 'S', 'T', 'B', 'C'}
};

// Function to find the position of a character in the key matrix
void findPosition(char matrix[SIZE][SIZE], char ch, int *row, int *col) {
    if (ch == 'J') ch = 'I'; // Treat 'J' as 'I'
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] == toupper(ch)) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Encrypt two characters using Playfair cipher rules
void encryptPair(char a, char b, char *encrypted) {
    int row1, col1, row2, col2;

    findPosition(matrix, a, &row1, &col1);
    findPosition(matrix, b, &row2, &col2);

    if (row1 == row2) {
        // Same row, move right
        encrypted[0] = matrix[row1][(col1 + 1) % SIZE];
        encrypted[1] = matrix[row2][(col2 + 1) % SIZE];
    } else if (col1 == col2) {
        // Same column, move down
        encrypted[0] = matrix[(row1 + 1) % SIZE][col1];
        encrypted[1] = matrix[(row2 + 1) % SIZE][col2];
    } else {
        // Rectangle, swap corners
        encrypted[0] = matrix[row1][col2];
        encrypted[1] = matrix[row2][col1];
    }
}

// Function to prepare the message for encryption
void prepareMessage(char message[], char prepared[]) {
    int len = strlen(message);
    int index = 0;

    for (int i = 0; i < len; i++) {
        if (isalpha(message[i])) {
            prepared[index++] = toupper(message[i]);
        }
    }

    // Ensure message has an even number of characters by adding 'X' if needed
    if (index % 2 != 0) {
        prepared[index++] = 'X';
    }
    prepared[index] = '\0';
}

// Function to encrypt the Playfair cipher text
void encryptPlayfair(char message[], char encrypted[]) {
    char prepared[1000];
    int len;

    // Prepare the message (remove non-letters and make pairs)
    prepareMessage(message, prepared);
    len = strlen(prepared);

    int index = 0;

    // Encrypt each pair of characters
    for (int i = 0; i < len; i += 2) {
        encryptPair(prepared[i], prepared[i + 1], &encrypted[index]);
        index += 2;
    }
    encrypted[index] = '\0'; // Null-terminate the encrypted string
}

int main() {
    char message[1000], encrypted[1000];

    // Input the message to encrypt
    printf("Enter the message: ");
    fgets(message, sizeof(message), stdin);

    // Encrypt the message using Playfair cipher
    encryptPlayfair(message, encrypted);

    // Output the encrypted message
    printf("Encrypted message: %s\n", encrypted);

    return 0;
}
