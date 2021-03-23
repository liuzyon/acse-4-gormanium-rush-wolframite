#include <stdio.h>
#include <vector>
#include <cmath>
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

void simulation()
{
    int vector[9] = {};

    int max_iterations = 10;
    double threshold = 1.0e-6;
    double circuit_gor = 10;
    double circuit_waste = 100;
    std::vector<CUnit> units(4);

    //给出给电路中每个单元的两个成分进料速率的初步猜测
    for (int i = 0; i < units.size(); i++)
    {
        units[i].feed_gor_rate = 10;
        units[i].feed_waste_rate = 100;
    }

    int iter_num = 0;
    while (iter_num < max_iterations)
    {
        // 对于每个单元，使用当前对进料流速的猜测来计算精矿和尾矿流中每个组分的流速（即根据前面提到的比例）
        for (int i = 0; i < units.size(); i++)
        {
            units[i].conc_gor_rate = 0.2 * units[i].feed_gor_rate;
            units[i].conc_waste_rate = 0.05 * units[i].feed_waste_rate;
            units[i].tails_gor_rate = units[i].feed_gor_rate - units[i].conc_gor_rate;
            units[i].tails_waste_rate = units[i].feed_waste_rate - units[i].conc_waste_rate;
        }

        // 对每个单元，将进料的当前值存储起来作为旧进料值，并将所有组分的当前进料值设置为0
        for (int i = 0; i < units.size(); i++)
        {
            units[i].old_feed_rate = units[i].feed_gor_rate + units[i].feed_waste_rate;
            units[i].feed_gor_rate = 0;
            units[i].feed_waste_rate = 0;
        }

        // 设置接收环路进料的那个单元的进料等于环路进料的总流速
        units[0].feed_gor_rate = circuit_gor;
        units[0].feed_waste_rate = circuit_waste;

        // 检查每个单元，将其精矿流速和尾矿流速加到合适单元的进料上（基于环路向量中各单元的关系），这也将导致对整个环路的精矿流和尾矿流的最新估计
        for (int i = 0; i < units.size(); i++)
        {
            units[units[i].conc_num].feed_gor_rate += units[i].conc_gor_rate;
            units[units[i].conc_num].feed_waste_rate += units[i].conc_waste_rate;
            units[units[i].tails_num].feed_waste_rate += units[i].tails_waste_rate;
            units[units[i].tails_num].feed_gor_rate += units[i].tails_gor_rate;
        }

        // 对每个单元，用新的进料流量和旧的进料流速（之前存的）作比较。如果任何一个单元它的相对变化在给定的设定阈值之上，则重复步骤2。
        for (int i = 0; i < units.size(); i++)
        {
            double error = std::fabs((units[i].feed_gor_rate+units[i].feed_waste_rate)-units[i].old_feed_rate);
            if (error > threshold)
            {
                continue;   
            }
            
        }

        iter_num++;
    }
    
}