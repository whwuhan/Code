#include "../../include/basic/point_cloud.h"
using namespace std;
using namespace Eigen;
using namespace wh::basic;
//构造函数
Point_cloud::Point_cloud():
points(),size(0){}

Point_cloud::Point_cloud(const unsigned int size, const int point_size):
points(size,point_size),size(size){}

Point_cloud::Point_cloud(const Eigen::MatrixXd& points):
points(points),size(points.rows()){}

//重载运算符
Point_cloud Point_cloud::operator+(const Point_cloud& point_cloud)
{
    //判断维度是否正确
    if(points.rows() != point_cloud.points.rows())
    {   
        cout << "wrong row dimension." << endl;
        return Point_cloud();
    }
    else if(points.cols() != point_cloud.points.cols())
    {
        cout << "wrong col dimension." << endl;
        return Point_cloud();
    }
    return Point_cloud(points + point_cloud.points);
}

Point_cloud Point_cloud::operator-(const Point_cloud& point_cloud)
{
    //判断维度是否正确
    if(points.rows() != point_cloud.points.rows())
    {   
        cout << "wrong row dimension." << endl;
        return Point_cloud();
    }
    else if(points.cols() != point_cloud.points.cols())
    {
        cout << "wrong col dimension." << endl;
        return Point_cloud();
    }
    return Point_cloud(points - point_cloud.points);

}

Point_cloud Point_cloud::operator*(const Eigen::MatrixXd transform_matrix)
{
    //判断维度是否正确
    if(points.cols() != transform_matrix.rows())
    {
        cout << "wrong dimension." << endl;
        return Point_cloud();
    }
    return Point_cloud(points * transform_matrix);
}

Point3d Point_cloud::operator[](const unsigned int index)
{   //判断索引是否正确
    if(index >= size)
    {
        cout << "wrong index." << endl;
        return Point3d();
    }
    return Point3d(points.row(index));
}

//重载友元<<
ostream& wh::basic::operator<<(ostream& ost, const Point_cloud point_cloud)
{
    ost << point_cloud.points;
    return ost;
}

//重新确定维度，注意如果维度改变，里面的数据也可能改变
void Point_cloud::resize(const unsigned int rows, const unsigned int cols)
{
    points.resize(rows, cols);
}

//重新确定维度，且不会改变内部数据(Eigen似乎有bug还是会改变数据)
//如果维度比原有的维度小，那么数据不改变，相当于裁剪矩阵，如果扩张了维度，数据会是随机值
//慎用！！！
void Point_cloud::conservative_resize(const unsigned int rows, const unsigned int cols)
{
        points.conservativeResize(rows, cols);
}
