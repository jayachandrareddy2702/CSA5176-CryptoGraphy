#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

// Function to remove duplicates from the keyword and generate the key matrix
void generateKeyMatrix(char key[], char matrix[SIZE][SIZE]) {
    int used[26] = {0};
    int row = 0, col = 0;

    for (int i = 0; key[i] != '\0'; i++) {
        char c = toupper(key[i]);
        if (c == 'J') c = 'I'; // Merge I and J
        
        if (!used[c - 'A']) {
            matrix[row][col] = c;
            used[c - 'A'] = 1;
            col++;
            if (col == SIZE) {
                col = 0;
                row++;
            }
        }
    }

    // Fill the matrix with the remaining letters
    for (char c = 'A'; c <= 'Z'; c++) {
        if (c == 'J') continue; // Skip 'J'
        if (!used[c - 'A']) {
            matrix[row][col] = c;
            used[c - 'A'] = 1;
            col++;
            if (col == SIZE) {
                col = 0;
                row++;
            }
        }
    }
}

// Function to find the position of a character in the key matrix
void findPosition(char matrix[SIZE][SIZE], char ch, int *row, int *col) {
    if (ch == 'J') ch = 'I'; // Treat 'J' as 'I'
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Decrypt two characters using Playfair cipher rules
void decryptPair(char matrix[SIZE][SIZE], char a, char b, char *decrypted) {
    int row1, col1, row2, col2;

    findPosition(matrix, a, &row1, &col1);
    findPosition(matrix, b, &row2, &col2);

    if (row1 == row2) {
        // Same row, move left
        decrypted[0] = matrix[row1][(col1 + SIZE - 1) % SIZE];
        decrypted[1] = matrix[row2][(col2 + SIZE - 1) % SIZE];
    } else if (col1 == col2) {
        // Same column, move up
        decrypted[0] = matrix[(row1 + SIZE - 1) % SIZE][col1];
        decrypted[1] = matrix[(row2 + SIZE - 1) % SIZE][col2];
    } else {
        // Rectangle, swap corners
        decrypted[0] = matrix[row1][col2];
        decrypted[1] = matrix[row2][col1];
    }
}

// Function to decrypt the Playfair cipher text
void decryptPlayfair(char matrix[SIZE][SIZE], char ciphertext[], char decrypted[]) {
    int len = strlen(ciphertext);
    int index = 0;

    for (int i = 0; i < len; i += 2) {
        decryptPair(matrix, toupper(ciphertext[i]), toupper(ciphertext[i + 1]), &decrypted[index]);
        index += 2;
    }
    decrypted[index] = '\0'; // Null-terminate the decrypted string
}

int main() {
    char key[100], ciphertext[1000], decrypted[1000];
    char matrix[SIZE][SIZE];

    // Input the keyword
    printf("Enter the keyword: ");
    scanf("%s", key);

    // Input the ciphertext
    printf("Enter the ciphertext (without spaces): ");
    scanf("%s", ciphertext);

    // Generate the Playfair cipher key matrix
    generateKeyMatrix(key, matrix);

    // Decrypt the ciphertext
    decryptPlayfair(matrix, ciphertext, decrypted);

    // Output the decrypted message
    printf("Decrypted message: %s\n", decrypted);

    return 0;
}
