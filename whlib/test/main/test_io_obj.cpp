#include <iostream>
#include "../../include/utils/io/io_obj.h"
#include "../../include/basic/point_cloud.h"
using namespace std;
using namespace Eigen;
using namespace wh::basic;
using namespace wh::utils::io;
int main()
{
    Point_cloud point_cloud;
    cout << "start" << endl;
    load_point_cloud_obj("C:/Users/Administrator/Desktop/CSCD/CSCD/trunk_mve_scan_1.obj", &point_cloud);
    auto res = point_cloud.points_to_vector();
    cout << res.size() << endl;
    // for(auto it = res.begin(); it != res.end(); it++)
    // {
    //     cout << it->data << endl;
    // }
    save_point_cloud_obj("C:/Users/Administrator/Desktop/CSCD/CSCD/io_test.obj",&point_cloud);
    cout << "end" << endl;
}