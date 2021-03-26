#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include "CUnit.h"
#include "CCircuit.h"


using namespace std;

int main(int argc, char * argv[]){

        int invalid[21] = {4,3,4,2,6,10,3,2,1,3,9,2,0,2,5,1,8,6,10,6,7};
        int valid[21] = {7,5,1,8,11,9,0,9,6,10,9,4,8,9,2,9,3,4,7,4,5};

	std::cout << "Check_Validity({4,3,4,2,6,10,3,2,1,3,9,2,0,2,5,1,8,6,10,6,7}):\n";
        if (Check_Validity(invalid))
	    std::cout  << "fail\n";
	else
	    std::cout << "pass\n";

  
	std::cout << "Check_Validity({7,5,1,8,11,9,0,9,6,10,9,4,8,9,2,9,3,4,7,4,5}):\n";
        if (Check_Validity(valid))
            std::cout << "pass\n";
        else
            std::cout << "fail\n";


}


