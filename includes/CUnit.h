/**
 * @file CUnit.h
 * @author LIU ZHIYONG
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
    int id;  ///< ID of Unit, the id is range from 0 to num_units -1.

public:
    /// Index of the unit to which this unit’s concentrate stream is connected
    int conc_num;
    /// Index of the unit to which this unit’s concentrate stream is connected
    int tails_num;
    /// A Boolean that is changed to true if the unit has been seen
    bool mark;
    /// the waste rate of concentrate stream in this unit
    double conc_waste_rate;
    /// the valuable material rate of concentrate stream in this unit
    double conc_gor_rate;

    double tails_waste_rate;    ///< the waste rate of tail stream in this unit

    double tails_gor_rate;  ///< the valuable rate of tail stream in this unit

    double feed_gor_rate;   ///< the valuable material rate of feed in this unit

    double feed_waste_rate;  ///< the waste rate of feed in this unit

    double old_feed_rate;   ///< old feed rate in this unit
    /// whether each unit directly access to the concentrate stream
    bool reachConcentrate;
    /// whether each unit directly access to the tailing stream
    bool reachTailings;

    /**
     * @brief This is a function that set the id of unit
     * @param id : an integer argument
     * @return void
     */
    void setId(int id);

    /**
     * @brief Init the feed of unit
     * @return void
     * @details This function is used to initialise the feed of each unit.
     *          The initial feed of unit is set to the value of whole circuit
     *          feed.
     */
    void init();

    /**
     * @brief Calculate the flowrate of each component in concentrate and tailings streams
     * @return void
     * @details use the current guess of the feed flowrates to calculate
     *          the flowrate of each component in both the concentrate and
     *          tailings streams. Each unit will recover 20% of the valuable
     *          material to the concentrate together with 5% of the waste.
     */
    void cal_con_tail();

    /**
     * @brief This function is used to record the current value and reset it
     * @return void
     * @details Store the current value of the feed to this cell as an old feed value
*               and set the current value for all components to zero
     */
    void reset();

    /**
     * @brief This function is used to transfer the concentrate flow
     * @param units : an reference of vector
     * @return void
     * @details Add the concentrate flows to the appropriate unit’s feed
     *          based on the linkages in the circuit vector.
     */
    void transf_con(std::vector<CUnit>& units);

    /**
     * @brief This function is used to transfer the tailing flow
     * @param units an reference of vector
     * @return void
     * @details Add the tailings flows to the appropriate unit’s feed
     *          based on the linkages in the circuit vector.
     */
    void transf_tail(std::vector<CUnit>& units);

    /**
     * @brief This function is used to compare new feed with old feed
     * @return double the absoluate value of difference
     * @details Check the difference between the newly calculated
     *          feed rate and the old feed rate for this cell
     */
    double compare_to_old();
};


