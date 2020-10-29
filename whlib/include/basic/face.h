#ifndef FACE_H
#define FACE_H
#include <iostream>
#include <Eigen/Dense>
namespace wh{
    namespace basic{
        typedef struct Face{
            unsigned int fir_ver_index;//第一个顶点位置
            unsigned int sec_ver_index;//第二个顶点位置
            unsigned int thd_ver_index;//第三个顶点位置
            Face();
            Face(Eigen::RowVector3i face_index);
            Face(unsigned int fir_ver_index,unsigned int sec_ver_index,unsigned int thd_ver_index);
            friend std::ostream& operator<<(std::ostream& ost,const wh::basic::Face face);
            bool operator<(const Face& face)const;
        } FACE;
        std::ostream& operator<<(std::ostream& ost,const wh::basic::Face face);
    }
}
#endif