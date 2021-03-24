//
// Created by Zhiyong Liu on 2021/3/24.
//
#include "CUnit.h"

void CUnit::setId(int id)
{
    CUnit::id = id;
}

void CUnit::init()
{
    feed_gor_rate = circuit_gor;
    feed_waste_rate = circuit_waste;
}

void CUnit::cal_con_tail()
{
    conc_gor_rate = 0.2 * feed_gor_rate;
    conc_waste_rate = 0.05 * feed_waste_rate;
    tails_gor_rate = feed_gor_rate - conc_gor_rate;
    tails_waste_rate = feed_waste_rate - conc_waste_rate;
}

void CUnit::reset()
{
    old_feed_rate = feed_gor_rate + feed_waste_rate;
    feed_gor_rate = 0;
    feed_waste_rate = 0;
}

void CUnit::transf_con(std::vector<CUnit> &units)
{
    units[this->conc_num].feed_gor_rate += conc_gor_rate;
    units[this->conc_num].feed_waste_rate += conc_waste_rate;
}

void CUnit::transf_tail(std::vector<CUnit> &units)
{
    units[this->tails_num].feed_waste_rate += tails_waste_rate;
    units[this->tails_num].feed_gor_rate += tails_gor_rate;
}

double CUnit::compare_to_old()
{
    return std::fabs((feed_gor_rate + feed_waste_rate) - old_feed_rate);
}