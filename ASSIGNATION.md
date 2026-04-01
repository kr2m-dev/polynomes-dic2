# Assignation des Tâches - Gestion de Polynômes

## 👥 Composition du Groupe

| Rôle | Nom | Filière | Contact |
|------|-----|---------|---------|
| **Lead & Merge** | [TOI] | [Ta filière] | [Email/Discord] |
| **Développeur 1** | [Nom 1] | IABD | [Email] |
| **Développeur 2** | [Nom 2] | IABD | [Email] |
| **Développeur 3** | [Nom 3] | Telecom Réseau | [Email] |
| **Développeur 4** | [Nom 4] | Système Sécurité | [Email] |
| **Développeur 5** | [Nom 5] | Système Sécurité | [Email] |

---

## 📋 Répartition des Questions par Filière

### 🎯 **TOI - Lead & Merge Master**
- **Rôle** : Gestion du dépôt, review des PR, résolution de conflits
- **Tâches** :
  - Valider les pull requests
  - S'assurer de la cohérence entre C et Java
  - Rédiger le rapport final
  - Préparer la présentation

---

### 💻 **IABD 1 - Question 4 : Analyseur Syntaxique & Structure**
**Filière** : Informatique Appliquée aux Big Data  
**Pourquoi** : Requires compréhension approfondie des structures de données et parsing

**Questions assignées** :
- ✅ Q4a : `insererMonome()` - Insertion par ordre décroissant
- ✅ Q4b : `analyserPolynome()` - Parser la chaîne de caractères
- ✅ Q4c : `afficherPolynome()` - Affichage formaté

**Fichiers à modifier** :
- `c/src/polynome.c` : fonctions Q4
- `java/src/Polynome.java` : méthodes Q4

**Indice** : Commencer par comprendre la structure de liste chaînée

---

### 💻 **IABD 2 - Question 6c & 6d : Multiplication & Division**
**Filière** : Informatique Appliquée aux Big Data  
**Pourquoi** : Algorithmes complexes, logique mathématique avancée

**Questions assignées** :
- ✅ Q6c : `fois()` - Multiplication de polynômes
- ✅ Q6d : `quotient()` - Division euclidienne avec reste

**Fichiers à modifier** :
- `c/src/polynome.c` : fonctions `fois()` et `quotient()`
- `java/src/Polynome.java` : méthodes `fois()` et `quotient()`

**Indice** : 
- Multiplication : Double boucle (distributivité)
- Division : Algorithme similaire à la division euclidienne entière

---

### 📡 **Telecom Réseau - Question 5 : Évaluation**
**Filière** : Télécommunications et Réseaux  
**Pourquoi** : Calculs numériques, tests et validation

**Questions assignées** :
- ✅ Q5 : `eval()` - Évaluation du polynôme en un point x
- 🧪 Tests unitaires pour toutes les questions

**Fichiers à modifier** :
- `c/src/polynome.c` : fonction `eval()`
- `java/src/Polynome.java` : méthode `eval()`
- `c/tests/test_q5.c` - Tests C
- Compléter `java/src/Main.java`

**Bonus** : Créer un fichier de test avec plusieurs valeurs de x

---

### 🔒 **Système Sécurité 1 - Question 6a & 6b : Addition & Soustraction**
**Filière** : Systèmes et Sécurité Informatique  
**Pourquoi** : Logique algorithmique, opérations binaires

**Questions assignées** :
- ✅ Q6a : `plus()` - Addition de polynômes
- ✅ Q6b : `moins()` - Soustraction de polynômes

**Fichiers à modifier** :
- `c/src/polynome.c` : fonctions `plus()` et `moins()`
- `java/src/Polynome.java` : méthodes `plus()` et `moins()`

**Indice** : Fusion de deux listes triées (décroissant)

---

### 🔒 **Système Sécurité 2 - Question 7 : Garbage Collector**
**Filière** : Systèmes et Sécurité Informatique  
**Pourquoi** : Gestion mémoire, sécurité mémoire - parfait pour cette filière!

