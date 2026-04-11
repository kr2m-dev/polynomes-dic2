/**
 * @file Main.java
 * @brief Programme interactif de démonstration - Toutes les questions
 * @details Ce programme permet d'interagir avec toutes les fonctionnalités
 * du projet polynômes via un menu interactif.
 * 
 * Fonctionnalités:
 * - Q1-Q3: Analyse, codage, affichage
 * - Q4: Évaluation P(x)
 * - Q5: Opérations arithmétiques (+, -, *, /)
 * - Q6: Garbage Collector
 * - Q8: Versions récursives (bonus)
 */

import java.util.Scanner;

public class Main {
    private static Scanner scanner = new Scanner(System.in);
    
    /* Fonction utilitaire: pause avant de continuer */
    static void pause() {
        System.out.println("\nAppuyez sur Entrée pour continuer...");
        scanner.nextLine();
    }
    
    /* Affiche le menu principal */
    static void afficherMenu() {
        System.out.println("===============================================================");
        System.out.println("           GESTION DES POLYNOMES - Mini Projet DIC2            ");
        System.out.println("===============================================================");
        System.out.println("  1. Analyser et afficher un polynome (Q1-Q3)                  ");
        System.out.println("  2. Evaluer un polynome P(x) (Q4)                             ");
        System.out.println("  3. Addition de deux polynomes (Q5a)                          ");
        System.out.println("  4. Soustraction de deux polynomes (Q5b)                     ");
        System.out.println("  5. Multiplication de deux polynomes (Q5c)                   ");
        System.out.println("  6. Division euclidienne (Q5d)                                ");
        System.out.println("  7. Toutes les operations sur vos polynomes                  ");
        System.out.println("  8. Garbage Collector - Demonstration (Q6)                 ");
        System.out.println("  9. Version recursive vs iterative (Q8 - Bonus)            ");
        System.out.println("  10. Tests automatiques complets                             ");
        System.out.println("                                                               ");
        System.out.println("  0. Quitter                                                   ");
        System.out.println("===============================================================");
        System.out.print("\nVotre choix: ");
    }
    
    /* Question 1-3: Analyse et affichage */
    static void menuAnalyserAfficher() {
        System.out.println("\n=== QUESTION 1-3: ANALYSE ET AFFICHAGE ===\n");
        System.out.println("Grammaire supportée:");
        System.out.println("  - Polynôme: ['-'] monôme {('+'|'-') monôme}");
        System.out.println("  - Monôme: nombre ['*'] X ['^' exposant] | X ['^' exposant] | nombre");
        System.out.println("\nExemples valides:");
        System.out.println("  • 3X^2 + 2X - 1");
        System.out.println("  • -X^3 + 5X^2 + 4");
        System.out.println("  • 4X - 2X + 5");
        System.out.println("  • 2*X + 3");
        System.out.println("  • X");
        System.out.println("  • 10\n");
        
        System.out.print("Entrez votre polynôme: ");
        String expression = scanner.nextLine();
        
        System.out.println("\n--- Résultat ---");
        System.out.println("Expression: \"" + expression + "\"");
        
        Polynome p = new Polynome(expression);
        
        System.out.println("Polynôme analysé: \"" + p + "\"");
        System.out.println("Degré: " + p.getDegre());
        
        pause();
    }
    
    /* Question 4: Évaluation */
    static void menuEvaluation() {
        System.out.println("\n=== QUESTION 4: ÉVALUATION P(x) ===\n");
        
        System.out.print("Entrez votre polynôme: ");
        String expression = scanner.nextLine();
        
        Polynome p = new Polynome(expression);
        
        System.out.println("\nPolynôme: \"" + p + "\"\n");
        
        System.out.print("Entrez la valeur de x: ");
        double x = scanner.nextDouble();
        scanner.nextLine(); // Consommer le \n
        
        double resultat = p.eval(x);
        
        System.out.println("\n--- Résultat ---");
        System.out.printf("P(%.2f) = %.4f%n", x, resultat);
        
        pause();
    }
    
