#include <stdio.h>
#include <iostream>
#include "CUnit.h"
#include "CCircuit.h"
#include "Genetic_Algorithm.h"



void Genetic_algorithm_test(int a[]) {
    solution* curt_pop = new solution[POP_SIZE];
    solution* child_pop = new solution[POP_SIZE];

    //Set the random seed
    srand(unsigned int(time(NULL)));

    ////Initialize two population, current population and children population
    init_population(curt_pop);
    init_population(child_pop);


    int gen = 0;

    //Initialize two children used to store the information after cross over
    solution child_1;
    solution child_2;

    child_1.curit_vector = new int[2 * num_units + 1];
    child_2.curit_vector = new int[2 * num_units + 1];

    //Record the best_fittness and number of unchanged iterations
    int ind = find_best_sol(curt_pop);
    double best_fittness = curt_pop[ind].fitness_value;
    int unchanged = 0;

    while (gen < MAX_ITERATION) {

        double pre_best = best_fittness;

        //std::cout << gen << std::endl;
        //std::cout << pre_best << std::endl;

        //The best solution in parents
        int best_ind = find_best_sol(curt_pop);

        int child_ind = 1;

        //Copy the best soultion in parent to child
        copy_solution(curt_pop[best_ind], child_pop[0]);

        while (child_ind < POP_SIZE) {
            //Cross over between two parents
            cross_over(curt_pop, child_1, child_2);

            //Mutate two children
            mutation(child_1);
            mutation(child_2);

            //Check whether two children are valid
            bool val1, val2;
            val1 = Check_Validity(child_1.curit_vector);
            val2 = Check_Validity(child_2.curit_vector);


            if (val1) {
                child_1.fitness_value = Evaluate_Circuit(child_1.curit_vector, 1e-6, 1000);
                //std::cout << child_1.fitness_value << std::endl;
                copy_solution(child_1, child_pop[child_ind]);
                child_ind++;
            }


            if (val2 && child_ind < POP_SIZE) {
                child_2.fitness_value = Evaluate_Circuit(child_2.curit_vector, 1e-6, 1000);
                //std::cout << child_2.fitness_value << std::endl;
                copy_solution(child_2, child_pop[child_ind]);
                child_ind++;
            }
        }

        //copy all current population to children population
        for (int i = 0; i < POP_SIZE; i++) {
            copy_solution(child_pop[i], curt_pop[i]);
        }

        //Update best fitness
        ind = find_best_sol(curt_pop);
        best_fittness = curt_pop[ind].fitness_value;


        //Record the number of unchanged best fitness
        if (best_fittness == pre_best) {
            unchanged++;
        }
        else {
            unchanged = 0;
        }

        gen++;
    }

    print_vector(curt_pop[ind].curit_vector);
    std::cout << best_fittness << std::endl;
    for (int i = 0; i < 2 * num_units + 1; i++) {
        a[i] = curt_pop[ind].curit_vector[i];
    }

    //Free memory
    free_memory(curt_pop);
    free_memory(child_pop);

    delete[] child_1.curit_vector;
    delete[] child_2.curit_vector;
    delete[] curt_pop;
    delete[] child_pop;
}


int main(int argc, char* argv[])
{
    int a[2 * num_units + 1];
    Genetic_algorithm_test(a);
    bool res = Check_Validity(a);
    // if the 
    if (res == true)
        std::cout << "pass\n";
    else
        std::cout << "fail\n";

    return 0;
}