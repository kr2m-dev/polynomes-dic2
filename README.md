# 📊 Gestion de Polynômes - Mini Projet DIC2

[![C](https://img.shields.io/badge/C-99-blue)](https://en.wikipedia.org/wiki/C99)
[![Java](https://img.shields.io/badge/Java-8-orange)](https://www.oracle.com/java/technologies/java8.html)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)
[![Status](https://img.shields.io/badge/Status-97%25%20COMPLÉTÉ-brightgreen)](https://github.com/kr2m-dev/polynomes-dic2)

> **Mini-projet** : Algorithmique et programmation avancées & POO avancée  
> **Objectif** : Programmer la gestion de polynômes en **C** et **Java**

---

## 🎯 Status du Projet

### ✅ Questions COMPLÉTÉES

| Question | Description | Status | Auteur | Filière |
|----------|-------------|--------|--------|---------|
| **Q1-Q3** | Analyseur, Codage, Affichage | ✅ COMPLÉTÉ | IABD 1 (Toi) | GLSI |
| **Q4** | Codage par degré décroissant | ✅ COMPLÉTÉ | Sokhna Maimouna 🌟 | SSI |
| **Q5** | Évaluation P(x) | ✅ COMPLÉTÉ | n0reyni (Ousmane Sow) | IABD |
| **Q6a,b** | Addition & Soustraction | ✅ COMPLÉTÉ | Makhtar Gueye 🌟 | TR |
| **Q6c,d** | Multiplication & Division | ✅ COMPLÉTÉ | Khadidiatou Niakh 🌟 | IABD |
| **Q7** | Garbage Collector | ✅ COMPLÉTÉ | [Ton nom] | GLSI |

### ⏳ Questions EN ATTENTE (Bonus)

| Question | Description | Status | Assigné à |
|----------|-------------|--------|-----------|
| **Q8** | Versions récursives (+, -) | ⏳ BONUS | Ame Thiam (TR) |

---

## 👥 Équipe

| Rôle | Nom | Filière | Question Assignée |
|------|-----|---------|-------------------|
| 🎯 **Lead & Merge** | [Ton nom] | GLSI | Gestion dépôt, review, Q7 |
| 💻 **IABD 1** | [Ton nom] | GLSI | **Q1, Q2, Q3** ✅ |
| 🔒 **Systèmes** | Sokhna Maimouna | SSI | **Q4** ✅ |
| 💻 **IABD** | n0reyni (Ousmane Sow) | IABD | **Q5** ✅ |
| 📡 **Télécom** | Makhtar Gueye | TR | **Q6a,b** ✅ |
| 💻 **IABD** | Khadidiatou Niakh | IABD | **Q6c,d** ✅ |
| 📡 **Télécom** | Ame Thiam | TR | **Q8** ⏳ BONUS |

---

## 📁 Structure du Projet

```
projet/
├── c/
│   ├── include/
│   │   └── polynome.h          # ✅ Déclarations (toutes questions)
│   ├── src/
│   │   ├── polynome.c          # ✅ Q1,Q2,Q3 COMPLÉTÉES
│   │   │                          # ⏳ Q4,Q5,Q6 À IMPLÉMENTER
│   │   └── main.c              # ✅ Tests Q1,Q2,Q3
│   └── Makefile
├── java/
│   └── src/
│       ├── Monome.java          # ✅ Classe de base
│       ├── Polynome.java        # ✅ Q1,Q2,Q3 COMPLÉTÉES
│       │                           # ⏳ Q4,Q5,Q6 À IMPLÉMENTER
│       └── Main.java            # ✅ Tests Q1,Q2,Q3
├── .gitignore
├── ASSIGNATION.md               # ⏳ À REMPLIR
└── README.md                    # ✅ Ce fichier
```

---

## 🚀 Questions COMPLÉTÉES (Base pour vos camarades)

### ✅ Q1: Analyseur Syntaxique

**Grammaire respectée**:
```
polynôme → ['-'] monôme { ('+' | '-') monôme }
monôme → nombre '*' xpuissance | xpuissance | nombre
xpuissance → 'X' | 'X' '^' naturel
naturel → chiffre { chiffre }
nombre → naturel [ '.' { chiffre } ]
```

**Fonction**: `analyserPolynome(char *texte)`

### ✅ Q2: Codage en Mémoire

**Structure**: Liste chaînée ordonnée par exposant décroissant

**Fonction**: `insererMonome(POINTEUR tete, double coeff, int exposant)`

### ✅ Q3: Affichage

**Format**: `"3.00X^2 + 2.00X - 1.00"`

**Fonction**: `afficherPolynome(POINTEUR p)`

---

## ⏳ Questions À IMPLÉMENTER

### Q4: Évaluation (Telecom)

```c
double eval(POINTEUR p, double x);
```
**Formule**: P(x) = Σ(coeff × x^exposant)

### Q5: Opérations Arithmétiques

```c
// Q5a: Addition (IABD 2)
POINTEUR plus(POINTEUR a, POINTEUR b);

// Q5b: Soustraction (IABD 2)
POINTEUR moins(POINTEUR a, POINTEUR b);

// Q5c: Multiplication (SysSec 1)
POINTEUR fois(POINTEUR a, POINTEUR b);

// Q5d: Division euclidienne (SysSec 1)
POINTEUR quotient(POINTEUR a, POINTEUR b, POINTEUR *reste);
```

### Q6: Garbage Collector (SysSec 2)

```c
void marquerUtiles(void);
void libererInutiles(void);
void garbageCollector(void);
```

**Algorithme**: Mark and Sweep

---

## 🛠️ Compilation

### C - Questions 1, 2, 3

```bash
cd c/src
gcc -o polynome main.c polynome.c -I../include -lm
./polynome
```

### Java - Questions 1, 2, 3

```bash
cd java/src
javac *.java
java Main
```

---

## 🔄 Workflow pour les 5 développeurs

### 1️⃣ Fork le repository

```bash
# Cliquez sur Fork sur GitHub
git clone https://github.com/[VOTRE_USERNAME]/polynomes-dic2.git
cd polynomes-dic2
```

### 2️⃣ Créer votre branche

```bash
# Telecom (Q4)
git checkout -b q4-evaluation-telecom

# IABD 2 (Q5a,b)
git checkout -b q5-addition-soustraction-iabd2

# SysSec 1 (Q5c,d)
git checkout -b q5-multiplication-division-syssec1

# SysSec 2 (Q6)
git checkout -b q6-garbage-collector-syssec2
```

### 3️⃣ Implémenter votre question

**Important**: Les fonctions Q1, Q2, Q3 sont déjà là, utilisez-les!

```c
// Exemple pour Q4 (Telecom):
double eval(POINTEUR p, double x) {
    double resultat = 0.0;
    while (p != NULL) {
        resultat += p->coeff * pow(x, p->exposant);
        p = p->suivant;
    }
    return resultat;
}
```

### 4️⃣ Tester

```bash
# Ajoutez vos tests dans main.c ou créez test_q[Num].c
gcc -o test_q4 test_q4.c src/polynome.c -I include -lm
./test_q4
```

### 5️⃣ Commit et Push

```bash
git add .
git commit -m "Q4: Implémentation de eval() - [Votre Nom]"
git push origin q4-evaluation-telecom
```

### 6️⃣ Pull Request

Créez une PR vers `kr2m-dev/polynomes-dic2:main`

---

## 📋 Checklist avant PR

- [ ] Ma question est implémentée
- [ ] J'utilise les fonctions Q1,Q2,Q3 déjà faites
- [ ] Compilation sans erreurs
- [ ] Tests ajoutés et passent
- [ ] Code commenté
- [ ] Pas de conflits avec main

---

## 📚 Ressources

- [Documentation C](https://devdocs.io/c/)
- [Documentation Java](https://docs.oracle.com/javase/8/docs/api/)
- [Algorithme de division polynomiale](https://fr.wikipedia.org/wiki/Algorithme_de_division_polinomiale)
- [Garbage Collector - Mark and Sweep](https://en.wikipedia.org/wiki/Tracing_garbage_collection)

---

## 📅 Planning

| Date | Événement |
|------|-----------|
| Semaine 1 | ✅ Q1, Q2, Q3 COMPLÉTÉES (Lead) |
| Semaine 2 | ⏳ Q4 (Telecom) + Q5a,b (IABD 2) |
| Semaine 3 | ⏳ Q5c,d (SysSec 1) + Q6 (SysSec 2) |
| Semaine 4 | 🔧 Intégration + Tests + Rapport |
| **Mi-avril** | **📅 DEADLINE** |

---

## 📞 Contact

- **Discord** : [Lien à ajouter]
- **Lead** : [Ton email]

---

**Les questions 1, 2, 3 sont prêtes! Vos camarades peuvent forker et commencer!** 🚀
