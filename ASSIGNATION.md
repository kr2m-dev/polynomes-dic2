# Assignation des Tâches - Gestion de Polynômes

## 👥 Composition du Groupe (6 personnes)

| Rôle | Nom | Filière | Questions Assignées |
|------|-----|---------|---------------------|
| **🎯 Lead & Merge** | [Toi] | [Ta filière] | Gestion dépôt, review, rapport |
| **💻 Dev 1** | [Nom 1] | IABD | **Q1, Q2, Q3, Q4** - Structure & Analyseur |
| **📡 Dev 2** | [Nom 2] | Telecom Réseau | **Q5** - Évaluation |
| **💻 Dev 3** | [Nom 3] | IABD | **Q6a, Q6b, Q8** - Addition/Soustraction + Récursif |
| **🔒 Dev 4** | [Nom 4] | Système Sécurité | **Q6c, Q6d** - Multiplication/Division |
| **🔒 Dev 5** | [Nom 5] | Système Sécurité | **Q7** - Garbage Collector |

---

## 📋 Liste complète des 8 Questions

### ✅ QUESTIONS DÉJÀ COMPLÉTÉES (Base)

#### **Q1 : Analyseur Syntaxique** ✓
**Assigné à :** IABD 1  
**Fichiers :** `c/src/polynome.c`, `java/src/Polynome.java`

**Description :** Programme qui lit un texte caractère par caractère et reconnaît un mot du langage défini par la grammaire.

**Grammaire :**
```
polynôme → ['-'] monôme { ('+' | '-') monôme }
monôme → nombre '*' xpuissance | xpuissance | nombre
xpuissance → 'X' | 'X' '^' naturel
naturel → chiffre { chiffre }
nombre → naturel [ '.' { chiffre } ]
```

**Fonction :** `analyserPolynome(char *texte)`

---

#### **Q2 : Codage en Mémoire** ✓
**Assigné à :** IABD 1  
**Fichiers :** `c/src/polynome.c`, `java/src/Polynome.java`

**Description :** Un polynôme est représenté par une liste chaînée où chaque maillon représente un monôme (coefficient, exposant).

**Structure :**
```c
typedef struct Maillon {
    double coeff;
    int exposant;
    struct Maillon *suivant;
    // Pour Q7: champs supplémentaires general et utile
    struct Maillon *general;
    int utile;
} Maillon, *POINTEUR;
```

**Fonctions :** `allouerMaillon()`, `insererMonome()`

---

#### **Q3 : Affichage** ✓
**Assigné à :** IABD 1  
**Fichiers :** `c/src/polynome.c`, `java/src/Polynome.java`

**Description :** Fonction qui affiche un polynôme de manière formatée.

**Format :** `"3.00X^2 + 2.00X - 1.00"`

**Fonction :** `afficherPolynome(POINTEUR p)` / `toString()`

---

### ⏳ QUESTIONS À IMPLÉMENTER

#### **Q4 : Codage par Degré Décroissant** ⏳
**Assigné à :** IABD 1 (même personne que Q1-Q3)  
**Fichiers :** Modification de `insererMonome()`

**Description :** Modification de la question 2 pour que les monômes soient rangés par ordre décroissant des degrés.

**Règle :** Les monômes doivent être insérés par exposant décroissant.

**Indication :** Déjà implémenté dans Q2 ! (L'insertion est déjà ordonnée)

---

#### **Q5 : Évaluation** ⏳
**Assigné à :** Telecom Réseau  
**Fichiers :** `c/src/polynome.c`, `java/src/Polynome.java`

**Description :** Calcule la valeur du polynôme pour une valeur x donnée.

**Formule :** P(x) = Σ(coeff × x^exposant)

**Prototype C :**
```c
double eval(POINTEUR p, double x);
```

**Prototype Java :**
```java
public double eval(double x);
```

**Exemple :**
```
P(X) = 3X^2 + 2X - 1
eval(P, 2) = 3×2² + 2×2 - 1 = 12 + 4 - 1 = 15
```

**Conseil :** Utilisez `pow(x, exposant)` en C ou `Math.pow(x, exposant)` en Java.

---

#### **Q6 : Opérations sur les Polynômes** ⏳
**Assignés à :** IABD 2 (Q6a, Q6b) + SysSec 1 (Q6c, Q6d)

**Règles de conduite :**
- Allouer autant de maillons que nécessaire
- Ne pas modifier un polynôme créé (préférer allocation nouvelle)
- Ne pas s'occuper de la restitution des maillons inutiles (Q7 s'en chargera)

