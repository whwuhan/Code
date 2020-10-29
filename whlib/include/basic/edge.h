#ifndef EDGE_H
#define EDGE_H
#include <iostream>
namespace wh{
    namespace basic{
        typedef struct Edge{
            //无序边默认第一个顶点一定比第二个顶点位置小
            unsigned int fir_ver_index;//第一个顶点位置
            unsigned int sec_ver_index;//第二个顶点位置

            Edge();
            Edge(unsigned int fir_ver_index,unsigned int sec_ver_index,bool unordered=true);
            friend std::ostream& operator<<(std::ostream& ost,const wh::basic::Edge edge);
            bool operator<(const Edge& edge)const;
        } EDGE;
        std::ostream& operator<<(std::ostream& ost,const wh::basic::Edge edge);
    }
}
#endif