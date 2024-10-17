#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

// Standard English letter frequencies (in percentages)
double englishFrequencies[ALPHABET_SIZE] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 
    0.153, 0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987, 
    6.327, 9.056, 2.758, 0.978, 2.360, 0.150, 1.974, 0.074
};

// Function to check if a character is a valid letter
int isValidChar(char c) {
    return isalpha(c);
}

// Function to calculate letter frequencies in a given text
void calculateFrequencies(char *text, double *frequencies) {
    int letterCount[ALPHABET_SIZE] = {0};
    int totalLetters = 0;

    // Count occurrences of each letter
    for (int i = 0; i < strlen(text); i++) {
        if (isValidChar(text[i])) {
            letterCount[tolower(text[i]) - 'a']++;
            totalLetters++;
        }
    }

    // Calculate frequency percentages
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        frequencies[i] = (double)letterCount[i] / totalLetters * 100.0;
    }
}

// Function to score a decrypted text based on English letter frequency comparison
double scoreDecryption(double *frequencies) {
    double score = 0.0;

    // Calculate score based on the difference from standard English frequencies
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        score += (frequencies[i] - englishFrequencies[i]) * (frequencies[i] - englishFrequencies[i]);
    }

    return score; // Lower score means better match to English
}

// Function to map letters using a substitution key and decrypt the ciphertext
void decryptWithSubstitution(char *ciphertext, char *substitutionKey, char *result) {
    for (int i = 0; i < strlen(ciphertext); i++) {
        if (isValidChar(ciphertext[i])) {
            char base = islower(ciphertext[i]) ? 'a' : 'A';
            int index = tolower(ciphertext[i]) - 'a';
            result[i] = islower(ciphertext[i]) ? tolower(substitutionKey[index]) : toupper(substitutionKey[index]);
        } else {
            result[i] = ciphertext[i];  // Preserve spaces and non-letters
        }
    }
    result[strlen(ciphertext)] = '\0';
}

// Function to perform frequency attack on the ciphertext
void frequencyAttack(char *ciphertext, int topN) {
    char possiblePlaintext[1000];
    double ciphertextFrequencies[ALPHABET_SIZE];

    // Calculate frequencies of letters in the ciphertext
    calculateFrequencies(ciphertext, ciphertextFrequencies);

    // Generate possible substitution keys (for simplicity, we'll assume a static substitution key for now)
    char substitutionKeys[ALPHABET_SIZE][ALPHABET_SIZE] = {
        "etaoinshrdlcumwfgypbvkjxqz",  // 1st likely substitution key (for simplicity)
        "tnrhaeiousdlgcmfywbvkzqpjx",  // 2nd likely substitution key (random example)
        // ... (Additional substitution keys can be added)
    };

    int numSubstitutions = 2;  // Number of substitution keys provided (for demo)

    // Try all substitution keys
    for (int i = 0; i < numSubstitutions; i++) {
        // Decrypt the ciphertext using the substitution key
        decryptWithSubstitution(ciphertext, substitutionKeys[i], possiblePlaintext);

        // Output the decrypted text
        printf("Possible Plaintext using Key %d: %s\n", i + 1, possiblePlaintext);
    }
}

int main() {
    char ciphertext[1000];
    int topN;

    // Input the ciphertext and number of top plaintexts to display
    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0'; // Remove newline character

    printf("Enter the number of top likely plaintexts to show: ");
    scanf("%d", &topN);

    // Perform frequency attack
    frequencyAttack(ciphertext, topN);

    return 0;
}
