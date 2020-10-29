#include <iostream>
#include <basic/cube.h>
#include <utils/io/io_obj.h>
using namespace std;
using namespace wh::basic;
using namespace wh::utils::io;
using namespace Eigen;
int main(){
    // Eigen::MatrixXf points(8,3);
    // points.row(0)=Eigen::RowVector3d(0.0f,0.0f,0.0f);
    // points.row(1)=Eigen::RowVector3d(1.0f,0.0f,0.0f);
    // points.row(2)=Eigen::RowVector3d(1.0f,1.0f,0.0f);
    // points.row(3)=Eigen::RowVector3d(0.0f,1.0f,0.0f);
    // points.row(4)=Eigen::RowVector3d(0.0f,1.0f,1.0f);
    // points.row(5)=Eigen::RowVector3d(1.0f,1.0f,1.0f);
    // points.row(6)=Eigen::RowVector3d(1.0f,0.0f,1.0f);
    // points.row(7)=Eigen::RowVector3d(0.0f,0.0f,1.0f);
    // wh::basic::Cube cube(points);

    // wh::utils::io::save_cube_mesh_obj("./test_cube_mesh.obj",&cube);
    // wh::utils::io::save_cube_wireframe_obj("./test_cube_wireframe.obj",&cube);

//----------------------------------

    // Point_cloud pc;
    // load_point_cloud_obj("/Users/wuhan/wuhan/研究生/研一/研一下/CSCD论文/CSCD/CSCD/experimental_data/point_cloud/realdata/obj/tree1_6678.obj",&pc);
    // auto boundingbox=pc.get_boundingbox();

    // Cube boundingbox=pc.get_normalized_point_cloud();
    // save_point_cloud_obj("./tree_nor.obj",&pc);
    // save_cube_wireframe_obj("./boundingbox.obj",&boundingbox);
    // boundingbox.show_inf();



    // Eigen::MatrixXd points(8,3);
    // points.row(0)=Eigen::RowVector3d(0.0f,0.0f,0.0f);
    // points.row(1)=Eigen::RowVector3d(1.0f,0.0f,0.0f);
    // points.row(2)=Eigen::RowVector3d(1.0f,1.0f,0.0f);
    // points.row(3)=Eigen::RowVector3d(0.0f,1.0f,0.0f);
    // points.row(4)=Eigen::RowVector3d(0.0f,1.0f,1.0f);
    // points.row(5)=Eigen::RowVector3d(1.0f,1.0f,1.0f);
    // points.row(6)=Eigen::RowVector3d(1.0f,0.0f,1.0f);
    // points.row(7)=Eigen::RowVector3d(0.0f,0.0f,1.0f);
    // wh::basic::Cube cube(points);
    // cube.show_inf();

    // Cube cube1(RowVector3d(1,1,1),1);
    // Cube cube2(RowVector3d(2,2,2),1);
    // Cube cube3(RowVector3d(3,3,3),1);
    // Cube cube4(RowVector3d(4,4,4),1);
    // Cube cube5(RowVector3d(5,5,5),1);
    // Cube cube6(RowVector3d(6,6,6),1);
    // Cube cube7(RowVector3d(7,7,7),1);
    // Cube cube8(RowVector3d(8,8,8),1);
    // Cube cube9(RowVector3d(9,9,9),1);

    // // cube1.show_inf();

    // vector<Cube> cubes;
    // cubes.push_back(cube1);
    // cubes.push_back(cube2);
    // cubes.push_back(cube3);
    // cubes.push_back(cube4);
    // cubes.push_back(cube5);
    // cubes.push_back(cube6);
    // cubes.push_back(cube7);
    // cubes.push_back(cube8);
    // cubes.push_back(cube9);

    // Eigen::MatrixXd points(8,3);
    // points.row(0)=Eigen::RowVector3d(0.0f,0.0f,0.0f);
    // points.row(1)=Eigen::RowVector3d(1.0f,0.0f,0.0f);
    // points.row(2)=Eigen::RowVector3d(1.0f,1.0f,0.0f);
    // points.row(3)=Eigen::RowVector3d(0.0f,1.0f,0.0f);
    // points.row(4)=Eigen::RowVector3d(0.0f,1.0f,1.0f);
    // points.row(5)=Eigen::RowVector3d(1.0f,1.0f,1.0f);
    // points.row(6)=Eigen::RowVector3d(1.0f,0.0f,1.0f);
    // points.row(7)=Eigen::RowVector3d(0.0f,0.0f,1.0f);
    // wh::basic::Cube cube(RowVector3d(0,0,0),1.0);
    // cube.show_inf();
    // save_cube_mesh_obj("./test_cube_mesh.obj",&cube);
    

    // auto cubes=cube.subdivision(0.3);
    // save_cube_meshes_obj("./test_cube_meshes.obj",cubes);

    vector<string> file_pathes={"Dinosaur.obj","Horse.obj","Couple.obj"};
    for(string file_path:file_pathes){
        //读入点云
        Point_cloud pc;
        load_point_cloud_obj(file_path,&pc);

        //获取boundingbox
        auto boundingbox=pc.get_boundingbox();
        boundingbox.show_inf();
        //体素化
        auto voxel=pc.voxelization(boundingbox,0.05);

        //保存信息
        save_cube_wireframe_obj("boundingbox_"+file_path,&boundingbox);
        //save_cube_wireframes_obj("test_cube_wireframes_all_"+file_path,boundingbox.subdivision(0.1));
        save_tri_cube_meshes_obj("test_cube_meshes_"+file_path,voxel);
        save_cube_wireframes_obj("test_cube_wireframes_"+file_path,voxel);
    }
}