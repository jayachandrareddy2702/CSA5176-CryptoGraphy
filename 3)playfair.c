#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

char matrix[SIZE][SIZE];  // 5x5 Playfair cipher matrix

// Function to remove duplicate characters from the keyword and build the matrix
void createMatrix(char key[]) {
    int len = strlen(key);
    int used[26] = {0};  // To track used characters (ignores 'J')
    int row = 0, col = 0;

    // Fill the matrix with the key, ignoring duplicates
    for (int i = 0; i < len; ++i) {
        char ch = toupper(key[i]);
        if (ch == 'J') ch = 'I';  // Replace 'J' with 'I'

        if (!used[ch - 'A']) {
            matrix[row][col] = ch;
            used[ch - 'A'] = 1;
            col++;
            if (col == SIZE) {
                col = 0;
                row++;
            }
        }
    }

    // Fill the remaining spaces in the matrix with the rest of the alphabet
    for (char ch = 'A'; ch <= 'Z'; ++ch) {
        if (ch == 'J') continue;  // Skip 'J'

        if (!used[ch - 'A']) {
            matrix[row][col] = ch;
            used[ch - 'A'] = 1;
            col++;
            if (col == SIZE) {
                col = 0;
                row++;
            }
        }
    }
}

// Function to find the position of a letter in the matrix
void findPosition(char ch, int *row, int *col) {
    if (ch == 'J') ch = 'I';  // Treat 'J' as 'I'
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Function to encrypt a pair of letters
void encryptPair(char *a, char *b) {
    int row1, col1, row2, col2;
    findPosition(toupper(*a), &row1, &col1);
    findPosition(toupper(*b), &row2, &col2);

    // Same row: move right
    if (row1 == row2) {
        *a = matrix[row1][(col1 + 1) % SIZE];
        *b = matrix[row2][(col2 + 1) % SIZE];
    }
    // Same column: move down
    else if (col1 == col2) {
        *a = matrix[(row1 + 1) % SIZE][col1];
        *b = matrix[(row2 + 1) % SIZE][col2];
    }
    // Rectangle: swap columns
    else {
        *a = matrix[row1][col2];
        *b = matrix[row2][col1];
    }
}

// Function to prepare the plaintext for encryption
void prepareText(char text[], char prepared[]) {
    int len = strlen(text);
    int idx = 0;

    for (int i = 0; i < len; ++i) {
        char ch = toupper(text[i]);
        if (isalpha(ch)) {
            if (ch == 'J') ch = 'I';  // Replace 'J' with 'I'
            
            // If two consecutive letters are the same, insert 'X' between them
            if (idx > 0 && prepared[idx - 1] == ch) {
                prepared[idx++] = 'X';
            }
            prepared[idx++] = ch;
        }
    }

    // If the prepared text has an odd length, add 'X' at the end
    if (idx % 2 != 0) {
        prepared[idx++] = 'X';
    }
    prepared[idx] = '\0';  // Null-terminate the string
}

// Function to encrypt the plaintext
void encrypt(char plaintext[], char ciphertext[]) {
    char prepared[100];  // Prepared plaintext (digraphs)
    prepareText(plaintext, prepared);

    int len = strlen(prepared);
    for (int i = 0; i < len; i += 2) {
        char a = prepared[i];
        char b = prepared[i + 1];
        encryptPair(&a, &b);
        ciphertext[i] = a;
        ciphertext[i + 1] = b;
    }
    ciphertext[len] = '\0';  // Null-terminate the ciphertext
}

int main() {
    char key[50], plaintext[100], ciphertext[100];

    // Get the keyword from the user
    printf("Enter the keyword: ");
    scanf("%s", key);

    // Create the Playfair matrix
    createMatrix(key);

    // Display the matrix
    printf("\nPlayfair Matrix:\n");
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }

    // Get the plaintext from the user
    printf("Enter the plaintext: ");
    scanf("%s", plaintext);

    // Encrypt the plaintext
    encrypt(plaintext, ciphertext);

    // Output the encrypted text
    printf("Encrypted text: %s\n", ciphertext);

    return 0;
}
