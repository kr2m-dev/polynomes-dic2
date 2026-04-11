# 🧪 GUIDE D'EXÉCUTION DES TESTS

## 📍 Où se trouvent les fichiers sur le serveur Ubuntu ?

**Chemin absolu** : `/tmp/polynomes-dic2/`

```bash
/tmp/polynomes-dic2/
├── c/
│   ├── include/
│   │   └── polynome.h
│   ├── src/
│   │   ├── polynome.c
│   │   └── main.c
│   └── tests/
│       ├── test_q1_analyseur.c
│       ├── test_q5_evaluation.c
│       ├── test_q6_operations.c
│       └── test_q7_gc.c
├── java/
│   └── src/
│       ├── Monome.java
│       ├── Polynome.java
│       └── Main.java
└── run_tests.sh
```

---

## 🚀 COMMANDES POUR EXÉCUTER LES TESTS

### 1️⃣ Se connecter au serveur Ubuntu

```bash
ssh srv-oracle
# ou
ssh -i ~/.ssh/srv-oracle ubuntu@141.253.111.148
```

### 2️⃣ Se rendre dans le répertoire du projet

```bash
cd /tmp/polynomes-dic2/c
```

### 3️⃣ Compilation du code principal

```bash
# Compiler polynome.c en objet
gcc -c src/polynome.c -I include -lm -Wall -o polynome.o
```

### 4️⃣ Compilation et exécution des tests individuels

#### Test Q1 : Analyseur Syntaxique
```bash
gcc -o test_q1 tests/test_q1_analyseur.c polynome.o -I include -lm
./test_q1
```

#### Test Q5 : Évaluation
```bash
gcc -o test_q5 tests/test_q5_evaluation.c polynome.o -I include -lm
./test_q5
```

#### Test Q6 : Opérations Arithmétiques
```bash
gcc -o test_q6 tests/test_q6_operations.c polynome.o -I include -lm
./test_q6
```

#### Test Q7 : Garbage Collector
```bash
gcc -o test_q7 tests/test_q7_gc.c polynome.o -I include -lm
./test_q7
```

### 5️⃣ Script de test automatique (tout en un)

```bash
cd /tmp/polynomes-dic2
bash run_tests.sh
```

---

## ☕ Tests Java

```bash
cd /tmp/polynomes-dic2/java/src
javac *.java
java Main
```

---

## 📊 Résultats Attendus

### ✅ Test Q1 (Analyseur)
```
Test 1: Polynôme complet
  Expression: "3X^2 + 2X - 1"
  Résultat:   "3.00X^2 + 2.00X - 1.00"
  ✓ Test réussi

RÉSULTATS: 8/8 tests réussis
```

### ✅ Test Q5 (Évaluation)
```
Test 1: P(2) = 3*4 + 2*2 - 1 = 15
  Expression: "3X^2 + 2X - 1", x = 2.00
  Résultat:   15.0000
  Attendu:    15.0000
  ✓ Test réussi

RÉSULTATS: 10/10 tests réussis
```

### ✅ Test Q6 (Opérations)
```
--- Addition (Q6a) ---
Test 1: Addition simple
  (3X^2 + 2X) + (X + 1)
  ✓ Test validé

--- Multiplication (Q6c) ---
Test 1: (X+1)(X-1) = X^2 - 1
  ✓ Multiplication effectuée

--- Division (Q6d) ---
Test 1: Division exacte
  ✓ Division effectuée

RÉSULTATS: 12/12 tests réussis
```

### ✅ Test Q7 (GC)
```
========================================
  Q7: GARBAGE COLLECTOR ✓ COMPLÉTÉ
========================================
```

---

## 🔧 Dépannage

### Erreur: "undefined reference to `negation`"
**Cause**: Fonction `negation()` définie après `moins()`

**Solution**: Le fichier a été corrigé sur GitHub. Faire :
```bash
cd /tmp/polynomes-dic2
git pull origin main
```

### Erreur: "cannot find -lm"
```bash
sudo apt-get update
sudo apt-get install build-essential
```

### Nettoyer et recommencer
```bash
cd /tmp/polynomes-dic2/c
rm -f *.o test_q*
gcc -c src/polynome.c -I include -lm -o polynome.o
```

---

## 📸 Captures d'écran pour le rapport

Pour créer des captures :

```bash
# Exécuter un test avec script
script -q /tmp/test_q1.txt
./test_q1
exit

# Le fichier /tmp/test_q1.txt contient la sortie
```

---

## ✅ Checklist Validation

- [ ] Compilation C sans erreurs (`gcc -c src/polynome.c -I include -lm`)
- [ ] Test Q1: 8/8 réussis
- [ ] Test Q5: 10/10 réussis  
- [ ] Test Q6: 12/12 réussis
- [ ] Test Q7: GC fonctionnel
- [ ] Java: `javac *.java` réussi
- [ ] Java: `java Main` exécuté

---

**Projet prêt pour soumission !** 🎉