**Questions assignées** :
- ✅ Q7a : `marquerUtiles()` - Marquer les maillons accessibles
- ✅ Q7b : `libererInutiles()` - Libérer mémoire non utilisée
- ✅ Q7c : `garbageCollector()` - Fonction principale

**Fichiers à modifier** :
- `c/src/polynome.c` : fonctions Q7
- `java/src/Polynome.java` : méthode `liberer()` (simulation GC Java)

**Indice** : Algorithme "Mark and Sweep" classique

---

## 🔄 Workflow de Collaboration

### Pour les Développeurs (5 personnes)

```bash
# 1. Fork le repo sur GitHub
# 2. Cloner VOTRE fork
git clone https://github.com/[VOTRE_USERNAME]/polynomes-dic2.git
cd polynomes-dic2

# 3. Créer une branche pour votre question
git checkout -b q[Numéro]-[Nom]
# Exemple : git checkout -b q4-analyseur

# 4. Implémenter votre question
# Modifier les fichiers assignés

# 5. Commit
git add .
git commit -m "Q[Numéro]: Implémentation de [fonction]"

# 6. Push sur votre fork
git push origin q[Numéro]-[Nom]

# 7. Créer une Pull Request sur GitHub
# Titre : "Q[Numéro]: [Description] - [Votre Nom]"
```

### Pour le Lead (TOI)

```bash
# Review et Merge
git fetch origin
git checkout main
git pull origin main

# Tester la branche du collègue
git checkout -b test-q[Numéro] origin/q[Numéro]-[Nom]
# Compiler et tester

# Si OK, merge sur main
git checkout main
git merge q[Numéro]-[Nom]
git push origin main
```

---

## 📊 Planning Suggeré

| Semaine | IABD 1 | IABD 2 | Telecom | SysSec 1 | SysSec 2 |
|---------|--------|--------|---------|----------|----------|
| **S1** | Q4 Structure | Comprendre Q6 | Q5 Base | Q6a Base | Q7 Théorie |
| **S2** | Parser C | Multiplication C | Tests C | Addition C | Marquage C |
| **S3** | Parser Java | Division Java | Tests Java | Soustraction Java | GC Java |
| **S4** | PR + Debug | PR + Debug | PR + Tests | PR + Debug | PR + Debug |

---

## ✅ Checklist avant Pull Request

### Pour chaque développeur :
- [ ] Code commenté
- [ ] Compilation sans erreurs
- [ ] Tests passent
- [ ] README à jour (si nécessaire)
- [ ] Message de commit clair
- [ ] Pas de fichiers inutiles (binaries, etc.)

### Pour le Lead :
- [ ] Review du code
- [ ] Tests de compilation
- [ ] Tests d'exécution
- [ ] Fusion sans conflit
- [ ] Documentation mise à jour

---

## 🆘 Support

### Channels de communication suggérés :
- **Discord/WhatsApp** : Questions rapides
- **Issues GitHub** : Bugs et problèmes techniques
- **Pull Request Comments** : Review de code

### Ressources par filière :
- **IABD** : Documentation sur les listes chaînées, parsing
- **Telecom** : Tests unitaires, validation de données
- **Système Sécurité** : Documentation mémoire C, malloc/free

---

## 📝 Notes Spéciales

### Pour IABD 1 (Q4) :
Commencer par implémenter `insererMonome()` car c'est la base utilisée par tous les autres.

### Pour Telecom (Q5) :
Après implémentation de `eval()`, créer des tests avec différents polynômes et valeurs de x.

### Pour Système Sécurité 2 (Q7) :
En Java, le GC est automatique, mais créer une méthode `liberer()` qui met les références à null.

---

**Dernière mise à jour** : [Date]  
**Prochaine réunion** : [Date/Heure]  
**Deadline** : Avant mi-avril (comme demandé par le prof)
