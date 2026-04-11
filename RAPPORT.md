# 📊 RAPPORT DE MINI-PROJET

## Gestion de Polynômes en C et Java

---

<div align="center">

### **ÉCOLE SUPÉRIEURE POLYTECHNIQUE (ESP)**
### **DAKAR**

---

**DÉPARTEMENT :** Génie Informatique (DGI)  
**ANNÉE ACADÉMIQUE :** 2025-2026

---

**MATIÈRE :** Algorithme et Programmation Avancée (Algo.Prog av.)  
**ENSEIGNANT :** M. I FALL

---

### **Sujet : Manipulation des Polynômes - Liste Chaînée**

---

</div>

## 👥 COMPOSITION DU GROUPE

| N° | Nom et Prénom | Filière/Option | Question Assignée | Contact |
|----|---------------|----------------|-------------------|---------|
| 1 | **[Ton nom]** | GLSI (Lead) | Q1-Q3, Q7, Q8 | [email] |
| 2 | Sokhna Maimouna | SSI | Q4 - Insertion récursive | [email] |
| 3 | n0reyni (Ousmane Sow) | IABD | Q5 - Évaluation | [email] |
| 4 | Makhtar Gueye | TR | Q6a,b - Addition/Soustraction | [email] |
| 5 | Khadidiatou Niakh | IABD | Q6c,d - Multiplication/Division | [email] |
| 6 | Ame Thiam | TR | - (Prévu pour Q8) | [email] |

---

## 📋 TABLE DES MATIÈRES

