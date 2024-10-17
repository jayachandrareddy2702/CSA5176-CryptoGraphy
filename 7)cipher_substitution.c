#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 1000

// Function to perform frequency analysis
void frequencyAnalysis(char *ciphertext) {
    int freq[256] = {0}; // Frequency array for ASCII characters
    
    // Calculate frequencies of each character
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isprint(ciphertext[i])) {  // Consider only printable characters
            freq[(unsigned char)ciphertext[i]]++;
        }
    }
    
    // Print frequencies of each character
    printf("Character Frequencies:\n");
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            printf("'%c' : %d\n", i, freq[i]);
        }
    }
}

// Function to substitute characters based on user input
void substitute(char *ciphertext, char *substitutions) {
    char plaintext[MAX];
    
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isprint(ciphertext[i])) {
            // Substitute based on the provided mapping
            plaintext[i] = substitutions[(unsigned char)ciphertext[i]];
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';  // Null-terminate the string

    printf("\nSubstituted Text:\n%s\n", plaintext);
}

int main() {
    // The ciphertext to be decrypted
    char ciphertext[] = "53‡‡†305))6*:4826)4‡.)4‡):806*;48+860))85::]8*::*8+83 (88)5*†:46(:88*96*?:8)*†(;485);5*†2:*‡(:4956*2(5*-4)88*4069285);)6+8)4‡‡:1($9:48081;8:81:48†85:4)485†528806*81 ($9:48:(88;4(1734:48)4;161;:188;?;";

    printf("Ciphertext:\n%s\n", ciphertext);
    
    // Perform frequency analysis
    frequencyAnalysis(ciphertext);
    
    // Define the substitution array (initially identity mapping)
    char substitutions[256];
    for (int i = 0; i < 256; i++) {
        substitutions[i] = i;  // Identity mapping (ciphertext to itself)
    }
    
    // Example: manually substitute some characters as guessed
    // Let's assume ‡ -> e, 5 -> t, 3 -> h
    substitutions['‡'] = 'e';
    substitutions['5'] = 't';
    substitutions['3'] = 'h';
    
    // Perform substitution based on guessed characters
    substitute(ciphertext, substitutions);
    
    return 0;
}
