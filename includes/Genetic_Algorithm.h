#pragma once
#include <vector>
//Hyper parameters
/// The number of the solutions, ie population
static int POP_SIZE = 100;
/// The rate of cross over. The range is from 0 to 1
static double CROSSOVER_RATE = 0.8;
/// The rate of mutation. The range is from 0 to 1
static double MUTATION_RATE = 0.1;
/// The number of iteration. It must more than 0
static int MAX_ITERATION = 100;

/**
* @brief This is a class that represent a chromosome.
* The chromosome has curit_vector representing the gene sequence.
* 
*/
// Solution class, store the vector and fitness value
class solution {
public:
	int* curit_vector;   ///< It is a address of array, which contains the gene sequence of this chromosome
	/// The fitness value of the vector
	/// @see Evaluate_Circuit()
	double fitness_value;
};

/**
        * @brief		Print the value in the vector
        * @param	    vec : the address of the array,
        * @return       void
        * @par Sample
        * @code
        *	int vec[2 * num_units + 1] = { 0,4,3,2,0,5,4,4,6,2,1 };
        *	print_vector(int* vec);
        * @endcode
        */
void print_vector(int* vec);

/**
        * @brief		This is a fitness function.
        * @param	    circuit_vector : the address of the array,
                        which contains the curit_vector of this solution.
        * @param	    tolerance :
        * @param	    max_iterations : the number of the maximum iteration.
        * @return       The double type value \n
        * @note	        The minimum of this value of this function -50000, 
        *               when the circuit is not steady.
        * @attention    max_iteration must more than 0.
        * @details  In this project, Each unit will recover 20% of 
        *           the gormanium to the concentrate together with 5% of 
        *           the waste. We will be paid £100 per kg of gormanium 
        *           in the product and charged £500 per kg of the waste material.
        *           According to these rule, we caulculate the final profit using
        *           this function.
        * @par Sample
        * @code
        *	int vec[2 * num_units + 1] = { 0,4,3,2,0,5,4,4,6,2,1 };
        *	double x = Evaluate_Circuit(vec , 1e-6 , 1000);
        * 	std::cout << x <<std::endl;
        * @endcode
        */
double Evaluate_Circuit(int* circuit_vector, double tolerance, int max_iterations);

/**
        * @brief		This is a function that initialise the population
        * @param	    pop : the address of the array, which contains the solutions
        * @return       void
        * @details      This function is used to initialise the POP_SIZE solutions that
        *               meet the requirements. The function that check the solutions' 
        *               validty is in function Check_Validity(int* circuit_vector). \n
        */
void init_population(solution* pop);


/**
        * @brief		This is a function that free the heap memory of each solution in population
        * @param	    pop : the address of the array, which contains the solutions
        * @return       void
        */
void free_memory(solution* pop);

/**
        * @brief		This is a function that randomly generated double value from 0 to 1
        * @param	    void
        * @return       The value of double type
        * @par Sample
        * @code
        *	double x =  rand_01();
        * 	std::cout << x <<std::endl;
        * @endcode
        */
double rand_01();

/**
        * @brief		This is a function that select one solution from the population
        * @param	    pop : the address of the array, which contains the solutions
        * @return       The value of int type
        * @details      We select the elements in the population according to the roulette method.
        */
int selection(solution* pop);

/**
        * @brief		This is a function that makes two solutions crossover to 
        *               generate two new solutions.
        * @param	    curt_pop : the address of the array,which contains the solutions
        * @param	    child_1 : An object of the solution type 
        * @param	    child_2 : An object of the solution type 
        * @return       void
        * @details      Using the selection(solution* pop) function to choose two solutions as parents 
        *               in population.Randomly decide if the parents should crossover. In this project, 
        *               we set the rate of the crossover is 0.8. You can change the rate by by yourself.
        *               If they don’t cross, they both go to the next step unchanged. If they are to 
        *               cross,  a random point in the vector is chosen and all of the values before 
        *               that point are swapped with the corresponding points in the other vector.After 
        *               cross over, store the two curit_vector in child_1 and child_2 respectively.
        */
void cross_over(solution* curt_pop, solution& child_1, solution& child_2);

/**
        * @brief		This is a function that makes the solution mutate.
        * @param	    curt_sol : An object of the solution type
        * @return       void
        * @details      Go over each of the numbers in the vectors and decide whether to mutate the curit_vector
        *               of this solution. You can set the rate of mutate through changing the double MUTATION_RATE.
        *               Randomly generate a number in the range from 0 to (num_units+1) as the value in this index 
        *               after mutation.
        */
void mutation(solution& curt_sol);


/**
        * @brief		This is a function that execute the genetic algorithm.
        * @param	    void
        * @return       void
        * @details      The steps of genetic algorithm are initialization, selection,cross over and mutation. 
        *               It will replace the parent vectors with generated child vectors and repeat the process
        *               until a set number of iterations have been completed or a threshold has been met.
        */
void Genetic_algorithm();

/**
        * @brief		This is a function that get the index of the solution in population that has the maximume 
        *               performance value.
        * @param	    pop : the address of the array,which contains the solutions
        * @return       The value of int type
        */
int find_best_sol(solution* pop);


/**
        * @brief		This is a function that copy the value of sol1's curit_vector to sol2's.
        *               This is deep copy.
        * @param	    sol1 : An object of the solution type
        * @param	    sol2 : An object of the solution type
        * @return       void
        */
void copy_solution(solution& sol1, solution& sol2);