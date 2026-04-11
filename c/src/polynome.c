/**
 * @file polynome.c
 * @brief Implémentation complète des fonctions de manipulation des polynômes
 * @details Mini Projet DIC2 - Gestion de Polynômes
 * 
 * QUESTIONS COMPLÉTÉES:
 * - Q1, Q2, Q3: Analyseur, Codage, Affichage (IABD 1 - GLSI)
 * - Q4: Codage par degré décroissant (Sokhna Maimouna - SSI)
 * - Q5: Évaluation (n0reyni/Ousmane Sow - IABD)
 * - Q6a,b: Addition & Soustraction (Makhtar Gueye - TR)
 * - Q6c,d: Multiplication & Division (Khadidiatou Niakh - IABD)
 * - Q7: Garbage Collector (Lead - GLSI)
 * 
 * QUESTION EN ATTENTE:
 * - Q8: Versions récursives (Ame Thiam - TR) - BONUS
 */

#include "../include/polynome.h"
#include <string.h>
#include <ctype.h>
#include <math.h>

/* ============================================================
 * VARIABLES GLOBALES (pour Q7 - Garbage Collector)
 * ============================================================
 * Gérées par Lead (GLSI)
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
void avancer() {
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
void initialiserAnalyseur(char *s) {
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

/* Fonction interne: analyse un monôme et extrait coeff et exposant */
static int analyserMonome(int signe, double *coeff, int *exposant) {
    *coeff = 1.0;
    *exposant = 0;
    int aCoeff = 0;
    int aX = 0;

    /* Premier élément: nombre ou X */
    if (tokenCourant.type == TOKEN_NB) {
        *coeff = tokenCourant.valeur;
        aCoeff = 1;
        avancer();

        /* Vérifier si X suit (avec ou sans *) */
        if (tokenCourant.type == TOKEN_MULT) {
            /* Format: nombre * X */
            avancer();
            if (tokenCourant.type == TOKEN_X) {
                aX = 1;
                avancer();
                *exposant = analyserXpuissance();
            } else {
                printf("Erreur: 'X' attendu après '* '\n");
                exit(1);
            }
        } else if (tokenCourant.type == TOKEN_X) {
            /* Format: nombreX (sans *) */
            aX = 1;
            avancer();
            *exposant = analyserXpuissance();
        }
    } else if (tokenCourant.type == TOKEN_X) {
        aX = 1;
        *coeff = 1.0;
        avancer();
        *exposant = analyserXpuissance();
    } else {
        printf("Erreur: nombre ou X attendu\n");
        exit(1);
    }

    *coeff *= signe;
    return 1; /* Succès */
}

/*
 * Q1: Analyseur syntaxique principal
 * Lit un texte caractère par caractère et reconnaît un polynôme
 */
