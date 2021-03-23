const int num_units = 10;

//module 2 used
const int max_iterations = 10;
const double threshold = 1.0e-6;
const double circuit_gor = 10;
const double circuit_waste = 100;
const int unit_size = 4;

bool Check_Validity(int *circuit_vector);

void mark_units(int unit_num);

void simulation(int *circuit_vector);