##### **Q6a : Addition** ⏳
**Assigné à :** IABD 2

**Prototype C :**
```c
POINTEUR plus(POINTEUR a, POINTEUR b);
```

**Algorithme :** Fusion de deux listes triées (décroissant). Si même exposant, additionner coefficients.

##### **Q6b : Soustraction** ⏳
**Assigné à :** IABD 2

**Prototype C :**
```c
POINTEUR moins(POINTEUR a, POINTEUR b);
```

**Algorithme :** Similaire à l'addition mais avec signes négatifs.

##### **Q6c : Multiplication** ⏳
**Assigné à :** SysSec 1

**Prototype C :**
```c
POINTEUR fois(POINTEUR a, POINTEUR b);
```

**Formule :**
```
P × Q = (aXⁿ + P') × (bXᵐ + Q') = abXⁿ⁺ᵐ + aXⁿ×Q' + P'×Q
```

**Algorithme :** Double boucle (distributivité). Multiplier coefficients et additionner exposants.

##### **Q6d : Division Euclidienne** ⏳
**Assigné à :** SysSec 1

**Prototype C :**
```c
POINTEUR quotient(POINTEUR a, POINTEUR b, POINTEUR *reste);
```

**Algorithme :**
```
Tant que deg(reste) ≥ deg(diviseur):
    terme = coeff_reste / coeff_diviseur, exp_reste - exp_diviseur
    quotient = quotient + terme
    reste = reste - (diviseur × terme)
```

**Relation :** a = b × quotient + reste

---

#### **Q7 : Meilleure Gestion de la Mémoire (Garbage Collector)** ⏳
**Assigné à :** SysSec 2

**Description :** Mécanisme de recyclage de la mémoire (garbage collector) qui fonctionne "en sous-sol".

**Structure ajoutée à chaque maillon (déjà dans le code) :**
```c
typedef struct Maillon {
    double coeff;
    int exposant;
    struct Maillon *suivant;
    struct Maillon *general;  // Chaînage de tous les maillons
    int utile;                 // Marque pour les maillons utiles
} Maillon;
```

**Variables globales (déjà dans le code) :**
```c
POINTEUR tousLesMaillons;  // Tête de la liste de tous les maillons
POINTEUR polyUtile[100];    // Tableau des polynômes utiles
int nbPolyUtiles;           // Nombre de polynômes utiles
```

**Fonctions à implémenter :**

**Q7a - Marquer les utiles :**
```c
void marquerUtiles(void);
```
- Parcourir les polynômes dans `polyUtile[]`
- Marquer chaque maillon accessible (`utile = 1`)

**Q7b - Libérer les inutiles :**
```c
void libererInutiles(void);
```
- Parcourir `tousLesMaillons`
- `free()` les maillons où `utile == 0`
- Réinitialiser les marques

**Q7c - Fonction principale :**
```c
void garbageCollector(void);
```
- Appeler `marquerUtiles()` puis `libererInutiles()`

**Algorithme : Mark and Sweep**
1. **Mark :** Parcourir les polynômes utiles et marquer les maillons
2. **Sweep :** Parcourir tousLesMaillons et libérer les non-marqués

---

#### **Q8 : Versions Récursives** ⏳
**Assigné à :** IABD 2 (Bonus après Q6a, Q6b)

**Description :** Écrire des versions récursives de l'addition et de la soustraction.

**Prototype C :**
```c
POINTEUR plus_recursif(POINTEUR a, POINTEUR b);
POINTEUR moins_recursif(POINTEUR a, POINTEUR b);
```

**Approche récursive :**
```
Si liste a vide : retourner copie de b
Si liste b vide : retourner copie de a
Si a->exposant > b->exposant : 
    retourner a + fusion(b, a->suivant)
Si a->exposant < b->exposant :
    retourner b + fusion(a, b->suivant)
Sinon (même exposant) :
    coeff = a->coeff + b->coeff
    retourner maillon(coeff, exposant) + fusion(a->suivant, b->suivant)
```

