#include <iostream>
#include "../../include/utils/io.h"
#include "../../include/basic/point_cloud.h"
using namespace std;
using namespace Eigen;
using namespace wh::basic;
using namespace wh::utils;
int main()
{
    Point_cloud point_cloud;
    cout << "start" << endl;
    load_point_cloud_obj("C:/Users/Administrator/Desktop/trunk_mve_scan_1.obj", &point_cloud);
    //cout << point_cloud << endl;
    cout << point_cloud.size << endl;
    cout << point_cloud.get_geometric_center() << endl;
    cout << "end" << endl;
}