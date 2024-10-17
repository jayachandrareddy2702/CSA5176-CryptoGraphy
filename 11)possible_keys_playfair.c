#include <stdio.h>
#include <math.h>

// Function to calculate factorial of a number
unsigned long long factorial(int n) {
    unsigned long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

// Function to approximate a number as a power of 2
int approximatePowerOf2(unsigned long long number) {
    return (int)(log2(number) + 0.5); // Rounds to the nearest integer
}

int main() {
    int totalLetters = 25; // Playfair uses 25 letters (I and J combined)
    
    // Calculate 25!
    unsigned long long totalPermutations = factorial(totalLetters);

     // Calculate 5!
    unsigned long long rowColPermutations = factorial(5) * factorial(5);
    
    // Calculate effectively unique keys
    unsigned long long uniqueKeys = totalPermutations / rowColPermutations;

    // Approximate as a power of 2
    int powerOf2 = approximatePowerOf2(totalPermutations);

    // Approximate as a power of 2
    int powerOf2Unique = approximatePowerOf2(uniqueKeys);
    
    // Print results
    printf("Total possible Playfair keys (without considering identical results): %llu\n", totalPermutations);
    printf("Approximation as power of 2: 2^%d\n", powerOf2);
    printf("Effectively unique Playfair keys: %llu\n", uniqueKeys);
    printf("Approximation as power of 2: 2^%d\n", powerOf2Unique);
    
    return 0;
}
