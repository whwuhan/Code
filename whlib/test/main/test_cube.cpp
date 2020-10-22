#include <iostream>
#include <basic/cube.h>
#include <utils/io/io_obj.h>
using namespace std;
using namespace wh::basic;
using namespace wh::utils::io;
int main(){
    // Eigen::MatrixXf points(8,3);
    // points.row(0)=Eigen::RowVector3f(0.0f,0.0f,0.0f);
    // points.row(1)=Eigen::RowVector3f(1.0f,0.0f,0.0f);
    // points.row(2)=Eigen::RowVector3f(1.0f,1.0f,0.0f);
    // points.row(3)=Eigen::RowVector3f(0.0f,1.0f,0.0f);
    // points.row(4)=Eigen::RowVector3f(0.0f,1.0f,1.0f);
    // points.row(5)=Eigen::RowVector3f(1.0f,1.0f,1.0f);
    // points.row(6)=Eigen::RowVector3f(1.0f,0.0f,1.0f);
    // points.row(7)=Eigen::RowVector3f(0.0f,0.0f,1.0f);
    // wh::basic::Cube cube(points);

    // wh::utils::io::save_cube_mesh_obj("./test_cube_mesh.obj",&cube);
    // wh::utils::io::save_cube_wireframe_obj("./test_cube_wireframe.obj",&cube);

    // Cube test_cube;
    Point_cloud pc;
    load_point_cloud_obj("/Users/wuhan/wuhan/研究生/研一/研一下/CSCD论文/CSCD/CSCD/experimental_data/point_cloud/realdata/obj/tree1_6678.obj",&pc);

    Cube bounding_box=pc.get_normalized_point_cloud();
    save_point_cloud_obj("./tree_nor.obj",&pc);
    save_cube_wireframe_obj("./boundingbox.obj",&bounding_box);

}