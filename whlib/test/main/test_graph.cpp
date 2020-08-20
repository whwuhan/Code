#include "../../include/utils/io/io_obj.h"
#include "../../include/basic/point_cloud.h"
#include "../../include/basic/abstract_data_type/graph.h"
using namespace std;
using namespace Eigen;
using namespace wh::basic;
using namespace wh::utils::io;
using namespace wh::basic::adt;
int main()
{
    Point_cloud point_cloud;
    cout << "start" << endl;
    //load_point_cloud_obj("C:/Users/Administrator/Desktop/CSCD/CSCD/trunk_mve_scan_1.obj", &point_cloud);
    auto res = point_cloud.points_to_vector();
    cout << res.size() << endl;
    vector<pair<unsigned int, unsigned int>> vec_pair(1);
    vec_pair[0] = pair<unsigned int, unsigned int>(1,2);
    Graph<Point3d> graph(res,vec_pair);
    auto test = graph.nodes_data_to_matrix();
    //cout << test << endl;
    cout << "end" << endl;
}