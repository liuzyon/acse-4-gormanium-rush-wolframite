class CUnit {
public:
    //index of the unit to which this unit’s concentrate stream is connected
    int conc_num;
    //index of the unit to which this unit’s concentrate stream is connected
    int tails_num;
    //A Boolean that is changed to true if the unit has been seen
    bool mark;

    int id;
    
    double conc_waste_rate;
    double conc_gor_rate;
    double conc_purity;
    
    double tails_waste_rate;
    double tails_gor_rate;

    double feed_gor_rate;
    double feed_waste_rate;

    double old_feed_rate;
    
    void process(double in_gor_rate, double in_waste_rate);
};