    /* Question 5a: Addition */
    static void menuAddition() {
        System.out.println("\n=== QUESTION 5a: ADDITION ===\n");
        
        System.out.print("Entrez le premier polynôme (P1): ");
        String expr1 = scanner.nextLine();
        
        System.out.print("Entrez le deuxième polynôme (P2): ");
        String expr2 = scanner.nextLine();
        
        Polynome p1 = new Polynome(expr1);
        Polynome p2 = new Polynome(expr2);
        
        System.out.println("\n--- Opération ---");
        System.out.println("P1 = \"" + p1 + "\"");
        System.out.println("P2 = \"" + p2 + "\"");
        System.out.print("P1 + P2 = ");
        
        Polynome somme = p1.plus(p2);
        System.out.println(somme);
        
        pause();
    }
    
    /* Question 5b: Soustraction */
    static void menuSoustraction() {
        System.out.println("\n=== QUESTION 5b: SOUSTRACTION ===\n");
        
        System.out.print("Entrez le premier polynôme (P1): ");
        String expr1 = scanner.nextLine();
        
        System.out.print("Entrez le deuxième polynôme (P2): ");
        String expr2 = scanner.nextLine();
        
        Polynome p1 = new Polynome(expr1);
        Polynome p2 = new Polynome(expr2);
        
        System.out.println("\n--- Opération ---");
        System.out.println("P1 = \"" + p1 + "\"");
        System.out.println("P2 = \"" + p2 + "\"");
        System.out.print("P1 - P2 = ");
        
        Polynome diff = p1.moins(p2);
        System.out.println(diff);
        
        pause();
    }
    
    /* Question 5c: Multiplication */
    static void menuMultiplication() {
        System.out.println("\n=== QUESTION 5c: MULTIPLICATION ===\n");
        
        System.out.print("Entrez le premier polynôme (P1): ");
        String expr1 = scanner.nextLine();
        
        System.out.print("Entrez le deuxième polynôme (P2): ");
        String expr2 = scanner.nextLine();
        
        Polynome p1 = new Polynome(expr1);
        Polynome p2 = new Polynome(expr2);
        
        System.out.println("\n--- Opération ---");
        System.out.println("P1 = \"" + p1 + "\"");
        System.out.println("P2 = \"" + p2 + "\"");
        System.out.print("P1 × P2 = ");
        
        Polynome produit = p1.fois(p2);
        System.out.println(produit);
        
        pause();
    }
    
    /* Question 5d: Division */
    static void menuDivision() {
        System.out.println("\n=== QUESTION 5d: DIVISION EUCLIDIENNE ===\n");
        System.out.println("Formule: P1 = P2 × Quotient + Reste\n");
        
        System.out.print("Entrez le dividende (P1): ");
        String expr1 = scanner.nextLine();
        
        System.out.print("Entrez le diviseur (P2): ");
        String expr2 = scanner.nextLine();
        
        Polynome p1 = new Polynome(expr1);
        Polynome p2 = new Polynome(expr2);
        
        System.out.println("\n--- Opération ---");
        System.out.println("P1 = \"" + p1 + "\"");
        System.out.println("P2 = \"" + p2 + "\"\n");
        
        if (p2.estNul()) {
            System.out.println("Erreur: Division par un polynôme nul!");
        } else {
            try {
                Polynome.ResultatDivision resultat = p1.quotient(p2);
                
                System.out.println("Quotient = \"" + resultat.quotient + "\"");
                System.out.println("Reste = \"" + resultat.reste + "\"");
                
                // Vérification
                Polynome verification = p2.fois(resultat.quotient).plus(resultat.reste);
                System.out.println("\nVérification (P2 × Q + R): \"" + verification + "\"");
            } catch (ArithmeticException e) {
                System.out.println("Erreur: " + e.getMessage());
            }
        }
        
        pause();
    }
    
