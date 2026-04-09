/**
 * @file Main.java
 * @brief Programme de test pour la gestion des polynômes
 * @details Ce fichier doit être complété par le membre assigné aux tests
 *          ou par chacun pour tester sa question individuellement.
 * 
 * INSTRUCTIONS POUR LE GROUPE:
 * - Compléter les tests au fur et à mesure des implémentations
 * - Chaque membre peut ajouter ses propres tests
 * - Tester individuellement avant de merger
 */
public class Main {

    public static void main(String[] args) {
        System.out.println("========================================");
        System.out.println("  TEST DES POLYNOMES - Mini Projet DIC");
        System.out.println("========================================\n");

        // Expressions de test
        String[] expressions = {
            "3X^2 + 2X - 1",
            "-X^3 + 5X^2 + 4",
            "10",
            "X",
            "X^5",
            "-2X^2",
            "4X - 2X + 5",    // Devrait donner 2X + 5
            "2X^2 + 3X^2",    // Devrait donner 5X^2
            "0"
        };

        /* ============================================================
         * QUESTION 4: Test de l'analyseur et affichage
         * Assigné à: ___
         * ============================================================
         * TODO: Décommenter après implémentation de Q4
         */
        System.out.println("--- QUESTION 4: Analyseur syntaxique ---\n");
        Polynome[] polynomes = new Polynome[expressions.length];
        for (int i = 0; i < expressions.length; i++) {
            polynomes[i] = new Polynome(expressions[i]);
            System.out.println("Expression " + (i+1) + ": " + expressions[i]);
            System.out.println("Polynôme " + (i+1) + ": " + polynomes[i]);
            System.out.println();
        }

        /* ============================================================
         * QUESTION 5: Test d'évaluation
         * Assigné à: ___
         * ============================================================
         * TODO: Décommenter après implémentation de Q5
         */
        System.out.println("--- QUESTION 5: Évaluation ---\n");
        if (polynomes[0] != null) {
            double x = 2.0;
            System.out.println("P1(x) = " + polynomes[0]);
            System.out.println("P1(" + x + ") = " + polynomes[0].eval(x));
        } else {
            System.out.println("Erreur: polynomes[0] est null");
        }
        System.out.println();

        /* ============================================================
         * QUESTION 6: Test des opérations arithmétiques
         * Assignés à: ___
         * ============================================================
         * TODO: Décommenter après implémentation de Q6
         */
        System.out.println("--- QUESTION 6: Opérations arithmétiques ---\n");
        
        // Q6a: Addition
        System.out.println("Q6a - Addition:");
        // Polynome somme = polynomes[0].plus(polynomes[2]);
        // System.out.println("P1 + P3 = " + somme);
        System.out.println("[TODO: Implémenter Q6a]\n");

        // Q6b: Soustraction
        System.out.println("Q6b - Soustraction:");
        // Polynome diff = polynomes[0].moins(polynomes[5]);
        // System.out.println("P1 - P6 = " + diff);
        System.out.println("[TODO: Implémenter Q6b]\n");

        // Q6c: Multiplication
        System.out.println("Q6c - Multiplication:");
        // Polynome prod = polynomes[3].fois(polynomes[3]);
        // System.out.println("P4 * P4 = " + prod);
        System.out.println("[TODO: Implémenter Q6c]\n");

        // Q6d: Division
        System.out.println("Q6d - Division euclidienne:");
        // Polynome.ResultatDivision resultat = polynomes[0].quotient(polynomes[3]);
        // System.out.println("Quotient: " + resultat.quotient);
        // System.out.println("Reste: " + resultat.reste);
        System.out.println("[TODO: Implémenter Q6d]\n");

        /* ============================================================
         * QUESTION 7: Test du Garbage Collector
         * Assigné à: ___
         * ============================================================
         * TODO: Décommenter après implémentation de Q7
         */
        System.out.println("--- QUESTION 7: Garbage Collector ---\n");
        // System.out.println("En Java, le GC est automatique.");
        // System.out.println("Mémoire avant: " + Runtime.getRuntime().totalMemory());
        // for (int i = 0; i < 10000; i++) {
        //     Polynome temp = new Polynome("X^2 + 2X + 1");
        // }
        // System.gc();
        // System.out.println("Mémoire après GC: " + Runtime.getRuntime().totalMemory());
        System.out.println("[TODO: Implémenter Q7 pour voir les résultats]\n");

        System.out.println("========================================");
        System.out.println("  FIN DES TESTS");
        System.out.println("========================================");
    }
}
