/*
 * polynome.c - Implementation des fonctions pour la manipulation des polynomes
 * Tableau noir - Question sur les listes chainees - Exercice C
 */

#include "../include/polynome.h"
#include <string.h>
#include <ctype.h>
#include <math.h>

/* ============================================================
 * VARIABLES GLOBALES (pour le garbage collector Q7)
 * ============================================================ */
POINTEUR tousLesMaillons = NULL;
POINTEUR polyUtile[100];
int nbPolyUtiles = 0;

/* Pour l'analyseur lexical */
typedef enum {
    TOKEN_PLUS,    /* + */
    TOKEN_MOINS,   /* - */
    TOKEN_MULT,    /* * */
    TOKEN_X,       /* X */
    TOKEN_PUISS,   /* ^ */
    TOKEN_NB,      /* nombre */
    TOKEN_FIN,     /* fin de chaine */
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

/* Declarations des fonctions internes */
static void avancer();
static void initialiserAnalyseur(char *s);
static int analyserXpuissance();
static POINTEUR analyserMonome(int signe);

/* ============================================================
 * 1. ANALYSEUR LEXICAL
 * ============================================================ */

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
                printf("Erreur: caractere '%c' inattendu a la position %d\n", texte[pos], pos);
                pos++;
            }
    }
}

static void initialiserAnalyseur(char *s) {
    texte = s;
    pos = 0;
    avancer();
}

/* ============================================================
 * 2. GESTION DES MAILLONS (avec support GC)
 * ============================================================ */

POINTEUR allouerMaillon(double coeff, int exposant) {
    POINTEUR m = (POINTEUR)malloc(sizeof(Maillon));
    if (m == NULL) {
        fprintf(stderr, "Erreur: allocation memoire echouee\n");
        exit(1);
    }
    m->coeff = coeff;
    m->exposant = exposant;
    m->suivant = NULL;
    m->utile = 0;

    /* Ajout a la liste de tous les maillons (GC) */
    m->general = tousLesMaillons;
    tousLesMaillons = m;

    return m;
}

/* ============================================================
 * 3. ANALYSEUR SYNTAXIQUE ET CODAGE (Q4)
 * ============================================================ */

