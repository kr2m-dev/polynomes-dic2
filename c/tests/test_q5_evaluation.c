/**
 * @file test_q5_evaluation.c
 * @brief Tests pour l'évaluation (Q5)
 * @details Vérifie que eval() calcule correctement P(x)
 * 
 * Commande: gcc -o test_q5 test_q5_evaluation.c ../src/polynome.c -I../include -lm && ./test_q5
 */

#include <stdio.h>
#include <math.h>
#include "../include/polynome.h"

int tests_reussis = 0;
int tests_total = 0;

typedef struct {
    const char* expression;
    double x;
    double attendu;
    const char* nom;
} TestEval;

void test_evaluation(const char* expression, double x, double attendu, const char* nom) {
    tests_total++;
    printf("Test %d: %s\n", tests_total, nom);
    printf("  Expression: \"%s\", x = %.2f\n", expression, x);
    
    POINTEUR p = analyserPolynome((char*)expression);
    double resultat = eval(p, x);
    
    printf("  Résultat:   %.4f\n", resultat);
    printf("  Attendu:    %.4f\n", attendu);
    
    /* Tolérance pour les flottants */
    if (fabs(resultat - attendu) < 0.001) {
        printf("  ✓ Test réussi\n\n");
        tests_reussis++;
    } else {
        printf("  ✗ Test ÉCHOUÉ\n\n");
    }
    
    ajouterPolyUtile(p);
}

int main() {
    printf("========================================\n");
    printf("  TESTS Q5: ÉVALUATION\n");
    printf("========================================\n\n");
    
    /* Tests simples */
    test_evaluation("3X^2 + 2X - 1", 2.0, 15.0, "P(2) = 3*4 + 2*2 - 1 = 15");
    test_evaluation("X", 5.0, 5.0, "P(X)=X en x=5");
    test_evaluation("10", 100.0, 10.0, "Constante 10");
    test_evaluation("X^2", 3.0, 9.0, "X^2 en x=3");
    
    /* Tests avec valeurs négatives */
    test_evaluation("X + 1", -1.0, 0.0, "X+1 en x=-1");
    test_evaluation("2X^2 - 3X + 1", 0.0, 1.0, "En x=0 (termes nuls)");
    test_evaluation("2X^2 - 3X + 1", 1.0, 0.0, "En x=1");
    test_evaluation("2X^2 - 3X + 1", 2.0, 3.0, "En x=2 : 8-6+1=3");
    
    /* Tests avec flottants */
    test_evaluation("X^2", 1.5, 2.25, "X^2 en x=1.5");
    test_evaluation("0.5X + 1", 4.0, 3.0, "0.5X + 1 en x=4");
    
    printf("========================================\n");
    printf("  RÉSULTATS: %d/%d tests réussis\n", tests_reussis, tests_total);
    printf("========================================\n");
    
    return (tests_reussis == tests_total) ? 0 : 1;
}
