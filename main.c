#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#include "wordlist.h"
#include "game.h"

#define MAX_ATTEMPTS 6
#define DICT_FILE "words.txt"

int main(void) {
    char words[MAX_WORDS][WORD_LEN+1];

    int count = load_words(words, DICT_FILE);
    if (count == 0) {
        printf("Error: no words loaded.\n");
        return 1;
    }

    srand(time(NULL));
    const char *target = words[rand() % count];

    char guess[256];

    printf("Welcome to Wordle in C.\n");

    for (int attempt = 1; attempt <= MAX_ATTEMPTS; attempt++) {
        printf("\nAttempt %d/%d: ", attempt, MAX_ATTEMPTS);

        fgets(guess, sizeof(guess), stdin);

        guess[strcspn(guess, "\n")] = 0;

        if (!is_valid_guess(guess, words, count)) {
            printf("Invalid guess.\n");
            attempt--;
            continue;
        }

        char g[WORD_LEN+1];
        for (int i = 0; i < WORD_LEN; i++)
            g[i] = tolower(guess[i]);
        g[WORD_LEN] = '\0';

        print_feedback(g, target);

        if (strcmp(g, target) == 0) {
            printf("\nYou win!\n");
            return 0;
        }
    }

    printf("\nYou lost. The word was: %s\n", target);
    return 0;
}