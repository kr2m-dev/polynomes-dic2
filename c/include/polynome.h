/**
 * @file polynome.h
 * @brief Déclarations pour la manipulation des polynômes - Mini Projet DIC2
 * @details Structure de données et prototypes de fonctions pour le projet
 *          Groupe: [VOTRE_GROUPE_ICI]
 *          
 * QUESTIONS IMPLÉMENTÉES:
 * - Q1: Analyseur syntaxique (grammaire)           (ASSIGNÉ À: IABD 1)
 * - Q2: Codage en mémoire (liste chaînée)          (ASSIGNÉ À: IABD 1)
 * - Q3: Affichage formaté                          (ASSIGNÉ À: IABD 1)
 * - Q4: Évaluation du polynôme                      (ASSIGNÉ À: Telecom)
 * - Q5: Opérations arithmétiques                    (ASSIGNÉ À: IABD 2, SysSec 1)
 * - Q6: Garbage Collector                           (ASSIGNÉ À: SysSec 2)
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
    
    /* Pour le Garbage Collector (Question 6) */
    struct Maillon *general;/* Chaînage de tous les maillons alloués */
    int utile;              /* Marque pour le GC (1=utile, 0=inutile) */
} Maillon, *POINTEUR;

/* ============================================================
 * VARIABLES GLOBALES (pour Q6 - Garbage Collector)
 * ============================================================
 * Le membre Q6 doit gérer ces variables
 */
extern POINTEUR tousLesMaillons;    /* Liste de tous les maillons */
extern POINTEUR polyUtile[];         /* Tableau des polynômes utiles */
extern int nbPolyUtiles;             /* Nombre de polynômes utiles */

/* ============================================================
 * QUESTION 1: ANALYSEUR SYNTAXIQUE
 * Assigné à: IABD 1
 * Grammaire:
 *   polynôme → ['-'] monôme { ('+' | '-') monôme }
 *   monôme → nombre '*' xpuissance | xpuissance | nombre
 *   xpuissance → 'X' | 'X' '^' naturel
 * ============================================================ */

/**
 * @brief Analyseur lexical - lit le caractère suivant
 * @details Fonction interne utilisée par l'analyseur syntaxique
 */
void avancer(void);

/**
 * @brief Initialise l'analyseur avec une chaîne
 * @param s Chaîne à analyser
 */
void initialiserAnalyseur(char *s);

/**
 * @brief Analyseur syntaxique: convertit une chaîne en polynôme
 * @param texte Expression textuelle (ex: "3X^2 + 2X - 1")
 * @return Pointeur vers le polynôme construit
 * 
 * @warning L'expression doit respecter la grammaire
 * @assigné Q1 - IMPLÉMENTÉ
 */
POINTEUR analyserPolynome(char *texte);

/* ============================================================
 * QUESTION 2: CODAGE EN MÉMOIRE
 * Assigné à: IABD 1
 * ============================================================ */

/**
 * @brief Alloue un nouveau maillon avec suivi pour le GC
 * @param coeff Coefficient du monôme
 * @param exposant Exposant du monôme
 * @return Pointeur vers le nouveau maillon alloué
 * 
 * @note Cette fonction gère automatiquement l'enregistrement pour Q6
 * @assigné Q2 - IMPLÉMENTÉ
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
 * @assigné Q2 - IMPLÉMENTÉ
 */
POINTEUR insererMonome(POINTEUR tete, double coeff, int exposant);

/* ============================================================
 * QUESTION 3: AFFICHAGE
 * Assigné à: IABD 1
 * ============================================================ */

/**
 * @brief Affiche un polynôme de manière formatée
 * @param p Polynôme à afficher
 * 
 * @example "3.00X^2 + 2.00X - 1.00"
 * @assigné Q3 - IMPLÉMENTÉ
 */
void afficherPolynome(POINTEUR p);

/* ============================================================
 * QUESTION 4: ÉVALUATION
 * Assigné à: Telecom Réseau
 * ============================================================ */

