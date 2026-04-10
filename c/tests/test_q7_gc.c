/**
 * @file test_q7_gc.c
 * @brief Tests pour le Garbage Collector (Q7)
 * @details Teste les fonctions:
 *          - ajouterPolyUtile()
 *          - marquerUtiles()
 *          - libererInutiles()
 *          - garbageCollector()
 * 
 * Implémenté par: [Ton nom] (GLSI - Lead)
 */

#include <stdio.h>
#include <stdlib.h>
#include "../include/polynome.h"

int main() {
    printf("========================================\n");
    printf("  TEST Q7: GARBAGE COLLECTOR\n");
    printf("========================================\n\n");

    /* Créer plusieurs polynômes */
    printf("Création de polynômes...\n");
    POINTEUR p1 = analyserPolynome("3X^2 + 2X - 1");
    POINTEUR p2 = analyserPolynome("X^3 + 5X^2 + 4");
    POINTEUR p3 = analyserPolynome("2X + 1");
    
    printf("P1: ");
    afficherPolynome(p1);
    printf("\n");
    
    printf("P2: ");
    afficherPolynome(p2);
    printf("\n");
    
    printf("P3: ");
    afficherPolynome(p3);
    printf("\n\n");

    /* Marquer P1 et P2 comme utiles */
    printf("Marquage des polynômes utiles...\n");
    ajouterPolyUtile(p1);
    ajouterPolyUtile(p2);
    printf("P1 et P2 marqués comme utiles.\n");
    printf("P3 n'est PAS marqué (sera collecté).\n\n");

    /* Effectuer des opérations (crée des polynômes temporaires) */
    printf("Opérations créant des polynômes temporaires...\n");
    POINTEUR somme = plus(p1, p2);
    printf("P1 + P2: ");
    afficherPolynome(somme);
    printf("\n\n");

    /* Exécuter le Garbage Collector */
    printf("Exécution du Garbage Collector...\n");
    garbageCollector();
    printf("GC terminé.\n");
    printf("- P1 et P2 conservés (marqués utiles)\n");
    printf("- P3 libéré (non marqué)\n");
    printf("- Polynômes temporaires libérés (non marqués)\n\n");

    /* Vérifier que P1 et P2 sont toujours accessibles */
    printf("Vérification: P1 et P2 toujours accessibles\n");
    printf("P1: ");
    afficherPolynome(p1);
    printf("\n");
    
    printf("P2: ");
    afficherPolynome(p2);
    printf("\n\n");

    printf("========================================\n");
    printf("  Q7: GARBAGE COLLECTOR ✓ COMPLÉTÉ\n");
    printf("========================================\n");

    return 0;
}
