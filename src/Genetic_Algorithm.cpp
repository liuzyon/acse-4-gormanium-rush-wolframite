#include <stdio.h>
#include <cmath>
#include <vector>

#include "CUnit.h"
#include "CCircuit.h"
#include "Genetic_Algorithm.h"


double Evaluate_Circuit(int *circuit_vector, int num_units, double tolerance, int max_iterations) {

    // int vector_size = 2*num_units+1;

    // create an array of units in the circuit
    std::vector<CUnit> units(num_units);

    // Initilization: set units id and their connections
    for (int i = 0; i < num_units; i++)
    {
        units[i].setId(i);
        units[i].conc_num = circuit_vector[i*2+1];
        units[i].tails_num = circuit_vector[i*2+2];
    }

    // Give an initial guess for the feed rate of both components to every cell in the circuit
    for (int i = 0; i < num_units; i++)
    {
        units[i].init();
    }

    int iter_num = 0;
    int steady_unit = 0;
    while (iter_num < max_iterations)
    {
        // For each unit use the current guess of the feed flowrates to calculate the flowrate of each component in both the concentrate and tailings streams
        for (int i = 0; i < num_units; i++)
        {
            units[i].cal_con_tail();
        }

        // Store the current value of the feed to each cell as an old feed value and set the current value for all components to zero
        for (int i = 0; i < num_units; i++)
        {
            units[i].reset();
        }
    
        // Set the feed to the cell receiving the circuit feed equal to the flowrates of the circuit feed
        units[circuit_vector[0]].init();

        // Go over each unit and add the concentrate and tailings flows to the appropriate unit’s feed
        // based on the linkages in the circuit vector. This will also result in an updated estimate for the
        // overall circuit concentrate and tailings streams’ flows.
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
        // Check the difference between the newly calculated feed rate and the old feed rate for each cell.
        // If any of them have a relative change that is above a given threshold then repeat from step 2; otherwise, leave the loop.
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

    //  Based on the flowrates of the overall circuit concentrate stream, calculate a performance value for the circuit. 
    int concentrate_num = num_units;
    double Performance = 0.0;

    if (steady_unit == num_units){
        for (int i = 0; i < num_units; i++) {
            if(units[i].conc_num == concentrate_num){
                Performance += (units[i].conc_gor_rate*100 - units[i].conc_waste_rate*500);
            }
        }
    }else{
        // If there is no convergence, use the worst possible performance as the performance value 
        // the flowrate of waste in the feed times the value of the waste, which is usually a negative number
        Performance = - circuit_waste*500;
    }
  
    return Performance;
}
