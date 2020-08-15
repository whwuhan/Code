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
    load_point_cloud_obj("C:/Users/Administrator/Desktop/CSCD/CSCD/trunk_mve_scan_1.obj", &point_cloud);
    // cout << point_cloud << endl;
    // cout << point_cloud.size << endl;
    // cout << point_cloud.get_geometric_center() << endl;
    //point_cloud.get_centered_point_cloud();
    cout << "begin:" << point_cloud.get_geometric_center() << endl;
    point_cloud.get_normalized_point_cloud();
    cout << "end:" << point_cloud.get_geometric_center() << endl;
    //cout << point_cloud << endl;
    cout << "end" << endl;
}