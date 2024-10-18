#include <stdio.h>
#include <stdint.h>

// Function to generate custom DES subkeys
void generate_custom_keys(uint64_t key, uint64_t subkeys[16]) {
    // Split the 56-bit key into two 28-bit halves
    uint32_t left = (key >> 28) & 0xFFFFFFF;  // Left 28 bits
    uint32_t right = key & 0xFFFFFFF;         // Right 28 bits
    
    for (int i = 0; i < 16; i++) {
        // Perform left circular shifts on both halves (1 or 2 shifts depending on round)
        int shift_amount = (i == 0 || i == 1 || i == 8 || i == 15) ? 1 : 2;
        left = ((left << shift_amount) | (left >> (28 - shift_amount))) & 0xFFFFFFF;
        right = ((right << shift_amount) | (right >> (28 - shift_amount))) & 0xFFFFFFF;

        // First 24 bits of the subkey come from the left 28-bit half
        uint64_t subkey_left_part = left >> 4;  // Use the top 24 bits of left half
        
        // Second 24 bits of the subkey come from the right 28-bit half
        uint64_t subkey_right_part = right >> 4;  // Use the top 24 bits of right half
        
        // Combine to form a 48-bit subkey (we only need 48 bits for DES subkeys)
        subkeys[i] = (subkey_left_part << 24) | subkey_right_part;
    }
}

int main() {
    uint64_t key = 0x133457799BBCDFF1;  // Example 64-bit key (after dropping parity bits, it will be 56-bit)
    uint64_t subkeys[16];  // Array to hold the 16 subkeys

    // Generate custom subkeys
    generate_custom_keys(key, subkeys);

    // Print the generated subkeys
    for (int i = 0; i < 16; i++) {
        printf("Subkey %d: %012llx\n", i + 1, subkeys[i]);
    }

    return 0;
}
