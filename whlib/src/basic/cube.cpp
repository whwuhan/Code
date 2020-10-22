#include <basic/cube.h>
using namespace std;
using namespace Eigen;
using namespace wh::basic;

//构造函数
Cube::Cube():position(0.0,0.0,0.0),side_len(0.0),points(){
    cout<<"position:["<<position[0]<<","<<position[1]<<","<<position[2]<<"]"<<endl;
    cout<<"side_len:"<<side_len<<endl;
    cout<<"points"<<points<<endl;
}



Cube::Cube(MatrixXd points):points(points){}

Cube::Cube(RowVector3d position,double side_len):position(position),side_len(side_len){}

Cube::Cube(Eigen::RowVector3d position,double x,double y,double z):position(position),x(x),y(y),z(z){}
//将position side_len转化成顶点表达式
void Cube::position_side_len_to_points(){
    points.resize(8,3);
    points.row(0)=position+RowVector3d(-side_len/2.0,-side_len/2.0,-side_len/2.0);
    points.row(1)=position+RowVector3d(side_len/2.0,-side_len/2.0,-side_len/2.0);
    points.row(2)=position+RowVector3d(side_len/2.0,side_len/2.0,-side_len/2.0);
    points.row(3)=position+RowVector3d(-side_len/2.0,side_len/2.0,-side_len/2.0);
    points.row(4)=position+RowVector3d(-side_len/2.0,side_len/2.0,side_len/2.0);
    points.row(5)=position+RowVector3d(side_len/2.0,side_len/2.0,side_len/2.0);
    points.row(6)=position+RowVector3d(-side_len/2.0,side_len/2.0,side_len/2.0);
    points.row(7)=position+RowVector3d(-side_len/2.0,-side_len/2.0,side_len/2.0);
}

//将position side_len转化成顶点表达式
void Cube::position_side_len_to_points_cuboid(){
    points.resize(8,3);
    points.row(0)=position+RowVector3d(-x/2.0,-y/2.0,-z/2.0);
    points.row(1)=position+RowVector3d(x/2.0,-y/2.0,-z/2.0);
    points.row(2)=position+RowVector3d(x/2.0,y/2.0,-z/2.0);
    points.row(3)=position+RowVector3d(-x/2.0,y/2.0,-z/2.0);
    points.row(4)=position+RowVector3d(-x/2.0,y/2.0,z/2.0);
    points.row(5)=position+RowVector3d(x/2.0,y/2.0,z/2.0);
    points.row(6)=position+RowVector3d(x/2.0,-y/2.0,z/2.0);
    points.row(7)=position+RowVector3d(-x/2.0,-y/2.0,z/2.0);
}





