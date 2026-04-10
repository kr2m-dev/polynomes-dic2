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
     * QUESTION 4: ÉVALUATION - À IMPLÉMENTER ⏳
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
     * QUESTION 5: OPÉRATIONS ARITHMÉTIQUES - À IMPLÉMENTER ⏳
     * ============================================================
     */

    /**
     * Additionne deux polynômes
     * TODO Q5a: À IMPLÉMENTER PAR IABD 2
     * @param autre Autre polynôme à additionner
     * @return Nouveau polynôme résultat
     */
    public Polynome plus(Polynome autre) {
        /* TODO Q5a: IMPLÉMENTER PAR IABD 2
         * Indice: Fusionner deux listes triées (décroissant)
         * Additionner coefficients si même exposant
         */
        
        /* Placeholder - À remplacer */
        throw new UnsupportedOperationException("Q5a: À implémenter par IABD 2");
        
        /* IABD 2: Implémentez ici!
        Polynome resultat = new Polynome();
        Monome p1 = this.tete;
        Monome p2 = autre.tete;
        
        while (p1 != null && p2 != null) {
            if (p1.getExposant() > p2.getExposant()) {
                resultat.insererMonome(p1.getCoeff(), p1.getExposant());
                p1 = p1.getSuivant();
            } else if (p1.getExposant() < p2.getExposant()) {
                resultat.insererMonome(p2.getCoeff(), p2.getExposant());
                p2 = p2.getSuivant();
            } else {
                resultat.insererMonome(p1.getCoeff() + p2.getCoeff(), p1.getExposant());
                p1 = p1.getSuivant();
                p2 = p2.getSuivant();
            }
        }
        
        while (p1 != null) {
            resultat.insererMonome(p1.getCoeff(), p1.getExposant());
            p1 = p1.getSuivant();
        }
        
        while (p2 != null) {
            resultat.insererMonome(p2.getCoeff(), p2.getExposant());
            p2 = p2.getSuivant();
        }
        
        return resultat;
        */
    }

    /**
     * Soustrait deux polynômes
     * TODO Q5b: À IMPLÉMENTER PAR IABD 2
     * @param autre Autre polynôme à soustraire
     * @return Nouveau polynôme résultat
     */
    public Polynome moins(Polynome autre) {
        /* TODO Q5b: IMPLÉMENTER PAR IABD 2
         * Indice: Similaire à l'addition mais avec signes négatifs
         */
        
        /* Placeholder - À remplacer */
        throw new UnsupportedOperationException("Q5b: À implémenter par IABD 2");
    }

    /**
     * Multiplie deux polynômes
     * TODO Q5c: À IMPLÉMENTER PAR SysSec 1
     * @param autre Autre polynôme à multiplier
     * @return Nouveau polynôme résultat
     */
    public Polynome fois(Polynome autre) {
        /* TODO Q5c: IMPLÉMENTER PAR SysSec 1
         * Indice: Double boucle (distributivité)
         * (a+b)*(c+d) = ac + ad + bc + bd
         * Multiplier coefficients et additionner exposants
         */
        
        /* Placeholder - À remplacer */
        throw new UnsupportedOperationException("Q5c: À implémenter par SysSec 1");
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
     * TODO Q5d: À IMPLÉMENTER PAR SysSec 1
     * @param diviseur Polynôme diviseur
     * @return Résultat contenant quotient et reste
     * @throws ArithmeticException si division par polynôme nul
     */
    public ResultatDivision quotient(Polynome diviseur) {
        /* TODO Q5d: IMPLÉMENTER PAR SysSec 1
         * a = b * quotient + reste
         * Algorithme:
         * Tant que deg(reste) >= deg(diviseur):
         *   terme = coeff_reste / coeff_diviseur, exp_reste - exp_diviseur
         *   quotient = quotient + terme
         *   reste = reste - (diviseur * terme)
         */
        
        if (diviseur.estNul()) {
            throw new ArithmeticException("Division par un polynôme nul");
        }
        
        /* Placeholder - À remplacer */
        throw new UnsupportedOperationException("Q5d: À implémenter par SysSec 1");
    }

    /* ============================================================
     * QUESTION 6: GARBAGE COLLECTOR - À IMPLÉMENTER ⏳
     * Assigné à: SysSec 2
     * ============================================================
     * En Java, le GC est automatique, mais on peut simuler:
     * - Marquer comme libérable: this.tete = null
     * - Suggérer GC: System.gc()
     */

    /**
     * Marque le polynôme comme pouvant être libéré
     * TODO Q6: À IMPLÉMENTER PAR SysSec 2
     */
    public void liberer() {
        /* TODO Q6: IMPLÉMENTER PAR SysSec 2
         * Indice: Mettre les références à null pour que le GC Java
         * puisse libérer la mémoire
         */
        
        /* Placeholder - À remplacer */
        throw new UnsupportedOperationException("Q6: À implémenter par SysSec 2");
        
        /* SysSec 2: Implémentez ici!
        this.tete = null;
        this.expressionOrig = null;
        */
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
}
