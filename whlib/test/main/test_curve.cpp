#include <iostream>
#include <vector>
#include "../../include/basic/abstract_data_type/curve.h"
#include "../../include/basic/point3d.h"
#include "../../include/utils/io/io_skel.h"
using namespace std;
using namespace wh::basic;
using namespace wh::utils::io;
using namespace wh::basic::adt;
int main()
{
    //vector<Point3d> points(10);
    // Curve<Point3d> curve;
    // vector<Point3d>& res = curve.get_points();
    // auto size = curve.get_size();
    // res[0].data[0] = 99;
    // res[0].data[1] = 99;
    // res[0].data[2] = 99;

    //cout << size << endl;
    //curve.show();
    vector< Curve<Point3d> >vec; 
    load_curves_skel("C:/Users/Administrator/Desktop/CSCD/CSCD/experimental_data/trunk_mve_scan_1.skel",&vec);
    cout << vec.size() << endl;
    for(auto it = vec.begin(); it != vec.end(); it++)
    {
        std::cout << "curve:";
        it->show();
    }
}