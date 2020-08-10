#include <iostream>
#include <string>
#include <vector>
#include "../../include/utils/string_lib.h"
#include "../../include/basic/point3d.h"
using namespace std;
using namespace Eigen;
using namespace wh::basic;
int main()
{
    Point3d point3d(1,1,1);
    cout << point3d << endl;

    Point3d point3d_1(9.1,3.3,3.0);
    cout << point3d_1 << endl;


    cout << point3d + point3d_1 << endl;
    cout << point3d - point3d_1 << endl;
    cout << point3d_1[1] << endl;
    cout << point3d_1[3] << endl;
}