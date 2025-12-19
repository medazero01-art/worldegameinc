#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <time.h>
#include "wordlist.h"
#include "game.h"
#include "solver.h"

int main() {
    char words[MAX_WORDS][WORD_LEN+1];
    int count = load_words(words, "words.txt");
    
    if (count == 0) return 1;

    // Choisir un mot secret au hasard pour le test
    srand(time(NULL));
    char *target = words[rand() % count];
    
    char guess[6];
    printf("--- MODE AUTOMATIQUE : TROUVER [%s] ---\n", target);

    init_solver(count);

    for (int attempt = 1; attempt <= 6; attempt++) {
        get_best_guess(guess, words, count);
        printf("Tentative %d: Le robot propose [%s] -> ", attempt, guess);
        
        // Utilise ta fonction existante pour l'affichage couleur
        print_feedback(guess, target); 

        if (strcmp(guess, target) == 0) {
            printf("\nSUCCÈS : Trouvé en %d coups !\n", attempt);
            return 0;
        }

        filter_words(guess, target, count, words);
    }

    printf("\nÉCHEC : Le robot n'a pas trouvé le mot.\n");
    return 0;
}