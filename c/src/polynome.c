/**
 * @file polynome.c
 * @brief Implémentation des fonctions de manipulation des polynômes
 * @details Ce fichier contient:
 *          - Q1, Q2, Q3: COMPLÉTÉES (Analyseur, Codage, Affichage)
 *          - Q4, Q5, Q6: À IMPLÉMENTER PAR VOS CAMARADES
 * 
 * INSTRUCTIONS POUR LE GROUPE:
 * - Q1, Q2, Q3: DÉJÀ COMPLÉTÉES (ne pas modifier)
 * - Q4, Q5, Q6: LAISSEZ VIDE avec TODO pour vos camarades
 * - Chaque membre implémente sa question assignée
 * - Ne pas modifier les signatures de fonctions
 * - Tester individuellement avant de merger
 */

#include "../include/polynome.h"
#include <string.h>
#include <ctype.h>
#include <math.h>

/* ============================================================
 * VARIABLES GLOBALES (pour Q6 - Garbage Collector)
 * ============================================================
 * Gérées par SysSec 2
 */
POINTEUR tousLesMaillons = NULL;
POINTEUR polyUtile[100];
int nbPolyUtiles = 0;

/* ============================================================
 * QUESTION 1: ANALYSEUR SYNTAXIQUE
 * Assigné à: IABD 1 - COMPLÉTÉ ✓
 * Grammaire: polynôme → ['-'] monôme { ('+' | '-') monôme }
 * ============================================================
 */

/* Types pour l'analyseur lexical */
typedef enum {
    TOKEN_PLUS,    /* + */
    TOKEN_MOINS,   /* - */
    TOKEN_MULT,    /* * */
    TOKEN_X,       /* X */
    TOKEN_PUISS,   /* ^ */
    TOKEN_NB,      /* nombre */
    TOKEN_FIN,     /* fin de chaîne */
    TOKEN_ERREUR   /* erreur */
} TokenType;

typedef struct {
    TokenType type;
    double valeur;    /* Pour TOKEN_NB */
    int entier;       /* Pour l'exposant */
} Token;

/* Variables globales de l'analyseur */
static char *texte;
static int pos = 0;
static Token tokenCourant;

/* Fonction interne: avance dans le flux de caractères */
static void avancer() {
    while (texte[pos] == ' ' || texte[pos] == '\t') pos++;

    if (texte[pos] == '\0') {
        tokenCourant.type = TOKEN_FIN;
        return;
    }

    switch (texte[pos]) {
        case '+':
            tokenCourant.type = TOKEN_PLUS;
            pos++;
            break;
        case '-':
            tokenCourant.type = TOKEN_MOINS;
            pos++;
            break;
        case '*':
            tokenCourant.type = TOKEN_MULT;
            pos++;
            break;
        case 'X':
        case 'x':
            tokenCourant.type = TOKEN_X;
            pos++;
            break;
        case '^':
            tokenCourant.type = TOKEN_PUISS;
            pos++;
            break;
        default:
            if (isdigit(texte[pos])) {
                /* Lecture d'un nombre */
                char nombre[50];
                int i = 0;
                while (isdigit(texte[pos])) {
                    nombre[i++] = texte[pos++];
                }
                if (texte[pos] == '.') {
                    nombre[i++] = texte[pos++];
                    while (isdigit(texte[pos])) {
                        nombre[i++] = texte[pos++];
                    }
                }
                nombre[i] = '\0';
                tokenCourant.type = TOKEN_NB;
                tokenCourant.valeur = atof(nombre);
            } else {
                tokenCourant.type = TOKEN_ERREUR;
                printf("Erreur: caractère '%c' inattendu à la position %d\n", texte[pos], pos);
                pos++;
            }
    }
}

/* Fonction interne: initialise l'analyseur */
static void initialiserAnalyseur(char *s) {
    texte = s;
    pos = 0;
    avancer();
}

/* Fonction interne: analyse X^exposant */
static int analyserXpuissance() {
    int exposant = 1; /* Par défaut, X = X^1 */

    if (tokenCourant.type == TOKEN_PUISS) {
        avancer();
        if (tokenCourant.type == TOKEN_NB) {
            exposant = (int)tokenCourant.valeur;
            if (exposant < 0) {
                printf("Erreur: exposant négatif non autorisé\n");
                exit(1);
            }
            avancer();
        } else {
            printf("Erreur: exposant attendu après '^'\n");
            exit(1);
        }
    }

    return exposant;
}

