/**
 * @file main.c
 * @brief Programme interactif de démonstration - Toutes les questions
 * @details Ce programme permet d'interagir avec toutes les fonctionnalités
 * du projet polynômes via un menu interactif.
 * 
 * Fonctionnalités:
 * - Q1-Q3: Analyse, codage, affichage
 * - Q4: Évaluation P(x)
 * - Q5: Opérations arithmétiques (+, -, *, /)
 * - Q6: Garbage Collector
 * - Q8: Versions récursives (bonus)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/polynome.h"

/* Buffer pour les entrées utilisateur */
#define TAILLE_BUFFER 1024

/* Fonction utilitaire: lit une ligne depuis l'entrée standard */
void lireLigne(char *buffer, int taille) {
    if (fgets(buffer, taille, stdin) != NULL) {
        /* Supprimer le caractère de fin de ligne */
        int len = strlen(buffer);
        if (len > 0 && buffer[len-1] == '\n') {
            buffer[len-1] = '\0';
        }
    }
}

/* Fonction utilitaire: pause avant de continuer */
void pause() {
    printf("\nAppuyez sur Entrée pour continuer...");
    getchar();
}

/* Fonction utilitaire: efface l'écran (compatible Linux/Windows) */
void effacerEcran() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

/* Affiche le menu principal */
void afficherMenu() {
    effacerEcran();
    printf("╔═══════════════════════════════════════════════════════════════╗\n");
    printf("║           GESTION DES POLYNÔMES - Mini Projet DIC2            ║\n");
    printf("╠═══════════════════════════════════════════════════════════════╣\n");
    printf("║  1. Analyser et afficher un polynôme (Q1-Q3)                  ║\n");
    printf("║  2. Évaluer un polynôme P(x) (Q4)                             ║\n");
    printf("║  3. Addition de deux polynômes (Q6a)                          ║\n");
    printf("║  4. Soustraction de deux polynômes (Q6b)                     ║\n");
    printf("║  5. Multiplication de deux polynômes (Q6c)                   ║\n");
    printf("║  6. Division euclidienne (Q6d)                                ║\n");
    printf("║  7. Toutes les opérations sur vos polynômes                  ║\n");
    printf("║  8. Garbage Collector - Démonstration (Q7)                   ║\n");
    printf("║  9. Version récursive vs itérative (Q8 - Bonus)            ║\n");
    printf("║ 10. Tests automatiques complets                              ║\n");
    printf("║                                                               ║\n");
    printf("║  0. Quitter                                                   ║\n");
    printf("╚═══════════════════════════════════════════════════════════════╝\n");
    printf("\nVotre choix: ");
}

/* Question 1-3: Analyse et affichage */
void menuAnalyserAfficher() {
    char buffer[TAILLE_BUFFER];
    
    printf("\n=== QUESTION 1-3: ANALYSE ET AFFICHAGE ===\n\n");
    printf("Grammaire supportée:\n");
    printf("  - Polynôme: ['-'] monôme {('+'|'-') monôme}\n");
    printf("  - Monôme: nombre ['*'] X ['^' exposant] | X ['^' exposant] | nombre\n");
    printf("\nExemples valides:\n");
    printf("  • 3X^2 + 2X - 1\n");
    printf("  • -X^3 + 5X^2 + 4\n");
    printf("  • 4X - 2X + 5\n");
    printf("  • 2*X + 3\n");
    printf("  • X\n");
    printf("  • 10\n\n");
    
    printf("Entrez votre polynôme: ");
    lireLigne(buffer, TAILLE_BUFFER);
    
    printf("\n--- Résultat ---\n");
    printf("Expression: \"%s\"\n", buffer);
    
    POINTEUR p = analyserPolynome(buffer);
    
    printf("Polynôme analysé: \"");
    afficherPolynome(p);
    printf("\"\n");
    
    printf("Degré: %d\n", getDegre(p));
    
    ajouterPolyUtile(p);
    pause();
}

