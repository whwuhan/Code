#ifndef IO_H
#define IO_H
#include <string>
#include "../../basic/point_cloud.h"
#include "../../basic/abstract_data_type/graph.h"
namespace wh
{
    namespace utils
    {   
        namespace io
        {
            //======声明=========
            //obj点云文件点云读取与写入
            void load_point_cloud_obj(const std::string file_name,struct wh::basic::Point_cloud* const point_cloud_ptr);
            void save_point_cloud_obj(const std::string file_name,const struct wh::basic::Point_cloud* const point_cloud_ptr);
            //obj图文件的读入
            //void load_graph_obj(const std::string file_name,wh::basic::adt::Graph* const graph_ptr);
            //void save_graph_obj(const std::string file_name,const wh::basic::adt::Graph* const graph_ptr);
            


        } 
    }
}
#endif