/* Fonction interne: analyse un monôme */
static POINTEUR analyserMonome(int signe) {
    double coeff = 1.0;
    int exposant = 0;
    int aCoeff = 0;
    int aX = 0;

    /* Premier élément: nombre ou X */
    if (tokenCourant.type == TOKEN_NB) {
        coeff = tokenCourant.valeur;
        aCoeff = 1;
        avancer();

        /* Vérifier si * X suit */
        if (tokenCourant.type == TOKEN_MULT) {
            avancer();
            if (tokenCourant.type == TOKEN_X) {
                aX = 1;
                avancer();
                exposant = analyserXpuissance();
            } else {
                printf("Erreur: 'X' attendu après '*'\n");
                exit(1);
            }
        }
    } else if (tokenCourant.type == TOKEN_X) {
        aX = 1;
        coeff = 1.0;
        avancer();
        exposant = analyserXpuissance();
    } else {
        printf("Erreur: nombre ou X attendu\n");
        exit(1);
    }

    coeff *= signe;
    return insererMonome(NULL, coeff, exposant);
}

/* 
 * Q1: Analyseur syntaxique principal
 * Lit un texte caractère par caractère et reconnaît un polynôme
 */
POINTEUR analyserPolynome(char *texte) {
    POINTEUR p = NULL;
    int signeGlobal = 1;

    initialiserAnalyseur(texte);

    /* Gérer le signe initial du polynôme */
    if (tokenCourant.type == TOKEN_MOINS) {
        signeGlobal = -1;
        avancer();
    } else if (tokenCourant.type == TOKEN_PLUS) {
        avancer();
    }

    p = analyserMonome(signeGlobal);

    while (tokenCourant.type == TOKEN_PLUS || tokenCourant.type == TOKEN_MOINS) {
        signeGlobal = (tokenCourant.type == TOKEN_PLUS) ? 1 : -1;
        avancer();
        POINTEUR monome = analyserMonome(signeGlobal);
        p = insererMonome(p, monome->coeff, monome->exposant);
    }

    return p;
}

/* ============================================================
 * QUESTION 2: CODAGE EN MÉMOIRE
 * Assigné à: IABD 1 - COMPLÉTÉ ✓
 * Structure: Liste chaînée ordonnée par exposant décroissant
 * ============================================================

/*
 * Q2: Alloue un nouveau maillon
 * Crée un monôme avec coefficient et exposant
 */
POINTEUR allouerMaillon(double coeff, int exposant) {
    POINTEUR m = (POINTEUR)malloc(sizeof(Maillon));
    if (m == NULL) {
        fprintf(stderr, "Erreur: allocation mémoire échouée\n");
        exit(1);
    }
    m->coeff = coeff;
    m->exposant = exposant;
    m->suivant = NULL;
    m->utile = 0;

    /* Pour Q6 (Garbage Collector) - géré par SysSec 2
     * m->general = tousLesMaillons;
     * tousLesMaillons = m;
     */

    return m;
}

/*
 * Q2: Insertion par ordre décroissant d'exposant
 * Si même exposant existe, additionne les coefficients
 */
POINTEUR insererMonome(POINTEUR tete, double coeff, int exposant) {
    POINTEUR nouveau;

    if (coeff == 0) return tete; /* Ignorer les coefficients nuls */

    nouveau = allouerMaillon(coeff, exposant);

    /* Insertion en tête si liste vide ou exposant plus grand */
    if (tete == NULL || exposant > tete->exposant) {
        nouveau->suivant = tete;
        return nouveau;
    }

    /* Si même exposant en tête */
    if (tete->exposant == exposant) {
        tete->coeff += coeff;
        /* Maillon créé devient inutile */
        tousLesMaillons = tousLesMaillons->general;
        free(nouveau);

        /* Si coefficient devient nul, éliminer le monôme */
        if (tete->coeff == 0) {
            POINTEUR temp = tete;
            tete = tete->suivant;
        }
        return tete;
    }

    /* Recherche de la position d'insertion */
    POINTEUR courant = tete;
    while (courant->suivant != NULL && courant->suivant->exposant > exposant) {
        courant = courant->suivant;
    }

    /* Vérifier si même exposant trouvé */
    if (courant->suivant != NULL && courant->suivant->exposant == exposant) {
        courant->suivant->coeff += coeff;
        /* Maillon créé devient inutile */
        tousLesMaillons = tousLesMaillons->general;
        free(nouveau);

        if (courant->suivant->coeff == 0) {
            POINTEUR temp = courant->suivant;
            courant->suivant = temp->suivant;
        }
        return tete;
    }

    /* Insertion au milieu */
    nouveau->suivant = courant->suivant;
    courant->suivant = nouveau;
    return tete;
}

