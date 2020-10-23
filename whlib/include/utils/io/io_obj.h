#ifndef IO_H
#define IO_H
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>
#include <vector>
#include <set>
#include <basic/point_cloud.h>
#include <basic/abstract_data_type/graph.h>
#include <basic/abstract_data_type/curve.h>
namespace wh{
    namespace utils{   
        namespace io{
            //======声明=========
            //点云Point_cloud
            void load_point_cloud_obj(const std::string file_name,struct wh::basic::Point_cloud* point_cloud_ptr);
            void save_point_cloud_obj(const std::string file_name,const struct wh::basic::Point_cloud* const point_cloud_ptr);
            
            //图Graph
            template <typename T>
            void load_graph_obj(const std::string file_name,wh::basic::adt::Graph<T>* graph_ptr);
            template <typename T>
            void save_graph_obj(const std::string file_name,const wh::basic::adt::Graph<T>* const graph_ptr);
            
            //曲线curve
            template <typename T>
            void save_curves_obj(const std::string file_name,const std::vector< wh::basic::adt::Curve<T> >* const curves_ptr);

            //立方体cube mesh
            void save_cube_mesh_obj(const std::string file_name,wh::basic::Cube* cube_ptr);
            void save_cube_wireframe_obj(const std::string file_name,wh::basic::Cube* cube_ptr);
            void save_cube_meshes_obj(const std::string file_name,const std::vector<wh::basic::Cube>& cubes);
            void save_cube_meshes_obj(const std::string file_name,const std::set<wh::basic::Cube>& cubes);
            void save_cube_wireframes_obj(const std::string file_name,const std::vector<wh::basic::Cube>& cubes);


            //=========模板方法实现=========
            template <typename T>
            void save_curves_obj(const std::string file_name, std::vector< wh::basic::adt::Curve<T> >* const curves_ptr){
                //打开文件
                std::ofstream data_destination(file_name);
                data_destination << "# whlib skeleton obj file" << std::endl;//文件头注释
                
                //获取当地时间
                time_t now = time(0);
                std::string date_time(ctime(&now));

                //注意时间后面自带换行
                data_destination << "# " << date_time;//写入存储时间
                data_destination << "o " << date_time;//以时间命名obj对象

                //存入数据
                //先存点
                for(auto it = curves_ptr->begin(); it != curves_ptr->end(); it++){
                    const std::vector<T>& points = it->get_points();
                    for(unsigned int i = 0; i < it->get_size(); i++){
                        data_destination << "v" << " " << std::setiosflags(std::ios::fixed) << std::setprecision(10) << points[i].data[0];
                        data_destination << " " << std::setiosflags(std::ios::fixed) << std::setprecision(10) << points[i].data[1];
                        data_destination << " " << std::setiosflags(std::ios::fixed) << std::setprecision(10) << points[i].data[2] << std::endl;
                    }
                }
                //再存边
                //获取每条curve的点的数量
                std::vector<unsigned int>  curve_points_count(curves_ptr->size());
                for(unsigned int i = 0; i < curves_ptr->size(); i++)
                {
                    curve_points_count[i] = (*curves_ptr)[i].get_size();
                    //std::cout << (*curves_ptr)[i].get_size() << std::endl;
                }

                unsigned int curves_points_sum = 0;//前面的curve一共有几个点
                unsigned int index = 0;//线的起始坐标
                for(unsigned int i = 0; i < curves_ptr->size(); i++){
                    for(unsigned int j = 0; j < (*curves_ptr)[i].get_size() - 1; j++){   
                        index = curves_points_sum + j + 1;
                        data_destination << "l" << " " << index << " " << (index + 1) << std::endl;
                    }
                    curves_points_sum = curves_points_sum + curve_points_count[i];
                }

                data_destination.close();
            }
        } 
    }
}
#endif