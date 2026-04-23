# 📚 EXPLICATION DU CODE - Gestion des Polynômes en Java

> **Guide pédagogique** : Comprendre chaque classe et méthode du projet, étape par étape.

---

## 🎯 Vue d'ensemble

Ce projet implémente une **calculatrice de polynômes** en Java. Un polynôme est une expression mathématique comme `3X² + 2X - 1`.

**Concepts clés :**
- **Monôme** : Un terme du polynôme (ex: `3X²`, `-5X`, `7`)
- **Polynôme** : Une somme de monômes
- **Liste chaînée** : Structure pour stocker les monômes en mémoire

---

## 📁 Structure des fichiers

```
java/src/
├── Monome.java      # Classe de base : représente un seul terme
├── Polynome.java    # Classe principale : gère les opérations
└── Main.java        # Programme interactif : menu utilisateur
```

---

## 1️⃣ Classe Monome.java

### 📝 Rôle
Représente **un seul terme** d'un polynôme (ex: `3X²`).

### 🔧 Attributs (données)

```java
private double coeff;      // Le nombre devant X (ex: 3, -5)
private int exposant;      // La puissance de X (ex: 2, 1, 0)
private Monome suivant;    // Lien vers le monôme suivant (liste chaînée)
```

**Exemple :**
- `3X²` → coeff=3.0, exposant=2
- `-5X` → coeff=-5.0, exposant=1
- `7` → coeff=7.0, exposant=0 (X⁰ = 1)

### 🔨 Méthodes principales

#### **Constructeur**
```java
public Monome(double coeff, int exposant)
```
**À quoi ça sert ?** Créer un nouveau monôme.

**Exemple :**
```java
Monome m = new Monome(3.0, 2);  // Crée 3X²
```

---

#### **Getters et Setters**
```java
public double getCoeff()           // Lit le coefficient
public int getExposant()           // Lit l'exposant
public Monome getSuivant()         // Lit le monôme suivant
public void setSuivant(Monome m)   // Change le monôme suivant
```

**Analogie :** C'est comme des "fenêtres" pour voir/modifier les données privées.

---

#### **Calculer la valeur**
```java
public double evaluer(double x)
```
**À quoi ça sert ?** Calcule la valeur du monôme pour un X donné.

**Formule :** `coeff × X^exposant`

**Exemple :**
```java
Monome m = new Monome(3.0, 2);  // 3X²
double resultat = m.evaluer(2.0); // 3 × 2² = 12.0
```

---

## 2️⃣ Classe Polynome.java

### 📝 Rôle
Gère **tout le polynôme** (ensemble des monômes) et les opérations mathématiques.

### 🔧 Attributs

```java
private Monome tete;              // Premier monôme de la liste
private String expressionOrig;    // Expression textuelle originale
```

**Analogie :** `tete` est comme le "premier maillon" d'une chaîne.

---

### 🔨 Méthodes principales

#### **Constructeur (Analyseur syntaxique)**
```java
public Polynome(String expression)
```
**À quoi ça sert ?** Transforme un texte en structure de données.

**Comment ça marche ?**
1. Reçoit une chaîne comme `"3X^2 + 2X - 1"`
2. Découpe en monômes
3. Insère chaque monôme dans la liste
4. Trie par exposant décroissant

**Exemple :**
```java
Polynome p = new Polynome("3X^2 + 2X - 1");
// Crée la liste: 3X² → 2X → -1
```

---

#### **Affichage formaté**
```java
public String toString()
```
**À quoi ça sert ?** Affiche le polynôme joliment.

**Exemple :**
```java
System.out.println(p);  // Affiche: "3,00X^2 + 2,00X - 1,00"
```

**Règles d'affichage :**
- Coefficients avec 2 décimales
- `X^1` s'affiche `X`
- `X^0` (constante) n'affiche pas X
- Signe négatif avec espace: " - "

---

#### **Insérer un monôme (Question 4)**
```java
private Monome insererTrie(Monome tete, double coeff, int exposant)
```
**À quoi ça sert ?** Ajoute un monôme en gardant l'ordre décroissant.

