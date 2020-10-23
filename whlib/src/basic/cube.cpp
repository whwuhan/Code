#include <basic/cube.h>
using namespace std;
using namespace Eigen;
using namespace wh::basic;

//构造函数
Cube::Cube():position(0.0,0.0,0.0),side_len(0.0),points(),x(0.0),y(0.0),z(0.0){}

Cube::Cube(MatrixXd points):points(points){
    RowVector3d center = points.colwise().sum();//colwise()按照矩阵每一列的方向上排列 这里相当于每一行相加
    position = center / points.rows();

    RowVector3d temp = points.row(1) - points.row(0);
    x=sqrt(temp.dot(temp));

    temp = points.row(3) - points.row(0);
    y=sqrt(temp.dot(temp));

    temp = points.row(7) - points.row(0);
    z=sqrt(temp.dot(temp));

    if( (x-y<0.00000001) && (y-z<0.00000001) ){
        side_len = x;
    }
}

Cube::Cube(RowVector3d position,double side_len):position(position),side_len(side_len){
    double half_size = side_len / 2.0;
    points.resize(8,3);

    points.row(0)=RowVector3d(position[0]-half_size,position[1]-half_size,position[2]-half_size);
    points.row(1)=RowVector3d(position[0]+half_size,position[1]-half_size,position[2]-half_size);
    points.row(2)=RowVector3d(position[0]+half_size,position[1]+half_size,position[2]-half_size);
    points.row(3)=RowVector3d(position[0]-half_size,position[1]+half_size,position[2]-half_size);
    points.row(4)=RowVector3d(position[0]-half_size,position[1]+half_size,position[2]+half_size);
    points.row(5)=RowVector3d(position[0]+half_size,position[1]+half_size,position[2]+half_size);
    points.row(6)=RowVector3d(position[0]+half_size,position[1]-half_size,position[2]+half_size);
    points.row(7)=RowVector3d(position[0]-half_size,position[1]-half_size,position[2]+half_size);
    // position_side_len_to_points();

    x=side_len;
    y=side_len;
    z=side_len;
}

Cube::Cube(Eigen::RowVector3d position,double x,double y,double z):position(position),x(x),y(y),z(z){
    side_len=0.0;
    position_side_len_to_points_cuboid();
}


//运算符重载
bool Cube::operator<(const Cube& cube)const{
    if(position[0]<cube.position[0]) return true;
    if(position[1]<cube.position[1]) return true;
    if(position[2]<cube.position[2]) return true;
    return false;
}

//显示信息
void Cube::show_inf(){
    cout<<"position:"<<position<<endl;
    cout<<"side_len:"<<side_len<<endl;
    cout<<"x:"<<x<<" y:"<<y<<" z:"<<z<<endl;
}

//显示信息
void Cube::show_inf()const{
    cout<<"position:"<<position<<endl;
    cout<<"side_len:"<<side_len<<endl;
    cout<<"x:"<<x<<" y:"<<y<<" z:"<<z<<endl;
}
//将position side_len转化成顶点表达式
void Cube::position_side_len_to_points(){
    points.resize(8,3);
    double half_size=side_len/2.0;
    points.row(0)=RowVector3d(position[0]-half_size,position[1]-half_size,position[2]-half_size);
    points.row(1)=RowVector3d(position[0]+half_size,position[1]-half_size,position[2]-half_size);
    points.row(2)=RowVector3d(position[0]+half_size,position[1]+half_size,position[2]-half_size);
    points.row(3)=RowVector3d(position[0]-half_size,position[1]+half_size,position[2]-half_size);
    points.row(4)=RowVector3d(position[0]-half_size,position[1]+half_size,position[2]+half_size);
    points.row(5)=RowVector3d(position[0]+half_size,position[1]+half_size,position[2]+half_size);
    points.row(6)=RowVector3d(position[0]+half_size,position[1]-half_size,position[2]+half_size);
    points.row(7)=RowVector3d(position[0]-half_size,position[1]-half_size,position[2]+half_size);
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

//细分
//TODO
//参数：细分的总个数
vector<Cube> Cube::subdivision(int amount){
    vector<Cube> res;
    return res;
}

//细分
//细分的立方体边长
vector<Cube> Cube::subdivision(double leaf_size){
    vector<Cube> res;
    if(x<=leaf_size || y<=leaf_size || z<=leaf_size) return res;

    //获取xyz方向细分的个数
    int x_amount = x / leaf_size;
    int y_amount = y / leaf_size;
    int z_amount = z / leaf_size;

    if(x_amount < x/leaf_size) x_amount++;
    if(y_amount < y/leaf_size) y_amount++;
    if(z_amount < z/leaf_size) z_amount++;

    double half_size = leaf_size / 2.0;

    //计算细分后的正方体
    for(int i=0;i<x_amount;i++){
        for(int j=0;j<y_amount;j++){
            for(int k=0;k<z_amount;k++){
                RowVector3d pos((2*i+1)*half_size,(2*j+1)*half_size,(2*k+1)*half_size);
                pos += points.row(0);
                res.push_back(Cube(pos,leaf_size));
            }
        }
    }
    
    return res;
}

