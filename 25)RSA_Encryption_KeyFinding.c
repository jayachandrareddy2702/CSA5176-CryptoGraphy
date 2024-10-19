#include <stdio.h>

// Function to calculate GCD of two numbers
unsigned long long gcd(unsigned long long a, unsigned long long b) {
    while (b != 0) {
        unsigned long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to calculate the modular inverse of e mod phi using the Extended Euclidean Algorithm
unsigned long long mod_inverse(unsigned long long e, unsigned long long phi) {
    unsigned long long t = 0, new_t = 1;
    unsigned long long r = phi, new_r = e;
    
    while (new_r != 0) {
        unsigned long long quotient = r / new_r;
        t = t - quotient * new_t;
        if (t < 0) t += phi;
        r = r - quotient * new_r;
    }
    
    if (r > 1) {
        printf("e is not invertible!\n");
        return 0;
    }
    return new_t;
}

int main() {
    unsigned long long n = 33;  // Example modulus n (small example for illustration)
    unsigned long long e = 3;    // Example public exponent e (small for illustration)
    unsigned long long block = 2; // Example plaintext block (small value for illustration)
    
    // Step 1: Calculate GCD of the block and n
    unsigned long long factor = gcd(block, n);

    // Step 2: Check if GCD is a non-trivial factor
    if (factor > 1 && factor < n) {
        printf("Non-trivial factor found: %llu\n", factor);
        
        // Step 3: Compute p and q
        unsigned long long p = factor;
        unsigned long long q = n / p;
        printf("p = %llu, q = %llu\n", p, q);
        
        // Step 4: Compute phi = (p-1)(q-1)
        unsigned long long phi = (p - 1) * (q - 1);

        // Step 5: Compute private key d as the modular inverse of e mod phi
        unsigned long long d = mod_inverse(e, phi);
        if (d != 0) {
            printf("Private key d found: %llu\n", d);
        } else {
            printf("Failed to compute private key!\n");
        }
    } else {
        printf("No common factor with n found.\n");
    }

    return 0;
}
