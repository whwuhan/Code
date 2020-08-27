#ifndef CARDINAL_H
#define CARDINAL_H
#include <vector>
#include <iostream>
namespace wh
{
    namespace alg
    {
        /**
         * Cardinal样条插值函数
         * points:初始点
         * inter_amount:插入点的数量
         * tightness:松紧系数，越大越直
        */
        template <typename T>
        std::vector<T> cardinal(std::vector<T> points, int inter_amount = 1, float tightness = -0.5);


        template <typename T>
        std::vector<T> cardinal(std::vector<T> points, int inter_amount, float tightness)
        {
            if(points.size() != 4)
            {
                std::cout << "wrong points" << std::endl;
                return std::vector<T> (); 
            }
        }
    }
}
#endif