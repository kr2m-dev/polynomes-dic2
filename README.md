# 📊 Gestion de Polynômes - Mini Projet DIC2

[![C](https://img.shields.io/badge/C-99-blue)](https://en.wikipedia.org/wiki/C99)
[![Java](https://img.shields.io/badge/Java-8-orange)](https://www.oracle.com/java/technologies/java8.html)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)

> **Mini-projet** : Algorithmique et programmation avancées & POO avancée  
> **Objectif** : Programmer la gestion de polynômes en **C** et **Java**

---

## 👥 Équipe

| Rôle | Nom | Filière | Question Assignée |
|------|-----|---------|-------------------|
| 🎯 **Lead & Merge** | [Toi] | [Ta filière] | Gestion dépôt, review, rapport |
| 💻 **Dev 1** | [Nom 1] | IABD | Q4 - Analyseur & Structure |
| 💻 **Dev 2** | [Nom 2] | IABD | Q6c/Q6d - Multiplication & Division |
| 📡 **Dev 3** | [Nom 3] | Telecom Réseau | Q5 - Évaluation + Tests |
| 🔒 **Dev 4** | [Nom 4] | Système Sécurité | Q6a/Q6b - Addition & Soustraction |
| 🔒 **Dev 5** | [Nom 5] | Système Sécurité | Q7 - Garbage Collector |

📋 **Détails complets** : Voir [`ASSIGNATION.md`](ASSIGNATION.md)

---

## 📁 Structure du Projet

```
projet/
├── c/
│   ├── include/
│   │   └── polynome.h          # Déclarations des fonctions
│   ├── src/
│   │   └── polynome.c          # Implémentation (à compléter)
│   └── tests/                  # Tests par question
│       ├── test_q4.c
│       ├── test_q5.c
│       └── ...
├── java/
│   └── src/
│       ├── Monome.java          # Classe de base
│       ├── Polynome.java        # Classe principale (à compléter)
│       └── Main.java            # Tests (à compléter)
├── .gitignore
├── ASSIGNATION.md               # Répartition des tâches
└── README.md                    # Ce fichier
```

---

## 🚀 Questions à Implémenter

| Question | Fonction C | Méthode Java | Description | Assigné à |
|----------|------------|--------------|-------------|-----------|
| **Q4** | `analyserPolynome()` | `Polynome(String)` | Parser une chaîne en polynôme | IABD 1 |
| **Q4** | `insererMonome()` | `insererMonome()` | Insertion ordonnée | IABD 1 |
| **Q4** | `afficherPolynome()` | `toString()` | Affichage formaté | IABD 1 |
| **Q5** | `eval()` | `eval()` | Évaluation P(x) | Telecom |
| **Q6a** | `plus()` | `plus()` | Addition | SysSec 1 |
| **Q6b** | `moins()` | `moins()` | Soustraction | SysSec 1 |
| **Q6c** | `fois()` | `fois()` | Multiplication | IABD 2 |
| **Q6d** | `quotient()` | `quotient()` | Division euclidienne | IABD 2 |
| **Q7** | `garbageCollector()` | `liberer()` | Gestion mémoire | SysSec 2 |

---

## 🔄 Workflow Git

### 1️⃣ Fork le repository

Cliquez sur le bouton **Fork** en haut à droite du repo.

### 2️⃣ Cloner VOTRE fork

```bash
git clone https://github.com/[VOTRE_USERNAME]/polynomes-dic2.git
cd polynomes-dic2
```

### 3️⃣ Créer une branche pour votre question

```bash
git checkout -b q[NUM]-[votre-nom]
# Exemple: git checkout -b q4-ahmed
```

### 4️⃣ Implémenter votre question

Modifiez les fichiers assignés dans [`ASSIGNATION.md`](ASSIGNATION.md)

### 5️⃣ Commit et Push

```bash
git add .
git commit -m "Q[NUM]: Implémentation de [fonction] - [Nom]"
git push origin q[NUM]-[votre-nom]
```

### 6️⃣ Créer une Pull Request

1. Allez sur GitHub
2. Cliquez sur **Compare & pull request**
3. Titre : `Q[NUM]: [Description] - [Nom]`
4. Décrivez ce que vous avez fait
5. Assignez le Lead comme reviewer

---

## 🛠️ Compilation

### C

```bash
# Compiler
cd c
make

# Ou manuellement
gcc -o polynome src/polynome.c tests/test_main.c -I include -lm

# Exécuter
./polynome
```

### Java

```bash
# Compiler
cd java/src
javac *.java

# Exécuter
java Main
```

---

## 📝 Exemple d'Utilisation

### C

```c
#include "polynome.h"

int main() {
    // Q4: Créer un polynôme
    POINTEUR p1 = analyserPolynome("3X^2 + 2X - 1");
    afficherPolynome(p1);  // "3.00X^2 + 2.00X - 1.00"
    
    // Q5: Évaluer
    double val = eval(p1, 2.0);  // 15.0
    
    // Q6: Opérations
    POINTEUR p2 = analyserPolynome("X + 1");
    POINTEUR somme = plus(p1, p2);
    
    // Q7: Cleanup
    ajouterPolyUtile(p1);
    garbageCollector();
    
    return 0;
}
```

### Java

```java
public class Main {
    public static void main(String[] args) {
        // Q4: Créer un polynôme
        Polynome p1 = new Polynome("3X^2 + 2X - 1");
        System.out.println(p1);  // "3.00X^2 + 2.00X - 1.00"
        
        // Q5: Évaluer
        double val = p1.eval(2.0);  // 15.0
        
        // Q6: Opérations
        Polynome p2 = new Polynome("X + 1");
        Polynome somme = p1.plus(p2);
        
        // Q7: Cleanup
        p1.liberer();
        System.gc();
    }
}
```

---

## ✅ Checklist avant PR

- [ ] Code compilé sans erreurs
- [ ] Tests passent
- [ ] Code commenté
- [ ] Pas de fichiers inutiles (`.exe`, `.class`, etc.)
- [ ] Message de commit clair
- [ ] README mis à jour si nécessaire

---

## 📚 Ressources

- [Documentation C](https://devdocs.io/c/)
- [Documentation Java](https://docs.oracle.com/javase/8/docs/api/)
- [Guide Git](https://rogerdudler.github.io/git-guide/)
- [Algorithmes sur les polynômes](https://fr.wikipedia.org/wiki/Algorithme_de_division_polinomiale)

---

## 📅 Planning

| Date | Événement |
|------|-----------|
| Semaine 1 | Setup + Q4 (Structure) |
| Semaine 2 | Q5 + Q6a/b (Opérations simples) |
| Semaine 3 | Q6c/d (Opérations complexes) |
| Semaine 4 | Q7 (GC) + Intégration |
| **Mi-avril** | **Deadline** |

---

## 📞 Contact

- **Discord/Slack** : [Lien à ajouter]
- **Email groupe** : [Email à ajouter]
- **Issue GitHub** : Pour les bugs techniques

---

## 📄 Licence

Ce projet est réalisé dans le cadre du **Mini Projet DIC2**.

---

**⭐ Bon courage à toute l'équipe !**
