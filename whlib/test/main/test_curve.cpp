#include <iostream>
#include <vector>
#include "../../include/basic/abstract_data_type/curve.h"
#include "../../include/basic/point3d.h"
#include "../../include/utils/io/io_skel.h"
#include "../../include/utils/io/io_obj.h"
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
    vector< Curve<Point3d> >vec_1; 
    vector< Curve<Point3d> >vec_2; 
    vector< Curve<Point3d> >vec_3; 
    load_curves_skel("C:/Users/Administrator/Desktop/CSCD/CSCD/experimental_data/trunk_mve_scan_1.skel",&vec_1);
    load_curves_skel("C:/Users/Administrator/Desktop/CSCD/CSCD/experimental_data/trunk_mve_scan_2.skel",&vec_2);
    load_curves_skel("C:/Users/Administrator/Desktop/CSCD/CSCD/experimental_data/trunk_mve_scan_3.skel",&vec_3);
    // for(auto it = vec.begin(); it != vec.end(); it++)
    // {
    //     std::cout << "curve:";
    //     it->show();
    // }
    save_curves_obj("C:/Users/Administrator/Desktop/CSCD/CSCD/experimental_data/trunk_mve_scan_skel_1.obj",&vec_1);
    save_curves_obj("C:/Users/Administrator/Desktop/CSCD/CSCD/experimental_data/trunk_mve_scan_skel_2.obj",&vec_2);
    save_curves_obj("C:/Users/Administrator/Desktop/CSCD/CSCD/experimental_data/trunk_mve_scan_skel_3.obj",&vec_3);

}