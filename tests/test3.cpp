#include "Genetic_Algorithm.h"
#include "CCircuit.h"
#include "CUnit.h"


int main(int argc, char* argv[])
{
    int solution[2 * num_units + 1];
    Genetic_algorithm(solution); 
    if (Check_Validity(solution)) {
        std::cout << "Pass" << std::endl;
    }
    else {
        std::cout << "Fail" << std::endl;
    }
}