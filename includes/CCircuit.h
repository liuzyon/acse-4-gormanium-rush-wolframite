#pragma once
#include <vector>

using namespace std;
const int num_units = 20;

const double circuit_gor = 10;
const double circuit_waste = 100;
const double purity_feed = 100*circuit_gor/(circuit_gor+circuit_waste);

const double gor_price = 100;
const double waste_price = 500;

bool Check_Validity(int *circuit_vector);

void mark_units(int unit_num);

bool check_requ_two(int *circuit_vector);

void dfs(int start, int *vis, vector<vector<int> > &inverse_graph);
