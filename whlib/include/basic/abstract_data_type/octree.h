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

                //创建polygon_mesh的八叉树
                void createOctree(int level,Eigen::MatrixXd& vertices);

                //数据插入八叉树
                OctreeNode<T>* insert(T& data);

                //获取某个节点(范围)中的数据
                T getDataAt(const Eigen::RowVector3d& position,
                double x,double y, double z,
                Eigen::MatrixXd& vertices);

                //判断面片是否在包含在节点内
                bool isContained(T& data);
            };

            

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

            //获取某个节点(范围)中的mesh数据
            template<typename T>
            T OctreeNode<T>::getDataAt(const Eigen::RowVector3d& position,
            double x,double y, double z,Eigen::MatrixXd& vertices){
                //获取限制
                double xMin=position[0]-x/2.0;
                double xMax=position[0]+x/2.0;
                double yMin=position[1]-y/2.0;
                double yMax=position[1]+y/2.0;
                double zMin=position[2]-z/2.0;
                double zMax=position[2]+z/2.0;

                std::set<wh::basic::Face> faces;
                for(int i=0;i<data.rows();i++){
                    if(
                        (
                            vertices(data.row(i)[0],0)>xMin && vertices(data.row(i)[0],0)<xMax &&
                            vertices(data.row(i)[0],1)>yMin && vertices(data.row(i)[0],1)<yMax &&
                            vertices(data.row(i)[0],2)>zMin && vertices(data.row(i)[0],2)<zMax
                        ) 
                        ||
                        (
                            vertices(data.row(i)[1],0)>xMin && vertices(data.row(i)[1],0)<xMax &&
                            vertices(data.row(i)[1],1)>yMin && vertices(data.row(i)[1],1)<yMax &&
                            vertices(data.row(i)[1],2)>zMin && vertices(data.row(i)[1],2)<zMax
                        )
                        ||
                        (
                            vertices(data.row(i)[2],0)>xMin && vertices(data.row(i)[2],0)<xMax &&
                            vertices(data.row(i)[2],1)>yMin && vertices(data.row(i)[2],1)<yMax &&
                            vertices(data.row(i)[2],2)>zMin && vertices(data.row(i)[2],2)<zMax
                        )

                    ){
                            faces.insert(wh::basic::Face(data.row(i)));
                    }//end if
                }
                //返回某个节点的面片数据
                int size=faces.size();
                T data(size,3);
                for(auto iter=faces.begin();iter!=faces.end();iter++){
                    for(int i=0;i<size;i++){
                        data(i,0)=iter->fir_ver_index;
                        data(i,1)=iter->sec_ver_index;
                        data(i,2)=iter->thd_ver_index;
                    }
                }
                return data;
            }




            //创建polygon_mesh八叉树
            template<typename T>
            void OctreeNode<T>::createOctree(int level,Eigen::MatrixXd& vertices){
                //递归地进行八叉树空间划分，直到最大深度
                if(level==maxLevel){
                    return;
                }
                //创建子节点
                //获取子节点的位置
                Eigen::RowVector3d BLFPos(position[0]-x/4.0,position[1]-y/4.0,position[2]+z/4.0);
                Eigen::RowVector3d BRFPos(position[0]+x/4.0,position[1]-y/4.0,position[2]+z/4.0);
                Eigen::RowVector3d BLBPos(position[0]-x/4.0,position[1]-y/4.0,position[2]-z/4.0);
                Eigen::RowVector3d BRBPos(position[0]+x/4.0,position[1]-y/4.0,position[2]-z/4.0);

                Eigen::RowVector3d TLFPos(position[0]-x/4.0,position[1]+y/4.0,position[2]+z/4.0);
                Eigen::RowVector3d TRFPos(position[0]+x/4.0,position[1]+y/4.0,position[2]+z/4.0);
                Eigen::RowVector3d TLBPos(position[0]-x/4.0,position[1]+y/4.0,position[2]-z/4.0);
                Eigen::RowVector3d TRBPos(position[0]+x/4.0,position[1]+y/4.0,position[2]-z/4.0);

                //获取子节点数据
                T BLFData=getDataAt(BLFPos,x/2.0,y/2.0,z/2.0,vertices);
                T BRFData=getDataAt(BRFPos,x/2.0,y/2.0,z/2.0,vertices);
                T BLBData=getDataAt(BLBPos,x/2.0,y/2.0,z/2.0,vertices);
                T BRBData=getDataAt(BRBPos,x/2.0,y/2.0,z/2.0,vertices);
                T TLFData=getDataAt(TLFPos,x/2.0,y/2.0,z/2.0,vertices);
                T TRFData=getDataAt(TRFPos,x/2.0,y/2.0,z/2.0,vertices);
                T TLBData=getDataAt(TLBPos,x/2.0,y/2.0,z/2.0,vertices);
                T TRBData=getDataAt(TRBPos,x/2.0,y/2.0,z/2.0,vertices);
                OctreeNode<T>* bottom_left_front_node=new OctreeNode<T>(BLFData,BOTTOM_LEFT_FRONT,BLFPos,x/2.0,y/2.0,z/2.0,level+1,maxLevel);
                OctreeNode<T>* bottom_right_front_node=new OctreeNode<T>(BRFData,BOTTOM_RIGHT_FRONT,BRFPos,x/2.0,y/2.0,z/2.0,level+1,maxLevel);
                OctreeNode<T>* bottom_left_back_node=new OctreeNode<T>(BLBData,BOTTOM_LEFT_BACK,BLBData,x/2.0,y/2.0,z/2.0,level+1,maxLevel);
                OctreeNode<T>* bottom_right_back_node=new OctreeNode<T>(BRBData,BOTTOM_RIGHT_BACK,BRBPos,x/2.0,y/2.0,z/2.0,level+1,maxLevel);
                OctreeNode<T>* top_left_front_node=new OctreeNode<T>(TLFData,TOP_LEFT_FRONT,TLFPos,x/2.0,y/2.0,z/2.0,level+1,maxLevel);
                OctreeNode<T>* top_right_front_node=new OctreeNode<T>(TRFData,TOP_RIGHT_FRONT,TRFPos,x/2.0,y/2.0,z/2.0,level+1,maxLevel);
                OctreeNode<T>* top_left_back_node=new OctreeNode<T>(TLBData,TOP_LEFT_BACK,TLBPos,x/2.0,y/2.0,z/2.0,level+1,maxLevel);
                OctreeNode<T>* top_right_back_node=new OctreeNode<T>(TRBData,TOP_RIGHT_BACK,TRBPos,x/2.0,y/2.0,z/2.0,level+1,maxLevel);

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