#include "../../include/basic/point3d.h"
using namespace std;
using namespace Eigen;

wh::basic::Point3d::Point3d():data(0.0,0.0,0.0){}
wh::basic::Point3d::Point3d(double x, double y, double z)
:data(x,y,z){}


ostream& wh::basic::operator<<(ostream& ost, const wh::basic::Point3d point3d)
{
    ost << point3d.data;
    return ost;
}
