#include <stdio.h>
#include <vector>
#include "CUnit.h"
#include "CCircuit.h"
#include "CCircuit.cpp"

using namespace std;

int main(int argc, char * argv[])
{
    double feed_gor_rate = 10;
    double feed_waste_rate = 100;

    //set the feed to the cell receiving the curcuit feed equal to the flowrates of the curcuit feed
    CUnit first_unit = units[0];
    first_unit.feed_gor_rate = feed_gor_rate;
    first_unit.feed_waste_rate = feed_waste_rate;
    
    //Start with the vectors representing the initial random collection of valid circuits.
    
    for(int i = 0; i < num_units; i++){
        
    }
    return 0;
}
