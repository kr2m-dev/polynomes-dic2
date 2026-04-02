/**
 * @file Polynome.java
 * @brief Classe représentant un polynôme - Questions 1, 2, 3 complétées
 * @details Structure complète pour les camarades (Questions 4, 5, 6)
 * 
 * QUESTIONS COMPLÉTÉES:
 * - Q1: Analyseur syntaxique (parser)
 * - Q2: Codage en mémoire (liste chaînée)
 * - Q3: Affichage formaté (toString)
 * 
 * QUESTIONS À IMPLÉMENTER PAR LES CAMARADES:
 * - Q4: Évaluation (eval)
 * - Q5: Opérations arithmétiques
 * - Q6: Garbage Collector (simulation)
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

    /**
     * Constructeur de copie
     * @param autre Autre polynôme à copier
     */
    public Polynome(Polynome autre) {
        this();
        if (autre != null && autre.tete != null) {
            Monome courant = autre.tete;
            while (courant != null) {
                this.insererMonome(courant.getCoeff(), courant.getExposant());
                courant = courant.getSuivant();
            }
        }
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
     * QUESTION 1: ANALYSEUR SYNTAXIQUE
     * Assigné à: IABD 1 - COMPLÉTÉ
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
     * QUESTION 2: CODAGE EN MÉMOIRE
     * Assigné à: IABD 1 - COMPLÉTÉ
     * Insertion par ordre décroissant d'exposant
     * ============================================================ */

    /**
     * Insère un monôme par ordre décroissant d'exposant
     * Q2: Codage en mémoire (liste chaînée ordonnée)
     * @param coeff Coefficient du monôme
     * @param exposant Exposant du monôme
     */
    public void insererMonome(double coeff, int exposant) {
        if (coeff == 0) return; // Ignorer les coefficients nuls

        Monome nouveau = new Monome(coeff, exposant);

        // Insertion en tête si liste vide ou exposant plus grand
        if (tete == null || exposant > tete.getExposant()) {
            nouveau.setSuivant(tete);
            tete = nouveau;
            return;
        }

        // Si même exposant en tête
        if (tete.getExposant() == exposant) {
            tete.setCoeff(tete.getCoeff() + coeff);
            if (tete.getCoeff() == 0) {
                tete = tete.getSuivant(); // Supprimer si coefficient devient nul
            }
            return;
        }

        // Recherche de la position d'insertion
        Monome courant = tete;
        while (courant.getSuivant() != null && courant.getSuivant().getExposant() > exposant) {
            courant = courant.getSuivant();
        }

        // Vérifier si même exposant trouvé
        if (courant.getSuivant() != null && courant.getSuivant().getExposant() == exposant) {
            courant.getSuivant().setCoeff(courant.getSuivant().getCoeff() + coeff);
            if (courant.getSuivant().getCoeff() == 0) {
                courant.setSuivant(courant.getSuivant().getSuivant());
            }
            return;
        }

        // Insertion au milieu
        nouveau.setSuivant(courant.getSuivant());
        courant.setSuivant(nouveau);
    }

    /* ============================================================
     * QUESTION 3: AFFICHAGE
     * Assigné à: IABD 1 - COMPLÉTÉ
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
     * QUESTION 4: ÉVALUATION
     * Assigné à: Telecom Réseau - À IMPLÉMENTER
     * ============================================================
     * Objectif: Calculer P(x) = Σ(coeff * x^exposant)
     */

    /**
     * Évalue le polynôme pour une valeur donnée de x
     * TODO Q4: À IMPLÉMENTER
     * @param x Valeur de la variable
     * @return Valeur du polynôme évalué en x
     */
    public double eval(double x) {
        // TODO Q4: Implémenter l'évaluation
        // Indice: Parcourir la liste et sommer coeff * Math.pow(x, exposant)
        return 0.0;
    }

    /* ============================================================
     * QUESTION 5: OPÉRATIONS ARITHMÉTIQUES
     * Assignés à: IABD 2 (Q5a, Q5b), SysSec 1 (Q5c, Q5d)
     * ============================================================ */

    /**
     * Additionne deux polynômes
     * TODO Q5a: À IMPLÉMENTER (IABD 2)
     * @param autre Autre polynôme à additionner
     * @return Nouveau polynôme résultat
     */
    public Polynome plus(Polynome autre) {
        // TODO Q5a: Implémenter l'addition
        // Indice: Fusionner deux listes triées
        return new Polynome();
    }

    /**
     * Soustrait deux polynômes
     * TODO Q5b: À IMPLÉMENTER (IABD 2)
     * @param autre Autre polynôme à soustraire
     * @return Nouveau polynôme résultat
     */
    public Polynome moins(Polynome autre) {
        // TODO Q5b: Implémenter la soustraction
        return new Polynome();
    }

    /**
     * Multiplie deux polynômes
     * TODO Q5c: À IMPLÉMENTER (SysSec 1)
     * @param autre Autre polynôme à multiplier
     * @return Nouveau polynôme résultat
     */
    public Polynome fois(Polynome autre) {
        // TODO Q5c: Implémenter la multiplication
        // Indice: Double boucle (distributivité)
        return new Polynome();
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
     * TODO Q5d: À IMPLÉMENTER (SysSec 1)
     * @param diviseur Polynôme diviseur
     * @return Résultat contenant quotient et reste
     * @throws ArithmeticException si division par polynôme nul
     */
    public ResultatDivision quotient(Polynome diviseur) {
        // TODO Q5d: Implémenter la division euclidienne
        // a = b * quotient + reste
        if (diviseur.estNul()) {
            throw new ArithmeticException("Division par un polynôme nul");
        }
        return new ResultatDivision(new Polynome(), new Polynome());
    }

    /* ============================================================
     * QUESTION 6: GARBAGE COLLECTOR
     * Assigné à: SysSec 2 - À IMPLÉMENTER
     * ============================================================
     * En Java, le GC est automatique, mais on peut simuler:
     * - Marquer comme libérable: this.tete = null
     * - Suggérer GC: System.gc()
     */

    /**
     * Marque le polynôme comme pouvant être libéré
     * TODO Q6: À IMPLÉMENTER (SysSec 2)
     */
    public void liberer() {
        // TODO Q6: Marquer le polynôme comme inutilisé
        this.tete = null;
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
