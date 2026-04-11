#!/bin/bash

echo "========================================"
echo "  TESTS AUTOMATISES - POLYNOMES DIC2"
echo "========================================"
echo ""

cd /tmp/polynomes-dic2/c

echo "🔨 Compilation de polynome.c..."
gcc -c src/polynome.c -I include -lm -Wall -o polynome.o 2>&1 | grep -E "error:" && echo "❌ ERREURS DE COMPILATION" || echo "✓ Compilation OK"

echo ""
echo "🔨 Compilation des tests..."

# Test Q1
echo -n "  Test Q1 (analyseur)... "
gcc -o test_q1 tests/test_q1_analyseur.c polynome.o -I include -lm 2>&1 | grep -E "error:" && echo "❌" || echo "✓"

# Test Q5
echo -n "  Test Q5 (evaluation)... "
gcc -o test_q5 tests/test_q5_evaluation.c polynome.o -I include -lm 2>&1 | grep -E "error:" && echo "❌" || echo "✓"

# Test Q6
echo -n "  Test Q6 (operations)... "
gcc -o test_q6 tests/test_q6_operations.c polynome.o -I include -lm 2>&1 | grep -E "error:" && echo "❌" || echo "✓"

# Test Q7
echo -n "  Test Q7 (GC)... "
gcc -o test_q7 tests/test_q7_gc.c polynome.o -I include -lm 2>&1 | grep -E "error:" && echo "❌" || echo "✓"

echo ""
echo "🧪 Execution des tests..."
echo ""

if [ -f test_q1 ]; then
    ./test_q1 && echo "✅ Q1: Analyseur - PASS"
fi

if [ -f test_q5 ]; then
    ./test_q5 && echo "✅ Q5: Evaluation - PASS"
fi

if [ -f test_q6 ]; then
    ./test_q6 && echo "✅ Q6: Operations - PASS"
fi

if [ -f test_q7 ]; then
    ./test_q7 && echo "✅ Q7: GC - PASS"
fi

echo ""
echo "========================================"
echo "  TESTS TERMINES"
echo "========================================"
