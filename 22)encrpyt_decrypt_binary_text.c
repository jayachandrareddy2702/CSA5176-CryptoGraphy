#include <stdio.h>
#include <string.h>

// S-DES encryption and decryption prototypes
unsigned char sdes_encrypt(unsigned char block, unsigned char key);
unsigned char sdes_decrypt(unsigned char block, unsigned char key);

// XOR function for 8-bit blocks
unsigned char XOR_blocks(unsigned char block1, unsigned char block2) {
    return block1 ^ block2;
}

// CBC Encryption using S-DES
void cbc_encrypt(unsigned char *plaintext, unsigned char *ciphertext, unsigned char IV, unsigned char key, int num_blocks) {
    unsigned char prev_block = IV;
    
    for (int i = 0; i < num_blocks; i++) {
        // XOR with the previous ciphertext (or IV for the first block)
        unsigned char xored_block = XOR_blocks(plaintext[i], prev_block);
        
        // Encrypt the block using S-DES
        ciphertext[i] = sdes_encrypt(xored_block, key);
        
        // Update the previous block
        prev_block = ciphertext[i];
    }
}

// CBC Decryption using S-DES
void cbc_decrypt(unsigned char *ciphertext, unsigned char *decrypted_text, unsigned char IV, unsigned char key, int num_blocks) {
    unsigned char prev_block = IV;
    
    for (int i = 0; i < num_blocks; i++) {
        // Decrypt the ciphertext block using S-DES
        unsigned char decrypted_block = sdes_decrypt(ciphertext[i], key);
        
        // XOR with the previous ciphertext (or IV for the first block)
        decrypted_text[i] = XOR_blocks(decrypted_block, prev_block);
        
        // Update the previous block
        prev_block = ciphertext[i];
    }
}

// S-DES encryption (Simplified version)
unsigned char sdes_encrypt(unsigned char block, unsigned char key) {
    // Simple S-DES logic placeholder (replace with actual logic)
    return block ^ key; // Basic XOR encryption for demo purposes
}

// S-DES decryption (Simplified version)
unsigned char sdes_decrypt(unsigned char block, unsigned char key) {
    // Simple S-DES logic placeholder (replace with actual logic)
    return block ^ key; // Basic XOR decryption for demo purposes
}

int main() {
    unsigned char plaintext[] = { 0b00000001, 0b00100011 };  // Binary plaintext
    unsigned char key = 0b0111111101;  // 10-bit key
    unsigned char IV = 0b10101010;     // Initialization vector (IV)
    int num_blocks = sizeof(plaintext);  // Number of 8-bit blocks in plaintext

    unsigned char ciphertext[num_blocks];
    unsigned char decrypted_text[num_blocks];

    // Encrypt the plaintext
    cbc_encrypt(plaintext, ciphertext, IV, key, num_blocks);

    printf("Ciphertext:\n");
    for (int i = 0; i < num_blocks; i++) {
        printf("%02x ", ciphertext[i]);
    }
    printf("\n");

    // Decrypt the ciphertext
    cbc_decrypt(ciphertext, decrypted_text, IV, key, num_blocks);

    printf("Decrypted text:\n");
    for (int i = 0; i < num_blocks; i++) {
        printf("%02x ", decrypted_text[i]);
    }
    printf("\n");

    return 0;
}
