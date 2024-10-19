#include <stdio.h>
#include <stdlib.h>

// Function to compute GCD (Greatest Common Divisor)
unsigned long long gcd(unsigned long long a, unsigned long long b) {
    while (b != 0) {
        unsigned long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to compute modular inverse (used to compute private key 'd')
unsigned long long mod_inverse(unsigned long long e, unsigned long long phi) {
    unsigned long long t = 0, new_t = 1;
    unsigned long long r = phi, new_r = e;

    while (new_r != 0) {
        unsigned long long quotient = r / new_r;
        unsigned long long temp_t = t - quotient * new_t;
        unsigned long long temp_r = r - quotient * new_r;
        
        t = new_t;
        new_t = temp_t;
        r = new_r;
        new_r = temp_r;
    }

    return (t + phi) % phi;  // Ensure positive value
}

int main() {
    // Simulated RSA values (example primes and modulus)
    unsigned long long p = 61;
    unsigned long long q = 53;
    unsigned long long n = p * q;
    unsigned long long phi = (p - 1) * (q - 1);
    
    unsigned long long e = 17;  // Public exponent
    unsigned long long d = mod_inverse(e, phi);  // Private key

    printf("Original public key e: %llu\n", e);
    printf("Original private key d: %llu\n", d);

    // Simulate a new public key generation (after private key leak)
    unsigned long long e_new = 19;  // New public key exponent
    unsigned long long d_new = mod_inverse(e_new, phi);  // New private key

    printf("New public key e': %llu\n", e_new);
    printf("New private key d': %llu\n", d_new);

    // Explaining the vulnerability: An attacker with d can compute phi
    unsigned long long known_phi = (e * d - 1) / e;
    printf("Attacker can compute phi(n): %llu\n", known_phi);

    return 0;
}
