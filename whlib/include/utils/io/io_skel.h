#ifndef IO_SKEL_H
#define IO_SKEL_H
#include <string>
#include <iomanip>
#include <fstream>
#include "../../basic/abstract_data_type/curve.h"
#include "../string_lib.h"
namespace wh
{
    namespace utils
    {
        namespace io
        {
            //======声明======
            //读取skel文件中的骨架线
            template <typename T>
            void load_curves_skel(const std::string file_name, std::vector< wh::basic::adt::Curve<T> >* curves_ptr);

            //=====实现=======
            //读取skel文件中的骨架线
            template <typename T>
            void load_curves_skel(const std::string file_name, std::vector< wh::basic::adt::Curve<T> >* curves_ptr)
            {
                //打开文件
                std::ifstream data_source(file_name);
                if(!data_source.is_open())
                {
                    std::cout << "no data source." << std::endl;
                    return;
                }
                //读入文件
                std::string line;
                std::vector<std::string> line_split;
                unsigned int curves_count = 0;//curves的数量
                unsigned int points_count = 0;//每条curve中点的数量
                while(getline(data_source, line))
                {
                    if("CN" == line.substr(0,2) && "CNN" != line.substr(0,3))
                    {
                        line_split = wh::utils::split(line, " ");
                        curves_count = atoi(line_split[1].c_str());
                        curves_ptr->resize(curves_count);
                        curves_count = 0;//作为index 
                    }
                    
                    if("CNN" == line.substr(0,3))
                    {   
                        //确定curve中的点数量
                        line_split = wh::utils::split(line, "   ");
                        points_count = atoi(line_split[1].c_str());

                        //存储单独的一条边中的点
                        std::vector<T> curve(points_count);
                        for(int i = 0; i < points_count; i++)
                        {   
                            if(getline(data_source, line))//往下读一行
                            {
                                line_split = wh::utils::split(line, "\t");//注意skel文件不是用的空格，用的制表符
                                double x = atof(line_split[0].c_str());
                                double y = atof(line_split[1].c_str());
                                double z = atof(line_split[2].c_str());
                                curve[i] = T(x, y, z);//一条边中的点
                            }
                            else
                            {
                                std::cout << "wrong skel data."<< std::endl;
                            }
                        }
                        //将curve放入curves
                        (*curves_ptr)[curves_count++] = wh::basic::adt::Curve<T>(curve); 
                    }
                }
                data_source.close();
            }
        }
    }
}
#endif