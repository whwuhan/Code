#ifndef POLYGON_MESH_H
#define POLYGON_MESH_H
#include <Eigen/Dense>

namespace wh{
    namespace basic{
        typedef struct Polygon_mesh{
            Eigen::MatrixXd vertices;//多边型顶点
            Eigen::MatrixXd faces;//多边形面片
            
        } POLYGON_MESH;
    }
}

#endif