/**
 * @file Polynome.java
 * @brief Classe représentant un polynôme - Q1, Q2, Q3 COMPLÉTÉES
 * @details Structure pour les camarades (Q4, Q5, Q6 À IMPLÉMENTER)
 * 
 * QUESTIONS COMPLÉTÉES:
 * - Q1: Analyseur syntaxique (parser)
 * - Q2: Codage en mémoire (liste chaînée)
 * - Q3: Affichage formaté (toString)
 * 
 * QUESTIONS À IMPLÉMENTER PAR LES CAMARADES:
 * - Q4: Évaluation (eval) - Telecom Réseau
 * - Q5a: Addition (plus) - IABD 2
 * - Q5b: Soustraction (moins) - IABD 2
 * - Q5c: Multiplication (fois) - SysSec 1
 * - Q5d: Division euclidienne (quotient) - SysSec 1
 * - Q6: Garbage Collector (liberer) - SysSec 2
 */

public class Polynome {
    private Monome tete;           // Premier monôme du polynôme
    private String expressionOrig; // Expression originale

    /**
     * Constructeur par défaut - crée un polynôme nul
     */
    public Polynome() {
        this.tete = null;
        this.expressionOrig = "";
    }

    /**
     * Constructeur à partir d'une expression textuelle
     * Q1: Analyseur syntaxique + Q2: Codage
     * @param expression Expression textuelle du polynôme
     */
    public Polynome(String expression) {
        this();
        this.expressionOrig = expression;
        parser(expression);
    }

    // Getters et Setters
    public Monome getTete() {
        return tete;
    }

    public void setTete(Monome tete) {
        this.tete = tete;
    }

    public boolean estNul() {
        return tete == null;
    }

    public int getDegre() {
        return (tete != null) ? tete.getExposant() : 0;
    }

    /* ============================================================
     * QUESTION 1: ANALYSEUR SYNTAXIQUE - COMPLÉTÉ ✓
     * Assigné à: IABD 1
     * Grammaire respectée:
     *   polynôme → ['-'] monôme { ('+' | '-') monôme }
     *   monôme → nombre '*' xpuissance | xpuissance | nombre
     * ============================================================ */

    /**
     * Parse une expression textuelle selon la grammaire
     * Q1: Analyseur syntaxique
     */
    private void parser(String expression) {
        String expr = expression.replaceAll("\\s+", ""); // Supprimer espaces
        int i = 0;
        int signe = 1;

        while (i < expr.length()) {
            // Gérer les signes
            if (expr.charAt(i) == '+') {
                signe = 1;
                i++;
            } else if (expr.charAt(i) == '-') {
                signe = -1;
                i++;
            }

            // Parser le monôme
            double coeff = 0;
            int exposant = 0;
            boolean aCoeff = false;
            boolean aX = false;

            // Parser le coefficient
            StringBuilder coeffStr = new StringBuilder();
            while (i < expr.length() && (Character.isDigit(expr.charAt(i)) || expr.charAt(i) == '.')) {
                coeffStr.append(expr.charAt(i));
                i++;
            }

            if (coeffStr.length() > 0) {
                coeff = Double.parseDouble(coeffStr.toString());
                aCoeff = true;
            }

            // Vérifier si '*' X suit
            if (i < expr.length() && expr.charAt(i) == '*') {
                i++;
            }

            // Vérifier si X
            if (i < expr.length() && (expr.charAt(i) == 'X' || expr.charAt(i) == 'x')) {
                aX = true;
                if (!aCoeff) {
                    coeff = 1.0;
                }
                i++;

                // Parser l'exposant
                if (i < expr.length() && expr.charAt(i) == '^') {
                    i++;
                    StringBuilder expStr = new StringBuilder();
                    while (i < expr.length() && Character.isDigit(expr.charAt(i))) {
                        expStr.append(expr.charAt(i));
                        i++;
                    }
                    if (expStr.length() > 0) {
                        exposant = Integer.parseInt(expStr.toString());
                    } else {
                        exposant = 1;
                    }
                } else {
                    exposant = 1;
                }
            }

            if (!aX) {
                exposant = 0;
                if (!aCoeff) {
                    coeff = 1.0;
                }
            }

            // Insérer le monôme
            if (coeff != 0) {
                insererMonome(signe * coeff, exposant);
            }

            signe = 1; // Reset signe par défaut
        }
    }

