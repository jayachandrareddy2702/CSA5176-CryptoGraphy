#include <stdio.h>

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

// Function to decrypt ciphertext
void decrypt(char *ciphertext, char *plaintext, int a, int b) {
    int a_inv = modInverse(a);  // Find modular inverse of 'a'
    if (a_inv == -1) {
        printf("Decryption not possible. Invalid 'a' value.\n");
        return;
    }

    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            int C = ciphertext[i] - base;
            plaintext[i] = (a_inv * (C - b + 26)) % 26 + base;
        } else {
            plaintext[i] = ciphertext[i];  // Non-alphabetic characters stay the same
        }
    }
}

int main() {
    char ciphertext[] = "YourCiphertextHere";  // Replace with your actual ciphertext
    char plaintext[100];
    
    int a, b;
    
    // Solving the system of equations for 'a' and 'b' manually or via logic
    // For example, you would have found:
    a = 15;  // Example value
    b = 1;   // Example value
    
    // Decrypt the ciphertext
    decrypt(ciphertext, plaintext, a, b);
    
    // Output the decrypted text
    printf("Decrypted text: %s\n", plaintext);

    return 0;
}