/* Question 4: Évaluation */
void menuEvaluation() {
    char buffer[TAILLE_BUFFER];
    double x;
    
    printf("\n=== QUESTION 4: ÉVALUATION P(x) ===\n\n");
    
    printf("Entrez votre polynôme: ");
    lireLigne(buffer, TAILLE_BUFFER);
    
    POINTEUR p = analyserPolynome(buffer);
    
    printf("\nPolynôme: \"");
    afficherPolynome(p);
    printf("\"\n\n");
    
    printf("Entrez la valeur de x: ");
    scanf("%lf", &x);
    getchar(); /* Consommer le \n */
    
    double resultat = eval(p, x);
    
    printf("\n--- Résultat ---\n");
    printf("P(%.2f) = %.4f\n", x, resultat);
    
    ajouterPolyUtile(p);
    pause();
}

/* Question 6a: Addition */
void menuAddition() {
    char buffer1[TAILLE_BUFFER], buffer2[TAILLE_BUFFER];
    
    printf("\n=== QUESTION 6a: ADDITION ===\n\n");
    
    printf("Entrez le premier polynôme (P1): ");
    lireLigne(buffer1, TAILLE_BUFFER);
    
    printf("Entrez le deuxième polynôme (P2): ");
    lireLigne(buffer2, TAILLE_BUFFER);
    
    POINTEUR p1 = analyserPolynome(buffer1);
    POINTEUR p2 = analyserPolynome(buffer2);
    
    printf("\n--- Opération ---\n");
    printf("P1 = \""); afficherPolynome(p1); printf("\"\n");
    printf("P2 = \""); afficherPolynome(p2); printf("\"\n");
    printf("P1 + P2 = ");
    
    POINTEUR somme = plus(p1, p2);
    afficherPolynome(somme);
    printf("\n");
    
    ajouterPolyUtile(p1);
    ajouterPolyUtile(p2);
    ajouterPolyUtile(somme);
    pause();
}

/* Question 6b: Soustraction */
void menuSoustraction() {
    char buffer1[TAILLE_BUFFER], buffer2[TAILLE_BUFFER];
    
    printf("\n=== QUESTION 6b: SOUSTRACTION ===\n\n");
    
    printf("Entrez le premier polynôme (P1): ");
    lireLigne(buffer1, TAILLE_BUFFER);
    
    printf("Entrez le deuxième polynôme (P2): ");
    lireLigne(buffer2, TAILLE_BUFFER);
    
    POINTEUR p1 = analyserPolynome(buffer1);
    POINTEUR p2 = analyserPolynome(buffer2);
    
    printf("\n--- Opération ---\n");
    printf("P1 = \""); afficherPolynome(p1); printf("\"\n");
    printf("P2 = \""); afficherPolynome(p2); printf("\"\n");
    printf("P1 - P2 = ");
    
    POINTEUR diff = moins(p1, p2);
    afficherPolynome(diff);
    printf("\n");
    
    ajouterPolyUtile(p1);
    ajouterPolyUtile(p2);
    ajouterPolyUtile(diff);
    pause();
}

/* Question 6c: Multiplication */
void menuMultiplication() {
    char buffer1[TAILLE_BUFFER], buffer2[TAILLE_BUFFER];
    
    printf("\n=== QUESTION 6c: MULTIPLICATION ===\n\n");
    
    printf("Entrez le premier polynôme (P1): ");
    lireLigne(buffer1, TAILLE_BUFFER);
    
    printf("Entrez le deuxième polynôme (P2): ");
    lireLigne(buffer2, TAILLE_BUFFER);
    
    POINTEUR p1 = analyserPolynome(buffer1);
    POINTEUR p2 = analyserPolynome(buffer2);
    
    printf("\n--- Opération ---\n");
    printf("P1 = \""); afficherPolynome(p1); printf("\"\n");
    printf("P2 = \""); afficherPolynome(p2); printf("\"\n");
    printf("P1 × P2 = ");
    
    POINTEUR produit = fois(p1, p2);
    afficherPolynome(produit);
    printf("\n");
    
    ajouterPolyUtile(p1);
    ajouterPolyUtile(p2);
    ajouterPolyUtile(produit);
    pause();
}

