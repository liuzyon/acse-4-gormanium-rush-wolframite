#include <stdio.h>
#include <iostream>
#include <vector>
#include "CUnit.h"
#include "CCircuit.h"

std::vector<CUnit> units(num_units);

// void CUnit::process(){
//    conc_gor_rate = feed_gor_rate * 0.2;
//    conc_waste_rate = feed_waste_rate * 0.05;

//    tails_gor_rate = feed_gor_rate - conc_gor_rate;
//    tails_waste_rate = feed_waste_rate - conc_waste_rate;

//    conc_purity = conc_gor_rate / (conc_gor_rate + conc_waste_rate);
// }


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

