#include <iostream>
#include <basic/cube.h>
#include <utils/io/io_obj.h>
#include <basic/abstract_data_type/octree.h>
#include <algorithm/LOP.h>
using namespace std;
using namespace wh::basic;
using namespace wh::basic::adt;
using namespace wh::utils::io;
using namespace wh::alg;
using namespace Eigen;
int main(){
    Point_cloud point_cloud;
    Eigen::MatrixXd X = Eigen::MatrixXd::Random(1000,3) * 3.5;
    Point_cloud Random(X);
    save_point_cloud_obj("Random.obj",&Random);
    load_point_cloud_obj("/Users/wuhan/wuhan/CodingSpace/LOP/tree1_6678.obj",&point_cloud);
    auto X1 = getXPrime1(Random.points,point_cloud.points);
    Point_cloud tree(X1);
    save_point_cloud_obj("tree1_6678X0.obj",&tree);
    for(int iter=0;iter<20;iter++){
        cout<<"第"<<iter+1<<"次迭代开始"<<endl;
        tree.points = LOP(tree.points,point_cloud.points);
        cout<<"第"<<iter+1<<"次迭代结束"<<endl;
        save_point_cloud_obj(string("tree1_6678X")+to_string(iter+1)+string(".obj"),&tree);
    }
}