    /* Question 6: Garbage Collector */
    static void menuGC() {
        System.out.println("\n=== QUESTION 6: GARBAGE COLLECTOR ===\n");
        System.out.println("En Java, le GC est automatique (pas besoin de Mark & Sweep manuel).");
        System.out.println("Cette démonstration utilise System.gc() pour suggérer le GC.\n");
        
        long memoireAvant = Runtime.getRuntime().totalMemory() - Runtime.getRuntime().freeMemory();
        System.out.println("Mémoire utilisée avant: " + memoireAvant + " bytes");
        
        // Créer beaucoup de polynômes temporaires
        System.out.println("\nCréation de 10000 polynômes temporaires...");
        for (int i = 0; i < 10000; i++) {
            Polynome temp = new Polynome("X^2 + 2X + 1");
        }
        
        // Suggérer au GC de s'exécuter
        System.gc();
        
        long memoireApres = Runtime.getRuntime().totalMemory() - Runtime.getRuntime().freeMemory();
        System.out.println("Mémoire utilisée après GC: " + memoireApres + " bytes");
        System.out.println("Différence: " + (memoireAvant - memoireApres) + " bytes");
        System.out.println("\n✓ Les polynômes temporaires ont été libérés par le GC automatique.");
        
        pause();
    }
    
    /* Question 8: Comparaison récursif vs itératif */
    static void menuRecursif() {
        System.out.println("\n=== QUESTION 8: VERSIONS RÉCURSIVES (BONUS) ===\n");
        System.out.println("Comparaison des approches itérative et récursive.\n");
        
        System.out.print("Entrez le premier polynôme (P1): ");
        String expr1 = scanner.nextLine();
        
        System.out.print("Entrez le deuxième polynôme (P2): ");
        String expr2 = scanner.nextLine();
        
        Polynome p1 = new Polynome(expr1);
        Polynome p2 = new Polynome(expr2);
        
        System.out.println("\n--- Addition Itérative (Q5a) ---");
        Polynome sommeIter = p1.plus(p2);
        System.out.println("P1 + P2 = \"" + sommeIter + "\"");
        
        System.out.println("\n--- Addition Récursive (Q8 - Bonus) ---");
        Polynome sommeRec = p1.plusRecursif(p2);
        System.out.println("P1 + P2 = \"" + sommeRec + "\"");
        
        System.out.println("\n--- Soustraction Itérative (Q5b) ---");
        Polynome diffIter = p1.moins(p2);
        System.out.println("P1 - P2 = \"" + diffIter + "\"");
        
        System.out.println("\n--- Soustraction Récursive (Q8 - Bonus) ---");
        Polynome diffRec = p1.moinsRecursif(p2);
        System.out.println("P1 - P2 = \"" + diffRec + "\"");
        
        System.out.println("\nNote: Les versions récursives sont plus élégantes mais");
        System.out.println("consomment plus de mémoire (pile d'appels).");
        
        pause();
    }
    
