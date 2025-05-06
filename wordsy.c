#include <stdio.h>

#define WORD_LEN 5
#define MAX_GUESSES 6

int read_mystery_word(char word[]);
int string_length(const char str[]);
void to_lower_case(char str[]);
int is_valid_guess(const char guess[]);
void get_user_guess(char guess[]);
int is_correct_guess(const char guess[], const char word[]);
void print_all_guesses(char guesses[][WORD_LEN + 1], int count, const char word[]);

int main() {
    char mystery_word[WORD_LEN + 1];
    if (!read_mystery_word(mystery_word)) {
        return 1;
    }

    char guesses[MAX_GUESSES][WORD_LEN + 1];
    int guess_count = 0;

    while (guess_count < MAX_GUESSES) {
        char guess[WORD_LEN + 2]; // +1 for null, +1 for potential newline
        get_user_guess(guess);
        to_lower_case(guess);

        if (!is_valid_guess(guess)) {
            printf("Invalid guess. Make sure it's 5 letters and alphabetic.\n");
            continue;
        }

        // Store guess
        for (int i = 0; i < WORD_LEN; i++) {
            guesses[guess_count][i] = guess[i];
        }
        guesses[guess_count][WORD_LEN] = '\0';
        guess_count++;

        print_all_guesses(guesses, guess_count, mystery_word);

        if (is_correct_guess(guess, mystery_word)) {
            printf("Congratulations! You guessed the word!\n");
            return 0;
        }
    }

    printf("Sorry, you've run out of guesses. The word was: %s\n", mystery_word);
    return 0;
}

// Read word from file
int read_mystery_word(char word[]) {
    FILE *file = fopen("word.txt", "r");
    if (!file) {
        printf("Failed to open word.txt\n");
        return 0;
    }
    fscanf(file, "%5s", word);
    fclose(file);
    return 1;
}

// Custom strlen
int string_length(const char str[]) {
    int len = 0;
    while (str[len] != '\0') len++;
    return len;
}

// Convert to lowercase
void to_lower_case(char str[]) {
    for (int i = 0; i < WORD_LEN; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] - 'A' + 'a';
        }
    }
}

// Check if valid 5-letter alphabetic string
int is_valid_guess(const char guess[]) {
    for (int i = 0; i < WORD_LEN; i++) {
        char c = guess[i];
        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')))
            return 0;
    }
    return guess[WORD_LEN] == '\0';
}

// Get user input
void get_user_guess(char guess[]) {
    printf("Enter your guess: ");
    scanf("%5s", guess);
    while (getchar() != '\n'); // flush input
}

// Check for exact match
int is_correct_guess(const char guess[], const char word[]) {
    for (int i = 0; i < WORD_LEN; i++) {
        if (guess[i] != word[i])
            return 0;
    }
    return 1;
}

// Show guesses and ^ indicators
void print_all_guesses(char guesses[][WORD_LEN + 1], int count, const char word[]) {
    for (int i = 0; i < count; i++) {
        char *guess = guesses[i];

        // Print guess with correct letters capitalized
        for (int j = 0; j < WORD_LEN; j++) {
            if (guess[j] == word[j]) {
                if (guess[j] >= 'a' && guess[j] <= 'z')
                    printf("%c", guess[j] - 'a' + 'A');
                else
                    printf("%c", guess[j]);
            } else {
                printf("%c", guess[j]);
            }
        }
        printf("\n");

        // Print ^ under misplaced but correct letters
        for (int j = 0; j < WORD_LEN; j++) {
            if (guess[j] != word[j]) {
                int found = 0;
                for (int k = 0; k < WORD_LEN; k++) {
                    if (guess[j] == word[k] && guess[k] != word[k]) {
                        found = 1;
                        break;
                    }
                }
                printf(found ? "^" : " ");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

