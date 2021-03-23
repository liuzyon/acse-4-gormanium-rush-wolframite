#include <vector>

#include <stdio.h>
#include <CUnit.h>
#include <CCircuit.h>

std::vector<CUnit> units(num_units);

void CUnit::process(double in_gor, double in_waste) {
    if(in_gor <= 0 || in_waste <= 0){
        cout << "unit process() input should greater than 0" << endl;
    }
    conc_gor_num = in_gor * 0.2;
    conc_waste_num = in_waste * 0.05;
    
    tails_gor_num = in_gor - conc_gor_num;
    tails_waste_num = in_waste - conc_waste_num;
    
    conc_purity = conc_gor_num / (conc_gor_num + conc_waste_num)
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