    /* ============================================================
     * QUESTION 2: CODAGE EN MÉMOIRE - COMPLÉTÉ ✓
     * Assigné à: IABD 1
     * Insertion par ordre décroissant d'exposant
     * ============================================================ */

    /**
     * Insère un monôme par ordre décroissant d'exposant
     * Q2: Codage en mémoire (liste chaînée ordonnée)
     * @param coeff Coefficient du monôme
     * @param exposant Exposant du monôme
     */
    public void insererMonome(double coeff, int exposant) {
        /* Q4: Insertion triée par degrés décroissants
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
        this.tete = insererTrie(this.tete, coeff, exposant);
    }

    /*
     * Q4: Insertion récursive triée par degrés décroissants
     * Implémenté par: Sokhna Maimouna
     * 
     * Algorithme récursif pour insérer un monôme dans une liste triée.
     * 
     * @param liste Tête de la liste chaînée
     * @param coef Coefficient du monôme à insérer
     * @param exp Exposant du monôme à insérer
     * @return Nouvelle tête de liste
     */
    private Monome insererTrie(Monome liste, double coef, int exp) {
        // Ignorer les coefficients nuls
        if (coef == 0.0) return liste;

        // Cas 1: Insertion en tête si liste vide ou exposant supérieur
        if (liste == null || exp > liste.getExposant()) {
            Monome m = new Monome(coef, exp);
            m.setSuivant(liste);
            return m;
        }

        // Cas 2: Même exposant en tête → fusionner les coefficients
        if (exp == liste.getExposant()) {
            liste.setCoeff(liste.getCoeff() + coef);
            // Si coefficient devient nul, supprimer ce monôme
            if (liste.getCoeff() == 0.0) {
                return liste.getSuivant(); // annulation
            }
            return liste;
        }

        // Cas 3: Insérer récursivement plus loin dans la liste
        liste.setSuivant(insererTrie(liste.getSuivant(), coef, exp));
        return liste;
    }

    /* ============================================================
     * QUESTION 3: AFFICHAGE - COMPLÉTÉ ✓
     * Assigné à: IABD 1
     * ============================================================ */

    /**
     * Affichage formaté du polynôme
     * Q3: Affichage
     * @return Représentation textuelle du polynôme
     */
    @Override
    public String toString() {
        if (tete == null) {
            return "0";
        }

        StringBuilder sb = new StringBuilder();
        Monome courant = tete;
        boolean premier = true;

        while (courant != null) {
            double coeff = courant.getCoeff();
            int exposant = courant.getExposant();

            if (!premier && coeff > 0) {
                sb.append(" + ");
            } else if (coeff < 0) {
                if (premier) {
                    sb.append("- ");
                } else {
                    sb.append(" - ");
                }
            }

            double absCoeff = Math.abs(coeff);
            if (exposant == 0 || absCoeff != 1.0) {
                sb.append(String.format("%.2f", absCoeff));
            }

            if (exposant > 0) {
                sb.append("X");
                if (exposant > 1) {
                    sb.append("^").append(exposant);
                }
            }

            premier = false;
            courant = courant.getSuivant();
        }

        return sb.toString();
    }

    /* ============================================================
     * QUESTION 4: ÉVALUATION - À IMPLÉMENTER
     * Assigné à: Telecom Réseau
     * ============================================================
     * Objectif: Calculer P(x) = Σ(coeff * x^exposant)
     */

    /**
     * Évalue le polynôme pour une valeur donnée de x
     * TODO Q4: À IMPLÉMENTER PAR Telecom Réseau
     * @param x Valeur de la variable
     * @return Valeur du polynôme évalué en x
     */
    public double eval(double x) {
        double resultat = 0.0;
        Monome courant = tete;
        while (courant != null) {
            resultat += courant.evaluer(x);
            courant = courant.getSuivant();
        }
        return resultat;
    }

    /* ============================================================
     * QUESTION 5: OPÉRATIONS ARITHMÉTIQUES - À IMPLÉMENTER
     * ============================================================
     */

    /**
     * Additionne deux polynômes
     * Implémenté par: Makhtar Gueye (IABD 2)
     * 
     * Fusion de deux listes triées par ordre décroissant d'exposant.
     * Algorithme: Parcours simultané avec pointeurs tête+queue pour insertion O(1).
     * 
     * Remerciements: Merci à Makhtar Gueye pour cette implémentation optimisée!
     * 
     * @param autre Autre polynôme à additionner
     * @return Nouveau polynôme résultat
     */
    public Polynome plus(Polynome autre) {
        Polynome resultat = new Polynome();
        Monome queue = null;
        
        Monome a = this.tete;
        Monome b = autre.tete;

        while (a != null || b != null) {
            double coeff;
            int exposant;

            /* Cas 1: a a un exposant plus grand que b (ou b est vide) */
            if (a != null && (b == null || a.getExposant() > b.getExposant())) {
                coeff = a.getCoeff();
                exposant = a.getExposant();
                a = a.getSuivant();
            }
            /* Cas 2: b a un exposant plus grand que a (ou a est vide) */
            else if (b != null && (a == null || b.getExposant() > a.getExposant())) {
                coeff = b.getCoeff();
                exposant = b.getExposant();
                b = b.getSuivant();
            }
            /* Cas 3: même exposant → additionner les coefficients */
            else {
                coeff = a.getCoeff() + b.getCoeff();
                exposant = a.getExposant();
                a = a.getSuivant();
                b = b.getSuivant();
            }

            /* Ignorer les coefficients nuls */
            if (coeff == 0.0) continue;

            /* Créer un nouveau monôme */
            Monome m = new Monome(coeff, exposant);
            
            /* Insérer en fin avec pointeur queue (O(1)) */
            if (resultat.tete == null) {
                resultat.tete = m;
                queue = m;
            } else {
                queue.setSuivant(m);
                queue = m;
            }
        }

        return resultat;
    }

    /**
     * Soustrait deux polynômes
     * Implémenté par: Makhtar Gueye (IABD 2)
     * 
     * Stratégie élégante: a - b = a + (-b)
     * La méthode privée negation() crée une copie de b avec coefficients inversés.
     * 
     * Remerciements: Merci à Makhtar Gueye pour cette approche astucieuse!
     * 
     * @param autre Autre polynôme à soustraire
     * @return Nouveau polynôme résultat
     */
    public Polynome moins(Polynome autre) {
        Polynome negB = negation(autre);
        return this.plus(negB);
    }

    /**
     * Méthode auxiliaire privée: Négation d'un polynôme
     * Crée une copie avec tous les coefficients multipliés par -1.
     * 
     * Utilisée par moins() pour implémenter a - b = a + (-b).
     * 
     * @param p Polynôme à négater
     * @return Nouveau polynôme avec coefficients inversés
     */
    private static Polynome negation(Polynome p) {
        Polynome neg = new Polynome();
        Monome queue = null;
        
        Monome courant = p.tete;
        while (courant != null) {
            Monome m = new Monome(-courant.getCoeff(), courant.getExposant());
            
            if (neg.tete == null) {
                neg.tete = m;
                queue = m;
            } else {
                queue.setSuivant(m);
                queue = m;
            }
            
            courant = courant.getSuivant();
        }
        
        return neg;
    }

    /**
     * Multiplie deux polynômes
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
     * 
     * @param autre Autre polynôme à multiplier
     * @return Nouveau polynôme résultat
     */
    public Polynome fois(Polynome autre) {
        /* Vérifier que les deux polynômes sont non nuls */
        if (this.estNul() || autre.estNul())
            return new Polynome();

        Polynome resultat = new Polynome();

        /* Double boucle: distribuer chaque monôme de this sur chaque monôme de autre */
        for (Monome p = this.tete; p != null; p = p.getSuivant()) {
            Polynome temp = new Polynome();

            for (Monome q = autre.tete; q != null; q = q.getSuivant()) {
                /* Créer un nouveau monôme: coeff produit, somme exposants */
                Monome m = new Monome(p.getCoeff() * q.getCoeff(), p.getExposant() + q.getExposant());
                
                /* Insérer dans temp (utilise l'insertion récursive de Q4) */
                temp.tete = insererTrie(temp.tete, m.getCoeff(), m.getExposant());
            }

            /* Additionner le résultat partiel au résultat global */
            resultat = resultat.plus(temp);
        }

        return resultat;
    }

    /**
     * Classe interne pour stocker le résultat de la division
     */
    public static class ResultatDivision {
        public final Polynome quotient;
        public final Polynome reste;

        public ResultatDivision(Polynome quotient, Polynome reste) {
            this.quotient = quotient;
            this.reste = reste;
        }
    }

    /**
     * Division euclidienne de deux polynômes
     * Implémenté par: Khadidiatou Niakh (SysSec 1)
     * 
     * Algorithme: Division polynomiale classique
     * Tant que deg(reste) >= deg(diviseur):
     *   terme = coeff_reste / coeff_diviseur, exp_reste - exp_diviseur
     *   quotient = quotient + terme
     *   reste = reste - (diviseur × terme)
     * 
     * Remerciements: Merci à Khadidiatou Niakh pour cette implémentation!
     * 
     * @param diviseur Polynôme diviseur
     * @return Résultat contenant quotient et reste
     * @throws ArithmeticException si division par polynôme nul
     */
    public ResultatDivision quotient(Polynome diviseur) {
        /* Vérifier division par zéro */
        if (diviseur.estNul()) {
            throw new ArithmeticException("Division par un polynôme nul");
        }

        Polynome q = new Polynome();      /* Quotient */
        Polynome r = this.copier();       /* Reste (initialisé au dividende) */

        /* Algorithme de division euclidienne */
        while (!r.estNul() && r.getDegre() >= diviseur.getDegre()) {
            /* Calculer le terme du quotient */
            double coeff = r.tete.getCoeff() / diviseur.tete.getCoeff();
            int exposant = r.getDegre() - diviseur.getDegre();

            /* Créer et ajouter le terme au quotient */
            Monome m = new Monome(coeff, exposant);
            q.tete = insererTrie(q.tete, m.getCoeff(), m.getExposant());

            /* Soustraire (diviseur × terme) du reste */
            Polynome temp = new Polynome();
            temp.tete = new Monome(coeff, exposant);
            Polynome produit = diviseur.fois(temp);
            r = r.moins(produit);
        }

        return new ResultatDivision(q, r);
    }

/* ============================================================
 * QUESTION 7: GARBAGE COLLECTOR
 * Implémenté par: [Ton nom] (GLSI - Lead)
 * ============================================================
 * 
 * En Java, le Garbage Collector est automatique, mais on peut
 * "suggérer" explicitement la libération en mettant les références
 * à null, rendant les objets éligibles au GC.
 */

/**
 * Q7: Marque le polynôme comme pouvant être libéré
 * 
 * En Java, le Garbage Collector est automatique, mais cette méthode
 * permet de suggérer explicitement la libération.
 * 
 * Remerciements: Merci à toute l'équipe pour cette collaboration!
 */
public void liberer() {
    /* Mettre les références à null pour que le GC Java
     * puisse libérer la mémoire associée */
    this.tete = null;
    this.expressionOrig = null;
    
    /* Suggérer explicitement au GC de s'exécuter (optionnel) */
    System.gc();
}

/**
 * Crée une copie profonde du polynôme
 * @return Une copie du polynôme
 */
public Polynome copier() {
    Polynome copie = new Polynome();
    Monome courant = this.tete;
    while (courant != null) {
        copie.insererMonome(courant.getCoeff(), courant.getExposant());
        courant = courant.getSuivant();
    }
    return copie;
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

/**
 * Q8a: Addition récursive (version bonus)
 * Implémenté par: Ame Thiam (TR) ou Lead (GLSI)
 * 
 * Approche récursive élégante:
 * - Cas de base: si a null, retourner copie de b; si b null, retourner copie de a
 * - Si a.exposant > b.exposant: créer maillon(a), puis fusionner(a.suivant, b)
 * - Si a.exposant < b.exposant: créer maillon(b), puis fusionner(a, b.suivant)
 * - Si même exposant: somme coefficients, puis fusionner(a.suivant, b.suivant)
 * 
 * Remerciements: Merci à Ame Thiam pour cette implémentation!
 * 
 * @param autre Autre polynôme à additionner
 * @return Nouveau polynôme résultat
 */
public Polynome plusRecursif(Polynome autre) {
    return plusRecursifAux(this.tete, autre.tete);
}

/**
 * Méthode auxiliaire récursive pour l'addition
 * 
 * @param a Tête de la première liste
 * @param b Tête de la deuxième liste
 * @return Nouveau polynôme résultat
 */
private static Polynome plusRecursifAux(Monome a, Monome b) {
    /* Cas de base: les deux listes vides */
    if (a == null && b == null) {
        return new Polynome();
    }
    
    /* Cas: a vide, copier b */
    if (a == null) {
        Polynome resultat = new Polynome();
        resultat.tete = new Monome(b.getCoeff(), b.getExposant());
        resultat.tete.setSuivant(plusRecursifAux(null, b.getSuivant()).tete);
        return resultat;
    }
    
    /* Cas: b vide, copier a */
    if (b == null) {
        Polynome resultat = new Polynome();
        resultat.tete = new Monome(a.getCoeff(), a.getExposant());
        resultat.tete.setSuivant(plusRecursifAux(a.getSuivant(), null).tete);
        return resultat;
    }
    
    /* Cas 1: exposant de a est supérieur */
    if (a.getExposant() > b.getExposant()) {
        Polynome resultat = new Polynome();
        resultat.tete = new Monome(a.getCoeff(), a.getExposant());
        resultat.tete.setSuivant(plusRecursifAux(a.getSuivant(), b).tete);
        return resultat;
    }
    
    /* Cas 2: exposant de b est supérieur */
    else if (a.getExposant() < b.getExposant()) {
        Polynome resultat = new Polynome();
        resultat.tete = new Monome(b.getCoeff(), b.getExposant());
        resultat.tete.setSuivant(plusRecursifAux(a, b.getSuivant()).tete);
        return resultat;
    }
    
    /* Cas 3: même exposant */
    else {
        double c = a.getCoeff() + b.getCoeff();
        if (c == 0.0) {
            /* Sauter les deux monômes si annulation */
            return plusRecursifAux(a.getSuivant(), b.getSuivant());
        }
        Polynome resultat = new Polynome();
        resultat.tete = new Monome(c, a.getExposant());
        resultat.tete.setSuivant(plusRecursifAux(a.getSuivant(), b.getSuivant()).tete);
        return resultat;
    }
}

/**
 * Q8b: Soustraction récursive (version bonus)
 * Implémenté par: Ame Thiam (TR) ou Lead (GLSI)
 * 
 * Stratégie: a - b = a + (-b)
 * Créer une négation de b, puis appeler plusRecursif.
 * 
 * Remerciements: Merci à Ame Thiam pour cette implémentation!
 * 
 * @param autre Autre polynôme à soustraire
 * @return Nouveau polynôme résultat
 */
public Polynome moinsRecursif(Polynome autre) {
    /* Créer la négation de b */
    Polynome negB = negationRecursif(autre.tete);
    
    /* Appeler plusRecursif avec a et -b */
    return this.plusRecursif(negB);
}

/**
 * Méthode auxiliaire récursive pour la négation
 * 
 * @param p Tête de la liste à négater
 * @return Nouveau polynôme avec coefficients inversés
 */
private static Polynome negationRecursif(Monome p) {
    if (p == null) {
        return new Polynome();
    }
    
    Polynome resultat = new Polynome();
    resultat.tete = new Monome(-p.getCoeff(), p.getExposant());
    resultat.tete.setSuivant(negationRecursif(p.getSuivant()).tete);
    return resultat;
}
}
