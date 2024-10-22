#include <stdio.h>
#include <math.h>

// Function to compute (base^exp) % mod (for modular exponentiation)
unsigned long long mod_exp(unsigned long long base, unsigned long long exp, unsigned long long mod) {
    unsigned long long result = 1;
    base = base % mod;
    
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

int main() {
    // RSA public key components
    unsigned long long n = 55;  // Example small modulus for illustration
    unsigned long long e = 3;   // Example small public exponent

    // Message: A = 0, B = 1, ..., Z = 25
    unsigned long long message = 2;  // Let's assume we're encrypting 'C' (mapped to 2)

    // Encrypt the message
    unsigned long long ciphertext = mod_exp(message, e, n);
    printf("Encrypted ciphertext: %llu\n", ciphertext);

    // Simulate attack: try all possible plaintexts
    printf("Attempting brute-force decryption:\n");
    for (unsigned long long i = 0; i < 26; i++) {
        unsigned long long test_ciphertext = mod_exp(i, e, n);
        if (test_ciphertext == ciphertext) {
            printf("Decrypted message: %llu (character %c)\n", i, 'A' + i);
            break;
        }
    }

    return 0;
}
