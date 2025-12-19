#ifndef SOLVER_H
#define SOLVER_H

#include "wordlist.h"

extern int is_possible[MAX_WORDS];

void init_solver(int count);
void filter_words(const char *guess, const char *target, int count, char words[][WORD_LEN+1]);
void get_best_guess(char *best_guess, char words[][WORD_LEN+1], int count);

#endif