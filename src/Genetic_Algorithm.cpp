#include "Genetic_Algorithm.h"


double Evaluate_Circuit(int* circuit_vector, int num_units, double tolerance, int max_iterations) {

    // int vector_size = 2*num_units+1;

    //创建各个unit
    std::vector<CUnit> units(num_units);

    // 赋值每个unit id, 以及连接到精矿流和尾矿流的单元id
    for (int i = 0; i < num_units; i++)
    {
        units[i].setId(i);
        units[i].conc_num = circuit_vector[i * 2 + 1];
        units[i].tails_num = circuit_vector[i * 2 + 2];
    }

    //给出给电路中每个单元的两个成分进料速率的初步猜测
    for (int i = 0; i < num_units; i++)
    {
        units[i].init();
    }

    int iter_num = 0;
    int steady_unit = 0;
    while (iter_num < max_iterations)
    {
        // 对于每个单元，使用当前对进料流速的猜测来计算精矿和尾矿流中每个组分的流速（即根据前面提到的比例）这里可以写成成员方法
        for (int i = 0; i < num_units; i++)
        {
            units[i].cal_con_tail();
        }

        // 对每个单元，将进料的当前值存储起来作为旧进料值，并将所有组分的当前进料值设置为0 这里可以写作成员方法
        for (int i = 0; i < num_units; i++)
        {
            units[i].reset();
        }

        // 设置接收环路进料的那个单元的进料等于环路进料的总流速
        units[circuit_vector[0]].init();

        // 检查每个单元，将其精矿流速和尾矿流速加到合适单元的进料上（基于环路向量中各单元的关系），这也将导致对整个环路的精矿流和尾矿流的最新估计
        for (int i = 0; i < num_units; i++)
        {
            if (units[i].conc_num < num_units)
            {
                units[i].transf_con(units);
            }

            if (units[i].tails_num < num_units)
            {
                units[i].transf_tail(units);
            }
        }

        steady_unit = 0;
        // 对每个单元，用新的进料流量和旧的进料流速（之前存的）作比较。如果任何一个单元它的相对变化在给定的设定阈值之上，则重复步骤2。 比较可以写作成员方法
        for (int i = 0; i < num_units; i++)
        {
            double error = units[i].compare_to_old();
            if (error <= tolerance)
            {
                steady_unit++;
            }
        }

        if (steady_unit == num_units) break;
        iter_num++;
    }

    int concentrate_num = num_units;
    double Performance = 0.0;

    if (steady_unit == num_units) {
        for (int i = 0; i < num_units; i++) {
            if (units[i].conc_num == concentrate_num) {
                Performance += (units[i].conc_gor_rate * 100 - units[i].conc_waste_rate * 500);
            }
        }
    }
    else {
        Performance = -circuit_waste * 500;
    }

    return Performance;
}

//Randomly generate value from 0 to 1
double rand_01() {
    double number = (double) rand();
    number = number / RAND_MAX;
    return number;
}


//Free the memory
void free_memory(solution* pop) {

    for (int i = 0; i < POP_SIZE; i++) {
        delete[] pop[i].curit_vector;
    }
}


//Judge whether two vectors are same
bool same_vector(int* v1, int* v2) {
    for (int i = 0; i < 2 * num_units + 1; i++) {
        if (v1[i] != v2[i]) {
            return false;
        }
    }
    return true;
}


//Randomly initialize the population
void init_population(solution* pop) {
    int vector_size = 2 * num_units + 1;

#pragma omp parallel
    {
        
        //int rand_num = (omp_get_thread_num()+1) * (int) time(NULL);
        //srand(rand_num);
#pragma omp for
        for (int i = 0; i < POP_SIZE; i++) {

            //Allocate memory to each solution

            pop[i].curit_vector = new int[vector_size];
            bool valid = true;
            double score;
            do {
                pop[i].curit_vector[0] = rand() % num_units;
                
                for (int j = 0; j < num_units; j++) {
                    //Cannot self-recycle
                    while ((pop[i].curit_vector[2 * j + 1] = rand() % num_units) == j);

                    //Cannot output to the same unit
                    while ((pop[i].curit_vector[2 * j + 2] = rand() % num_units) == j ||
                        pop[i].curit_vector[2 * j + 2] == pop[i].curit_vector[2 * j + 1]);
                }

                int con_num = rand() % num_units;
                int tail_num = rand() % num_units;

                pop[i].curit_vector[2 * con_num + 1] = num_units;
                pop[i].curit_vector[2 * tail_num + 2] = num_units + 1;


#pragma omp critical
                {
                    valid = Check_Validity(pop[i].curit_vector);
                }

                score = Evaluate_Circuit(pop[i].curit_vector, num_units, 1e-6, 10000);
                   
                //The result doesn't converge
                if (score == -50000) {
                    valid = false;
                }
                
            } while (!valid);

            pop[i].fitness_value = score;
        }
    }


}


