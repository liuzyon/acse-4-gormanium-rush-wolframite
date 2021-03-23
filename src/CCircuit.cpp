#include <stdio.h>
#include <iostream>
#include <vector>
#include "CUnit.h"
#include "CCircuit.h"

std::vector<CUnit> units(num_units);

void CUnit::process(double in_gor_rate, double in_waste_rate){
    if(in_gor_rate <= 0 || in_waste_rate <= 0){
        std::cout << "unit process() input should greater than 0" << std::endl;
    }
    conc_gor_rate = in_gor_rate * 0.2;
    conc_waste_rate = in_waste_rate * 0.05;
    
    tails_gor_rate = in_gor_rate - conc_gor_rate;
    tails_waste_rate = in_waste_rate - conc_waste_rate;
    
    conc_purity = conc_gor_rate / (conc_gor_rate + conc_waste_rate);
}

void output_circuit(int *circuit_vector){
    circuit_vector[0] = 0;
    int count = 1;
    for (int i = 0; i < units.size(); i++)
    {
        circuit_vector[count] = units[i].conc_num;
        circuit_vector[++count] = units[i].tails_num;
        count++;
    }
}

bool Check_Validity(int *circuit_vector)
{

  return true;
}

void mark_units(int unit_num) {

  if (units[unit_num].mark) return;

  units[unit_num].mark = true;

  //If we have seen this unit already exit
  //Mark that we have now seen the unit
  //If conc_num does not point at a circuit outlet recursively call the function

  if (units[unit_num].conc_num<num_units) {
    mark_units(units[unit_num].conc_num);
  } else {
    // ...Potentially do something to indicate that you have seen an exit
  }
  //If tails_num does not point at a circuit outlet recursively call the function

  if (units[unit_num].tails_num<num_units) {
    mark_units(units[unit_num].tails_num);
  } else {
    // ...Potentially do something to indicate that you have seen an exit
  }
}

void simulation(int *circuit_vector)
{
    // n个unit：0 到 n-1 标识别unit，n和n+1标识最终精矿流和最终尾矿流
    int circuit_vector[9] = {0, 1, 3, 2, 0, 4, 3, 0, 5};

    std::vector<CUnit> units(unit_size+2);

    // 赋值每个unit id（包括final流单元）
    for (int i = 0; i < units.size(); i++)
    {
        units[i].id = i;
    }

    // 赋值每个unit连接到下两个单元的信息（不包括final两个流）
    for (int i = 0; i < units.size()-2; i++)
    {
        units[i].conc_num = circuit_vector[i*2+1];
        units[i].tails_num = circuit_vector[i*2+2];
    }
    

    //给出给电路中每个单元的两个成分进料速率的初步猜测
    for (int i = 0; i < units.size()-2; i++)
    {
        units[i].feed_gor_rate = 10;
        units[i].feed_waste_rate = 100;
    }

    int iter_num = 0;
    while (iter_num < max_iterations)
    {
        // 对于每个单元，使用当前对进料流速的猜测来计算精矿和尾矿流中每个组分的流速（即根据前面提到的比例）
        for (int i = 0; i < units.size()-2; i++)
        {
            units[i].conc_gor_rate = 0.2 * units[i].feed_gor_rate;
            units[i].conc_waste_rate = 0.05 * units[i].feed_waste_rate;
            units[i].tails_gor_rate = units[i].feed_gor_rate - units[i].conc_gor_rate;
            units[i].tails_waste_rate = units[i].feed_waste_rate - units[i].conc_waste_rate;
        }

        // 对每个单元，将进料的当前值存储起来作为旧进料值，并将所有组分的当前进料值设置为0
        for (int i = 0; i < units.size()-2; i++)
        {
            units[i].old_feed_rate = units[i].feed_gor_rate + units[i].feed_waste_rate;
            units[i].feed_gor_rate = 0;
            units[i].feed_waste_rate = 0;
        }
        //设置final两个流为各组分为0
        for (int i = 0; i < 2; i++)
        {
            units[units.size()-i].feed_gor_rate = 0;
            units[units.size()-i].feed_waste_rate = 0;
        }
    

        // 设置接收环路进料的那个单元的进料等于环路进料的总流速
        units[0].feed_gor_rate = circuit_gor;
        units[0].feed_waste_rate = circuit_waste;

        // 检查每个单元，将其精矿流速和尾矿流速加到合适单元的进料上（基于环路向量中各单元的关系），这也将导致对整个环路的精矿流和尾矿流的最新估计
        for (int i = 0; i < units.size()-2; i++)
        {
            units[units[i].conc_num].feed_gor_rate += units[i].conc_gor_rate;
            units[units[i].conc_num].feed_waste_rate += units[i].conc_waste_rate;
            units[units[i].tails_num].feed_waste_rate += units[i].tails_waste_rate;
            units[units[i].tails_num].feed_gor_rate += units[i].tails_gor_rate;
        }

        // 对每个单元，用新的进料流量和旧的进料流速（之前存的）作比较。如果任何一个单元它的相对变化在给定的设定阈值之上，则重复步骤2。
        for (int i = 0; i < units.size()-2; i++)
        {
            double error = std::fabs((units[i].feed_gor_rate+units[i].feed_waste_rate)-units[i].old_feed_rate);
            if (error > threshold)
            {
                break;   
            }
            
        }

        iter_num++;
    }  
}

