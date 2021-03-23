#include <stdio.h>
#include <iostream>
#include <vector>
#include "CUnit.h"
#include "CCircuit.h"

std::vector<CUnit> units(num_units);

void CUnit::process(double in_gor_rate, double in_waste_rate){
    if(in_gor_rate <= 0 || in_waste_rate <= 0){
        std::cout << "unit process() input should greater than 0" << std::endl;
    }
    conc_gor_rate = in_gor_rate * 0.2;
    conc_waste_rate = in_waste_rate * 0.05;
    
    tails_gor_rate = in_gor_rate - conc_gor_rate;
    tails_waste_rate = in_waste_rate - conc_waste_rate;
    
    conc_purity = conc_gor_rate / (conc_gor_rate + conc_waste_rate);
}

void output_circuit(int *circuit_vector){
    circuit_vector[0] = 0;
    int count = 1;
    for (int i = 0; i < units.size(); i++)
    {
        circuit_vector[count] = units[i].conc_num;
        circuit_vector[++count] = units[i].tails_num;
        count++;
    }
}

bool Check_Validity(int *circuit_vector)
{

  return true;
}

void mark_units(int unit_num) {

  if (units[unit_num].mark) return;

  units[unit_num].mark = true;

  //If we have seen this unit already exit
  //Mark that we have now seen the unit
  //If conc_num does not point at a circuit outlet recursively call the function

  if (units[unit_num].conc_num<num_units) {
    mark_units(units[unit_num].conc_num);
  } else {
    // ...Potentially do something to indicate that you have seen an exit
  }
  //If tails_num does not point at a circuit outlet recursively call the function

  if (units[unit_num].tails_num<num_units) {
    mark_units(units[unit_num].tails_num);
  } else {
    // ...Potentially do something to indicate that you have seen an exit
  }
}

