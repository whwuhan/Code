#ifndef CUBE_H
#define CUBE_H
#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include <basic/point3d.h>
namespace wh{
    namespace basic{
        typedef struct Cube{
            Eigen::MatrixXd points;//正方形顶点
            Eigen::RowVector3d position;//立方体的位置(中心位置)
            double side_len;//边长
            double x;
            double y;
            double z;

            //构造函数
            Cube();                                                 //默认构造函数
            Cube(Eigen::MatrixXd points);                           //8个顶点描述cube
            Cube(Eigen::RowVector3d position,double side_len);      //使用中心位置和边长描述cube
            Cube(Eigen::RowVector3d position,double x,double y,double z);//使用中心位置和边长描述cuboid
            void position_side_len_to_points();//位置边长表示转化成顶点表示
            void position_side_len_to_points_cuboid();//位置边长表示转化成顶点表示

        } CUBE;
    }
}
#endif