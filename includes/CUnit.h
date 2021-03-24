#pragma once
#include <vector>
#include <cmath>

class CUnit {

private:
    int id;

public:
    //index of the unit to which this unit’s concentrate stream is connected
    int conc_num;
    //index of the unit to which this unit’s concentrate stream is connected
    int tails_num;
    //A Boolean that is changed to true if the unit has been seen
    bool mark;
    
    double conc_waste_rate;
    double conc_gor_rate;
    
    double tails_waste_rate;
    double tails_gor_rate;

    double feed_gor_rate;
    double feed_waste_rate;

    double old_feed_rate;

    void setId(int id);

    void init();

    void cal_con_tail();

    void reset();

    void transf_con(std::vector<CUnit> &units);

    void transf_tail(std::vector<CUnit> &units);

    double compare_to_old();

    
};