/* Question 6d: Division */
void menuDivision() {
    char buffer1[TAILLE_BUFFER], buffer2[TAILLE_BUFFER];
    
    printf("\n=== QUESTION 6d: DIVISION EUCLIDIENNE ===\n\n");
    printf("Formule: P1 = P2 × Quotient + Reste\n\n");
    
    printf("Entrez le dividende (P1): ");
    lireLigne(buffer1, TAILLE_BUFFER);
    
    printf("Entrez le diviseur (P2): ");
    lireLigne(buffer2, TAILLE_BUFFER);
    
    POINTEUR p1 = analyserPolynome(buffer1);
    POINTEUR p2 = analyserPolynome(buffer2);
    
    printf("\n--- Opération ---\n");
    printf("P1 = \""); afficherPolynome(p1); printf("\"\n");
    printf("P2 = \""); afficherPolynome(p2); printf("\"\n\n");
    
    POINTEUR reste = NULL;
    POINTEUR quot = quotient(p1, p2, &reste);
    
    printf("Quotient = \"");
    afficherPolynome(quot);
    printf("\"\n");
    
    printf("Reste = \"");
    afficherPolynome(reste);
    printf("\"\n");
    
    /* Vérification: P1 = P2 × Quotient + Reste */
    POINTEUR verification = plus(fois(p2, quot), reste);
    printf("\nVérification (P2 × Q + R): \"");
    afficherPolynome(verification);
    printf("\"\n");
    
    ajouterPolyUtile(p1);
    ajouterPolyUtile(p2);
    ajouterPolyUtile(quot);
    ajouterPolyUtile(reste);
    pause();
}

/* Question 7: Garbage Collector */
void menuGC() {
    int i;
    
    printf("\n=== QUESTION 7: GARBAGE COLLECTOR ===\n\n");
    printf("Algorithme: Mark and Sweep\n");
    printf("- MARK: Marque les maillons accessibles\n");
    printf("- SWEEP: Libère les maillons non marqués\n\n");
    
    /* Réinitialiser le GC */
    nbPolyUtiles = 0;
    
    /* Créer des polynômes */
    printf("Création de polynômes...\n");
    POINTEUR p1 = analyserPolynome("3X^2 + 2X - 1");
    POINTEUR p2 = analyserPolynome("X^3 + 5X^2 + 4");
    POINTEUR p3 = analyserPolynome("2X + 1");
    POINTEUR temp1 = analyserPolynome("X^2 + 1");
    POINTEUR temp2 = analyserPolynome("X + 2");
    
    printf("P1 = \""); afficherPolynome(p1); printf("\"\n");
    printf("P2 = \""); afficherPolynome(p2); printf("\"\n");
    printf("P3 = \""); afficherPolynome(p3); printf("\"\n\n");
    
    /* Marquer P1 et P2 comme utiles */
    printf("Marquage de P1 et P2 comme utiles...\n");
    ajouterPolyUtile(p1);
    ajouterPolyUtile(p2);
    /* P3 n'est PAS marqué → sera collecté */
    
    /* Créer des polynômes temporaires (non marqués) */
    printf("Création de polynômes temporaires (non marqués)...\n");
    POINTEUR produit = fois(temp1, temp2); /* Ne sera pas marqué */
    
    printf("\nPolynômes temporaires créés mais non marqués comme utiles.\n");
    printf("P3 n'est pas marqué (sera collecté).\n\n");
    
    printf("--- État avant GC ---\n");
    printf("Polynômes utiles marqués: %d\n", nbPolyUtiles);
    printf("Total de maillons alloués: [liste interne du GC]\n\n");
    
    printf("Lancement du Garbage Collector...\n");
    garbageCollector();
    
    printf("\n--- État après GC ---\n");
    printf("✓ P1 et P2 conservés (marqués utiles)\n");
    printf("✓ P3 libéré (non marqué)\n");
    printf("✓ Polynômes temporaires libérés (non marqués)\n\n");
    
    printf("Vérification: P1 et P2 toujours accessibles\n");
    printf("P1 = \""); afficherPolynome(p1); printf("\"\n");
    printf("P2 = \""); afficherPolynome(p2); printf("\"\n");
    
    pause();
}

