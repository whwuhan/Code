#include <basic/polygon_mesh.h>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <basic/edge.h>
#include <basic/point3d.h>
#include <basic/face.h>
using namespace std;
using namespace wh::basic;
using namespace Eigen;
bool is_exist(const unsigned int i,const RowVector3i& vec);//判断vec中是否存在i
//构造函数
wh::basic::Polygon_mesh::Polygon_mesh():vertices(),faces(){

}

wh::basic::Polygon_mesh::Polygon_mesh(Eigen::MatrixXd& vertices,Eigen::MatrixXi& faces):vertices(vertices),faces(faces){

}

set<Edge> Polygon_mesh::creat_unordered_edges(){
    set<Edge> res;
    for(int i=0;i<faces.rows();i++){
        res.insert(Edge(faces(i,0),faces(i,1)));
        res.insert(Edge(faces(i,1),faces(i,2)));
        res.insert(Edge(faces(i,2),faces(i,0)));
    }
    return res;
}

std::set<wh::basic::Edge> Polygon_mesh::creat_ordered_edges(){
    set<Edge> res;
    for(int i=0;i<faces.rows();i++){
        res.insert(Edge(faces(i,0),faces(i,1),false));
        res.insert(Edge(faces(i,1),faces(i,2),false));
        res.insert(Edge(faces(i,2),faces(i,0),false));
    }
    return res;
}

