#ifndef POLYGON_MESH_H
#define POLYGON_MESH_H
#include <Eigen/Dense>
#include <basic/edge.h>
#include <basic/face.h>
#include <set>
#include <map>
namespace wh{
    namespace basic{
        typedef struct Polygon_mesh{
            Eigen::MatrixXd vertices;//多边型顶点
            Eigen::MatrixXi faces;//多边形面片
            //std::set<wh::basic::Edge> edges;//边集合
            //构造函数
            Polygon_mesh();
            Polygon_mesh(Eigen::MatrixXd& vertices,Eigen::MatrixXi& faces);
            

            //mesh 细分
            void tri_mesh_subdivision();//三角面片细分
            void loop_subdivision();//loop细分


            //=======其他功能
            //生成边集
            std::set<wh::basic::Edge> creat_unordered_edges();//无序边
            std::set<wh::basic::Edge> creat_ordered_edges();//有序边

            //找到边的相邻面片
            std::map<wh::basic::Edge,std::set<wh::basic::Face> > find_edge_near_faces(std::set<wh::basic::Edge>& edges);
        } POLYGON_MESH;
    }
}

#endif