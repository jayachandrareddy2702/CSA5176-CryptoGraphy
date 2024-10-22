#include <stdio.h>
#include <stdint.h>

// Define the size of block and key
#define BLOCK_SIZE 64   // 64-bit block size for DES
#define KEY_SIZE 56     // 56-bit key size for DES

// Example S-box (simplified)
int S[8][4][16] = {
    // S-box 1
    { {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
      {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
      {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
      {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
    },
    // ... Other S-boxes would follow similarly ...
};

// Initial permutation (simplified)
int IP[] = {58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4};

// Final permutation (simplified)
int FP[] = {40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31};

// Permutation function
uint64_t permute(uint64_t block, int *table, int n) {
    uint64_t permuted_block = 0;
    for (int i = 0; i < n; i++) {
        permuted_block <<= 1;
        permuted_block |= (block >> (BLOCK_SIZE - table[i])) & 1;
    }
    return permuted_block;
}

// Simplified F-function (with expansion, S-boxes, and permutation)
uint32_t f(uint32_t R, uint64_t K) {
    // Expansion of R (simplified) and XOR with the key
    uint32_t expanded_R = R ^ (K & 0xFFFFFFFF);  // Simplified XOR with key

    // S-box substitution (simplified)
    uint32_t result = 0;
    for (int i = 0; i < 8; i++) {
        int row = (expanded_R >> (6 * (7 - i))) & 0x3;
        int col = (expanded_R >> (6 * (7 - i))) & 0xF;
        result |= S[i][row][col] << (4 * (7 - i));
    }

    return result;  // Return substituted and permuted value
}

// DES rounds (simplified)
uint64_t des_rounds(uint64_t block, uint64_t *round_keys) {
    uint32_t L = block >> 32;  // Left half
    uint32_t R = block & 0xFFFFFFFF;  // Right half

    for (int i = 0; i < 16; i++) {
        uint32_t tmp = R;
        R = L ^ f(R, round_keys[i]);  // Apply the F function and XOR with left half
        L = tmp;  // Swap halves
    }

    return ((uint64_t)R << 32) | L;  // Final swapped halves
}

// Key scheduling (simplified key generation for 16 rounds)
void generate_round_keys(uint64_t key, uint64_t *round_keys) {
    for (int i = 0; i < 16; i++) {
        round_keys[i] = key ^ (i + 1);  // Simplified round key derivation
    }
}

// DES encryption
uint64_t des_encrypt(uint64_t block, uint64_t key) {
    uint64_t round_keys[16];
    block = permute(block, IP, BLOCK_SIZE);  // Initial permutation
    generate_round_keys(key, round_keys);
    block = des_rounds(block, round_keys);   // Apply 16 DES rounds
    return permute(block, FP, BLOCK_SIZE);   // Final permutation
}

// DES decryption
uint64_t des_decrypt(uint64_t block, uint64_t key) {
    uint64_t round_keys[16];
    block = permute(block, IP, BLOCK_SIZE);  // Initial permutation
    generate_round_keys(key, round_keys);
    for (int i = 0; i < 8; i++) {  // Reverse the round key order for decryption
        uint64_t temp = round_keys[i];
        round_keys[i] = round_keys[15 - i];
        round_keys[15 - i] = temp;
    }
    block = des_rounds(block, round_keys);   // Apply 16 DES rounds
    return permute(block, FP, BLOCK_SIZE);   // Final permutation
}

int main() {
    // Example 64-bit block and 56-bit key (simplified)
    uint64_t plaintext = 0x123456789ABCDEF0;
    uint64_t key = 0x0F1571C947D9E859;

    printf("Plaintext:  %016llX\n", plaintext);

    // Encrypt
    uint64_t ciphertext = des_encrypt(plaintext, key);
    printf("Ciphertext: %016llX\n", ciphertext);

    // Decrypt
    uint64_t decrypted = des_decrypt(ciphertext, key);
    printf("Decrypted:  %016llX\n", decrypted);

    return 0;
}
