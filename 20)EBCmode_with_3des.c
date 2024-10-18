#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE 8  // DES works on 64-bit (8-byte) blocks

// Dummy function to simulate 3DES block encryption
void encrypt_3des_block(unsigned char *input, unsigned char *output, unsigned char *key) {
    // In a real implementation, this would encrypt 'input' with 3DES and store result in 'output'
    // For simplicity, we are just copying input to output in this example
    for (int i = 0; i < BLOCK_SIZE; i++) {
        output[i] = input[i] ^ key[i % BLOCK_SIZE];  // Example XOR operation with key
    }
}

// ECB mode encryption function
void ecb_encrypt(unsigned char *plaintext, unsigned char *ciphertext, unsigned char *key, int plaintext_len) {
    unsigned char block[BLOCK_SIZE];
    
    // Process each block of plaintext
    for (int i = 0; i < plaintext_len; i += BLOCK_SIZE) {
        // Copy the current block from the plaintext
        memcpy(block, plaintext + i, BLOCK_SIZE);
        
        // Encrypt the block using 3DES
        encrypt_3des_block(block, ciphertext + i, key);
    }
}

int main() {
    unsigned char plaintext[] = "This is a test of ECB mode. Each block is independent!.";
    unsigned char key[BLOCK_SIZE] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};  // Example key
    unsigned char ciphertext[64];  // Output buffer for ciphertext
    int plaintext_len = strlen((char *)plaintext);
    
    // Ensure plaintext length is a multiple of the block size (ECB mode doesn't handle padding)
    if (plaintext_len % BLOCK_SIZE != 0) {
        printf("Error: Plaintext length must be a multiple of %d bytes!\n", BLOCK_SIZE);
        return 1;
    }

    // Perform ECB encryption
    ecb_encrypt(plaintext, ciphertext, key, plaintext_len);

    // Print the ciphertext in hex format
    printf("Ciphertext: ");
    for (int i = 0; i < plaintext_len; i++) {
        printf("%02X ", ciphertext[i]);
    }
    printf("\n");

    return 0;
}
