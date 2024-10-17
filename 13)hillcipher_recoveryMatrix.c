#include <stdio.h>
#include <stdlib.h>

#define SIZE 2 // Size of the key matrix

// Function to convert a character to its corresponding numeric value (A=0, B=1, ..., Z=25)
int charToNum(char ch) {
    return ch - 'A';
}

// Function to convert a numeric value to its corresponding character (0=A, 1=B, ..., 25=Z)
char numToChar(int num) {
    return num + 'A';
}

// Function to compute the determinant of a 2x2 matrix
int determinant(int matrix[SIZE][SIZE]) {
    return (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]) % 26;
}

// Function to compute the modular inverse of a number
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1; // No modular inverse exists
}

// Function to compute the inverse of a 2x2 matrix
void matrixInverse(int matrix[SIZE][SIZE], int inverse[SIZE][SIZE]) {
    int det = determinant(matrix);
    int invDet = modInverse(det, 26);
    
    if (invDet == -1) {
        printf("Matrix is not invertible.\n");
        exit(1);
    }

    // Adjugate matrix
    inverse[0][0] = (matrix[1][1] * invDet) % 26;
    inverse[0][1] = (-matrix[0][1] * invDet) % 26;
    inverse[1][0] = (-matrix[1][0] * invDet) % 26;
    inverse[1][1] = (matrix[0][0] * invDet) % 26;

    // Ensure non-negative values
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (inverse[i][j] < 0) {
                inverse[i][j] += 26;
            }
        }
    }
}

// Function to solve for the key matrix using plaintext and ciphertext pairs
void recoverKeyMatrix(char plaintext[SIZE][SIZE], char ciphertext[SIZE][SIZE], int keyMatrix[SIZE][SIZE]) {
    int ptMatrix[SIZE][SIZE], ctMatrix[SIZE][SIZE];
    
    // Convert plaintext and ciphertext to numeric values
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            ptMatrix[i][j] = charToNum(plaintext[i][j]);
            ctMatrix[i][j] = charToNum(ciphertext[i][j]);
        }
    }

    // Calculate key matrix
    int ptInverse[SIZE][SIZE];
    matrixInverse(ptMatrix, ptInverse);
    
    // Calculate key matrix = ciphertext * inverse(plaintext)
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            keyMatrix[i][j] = 0;
            for (int k = 0; k < SIZE; k++) {
                keyMatrix[i][j] = (keyMatrix[i][j] + ctMatrix[i][k] * ptInverse[k][j]) % 26;
            }
        }
    }
}

// Main function
int main() {
    // Example plaintext-ciphertext pairs
    char plaintext[SIZE][SIZE] = {
        {'M', 'E'},
        {'A', 'T'}
    };

    char ciphertext[SIZE][SIZE] = {
        {'T', 'H'},
        {'E', 'X'}
    };

    int keyMatrix[SIZE][SIZE];

    // Recover the key matrix
    recoverKeyMatrix(plaintext, ciphertext, keyMatrix);

    // Output the recovered key matrix
    printf("Recovered Key Matrix:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", keyMatrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}
