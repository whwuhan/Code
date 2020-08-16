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
    save_point_cloud_obj("C:/Users/Administrator/Desktop/CSCD/CSCD/io_test.obj",&point_cloud);
    cout << "end" << endl;
}