//普通三角细分
void wh::basic::Polygon_mesh::tri_mesh_subdivision(){
    //subdivision非三角面片不能细分
    if(faces.cols()!=3){
        cout<<"subdivision can not subdivide non-triangular mesh!"<<endl;
        return;
    }

    //生成无序边集 
    set<Edge> unordered_edges=creat_unordered_edges();
    int rows=vertices.rows();
    //cout<<"edges.size:"<<edges.size()<<endl;
    //vertices.conservativeResize(rows+unordered_edges.size(),3);//直接用resize会调用析构函数，里面的数据会消失
    //细分面片
    MatrixXd new_vertices(rows+unordered_edges.size(),3);//细分后的顶点
    MatrixXi new_faces(faces.rows()*4,3);//细分后的面片
    //set<Point3d> points;
    map<Point3d,unsigned int> new_vertices_index;
    int vertex_index=0;
    for(int i=0;i<faces.rows();i++){
        vector<Point3d> cur_points;//记录当前面片顶点
        for(int j=0;j<3;j++){
            //存放原有的顶点
            Point3d point(vertices.row( faces(i,j)-1 ));
            cur_points.push_back(point);
            if(new_vertices_index.count(point) == 0 ){
                //cout<<"point:"<<point<<endl;
                //如果没有保存当前顶点(防止重复存储)
                new_vertices.row(vertex_index++)=vertices.row( faces(i,j)-1 );//这个下标从0开始
                new_vertices_index[point]=vertex_index;//注意这个下标从1开始
            }
        }

        //新增顶点
        Point3d new_point_1( (vertices.row( faces(i,0)-1 ) + vertices.row( faces(i,1)-1 )) / 2.0 );
        if(new_vertices_index.count( new_point_1 ) == 0){
            new_vertices.row(vertex_index++)=new_point_1.data;//这个下标从0开始
            new_vertices_index[new_point_1]=vertex_index;//注意这个下标从1开始
        }
        cur_points.push_back(new_point_1);

        Point3d new_point_2( (vertices.row( faces(i,1)-1 ) + vertices.row( faces(i,2)-1 )) / 2.0 );
        if(new_vertices_index.count( new_point_2 ) == 0){
            new_vertices.row(vertex_index++)=new_point_2.data;//这个下标从0开始
            new_vertices_index[new_point_2]=vertex_index;//注意这个下标从1开始
        }
        cur_points.push_back(new_point_2);

        Point3d new_point_3( (vertices.row( faces(i,2)-1 ) + vertices.row( faces(i,0)-1 )) / 2.0 );
        if(new_vertices_index.count( new_point_3 ) == 0){
            new_vertices.row(vertex_index++)=new_point_3.data;//这个下标从0开始
            new_vertices_index[new_point_3]=vertex_index;//注意这个下标从1开始
        }
        cur_points.push_back(new_point_3);
        
        //生成细分的面片
        //第一个细分面片
        new_faces(4*i,0)=new_vertices_index[cur_points[0]];
        new_faces(4*i,1)=new_vertices_index[cur_points[3]];
        new_faces(4*i,2)=new_vertices_index[cur_points[5]];
        //第二个细分面片
        new_faces(4*i+1,0)=new_vertices_index[cur_points[1]];
        new_faces(4*i+1,1)=new_vertices_index[cur_points[3]];
        new_faces(4*i+1,2)=new_vertices_index[cur_points[4]];
        //第三个细分面片
        new_faces(4*i+2,0)=new_vertices_index[cur_points[2]];
        new_faces(4*i+2,1)=new_vertices_index[cur_points[4]];
        new_faces(4*i+2,2)=new_vertices_index[cur_points[5]];
        //第四个细分面片
        new_faces(4*i+3,0)=new_vertices_index[cur_points[3]];
        new_faces(4*i+3,1)=new_vertices_index[cur_points[4]];
        new_faces(4*i+3,2)=new_vertices_index[cur_points[5]];

    }
    
    // cout<<"new_vertices: \n"<<new_vertices<<endl;
    // cout<<"new_vertices_index:\n";
    // for(auto iter=new_vertices_index.begin();iter!=new_vertices_index.end();iter++){
    //     cout<<iter->second<<endl;
    // }
    //块操作
    //new_vertices.block(0,0,rows,3)=vertices;
    // cout<<"vertices:"<<vertices<<endl;
    // cout<<"new_vertices:"<<new_vertices<<endl;

    //生成odd vertices 注意下标
    // for(auto iter=unordered_edges.begin();iter!=unordered_edges.end();iter++){
    //     vertices.row(rows++)=(vertices.row(iter->fir_ver_index-1)+vertices.row(iter->sec_ver_index-1))/2.0;
    // }

    

    //顶点构建邻居数据结构
    // map<int,set<int> > neighbors;
    // for(int i=0;i<faces.rows();i++){
    //     for(int j=0;j<3;j++){
    //         for(int k=0;k<3;k++){
    //             if(j!=k){
    //                 neighbors[faces(i,j)].insert(faces(i,k));
    //             }
    //         }
    //     }
    // }

    //将新的vertices和faces赋值给mesh
    vertices=new_vertices;
    faces=new_faces;

    // for(auto iter_map=neighbors.begin();iter_map!=neighbors.end();iter_map++){
    //     for(auto iter_set=iter_map->second.begin();iter_set!=iter_map->second.end();iter_set++){
    //         cout<<*iter_set;
    //     }
    //     cout<<endl;
    // }

    // cout<<"vertices:"<<endl;
    // cout<<vertices<<endl;
}

//loop细分
void wh::basic::Polygon_mesh::loop_subdivision(){
    //subdivision非三角面片不能细分
    if(faces.cols()!=3){
        cout<<"loop subdivision can not subdivide non-triangular mesh!"<<endl;
        return;
    }
    //找到边集（无序边默认第一个索引比第二个小）
    set<Edge> unordered_edges=creat_unordered_edges();

}

//找到边的相邻面片
std::map<wh::basic::Edge,std::set<wh::basic::Face> > 
wh::basic::Polygon_mesh::find_edge_near_faces(std::set<wh::basic::Edge>& edges){
    map<Edge,set<Face> > res;//结果
    for(auto iter=edges.begin();iter!=edges.end();iter++){
        for(int i=0;i<faces.rows();i++){
            if(is_exist(iter->fir_ver_index,faces.row(i)) && is_exist(iter->sec_ver_index,faces.row(i))){
                res[*iter].insert(Face(faces.row(i)));
            }
        }
    }
    return res;
}

//判断vec中是否存在i
bool is_exist(const unsigned int i,const RowVector3i& vec){
    if(i==vec[0]||i==vec[1]||i==vec[2]){
        return true;
    }
    return false;
}