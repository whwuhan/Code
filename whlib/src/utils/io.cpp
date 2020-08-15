#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include "../../include/utils/io.h"
#include "../../include/utils/string_lib.h"
using namespace std;
using namespace wh::utils;
using namespace wh::basic;
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
        if(line[0] == 'v')
        {   
            line_split = split(line, " ");
            point_cloud_ptr->points(count, 0) = atof(line_split[1].c_str());
            point_cloud_ptr->points(count, 1) = atof(line_split[2].c_str());
            point_cloud_ptr->points(count, 2) = atof(line_split[3].c_str());
            count++;
        }
    }
    data_source.close();
}