---

## 📊 Récapitulatif par Développeur

### 🎯 **Lead (Toi)**
- ✅ Valider les pull requests
- ✅ Gérer les conflits de merge
- ✅ Rédiger le rapport final
- ✅ Préparer la présentation

### 💻 **IABD 1 - Structure & Analyseur**
- ✅ **Q1** : Analyseur syntaxique (grammaire)
- ✅ **Q2** : Codage en mémoire (liste chaînée)
- ✅ **Q3** : Affichage formaté
- ✅ **Q4** : Insertion par degré décroissant
- **Fichiers :** `c/src/polynome.c` (lignes Q1-Q4), `java/src/Polynome.java`

### 📡 **Telecom Réseau - Évaluation**
- ⏳ **Q5** : `eval()` - Évaluation du polynôme
- **Fichiers :** `c/src/polynome.c` (fonction eval), `java/src/Polynome.java` (méthode eval)

### 💻 **IABD 2 - Opérations de Base**
- ⏳ **Q6a** : `plus()` - Addition
- ⏳ **Q6b** : `moins()` - Soustraction
- ⏳ **Q8** : Versions récursives (bonus)
- **Fichiers :** `c/src/polynome.c` (fonctions plus, moins), `java/src/Polynome.java`

### 🔒 **SysSec 1 - Opérations Avancées**
- ⏳ **Q6c** : `fois()` - Multiplication
- ⏳ **Q6d** : `quotient()` - Division euclidienne
- **Fichiers :** `c/src/polynome.c` (fonctions fois, quotient), `java/src/Polynome.java`

### 🔒 **SysSec 2 - Gestion Mémoire**
- ⏳ **Q7a** : `marquerUtiles()` - Marquer les maillons accessibles
- ⏳ **Q7b** : `libererInutiles()` - Libérer les maillons non marqués
- ⏳ **Q7c** : `garbageCollector()` - Fonction principale
- **Fichiers :** `c/src/polynome.c` (fonctions GC), `java/src/Polynome.java` (méthode liberer)

---

## 🔄 Workflow Git pour les 5 Développeurs

### 1️⃣ Fork le repository
```bash
git clone https://github.com/[VOTRE_USERNAME]/polynomes-dic2.git
cd polynomes-dic2
```

### 2️⃣ Créer une branche spécifique
```bash
# IABD 1 (si modifications nécessaires sur Q1-Q4)
git checkout -b q1-q4-structure-iabd1

# Telecom (Q5)
git checkout -b q5-evaluation-telecom

# IABD 2 (Q6a, Q6b, Q8)
git checkout -b q6-operations-iabd2

# SysSec 1 (Q6c, Q6d)
git checkout -b q6-multiplication-division-syssec1

# SysSec 2 (Q7)
git checkout -b q7-garbage-collector-syssec2
```

### 3️⃣ Implémenter sa question
**Important :** Les Q1, Q2, Q3 sont déjà complétées, utilisez-les !

```c
// Exemple pour Q5 (Telecom):
double eval(POINTEUR p, double x) {
    double resultat = 0.0;
    while (p != NULL) {
        resultat += p->coeff * pow(x, p->exposant);
        p = p->suivant;
    }
    return resultat;
}
```

### 4️⃣ Tester individuellement
```bash
# Compiler
cd c/src
gcc -o test test_q5.c polynome.c -I../include -lm
./test
```

### 5️⃣ Commit et Push
```bash
git add .
git commit -m "Q5: Implémentation de eval() - Telecom Réseau"
git push origin q5-evaluation-telecom
```

### 6️⃣ Pull Request
Titre : `Q5: Évaluation du polynôme - [Votre Nom]`

---

## 📅 Planning Suggeré

