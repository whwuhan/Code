#include <basic/point_cloud.h>
using namespace std;
using namespace Eigen;
using namespace wh::basic;
//构造函数
Point_cloud::Point_cloud():
points(),size(0){}

Point_cloud::Point_cloud(const unsigned int size, const int point_size):
points(size,point_size),size(size){}

Point_cloud::Point_cloud(const Eigen::MatrixXd& points):
points(points),size(points.rows()){}

//重载运算符
Point_cloud Point_cloud::operator+(const Point_cloud& point_cloud){
    //判断维度是否正确
    if(points.rows() != point_cloud.points.rows()){   
        cout << "wrong row dimension." << endl;
        return Point_cloud();
    }
    else if(points.cols() != point_cloud.points.cols()){
        cout << "wrong col dimension." << endl;
        return Point_cloud();
    }
    return Point_cloud(points + point_cloud.points);
}

Point_cloud Point_cloud::operator-(const Point_cloud& point_cloud){
    //判断维度是否正确
    if(points.rows() != point_cloud.points.rows()){   
        cout << "wrong row dimension." << endl;
        return Point_cloud();
    }
    else if(points.cols() != point_cloud.points.cols()){
        cout << "wrong col dimension." << endl;
        return Point_cloud();
    }
    return Point_cloud(points - point_cloud.points);

}

Point_cloud Point_cloud::operator*(const Eigen::MatrixXd transform_matrix){
    //判断维度是否正确
    if(points.cols() != transform_matrix.rows()){
        cout << "wrong dimension." << endl;
        return Point_cloud();
    }
    return Point_cloud(points * transform_matrix);
}

Point3d Point_cloud::operator[](const unsigned int index){   //判断索引是否正确
    if(index >= size){
        cout << "wrong index." << endl;
        return Point3d();
    }
    return Point3d(points.row(index));
}

//重载友元<<
ostream& wh::basic::operator<<(ostream& ost, const Point_cloud point_cloud){
    ost << point_cloud.points;
    return ost;
}

//重新确定维度，注意如果维度改变，里面的数据也可能改变
void Point_cloud::resize(const unsigned int rows, const unsigned int cols){   
    size = rows;
    points.resize(rows, cols);
}

//重新确定维度，且不会改变内部数据(Eigen似乎有bug还是会改变数据)
//如果维度比原有的维度小，那么数据不改变，相当于裁剪矩阵，如果扩张了维度，数据会是随机值
//慎用！！！
void Point_cloud::conservative_resize(const unsigned int rows, const unsigned int cols){   
    size = rows;
    points.conservativeResize(rows, cols);
}

//获取点云几何中心
RowVector3d Point_cloud::get_geometric_center(){
    RowVector3d center = points.colwise().sum();//colwise()按照矩阵每一列的方向上排列 这里相当于每一行相加
    return center / size;
}

//将点云放回原点
void Point_cloud::get_centered_point_cloud(){   
    //获取点云几何中心
    RowVector3d center = get_geometric_center();
    //将点云数据放回坐标原点
    for(int i = 0; i < size; i++){
        points.row(i) = points.row(i) - center;
    }
}

//归一化点云
Cube Point_cloud::get_normalized_point_cloud(){
    RowVector3d max_xyz = points.colwise().maxCoeff();//xyz坐标的最大值
    RowVector3d min_xyz = points.colwise().minCoeff();//xyz坐标的最小值

    //包围盒中心
    RowVector3d boundingbox_center = (max_xyz + min_xyz) / 2.0;
    //将点云中心放置到坐标原点
    for(int i = 0; i < size; i++){
        points.row(i) = points.row(i) - boundingbox_center;
    }

    //boundingbox的xyz轴上的边长
    RowVector3d boundingbox_side_length = max_xyz - min_xyz;

    //获取最长边长
    double max_side_length = boundingbox_side_length.maxCoeff();

    //缩放大小
    double scale = max_side_length / 2.0;

    //将坐标归一化到[-1,1]
    for(int i = 0; i < size; i++){
        points.row(i) = points.row(i) / scale;
    }

    boundingbox_side_length=boundingbox_side_length / scale;//同时缩放boudingbox的大小（归一化boundingbox）
    Cube boundingbox(RowVector3d(0.0,0.0,0.0),boundingbox_side_length[0],boundingbox_side_length[1],boundingbox_side_length[2]);
    boundingbox.position_side_len_to_vertices_cuboid();//将位置边长表达形式表示成顶点形式
    return boundingbox;
}

//点云转化为vector存储
vector<Point3d> Point_cloud::points_to_vector(){
    vector<Point3d> res(size);
    for(int i = 0; i < size; i++){
        res[i] = Point3d(points.row(i));
    }
    return res;
}

//获取boundingbox
Cube Point_cloud::get_boundingbox(){
    RowVector3d max_xyz = points.colwise().maxCoeff();//xyz坐标的最大值
    RowVector3d min_xyz = points.colwise().minCoeff();//xyz坐标的最小值

    //包围盒中心
    RowVector3d boundingbox_center = (max_xyz + min_xyz) / 2.0;
    //boundingbox的xyz轴上的边长
    RowVector3d boundingbox_side_length = max_xyz - min_xyz;

    Cube boundingbox(boundingbox_center,boundingbox_side_length[0],boundingbox_side_length[1],boundingbox_side_length[2]);
    return boundingbox;
}

//体素化点云
set<Cube> Point_cloud::voxelization(wh::basic::Cube& boundingbox,double leaf_size){
    set<Cube> res;
    //先细分boundingbox，
    vector<Cube> voxel=boundingbox.subdivision(leaf_size);

    //获取xyz方向细分的个数
    int x_amount = boundingbox.x / leaf_size;
    int y_amount = boundingbox.y / leaf_size;
    int z_amount = boundingbox.z / leaf_size;

    // 边界位置增加一个cube
    // x_amount++;
    // y_amount++;
    // z_amount++;

    // 边界位置不增加cube，即一个点恰好在boundingbox的一个面上，不在增加细分cube的个数
    if(x_amount < boundingbox.x/leaf_size) x_amount++;
    if(y_amount < boundingbox.y/leaf_size) y_amount++;
    if(z_amount < boundingbox.z/leaf_size) z_amount++;
    
    //原点
    RowVector3d origin = boundingbox.vertices.row(0);
    //体素的位置
    int x_index=0;
    int y_index=0;
    int z_index=0;

    for(int i=0;i<points.rows();i++){
        RowVector3d index=(points.row(i)-origin)/leaf_size;//获取体素位置
        x_index=index[0];
        y_index=index[1];
        z_index=index[2];
        //计算体素在vector中的位置
        //边界位置处理（恰好在boundingbox的一个面上）
        if(x_index==x_amount) x_index--;
        if(y_index==y_amount) y_index--;
        if(z_index==z_amount) z_index--;
        int vox_index = x_index * y_amount * z_amount + y_index * z_amount + z_index;

        // index越界检验
        // if(voxel[vox_index].vertices.rows()!=8){
        //     cout<<"index[0]:"<<index[0]<<endl;
        //     cout<<"index[1]:"<<index[1]<<endl;
        //     cout<<"index[2]:"<<index[2]<<endl;
        //     cout<<"x_amount:"<<x_amount<<" y_amount:"<<y_amount<<" z_amount:"<<z_amount<<endl;
        //     cout<<"x_index:"<<x_index<<" y_index:"<<y_index<<" z_index:"<<z_index<<endl;
        //     cout<<"index wrong:"<<vox_index<<endl;
        // }
        
        res.insert(voxel[vox_index]);
    }
    return res;
}