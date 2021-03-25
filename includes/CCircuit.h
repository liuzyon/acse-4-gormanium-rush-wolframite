#pragma once
const int num_units = 10;
const double circuit_gor = 10;
const double circuit_waste = 100;

bool Check_Validity(int *circuit_vector);

void mark_units(int unit_num);

bool check_requ_two(int *circuit_vector);

void dfs(int start, int *vis, vector<vector<int> > &inverse_graph);