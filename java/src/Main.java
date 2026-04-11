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
         * QUESTION 7: Test du Garbage Collector
         * Assigné à: Lead (GLSI)
         * Statut: ✅ IMPLÉMENTÉ
         * ============================================================
         * En Java, le GC est automatique. Cette démonstration montre
         * l'utilisation de System.gc() pour suggérer le garbage collection.
         */
        System.out.println("--- QUESTION 7: Garbage Collector ---\n");
        System.out.println("En Java, le GC est automatique.");
        long memoireAvant = Runtime.getRuntime().totalMemory() - Runtime.getRuntime().freeMemory();
        System.out.println("Mémoire utilisée avant: " + memoireAvant + " bytes");
        
        // Créer beaucoup de polynômes temporaires
        for (int i = 0; i < 10000; i++) {
            Polynome temp = new Polynome("X^2 + 2X + 1");
        }
        
        // Suggérer au GC de s'exécuter
        System.gc();
        
        long memoireApres = Runtime.getRuntime().totalMemory() - Runtime.getRuntime().freeMemory();
        System.out.println("Mémoire utilisée après GC: " + memoireApres + " bytes");
        System.out.println("Différence: " + (memoireAvant - memoireApres) + " bytes");

        System.out.println("========================================");
        System.out.println("  FIN DES TESTS");
        System.out.println("========================================");
    }
}