| Semaine | IABD 1 | Telecom | IABD 2 | SysSec 1 | SysSec 2 |
|---------|--------|---------|--------|----------|----------|
| **S1** | ✅ Q1,Q2,Q3,Q4 complétées | - | - | - | - |
| **S2** | Support si besoin | ⏳ Q5 | ⏳ Q6a,Q6b | ⏳ Q6c,Q6d | ⏳ Q7 |
| **S3** | Tests intégration | PR + Debug | PR + Q8 | PR + Debug | PR + Debug |
| **S4** | 🔧 Merge final + Rapport | Tests | Tests | Tests | Tests |
| **Mi-avril** | **📅 DEADLINE** | | | | |

---

## ✅ Checklist avant Pull Request

- [ ] Ma question est implémentée
- [ ] J'utilise les fonctions Q1,Q2,Q3 déjà faites
- [ ] Compilation sans erreurs (`gcc -Wall`)
- [ ] Tests passent
- [ ] Code commenté avec en-tête de question
- [ ] Pas de fuites mémoire (sauf si Q7 pas encore fait)
- [ ] Message de commit clair : "QX: Description - [Votre Nom]"

---

## 📚 Ressources par Question

### Q1-Q4 (IABD 1)
- [Analyse syntaxique - Wikipedia](https://fr.wikipedia.org/wiki/Analyse_syntaxique)
- [Listes chaînées en C](https://www.geeksforgeeks.org/linked-list-set-1-introduction/)

### Q5 (Telecom)
- [Fonction pow() en C](https://en.cppreference.com/w/c/numeric/math/pow)
- Évaluation polynomiale : Horner's method (optionnel)

### Q6a,b (IABD 2)
- [Fusion de deux listes triées](https://www.geeksforgeeks.org/merge-two-sorted-lists/)
- Algorithmes récursifs sur les listes

### Q6c,d (SysSec 1)
- [Multiplication de polynômes](https://fr.wikipedia.org/wiki/Produit_de_polyn%C3%B4mes)
- [Division euclidienne polynomiale](https://fr.wikipedia.org/wiki/Algorithme_de_division_polinomiale)

### Q7 (SysSec 2)
- [Garbage Collection - Mark and Sweep](https://en.wikipedia.org/wiki/Tracing_garbage_collection)
- Gestion mémoire en C : malloc/free

### Q8 (IABD 2 - Bonus)
- [Récursivité sur les listes chaînées](https://www.cs.cmu.edu/~adamchik/15-121/lectures/Linked%20Lists/linkedlist_recursive.pdf)

---

## 📝 Notes Importantes

### Pour IABD 1 (Q1-Q4)
Les questions 1-4 sont déjà **complétées** dans le dépôt. Vous pouvez vous concentrer sur le support et les tests d'intégration.

### Pour Telecom (Q5)
- Utilisez les fonctions `insererMonome()` et `allouerMaillon()` déjà faites
- Testez avec plusieurs valeurs de x (positives, négatives, nulles)

### Pour IABD 2 (Q6a,b + Q8)
- Q6a et Q6b sont similaires (seul le signe change)
- Q8 (récursif) est un bonus après avoir fini Q6a,b

### Pour SysSec 1 (Q6c,d)
- Multiplication : pensez à la distributivité
- Division : algorithme similaire à la division entière scolaire

### Pour SysSec 2 (Q7)
- Le plus important : comprendre l'algorithme Mark and Sweep
- Les champs `general` et `utile` sont déjà dans la structure
- Les variables globales sont déjà déclarées

---

## 📞 Contact et Support

| Problème | Qui contacter |
|----------|---------------|
| Compilation | Lead |
| Merge conflicts | Lead |
| Questions Q1-Q4 | IABD 1 |
| Questions Q5 | Telecom |
| Questions Q6a,b | IABD 2 |
| Questions Q6c,d | SysSec 1 |
| Questions Q7 | SysSec 2 |

---

## 🎯 Objectif Final

Avoir un programme complet qui :
1. ✅ Parse une expression de polynôme (Q1)
2. ✅ Stocke en mémoire sous forme de liste chaînée ordonnée (Q2, Q4)
3. ✅ Affiche le polynôme (Q3)
4. ⏳ Évalue P(x) pour un x donné (Q5)
5. ⏳ Effectue les opérations +, -, ×, ÷ (Q6)
6. ⏳ Gère automatiquement la mémoire (Q7)
7. ⏳ Propose des versions récursives (Q8)

---

**Bonne chance à toute l'équipe !** 🚀
