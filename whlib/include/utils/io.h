#ifndef IO_H
#define IO_H
#include <string>
#include "../basic/point_cloud.h"
namespace wh
{
    namespace utils
    {
        //obj文件点云读取与写入
        void load_point_cloud_obj(const std::string file_name,struct wh::basic::Point_cloud* const point_cloud_ptr);
        void save_point_cloud_obj(const std::string file_name,const struct wh::basic::Point_cloud* const point_cloud_ptr);
    }
}
#endif