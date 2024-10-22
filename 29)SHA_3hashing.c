#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 5
#define COLS 5
#define LANES ROWS * COLS   // 25 lanes
#define CAPACITY_LANES 8    // Last 8 lanes for capacity
#define RATE_LANES (LANES - CAPACITY_LANES) // First 17 lanes for rate
#define NONZERO 0x1ULL      // Example nonzero bit (can be randomized if needed)

// Function to check if all lanes have at least one nonzero bit
int all_lanes_nonzero(uint64_t state[LANES]) {
    for (int i = 0; i < LANES; i++) {
        if (state[i] == 0) {
            return 0; // Found a lane with only zeros
        }
    }
    return 1; // All lanes have nonzero bits
}

int main() {
    uint64_t state[LANES] = {0};  // Initialize all lanes to zero (capacity part is zero)
    
    // Simulate the message block P0 where all lanes in the rate have at least one nonzero bit
    srand(time(NULL));  // Seed the random number generator
    
    // Fill the rate portion with nonzero values
    for (int i = 0; i < RATE_LANES; i++) {
        state[i] = NONZERO | (rand() % 0xFFFFFFFFFFFFFFFF);  // Insert nonzero bits randomly
    }

    // Keep track of iterations until all lanes have at least one nonzero bit
    int iterations = 0;

    // Iterate until all lanes are nonzero
    while (!all_lanes_nonzero(state)) {
        iterations++;

        // Update capacity lanes with some nonzero value (simulating input over time)
        for (int i = RATE_LANES; i < LANES; i++) {
            if (state[i] == 0) {  // Only modify if it's still zero
                state[i] = NONZERO | (rand() % 0xFFFFFFFFFFFFFFFF);  // Add nonzero bits
            }
        }

        // You can print the state matrix for debugging purposes
        // printf("Iteration %d:\n", iterations);
        // for (int i = 0; i < LANES; i++) {
        //     printf("Lane[%d]: %llu\n", i, state[i]);
        // }
    }

    printf("It took %d iterations for all lanes to have at least one nonzero bit.\n", iterations);

    return 0;
}
