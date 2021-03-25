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
* @brief This is a class that represent a CUnit.
* The Cunit has some attributes and actions used in the circuit simulation.
* 
*/
class CUnit {

private:

    int id; ///< ID of Unit, the id is range from 0 to num_units -1.

public:

    int conc_num;   ///< index of the unit to which this unit’s concentrate stream is connected

    int tails_num;  ///< index of the unit to which this unit’s concentrate stream is connected

    bool mark;  ///< A Boolean that is changed to true if the unit has been seen

    double conc_waste_rate; ///< the waste rate of concentrate stream in this unit

    double conc_gor_rate;   ///< the valuable material rate of concentrate stream in this unit

    double tails_waste_rate;    ///< the waste rate of tail stream in this unit

    ///< the valuable rate of tail stream in this unit
    double tails_gor_rate;

    ///< the valuable material rate of feed in this unit
    double feed_gor_rate;

    double feed_waste_rate; ///< the waste rate of feed in this unit

    double old_feed_rate;   ///< old feed rate in this unit

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
     * @brief Add the tailings flows to the appropriate unit’s feed based on the linkages in the circuit vector.
     * @param units an reference of vector
     */
    void transf_tail(std::vector<CUnit> &units);

    /**
     * @brief Check the difference between the newly calculated feed rate and the old feed rate for this cell
     * @return the absoluate value of difference
     */
    double compare_to_old();

    
};