**Algorithme :**
```
Si liste vide OU nouvel exposant > exposant tête:
    → Insérer en tête
Sinon si même exposant:
    → Additionner les coefficients
Sinon:
    → Appel récursif sur le suivant
```

**Pourquoi trier ?** Pour faciliter les opérations (+, -, ×, ÷).

---

#### **Évaluation (Question 5)**
```java
public double eval(double x)
```
**À quoi ça sert ?** Calcule P(x) pour une valeur donnée.

**Formule :** Σ (coeff × x^exposant)

**Exemple :**
```java
Polynome p = new Polynome("3X^2 + 2X - 1");
double resultat = p.eval(2.0);  // 3×4 + 2×2 - 1 = 15.0
```

**Comment ça marche ?**
1. Parcourt tous les monômes
2. Calcule chaque terme avec `Math.pow(x, exposant)`
3. Additionne tout

---

#### **Addition (Question 6a)**
```java
public Polynome plus(Polynome autre)
```
**À quoi ça sert ?** Additionne deux polynômes.

**Algorithme (fusion de listes triées) :**
```
Tant que P1 ou P2 non vide:
    Si P1.exposant > P2.exposant:
        → Copier P1 dans résultat
        → Avancer dans P1
    Sinon si P2.exposant > P1.exposant:
        → Copier P2 dans résultat
        → Avancer dans P2
    Sinon (même exposant):
        → Additionner coefficients
        → Avancer dans les deux
```

**Exemple :**
```
P1 = 3X² + 2X - 1
P2 = X² - 5X + 4
Résultat = 4X² - 3X + 3
```

---

#### **Soustraction (Question 6b)**
```java
public Polynome moins(Polynome autre)
```
**À quoi ça sert ?** Calcule P1 - P2.

**Astuce :** P1 - P2 = P1 + (-P2)

**Étapes :**
1. Crée une copie de P2 avec coefficients négatifs (`negation()`)
2. Appelle `plus()` avec P1 et -P2

**Pourquoi cette méthode ?** Réutilise le code existant (pas de duplication).

---

#### **Multiplication (Question 6c)**
```java
public Polynome fois(Polynome autre)
```
**À quoi ça sert ?** Multiplie deux polynômes.

**Algorithme (distributivité) :**
```
Pour chaque monôme M1 de P1:
    Pour chaque monôme M2 de P2:
        → Multiplier les coefficients
        → Additionner les exposants
        → Ajouter au résultat
```

**Formules :**
- Coefficient: `c1 × c2`
- Exposant: `e1 + e2`

**Exemple :**
```
(X + 1) × (X - 1) = X² - 1
```

---

#### **Division euclidienne (Question 6d)**
```java
public ResultatDivision quotient(Polynome diviseur)
```
**À quoi ça sert ?** Divise P1 par P2 (comme la division de nombres).

**Formule :** `P1 = P2 × Quotient + Reste`

**Algorithme :**
```
Tant que deg(Reste) >= deg(Diviseur):
    → Calculer terme: coeff_R / coeff_D, exp_R - exp_D
    → Ajouter terme au Quotient
    → Soustraire (Diviseur × terme) du Reste
```

**Classe interne ResultatDivision :**
```java
public static class ResultatDivision {
    public final Polynome quotient;
    public final Polynome reste;
}
```

**Exemple :**
```
(X² - 1) ÷ (X + 1) = Quotient: X - 1, Reste: 0
```

---

#### **Garbage Collector (Question 7)**
```java
public void liberer()
```
**À quoi ça sert ?** Libère la mémoire (suggère au GC Java de nettoyer).

**Comment ?**
```java
this.tete = null;          // Coupe la référence
this.expressionOrig = null; // Coupe la référence
System.gc();               // Suggère le garbage collection
```

**Note :** En Java, le GC est automatique. Cette méthode est surtout illustrative.

---

#### **Versions récursives (Question 8 - Bonus)**
```java
public Polynome plusRecursif(Polynome autre)
public Polynome moinsRecursif(Polynome autre)
```
**À quoi ça sert ?** Mêmes opérations, mais avec récursivité.

**Différence :**
- **Itératif :** Utilise des boucles (`while`)
- **Récursif :** Appelle la méthode elle-même

**Avantages récursif :**
- ✅ Code plus élégant
- ✅ Plus proche de la définition mathématique

