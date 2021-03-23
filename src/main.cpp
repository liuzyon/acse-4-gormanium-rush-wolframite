#include <stdio.h>
#include <vector>
#include <cmath>
// #include "CUnit.h"
// #include "CCircuit.h"
// #include "CCircuit.cpp"
#include "Genetic_Algorithm.h"

using namespace std;
int main(int argc, char * argv[])
{
    int circuit_vector[11] = {0, 4, 3, 2, 0, 5, 4, 4, 6, 2, 1};
    Evaluate_Circuit(circuit_vector, 1.0e-6, 1000);
    return 0;
}
