#include "game.h"
#include <stdio.h>
#include <ctype.h>

/* Terminal colors */
#define COL_RESET "\x1b[0m"
#define COL_GREEN  "\x1b[42;30m"
#define COL_YELLOW "\x1b[43;30m"
#define COL_GRAY   "\x1b[47;30m"

/*
 * Print color feedback like Wordle:
 * - green = right letter, right place
 * - yellow = right letter, wrong place
 * - gray = not present
 */
void print_feedback(const char *guess, const char *target) {
    char status[WORD_LEN] = {0};
    int freq[26] = {0};

    // First pass: green
    for (int i = 0; i < WORD_LEN; i++) {
        if (guess[i] == target[i]) status[i] = 2;
    }

    // Count remaining target letters
    for (int i = 0; i < WORD_LEN; i++) {
        if (status[i] != 2)
            freq[target[i] - 'a']++;
    }

    // Second pass: yellow
    for (int i = 0; i < WORD_LEN; i++) {
        if (status[i] == 0) {
            int idx = guess[i] - 'a';
            if (freq[idx] > 0) {
                status[i] = 1;
                freq[idx]--;
            }
        }
    }

    // Print result
    for (int i = 0; i < WORD_LEN; i++) {
        if (status[i] == 2)
            printf(COL_GREEN " %c " COL_RESET, toupper(guess[i]));
        else if (status[i] == 1)
            printf(COL_YELLOW " %c " COL_RESET, toupper(guess[i]));
        else
            printf(COL_GRAY " %c " COL_RESET, toupper(guess[i]));
    }

    printf("\n");
}