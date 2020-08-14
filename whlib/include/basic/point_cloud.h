#ifndef POINT_CLOUD_H
#define POINT_CLOUD_H
#include <iostream>
#include "../../deps/eigen-3.3.7/Eigen/Dense"
#include "point3d.h"
namespace wh
{
    namespace basic
    {
        const int POINT3D_SIZE = 3;
        //点云
        typedef struct Point_cloud
        {
            //点云数据
            Eigen::MatrixXd points;
            //点云大小
            unsigned int size;
            
            //构造函数
            Point_cloud();
            Point_cloud(const unsigned int size, const int point_size = POINT3D_SIZE);
            Point_cloud(const Eigen::MatrixXd& points);

            //重载运算符
            Point_cloud operator+(const Point_cloud& point_cloud);
            Point_cloud operator-(const Point_cloud& point_cloud);
            Point_cloud operator*(const Eigen::MatrixXd transform_matrix);
            Point3d operator[](const unsigned int index);
            friend std::ostream& operator<<(std::ostream& ost, const Point_cloud point_cloud);

            //改变维度，注意resize()会改变矩阵内部数据
            void resize(const unsigned int rows, const unsigned int cols);
            //如果维度比原有的维度小，那么数据不改变，相当于裁剪矩阵，如果扩张了维度，数据会是随机值
            void conservative_resize (const unsigned int rows, const unsigned int cols);

            //获取点云几何中心
            Eigen::RowVector3d get_geometric_center();

        } POINT_CLOUD;
        //注意这里要声明友元函数，结构体里面不是声明这个函数，而是告诉说明这个是友元函数
        std::ostream& operator<<(std::ostream& ost, const Point_cloud point_cloud);
    }
}
#endif