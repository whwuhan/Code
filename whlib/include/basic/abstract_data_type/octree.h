//八叉树结构体
#ifndef OCTREE_H
#define OCTREE_H
#include <basic/face.h>
#include <Eigen/Dense>
#include <set>
#include <vector>
namespace wh{
    namespace basic{
        namespace adt{
            //声明
            //八叉树类型枚举
            enum OctreeNodeType{
                ROOT,                   //根
                BOTTOM_LEFT_FRONT,      // 1 
                BOTTOM_RIGHT_FRONT,     // 2 
                BOTTOM_LEFT_BACK,       // 3 
                BOTTOM_RIGHT_BACK,      // 4 
                TOP_LEFT_FRONT,         // 5 
                TOP_RIGHT_FRONT,        // 6 
                TOP_LEFT_BACK,          // 7 
                TOP_RIGHT_BACK,         // 8
                UN_DEFINE               // 9
            };

            //八叉树声明
            template<typename T>
            class OctreeNode{
            public:
                T data; //节点数据(都用set存储)
                OctreeNodeType octreeNodeType;//节点类型
                Eigen::RowVector3d position;//节点中心的位置
                //节点长宽高
                double x;
                double y;
                double z;

                //节点的子结点  
                OctreeNode <T>*top_left_front;
                OctreeNode <T>*top_left_back; 
                OctreeNode <T>*top_right_front;
                OctreeNode <T>*top_right_back;
                OctreeNode <T>*bottom_left_front;
                OctreeNode <T>*bottom_left_back;
                OctreeNode <T>*bottom_right_front;
                OctreeNode <T>*bottom_right_back;

                unsigned int level;//当前层级
                unsigned int maxLevel;//最大层级

                OctreeNode();
                OctreeNode(
                    T data,                         //节点数据
                    OctreeNodeType octreeNodeType,  //节点类型
                    Eigen::RowVector3d position,    //节点位置
                    double x,                       //节点x长度
                    double y,                       //节点y长度
                    double z,                       //节点z长度
                    // OctreeNode <T>*top_left_front, 
                    // OctreeNode <T>*top_left_back,
                    // OctreeNode <T>*top_right_front, 
                    // OctreeNode <T>*top_right_back,
                    // OctreeNode <T>*bottom_left_front, 
                    // OctreeNode <T>*bottom_left_back,
                    // OctreeNode <T>*bottom_right_front, 
                    // OctreeNode <T>*bottom_right_back,
                    unsigned int level,             //节点层数
                    unsigned int maxLevel           //最大层数
                );
            };

            //创建八叉树
            template<typename T>
            OctreeNode<T>* createOctree(int level,Eigen::MatrixXd& vertices);

            //数据插入八叉树
            template<typename T>
            OctreeNode<T>* insert(T& data);

            //获取某个节点(范围)中的数据
            template<typename T>
            T getDataAt(const Eigen::RowVector3d& position);

            //判断面片是否在包含在节点内
            template<typename T>
            bool isContained(T& data);

            //============实现
            //无参构造函数
            template<typename T>
            OctreeNode<T>::OctreeNode()
            :data(),octreeNodeType(UN_DEFINE),position(),
            x(0.0),y(0.0),z(0.0),
            top_left_front(nullptr),
            top_left_back(nullptr),
            top_right_front(nullptr),
            top_right_back(nullptr),
            bottom_left_front(nullptr),
            bottom_left_back(nullptr),
            bottom_right_front(nullptr),
            bottom_right_back(nullptr),
            level(0),
            maxLevel(0)
            {}

            //polygon_mesh 八叉树 data是面片索引(Eigen::MatrixXi faces)，顶点信息不保存在octree中，在创建octree的时候传入
            template<typename T>
            OctreeNode<T>::OctreeNode(
                T data,
                OctreeNodeType octreeNodeType,
                Eigen::RowVector3d position,
                double x,
                double y,
                double z,
                // OctreeNode <T>*top_left_front, 
                // OctreeNode <T>*top_left_back,
                // OctreeNode <T>*top_right_front, 
                // OctreeNode <T>*top_right_back,
                // OctreeNode <T>*bottom_left_front, 
                // OctreeNode <T>*bottom_left_back,
                // OctreeNode <T>*bottom_right_front, 
                // OctreeNode <T>*bottom_right_back,
                unsigned int level,
                unsigned int maxLevel
            ):
            data(data),
            octreeNodeType(octreeNodeType),
            position(position),
            x(x),
            y(y),
            z(z),
            // top_left_front(top_left_front),
            // top_left_back(top_left_back),
            // top_right_front(top_right_front),
            // top_right_back(top_right_back),
            // bottom_left_front(bottom_left_front),
            // bottom_left_back(bottom_left_back),
            // bottom_right_front(bottom_right_front),
            // bottom_right_back(bottom_right_back),
            level(level),
            maxLevel(maxLevel){

            }
            
            //判断面片是否在包含在节点内
            template<typename T>
            bool OctreeNode<T>::isContained(T& data){
                //获取限制
                double xMin=position[0]-x/2.0;
                double xMax=position[0]+x/2.0;
                double yMin=position[1]-y/2.0;
                double yMax=position[1]+y/2.0;
                double zMin=position[2]-z/2.0;
                double zMax=position[2]+z/2.0;
            }

            //获取某个节点(范围)中的数据
            template<typename T>
            T OctreeNode<T>::getDataAt(const Eigen::RowVector3d& position){
                //获取限制
                double xMin=position[0]-x/2.0;
                double xMax=position[0]+x/2.0;
                double yMin=position[1]-y/2.0;
                double yMax=position[1]+y/2.0;
                double zMin=position[2]-z/2.0;
                double zMax=position[2]+z/2.0;
            }




            //创建polygon_mesh八叉树
            template<typename T>
            OctreeNode<T>* OctreeNode<T>::createOctree(int level,Eigen::MatrixXd& vertices){
                //递归地进行八叉树空间划分，直到最大深度
                if(level==maxLevel){
                    return;
                }
                //创建子节点
                bottom_left_front_node=new OctreeNode<T>(,BOTTOM_LEFT_FRONT,level+1,maxLevel);
                bottom_right_front_node=new OctreeNode<T>(,BOTTOM_RIGHT_FRONT,level+1,maxLevel);
                bottom_left_back_node=new OctreeNode<T>(,BOTTOM_LEFT_BACK,level+1,maxLevel);
                bottom_right_back_node=new OctreeNode<T>(,BOTTOM_RIGHT_BACK,level+1,maxLevel);
                top_left_front_node=new OctreeNode<T>(,TOP_LEFT_FRONT,level+1,maxLevel);
                top_right_front_node=new OctreeNode<T>(,TOP_RIGHT_FRONT,level+1,maxLevel);
                top_left_back_node=new OctreeNode<T>(,TOP_LEFT_BACK,level+1,maxLevel);
                top_right_back_node=new OctreeNode<T>(,TOP_RIGHT_BACK,level+1,maxLevel);
                //递归构造
                bottom_left_front_node->createOctree(level+1);
                bottom_right_front_node->createOctree(level+1);
                bottom_left_back_node->createOctree(level+1);
                bottom_right_back_node->createOctree(level+1);
                top_left_front_node->createOctree(level+1);
                top_right_front_node->createOctree(level+1);
                top_left_back_node->createOctree(level+1);
                top_right_back_node->createOctree(level+1);
            }
        }
    }
}
#endif