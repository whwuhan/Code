#ifndef CARDINAL_H
#define CARDINAL_H
#include <vector>
#include <iostream>
#include <cmath>
namespace wh{
    namespace alg{   
        //==============声明===============
        /**
         * Cardinal样条插值函数
         * points:初始点
         * inter_amount:插入点的数量
         * tightness:松紧系数，越大越直
        */
        template <typename T>
        std::vector<T> cardinal(std::vector<T> points, int inter_amount = 1, double tightness = -0.5);



        //==============算法实现===============
        template <typename T>
        std::vector<T> cardinal(std::vector<T> points, int inter_amount, double tightness){
            if(points.size() != 4){
                std::cout << "wrong points" << std::endl;
                return std::vector<T> (); 
            }
            //Cardinal样条插值
            std::vector<T> res;//返回的结果
            double delta = (1.0 - tightness) / 2.0;//用tightness控制松紧程度
            for(int i = 0; i < inter_amount; i++){
                double u = (i + 1) * 1.0 / (1.0 + inter_amount);
                //计算插入点
                T inter_point= \
                points[0] * ((-delta * std::pow(u,3)) + 2 * delta * std::pow(u,2) - delta * u) +\
                points[1] * ((2 - delta) * std::pow(u,3) + (delta - 3) * std::pow(u,2) + 1) +\
                points[2] * ((delta - 2) * std::pow(u,3) + (3 - 2 * delta) * std::pow(u,2) + delta * u) +\
                points[3] * (delta *  std::pow(u,3) - delta * std::pow(u,3));
                res.push_back(inter_point);
            }
            return res;
        }
    }
}
#endif