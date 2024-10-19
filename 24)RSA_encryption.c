#include <stdio.h>

// Function to compute gcd using the extended Euclidean algorithm
int extended_gcd(int a, int b, int *x, int *y) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }
    
    int x1, y1;
    int gcd = extended_gcd(b % a, a, &x1, &y1);

    *x = y1 - (b / a) * x1;
    *y = x1;

    return gcd;
}

// Function to find modular inverse of e mod phi
int mod_inverse(int e, int phi) {
    int x, y;
    int gcd = extended_gcd(e, phi, &x, &y);
    
    // Make sure x is positive
    if (x < 0) x += phi;

    return x;
}

int main() {
    int n = 3599;
    int e = 31;
    
    // Step 1: Find p and q (prime factors of n)
    int p = 59;  // Trial and error
    int q = 61;  // Trial and error

    // Step 2: Compute φ(n) = (p - 1) * (q - 1)
    int phi_n = (p - 1) * (q - 1);

    // Step 3: Compute the private key d (modular inverse of e mod φ(n))
    int d = mod_inverse(e, phi_n);

    // Output the private key
    printf("Private key d = %d\n", d);

    return 0;
}
