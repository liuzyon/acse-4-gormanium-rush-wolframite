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


bool same_vector(int* v1, int* v2) {
    for (int i = 0; i < 2 * num_units + 1; i++) {
        if (v1[i] != v2[i]) {
            return false;
        }
    }
    return true;
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


//Randomly initialize the population
void init_population(solution* pop) {
    int vector_size = 2 * num_units + 1;

#pragma omp parallel
    {
        int rand_num = omp_get_thread_num() * (int) time(NULL);
        srand(rand_num * 1000);
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

                score = Evaluate_Circuit(pop[i].curit_vector, num_units, 1e-6, 1000);
                if (score < 0) {
                    valid = false;
                }
                //print_vector(pop[i].curit_vector);
                //std::cout << valid << std::endl;
            } while (!valid);

            //Calculate the fitness_value for each solution
            //print_vector(pop[i].curit_vector);
            pop[i].fitness_value = score;
            //std::cout << score << std::endl;
            //std::cout << omp_get_thread_num() << std::endl;
        }
    }


}


//Roulette selection method
//Randomly choose the parents solution
int selection(solution* pop) {
    
    double total_p = 0;

    //Calculate total finess value
    for (int i = 0; i < POP_SIZE; i++) {
        total_p += pop[i].fitness_value;
    }

    //select a random number from 0 to 1
    double temp = rand_01();
    double wheel = 0;

    //Roulette selection method to select the parent index
    //If accumulation is larger than temp, output the index
    for (int i = 0; i < POP_SIZE; i++) {
        wheel += (pop[i].fitness_value) / total_p;
        if (wheel > temp) {
            return i;
        }
    }

    return POP_SIZE-1;
}


//Find the best fitness value solution
int find_best_sol(solution* pop) {

    int best_ind = 0;

    for (int i = 1; i < POP_SIZE; i++) {
        if (pop[i].fitness_value > pop[best_ind].fitness_value) {
            best_ind = i;
        }
    }

    return best_ind;
}


//deep copy one solution to another
void copy_solution(solution& sol1, solution& sol2) {
    for (int i = 0; i < 2 * num_units + 1; i++) {
        sol2.curit_vector[i] = sol1.curit_vector[i];
    }

    sol2.fitness_value = sol1.fitness_value;
}


int hamming_distance(int* v1, int* v2) {
    int ham_dis = 0;
    for (int i = 0; i < 2 * num_units + 1; i++) {
        if (v1[i] != v2[i]) {
            ham_dis++;
        }
    }
    return ham_dis;
}


//Cross over
void cross_over(solution* curt_pop, solution& child_1, solution& child_2) {
    int vector_size = 2 * num_units + 1;

    double cross_rate = rand_01();

    int par1_index = selection(curt_pop);
    int par2_index = selection(curt_pop);

    //Par2 should not be same as par1
    while ((par2_index = selection(curt_pop)) == par1_index);

    
    solution par1 = curt_pop[par1_index];
    solution par2 = curt_pop[par2_index];
    
    //One-point cross over
    if (cross_rate < CROSSOVER_RATE) {
        //Randomly select the cross point
        int cross_point = rand() % vector_size;
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
    for (int i = 1; i < vector_size; i++) {
        double mutation_rate = rand_01();

        //Randomly choose a mutated number
        if (mutation_rate < MUTATION_RATE) {
            curt_sol.curit_vector[i] = rand() % (num_units+2);
        }
    }
}


void print_vector(int* vec) {
    for (int i = 0; i < 2 * num_units + 1; i++) {
        std::cout << vec[i] << " ";
    }
    std::cout<<std::endl;
}

void Genetic_algorithm() {

    
    solution* curt_pop = new solution[POP_SIZE];
    solution* child_pop = new solution[POP_SIZE];

    ////Initialize two population, current population and children population
    std::cout << "Start Initializeing" << std::endl;
    init_population(curt_pop);
    //init_population(child_pop);
    for (int i = 0; i < POP_SIZE; i++) {
        child_pop[i].curit_vector = new int[2 * num_units + 1];
    }

    
    int gen = 0;
    
    //Initialize two children used to store the information after cross over
    
    //Record the best_fittness and number of unchanged iterations
    int ind = find_best_sol(curt_pop);
    double best_fittness = curt_pop[ind].fitness_value;
    int unchanged = 0;
    
    double start = omp_get_wtime();
    while (gen < MAX_ITERATION && unchanged < 200) {

        double pre_best = best_fittness;

        std::cout << gen << std::endl;
        std::cout << pre_best << std::endl;

        //The best solution in parents
        int best_ind = find_best_sol(curt_pop);

        int child_ind = 1;

        //Copy the best soultion in parent to child
        copy_solution(curt_pop[best_ind], child_pop[0]);
#pragma omp parallel shared(child_ind)
        {
            int rand_num = omp_get_thread_num() * (int)time(NULL);
            srand(gen * 1000 + rand_num);
            while (child_ind < POP_SIZE) {
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
#pragma omp critical
                {
                    val1 = Check_Validity(child_1.curit_vector);
                    val2 = Check_Validity(child_2.curit_vector);
                }
                double score_child1 = Evaluate_Circuit(child_1.curit_vector, num_units, 1e-6, 1000);
                double score_child2 = Evaluate_Circuit(child_2.curit_vector, num_units, 1e-6, 1000);


#pragma omp critical
                {
                    if (val1 && score_child1 > 0 && child_ind < POP_SIZE) {
                        child_1.fitness_value = score_child1;
                        copy_solution(child_1, child_pop[child_ind]);
                        child_ind++;
                    }


                    if (val2 && score_child2 > 0 && child_ind < POP_SIZE) {
                        child_2.fitness_value = score_child2;
                        copy_solution(child_2, child_pop[child_ind]);
                        child_ind++;
                    }
                }

                delete[] child_1.curit_vector;
                delete[] child_2.curit_vector;
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
    double end = omp_get_wtime();
    std::cout << end - start << std::endl;

    print_vector(curt_pop[ind].curit_vector);
    std::cout << best_fittness << std::endl;

    std::ofstream output_file("output.txt");

    for (int i = 0; i < 2 * num_units + 1; i++) {
        output_file << curt_pop[ind].curit_vector[i] << " ";
    }
    output_file << std::endl;
    output_file << gen << std::endl;
    output_file << best_fittness << std::endl;

    output_file.close();

    //Free memory
    free_memory(curt_pop);
    free_memory(child_pop);
    delete[] curt_pop;
    delete[] child_pop;
}