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
    int circuit_vector[41] = {18, 14, 2, 14, 16, 14, 9, 8, 19, 20, 15, 8, 18,18,12,14,0,4,13,14,10,3,11,19,17,18,21,4,14,8,3,20,8,14,7,5,6,14,1,8,5};
    int pass = check_requ_two(circuit_vector);
    cout << "是否通过：" << pass;
    // int max_iterations = 1000;
    // double tolerance = 1.0e-6;
    // double performance = Evaluate_Circuit(circuit_vector, 5, tolerance, max_iterations);
    // cout << "Performance: " <<  performance << endl;
    return 0;
}

