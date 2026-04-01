/**
 * @file Monome.java
 * @brief Classe représentant un monôme d'un polynôme
 * @details Structure de base pour les membres du groupe
 * 
 * INSTRUCTIONS POUR LE GROUPE:
 * - Ne pas modifier cette classe (structure de base)
 * - Comprendre les attributs et méthodes fournies
 * - Utiliser cette classe dans Polynome.java
 */
public class Monome {
    // Attributs privés - Encapsulation (POO)
    private double coeff;       // Coefficient du monôme
    private int exposant;       // Exposant (degré)
    private Monome suivant;     // Lien vers le monôme suivant (liste chaînée)

    /**
     * Constructeur d'un monôme
     * @param coeff Coefficient du monôme
     * @param exposant Exposant (degré) du monôme
     */
    public Monome(double coeff, int exposant) {
        this.coeff = coeff;
        this.exposant = exposant;
        this.suivant = null;
    }

    // Getters et Setters (Encapsulation)
    public double getCoeff() {
        return coeff;
    }

    public void setCoeff(double coeff) {
        this.coeff = coeff;
    }

    public int getExposant() {
        return exposant;
    }

    public void setExposant(int exposant) {
        this.exposant = exposant;
    }

    public Monome getSuivant() {
        return suivant;
    }

    public void setSuivant(Monome suivant) {
        this.suivant = suivant;
    }

    /**
     * Vérifie si le monôme est nul (coefficient = 0)
     * @return true si le coefficient est nul
     */
    public boolean estNul() {
        return coeff == 0;
    }

    /**
     * Évalue le monôme pour une valeur donnée de x
     * @param x Valeur de la variable
     * @return Valeur du monôme évalué
     */
    public double evaluer(double x) {
        return coeff * Math.pow(x, exposant);
    }

    /**
     * Crée une copie du monôme
     * @return Une copie du monôme
     */
    public Monome copier() {
        return new Monome(this.coeff, this.exposant);
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        
        if (coeff < 0) {
            sb.append("- ");
        } else if (coeff > 0) {
            sb.append("+ ");
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

        return sb.toString();
    }
}
