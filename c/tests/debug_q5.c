/**
 * @file debug_q5.c
 * @brief Debug pour Q5 - Évaluation
 */

#include <stdio.h>
#include <string.h>
#include <math.h>
#include "../include/polynome.h"

void debug_afficher_structure(POINTEUR p, const char* nom) {
    printf("  Structure %s:\n", nom);
    int i = 0;
    while (p != NULL) {
        printf("    [%d] coeff=%.2f, exposant=%d, suivant=%p\n", 
               i, p->coeff, p->exposant, (void*)p->suivant);
        p = p->suivant;
        i++;
    }
    if (i == 0) printf("    (vide)\n");
}

int main() {
    printf("========================================\n");
    printf(" DEBUG Q5: ÉVALUATION\n");
    printf("========================================\n\n");

    /* Test: P(X) = 3X^2 + 2X - 1, P(2) = ? */
    printf("Test: P(X) = 3X^2 + 2X - 1\n");
    printf("Attendu: P(2) = 3*4 + 2*2 - 1 = 15\n\n");
    
    POINTEUR p = analyserPolynome("3X^2 + 2X - 1");
    
    printf("Après parsing:\n");
    debug_afficher_structure(p, "P");
    
    printf("\nAffichage du polynôme: \"");
    afficherPolynome(p);
    printf("\"\n\n");
    
    double resultat = eval(p, 2.0);
    printf("Résultat eval(p, 2.0) = %.4f\n", resultat);
    printf("Attendu: 15.0000\n");
    
    if (fabs(resultat - 15.0) < 0.001) {
        printf("\n✓ Test RÉUSSI\n");
    } else {
        printf("\n✗ Test ÉCHOUÉ\n");
    }

    return 0;
}
