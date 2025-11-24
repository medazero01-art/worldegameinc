#include "wordlist.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/*
 * Load all 5-letter words from dictionary file (words.txt).
 * Returns number of words loaded.
 */
int load_words(char words[][WORD_LEN+1], const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        fprintf(stderr, "Error: cannot open %s\n", filename);
        return 0;
    }

    int count = 0;
    char line[256];

    while (fgets(line, sizeof(line), f) && count < MAX_WORDS) {
        int len = strlen(line);

        // Trim newline
        if (len > 0 && line[len-1] == '\n') {
            line[len-1] = '\0';
            len--;
        }

        // Must be exactly 5 letters
        if (len != WORD_LEN) continue;

        int ok = 1;
        for (int i = 0; i < WORD_LEN; i++) {
            if (!isalpha((unsigned char)line[i])) {
                ok = 0;
                break;
            }
        }

        if (!ok) continue;

        // Convert to lowercase
        for (int i = 0; i < WORD_LEN; i++)
            line[i] = tolower((unsigned char)line[i]);

        line[WORD_LEN] = '\0';
        strcpy(words[count++], line);
    }

    fclose(f);
    return count;
}

/*
 * Check if guess is valid and exists in dictionary.
 */
int is_valid_guess(const char *guess, char words[][WORD_LEN+1], int word_count) {
    if ((int)strlen(guess) != WORD_LEN) return 0;

    for (int i = 0; i < WORD_LEN; i++)
        if (!isalpha((unsigned char)guess[i]))
            return 0;

    char g[WORD_LEN+1];
    for (int i = 0; i < WORD_LEN; i++)
        g[i] = tolower((unsigned char)guess[i]);
    g[WORD_LEN] = '\0';

    for (int i = 0; i < word_count; i++)
        if (strcmp(words[i], g) == 0)
            return 1;

    return 0;
}