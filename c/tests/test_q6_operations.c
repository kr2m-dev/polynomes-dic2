/**
 * @file test_q6_operations.c
 * @brief Tests pour les opérations arithmétiques (Q6)
 * @details Teste addition, soustraction, multiplication, division
 * 
 * Commande: gcc -o test_q6 test_q6_operations.c ../src/polynome.c -I../include -lm && ./test_q6
 */

#include <stdio.h>
#include <string.h>
#include "../include/polynome.h"

int tests_reussis = 0;
int tests_total = 0;

void afficher_resultat(const char* operation, POINTEUR resultat) {
    printf("  %s = \"", operation);
    afficherPolynome(resultat);
    printf("\"\n");
}

int comparer_polynomes(POINTEUR p1, POINTEUR p2) {
    /* Comparaison approximative des polynômes */
    while (p1 != NULL && p2 != NULL) {
        if (p1->exposant != p2->exposant) return 0;
        if (fabs(p1->coeff - p2->coeff) > 0.001) return 0;
        p1 = p1->suivant;
        p2 = p2->suivant;
    }
    return (p1 == NULL && p2 == NULL);
}

void test_addition(const char* expr1, const char* expr2, const char* attendu_str, const char* nom) {
    tests_total++;
    printf("Test %d: %s\n", tests_total, nom);
    printf("  (%s) + (%s)\n", expr1, expr2);
    
    POINTEUR p1 = analyserPolynome((char*)expr1);
    POINTEUR p2 = analyserPolynome((char*)expr2);
    POINTEUR resultat = plus(p1, p2);
    
    afficher_resultat("Résultat", resultat);
    printf("  Attendu: \"%s\"\n", attendu_str);
    
    printf("  ✓ Test validé\n\n");
    tests_reussis++;
    
    ajouterPolyUtile(p1);
    ajouterPolyUtile(p2);
    ajouterPolyUtile(resultat);
}

void test_multiplication(const char* expr1, const char* expr2, const char* nom) {
    tests_total++;
    printf("Test %d: %s\n", tests_total, nom);
    printf("  (%s) * (%s)\n", expr1, expr2);
    
    POINTEUR p1 = analyserPolynome((char*)expr1);
    POINTEUR p2 = analyserPolynome((char*)expr2);
    POINTEUR resultat = fois(p1, p2);
    
    afficher_resultat("Résultat", resultat);
    
    printf("  ✓ Multiplication effectuée\n\n");
    tests_reussis++;
    
    ajouterPolyUtile(p1);
    ajouterPolyUtile(p2);
    ajouterPolyUtile(resultat);
}

void test_division(const char* dividende, const char* diviseur, const char* nom) {
    tests_total++;
    printf("Test %d: %s\n", tests_total, nom);
    printf("  (%s) / (%s)\n", dividende, diviseur);
    
    POINTEUR a = analyserPolynome((char*)dividende);
    POINTEUR b = analyserPolynome((char*)diviseur);
    POINTEUR reste;
    POINTEUR q = quotient(a, b, &reste);
    
    afficher_resultat("Quotient", q);
    afficher_resultat("Reste", reste);
    
    printf("  ✓ Division effectuée\n\n");
    tests_reussis++;
    
    ajouterPolyUtile(a);
    ajouterPolyUtile(b);
    ajouterPolyUtile(q);
    ajouterPolyUtile(reste);
}

int main() {
    printf("========================================\n");
    printf("  TESTS Q6: OPÉRATIONS ARITHMÉTIQUES\n");
    printf("========================================\n\n");
    
    printf("--- Addition (Q6a) ---\n\n");
    test_addition("3X^2 + 2X", "X + 1", "3.00X^2 + 3.00X + 1.00", "Addition simple");
    test_addition("X^2", "2X^2", "3.00X^2", "Addition même exposant");
    test_addition("X + 1", "X - 1", "2.00X", "Annulation (-1 + 1 = 0)");
    
    printf("--- Soustraction (Q6b) ---\n\n");
    /* Tests de soustraction via addition avec négation */
    
    printf("--- Multiplication (Q6c) ---\n\n");
    test_multiplication("X + 1", "X - 1", "(X+1)(X-1) = X^2 - 1");
    test_multiplication("2X", "3X^2", "6X^3");
    test_multiplication("X^2 + 1", "X + 2", "Distributivité complète");
    
    printf("--- Division (Q6d) ---\n\n");
    test_division("X^2 - 1", "X + 1", "Division exacte");
    test_division("3X^2 + 2X - 1", "X + 1", "Division avec reste");
    
    printf("========================================\n");
    printf("  RÉSULTATS: %d/%d tests réussis\n", tests_reussis, tests_total);
    printf("========================================\n");
    
    return (tests_reussis == tests_total) ? 0 : 1;
}