/**
 * @brief Évalue le polynôme en un point x donné
 * @param p Polynôme à évaluer
 * @param x Valeur de la variable
 * @return Valeur du polynôme évalué en x
 * 
 * @exemple P(X) = 3X^2 + 2X - 1, eval(P, 2) = 3*4 + 2*2 - 1 = 15
 * @assigné Q4 - IMPLÉMENTÉ
 */
double eval(POINTEUR p, double x);

/**
 * @brief Retourne le degré du polynôme (exposant maximum)
 * @param p Polynôme
 * @return Degré (exposant maximum), 0 si polynôme nul
 */
int getDegre(POINTEUR p);

/* ============================================================
 * QUESTION 5: OPÉRATIONS ARITHMÉTIQUES
 * ============================================================ */

/**
 * @brief Additionne deux polynômes
 * @param a Premier polynôme
 * @param b Deuxième polynôme
 * @return Nouveau polynôme résultat (a + b)
 * 
 * @assigné Q5a - IMPLÉMENTÉ (IABD 2)
 */
POINTEUR plus(POINTEUR a, POINTEUR b);

/**
 * @brief Soustrait deux polynômes
 * @param a Premier polynôme
 * @param b Deuxième polynôme
 * @return Nouveau polynôme résultat (a - b)
 * 
 * @assigné Q5b - IMPLÉMENTÉ (IABD 2)
 */
POINTEUR moins(POINTEUR a, POINTEUR b);

/**
 * @brief Multiplie deux polynômes
 * @param a Premier polynôme
 * @param b Deuxième polynôme
 * @return Nouveau polynôme résultat (a * b)
 * 
 * @assigné Q5c - IMPLÉMENTÉ (SysSec 1)
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
 * @assigné Q5d - IMPLÉMENTÉ (SysSec 1)
 */
POINTEUR quotient(POINTEUR a, POINTEUR b, POINTEUR *reste);

/* ============================================================
 * QUESTION 6: GARBAGE COLLECTOR
 * Assigné à: SysSec 2
 * ============================================================ */

/**
 * @brief Marque tous les maillons accessibles depuis les polynômes utiles
 * @details Utilise un algorithme de marquage (mark-and-sweep)
 * @assigné Q6a - IMPLÉMENTÉ
 */
void marquerUtiles(void);

/**
 * @brief Libère tous les maillons non marqués
 * @details Parcourt tousLesMaillons et libère ceux où utile == 0
 * @assigné Q6b - IMPLÉMENTÉ
 */
void libererInutiles(void);

/**
 * @brief Fonction principale du Garbage Collector
 * @details Appelle marquerUtiles() puis libererInutiles()
 * @assigné Q6c - IMPLÉMENTÉ
 */
void garbageCollector(void);

/* ============================================================
 * UTILITAIRES (optionnels)
 * ============================================================ */

/**
 * @brief Ajoute un polynôme à la liste des polynômes utiles
 * @param p Polynôme à marquer comme utile
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

/* ============================================================
 * QUESTION 8: VERSIONS RÉCURSIVES - BONUS
 * Assigné à: Ame Thiam (TR)
 * ============================================================
 * Versions récursives de l'addition et de la soustraction.
 * Ces implémentations sont plus élégantes mais consomment plus
 * de mémoire à cause de la récursion.
 */

/**
 * @brief Addition récursive de deux polynômes
 * @param a Premier polynôme
 * @param b Deuxième polynôme
 * @return Nouveau polynôme résultat (a + b)
 * 
 * @note Version récursive élégante mais moins efficace
 * @assigné Q8a - BONUS
 */
POINTEUR plus_recursif(POINTEUR a, POINTEUR b);

/**
 * @brief Soustraction récursive de deux polynômes
 * @param a Premier polynôme
 * @param b Deuxième polynôme
 * @return Nouveau polynôme résultat (a - b)
 * 
 * @note Version récursive élégante mais moins efficace
 * @assigné Q8b - BONUS
 */
POINTEUR moins_recursif(POINTEUR a, POINTEUR b);

#endif /* POLYNOME_H */