/* Insertion d'un monome par ordre decroissant d'exposant (Q4) */
POINTEUR insererMonome(POINTEUR tete, double coeff, int exposant) {
    POINTEUR nouveau;

    if (coeff == 0) return tete; /* Ignorer les coefficients nuls */

    nouveau = allouerMaillon(coeff, exposant);

    /* Insertion en tete si liste vide ou exposant plus grand */
    if (tete == NULL || exposant > tete->exposant) {
        nouveau->suivant = tete;
        return nouveau;
    }

    /* Si meme exposant en tete */
    if (tete->exposant == exposant) {
        tete->coeff += coeff;
        /* Maillon cree devient inutile - on le laisse pour GC (question 7) */
        tousLesMaillons = tousLesMaillons->general; /* Retirer de la liste GC */
        free(nouveau);

        /* Si coefficient devient nul, eliminer le monome */
        if (tete->coeff == 0) {
            POINTEUR temp = tete;
            tete = tete->suivant;
            /* temp reste dans tousLesMaillons pour GC */
        }
        return tete;
    }

    /* Recherche de la position d'insertion */
    POINTEUR courant = tete;
    while (courant->suivant != NULL && courant->suivant->exposant > exposant) {
        courant = courant->suivant;
    }

    /* Verifier si meme exposant trouve */
    if (courant->suivant != NULL && courant->suivant->exposant == exposant) {
        courant->suivant->coeff += coeff;
        /* Maillon cree devient inutile */
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

static int analyserXpuissance() {
    int exposant = 1; /* Par defaut, X = X^1 */

    if (tokenCourant.type == TOKEN_PUISS) {
        avancer();
        if (tokenCourant.type == TOKEN_NB) {
            exposant = (int)tokenCourant.valeur;
            if (exposant < 0) {
                printf("Erreur: exposant negatif non autorise\n");
                exit(1);
            }
            avancer();
        } else {
            printf("Erreur: exposant attendu apres '^'\n");
            exit(1);
        }
    }

    return exposant;
}

static POINTEUR analyserMonome(int signe) {
    double coeff = 1.0;
    int exposant = 0;
    int aCoeff = 0;
    int aX = 0;

    /* Premier element: nombre ou X */
    if (tokenCourant.type == TOKEN_NB) {
        coeff = tokenCourant.valeur;
        aCoeff = 1;
        avancer();

        /* Verifier si * X suit */
        if (tokenCourant.type == TOKEN_MULT) {
            avancer();
            if (tokenCourant.type == TOKEN_X) {
                aX = 1;
                avancer();
                exposant = analyserXpuissance();
            } else {
                printf("Erreur: 'X' attendu apres '*'\n");
                exit(1);
            }
        }
    } else if (tokenCourant.type == TOKEN_X) {
        aX = 1;
        coeff = 1.0;
        avancer();
        exposant = analyserXpuissance();
    } else {
        printf("Erreur: nombre ou X attendu, trouve token=%d\n", tokenCourant.type);
        exit(1);
    }

    coeff *= signe;
    return insererMonome(NULL, coeff, exposant);
}

POINTEUR analyserPolynome(char *texte) {
    POINTEUR p = NULL;
    int signeGlobal = 1;

    initialiserAnalyseur(texte);

    /* Gerer le signe initial du polynome */
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
 * 4. AFFICHAGE DES POLYNOMES (Q4)
 * ============================================================ */

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
 * QUESTION 5: EVALUATION
 * ============================================================ */

double eval(POINTEUR p, double x) {
    double resultat = 0.0;
    while (p != NULL) {
        resultat += p->coeff * pow(x, p->exposant);
        p = p->suivant;
    }
    return resultat;
}

/* ============================================================
 * QUESTION 6: OPERATIONS ARITHMETIQUES
 * ============================================================ */

/* Addition de deux polynomes */
POINTEUR plus(POINTEUR a, POINTEUR b) {
    POINTEUR resultat = NULL;

    /* Parcourir les deux polynomes simultanement */
    while (a != NULL && b != NULL) {
        if (a->exposant > b->exposant) {
            resultat = insererMonome(resultat, a->coeff, a->exposant);
            a = a->suivant;
        } else if (a->exposant < b->exposant) {
            resultat = insererMonome(resultat, b->coeff, b->exposant);
            b = b->suivant;
        } else {
            /* Meme exposant : additionner les coefficients */
            resultat = insererMonome(resultat, a->coeff + b->coeff, a->exposant);
            a = a->suivant;
            b = b->suivant;
        }
    }

    /* Ajouter les monomes restants de a */
    while (a != NULL) {
        resultat = insererMonome(resultat, a->coeff, a->exposant);
        a = a->suivant;
    }

    /* Ajouter les monomes restants de b */
    while (b != NULL) {
        resultat = insererMonome(resultat, b->coeff, b->exposant);
        b = b->suivant;
    }

    return resultat;
}

/* Soustraction de deux polynomes */
POINTEUR moins(POINTEUR a, POINTEUR b) {
    POINTEUR resultat = NULL;

    /* Parcourir les deux polynomes simultanement */
    while (a != NULL && b != NULL) {
        if (a->exposant > b->exposant) {
            resultat = insererMonome(resultat, a->coeff, a->exposant);
            a = a->suivant;
        } else if (a->exposant < b->exposant) {
            resultat = insererMonome(resultat, -b->coeff, b->exposant);
            b = b->suivant;
        } else {
            /* Meme exposant : soustraire les coefficients */
            resultat = insererMonome(resultat, a->coeff - b->coeff, a->exposant);
            a = a->suivant;
            b = b->suivant;
        }
    }

    /* Ajouter les monomes restants de a */
    while (a != NULL) {
        resultat = insererMonome(resultat, a->coeff, a->exposant);
        a = a->suivant;
    }

    /* Soustraire les monomes restants de b */
    while (b != NULL) {
        resultat = insererMonome(resultat, -b->coeff, b->exposant);
        b = b->suivant;
    }

    return resultat;
}

/* Multiplication de deux polynomes */
POINTEUR fois(POINTEUR a, POINTEUR b) {
    POINTEUR resultat = NULL;
    POINTEUR tempA = a;
    POINTEUR tempB;

    while (tempA != NULL) {
        tempB = b;
        while (tempB != NULL) {
            double nouveauCoeff = tempA->coeff * tempB->coeff;
            int nouvelExposant = tempA->exposant + tempB->exposant;
            resultat = insererMonome(resultat, nouveauCoeff, nouvelExposant);
            tempB = tempB->suivant;
        }
        tempA = tempA->suivant;
    }

    return resultat;
}

/* Division euclidienne: quotient et reste */
POINTEUR quotient(POINTEUR a, POINTEUR b, POINTEUR *reste) {
    POINTEUR q = NULL;
    POINTEUR r = NULL;
    POINTEUR temp;

    /* Copier le dividende a dans r */
    temp = a;
    while (temp != NULL) {
        r = insererMonome(r, temp->coeff, temp->exposant);
        temp = temp->suivant;
    }

    /* Verifier que le diviseur n'est pas nul */
    if (b == NULL) {
        fprintf(stderr, "Erreur: division par un polynome nul\n");
        exit(1);
    }

    /* Algorithme de division euclidienne */
    while (r != NULL && r->exposant >= b->exposant) {
        double coeffQuotient = r->coeff / b->coeff;
        int exposantQuotient = r->exposant - b->exposant;

        /* Ajouter le terme au quotient */
        q = insererMonome(q, coeffQuotient, exposantQuotient);

        /* Soustraire (b * terme_quotient) de r */
        POINTEUR terme = NULL;
        terme = insererMonome(terme, coeffQuotient, exposantQuotient);
        POINTEUR produit = fois(b, terme);
        POINTEUR nouveauR = moins(r, produit);

        /* Mettre a jour r */
        r = nouveauR;
    }

    *reste = r;
    return q;
}

/* ============================================================
 * QUESTION 7: GARBAGE COLLECTOR
 * ============================================================ */

/* Marque recursivement tous les maillons accessibles depuis un polynome */
static void marquerPolynome(POINTEUR p) {
    while (p != NULL) {
        p->utile = 1;
        p = p->suivant;
    }
}

/* Marque tous les maillons accessibles depuis les polynomes utiles */
void marquerUtiles(void) {
    /* Reinitialiser tous les marquages */
    POINTEUR courant = tousLesMaillons;
    while (courant != NULL) {
        courant->utile = 0;
        courant = courant->general;
    }

    /* Marquer les polynomes utiles */
    int i;
    for (i = 0; i < nbPolyUtiles; i++) {
        marquerPolynome(polyUtile[i]);
    }
}

/* Libere les maillons non marques */
void libererInutiles(void) {
    POINTEUR courant = tousLesMaillons;
    POINTEUR precedent = NULL;

    while (courant != NULL) {
        if (courant->utile == 0) {
            /* Maillon non utilise : le liberer */
            POINTEUR aLiberer = courant;
            courant = courant->general;

            if (precedent == NULL) {
                tousLesMaillons = courant;
            } else {
                precedent->general = courant;
            }

            free(aLiberer);
        } else {
            /* Maillon utilise : garder */
            precedent = courant;
            courant = courant->general;
        }
    }
}

/* Fonction principale du GC */
void garbageCollector(void) {
    marquerUtiles();
    libererInutiles();
}

/* ============================================================
 * UTILITAIRES
 * ============================================================ */

void ajouterPolyUtile(POINTEUR p) {
    if (nbPolyUtiles < 100) {
        polyUtile[nbPolyUtiles] = p;
        nbPolyUtiles++;
    } else {
        fprintf(stderr, "Erreur: trop de polynomes utiles\n");
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
            /* Decaler les elements */
            for (j = i; j < nbPolyUtiles - 1; j++) {
                polyUtile[j] = polyUtile[j + 1];
            }
            nbPolyUtiles--;
            break;
        }
    }
}
