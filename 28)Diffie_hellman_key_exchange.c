#include <stdio.h>
#include <math.h>

// Function to perform modular exponentiation
long long modExp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

int main() {
    long long p, g, a, b, A, B, sharedKeyA, sharedKeyB;

    // Publicly agreed upon prime p and base g
    p = 23;  // Example prime number
    g = 5;   // Example base

    // Alice's private key (secret)
    a = 6;   // Example secret key

    // Bob's private key (secret)
    b = 15;  // Example secret key

    // Calculate public values A and B
    A = modExp(g, a, p);
    B = modExp(g, b, p);

    // Calculate shared keys
    sharedKeyA = modExp(B, a, p);  // Alice calculates the shared key
    sharedKeyB = modExp(A, b, p);  // Bob calculates the shared key

    // Display the results
    printf("Alice's Public Value (A): %lld\n", A);
    printf("Bob's Public Value (B): %lld\n", B);
    printf("Shared Key computed by Alice: %lld\n", sharedKeyA);
    printf("Shared Key computed by Bob: %lld\n", sharedKeyB);

    return 0;
}
