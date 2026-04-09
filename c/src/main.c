/**
 * @file main.c
 * @brief Programme de test - Questions 1, 2, 3 (Analyseur, Codage, Affichage)
 * @details Ce fichier teste les fonctionnalités de base:
 *          - Q1: Analyseur syntaxique
 *          - Q2: Codage en mémoire (insertion ordonnée)
 *          - Q3: Affichage formaté
 * 
 * Ce fichier servira de base pour vos camarades qui implémenteront
 * les questions 4, 5, 6 (évaluation, opérations arithmétiques, GC)
 */

#include <stdio.h>
#include "../include/polynome.h"

int main() {
    printf("========================================\n");
    printf("  TEST Q1, Q2, Q3: Analyseur Syntaxique\n");
    printf("         Codage et Affichage\n");
    printf("========================================\n\n");

    /* ============================================================
     * QUESTION 1: Analyseur Syntaxique
     * Grammaire: polynôme → ['-'] monôme { ('+' | '-') monôme }
     * Test de reconnaissance de différentes expressions
     * ============================================================ */
    printf("--- QUESTION 1: Analyseur Syntaxique ---\n\n");

    char *expressions[] = {
        "3*X^2 + 2*X - 1",        // Polymôme complet
        "-X^3 + 5*X^2 + 4",       // Signe négatif initial
        "10",                      // Constante
        "X",                       // X simple
        "X^5",                     // Puissance seule
        "-2*X^2",                  // Coefficient négatif
        "4*X + 5",                // Expression simple
        "2*X^2 + 3*X",            // Exposants différents
        "0",                       // Polymôme nul
        NULL                       // Marqueur de fin
    };

    /* ============================================================
     * QUESTION 2: Codage en mémoire
     * Les polynômes sont stockés sous forme de listes chaînées
     * ordonnées par exposant décroissant
     * ============================================================ */
    printf("--- QUESTION 2: Codage en mémoire ---\n");
    printf("Stockage sous forme de liste chaînée (exposant décroissant)\n\n");

    /* ============================================================
     * QUESTION 3: Affichage
     * Affichage formaté des polynômes analysés
     * ============================================================ */
    printf("--- QUESTION 3: Affichage formaté ---\n\n");

    POINTEUR polynomes[10];
    int i = 0;
    
    while (expressions[i] != NULL) {
        printf("Expression %d: \"%s\"\n", i+1, expressions[i]);
        
        // Q1 + Q2: Analyse et codage
        polynomes[i] = analyserPolynome(expressions[i]);
        
        printf("Polynôme  %d: \"", i+1);
        // Q3: Affichage
        afficherPolynome(polynomes[i]);
        printf("\"\n\n");
        
        i++;
    }

    /* ============================================================
     * QUESTION 4: Évaluation
     * Test de eval() sur P1(X) = 3X^2 + 2X - 1 avec x = 2
     * Résultat attendu: 15
     * ============================================================ */
    printf("--- QUESTION 4: Évaluation ---\n\n");
    if (polynomes[0] != NULL) {
        double x = 2.0;
        double valeur = eval(polynomes[0], x);
        printf("P1(x) = \"");
        afficherPolynome(polynomes[0]);
        printf("\"\n");
        printf("P1(%.1f) = %.2f \n\n", x, valeur);
    } else {
        printf("Erreur: polynomes[0] est NULL\n\n");
    }

    printf("========================================\n");
    printf("  Questions 1, 2, 3: COMPLÉTÉES ✓\n");
    printf("========================================\n\n");

    printf("Prochaines étapes pour vos camarades:\n");
    printf("→ Q4 (Telecom): Implémenter eval() pour évaluer P(x)\n");
    printf("→ Q5a (IABD 2): Implémenter plus() pour addition\n");
    printf("→ Q5b (IABD 2): Implémenter moins() pour soustraction\n");
    printf("→ Q5c (SysSec 1): Implémenter fois() pour multiplication\n");
    printf("→ Q5d (SysSec 1): Implémenter quotient() pour division\n");
    printf("→ Q6 (SysSec 2): Implémenter le Garbage Collector\n");

    return 0;
}
