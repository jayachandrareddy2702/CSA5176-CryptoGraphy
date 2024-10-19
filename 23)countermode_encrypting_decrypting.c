#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Function prototypes
uint8_t sdes_encrypt(uint8_t input, uint8_t key);
uint8_t sdes_decrypt(uint8_t input, uint8_t key);
uint8_t sdes(uint8_t input, uint8_t key);
uint8_t xor_bytes(uint8_t a, uint8_t b);
void print_binary(uint8_t byte);

int main() {
    uint8_t plaintext[] = {0x01, 0x02, 0x04}; // Binary: 0000 0001, 0000 0010, 0000 0100
    uint8_t key = 0xFD; // Binary key: 01111 11101
    uint8_t counter = 0x00; // Counter starts at 0000 0000
    uint8_t ciphertext[3];
    uint8_t decrypted[3];

    printf("Plaintext:\n");
    for (int i = 0; i < 3; i++) {
        print_binary(plaintext[i]);
    }

    // Encrypt
    printf("\nEncrypting...\n");
    for (int i = 0; i < 3; i++) {
        uint8_t encrypted_counter = sdes(counter, key); // Encrypt the counter
        ciphertext[i] = xor_bytes(plaintext[i], encrypted_counter); // XOR with plaintext
        print_binary(ciphertext[i]);
        counter++;
    }

    // Reset counter for decryption
    counter = 0x00;

    // Decrypt
    printf("\nDecrypting...\n");
    for (int i = 0; i < 3; i++) {
        uint8_t encrypted_counter = sdes(counter, key); // Encrypt the counter
        decrypted[i] = xor_bytes(ciphertext[i], encrypted_counter); // XOR with ciphertext
        print_binary(decrypted[i]);
        counter++;
    }

    return 0;
}

// S-DES Encryption function (this is a placeholder, S-DES involves multiple steps)
uint8_t sdes(uint8_t input, uint8_t key) {
    // In practice, you'd implement the full S-DES algorithm here.
    // For now, this is a dummy function that just XORs the input and key.
    return input ^ key; // Placeholder for actual S-DES encryption
}

// XOR two bytes together
uint8_t xor_bytes(uint8_t a, uint8_t b) {
    return a ^ b;
}

// Function to print a byte in binary
void print_binary(uint8_t byte) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (byte >> i) & 1);
    }
    printf("\n");
}
