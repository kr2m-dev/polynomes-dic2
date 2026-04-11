# 🧪 GUIDE DE TESTS DU PROJET POLYNÔMES

## 📋 Instructions pour compiler et tester sur Ubuntu

### 1️⃣ Se connecter au serveur Ubuntu

```bash
ssh srv-oracle
# ou
ssh ubuntu@141.253.111.148
```

### 2️⃣ Cloner le dépôt

```bash
cd /tmp
git clone https://github.com/kr2m-dev/polynomes-dic2.git
cd polynomes-dic2
```

### 3️⃣ Compiler les tests C

```bash
cd c

# Compilation du fichier principal
gcc -o polynome src/polynome.c -I include -lm -Wall

# Compilation des tests individuels
gcc -o tests/test_q1 tests/test_q1_analyseur.c src/polynome.c -I include -lm -Wall
gcc -o tests/test_q5 tests/test_q5_evaluation.c src/polynome.c -I include -lm -Wall
gcc -o tests/test_q6 tests/test_q6_operations.c src/polynome.c -I include -lm -Wall
gcc -o tests/test_q7 tests/test_q7_gc.c src/polynome.c -I include -lm -Wall
```

### 4️⃣ Exécuter les tests

```bash
# Test Q1: Analyseur syntaxique
./tests/test_q1

# Test Q5: Évaluation
./tests/test_q5

# Test Q6: Opérations arithmétiques
./tests/test_q6

# Test Q7: Garbage Collector
./tests/test_q7
```

### 5️⃣ Compiler et tester Java

```bash
cd java/src
javac *.java
java Main
```

---

## 📊 Résultats attendus

### ✅ Tests Q1 - Analyseur
```
Test 1: Polynôme complet
  Expression: "3X^2 + 2X - 1"
  Résultat:   "3.00X^2 + 2.00X - 1.00"
  ✓ Test réussi

RÉSULTATS: 8/8 tests réussis
```

### ✅ Tests Q5 - Évaluation
```
Test 1: P(2) = 3*4 + 2*2 - 1 = 15
  Expression: "3X^2 + 2X - 1", x = 2.00
  Résultat:   15.0000
  Attendu:    15.0000
  ✓ Test réussi

RÉSULTATS: 10/10 tests réussis
```

### ✅ Tests Q6 - Opérations
```
--- Addition (Q6a) ---
Test 1: Addition simple
  (3X^2 + 2X) + (X + 1)
  Résultat = "3.00X^2 + 3.00X + 1.00"
  ✓ Test validé

--- Multiplication (Q6c) ---
Test 1: (X+1)(X-1) = X^2 - 1
  ✓ Multiplication effectuée

--- Division (Q6d) ---
Test 1: Division exacte
  (X^2 - 1) / (X + 1)
  Quotient: "1.00X - 1.00"
  Reste: "0"
  ✓ Division effectuée

RÉSULTATS: 12/12 tests réussis
```

### ✅ Tests Q7 - GC
```
========================================
  TEST Q7: GARBAGE COLLECTOR
========================================

Création de polynômes...
P1: 3.00X^2 + 2.00X - 1.00
P2: 1.00X^3 + 5.00X^2 + 4.00
P3: 2.00X + 1.00

Marquage des polynômes utiles...
P1 et P2 marqués comme utiles.
P3 n'est PAS marqué (sera collecté).

Opérations créant des polynômes temporaires...
P1 + P2: 1.00X^3 + 8.00X^2 + 6.00X + 3.00

Exécution du Garbage Collector...
GC terminé.
- P1 et P2 conservés (marqués utiles)
- P3 libéré (non marqué)
- Polynômes temporaires libérés (non marqués)

Vérification: P1 et P2 toujours accessibles
P1: 3.00X^2 + 2.00X - 1.00
P2: 1.00X^3 + 5.00X^2 + 4.00

========================================
  Q7: GARBAGE COLLECTOR ✓ COMPLÉTÉ
========================================
```

---

## 🎯 Tests automatisés complets

### Script de test automatique (`run_all_tests.sh`):

```bash
#!/bin/bash

echo "=========================================="
echo "  TESTS AUTOMATISÉS - POLYNÔMES DIC2"
echo "=========================================="
echo ""

cd /tmp/polynomes-dic2/c

# Compilation
echo "🔨 Compilation..."
gcc -o tests/test_q1 tests/test_q1_analyseur.c src/polynome.c -I include -lm -Wall 2>&1 | grep -E "(error|warning)" || echo "✓ Compilation Q1 OK"
gcc -o tests/test_q5 tests/test_q5_evaluation.c src/polynome.c -I include -lm -Wall 2>&1 | grep -E "(error|warning)" || echo "✓ Compilation Q5 OK"
gcc -o tests/test_q6 tests/test_q6_operations.c src/polynome.c -I include -lm -Wall 2>&1 | grep -E "(error|warning)" || echo "✓ Compilation Q6 OK"
gcc -o tests/test_q7 tests/test_q7_gc.c src/polynome.c -I include -lm -Wall 2>&1 | grep -E "(error|warning)" || echo "✓ Compilation Q7 OK"

echo ""
echo "🧪 Exécution des tests..."
echo ""

# Exécution
./tests/test_q1 && echo "✅ Q1: Analyseur - PASS" || echo "❌ Q1: Analyseur - FAIL"
./tests/test_q5 && echo "✅ Q5: Évaluation - PASS" || echo "❌ Q5: Évaluation - FAIL"
./tests/test_q6 && echo "✅ Q6: Opérations - PASS" || echo "❌ Q6: Opérations - FAIL"
./tests/test_q7 && echo "✅ Q7: GC - PASS" || echo "❌ Q7: GC - FAIL"

echo ""
echo "=========================================="
echo "  TESTS COMPLÉTÉS"
echo "=========================================="
```

Pour exécuter:
```bash
chmod +x run_all_tests.sh
./run_all_tests.sh
```

---

## 📸 Captures d'écran attendues

### 1. Compilation réussie
![Compilation](capture_compilation.png)

### 2. Tests Q1-Q7 réussis
![Tests](capture_tests.png)

### 3. Exécution Java
![Java](capture_java.png)

---

## 🔧 Dépannage

### Erreur: "undefined reference to `pow`"
**Solution:** Ajouter `-lm` à la compilation

### Erreur: "implicit declaration of function `negation`"
**Solution:** La fonction `negation()` doit être définie AVANT `moins()`

### Erreur: "cannot find -lm"
**Solution:** Installer les packages de développement:
```bash
sudo apt-get install build-essential
```

---

## 📁 Structure des tests

```
c/tests/
├── test_q1_analyseur.c      # Test Q1: Analyseur syntaxique
├── test_q5_evaluation.c     # Test Q5: Évaluation
├── test_q6_operations.c       # Test Q6: Opérations arithmétiques
├── test_q7_gc.c             # Test Q7: Garbage Collector
└── run_all_tests.sh         # Script de test automatique
```

---

## ✅ Checklist de validation

- [ ] Compilation C sans erreurs
- [ ] Compilation Java sans erreurs
- [ ] Test Q1: 8/8 réussis
- [ ] Test Q5: 10/10 réussis
- [ ] Test Q6: 12/12 réussis
- [ ] Test Q7: GC fonctionnel
- [ ] Java: Exécution sans erreurs
- [ ] Tous les artefacts générés

---

**Projet prêt pour soumission !** 🎉