//deep copy one solution to another
void copy_solution(solution& sol1, solution& sol2) {
    for (int i = 0; i < 2 * num_units + 1; i++) {
        sol2.curit_vector[i] = sol1.curit_vector[i];
    }

    sol2.fitness_value = sol1.fitness_value;
}


//Bubble sort the population based on the fittness value
void sort_pop(solution* pop) {
    solution temp;
    temp.curit_vector = new int[2 * num_units + 1];
    //Sort the population
    for (int i = 0; i < POP_SIZE-1; i++) {
        for (int j = 0; j < POP_SIZE - 1 - i; j++) {
            if (pop[j].fitness_value > pop[j+1].fitness_value) {
                copy_solution(pop[j], temp);
                copy_solution(pop[j+1], pop[j]);
                copy_solution(temp, pop[j + 1]);
            }
        }
    }
    delete[] temp.curit_vector;
 }



//linear ranking solution
int selection(solution* pop) {
    double p_min = 0.1;
    double p_max = 0.9;
    double* prob = new double[POP_SIZE];

    //Give every solution a selected posibility
    for (int i = 0; i < POP_SIZE; i++) {
        prob[i] = p_min + (p_max - p_min) * (i / (POP_SIZE - 1));
    }
    double p_sum = 0;

    //Accumulate all possibility
    for (int i = 0; i < POP_SIZE; i++) {
        p_sum += prob[i];
    }

    //Randomly select one solution as parent
    double wheel = 0;
    double temp = rand_01();
    for (int i = 0; i < POP_SIZE; i++) {
        wheel += prob[i] / p_sum;
        if (wheel > temp) {
            delete[] prob;
            return i;
        }
    }
    delete[] prob;
    return POP_SIZE - 1;
}

//Cross over
void cross_over(solution* curt_pop, solution& child_1, solution& child_2) {
    int vector_size = 2 * num_units + 1;

    double cross_rate = rand_01();

    int par1_index = selection(curt_pop);
    int par2_index = selection(curt_pop);

    //Par2 should not be same as par1
    while ((par2_index = selection(curt_pop)) == par1_index);

    //Linear ranking method to select parents
    solution par1 = curt_pop[par1_index];
    solution par2 = curt_pop[par2_index];   

    
    //One-point cross over
    if (cross_rate < CROSSOVER_RATE) {
        //Randomly select the cross point
        int cross_point = 1+rand() % (vector_size-2);

        for (int j = 0; j < cross_point; j++) {
            child_1.curit_vector[j] = par2.curit_vector[j];
            child_2.curit_vector[j] = par1.curit_vector[j];
        }

        for (int j = cross_point; j < vector_size; j++) {
            child_1.curit_vector[j] = par1.curit_vector[j];
            child_2.curit_vector[j] = par2.curit_vector[j];
        }
    }
    else {
        for (int j = 0; j < vector_size; j++) {
            child_1.curit_vector[j] = par1.curit_vector[j];
            child_2.curit_vector[j] = par2.curit_vector[j];
        }
    }
}


//Mutate the solution
void mutation(solution& curt_sol) {
    int vector_size = 2 * num_units + 1;

    //Randomly mutated, but not equal to itself
    double mutation_rate = rand_01();
    if (mutation_rate < MUTATION_RATE) {
        int pre_value = curt_sol.curit_vector[0];
        while((curt_sol.curit_vector[0] = rand() % (num_units)) == pre_value);
    }

    for (int i = 1; i < vector_size; i++) {
        mutation_rate = rand_01();

        //Randomly choose a mutated number,  but not equal to itself
        if (mutation_rate < MUTATION_RATE) {
            int pre_value = curt_sol.curit_vector[i];
            while ((curt_sol.curit_vector[i] = rand() % (num_units+2)) == pre_value);
        }
    }
}