/* ============================================================
 * QUESTION 3: AFFICHAGE
 * Assigné à: IABD 1 - COMPLÉTÉ ✓
 * Format: "3.00X^2 + 2.00X - 1.00"
 * ============================================================

/*
 * Q3: Affichage formaté d'un polynôme
 * Affiche sous la forme: coefficientX^exposant + coefficientX^exposant ...
 */
void afficherPolynome(POINTEUR p) {
    if (p == NULL) {
        printf("0");
        return;
    }

    int premier = 1;
    while (p != NULL) {
        if (!premier && p->coeff > 0) {
            printf(" + ");
        } else if (p->coeff < 0) {
            printf(" - ");
        }

        if (p->exposant == 0 || fabs(p->coeff) != 1.0) {
            printf("%.2f", fabs(p->coeff));
        }

        if (p->exposant > 0) {
            printf("X");
            if (p->exposant > 1) {
                printf("^%d", p->exposant);
            }
        }
        premier = 0;
        p = p->suivant;
    }
}

/* ============================================================
 * QUESTION 4: ÉVALUATION
 * Assigné à: Telecom Réseau - À IMPLÉMENTER ⏳
 * ============================================================
 * Objectif: Calculer P(x) pour un x donné
 * Formule: Σ(coeff * x^exposant)
 */

double eval(POINTEUR p, double x) {
    /* TODO Q4: IMPLÉMENTER PAR Telecom Réseau
     * Indice: Parcourir la liste et sommer coeff * pow(x, exposant)
     * 
     * Exemple: P(X) = 3X^2 + 2X - 1
     * eval(P, 2) = 3*2^2 + 2*2 - 1 = 12 + 4 - 1 = 15
     */
    
    /* Placeholder - À remplacer par l'implémentation réelle */
    (void)p; /* Pour éviter le warning */
    (void)x; /* Pour éviter le warning */
    
    /* Telecom Réseau: Implémentez ici! */
    /* 
    double resultat = 0.0;
    while (p != NULL) {
        resultat += p->coeff * pow(x, p->exposant);
        p = p->suivant;
    }
    return resultat;
    */
    
    return 0.0; /* TEMPORAIRE - À SUPPRIMER */
}

/* ============================================================
 * QUESTION 5: OPÉRATIONS ARITHMÉTIQUES
 * ============================================================
 */

/*
 * Q5a: ADDITION
 * Assigné à: IABD 2 - À IMPLÉMENTER ⏳
 * Objectif: Calculer a + b
 */
POINTEUR plus(POINTEUR a, POINTEUR b) {
    /* TODO Q5a: IMPLÉMENTER PAR IABD 2
     * Indice: Fusionner deux listes triées (décroissant)
     * Additionner coefficients si même exposant
     */
    
    /* Placeholder - À remplacer */
    (void)a;
    (void)b;
    
    /* IABD 2: Implémentez ici! */
    
    return NULL; /* TEMPORAIRE - À SUPPRIMER */
}

/*
 * Q5b: SOUSTRACTION
 * Assigné à: IABD 2 - À IMPLÉMENTER ⏳
 * Objectif: Calculer a - b
 */
POINTEUR moins(POINTEUR a, POINTEUR b) {
    /* TODO Q5b: IMPLÉMENTER PAR IABD 2
     * Indice: Similaire à l'addition mais avec signes négatifs
     */
    
    /* Placeholder - À remplacer */
    (void)a;
    (void)b;
    
    /* IABD 2: Implémentez ici! */
    
    return NULL; /* TEMPORAIRE - À SUPPRIMER */
}

