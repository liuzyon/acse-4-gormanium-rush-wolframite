/**                                 
 * @file CUnit.h                      
 * @author liuzhiyong
 * @version 1.0
 * @date 2021.3.24
 * @brief The header file of CUnit
 * @note
 */

#pragma once
#include <vector>
#include <cmath>

/** 
 * CUnit class
 * */
class CUnit {

private:
    /// id of Unit
    int id;

public:
    /// index of the unit to which this unit’s concentrate stream is connected
    int conc_num;

    /// index of the unit to which this unit’s concentrate stream is connected
    int tails_num;

    /// A Boolean that is changed to true if the unit has been seen
    bool mark;

    /// the waste rate of concentrate stream in this unit
    double conc_waste_rate;

    /// the valuable material rate of concentrate stream in this unit
    double conc_gor_rate;

    /// the waste rate of tail stream in this unit
    double tails_waste_rate;

    /// the valuable rate of tail stream in this unit
    double tails_gor_rate;

    /// the valuable material rate of feed in this unit
    double feed_gor_rate;

    /// the waste rate of feed in this unit
    double feed_waste_rate;

    /// old feed rate in this unit
    double old_feed_rate;

    /// whether each unit directly access to the concentrate stream
    bool reachConcentrate;

    ///whether each unit directly access to the tailing stream
    bool reachTailings;
    

    /**
     * @brief Set the id of unit
     * @param id an integer argument
     */
    void setId(int id);

    /**
     * @brief Init the feed of unit
     */ 
    void init();

    /**
     * @brief Calculate the flowrate of each component in both the concentrate and tailings streams 
     */ 
    void cal_con_tail();

    /**
     * @brief Store the current value of the feed to this cell as an old feed value and set the current value for all components to zero
     */
    void reset();

    /**
     * @brief Add the concentrate flows to the appropriate unit’s feed based on the linkages in the circuit vector.
     * @param units an reference of vector
     */
    void transf_con(std::vector<CUnit> &units);

    /**
     * @brief This function is used to transfer the tailing flow
     * @param units : an reference of vector
     * @return void
     * @details Add the tailings flows to the appropriate unit’s feed 
     *          based on the linkages in the circuit vector.
     */
    void transf_tail(std::vector<CUnit> &units);

    /**
     * @brief Check the difference between the newly calculated feed rate and the old feed rate for this cell
     * @return the absoluate value of difference
     */
    double compare_to_old();
    
};

