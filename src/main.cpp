#include <iostream>
#include <vector>
#include <cmath>
#include "CUnit.h"
#include "CCircuit.h"
#include "Genetic_Algorithm.h"

using namespace std;
int main(int argc, char * argv[])
{
    cout << "Starting genetic algorithm program..." << endl;
    int circuit_vector[11] = {0,4,3,2,0,5,4,4,6,2,1};
    int max_iterations = 1000;
    double tolerance = 1.0e-6;
    double performance = Evaluate_Circuit(circuit_vector, 5, tolerance, max_iterations);
    cout << "Performance: " <<  performance << endl;
    return 0;
}
