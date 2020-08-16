#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
#include "../../include/utils/io.h"
#include "../../include/utils/string_lib.h"
using namespace std;
using namespace wh::utils;
using namespace wh::basic;
//读取obj文件
void wh::utils::load_point_cloud_obj(const string file_name,struct Point_cloud* point_cloud_ptr)
{   
    //打开文件
    ifstream data_source(file_name);
    if(!data_source.is_open())
    {
        cout << "no data source." << endl;
        return;
    }

    //读入文件
    string line;
    vector<string> line_split;
    unsigned int count = 0;//obj文件点的数量

    while(getline(data_source, line))
    {   
        if(line[0] == 'v')
        {   
            line_split = split(line, " ");
            count++;
            //cout << count << endl;
            /** resize()效率太低，改成先遍历点的个数，再resize()一次
            point_cloud_ptr->conservative_resize((++point_cloud_ptr->size), 3);
            point_cloud_ptr->points(point_cloud_ptr->size-1, 0) = atof(line_split[1].c_str());
            point_cloud_ptr->points(point_cloud_ptr->size-1, 1) = atof(line_split[2].c_str());
            point_cloud_ptr->points(point_cloud_ptr->size-1, 2) = atof(line_split[3].c_str());
            */
        }
    }

    data_source.clear();//先要clear()才能回到文件头
    data_source.seekg(0, ios::beg);
    point_cloud_ptr->resize(count, 3);
    count = 0;

    while(getline(data_source, line))
    {   
        switch(line[0])
        {   
            case 'v':
                line_split = split(line, " ");
                point_cloud_ptr->points(count, 0) = atof(line_split[1].c_str());
                point_cloud_ptr->points(count, 1) = atof(line_split[2].c_str());
                point_cloud_ptr->points(count, 2) = atof(line_split[3].c_str());
                count++;
                break;
        }
    }
    data_source.close();
}

//点云存入obj文件
void wh::utils::save_point_cloud_obj(const string file_name,const struct Point_cloud* const point_cloud_ptr)
{
    //打开文件
    ofstream data_destination(file_name);
    data_destination << "# whlib point cloud obj file" << endl;//文件头注释
    
    //获取当地时间
    time_t now = time(0);
    string date_time(ctime(&now));

    //注意时间后面自带换行
    data_destination << "# " << date_time;//写入存储时间
    data_destination << "o " << date_time;//以时间命名obj对象

    //存入数据
    for(int i = 0; i < point_cloud_ptr->size; i++)
    {
        data_destination << "v" << " " << setiosflags(ios::fixed) << setprecision(6) << point_cloud_ptr->points.row(i)[0];
        data_destination << " " << setiosflags(ios::fixed) << setprecision(6) << point_cloud_ptr->points.row(i)[1];
        data_destination << " " << setiosflags(ios::fixed) << setprecision(6) << point_cloud_ptr->points.row(i)[2] << endl;
    }
    data_destination.close();
}