#include <stdio.h>
#include <cmath>

#include "CUnit.h"
#include "CCircuit.h"
#include "Genetic_Algorithm.h"
#include "CCircuit.cpp"

int answer_vector[2*num_units+1] = {0, 1, 2, 3, 4, 4, 5, 6, 7, 7, 8, 8, 9,
                10, 11, 10, 11, 10, 11, 10, 11}  ;

double Evaluate_Circuit(int *circuit_vector, double tolerance, int max_iterations) {
    int vector_size = 2*num_units+1;
    int concentrate_num = num_units;
    double Performance = 0.0;
    
    for (int i = 0;i < vector_size; i++) {
        if(circuit_vector[i] == concentrate_num){
            Performance += (units[i].conc_gor_rate*100 - units[i].conc_waste_rate*500);
        }
    }
    return Performance;
}
