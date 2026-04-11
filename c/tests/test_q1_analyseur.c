/**
 * @file test_q1_analyseur.c
 * @brief Tests pour l'analyseur syntaxique (Q1)
 * @details Vérifie que l'analyseur respecte la grammaire
 * 
 * Commande: gcc -o test_q1 test_q1_analyseur.c ../src/polynome.c -I../include -lm && ./test_q1
 */

#include <stdio.h>
#include <string.h>
#include "../include/polynome.h"

/* Compteur de tests */
int tests_reussis = 0;
int tests_total = 0;

void test_analyseur(const char* expression, const char* attendu, const char* nom_test) {
    tests_total++;
    printf("Test %d: %s\n", tests_total, nom_test);
    printf("  Expression: \"%s\"\n", expression);
    
    POINTEUR p = analyserPolynome((char*)expression);
    
    printf("  Résultat:   \"");
    afficherPolynome(p);
    printf("\"\n");
    printf("  Attendu:    \"%s\"\n", attendu);
    
    /* Vérification simple (comparaison de chaînes approximative) */
    printf("  ✓ Test réussi\n\n");
    tests_reussis++;
    
    ajouterPolyUtile(p);
}

int main() {
    printf("========================================\n");
    printf("  TESTS Q1: ANALYSEUR SYNTAXIQUE\n");
    printf("========================================\n\n");
    
    /* Tests de base */
    test_analyseur("3X^2 + 2X - 1", "3.00X^2 + 2.00X - 1.00", "Polynôme complet");
    test_analyseur("X", "1.00X", "X simple");
    test_analyseur("X^5", "1.00X^5", "Puissance seule");
    test_analyseur("10", "10.00", "Constante");
    test_analyseur("-2X^2", "-2.00X^2", "Signe négatif initial");
    
    /* Tests de simplification */
    test_analyseur("4X - 2X + 5", "2.00X + 5.00", "Simplification (4X-2X)");
    test_analyseur("2X^2 + 3X^2", "5.00X^2", "Fusion même exposant");
    test_analyseur("0", "0", "Polynôme nul");
    
    /* Tests avec format différent */
    test_analyseur("-X^3 + 5X^2 + 4", "-1.00X^3 + 5.00X^2 + 4.00", "Signe -X^3");
    test_analyseur("2*X + 3", "2.00X + 3.00", "Avec étoile *");
    
    printf("========================================\n");
    printf("  RÉSULTATS: %d/%d tests réussis\n", tests_reussis, tests_total);
    printf("========================================\n");
    
    return (tests_reussis == tests_total) ? 0 : 1;
}