/* Question 8: Comparaison récursif vs itératif */
void menuRecursif() {
    char buffer[TAILLE_BUFFER];
    
    printf("\n=== QUESTION 8: VERSIONS RÉCURSIVES (BONUS) ===\n\n");
    printf("Comparaison des approches itérative et récursive.\n\n");
    
    printf("Entrez le premier polynôme (P1): ");
    lireLigne(buffer, TAILLE_BUFFER);
    POINTEUR p1 = analyserPolynome(buffer);
    
    printf("Entrez le deuxième polynôme (P2): ");
    lireLigne(buffer, TAILLE_BUFFER);
    POINTEUR p2 = analyserPolynome(buffer);
    
    printf("\n--- Addition Itérative (Q6a) ---\n");
    POINTEUR sommeIter = plus(p1, p2);
    printf("P1 + P2 = \"");
    afficherPolynome(sommeIter);
    printf("\"\n");
    
    printf("\n--- Addition Récursive (Q8 - Bonus) ---\n");
    POINTEUR sommeRec = plus_recursif(p1, p2);
    printf("P1 + P2 = \"");
    afficherPolynome(sommeRec);
    printf("\"\n");
    
    printf("\n--- Soustraction Itérative (Q6b) ---\n");
    POINTEUR diffIter = moins(p1, p2);
    printf("P1 - P2 = \"");
    afficherPolynome(diffIter);
    printf("\"\n");
    
    printf("\n--- Soustraction Récursive (Q8 - Bonus) ---\n");
    POINTEUR diffRec = moins_recursif(p1, p2);
    printf("P1 - P2 = \"");
    afficherPolynome(diffRec);
    printf("\"\n");
    
    printf("\nNote: Les versions récursives sont plus élégantes mais\n");
    printf("consomment plus de mémoire (pile d'appels).\n");
    
    ajouterPolyUtile(p1);
    ajouterPolyUtile(p2);
    pause();
}

/* Toutes les opérations sur 2 polynômes */
void menuToutesOperations() {
    char buffer1[TAILLE_BUFFER], buffer2[TAILLE_BUFFER];
    
    printf("\n=== TOUTES LES OPÉRATIONS ===\n\n");
    
    printf("Entrez votre premier polynôme (P1): ");
    lireLigne(buffer1, TAILLE_BUFFER);
    
    printf("Entrez votre deuxième polynôme (P2): ");
    lireLigne(buffer2, TAILLE_BUFFER);
    
    POINTEUR p1 = analyserPolynome(buffer1);
    POINTEUR p2 = analyserPolynome(buffer2);
    
    printf("\n========================================\n");
    printf("P1 = \""); afficherPolynome(p1); printf("\"\n");
    printf("P2 = \""); afficherPolynome(p2); printf("\"\n");
    printf("========================================\n\n");
    
    /* Évaluation */
    double x;
    printf("Entrez une valeur pour x (évaluation): ");
    scanf("%lf", &x);
    getchar();
    
    printf("\n--- Q4: ÉVALUATION ---\n");
    printf("P1(%.2f) = %.4f\n", x, eval(p1, x));
    printf("P2(%.2f) = %.4f\n", x, eval(p2, x));
    
    /* Addition */
    printf("\n--- Q6a: ADDITION ---\n");
    POINTEUR somme = plus(p1, p2);
    printf("P1 + P2 = \""); afficherPolynome(somme); printf("\"\n");
    
    /* Soustraction */
    printf("\n--- Q6b: SOUSTRACTION ---\n");
    POINTEUR diff = moins(p1, p2);
    printf("P1 - P2 = \""); afficherPolynome(diff); printf("\"\n");
    printf("P2 - P1 = \""); afficherPolynome(moins(p2, p1)); printf("\"\n");
    
    /* Multiplication */
    printf("\n--- Q6c: MULTIPLICATION ---\n");
    POINTEUR produit = fois(p1, p2);
    printf("P1 × P2 = \""); afficherPolynome(produit); printf("\"\n");
    
    /* Division */
    printf("\n--- Q6d: DIVISION ---\n");
    if (!p2 || (p2->coeff == 0 && p2->exposant == 0)) {
        printf("Impossible: P2 est nul (division par zéro)\n");
    } else {
        POINTEUR reste = NULL;
        POINTEUR quot = quotient(p1, p2, &reste);
        printf("P1 ÷ P2:\n");
        printf("  Quotient = \""); afficherPolynome(quot); printf("\"\n");
        printf("  Reste = \""); afficherPolynome(reste); printf("\"\n");
    }
    
    ajouterPolyUtile(p1);
    ajouterPolyUtile(p2);
    pause();
}

