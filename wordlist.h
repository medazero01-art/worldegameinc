#ifndef WORDLIST_H
#define WORDLIST_H

#define WORD_LEN 5
#define MAX_WORDS 20000

int load_words(char words[][WORD_LEN+1], const char *filename);
int is_valid_guess(const char *guess, char words[][WORD_LEN+1], int word_count);

#endif