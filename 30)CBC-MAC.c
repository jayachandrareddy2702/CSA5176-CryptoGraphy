#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Example Block Size and Key
#define BLOCK_SIZE 16  // 16 bytes (128 bits)
#define KEY_SIZE 16    // 16 bytes (128-bit key)

// Dummy AES encryption function (replace with actual AES encryption)
void AES_encrypt(uint8_t *input, uint8_t *key, uint8_t *output) {
    // Simple XOR-based encryption (for demonstration purposes)
    for (int i = 0; i < BLOCK_SIZE; i++) {
        output[i] = input[i] ^ key[i];
    }
}

// CBC-MAC function for one block
void CBC_MAC(uint8_t *message, uint8_t *key, uint8_t *mac) {
    uint8_t temp[BLOCK_SIZE];
    
    // Initial vector (IV) is zero for CBC-MAC
    memset(temp, 0, BLOCK_SIZE);
    
    // XOR message with IV (for first block)
    for (int i = 0; i < BLOCK_SIZE; i++) {
        temp[i] ^= message[i];
    }

    // Encrypt the result using AES (or another block cipher)
    AES_encrypt(temp, key, mac);
}

// XOR function for two blocks
void xor_blocks(uint8_t *block1, uint8_t *block2, uint8_t *result) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        result[i] = block1[i] ^ block2[i];
    }
}

int main() {
    uint8_t key[KEY_SIZE] = { /* Fill with key bytes */ };
    uint8_t X[BLOCK_SIZE] = { /* Fill with message block bytes */ };
    uint8_t T[BLOCK_SIZE];  // CBC-MAC of X (T = MAC(K, X))
    uint8_t X_XOR_T[BLOCK_SIZE];  // X ⊕ T
    uint8_t two_block_MAC[BLOCK_SIZE];  // MAC of two-block message
    
    // Step 1: Compute the CBC-MAC T for message X
    CBC_MAC(X, key, T);
    
    // Step 2: Compute (X ⊕ T)
    xor_blocks(X, T, X_XOR_T);
    
    // Step 3: Compute CBC-MAC of two-block message X || (X ⊕ T)
    // CBC-MAC of two-block message works as:
    // MAC(K, X || (X ⊕ T)) = E_K(E_K(IV ⊕ X) ⊕ (X ⊕ T))
    
    // Step 3.1: First block encryption (X)
    CBC_MAC(X, key, two_block_MAC);  // First block same as T
    
    // Step 3.2: XOR the result with the second block (X ⊕ T)
    xor_blocks(two_block_MAC, X_XOR_T, two_block_MAC);  // XOR with second block
    
    // Step 3.3: Encrypt the result again
    AES_encrypt(two_block_MAC, key, two_block_MAC);
    
    // Output the final two-block CBC-MAC
    printf("The CBC-MAC for the two-block message X || (X ⊕ T) is: ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02x", two_block_MAC[i]);
    }
    printf("\n");
    
    return 0;
}
