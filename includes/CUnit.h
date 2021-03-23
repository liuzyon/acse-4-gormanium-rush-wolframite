class CUnit {
public:
    //index of the unit to which this unit’s concentrate stream is connected
    int conc_num;
    //index of the unit to which this unit’s concentrate stream is connected
    int tails_num;
    //A Boolean that is changed to true if the unit has been seen
    bool mark;

    double conc_waste_num;
    double conc_gor_num;
    double conc_purity;
    
    double tails_waste_num;
    double tails_gor_num;

    double feed_gor_num;
    double feed_waste_num;

    double old_feed;
    
    void process();
};