**Inconvénients :**
- ⚠️ Plus de mémoire utilisée (pile d'appels)
- ⚠️ Risque de dépassement pour grands polynômes

---

## 3️⃣ Classe Main.java

### 📝 Rôle
Programme interactif avec **menu utilisateur**.

### 🔨 Structure

#### **Menu principal**
```java
static void afficherMenu()
```
Affiche :
```
===============================================================
           GESTION DES POLYNOMES - Mini Projet DIC2
===============================================================
  1. Analyser et afficher un polynome (Q1-Q3)
  2. Evaluer un polynome P(x) (Q4)
  3. Addition de deux polynomes (Q5a)
  ...
  0. Quitter
===============================================================
```

---

#### **Lecture sécurisée**
```java
String input = scanner.nextLine();
try {
    choix = Integer.parseInt(input);
} catch (NumberFormatException e) {
    choix = -1;  // Valeur invalide
}
```
**Pourquoi ?** Évite le plantage si l'utilisateur tape du texte.

---

#### **Switch des fonctionnalités**
```java
switch(choix) {
    case 1: menuAnalyserAfficher(); break;
    case 2: menuEvaluation(); break;
    case 3: menuAddition(); break;
    // ... etc
}
```

Chaque méthode `menuXxx()` :
1. Affiche les instructions
2. Lit les entrées utilisateur
3. Crée les polynômes
4. Effectue l'opération
5. Affiche le résultat
6. Pause (attente Entrée)

---

## 🧠 Concepts importants à retenir

### 1. **Liste chaînée**
```
┌─────────┐    ┌─────────┐    ┌─────────┐
│ 3X²     │───→│ 2X      │───→│ -1      │───→ null
│ coeff:3 │    │ coeff:2 │    │ coeff:-1│
│ exp:2   │    │ exp:1   │    │ exp:0   │
└─────────┘    └─────────┘    └─────────┘
```
Chaque maillon pointe vers le suivant.

### 2. **Tri par exposant décroissant**
Toujours garder l'ordre : X³ → X² → X → constante
→ Facilite les opérations

### 3. **Opérations = Fusion**
Addition, soustraction = fusionner deux listes triées

### 4. **Multiplication = Double boucle**
Chaque terme de P1 multiplié par chaque terme de P2

### 5. **Division = Soustractions successives**
Tant que possible, soustraire (Diviseur × Terme)

---

## 📝 Exemple complet d'utilisation

```java
// Créer deux polynômes
Polynome p1 = new Polynome("3X^2 + 2X - 1");
Polynome p2 = new Polynome("X + 1");

// Afficher
System.out.println("P1 = " + p1);  // 3,00X^2 + 2,00X - 1,00
System.out.println("P2 = " + p2);  // X + 1,00

// Évaluer
double v1 = p1.eval(2.0);  // 15.0

// Additionner
Polynome somme = p1.plus(p2);  // 3,00X^2 + 3,00X

// Multiplier
Polynome prod = p1.fois(p2);   // 3,00X^3 + 5,00X^2 + X - 1,00

// Diviser
Polynome.ResultatDivision res = p1.quotient(p2);
// Quotient: 3,00X - 1,00
// Reste: 0
```

---

## 🎯 Points clés pour l'examen

| Concept | Explication rapide |
|---------|-------------------|
| **Monome** | Terme simple: coeff × X^exp |
| **Polynome** | Liste chaînée de monômes |
| **Insertion** | Toujours triée par exp décroissant |
| **Addition** | Fusion de listes triées |
| **Évaluation** | Σ coeff × x^exp |
| **Division** | Quotient + Reste (comme nombres) |
| **GC Java** | Automatique (pas besoin de free) |

---

## 🔗 Lien avec le C

| Java | C équivalent |
|------|-------------|
| `class Monome` | `struct Maillon` |
| `new Monome(...)` | `malloc(sizeof(Maillon))` |
| `p.suivant` | `p->suivant` |
| `null` | `NULL` |
| `System.gc()` | `free()` + Mark & Sweep |

**Différence majeure :** En Java, pas besoin de gérer la mémoire manuellement !

---

*Fin de l'explication. Pour toute question, consulter le code source commenté.*