POINTEUR analyserPolynome(char *texte) {
    POINTEUR p = NULL;
    double coeff;
    int exposant;
    int signeGlobal = 1;

    initialiserAnalyseur(texte);

    /* Gérer le signe initial du polynôme */
    if (tokenCourant.type == TOKEN_MOINS) {
        signeGlobal = -1;
        avancer();
    } else if (tokenCourant.type == TOKEN_PLUS) {
        avancer();
    }

    /* Analyser le premier monôme */
    analyserMonome(signeGlobal, &coeff, &exposant);
    p = insererMonome(p, coeff, exposant);

    /* Analyser les monômes suivants */
    while (tokenCourant.type == TOKEN_PLUS || tokenCourant.type == TOKEN_MOINS) {
        signeGlobal = (tokenCourant.type == TOKEN_PLUS) ? 1 : -1;
        avancer();
        analyserMonome(signeGlobal, &coeff, &exposant);
        p = insererMonome(p, coeff, exposant);
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

    /* Pour Q7 (Garbage Collector) - Enregistrer dans la liste générale */
    m->general = tousLesMaillons;
    tousLesMaillons = m;

    return m;
}

/*
 * Q4: Insertion triée par degrés décroissants
 * Implémenté par: Sokhna Maimouna
 * Approche: Récursive (plus élégante que l'itérative)
 * 
 * Algorithme:
 * 1. Ignorer les coefficients nuls
 * 2. Insérer en tête si liste vide ou exposant supérieur
 * 3. Fusionner si même exposant
 * 4. Insérer récursivement sinon
 * 
 * Remerciements: Merci à Sokhna Maimouna pour cette implémentation élégante!
 */
POINTEUR insererMonome(POINTEUR tete, double coeff, int exposant) {
    /* Ignorer les coefficients nuls */
    if (coeff == 0.0) return tete;

    /* Cas 1: Insertion en tête si liste vide ou exposant supérieur */
    if (tete == NULL || exposant > tete->exposant) {
        POINTEUR m = allouerMaillon(coeff, exposant);
        m->suivant = tete;
        return m;
    }

    /* Cas 2: Même exposant en tête → fusionner les coefficients */
    if (exposant == tete->exposant) {
        tete->coeff += coeff;
        /* Si coefficient devient nul, supprimer ce monôme */
        if (tete->coeff == 0.0) {
            POINTEUR suite = tete->suivant;
            /* Pour Q7 (Garbage Collector) - marquer comme inutile */
            /* tete->utile = 0; */
            free(tete);
            return suite;
        }
        return tete;
    }

    /* Cas 3: Insérer récursivement plus loin dans la liste */
    tete->suivant = insererMonome(tete->suivant, coeff, exposant);
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
    double resultat = 0.0;

    while (p != NULL) {
        resultat += p->coeff * pow(x, p->exposant);
        p = p->suivant;
    }

    return resultat;
}

/*
 * Fonction utilitaire: retourne le degré du polynôme
 * Degré = exposant maximum
 */
int getDegre(POINTEUR p) {
    if (p == NULL) return 0;
    return p->exposant; /* Liste triée par ordre décroissant */
}

/* ============================================================
 * QUESTION 5: OPÉRATIONS ARITHMÉTIQUES
 * ============================================================
 */

/*
 * Q6a: ADDITION
 * Implémenté par: Makhtar Gueye (IABD 2)
 * 
 * Fusion de deux listes triées par ordre décroissant d'exposant.
 * Algorithme: Parcours simultané avec pointeurs tête+queue pour insertion O(1).
 * 
 * Remerciements: Merci à Makhtar Gueye pour cette implémentation optimisée!
 */
POINTEUR plus(POINTEUR a, POINTEUR b) {
    POINTEUR resultat = NULL;
    POINTEUR queue = NULL;

    while (a != NULL || b != NULL) {
        double coeff;
        int exposant;

        /* Cas 1: a a un exposant plus grand que b (ou b est vide) */
        if (a != NULL && (b == NULL || a->exposant > b->exposant)) {
            coeff = a->coeff;
            exposant = a->exposant;
            a = a->suivant;
        }
        /* Cas 2: b a un exposant plus grand que a (ou a est vide) */
        else if (b != NULL && (a == NULL || b->exposant > a->exposant)) {
            coeff = b->coeff;
            exposant = b->exposant;
            b = b->suivant;
        }
        /* Cas 3: même exposant → additionner les coefficients */
        else {
            coeff = a->coeff + b->coeff;
            exposant = a->exposant;
            a = a->suivant;
            b = b->suivant;
        }

        /* Ignorer les coefficients nuls */
        if (coeff == 0.0) continue;

        /* Créer un nouveau maillon */
        POINTEUR m = allouerMaillon(coeff, exposant);
        
        /* Insérer en fin avec pointeur queue (O(1)) */
        if (resultat == NULL) {
            resultat = m;
            queue = m;
        } else {
            queue->suivant = m;
            queue = m;
        }
    }

    return resultat;
}

/*
 * Fonction auxiliaire: Négation d'un polynôme
 * Crée une copie avec tous les coefficients multipliés par -1.
 * 
 * Utilisée par moins() pour implémenter a - b = a + (-b).
 * DOIT être définie AVANT moins() pour éviter l'erreur de déclaration implicite.
 */
static POINTEUR negation(POINTEUR p) {
    POINTEUR neg = NULL;
    POINTEUR queue = NULL;
    
    while (p != NULL) {
        POINTEUR m = allouerMaillon(-p->coeff, p->exposant);
        
        if (neg == NULL) {
            neg = m;
            queue = m;
        } else {
            queue->suivant = m;
            queue = m;
        }
        
        p = p->suivant;
    }
    
    return neg;
}

/*
 * Q6b: SOUSTRACTION
 * Implémenté par: Makhtar Gueye (TR)
 *
 * Algorithme: a - b = a + (-b)
 * Utilise la fonction negation() pour inverser b, puis appelle plus().
 *
 * Remerciements: Merci à Makhtar Gueye pour cette implémentation!
 */
POINTEUR moins(POINTEUR a, POINTEUR b) {
    /* Cas simple: b est NULL */
    if (b == NULL) {
        return a;
    }
    /* Cas simple: a est NULL → retourne -b */
    if (a == NULL) {
        return negation(b);
    }
    /* Cas général: a - b = a + (-b) */
    POINTEUR neg_b = negation(b);
    return plus(a, neg_b);
}

/*
 * Q6c: MULTIPLICATION
 * Implémenté par: Khadidiatou Niakh (SysSec 1)
 * 
 * Algorithme: Double boucle (distributivité)
 * P × Q = Σ(i) Σ(j) (pi × qj) X^(ei+ej)
 * 
 * Pour chaque monôme de a:
 *   Pour chaque monôme de b:
 *     Multiplier les coefficients
 *     Additionner les exposants
 *     Ajouter au résultat
 * 
 * Remerciements: Merci à Khadidiatou Niakh pour cette implémentation!
 */
POINTEUR fois(POINTEUR a, POINTEUR b) {
    /* Vérifier que les deux polynômes sont non nuls */
    if (!a || !b)
        return NULL;

    POINTEUR resultat = NULL;

    /* Double boucle: distribuer chaque monôme de a sur chaque monôme de b */
    for (POINTEUR p = a; p != NULL; p = p->suivant) {
        POINTEUR temp = NULL;

        for (POINTEUR q = b; q != NULL; q = q->suivant) {
            /* Créer un nouveau monôme: coeff produit, somme exposants */
            POINTEUR m = allouerMaillon(p->coeff * q->coeff, p->exposant + q->exposant);
            /* Additionner temporairement (fusionner si même exposant) */
            temp = plus(temp, m);
        }

        /* Additionner le résultat partiel au résultat global */
        resultat = plus(resultat, temp);
    }

    return resultat;
}

/*
 * Q6d: DIVISION EUCLIDIENNE
 * Implémenté par: Khadidiatou Niakh (SysSec 1)
 * 
 * Algorithme: Division polynomiale classique
 * Tant que deg(reste) >= deg(diviseur):
 *   terme = coeff_reste / coeff_diviseur, exp_reste - exp_diviseur
 *   quotient = quotient + terme
 *   reste = reste - (diviseur × terme)
 * 
 * Remerciements: Merci à Khadidiatou Niakh pour cette implémentation!
 */
POINTEUR quotient(POINTEUR a, POINTEUR b, POINTEUR *reste) {
    /* Vérifier division par zéro */
    if (!b)
        return NULL;

    POINTEUR q = NULL;      /* Quotient */
    POINTEUR r = a;         /* Reste (initialisé au dividende) */

    /* Algorithme de division euclidienne */
    while (r && r->exposant >= b->exposant) {
        /* Calculer le terme du quotient */
        double coeff = r->coeff / b->coeff;
        int exposant = r->exposant - b->exposant;

        /* Créer et ajouter le terme au quotient */
        POINTEUR m = allouerMaillon(coeff, exposant);
        q = plus(q, m);

        /* Soustraire (diviseur × terme) du reste */
        POINTEUR temp = fois(m, b);
        r = moins(r, temp);
    }

    *reste = r;
    return q;
}

/* ============================================================
 * QUESTION 7: GARBAGE COLLECTOR
 * Implémenté par: [Ton nom] (GLSI - Lead)
 * ============================================================
 * 
 * Mécanisme de recyclage de la mémoire fonctionnant "en sous-sol".
 * Algorithme: Mark and Sweep (Marquer et Balayer)
 * 
 * Principe:
 * 1. MARK (Marquer): Parcourir les polynômes utiles et marquer leurs maillons
 * 2. SWEEP (Balayer): Parcourir tousLesMaillons et libérer les non marqués
 * 
 * Chaque maillon possède:
 * - 'general': pointeur vers le maillon suivant dans la liste globale
 * - 'utile': flag indiquant si le maillon est accessible (1) ou non (0)
 * 
 * Remerciements: Merci à toute l'équipe pour cette collaboration!
 */

/*
 * Q7a: Marquer les maillons accessibles
 * 
 * Parcours récursif d'un polynôme pour marquer tous ses maillons.
 * Un maillon marqué (utile = 1) ne sera pas libéré par le GC.
 */
static void marquerPolynome(POINTEUR p) {
    while (p != NULL) {
        p->utile = 1;  /* Marquer comme accessible */
        p = p->suivant;
    }
}

/*
 * Q7a: Marquer tous les maillons utiles
 * 
 * Parcourt tous les polynômes enregistrés dans polyUtile[]
 * et marque récursivement tous leurs maillons.
 */
void marquerUtiles(void) {
    /* Réinitialiser tous les marquages */
    POINTEUR courant = tousLesMaillons;
    while (courant != NULL) {
        courant->utile = 0;  /* Réinitialiser à 0 (non marqué) */
        courant = courant->general;
    }

    /* Marquer les maillons des polynômes utiles */
    int i;
    for (i = 0; i < nbPolyUtiles; i++) {
        marquerPolynome(polyUtile[i]);
    }
}

/*
 * Q7b: Libérer les maillons non marqués
 * 
 * Parcourt la liste de tous les maillons alloués (tousLesMaillons)
 * et libère ceux qui n'ont pas été marqués (utile == 0).
 * Met à jour les liens dans la liste générale.
 */
void libererInutiles(void) {
    POINTEUR courant = tousLesMaillons;
    POINTEUR precedent = NULL;

    while (courant != NULL) {
        if (courant->utile == 0) {
            /* Maillon non utilisé : le libérer */
            POINTEUR aLiberer = courant;
            courant = courant->general;

            if (precedent == NULL) {
                tousLesMaillons = courant;
            } else {
                precedent->general = courant;
            }

            free(aLiberer);
        } else {
            /* Maillon utilisé : garder et passer au suivant */
            precedent = courant;
            courant = courant->general;
        }
    }
}

/*
 * Q7c: Fonction principale du Garbage Collector
 * 
 * Exécute le mécanisme complet de recyclage:
 * 1. Marquer les maillons accessibles
 * 2. Libérer les maillons non marqués
 * 
 * Cette fonction peut être appelée périodiquement ou manuellement
 * pour nettoyer la mémoire des maillons devenus inutiles.
 */
void garbageCollector(void) {
    marquerUtiles();
    libererInutiles();
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

/* ============================================================
 * QUESTION 8: VERSIONS RÉCURSIVES - BONUS
 * Implémenté par: Ame Thiam (TR) ou Lead (GLSI)
 * ============================================================
 * 
 * Versions récursives de l'addition et de la soustraction.
 * Ces implémentations sont plus élégantes mais consomment plus
 * de mémoire à cause de la récursion.
 */

/*
 * Q8a: Addition récursive (version bonus)
 * 
 * Approche récursive élégante:
 * - Cas de base: si a NULL, retourner copie de b; si b NULL, retourner copie de a
 * - Si a->exposant > b->exposant: créer maillon(a), puis fusionner(a->suivant, b)
 * - Si a->exposant < b->exposant: créer maillon(b), puis fusionner(a, b->suivant)
 * - Si même exposant: somme coefficients, puis fusionner(a->suivant, b->suivant)
 */
static POINTEUR plus_recursif_aux(POINTEUR a, POINTEUR b) {
    /* Cas de base: listes vides */
    if (a == NULL) return NULL;
    if (b == NULL) return NULL;
    
    /* Cas 1: exposant de a est supérieur */
    if (a->exposant > b->exposant) {
        POINTEUR r = allouerMaillon(a->coeff, a->exposant);
        r->suivant = plus_recursif_aux(a->suivant, b);
        return r;
    }
    /* Cas 2: exposant de b est supérieur */
    else if (a->exposant < b->exposant) {
        POINTEUR r = allouerMaillon(b->coeff, b->exposant);
        r->suivant = plus_recursif_aux(a, b->suivant);
        return r;
    }
    /* Cas 3: même exposant */
    else {
        double c = a->coeff + b->coeff;
        if (c == 0.0) {
            /* Sauter les deux monômes si annulation */
            return plus_recursif_aux(a->suivant, b->suivant);
        }
        POINTEUR r = allouerMaillon(c, a->exposant);
        r->suivant = plus_recursif_aux(a->suivant, b->suivant);
        return r;
    }
}

/*
 * Q8a: Addition récursive (version publique)
 * 
 * Version récursive de l'addition.
 * Plus élégante mais moins efficace que la version itérative.
 */
POINTEUR plus_recursif(POINTEUR a, POINTEUR b) {
    /* Gérer les cas simples */
    if (a == NULL && b == NULL) return NULL;
    if (a == NULL) {
        /* Copier b si a est NULL */
        if (b == NULL) return NULL;
        POINTEUR r = allouerMaillon(b->coeff, b->exposant);
        r->suivant = plus_recursif(NULL, b->suivant);
        return r;
    }
    if (b == NULL) {
        /* Copier a si b est NULL */
        POINTEUR r = allouerMaillon(a->coeff, a->exposant);
        r->suivant = plus_recursif(a->suivant, NULL);
        return r;
    }
    
    return plus_recursif_aux(a, b);
}

/*
 * Q8b: Soustraction récursive (version bonus)
 * 
 * Stratégie: a - b = a + (-b)
 * Créer une négation de b, puis appeler plus_recursif.
 */
POINTEUR moins_recursif(POINTEUR a, POINTEUR b) {
    /* Cas simple: b est NULL */
    if (b == NULL) {
        if (a == NULL) return NULL;
        POINTEUR r = allouerMaillon(a->coeff, a->exposant);
        r->suivant = moins_recursif(a->suivant, NULL);
        return r;
    }
    
    /* Créer la négation de b récursivement */
    POINTEUR neg_b = allouerMaillon(-b->coeff, b->exposant);
    neg_b->suivant = moins_recursif(NULL, b->suivant);
    
    /* Appeler plus_recursif avec a et -b */
    POINTEUR resultat = plus_recursif(a, neg_b);
    
    return resultat;
}