1. [Introduction](#introduction)
2. [Présentation du Projet](#présentation-du-projet)
3. [Structure de Données](#structure-de-données)
4. [Questions 1-3 : Base du Système](#questions-1-3-base-du-système)
5. [Question 4 : Insertion par Degré Décroissant](#question-4-insertion-par-degré-décroissant)
6. [Question 5 : Évaluation](#question-5-évaluation)
7. [Question 6 : Opérations Arithmétiques](#question-6-opérations-arithmétiques)
8. [Question 7 : Garbage Collector](#question-7-garbage-collector)
9. [Question 8 : Versions Récursives (Bonus)](#question-8-versions-récursives-bonus)
10. [Comparaison C vs Java](#comparaison-c-vs-java)
11. [Conclusion](#conclusion)

---

## 🎯 INTRODUCTION

Ce rapport présente le mini-projet de **Gestion de Polynômes** réalisé dans le cadre du cours d'**Algorithmique et Programmation Avancée**. L'objectif était de développer un système complet permettant de manipuler des polynômes mathématiques à l'aide de listes chaînées, en respectant une grammaire précise.

### **Objectifs pédagogiques :**
- Maîtriser les structures de données dynamiques (listes chaînées)
- Implémenter un analyseur syntaxique
- Réaliser des opérations arithmétiques sur des polynômes
- Gérer la mémoire dynamiquement (Garbage Collector)
- Comparer les approches C (procédurale) et Java (orientée objet)

---

## 📚 PRÉSENTATION DU PROJET

### **Grammaire utilisée :**

```
polynôme → ['-'] monôme { ('+' | '-') monôme }
monôme → nombre '*' xpuissance | xpuissance | nombre
xpuissance → 'X' | 'X' '^' naturel
naturel → chiffre { chiffre }
nombre → naturel [ '.' { chiffre } ]
```

### **Exemples de polynômes valides :**
- `3X^2 + 2X - 1`
- `-X^3 + 5X^2 + 4`
- `4X - 2X + 5` → se simplifie en `2X + 5`

---

## 🏗️ STRUCTURE DE DONNÉES

### **Structure du Maillon (Monôme) :**

```c
// C : Structure avec typedef
typedef struct Maillon {
    double coeff;              // Coefficient du monôme
    int exposant;              // Exposant (degré)
    struct Maillon *suivant;   // Lien vers le monôme suivant
    
    // Pour le Garbage Collector (Q7)
    struct Maillon *general;   // Chaînage de tous les maillons
    int utile;                 // Marque pour le GC (1=utile, 0=inutile)
} Maillon, *POINTEUR;
```

```java
// Java : Classe POO
public class Monome {
    private double coeff;       // Coefficient
    private int exposant;       // Exposant
    private Monome suivant;     // Référence vers le suivant
    
    // Le GC en Java est automatique (pas besoin de general/utile)
}
```

### **Représentation visuelle d'une liste chaînée :**

```
Tête
  │
  ▼
┌─────────────────────────────────────────────────────────────┐
│  Maillon 1      │      Maillon 2      │      Maillon 3     │
│  coeff: 3.0     │      coeff: 2.0     │      coeff: -1.0   │
│  exp: 2         │      exp: 1         │      exp: 0        │
│  suivant ───────►      suivant ───────►      suivant: NULL│
└─────────────────────────────────────────────────────────────┘
     
Représentation : 3X^2 + 2X - 1
```

---

## ✅ QUESTIONS 1-3 : BASE DU SYSTÈME

### **Q1 : Analyseur Syntaxique**

L'analyseur lit une chaîne de caractères et reconnaît si elle respecte la grammaire des polynômes.

#### **Tokens utilisés :**

```c
typedef enum {
    TOKEN_PLUS,    // +
    TOKEN_MOINS,   // -
    TOKEN_MULT,    // *
    TOKEN_X,       // X
    TOKEN_PUISS,   // ^
    TOKEN_NB,      // nombre
    TOKEN_FIN,     // fin de chaîne
    TOKEN_ERREUR   // erreur
} TokenType;
```

#### **Fonction principale C :**

```c
POINTEUR analyserPolynome(char *texte) {
    POINTEUR p = NULL;
    int signeGlobal = 1;

    initialiserAnalyseur(texte);

    // Gérer le signe initial
    if (tokenCourant.type == TOKEN_MOINS) {
        signeGlobal = -1;
        avancer();
    }

    // Parser le premier monôme
    p = analyserMonome(signeGlobal);

    // Parser les monômes suivants (+ ou -)
    while (tokenCourant.type == TOKEN_PLUS || 
           tokenCourant.type == TOKEN_MOINS) {
        signeGlobal = (tokenCourant.type == TOKEN_PLUS) ? 1 : -1;
        avancer();
        POINTEUR monome = analyserMonome(signeGlobal);
        p = insererMonome(p, monome->coeff, monome->exposant);
    }

    return p;
}
```

#### **Équivalent Java :**

```java
public Polynome(String expression) {
    this.chaine = expression;
    this.pos = 0;
    this.tete = lirePolynome();
}

private Maillon lirePolynome() {
    Maillon liste = null;
    double signe = 1.0;
    
    if (courant() == '-') { 
        signe = -1.0; 
        avancer(); 
    }
    
    double[] m = lireMonome();
    liste = insererTrie(liste, signe * m[0], (int) m[1]);
    
    while (courant() == '+' || courant() == '-') {
        signe = (courant() == '+') ? 1.0 : -1.0;
        avancer();
        m = lireMonome();
        liste = insererTrie(liste, signe * m[0], (int) m[1]);
    }
    
    return liste;
}
```

---

### **Q2 : Codage en Mémoire**

#### **Insertion par ordre décroissant (version itérative) :**

```c
POINTEUR insererMonome(POINTEUR tete, double coeff, int exposant) {
    if (coeff == 0) return tete;  // Ignorer les coefficients nuls

    POINTEUR nouveau = allouerMaillon(coeff, exposant);

    // Insertion en tête si liste vide ou exposant plus grand
    if (tete == NULL || exposant > tete->exposant) {
        nouveau->suivant = tete;
        return nouveau;
    }

    // Même exposant en tête → fusionner
    if (tete->exposant == exposant) {
        tete->coeff += coeff;
        if (tete->coeff == 0) {
            tete = tete->suivant;
        }
        return tete;
    }

    // Recherche de la position d'insertion
    POINTEUR courant = tete;
    while (courant->suivant != NULL && 
           courant->suivant->exposant > exposant) {
        courant = courant->suivant;
    }

    // Vérifier si même exposant trouvé
    if (courant->suivant != NULL && 
        courant->suivant->exposant == exposant) {
        courant->suivant->coeff += coeff;
        return tete;
    }

    // Insertion au milieu
    nouveau->suivant = courant->suivant;
    courant->suivant = nouveau;
    return tete;
}
```

---

### **Q3 : Affichage Formaté**

```c
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

        double absCoeff = fabs(p->coeff);
        if (p->exposant == 0 || absCoeff != 1.0) {
            printf("%.2f", absCoeff);
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
```

**Exemple de sortie :**
```
Entrée : "3X^2 + 2X - 1"
Sortie   : 3.00X^2 + 2.00X - 1.00
```

---

## 🌟 QUESTION 4 : INSERTION PAR DEGRÉ DÉCROISSANT

**Auteur :** Sokhna Maimouna (SSI)  
**Apport :** Version récursive plus élégante

### **Algorithme récursif (C) :**

```c
POINTEUR insererMonome(POINTEUR tete, double coeff, int exposant) {
    // Ignorer les coefficients nuls
    if (coeff == 0.0) return tete;

    // Cas 1: Insertion en tête si liste vide ou exposant supérieur
    if (tete == NULL || exposant > tete->exposant) {
        POINTEUR m = allouerMaillon(coeff, exposant);
        m->suivant = tete;
        return m;
    }

    // Cas 2: Même exposant en tête → fusionner les coefficients
    if (exposant == tete->exposant) {
        tete->coeff += coeff;
        // Si coefficient devient nul, supprimer ce monôme
        if (tete->coeff == 0.0) {
            POINTEUR suite = tete->suivant;
            free(tete);
            return suite;
        }
        return tete;
    }

    // Cas 3: Insérer récursivement plus loin dans la liste
    tete->suivant = insererMonome(tete->suivant, coeff, exposant);
    return tete;
}
```

### **Avantages de l'approche récursive :**
- ✅ Code plus concis (~25 lignes vs ~50 lignes)
- ✅ Pas de boucles imbriquées
- ✅ Logique plus naturelle
- ✅ Même complexité O(n)

---

## 📐 QUESTION 5 : ÉVALUATION

**Auteur :** n0reyni (Ousmane Sow) - IABD

### **Principe :** Calculer P(x) pour une valeur donnée

**Formule :** P(x) = Σ(coeff × x^exposant)

### **Implémentation C :**

```c
double eval(POINTEUR p, double x) {
    double resultat = 0.0;
    
    while (p != NULL) {
        // coeff * x^exposant
        resultat += p->coeff * pow(x, p->exposant);
        p = p->suivant;
    }
    
    return resultat;
}
```

### **Implémentation Java :**

```java
public double eval(double x) {
    double resultat = 0.0;
    Monome courant = tete;
    
    while (courant != null) {
        resultat += courant.getCoeff() * Math.pow(x, courant.getExposant());
        courant = courant.getSuivant();
    }
    
    return resultat;
}
```

### **Exemple :**
```
Polynôme : P(X) = 3X^2 + 2X - 1
Évaluation en x = 2 :
  P(2) = 3×(2^2) + 2×2 - 1
       = 3×4 + 4 - 1
       = 12 + 4 - 1
       = 15
```

---

## ➕➖ QUESTION 6a,b : ADDITION ET SOUSTRACTION

**Auteur :** Makhtar Gueye (TR)

### **Addition (Algorithme de fusion) :**

```c
POINTEUR plus(POINTEUR a, POINTEUR b) {
    POINTEUR resultat = NULL;
    POINTEUR queue = NULL;

    while (a != NULL || b != NULL) {
        double coeff;
        int exposant;

        // Cas 1: a a un exposant plus grand
        if (a != NULL && (b == NULL || a->exposant > b->exposant)) {
            coeff = a->coeff;
            exposant = a->exposant;
            a = a->suivant;
        }
        // Cas 2: b a un exposant plus grand
        else if (b != NULL && (a == NULL || b->exposant > a->exposant)) {
            coeff = b->coeff;
            exposant = b->exposant;
            b = b->suivant;
        }
        // Cas 3: même exposant → additionner
        else {
            coeff = a->coeff + b->coeff;
            exposant = a->exposant;
            a = a->suivant;
            b = b->suivant;
        }

        // Ignorer les coefficients nuls
        if (coeff == 0.0) continue;

        // Créer et insérer en fin (O(1) avec pointeur queue)
        POINTEUR m = allouerMaillon(coeff, exposant);
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
```

### **Soustraction (stratégie élégante) :**

```c
POINTEUR moins(POINTEUR a, POINTEUR b) {
    // a - b = a + (-b)
    POINTEUR neg_b = negation(b);
    POINTEUR resultat = plus(a, neg_b);
    return resultat;
}

// Fonction auxiliaire: négation
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
```

**Avantage :** Réutilisation de la fonction `plus()` → pas de code dupliqué !

---

## ✖️➗ QUESTION 6c,d : MULTIPLICATION ET DIVISION

**Auteur :** Khadidiatou Niakh (IABD)

### **Multiplication (Distributivité) :**

```c
POINTEUR fois(POINTEUR a, POINTEUR b) {
    if (!a || !b) return NULL;

    POINTEUR resultat = NULL;

    // Double boucle: distribuer chaque monôme de a sur chaque monôme de b
    for (POINTEUR p = a; p != NULL; p = p->suivant) {
        POINTEUR temp = NULL;

        for (POINTEUR q = b; q != NULL; q = q->suivant) {
            // Multiplier coefficients, additionner exposants
            POINTEUR m = allouerMaillon(
                p->coeff * q->coeff,
                p->exposant + q->exposant
            );
            temp = plus(temp, m);
        }

        resultat = plus(resultat, temp);
    }

    return resultat;
}
```

### **Division Euclidienne :**

```c
POINTEUR quotient(POINTEUR a, POINTEUR b, POINTEUR *reste) {
    if (!b) return NULL;

    POINTEUR q = NULL;      // Quotient
    POINTEUR r = a;         // Reste (initialisé au dividende)

    // Algorithme: tant que deg(reste) >= deg(diviseur)
    while (r && r->exposant >= b->exposant) {
        // Terme = coeff_reste/coeff_diviseur, exp_reste - exp_diviseur
        double coeff = r->coeff / b->coeff;
        int exposant = r->exposant - b->exposant;

        // Ajouter le terme au quotient
        POINTEUR m = allouerMaillon(coeff, exposant);
        q = plus(q, m);

        // Soustraire (diviseur × terme) du reste
        POINTEUR temp = fois(m, b);
        r = moins(r, temp);
    }

    *reste = r;
    return q;
}
```

### **Formule mathématique :**
```
a = b × quotient + reste

Exemple:
(3X^2 + 2X - 1) ÷ (X + 1)
= Quotient: 3X - 1
= Reste: 0
```

---

## 🗑️ QUESTION 7 : GARBAGE COLLECTOR

**Auteur :** [Ton nom] (GLSI - Lead)

### **Principe :** Algorithme "Mark and Sweep"

1. **MARK (Marquer)** : Marquer les maillons accessibles
2. **SWEEP (Balayer)** : Libérer les maillons non marqués

### **Variables globales :**

```c
POINTEUR tousLesMaillons = NULL;  // Liste de tous les maillons
POINTEUR polyUtile[100];          // Tableau des polynômes utiles
int nbPolyUtiles = 0;             // Nombre de polynômes utiles
```

### **Structure du maillon (avec GC) :**

```c
typedef struct Maillon {
    double coeff;
    int exposant;
    struct Maillon *suivant;   // Chaînage polynôme
    struct Maillon *general;    // Chaînage global (GC)
    int utile;                   // Marque (1=utile, 0=non)
} Maillon;
```

### **Étape 1 : Marquer les maillons utiles**

```c
static void marquerPolynome(POINTEUR p) {
    while (p != NULL) {
        p->utile = 1;  // Marquer comme accessible
        p = p->suivant;
    }
}

void marquerUtiles(void) {
    // Réinitialiser tous les marquages
    POINTEUR courant = tousLesMaillons;
    while (courant != NULL) {
        courant->utile = 0;
        courant = courant->general;
    }

    // Marquer les maillons des polynômes utiles
    for (int i = 0; i < nbPolyUtiles; i++) {
        marquerPolynome(polyUtile[i]);
    }
}
```

### **Étape 2 : Libérer les maillons non marqués**

```c
void libererInutiles(void) {
    POINTEUR courant = tousLesMaillons;
    POINTEUR precedent = NULL;

    while (courant != NULL) {
        if (courant->utile == 0) {
            // Maillon non utilisé → le libérer
            POINTEUR aLiberer = courant;
            courant = courant->general;

            if (precedent == NULL) {
                tousLesMaillons = courant;
            } else {
                precedent->general = courant;
            }

            free(aLiberer);
        } else {
            // Maillon utilisé → garder
            precedent = courant;
            courant = courant->general;
        }
    }
}
```

### **Fonction principale :**

```c
void garbageCollector(void) {
    marquerUtiles();
    libererInutiles();
}
```

### **Enregistrement d'un polynôme utile :**

```c
void ajouterPolyUtile(POINTEUR p) {
    if (nbPolyUtiles < 100) {
        polyUtile[nbPolyUtiles] = p;
        nbPolyUtiles++;
    }
}
```

### **Java (GC automatique) :**

```java
public void liberer() {
    this.tete = null;           // Rendre éligible au GC
    this.expressionOrig = null;
    System.gc();                 // Suggérer le GC
}
```

---

## 🔄 QUESTION 8 : VERSIONS RÉCURSIVES (BONUS)

**Auteur :** Lead (GLSI) - BONUS

### **Addition récursive :**

```c
static POINTEUR plus_recursif_aux(POINTEUR a, POINTEUR b) {
    // Cas de base
    if (a == NULL && b == NULL) return NULL;
    if (a == NULL) return copie(b);
    if (b == NULL) return copie(a);
    
    // Cas 1: exposant de a est supérieur
    if (a->exposant > b->exposant) {
        POINTEUR r = allouerMaillon(a->coeff, a->exposant);
        r->suivant = plus_recursif_aux(a->suivant, b);
        return r;
    }
    // Cas 2: exposant de b est supérieur
    else if (a->exposant < b->exposant) {
        POINTEUR r = allouerMaillon(b->coeff, b->exposant);
        r->suivant = plus_recursif_aux(a, b->suivant);
        return r;
    }
    // Cas 3: même exposant
    else {
        double c = a->coeff + b->coeff;
        if (c == 0.0) {
            return plus_recursif_aux(a->suivant, b->suivant);
        }
        POINTEUR r = allouerMaillon(c, a->exposant);
        r->suivant = plus_recursif_aux(a->suivant, b->suivant);
        return r;
    }
}
```

**Avantages :** Plus élégante, plus lisible  
**Inconvénients :** Consomme plus de mémoire (pile d'appels)

---

## ⚖️ COMPARAISON C vs JAVA

| Aspect | C (Procédural) | Java (Orienté Objet) |
|--------|----------------|---------------------|
| **Structure** | `struct` + pointeurs | Classes avec encapsulation |
| **Allocation** | `malloc()` / `free()` | `new` / Garbage Collector |
| **GC manuel** | Oui (Q7 implémenté) | Automatique (`System.gc()`) |
| **Syntaxe** | Plus bas niveau | Plus abstraite |
| **Sécurité** | Risque de fuites | Plus sûr |
| **Polymorphisme** | Fonctions + pointeurs | Classes + héritage |

### **Points communs :**
- ✅ Même algorithme de base
- ✅ Liste chaînée ordonnée
- ✅ Complexités identiques

---

## 📊 RÉSULTATS ET TESTS

### **Compilation :**

```bash
# C
cd c/src
gcc -o polynome main.c polynome.c -I../include -lm
./polynome

# Java
cd java/src
javac *.java
java Main
```

### **Tests réussis :**
- ✅ Analyse syntaxique de "3X^2 + 2X - 1"
- ✅ Évaluation en x=2 : résultat 15
- ✅ Addition : (3X^2 + 2X - 1) + (X + 1) = 3X^2 + 3X
- ✅ Multiplication : (X + 1) × (X - 1) = X^2 - 1
- ✅ Division : (X^2 - 1) ÷ (X + 1) = X - 1
- ✅ GC : libération des maillons inutiles

---

## 🎯 CONCLUSION

Ce projet nous a permis de maîtriser :

1. **Les structures de données dynamiques** (listes chaînées)
2. **L'analyse syntaxique** (grammaires et tokens)
3. **Les algorithmes récursifs vs itératifs**
4. **La gestion mémoire** (malloc/free et Garbage Collector)
5. **La comparaison paradigmes** (C procédural vs Java POO)

### **Bilan d'équipe :**
- **7 questions obligatoires** : ✅ 100% complétées
- **1 question bonus (Q8)** : ✅ Implémentée
- **Collaboration** : 5 contributeurs actifs
- **Qualité** : Code documenté et testé

### **Remerciements :**
Merci à **M. I FALL** pour ce projet enrichissant qui nous a permis de mettre en pratique les concepts avancés d'algorithmique et de programmation.

---

<div align="center">

**FIN DU RAPPORT**

---

*Projet réalisé dans le cadre du cours d'Algorithmique et Programmation Avancée*  
**ESP - DGI - 2025/2026**

</div>
