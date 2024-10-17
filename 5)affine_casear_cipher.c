#include <stdio.h>
#include <string.h>

// Function to find gcd (greatest common divisor)
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to find modular inverse of 'a' under modulo 26
int modInverse(int a) {
    for (int i = 1; i < 26; i++) {
        if ((a * i) % 26 == 1) {
            return i;
        }
    }
    return -1;  // No inverse exists
}

// Encryption function
void encrypt(char *plaintext, char *ciphertext, int a, int b) {
    int textLen = strlen(plaintext);

    for (int i = 0; i < textLen; i++) {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            int p = plaintext[i] - base;  // Position of plaintext letter (0-25)
            ciphertext[i] = (a * p + b) % 26 + base;  // Apply affine formula
        } else {
            ciphertext[i] = plaintext[i];  // Non-alphabetic characters stay the same
        }
    }
    ciphertext[textLen] = '\0';  // Null-terminate the ciphertext string
}

// Decryption function
void decrypt(char *ciphertext, char *plaintext, int a, int b) {
    int textLen = strlen(ciphertext);
    int a_inv = modInverse(a);  // Find inverse of 'a'

    if (a_inv == -1) {
        printf("Decryption not possible. Invalid 'a' value.\n");
        return;
    }

    for (int i = 0; i < textLen; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            int C = ciphertext[i] - base;  // Position of ciphertext letter (0-25)
            plaintext[i] = (a_inv * (C - b + 26)) % 26 + base;  // Apply decryption formula
        } else {
            plaintext[i] = ciphertext[i];  // Non-alphabetic characters stay the same
        }
    }
    plaintext[textLen] = '\0';  // Null-terminate the plaintext string
}

int main() {
    char plaintext[100], ciphertext[100], decryptedtext[100];
    int a, b;

    // Input values
    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';  // Remove newline character from input

    printf("Enter value of a: ");
    scanf("%d", &a);
    printf("Enter value of b: ");
    scanf("%d", &b);

    // Check if 'a' is valid (coprime with 26)
    if (gcd(a, 26) != 1) {
        printf("Invalid 'a' value. 'a' must be coprime with 26.\n");
        return 1;
    }

    // Encrypt the plaintext
    encrypt(plaintext, ciphertext, a, b);
    printf("Ciphertext: %s\n", ciphertext);

    // Decrypt the ciphertext
    decrypt(ciphertext, decryptedtext, a, b);
    printf("Decrypted text: %s\n", decryptedtext);

    return 0;
}
