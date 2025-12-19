#include "solver.h"
#include <string.h>
#include <stdbool.h>

int is_possible[MAX_WORDS];

void init_solver(int count) {
    for (int i = 0; i < count; i++) is_possible[i] = 1;
}

// Fonction interne pour simuler le feedback sans l'afficher
void get_feedback_logic(const char *guess, const char *target, int *status) {
    int freq[26] = {0};
    for(int i=0; i<5; i++) status[i] = 0;
    for(int i=0; i<5; i++) {
        if(guess[i] == target[i]) status[i] = 2;
        else freq[target[i]-'a']++;
    }
    for(int i=0; i<5; i++) {
        if(status[i] == 0 && freq[guess[i]-'a'] > 0) {
            status[i] = 1;
            freq[guess[i]-'a']--;
        }
    }
}

// Stratégie d'élimination
void filter_words(const char *guess, const char *target, int count, char words[][WORD_LEN+1]) {
    int feedback[5];
    get_feedback_logic(guess, target, feedback);

    for (int i = 0; i < count; i++) {
        if (is_possible[i]) {
            int temp_feedback[5];
            get_feedback_logic(guess, words[i], temp_feedback);
            
            for(int j=0; j<5; j++) {
                if (temp_feedback[j] != feedback[j]) {
                    is_possible[i] = 0;
                    break;
                }
            }
        }
    }
}

// Choix du mot : ici on prend le premier disponible (on peut améliorer par fréquence)
void get_best_guess(char *best_guess, char words[][WORD_LEN+1], int count) {
    for (int i = 0; i < count; i++) {
        if (is_possible[i]) {
            strcpy(best_guess, words[i]);
            return;
        }
    }
}