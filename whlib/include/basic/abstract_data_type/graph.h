/**
 * 图抽象数据结构
 * 2020.08.20
 * wuhan
*/
#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <utility> //std::pair<>
#include <Eigen/Dense>
namespace wh{
    namespace basic{
        namespace adt{   
            template <typename T>
            class Graph{
            protected:
                std::vector<T> nodes;//图的节点
                std::vector< std::pair<unsigned int, unsigned int> > edges;//图的边
                unsigned int size;//图的点的个数
            public:
                Graph();
                Graph(const std::vector<T>& nodes, const std::vector< std::pair<unsigned int, unsigned int> >& edges);
                
                //get函数
                std::vector<T>& get_nodes();
                std::vector< std::pair<unsigned int, unsigned int> >& get_edges();
                unsigned int get_size();

                //专用函数
                //将节点数据转化成Eigen矩阵
                Eigen::MatrixXd nodes_data_to_matrix();

                //将图的边转化成邻接矩阵
                Eigen::MatrixXd get_adjacent_matrix();
            };

            //构造函数
            template <typename T>
            Graph<T>::Graph():nodes(),edges(),size(0){

            }

            template <typename T>
            Graph<T>::Graph(const std::vector<T>& nodes, const std::vector< std::pair<unsigned int, unsigned int> >& edges)
            :nodes(nodes),edges(edges),size(nodes.size()){

            }

            //get函数
            template <typename T>
            std::vector<T>& Graph<T>::get_nodes(){
                return nodes;
            }
            
            template <typename T>
            std::vector< std::pair<unsigned int, unsigned int> >& Graph<T>::get_edges(){
                return edges;
            }
            
            template <typename T>
            unsigned int Graph<T>::get_size(){
                return size;
            }

            //专用函数
            //将节点数据转化成Eigen矩阵
            template <typename T>
            Eigen::MatrixXd Graph<T>::nodes_data_to_matrix(){
                if(nodes.size() <= 0){
                    std::cout << "no nodes data" << std::endl;
                    return Eigen::MatrixXd(0,0);
                }
                int point_size = nodes[0].data.size();
                Eigen::MatrixXd res(size, point_size);//返回结果
                for(unsigned int i = 0; i < size; i++){
                    for(unsigned int j = 0; j < point_size; j++){
                        res(i,j) = nodes[i][j];
                    }
                }
                return res;
            }
        }
    }
}

#endif