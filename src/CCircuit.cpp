#include <stdio.h>
#include <iostream>
#include <vector>
#include <numeric>
#include "CUnit.h"
#include "CCircuit.h"

using namespace std;

static bool valid;
static bool debug = true;

std::vector<CUnit> units(num_units);

//assign conc_num&tails_num to units[unit_index]
void assignUnit(int *circuit_vector, int unit_index, int &vector_index)
{
    if(unit_index < num_units)
    {
        units[unit_index].conc_num = circuit_vector[vector_index];
        units[unit_index].tails_num = circuit_vector[vector_index + 1];
        vector_index += 2;
        assignUnit(circuit_vector, unit_index + 1, vector_index);
    }
    return;
}


void mark_units(int unit_num)
{
    if(valid == false || units[unit_num].mark)
    {
        return;
    }

    units[unit_num].mark = true;

    //detect self recyle
    if(units[unit_num].conc_num == unit_num || units[unit_num].tails_num == unit_num)
    {
        valid = false;
        return;
    }

    //detect the destinations are the same unit
    if(units[unit_num].conc_num == units[unit_num].tails_num)
    {
        valid = false;
        return;
    }

    //If we have seen this unit already exit
    //Mark that we have now seen the unit
    //If conc_num does not point at a circuit outlet recursively call the function
    if (units[unit_num].conc_num<num_units) 
    {
        mark_units(units[unit_num].conc_num);
    }
    else
    {
        // ...Potentially do something to indicate that you have seen an exit
        units[unit_num].reachConcentrate = true;
    }


    //If tails_num does not point at a circuit outlet recursively call the function
    if (units[unit_num].tails_num<num_units)
    {
        mark_units(units[unit_num].tails_num);
    }
    else
    {
        // ...Potentially do something to indicate that you have seen an exit
        units[unit_num].reachTailings = true;
    }
}


void dfs(int start, int *vis, vector< vector<int> > &inverse_graph)
{
  if (vis[start] == 1) return; // if seen before, stop search

  vis[start] = 1; // if not seen before, mark it

  //search the units out from this unit
  for (auto m: inverse_graph[start])
  {
        dfs(m, vis, inverse_graph);
  }
}

bool check_requ_two(int *circuit_vector)
{
  vector< vector<int> > inverse_graph(num_units+2);
  //Inverse the circuit
  for (int i = 0; i < num_units; i++)
  {
      int a = circuit_vector[i*2+1];
      int b = circuit_vector[i*2+2];
      inverse_graph[a].push_back(i);
      inverse_graph[b].push_back(i);
  }
  
  // cout << "Test for each cell to final concentrate" << endl;
  //test for each cell to final concentrate
  int vis_con[num_units+2]={0};
  dfs(num_units, vis_con, inverse_graph);
  
  int test_con = accumulate(vis_con, vis_con+num_units+2, 0);
  // cout << "test final concentrate: " << test1 << endl;
  bool con_pass = (test_con == num_units+1) && (vis_con[num_units+1] == 0);
  
  //test for each cell to final tailings
  int vis_tail[num_units+2]={0};
  dfs(num_units+1, vis_tail, inverse_graph);

  
  
  int test_tail = accumulate(vis_tail, vis_tail+num_units+2, 0);
  // cout  <<  "test final tailings: " << test2 << endl;
  bool tail_pass = (test_tail == num_units+1) && (vis_tail[num_units] == 0);
  
  valid = tail_pass&&con_pass;

  return valid;
}

bool Check_Validity(int *circuit_vector)
{
    valid = true;
    int startUnit = circuit_vector[0];
    //build the connection between units
    int vector_index = 1;
    assignUnit(circuit_vector, 0, vector_index);
    
    /*
    std::cout<<"circuit_vector="<<std::endl;
    for(int i = 0; i < 2 * num_units + 1; ++i)
    {
        std::cout<<circuit_vector[i]<<" ";
    }
    std::cout<<std::endl;
    std::cout<<"units="<<std::endl;
    for(int i = 0; i < num_units; ++i)
    {
        std::cout<<i<<" con="<<units[i].conc_num<<" tail="<<units[i].tails_num<<std::endl;
    }
    */

    for(int i = 0; i < num_units; ++i)
    {
        units[i].mark = units[i].reachConcentrate = units[i].reachTailings = false;
    }
    //traverse start at 0
    mark_units(startUnit);

    
    //check whether all unit are accessible
    for(int i = 0; i < num_units; ++i)
    {
        //this unit is not available
        if(units[i].mark == false)
        {
            return false;
        }
    }
    
    check_requ_two(circuit_vector);

    return valid;
}