#include <basic/point3d.h>
using namespace std;
using namespace Eigen;
using namespace wh::basic;
//构造函数
Point3d::Point3d():data(0.0,0.0,0.0),x(0.0),y(0.0),z(0.0){}

Point3d::Point3d(double x, double y, double z)
:data(x,y,z),x(x),y(y),z(z){}

Point3d::Point3d(const RowVector3d data)
:data(data),x(data[0]),y(data[1]),z(data[2]){}

//运算符重载
Point3d Point3d::operator+(const Point3d& point){
    return Point3d(point.data + data);
}

Point3d Point3d::operator-(const Point3d& point){
    return Point3d(data - point.data);
}

double Point3d::operator[](int i){
    if( 0 <= i && i <= 2){
        return data[i];
    }
    else{
        cout << "wrong index" << endl; 
        return 0.0;
    }
}

//友元重载<< 注意前面的wh::basic不能省略
ostream& wh::basic::operator<<(ostream& ost, const Point3d point3d){
    ost << point3d.data;
    return ost;
}

//重载*运算符
Point3d wh::basic::operator*(Point3d& point3d, double coefficient){
    return Point3d(point3d.data * coefficient);
}

Point3d wh::basic::operator*(double coefficient, Point3d& point3d){
    return Point3d(point3d.data * coefficient);
}

//重载<
bool wh::basic::Point3d::operator<(const Point3d& point)const{
    if(data[0]<point.data[0]){
        return true;
    }else if(data[0]>point.data[0]){
        return false;
    }

    if(data[1]<point.data[1]){
        return true;
    }else if(data[1]>point.data[1]){
        return false;
    }

    if(data[2]<point.data[2]){
        return true;
    }else if(data[2]>point.data[2]){
        return false;
    }
    return false;
}

bool wh::basic::Point3d::operator==(const Point3d& point)const{
    return data==point.data;
}
//xyz和data同步
void wh::basic::Point3d::syn_xyz_to_data(){
    if(x != data[0] || y != data[1] || z != data[2]){
        data[0] = x;
        data[1] = y;
        data[2] = z;
    }
}

//data和xyz同步
void wh::basic::Point3d::syn_data_to_xyz(){
    if(x != data[0] || y != data[1] || z != data[2]){
        x = data[0];
        y = data[1];
        z = data[2];
    }
}