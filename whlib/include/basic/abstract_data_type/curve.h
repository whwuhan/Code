/**
 * 曲线抽象结构
 * 2020.08.21
 * wuhan
*/
#ifndef CURVE_H
#define CURVE_H
#include <vector>
namespace wh{
    namespace basic{
        namespace adt{
            template <typename T>
            class Curve{
            protected:
                std::vector<T> points;//一条曲线上按顺序排列的点
                unsigned int size;//曲线点的个数
            public:
                Curve();
                Curve(const std::vector<T>& points);

                //获取曲线所有点数据
                std::vector<T>& get_points();
                //获取曲线点的个数
                unsigned int get_size();
                //设置点数量
                void resize(const unsigned int new_size);
                //显示曲线点的信息
                void show();
            };
            
            //构造函数
            template <typename T>
            Curve<T>::Curve():points(),size(0){}

            template <typename T>
            Curve<T>::Curve(const std::vector<T>& points):points(points),size(points.size()){

            }

            //get函数
            template <typename T>
            std::vector<T>& Curve<T>::get_points(){
                return points;
            }

            template <typename T>
            unsigned int Curve<T>::get_size(){
                return size;
            }

            //设置点数量
            template <typename T>
            void Curve<T>::resize(const unsigned int new_size){
                size = new_size;
                points.resize(new_size);
            }
            //显示曲线点的信息
            template <typename T>
            void Curve<T>::show(){
                if(size <= 0){
                    std::cout << "no points data." << std::endl;
                }
                for(auto it = points.cbegin(); it != points.cend(); it++){
                    std::cout << *it << std::endl;
                }
            }
        }
    }
}
#endif