//Print out the vector
void print_vector(int* vec) {
    for (int i = 0; i < 2 * num_units + 1; i++) {
        std::cout << vec[i] << " ";
    }
    std::cout<<std::endl;
}


//Output the best solution to the txt file
void output(solution& best, int gen) {
    ofstream outfile("Output.txt");
    for (int i = 0; i < 2 * num_units + 1; i++) {
        outfile << best.curit_vector[i] << " ";
    }

    outfile << std::endl;
    outfile << gen << std::endl;
    outfile << best.fitness_value << std::endl;

    outfile.close();
}

double Genetic_algorithm() {

    solution* curt_pop = new solution[POP_SIZE];
    solution* child_pop = new solution[POP_SIZE];

    //Initialize two population, current population and children population
    std::cout << "Start Initializeing" << std::endl;
    init_population(curt_pop);
    for (int i = 0; i < POP_SIZE; i++) {
        child_pop[i].curit_vector = new int[2 * num_units + 1];
    }

    int gen = 0;
    sort_pop(curt_pop);
    double best_fitness = 0;
    int unchanged = 0;
    int best_gen = 0;

    while (gen < MAX_ITERATION && unchanged < 500) {
        //std::cout << gen << std::endl;
        double pre_best = curt_pop[POP_SIZE - 1].fitness_value;
        //copy the best into child population
        copy_solution(curt_pop[POP_SIZE - 1], child_pop[0]);
        int child_ind = 1;

#pragma omp parallel shared(child_ind)
        {
            while (child_ind < POP_SIZE) {

                //Initialize two children vector
                solution child_1;
                solution child_2;
                child_1.curit_vector = new int[2 * num_units + 1];
                child_2.curit_vector = new int[2 * num_units + 1];

                //Cross over between two parents
                cross_over(curt_pop, child_1, child_2);

                //Mutate two children
                mutation(child_1);
                mutation(child_2);

                //Check whether two children are valid
                bool val1, val2;

                //Check the validity of two children
#pragma omp critical
                {
                    val1 = Check_Validity(child_1.curit_vector);
                    val2 = Check_Validity(child_2.curit_vector);
                }

                //Evaluate the score of two children
                double score_child1 = Evaluate_Circuit(child_1.curit_vector, num_units, 1e-6, 1000);
                double score_child2 = Evaluate_Circuit(child_2.curit_vector, num_units, 1e-6, 1000);
                

#pragma omp critical
                {
                    //If score doesn't converge, it's invalid
                    if (val1 && score_child1 != -50000 && child_ind < POP_SIZE) {
                        child_1.fitness_value = score_child1;
                        copy_solution(child_1, child_pop[child_ind]);
                        child_ind++;
                    }


                    if (val2  && score_child1 != -50000 && child_ind < POP_SIZE) {
                        child_2.fitness_value = score_child2;
                        copy_solution(child_2, child_pop[child_ind]);
                        child_ind++;
                    }
                }

                delete[] child_1.curit_vector;
                delete[] child_2.curit_vector;
            }

        }

            //Update current population
            for (int i = 0; i < POP_SIZE; i++) {
                copy_solution(child_pop[i], curt_pop[i]);
            }

            //Sort the current population
            sort_pop(curt_pop);
            best_fitness = curt_pop[POP_SIZE - 1].fitness_value;

            if (best_fitness != pre_best) {
                std::cout << "Best fittness updated: " << best_fitness << std::endl;
                std::cout << "At generation: " << gen << std::endl;
                best_gen = gen;
            }
            
            //Calcuate unchanged iterations
            if (best_fitness == pre_best) {
                unchanged++;
            }
            else {
                unchanged = 0;
            }
            gen++;
        
    }

    //Print out the result
    std::cout << "Best fitness didn't change in 500 generation, quit the Genetic algorithm" << std::endl;
    std::cout << "The best vector is: " << std::endl;
    print_vector(curt_pop[POP_SIZE - 1].curit_vector);
    std::cout << "At generation: " << best_gen << std::endl;
    std::cout << "The best performace is: " << best_fitness << std::endl;

    output(curt_pop[POP_SIZE - 1], best_gen);

    //Free memory
    free_memory(curt_pop);
    free_memory(child_pop);
    delete[] curt_pop;
    delete[] child_pop;

    return best_fitness;

}