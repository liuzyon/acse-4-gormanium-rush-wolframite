#include "Genetic_Algorithm.h"
#include "CCircuit.h"

int main(int argc, char * argv[])
{
    cout << "Starting The Gormanium Rush..." << endl;
    cout << "Gormanium feed rate: " << circuit_gor << "kg/s" << endl;
    cout << "Waste feed rate: " << circuit_waste << "kg/s" << endl;
    cout << "purity of feed stream: " << purity_feed << "%" << endl;
    cout << "Gormanium price: " << gor_price << "£/kg" << endl;
    cout << "Waste cost: " << waste_price << "£/kg" << endl;
    cout << "the number of units in a circuit: " << num_units << endl;
    int sol[2*num_units + 1];
    Genetic_algorithm(sol);
    return 0;
}
