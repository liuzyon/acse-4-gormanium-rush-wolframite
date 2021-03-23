#include <stdio.h>
#include <cmath>
#include <vector>

#include "CUnit.h"
#include "CCircuit.h"
#include "Genetic_Algorithm.h"


// int answer_vector[2*num_units+1] = {0, 1, 2, 3, 4, 4, 5, 6, 7, 7, 8, 8, 9,
//                 10, 11, 10, 11, 10, 11, 10, 11}  ;

double Evaluate_Circuit(int *circuit_vector, double tolerance, int max_iterations) {

  int vector_size = 2*num_units+1;

  // n个unit：0 到 n-1 标识别unit，n和n+1标识最终精矿流和最终尾矿流
  // int circuit_vector[9] = {0, 1, 3, 2, 0, 4, 3, 0, 5};

  //创建各个unit
  std::vector<CUnit> units(num_units);

  // 赋值每个unit id, 以及连接到精矿流和尾矿流的单元id
  for (int i = 0; i < num_units; i++)
  {
      units[i].id = i;
      units[i].conc_num = circuit_vector[i*2+1];
      units[i].tails_num = circuit_vector[i*2+2];
  }
  

  //给出给电路中每个单元的两个成分进料速率的初步猜测
  for (int i = 0; i < num_units; i++)
  {
      units[i].feed_gor_rate = 10;
      units[i].feed_waste_rate = 100;
  }

  int iter_num = 0;
  while (iter_num < max_iterations)
  {
      // 对于每个单元，使用当前对进料流速的猜测来计算精矿和尾矿流中每个组分的流速（即根据前面提到的比例）
      for (int i = 0; i < num_units; i++)
      {
          units[i].conc_gor_rate = 0.2 * units[i].feed_gor_rate;
          units[i].conc_waste_rate = 0.05 * units[i].feed_waste_rate;
          units[i].tails_gor_rate = units[i].feed_gor_rate - units[i].conc_gor_rate;
          units[i].tails_waste_rate = units[i].feed_waste_rate - units[i].conc_waste_rate;
      }

      // 对每个单元，将进料的当前值存储起来作为旧进料值，并将所有组分的当前进料值设置为0
      for (int i = 0; i < num_units; i++)
      {
          units[i].old_feed_rate = units[i].feed_gor_rate + units[i].feed_waste_rate;
          units[i].feed_gor_rate = 0;
          units[i].feed_waste_rate = 0;
      }
  
      // 设置接收环路进料的那个单元的进料等于环路进料的总流速
      units[circuit_vector[0]].feed_gor_rate = circuit_gor;
      units[circuit_vector[0]].feed_waste_rate = circuit_waste;

      // 检查每个单元，将其精矿流速和尾矿流速加到合适单元的进料上（基于环路向量中各单元的关系），这也将导致对整个环路的精矿流和尾矿流的最新估计
      for (int i = 0; i < num_units; i++)
      {
          units[units[i].conc_num].feed_gor_rate += units[i].conc_gor_rate;
          units[units[i].conc_num].feed_waste_rate += units[i].conc_waste_rate;
          units[units[i].tails_num].feed_waste_rate += units[i].tails_waste_rate;
          units[units[i].tails_num].feed_gor_rate += units[i].tails_gor_rate;
      }

      int steady_unit = 0;
      // 对每个单元，用新的进料流量和旧的进料流速（之前存的）作比较。如果任何一个单元它的相对变化在给定的设定阈值之上，则重复步骤2。
      for (int i = 0; i < num_units; i++)
      {
          double error = std::fabs((units[i].feed_gor_rate+units[i].feed_waste_rate)-units[i].old_feed_rate);
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
  
  for (int i = 0; i < num_units; i++) {
      if(units[i].conc_num == concentrate_num){
          Performance += (units[i].conc_gor_rate*100 - units[i].conc_waste_rate*500);
      }
  }
  return Performance;
}
