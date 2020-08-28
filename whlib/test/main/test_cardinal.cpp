#include <iostream>
#include <string>
#include <vector>
#include "../../include/algorithm/cardinal.h"
#include "../../include/basic/point3d.h"
#include "../../include/basic/point_cloud.h"
#include "../../include/utils/io/io_obj.h"
using namespace std;
using namespace Eigen;
using namespace wh::basic;
int main()
{   
    Point3d p1(0,0,0);
    Point3d p2(1,1,0);
    Point3d p3(4,1,0);
    Point3d p4(3,0,0);
    vector<Point3d> points = {p1,p2,p3,p4};
    auto res = wh::alg::cardinal(points,10,-2.5);
    for(auto iter = res.cbegin(); iter != res.cend(); iter++)
    {
        cout << *iter << endl;
    }
    MatrixXd point_cloud_data(res.size(),3);
    for(int i = 0; i < point_cloud_data.rows(); i++)
    {
        point_cloud_data.row(i) = res[i].data;
    }
    Point_cloud point_cloud(point_cloud_data);
    wh::utils::io::save_point_cloud_obj("cardinal_test.obj",&point_cloud);
}