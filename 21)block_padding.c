#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BLOCK_SIZE 16  // Example block size

// Function prototypes
void ECB_encrypt(const unsigned char *plaintext, const unsigned char *key, unsigned char *ciphertext);
void CBC_encrypt(const unsigned char *plaintext, const unsigned char *key, unsigned char *ciphertext, unsigned char *IV);
void CFB_encrypt(const unsigned char *plaintext, const unsigned char *key, unsigned char *ciphertext, unsigned char *IV);
void pad(unsigned char *plaintext, int *len);

void XOR_blocks(const unsigned char *block1, const unsigned char *block2, unsigned char *result) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        result[i] = block1[i] ^ block2[i];
    }
}

void encrypt_block(const unsigned char *block, const unsigned char *key, unsigned char *ciphertext) {
    // Placeholder for block encryption (e.g., AES, DES)
    memcpy(ciphertext, block, BLOCK_SIZE); // Example: no actual encryption for simplicity
}

// ECB Encryption
void ECB_encrypt(const unsigned char *plaintext, const unsigned char *key, unsigned char *ciphertext) {
    int len = strlen((const char *)plaintext);
    for (int i = 0; i < len; i += BLOCK_SIZE) {
        encrypt_block(&plaintext[i], key, &ciphertext[i]);
    }
}

// CBC Encryption
void CBC_encrypt(const unsigned char *plaintext, const unsigned char *key, unsigned char *ciphertext, unsigned char *IV) {
    int len = strlen((const char *)plaintext);
    unsigned char prev_block[BLOCK_SIZE];
    memcpy(prev_block, IV, BLOCK_SIZE);

    for (int i = 0; i < len; i += BLOCK_SIZE) {
        unsigned char xor_block[BLOCK_SIZE];
        XOR_blocks(&plaintext[i], prev_block, xor_block);
        encrypt_block(xor_block, key, &ciphertext[i]);
        memcpy(prev_block, &ciphertext[i], BLOCK_SIZE); // Update IV for next round
    }
}

// CFB Encryption
void CFB_encrypt(const unsigned char *plaintext, const unsigned char *key, unsigned char *ciphertext, unsigned char *IV) {
    int len = strlen((const char *)plaintext);
    unsigned char feedback[BLOCK_SIZE];
    memcpy(feedback, IV, BLOCK_SIZE);

    for (int i = 0; i < len; i += BLOCK_SIZE) {
        unsigned char encrypted_feedback[BLOCK_SIZE];
        encrypt_block(feedback, key, encrypted_feedback);
        XOR_blocks(encrypted_feedback, &plaintext[i], &ciphertext[i]);
        memcpy(feedback, &ciphertext[i], BLOCK_SIZE); // Shift feedback
    }
}

// Padding Function
void pad(unsigned char *plaintext, int *len) {
    int padding_len = BLOCK_SIZE - (*len % BLOCK_SIZE);
    if (padding_len == 0) {
        padding_len = BLOCK_SIZE;
    }
    for (int i = 0; i < padding_len; i++) {
        plaintext[*len + i] = (i == 0) ? 0x80 : 0x00;  // Padding: 0x80 then 0x00
    }
    *len += padding_len;
}

int main() {
    unsigned char plaintext[128] = "This is a test message.";
    unsigned char key[BLOCK_SIZE] = "examplekey123456"; // Example key
    unsigned char ciphertext[128];
    unsigned char IV[BLOCK_SIZE] = "initialvector123"; // Example IV
    int len = strlen((const char *)plaintext);

    pad(plaintext, &len);  // Pad plaintext to block size

    printf("Choose encryption mode: ECB, CBC, CFB\n");
    char mode[4];
    scanf("%s", mode);

    if (strcmp(mode, "ECB") == 0) {
        ECB_encrypt(plaintext, key, ciphertext);
    } else if (strcmp(mode, "CBC") == 0) {
        CBC_encrypt(plaintext, key, ciphertext, IV);
    } else if (strcmp(mode, "CFB") == 0) {
        CFB_encrypt(plaintext, key, ciphertext, IV);
    } else {
        printf("Invalid mode selected!\n");
        return 1;
    }

    printf("Ciphertext: ");
    for (int i = 0; i < len; i++) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");

    return 0;
}
