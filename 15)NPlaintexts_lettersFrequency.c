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

// Function to convert a character to lowercase and check if it's a letter
int isValidChar(char c) {
    return isalpha(c);
}

// Function to decrypt using a given shift
void decryptWithShift(char *ciphertext, int shift, char *result) {
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i++) {
        if (isValidChar(ciphertext[i])) {
            char base = islower(ciphertext[i]) ? 'a' : 'A';
            result[i] = ((ciphertext[i] - base - shift + ALPHABET_SIZE) % ALPHABET_SIZE) + base;
        } else {
            result[i] = ciphertext[i];
        }
    }
    result[len] = '\0';
}

// Function to calculate the frequency of letters in the text
void calculateFrequencies(char *text, double *frequencies) {
    int letterCount[ALPHABET_SIZE] = {0};
    int totalLetters = 0;

    // Count letters in the text
    for (int i = 0; i < strlen(text); i++) {
        if (isValidChar(text[i])) {
            letterCount[tolower(text[i]) - 'a']++;
            totalLetters++;
        }
    }

    // Calculate the frequency percentages
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        frequencies[i] = (double)letterCount[i] / totalLetters * 100.0;
    }
}

// Function to calculate the score for a given shift (closer to English frequencies is better)
double scoreDecryption(char *decryptedText) {
    double frequencies[ALPHABET_SIZE] = {0};
    calculateFrequencies(decryptedText, frequencies);

    double score = 0.0;
    // Compare frequencies to standard English frequencies
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        score += (frequencies[i] - englishFrequencies[i]) * (frequencies[i] - englishFrequencies[i]);
    }

    return score; // Lower score means it's closer to English letter frequencies
}

// Function to perform frequency attack and return the top N most likely plaintexts
void frequencyAttack(char *ciphertext, int topN) {
    char decryptedText[1000];
    double scores[ALPHABET_SIZE];
    int bestShifts[ALPHABET_SIZE];

    // Try all possible shifts and calculate the scores
    for (int shift = 0; shift < ALPHABET_SIZE; shift++) {
        decryptWithShift(ciphertext, shift, decryptedText);
        scores[shift] = scoreDecryption(decryptedText);
        bestShifts[shift] = shift;
    }

    // Sort shifts based on their score
    for (int i = 0; i < ALPHABET_SIZE - 1; i++) {
        for (int j = i + 1; j < ALPHABET_SIZE; j++) {
            if (scores[i] > scores[j]) {
                double tempScore = scores[i];
                scores[i] = scores[j];
                scores[j] = tempScore;

                int tempShift = bestShifts[i];
                bestShifts[i] = bestShifts[j];
                bestShifts[j] = tempShift;
            }
        }
    }

    // Output the top N most likely plaintexts
    printf("Top %d most likely plaintexts:\n", topN);
    for (int i = 0; i < topN && i < ALPHABET_SIZE; i++) {
        decryptWithShift(ciphertext, bestShifts[i], decryptedText);
        printf("Shift %d: %s\n", bestShifts[i], decryptedText);
    }
}

int main() {
    char ciphertext[1000];
    int topN;

    // Input the ciphertext and number of top results the user wants
    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0'; // Remove newline character from input

    printf("Enter the number of top likely plaintexts to show: ");
    scanf("%d", &topN);

    // Perform frequency attack
    frequencyAttack(ciphertext, topN);

    return 0;
}