/*
 * Q5c: MULTIPLICATION
 * Assigné à: SysSec 1 - À IMPLÉMENTER ⏳
 * Objectif: Calculer a * b
 */
POINTEUR fois(POINTEUR a, POINTEUR b) {
    /* TODO Q5c: IMPLÉMENTER PAR SysSec 1
     * Indice: Double boucle (distributivité)
     * (a+b)*(c+d) = ac + ad + bc + bd
     * Multiplier coefficients et additionner exposants
     */
    
    /* Placeholder - À remplacer */
    (void)a;
    (void)b;
    
    /* SysSec 1: Implémentez ici! */
    
    return NULL; /* TEMPORAIRE - À SUPPRIMER */
}

/*
 * Q5d: DIVISION EUCLIDIENNE
 * Assigné à: SysSec 1 - À IMPLÉMENTER ⏳
 * Objectif: Calculer quotient et reste
 * Algorithme: Division polynomiale classique
 *         a = b * quotient + reste
 */
POINTEUR quotient(POINTEUR a, POINTEUR b, POINTEUR *reste) {
    /* TODO Q5d: IMPLÉMENTER PAR SysSec 1
     * Indice: Algorithme similaire à la division entière
     * Tant que deg(reste) >= deg(b):
     *   terme = coeff_reste / coeff_b, exp_reste - exp_b
     *   quotient = quotient + terme
     *   reste = reste - (b * terme)
     */
    
    /* Placeholder - À remplacer */
    (void)a;
    (void)b;
    
    /* SysSec 1: Implémentez ici! */
    
    *reste = NULL; /* TEMPORAIRE - À SUPPRIMER */
    return NULL;    /* TEMPORAIRE - À SUPPRIMER */
}

/* ============================================================
 * QUESTION 6: GARBAGE COLLECTOR
 * Assigné à: SysSec 2 - À IMPLÉMENTER ⏳
 * ============================================================
 * Algorithme: Mark and Sweep
 * 1. Marquer tous les maillons accessibles depuis polyUtile[]
 * 2. Libérer les maillons non marqués
 */

/*
 * Q6a: Marquer les maillons utiles
 */
void marquerUtiles(void) {
    /* TODO Q6a: IMPLÉMENTER PAR SysSec 2
     * Indice: Parcourir récursivement depuis chaque polyUtile[]
     * Mettre utile = 1 pour les maillons accessibles
     */
    
    /* SysSec 2: Implémentez ici! */
}

/*
 * Q6b: Libérer les maillons non marqués
 */
void libererInutiles(void) {
    /* TODO Q6b: IMPLÉMENTER PAR SysSec 2
     * Indice: Parcourir tousLesMaillons et free() si utile == 0
     * Mettre à jour les liens dans la liste générale
     */
    
    /* SysSec 2: Implémentez ici! */
}

/*
 * Q6c: Fonction principale du GC
 */
void garbageCollector(void) {
    /* TODO Q6c: IMPLÉMENTER PAR SysSec 2
     * Indice: Appeler marquerUtiles() puis libererInutiles()
     */
    
    /* SysSec 2: Implémentez ici! */
}

/* ============================================================
 * UTILITAIRES (optionnels)
 * ============================================================
 */

void ajouterPolyUtile(POINTEUR p) {
    if (nbPolyUtiles < 100) {
        polyUtile[nbPolyUtiles] = p;
        nbPolyUtiles++;
    } else {
        fprintf(stderr, "Erreur: trop de polynômes utiles\n");
    }
}

POINTEUR copierMonome(POINTEUR m) {
    if (m == NULL) return NULL;
    return allouerMaillon(m->coeff, m->exposant);
}

void libererPolynome(POINTEUR p) {
    int i, j;
    for (i = 0; i < nbPolyUtiles; i++) {
        if (polyUtile[i] == p) {
            for (j = i; j < nbPolyUtiles - 1; j++) {
                polyUtile[j] = polyUtile[j + 1];
            }
            nbPolyUtiles--;
            break;
        }
    }
}
