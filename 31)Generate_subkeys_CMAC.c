#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE_64 8   // 64-bit block size
#define BLOCK_SIZE_128 16 // 128-bit block size

// Dummy encryption function (replace with AES or another block cipher)
void block_cipher_encrypt(uint8_t *input, uint8_t *key, uint8_t *output, int block_size) {
    // Example: copying input to output (replace with actual block cipher encryption)
    memcpy(output, input, block_size);
}

// Left shift function (shift by 1 bit)
void left_shift(uint8_t *input, uint8_t *output, int block_size) {
    uint8_t overflow = 0;
    for (int i = block_size - 1; i >= 0; i--) {
        output[i] = (input[i] << 1) | overflow;
        overflow = (input[i] & 0x80) ? 1 : 0;  // Capture MSB for next byte
    }
}

// XOR function
void xor_with_constant(uint8_t *input, uint8_t constant, int block_size) {
    input[block_size - 1] ^= constant;  // XOR only with the last byte
}

// Subkey generation function
void generate_subkeys(uint8_t *key, int block_size, uint8_t *K1, uint8_t *K2) {
    uint8_t L[block_size];  // Result of block cipher encryption of a zero block
    uint8_t Rb;             // Block size-specific constant for XOR

    // Determine the Rb constant based on block size
    if (block_size == BLOCK_SIZE_64) {
        Rb = 0x1B;  // 64-bit block size constant
    } else if (block_size == BLOCK_SIZE_128) {
        Rb = 0x87;  // 128-bit block size constant
    } else {
        printf("Unsupported block size.\n");
        return;
    }

    // Step 1: Apply the block cipher to a zero block to get L
    uint8_t zero_block[block_size];
    memset(zero_block, 0, block_size);
    block_cipher_encrypt(zero_block, key, L, block_size);

    // Step 2: Derive K1 (first subkey) by left-shifting L
    left_shift(L, K1, block_size);

    // If the MSB of L is 1, XOR K1 with the constant Rb
    if (L[0] & 0x80) {
        xor_with_constant(K1, Rb, block_size);
    }

    // Step 3: Derive K2 (second subkey) by left-shifting K1
    left_shift(K1, K2, block_size);

    // If the MSB of K1 is 1, XOR K2 with the constant Rb
    if (K1[0] & 0x80) {
        xor_with_constant(K2, Rb, block_size);
    }
}

int main() {
    uint8_t key[BLOCK_SIZE_128] = { /* Fill with your key bytes */ };
    uint8_t K1[BLOCK_SIZE_128], K2[BLOCK_SIZE_128];

    // Generate subkeys for 128-bit block size
    generate_subkeys(key, BLOCK_SIZE_128, K1, K2);

    // Print the subkeys
    printf("K1: ");
    for (int i = 0; i < BLOCK_SIZE_128; i++) {
        printf("%02x", K1[i]);
    }
    printf("\n");

    printf("K2: ");
    for (int i = 0; i < BLOCK_SIZE_128; i++) {
        printf("%02x", K2[i]);
    }
    printf("\n");

    return 0;
}
