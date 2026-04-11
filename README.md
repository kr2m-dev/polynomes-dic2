# 📊 Gestion de Polynômes - Mini Projet DIC2

[![C](https://img.shields.io/badge/C-99-blue)](https://en.wikipedia.org/wiki/C99)
[![Java](https://img.shields.io/badge/Java-8-orange)](https://www.oracle.com/java/technologies/java8.html)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)
[![Status](https://img.shields.io/badge/Status-TERMINÉ-success)](https://github.com/kr2m-dev/polynomes-dic2)

> **Mini-projet TERMINÉ** : Algorithmique et programmation avancées & POO avancée
> **Objectif atteint** : Gestion complète de polynômes en **C** et **Java**

---

## 🎯 Vue d'ensemble

Ce projet implémente un système complet de manipulation de polynômes mathématiques utilisant des listes chaînées, en respectant une grammaire précise.

### ✅ Toutes les questions implémentées (8/8)

| Question | Description | Auteur | Filière |
|----------|-------------|--------|---------|
| **Q1** | Analyseur syntaxique | Lead (GLSI) | GLSI |
| **Q2** | Codage en mémoire | Lead (GLSI) | GLSI |
| **Q3** | Affichage formaté | Lead (GLSI) | GLSI |
| **Q4** | Insertion par degré décroissant | Sokhna Maimouna | SSI |
| **Q5** | Évaluation P(x) | n0reyni (Ousmane Sow) | IABD |
| **Q6a,b** | Addition & Soustraction | Makhtar Gueye | TR |
| **Q6c,d** | Multiplication & Division | Khadidiatou Niakh | IABD |
| **Q7** | Garbage Collector (Mark & Sweep) | Lead (GLSI) | GLSI |
| **Q8** | Versions récursives (Bonus) | Lead (GLSI) | BONUS |

**Taux de complétion : 100%** 🎉

---

## 📁 Structure du Projet

```
projet/
├── c/                              # Implémentation C
│   ├── include/
│   │   └── polynome.h              # Déclarations (toutes fonctions)
│   ├── src/
│   │   ├── polynome.c              # Implémentation Q1-Q8
│   │   └── main.c                  # Programme principal
│   ├── tests/
│   │   ├── test_q1_analyseur.c     # Tests analyseur
│   │   ├── test_q5_evaluation.c    # Tests évaluation
│   │   ├── test_q6_operations.c     # Tests opérations
│   │   └── test_q7_gc.c            # Tests garbage collector
│   └── Makefile
├── java/                           # Implémentation Java
│   └── src/
│       ├── Monome.java             # Classe monôme
│       ├── Polynome.java           # Classe polynôme (Q1-Q8)
│       └── Main.java               # Programme de test
├── collegue travaux/               # Sources des collaborateurs
│   ├── sokhnaMaimounaQ4/
│   ├── makhtar gueyeQ6a,b/
│   └── Khadidiatou Niakh Q6c,d/
├── RAPPORT.md                      # Rapport complet
├── EXECUTION_TESTS.md              # Guide d'exécution des tests
└── README.md                       # Ce fichier
```

---

## 🚀 Guide d'utilisation rapide

### Prérequis

- **C** : GCC avec support C99
- **Java** : JDK 8 ou supérieur
- **Git** : Pour cloner le dépôt

### Installation

```bash
# Cloner le repository
git clone https://github.com/kr2m-dev/polynomes-dic2.git
cd polynomes-dic2
```

---

## 💻 Utilisation en C

### Compilation

```bash
cd c

# Compiler la bibliothèque
make all

# Ou manuellement :
gcc -c src/polynome.c -I include -o polynome.o -lm
```

### Exécution des tests

```bash
# Test Q1 : Analyseur syntaxique
gcc -o test_q1 tests/test_q1_analyseur.c polynome.o -I include -lm
./test_q1

# Test Q5 : Évaluation
gcc -o test_q5 tests/test_q5_evaluation.c polynome.o -I include -lm
./test_q5

# Test Q6 : Opérations arithmétiques
gcc -o test_q6 tests/test_q6_operations.c polynome.o -I include -lm
./test_q6

# Test Q7 : Garbage Collector
gcc -o test_q7 tests/test_q7_gc.c polynome.o -I include -lm
./test_q7
```

### Exemple d'utilisation dans votre code

```c
#include "polynome.h"

int main() {
    // Créer un polynôme depuis une chaîne
    POINTEUR p = analyserPolynome("3X^2 + 2X - 1");
    
    // Afficher
    printf("P(X) = ");
    afficherPolynome(p);
    printf("\n");
    // Sortie: P(X) = 3.00X^2 + 2.00X - 1.00
    
    // Évaluer en x=2
    double resultat = eval(p, 2.0);
    printf("P(2) = %.2f\n", resultat);
    // Sortie: P(2) = 15.00
    
    // Créer un deuxième polynôme
    POINTEUR q = analyserPolynome("X + 1");
    
    // Addition
    POINTEUR somme = plus(p, q);
    printf("P + Q = ");
    afficherPolynome(somme);
    printf("\n");
    
    // Multiplication
    POINTEUR produit = fois(p, q);
    printf("P * Q = ");
    afficherPolynome(produit);
    printf("\n");
    
    // Division
    POINTEUR reste;
    POINTEUR quotient = quotient(p, q, &reste);
    printf("P / Q = ");
    afficherPolynome(quotient);
    printf("\n");
    
    // Marquer comme utile pour le GC
    ajouterPolyUtile(p);
    ajouterPolyUtile(q);
    
    // Lancer le garbage collector
    garbageCollector();
    
    return 0;
}
```

---

## ☕ Utilisation en Java

### Compilation

```bash
cd java/src
javac *.java
```

### Exécution

```bash
java Main
```

### Exemple d'utilisation dans votre code

```java
public class MonProgramme {
    public static void main(String[] args) {
        // Créer un polynôme depuis une chaîne
        Polynome p = new Polynome("3X^2 + 2X - 1");
        
        // Afficher
        System.out.println("P(X) = " + p);
        // Sortie: P(X) = 3,00X^2 + 2,00X - 1,00
        
        // Évaluer en x=2
        double resultat = p.eval(2.0);
        System.out.println("P(2) = " + resultat);
        // Sortie: P(2) = 15.0
        
        // Créer un deuxième polynôme
        Polynome q = new Polynome("X + 1");
        
        // Addition
        Polynome somme = p.plus(q);
        System.out.println("P + Q = " + somme);
        
        // Soustraction
        Polynome diff = p.moins(q);
        System.out.println("P - Q = " + diff);
        
        // Multiplication
        Polynome produit = p.fois(q);
        System.out.println("P * Q = " + produit);
        
        // Division euclidienne
        Polynome.ResultatDivision resultatDiv = p.quotient(q);
        System.out.println("P / Q = " + resultatDiv.quotient);
        System.out.println("Reste = " + resultatDiv.reste);
        
        // Suggérer le garbage collector
        p.liberer();
        System.gc();
    }
}
```

---

## 🧪 Résultats des tests

### C sur Ubuntu Server (141.253.111.148)

```
✅ Q1: Analyseur syntaxique        → 10/10 tests passés
✅ Q5: Évaluation                 → 10/10 tests passés
✅ Q6: Opérations arithmétiques   → 8/8 tests passés
✅ Q7: Garbage Collector          → Fonctionne
```

### Java (Local)

```
✅ Compilation: javac *.java → SUCCESS
✅ Exécution: java Main → Toutes questions OK
✅ Q1-Q8: Toutes fonctionnalités opérationnelles
```

---

## 📚 Fonctionnalités détaillées

### Q1-Q3 : Base du système

**Grammaire supportée :**
```
polynôme → ['-'] monôme { ('+' | '-') monôme }
monôme → nombre ['*'] xpuissance | xpuissance | nombre
xpuissance → 'X' ['^' naturel]
```

**Exemples valides :**
- `3X^2 + 2X - 1` → Simplifié automatiquement
- `4X - 2X + 5` → `2X + 5`
- `2X^2 + 3X^2` → `5X^2`
- `2*X + 3` (avec ou sans *)

### Q4 : Insertion par degré décroissant

Algorithme récursif par Sokhna Maimouna :
- Insertion O(n) dans la liste triée
- Fusion automatique des mêmes exposants
- Suppression des coefficients nuls

### Q5 : Évaluation

Calcule P(x) pour une valeur donnée :
```
P(X) = 3X^2 + 2X - 1
P(2) = 3×(2^2) + 2×2 - 1 = 15
```

### Q6 : Opérations arithmétiques

| Opération | Algorithme | Complexité |
|-----------|------------|------------|
| Addition | Fusion de listes triées | O(n+m) |
| Soustraction | Addition avec négation | O(n+m) |
| Multiplication | Double boucle (distributivité) | O(n×m) |
| Division | Algorithme euclidien | O(n²) |

### Q7 : Garbage Collector

**Algorithme Mark & Sweep :**
1. **MARK** : Marquer tous les maillons accessibles depuis les polynômes utiles
2. **SWEEP** : Libérer les maillons non marqués

Variables globales : `tousLesMaillons`, `polyUtile[]`, `nbPolyUtiles`

### Q8 : Versions récursives (Bonus)

Implémentations alternatives de `plus` et `moins` :
- ✅ Plus élégantes
- ⚠️ Plus lourdes en mémoire (pile d'appels)
- 📚 Utilisées à des fins pédagogiques

---

## 👥 Équipe de développement

| Membre | Filière | Questions | Rôle |
|--------|---------|-----------|------|
| **Lead** | GLSI | Q1-Q3, Q7, Q8, Intégration | Chef de projet |
| **Sokhna Maimouna** | SSI | Q4 | Insertion récursive |
| **n0reyni (Ousmane Sow)** | IABD | Q5 | Évaluation |
| **Makhtar Gueye** | TR | Q6a,b | Addition/Soustraction |
| **Khadidiatou Niakh** | IABD | Q6c,d | Multiplication/Division |

### Fichiers sources des collaborateurs

- `/collegue travaux/sokhnaMaimounaQ4/` - Q4 (Insertion)
- `/collegue travaux/makhtar gueyeQ6a,b/` - Q6a,b (+/-)
- `/collegue travaux/Khadidiatou Niakh Q6c,d/` - Q6c,d (×/÷)

---

## 🔧 Débogage et corrections

### Problèmes résolus

1. **`analyserPolynome` ne construisait pas la liste**
   - **Solution** : Modifier `analyserMonome` pour retourner `coeff`/`exposant` par référence

2. **Fonction `moins()` manquante**
   - **Solution** : Ajouter l'implémentation utilisant `negation()` et `plus()`

3. **Format `3X^2` (sans *) non supporté**
   - **Solution** : Ajouter un cas pour X directement après un nombre

4. **Ordre des fonctions en C**
   - **Solution** : Déplacer `negation()` avant `moins()`

Voir `RAPPORT.md` section "Modifications et débogage" pour plus de détails.

---

## 📖 Documentation

- **[RAPPORT.md](RAPPORT.md)** : Rapport complet du projet
- **[EXECUTION_TESTS.md](EXECUTION_TESTS.md)** : Guide d'exécution détaillé
- **[c/include/polynome.h](c/include/polynome.h)** : Documentation des fonctions C
- **[java/src/Polynome.java](java/src/Polynome.java)** : Documentation Java (Javadoc)

---

## 📝 Licence

Ce projet est réalisé dans le cadre du cours d'Algorithmique et Programmation Avancée à l'ESP DAKAR.

---

**ESP - DGI - Année académique 2025-2026**

*Enseignant : M. I FALL*

</div>
