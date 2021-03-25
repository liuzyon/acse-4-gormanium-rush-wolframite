#include <stdio.h>
#include <cmath>
#include <vector>

#include "CUnit.h"
#include "CCircuit.h"
#include "Genetic_Algorithm.h"


double Evaluate_Circuit(int *circuit_vector, int num_units, double tolerance, int max_iterations) {

    //创建各个unit
    std::vector<CUnit> units(num_units);

    // 赋值每个unit id, 以及连接到精矿流和尾矿流的单元id
    for (int i = 0; i < num_units; i++)
    {
        units[i].setId(i);
        units[i].conc_num = circuit_vector[i*2+1];
        units[i].tails_num = circuit_vector[i*2+2];
    }

    //给出给电路中每个单元的两个成分进料速率的初步猜测
    for (int i = 0; i < num_units; i++)
    {
        units[i].init();
    }

    int iter_num = 0;
    int steady_unit = 0;
    while (iter_num < max_iterations)
    {
        // 对于每个单元，使用当前对进料流速的猜测来计算精矿和尾矿流中每个组分的流速（即根据前面提到的比例）这里可以写成成员方法
        for (int i = 0; i < num_units; i++)
        {
            units[i].cal_con_tail();
        }

        // 对每个单元，将进料的当前值存储起来作为旧进料值，并将所有组分的当前进料值设置为0 这里可以写作成员方法
        for (int i = 0; i < num_units; i++)
        {
            units[i].reset();
        }
    
        // 设置接收环路进料的那个单元的进料等于环路进料的总流速
        units[circuit_vector[0]].init();

        // 检查每个单元，将其精矿流速和尾矿流速加到合适单元的进料上（基于环路向量中各单元的关系），这也将导致对整个环路的精矿流和尾矿流的最新估计
        for (int i = 0; i < num_units; i++)
        {
            if (units[i].conc_num < num_units)
            {
                units[i].transf_con(units);
            }

            if (units[i].tails_num < num_units)
            {
                units[i].transf_tail(units);
            }
        }

        steady_unit = 0;
        // 对每个单元，用新的进料流量和旧的进料流速（之前存的）作比较。如果任何一个单元它的相对变化在给定的设定阈值之上，则重复步骤2。 比较可以写作成员方法
        for (int i = 0; i < num_units; i++)
        {
            double error = units[i].compare_to_old();
            if (error <= tolerance)
            {
                steady_unit++;
            }
        }

        if (steady_unit == num_units) break;
        iter_num++;
    }  

    int concentrate_num = num_units;
    double Performance = 0.0;

    if (steady_unit == num_units){
        for (int i = 0; i < num_units; i++) {
            if(units[i].conc_num == concentrate_num){
                Performance += (units[i].conc_gor_rate*100 - units[i].conc_waste_rate*500);
            }
        }
    }else{
        Performance = - circuit_waste*500;
    }
  
    return Performance;
}
