#include <cmath>
#include <iostream>

#include "CUnit.h"
#include "CCircuit.h"
#include "Genetic_Algorithm.h"

int main(int argc, char * argv[])
{
    int max_iterations = 243;
    double tolerance = 1.0e-6;
    int vec1[2*num_units+1] = {0,4,3,2,0,5,4,4,6,2,1};
    std::cout << "Evaluate_Circuit(vec1, 5, " << tolerance << ", " << max_iterations << ") close to 24.82:\n";
    if (std::fabs(Evaluate_Circuit(vec1, 5, tolerance, max_iterations) - 24.82) < tolerance)
        std::cout << "pass\n";
    else
        std::cout << "fail\n";

    int vec2[2*num_units+1] = {6,16,7,7,13,11,12,15,5,3,6,0,2,14,12,1,12,14,11,5,16,11,9,4,1,0,8,5,10,2,6};
    max_iterations = 10000;
    std::cout << "Evaluate_Circuit(vec2, 15, " << tolerance << ", " << max_iterations << ") close to 10.47:\n";
    if (std::fabs(Evaluate_Circuit(vec2, 15, tolerance, max_iterations) - 10.47) < tolerance)
        std::cout << "pass\n";
    else
        std::cout << "fail";
}
