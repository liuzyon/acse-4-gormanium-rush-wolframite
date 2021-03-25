#include <stdio.h>
#include <iostream>
#include <vector>
#include <numeric>
#include "CUnit.h"
#include "CCircuit.h"

using namespace std;

std::vector<CUnit> units(num_units);

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


void dfs(int start, int *vis, vector<vector<int> > &inverse_graph)
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
  //unit i : i*2+1, i*2+2 in circuit_vector
  vector< vector<int> > inverse_graph(num_units+2); //Inverse the circuit
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

  // for (int i = 0; i < num_units+2; i++)
  // {
  //   cout << vis_con[i] << " ";
  // }
  
  int test_con = accumulate(vis_con, vis_con+num_units+2, 0);
  // cout << "test final concentrate: " << test1 << endl;
  bool con_pass = (test_con == num_units+1) && (vis_con[num_units+1] == 0);
  
  // cout << "Test for each cell to final talings" << endl;
  //test for each cell to final tailings
  int vis_tail[num_units+2]={0};
  dfs(num_units+1, vis_tail, inverse_graph);

  // for (int i = 0; i < num_units+2; i++)
  // {
  //   cout << vis_tail[i] << " ";
  // }
  
  int test_tail = accumulate(vis_tail, vis_tail+num_units+2, 0);
  // cout  <<  "test final tailings: " << test2 << endl;
  bool tail_pass = (test_tail == num_units+1) && (vis_tail[num_units] == 0);


  return con_pass && tail_pass;
}