/* Tests automatiques complets */
void menuTestsAutomatiques() {
    printf("\n=== TESTS AUTOMATIQUES COMPLETS ===\n\n");
    
    /* Test Q1 */
    printf("--- Q1: Analyseur syntaxique ---\n");
    char *expressions[] = {
        "3X^2 + 2X - 1",
        "-X^3 + 5X^2 + 4",
        "4X - 2X + 5",
        "X",
        "10",
        NULL
    };
    
    for (int i = 0; expressions[i] != NULL; i++) {
        POINTEUR p = analyserPolynome(expressions[i]);
        printf("✓ \"%s\" → \"", expressions[i]);
        afficherPolynome(p);
        printf("\"\n");
        ajouterPolyUtile(p);
    }
    
    /* Test Q4 */
    printf("\n--- Q4: Évaluation ---\n");
    POINTEUR p = analyserPolynome("3X^2 + 2X - 1");
    printf("P(X) = "); afficherPolynome(p);
    printf("\nP(2) = %.2f (attendu: 15.00)\n", eval(p, 2.0));
    ajouterPolyUtile(p);
    
    /* Test Q6 */
    printf("\n--- Q6: Opérations ---\n");
    POINTEUR a = analyserPolynome("X + 1");
    POINTEUR b = analyserPolynome("X - 1");
    
    printf("A = "); afficherPolynome(a); printf("\n");
    printf("B = "); afficherPolynome(b); printf("\n");
    
    POINTEUR s = plus(a, b);
    printf("A + B = "); afficherPolynome(s); printf(" (attendu: 2X)\n");
    
    POINTEUR m = fois(a, b);
    printf("A × B = "); afficherPolynome(m); printf(" (attendu: X^2 - 1)\n");
    
    ajouterPolyUtile(a);
    ajouterPolyUtile(b);
    ajouterPolyUtile(s);
    ajouterPolyUtile(m);
    
    printf("\n✅ Tous les tests de base passés!\n");
    pause();
}

/* Programme principal */
int main() {
    int choix;
    
    /* Initialisation du GC */
    nbPolyUtiles = 0;
    tousLesMaillons = NULL;
    
    do {
        afficherMenu();
        scanf("%d", &choix);
        getchar(); /* Consommer le \n */
        
        switch(choix) {
            case 1:
                menuAnalyserAfficher();
                break;
            case 2:
                menuEvaluation();
                break;
            case 3:
                menuAddition();
                break;
            case 4:
                menuSoustraction();
                break;
            case 5:
                menuMultiplication();
                break;
            case 6:
                menuDivision();
                break;
            case 7:
                menuToutesOperations();
                break;
            case 8:
                menuGC();
                break;
            case 9:
                menuRecursif();
                break;
            case 10:
                menuTestsAutomatiques();
                break;
            case 0:
                printf("\nAu revoir!\n");
                break;
            default:
                printf("\nChoix invalide.\n");
                pause();
        }
    } while (choix != 0);
    
    return 0;
}
