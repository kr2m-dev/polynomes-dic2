/**
 * @file polynome.h
 * @brief Déclarations pour la manipulation des polynômes - Mini Projet DIC2
 * @details Structure de données et prototypes de fonctions pour le projet
 *          Groupe: [VOTRE_GROUPE_ICI]
 *          
 * QUESTIONS À IMPLÉMENTER:
 * - Q4: Analyseur syntaxique, insertion, affichage  (ASSIGNÉ À: ___)
 * - Q5: Évaluation du polynôme                      (ASSIGNÉ À: ___)
 * - Q6a: Addition de polynômes                      (ASSIGNÉ À: ___)
 * - Q6b: Soustraction de polynômes                  (ASSIGNÉ À: ___)
 * - Q6c: Multiplication de polynômes                (ASSIGNÉ À: ___)
 * - Q6d: Division euclidienne                       (ASSIGNÉ À: ___)
 * - Q7: Garbage Collector                           (ASSIGNÉ À: ___)
 */

#ifndef POLYNOME_H
#define POLYNOME_H

#include <stdio.h>
#include <stdlib.h>

/* ============================================================
 * STRUCTURE DE DONNÉES
 * ============================================================
 * Chaque membre du groupe doit comprendre cette structure
 * Elle représente un monôme dans une liste chaînée
 */
typedef struct Maillon {
    double coeff;           /* Coefficient du monôme */
    int exposant;           /* Exposant (degré) */
    struct Maillon *suivant;/* Lien vers le monôme suivant */
    
    /* Pour le Garbage Collector (Question 7) */
    struct Maillon *general;/* Chaînage de tous les maillons alloués */
    int utile;              /* Marque pour le GC (1=utile, 0=inutile) */
} Maillon, *POINTEUR;

/* ============================================================
 * VARIABLES GLOBALES (pour Q7 - Garbage Collector)
 * ============================================================
 * Le membre Q7 doit gérer ces variables
 */
extern POINTEUR tousLesMaillons;    /* Liste de tous les maillons */
extern POINTEUR polyUtile[];         /* Tableau des polynômes utiles */
extern int nbPolyUtiles;             /* Nombre de polynômes utiles */

/* ============================================================
 * FONCTIONS DE BASE (à compléter par Q4)
 * ============================================================ */

/**
 * @brief Alloue un nouveau maillon avec suivi pour le GC
 * @param coeff Coefficient du monôme
 * @param exposant Exposant du monôme
 * @return Pointeur vers le nouveau maillon alloué
 * 
 * @note Cette fonction gère automatiquement l'enregistrement pour Q7
 * @assigné Q4 - Doit être complétée
 */
POINTEUR allouerMaillon(double coeff, int exposant);

/**
 * @brief Insère un monôme par ordre décroissant d'exposant
 * @param tete Tête de la liste chaînée
 * @param coeff Coefficient du monôme à insérer
 * @param exposant Exposant du monôme à insérer
 * @return Nouvelle tête de liste
 * 
 * @note Si un monôme avec le même exposant existe, additionne les coefficients
 * @assigné Q4 - À IMPLÉMENTER
 */
POINTEUR insererMonome(POINTEUR tete, double coeff, int exposant);

/**
 * @brief Analyseur syntaxique: convertit une chaîne en polynôme
 * @param texte Expression textuelle (ex: "3X^2 + 2X - 1")
 * @return Pointeur vers le polynôme construit
 * 
 * @warning L'expression doit être correctement formatée
 * @assigné Q4 - À IMPLÉMENTER
 */
POINTEUR analyserPolynome(char *texte);

/**
 * @brief Affiche un polynôme de manière formatée
 * @param p Polynôme à afficher
 * 
 * @example "3.00X^2 + 2.00X - 1.00"
 * @assigné Q4 - À IMPLÉMENTER
 */
void afficherPolynome(POINTEUR p);

/* ============================================================
 * QUESTION 5: ÉVALUATION (ASSIGNÉ À: ___)
 * ============================================================ */

/**
 * @brief Évalue le polynôme en un point x donné
 * @param p Polynôme à évaluer
 * @param x Valeur de la variable
 * @return Valeur du polynôme évalué en x
 * 
 * @exemple P(X) = 3X^2 + 2X - 1, eval(P, 2) = 3*4 + 2*2 - 1 = 15
 * @assigné Q5 - À IMPLÉMENTER
 */
double eval(POINTEUR p, double x);

/* ============================================================
 * QUESTION 6: OPÉRATIONS ARITHMÉTIQUES
 * ============================================================ */

/**
 * @brief Additionne deux polynômes
 * @param a Premier polynôme
 * @param b Deuxième polynôme
 * @return Nouveau polynôme résultat (a + b)
 * 
 * @assigné Q6a - À IMPLÉMENTER
 */
POINTEUR plus(POINTEUR a, POINTEUR b);

/**
 * @brief Soustrait deux polynômes
 * @param a Premier polynôme
 * @param b Deuxième polynôme
 * @return Nouveau polynôme résultat (a - b)
 * 
 * @assigné Q6b - À IMPLÉMENTER
 */
POINTEUR moins(POINTEUR a, POINTEUR b);

/**
 * @brief Multiplie deux polynômes
 * @param a Premier polynôme
 * @param b Deuxième polynôme
 * @return Nouveau polynôme résultat (a * b)
 * 
 * @assigné Q6c - À IMPLÉMENTER
 */
POINTEUR fois(POINTEUR a, POINTEUR b);

/**
 * @brief Division euclidienne de deux polynômes
 * @param a Dividende
 * @param b Diviseur
 * @param reste Pointeur pour stocker le reste
 * @return Quotient de la division
 * 
 * @note a = b * quotient + reste
 * @warning Vérifier que b n'est pas nul
 * @assigné Q6d - À IMPLÉMENTER
 */
POINTEUR quotient(POINTEUR a, POINTEUR b, POINTEUR *reste);

/* ============================================================
 * QUESTION 7: GARBAGE COLLECTOR (ASSIGNÉ À: ___)
 * ============================================================ */

/**
 * @brief Marque tous les maillons accessibles depuis les polynômes utiles
 * @details Utilise un algorithme de marquage (mark-and-sweep)
 * @assigné Q7 - À IMPLÉMENTER
 */
void marquerUtiles(void);

/**
 * @brief Libère tous les maillons non marqués
 * @details Parcourt tousLesMaillons et libère ceux où utile == 0
 * @assigné Q7 - À IMPLÉMENTER
 */
void libererInutiles(void);

/**
 * @brief Fonction principale du Garbage Collector
 * @details Appelle marquerUtiles() puis libererInutiles()
 * @assigné Q7 - À IMPLÉMENTER
 */
void garbageCollector(void);

/* ============================================================
 * UTILITAIRES (optionnels)
 * ============================================================ */

/**
 * @brief Ajoute un polynôme à la liste des polynômes utiles
 * @param p Polynôme à marquer comme utile
 * @assigné Q7 - Utilisée par tous
 */
void ajouterPolyUtile(POINTEUR p);

/**
 * @brief Crée une copie d'un monôme
 * @param m Monôme à copier
 * @return Nouveau maillon copié
 */
POINTEUR copierMonome(POINTEUR m);

/**
 * @brief Libère explicitement un polynôme
 * @param p Polynôme à retirer de la liste des utiles
 */
void libererPolynome(POINTEUR p);

#endif /* POLYNOME_H */
