#pragma once
#include <vector>
#include <stdio.h>
#include <cmath>
#include <fstream>
#include <iostream>
#include "CUnit.h"
#include "CCircuit.h"
#include <omp.h>

//Hyper parameters
static int POP_SIZE = 150;
static double CROSSOVER_RATE = 0.8;
static double MUTATION_RATE = 0.001;
static int MAX_ITERATION = 1000;

//Solution class, store the vector and fitness value
class solution {
public:
	int* curit_vector;
	double fitness_value;
};

bool same_vector(int* v1, int* v2);

void print_vector(int* vec);

double Evaluate_Circuit(int *circuit_vector, int num_units, double tolerance, int max_iterations);

void init_population(solution* pop);

void free_memory(solution* pop);

double rand_01();

int selection(solution* pop);

void cross_over(solution* curt_pop, solution& child_1, solution& child_2);

void mutation(solution& curt_sol);

void Genetic_algorithm();