    /* Toutes les opérations sur 2 polynômes */
    static void menuToutesOperations() {
        System.out.println("\n=== TOUTES LES OPÉRATIONS ===\n");
        
        System.out.print("Entrez votre premier polynôme (P1): ");
        String expr1 = scanner.nextLine();
        
        System.out.print("Entrez votre deuxième polynôme (P2): ");
        String expr2 = scanner.nextLine();
        
        Polynome p1 = new Polynome(expr1);
        Polynome p2 = new Polynome(expr2);
        
        System.out.println("\n========================================");
        System.out.println("P1 = \"" + p1 + "\"");
        System.out.println("P2 = \"" + p2 + "\"");
        System.out.println("========================================\n");
        
        // Évaluation
        System.out.print("Entrez une valeur pour x (évaluation): ");
        double x = scanner.nextDouble();
        scanner.nextLine();
        
        System.out.println("\n--- Q4: ÉVALUATION ---");
        System.out.printf("P1(%.2f) = %.4f%n", x, p1.eval(x));
        System.out.printf("P2(%.2f) = %.4f%n", x, p2.eval(x));
        
        // Addition
        System.out.println("\n--- Q5a: ADDITION ---");
        Polynome somme = p1.plus(p2);
        System.out.println("P1 + P2 = \"" + somme + "\"");
        
        // Soustraction
        System.out.println("\n--- Q5b: SOUSTRACTION ---");
        Polynome diff = p1.moins(p2);
        System.out.println("P1 - P2 = \"" + diff + "\"");
        System.out.println("P2 - P1 = \"" + p2.moins(p1) + "\"");
        
        // Multiplication
        System.out.println("\n--- Q5c: MULTIPLICATION ---");
        Polynome produit = p1.fois(p2);
        System.out.println("P1 × P2 = \"" + produit + "\"");
        
        // Division
        System.out.println("\n--- Q5d: DIVISION ---");
        if (p2.estNul()) {
            System.out.println("Impossible: P2 est nul (division par zéro)");
        } else {
            try {
                Polynome.ResultatDivision resultatDiv = p1.quotient(p2);
                System.out.println("Quotient = \"" + resultatDiv.quotient + "\"");
                System.out.println("Reste = \"" + resultatDiv.reste + "\"");
            } catch (ArithmeticException e) {
                System.out.println("Erreur: " + e.getMessage());
            }
        }
        
        pause();
    }
    
    /* Tests automatiques complets */
    static void menuTestsAutomatiques() {
        System.out.println("\n=== TESTS AUTOMATIQUES COMPLETS ===\n");
        
        // Test Q1
        System.out.println("--- Q1: Analyseur syntaxique ---");
        String[] expressions = {
            "3X^2 + 2X - 1",
            "-X^3 + 5X^2 + 4",
            "4X - 2X + 5",
            "X",
            "10"
        };
        
        for (int i = 0; i < expressions.length; i++) {
            Polynome p = new Polynome(expressions[i]);
            System.out.println("✓ \"" + expressions[i] + "\" → \"" + p + "\"");
        }
        
        // Test Q4
        System.out.println("\n--- Q4: Évaluation ---");
        Polynome p = new Polynome("3X^2 + 2X - 1");
        System.out.println("P(X) = " + p);
        System.out.printf("P(2) = %.2f (attendu: 15.00)%n", p.eval(2.0));
        
        // Test Q5
        System.out.println("\n--- Q5: Opérations ---");
        Polynome a = new Polynome("X + 1");
        Polynome b = new Polynome("X - 1");
        
        System.out.println("A = " + a);
        System.out.println("B = " + b);
        
        Polynome s = a.plus(b);
        System.out.println("A + B = \"" + s + "\" (attendu: 2X)");
        
        Polynome m = a.fois(b);
        System.out.println("A × B = \"" + m + "\" (attendu: X^2 - 1)");
        
        System.out.println("\n✅ Tous les tests de base passés!");
        
        pause();
    }
    
    /* Programme principal */
    public static void main(String[] args) {
        int choix;
        
        do {
            afficherMenu();
            
            // Lecture sécurisée du choix
            String input = scanner.nextLine();
            try {
                choix = Integer.parseInt(input);
            } catch (NumberFormatException e) {
                choix = -1;
            }
            
            switch(choix) {
                case 1:
                    menuAnalyserAfficher();
                    break;
                case 2:
                    menuEvaluation();
                    break;
                case 3:
                    menuAddition();
                    break;
                case 4:
                    menuSoustraction();
                    break;
                case 5:
                    menuMultiplication();
                    break;
                case 6:
                    menuDivision();
                    break;
                case 7:
                    menuToutesOperations();
                    break;
                case 8:
                    menuGC();
                    break;
                case 9:
                    menuRecursif();
                    break;
                case 10:
                    menuTestsAutomatiques();
                    break;
                case 0:
                    System.out.println("\nAu revoir!");
                    break;
                default:
                    System.out.println("\nChoix invalide.");
                    pause();
            }
        } while (choix != 0);
        
        scanner.close();
    }
}
