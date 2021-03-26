#pragma once
#include <vector>

using namespace std;

const int num_units = 10;     ///< The number of units in circuit

const double circuit_gor = 10;     ///< The gor flowrate in the circuit feed
const double circuit_waste = 100;       ///< The waste flowrate in the circuit feed
const double purity_feed = 100*circuit_gor/(circuit_gor+circuit_waste);    ///< The purity in the circuit feed

const double gor_price = 100;      ///< The price of gor
const double waste_price = 500;    ///< The price of waste

/**
     * @brief check the validity of circuit
     * @return bool
     * @param units : an reference of circuit vector
     * @details This function is used to check the validity of circuit by checking 
     *          if every unit of circuit satisfy four different conditions.
     */ 
bool Check_Validity(int *circuit_vector);

/**
     * @brief mark the unit
     * @return void
     * @param units : the number of units in the circuit
     * @details This function is used to mark every unit of the circuit
     *          by using the recursive function.
     */ 
void mark_units(int unit_num);

/**
     * @brief assign the vector of circuit into the vector of units
     * @return void
     * @param units : the vector of circuit, the index of vector unit, the index of the vector of circuit
     * @details This function is used to assign the the vector of circuit 
     *          into the vector of units by using the recursive function.   
     *          The rule in the assign function is that the first number of the unit in circuit vector is 
     *          the concentrate stream and the second number of the unit in circuit vector is 
     *          the tailing stream.
     */ 
void assignUnit(int *circuit_vector, int unit_index, int &vector_index);

/**
     * @brief check if every unit has a route forward to both of the outlet streams
     * @return void
     * @param units : an reference of vector
     * @details This function is check if every unit has a route forward to both 
     *          of the outlet streams. We firstly reverse the circuit and then
     *          test whether each unit has a path to the two streams.
     */ 
bool check_requ_two(int *circuit_vector);

/**
     * @brief search the units out from one unit of the reversed graph
     * @return void
     * @param units : start unit, vector of inversed circuit, stream of each unit
     * @details This function is used to search the units out from one unit of the reversed graph.
     *          If the unit has seen before,we will stop search.
     *          If the unit hasn't seen before, we will mark it.
     */ 
void dfs(int start, int *vis, vector< vector<int> > &inverse_graph);
