#include "../../include/basic/point3d.h"
using namespace std;
using namespace Eigen;
using namespace wh::basic;
//构造函数
Point3d::Point3d():data(0.0,0.0,0.0),x(0.0),y(0.0),z(0.0){}

Point3d::Point3d(double x, double y, double z)
:data(x,y,z),x(x),y(y),z(z){}

Point3d::Point3d(const Vector3d data)
:data(data),x(data[0]),y(data[1]),z(data[2]){}

//运算符重载
Point3d wh::basic::Point3d::operator+(const Point3d& point)
{
    return Point3d(point.data + data);
}

Point3d wh::basic::Point3d::operator-(const Point3d& point)
{
    return Point3d(point.data - data);
}

double wh::basic::Point3d::operator[](int i)
{
    if( 0 <= i && i <= 2)
    {
        return data[i];
    }
    else
    {
        cout << "wrong index" << endl; 
        return 0.0;
    }
}






ostream& wh::basic::operator<<(ostream& ost, const Point3d point3d)
{
    ost << point3d.x << " " << point3d.y << " " << point3d.z << endl;    
    return ost;
}
