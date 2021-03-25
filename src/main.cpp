#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include "CUnit.h"
#include "CCircuit.h"
#include "Genetic_Algorithm.h"

using namespace std;


int main(int argc, char * argv[])
{
    cout << "Starting genetic algorithm program..." << endl;
    int circuit_vector[21] = {4, 3, 4, 2, 6, 10, 3, 2, 1, 3, 9, 2, 0, 2, 5, 1, 8, 6, 10, 6, 7};
    int pass = check_requ_two(circuit_vector);
    cout << "是否通过：" << pass;
    // int max_iterations = 1000;
    // double tolerance = 1.0e-6;
    // double performance = Evaluate_Circuit(circuit_vector, 5, tolerance, max_iterations);
    // cout << "Performance: " <<  performance << endl;
    return 0;
}

