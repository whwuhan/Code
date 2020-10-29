#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
#include <utils/io/io_obj.h>
#include <utils/string_lib.h>
using namespace std;
using namespace wh::utils::io;
using namespace wh::basic;
//读取obj点云文件
void wh::utils::io::load_point_cloud_obj(const string file_name,struct Point_cloud* point_cloud_ptr){   
    //打开文件
    ifstream data_source(file_name);
    if(!data_source.is_open()){
        cout << "no data source." << endl;
        return;
    }

    //读入文件
    string line;
    vector<string> line_split;
    unsigned int count = 0;//obj文件点的数量

    while(getline(data_source, line)){   
        if(line[0] == 'v'){   
            //line_split = split(line, " ");
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
    cout<<"Point Cloud size:"<<count<<endl;
    data_source.clear();//先要clear()才能回到文件头
    data_source.seekg(0, ios::beg);
    point_cloud_ptr->resize(count, 3);
    count = 0;

    while(getline(data_source, line)){   
        switch(line[0]){   
            case 'v':
                line_split = split(line, " ");
                point_cloud_ptr->points(count, 0) = atof(line_split[1].c_str());
                point_cloud_ptr->points(count, 1) = atof(line_split[2].c_str());
                point_cloud_ptr->points(count, 2) = atof(line_split[3].c_str());
                count++;
                break;
        }
    }
    cout<<"Load Point Cloud Successfully!"<<endl;
    data_source.close();
}

//点云存入obj文件
void wh::utils::io::save_point_cloud_obj(const string file_name,const struct Point_cloud* const point_cloud_ptr){
    //打开文件
    ofstream data_destination(file_name);
    data_destination << "# whlib point cloud obj file" << endl;//文件头注释
    
    //获取当地时间
    time_t now = time(0);
    string date_time(ctime(&now));

    //注意时间后面自带换行
    data_destination << "# " << date_time;//写入存储时间

    //存储对象名
    std::vector<std::string> file_name_split = wh::utils::split(file_name,"/.\\");
    int file_name_index = file_name_split.size() - 2;
    data_destination << "o " << file_name_split[file_name_index]<<endl;//obj对象

    //存入数据
    for(int i = 0; i < point_cloud_ptr->size; i++){
        data_destination << "v" << " " << setiosflags(ios::fixed) << setprecision(10) << point_cloud_ptr->points.row(i)[0];
        data_destination << " " << setiosflags(ios::fixed) << setprecision(10) << point_cloud_ptr->points.row(i)[1];
        data_destination << " " << setiosflags(ios::fixed) << setprecision(10) << point_cloud_ptr->points.row(i)[2] << endl;
    }
    cout<<"Save Point Cloud Successfully!"<<endl;
    data_destination.close();
}

//cube triangular mesh 写入obj文件
void wh::utils::io::save_tri_cube_mesh_obj(const std::string file_name,wh::basic::Cube* cube_ptr){
    //打开文件
    ofstream data_destination(file_name);
    data_destination << "# whlib cube mesh obj file" << endl;//文件头注释

    //获取当地时间
    time_t now = time(0);
    string date_time(ctime(&now));

    //注意时间后面自带换行
    data_destination << "# " << date_time;//写入存储时间

    //存储对象名
    std::vector<std::string> file_name_split = wh::utils::split(file_name,"/.\\");
    int file_name_index = file_name_split.size() - 2;
    data_destination << "o " << file_name_split[file_name_index]<<endl;//obj对象

    //存入点数据
    for(int i = 0; i < cube_ptr->vertices.rows(); i++){
        data_destination << "v" << " " << setiosflags(ios::fixed) << setprecision(10) << cube_ptr->vertices.row(i)[0];
        data_destination << " " << setiosflags(ios::fixed) << setprecision(10) << cube_ptr->vertices.row(i)[1];
        data_destination << " " << setiosflags(ios::fixed) << setprecision(10) << cube_ptr->vertices.row(i)[2] << endl;
    }

    //写入面数据（注意顺序首个索引从小到大）
    data_destination << "f" << " " <<"1"<<" "<<"2"<<" "<<"3"<<endl;
    data_destination << "f" << " " <<"1"<<" "<<"3"<<" "<<"4"<<endl;
    data_destination << "f" << " " <<"1"<<" "<<"4"<<" "<<"5"<<endl;
    data_destination << "f" << " " <<"1"<<" "<<"5"<<" "<<"8"<<endl;
    data_destination << "f" << " " <<"1"<<" "<<"2"<<" "<<"7"<<endl;
    data_destination << "f" << " " <<"1"<<" "<<"7"<<" "<<"8"<<endl;
    data_destination << "f" << " " <<"2"<<" "<<"3"<<" "<<"6"<<endl;
    data_destination << "f" << " " <<"2"<<" "<<"6"<<" "<<"7"<<endl;
    data_destination << "f" << " " <<"3"<<" "<<"4"<<" "<<"6"<<endl;
    data_destination << "f" << " " <<"4"<<" "<<"5"<<" "<<"6"<<endl;
    data_destination << "f" << " " <<"5"<<" "<<"6"<<" "<<"7"<<endl;
    data_destination << "f" << " " <<"5"<<" "<<"7"<<" "<<"8"<<endl;
    data_destination.close();
}

//保存triangular cube meshes 
void wh::utils::io::save_tri_cube_meshes_obj(const std::string file_name,const std::vector<wh::basic::Cube>& cubes){
    //打开文件
    ofstream data_destination(file_name);
    
    data_destination << "# whlib cube mesh obj file" << endl;//文件头注释

    //获取当地时间
    time_t now = time(0);
    string date_time(ctime(&now));

    //注意时间后面自带换行
    data_destination << "# " << date_time;//写入存储时间

    //存储对象名
    std::vector<std::string> file_name_split = wh::utils::split(file_name,"/.\\");
    int file_name_index = file_name_split.size() - 2;
    data_destination << "o " << file_name_split[file_name_index]<<endl;//obj对象

    //存入点数据
    for(Cube cube : cubes){
        //cout<<cube.vertices.size()<<endl;
        for(int i = 0; i < cube.vertices.rows(); i++){
            data_destination << "v" << " " << setiosflags(ios::fixed) << setprecision(10) << cube.vertices.row(i)[0];
            data_destination << " " << setiosflags(ios::fixed) << setprecision(10) << cube.vertices.row(i)[1];
            data_destination << " " << setiosflags(ios::fixed) << setprecision(10) << cube.vertices.row(i)[2] << endl;
        }
    }

    //存入面数据
    for(int i=0;i<cubes.size();i++){
        data_destination << "f" << " " <<8*i+1<<" "<<8*i+2<<" "<<8*i+3<<endl;
        data_destination << "f" << " " <<8*i+1<<" "<<8*i+3<<" "<<8*i+4<<endl;
        data_destination << "f" << " " <<8*i+1<<" "<<8*i+4<<" "<<8*i+5<<endl;
        data_destination << "f" << " " <<8*i+1<<" "<<8*i+5<<" "<<8*i+8<<endl;
        data_destination << "f" << " " <<8*i+1<<" "<<8*i+2<<" "<<8*i+7<<endl;
        data_destination << "f" << " " <<8*i+1<<" "<<8*i+7<<" "<<8*i+8<<endl;
        data_destination << "f" << " " <<8*i+2<<" "<<8*i+3<<" "<<8*i+6<<endl;
        data_destination << "f" << " " <<8*i+2<<" "<<8*i+6<<" "<<8*i+7<<endl;
        data_destination << "f" << " " <<8*i+3<<" "<<8*i+4<<" "<<8*i+6<<endl;
        data_destination << "f" << " " <<8*i+4<<" "<<8*i+5<<" "<<8*i+6<<endl;
        data_destination << "f" << " " <<8*i+5<<" "<<8*i+6<<" "<<8*i+7<<endl;
        data_destination << "f" << " " <<8*i+5<<" "<<8*i+7<<" "<<8*i+8<<endl;
    }
    
    data_destination.close();
}

//重载保存triangular cube meshes
void wh::utils::io::save_tri_cube_meshes_obj(const std::string file_name,const std::set<wh::basic::Cube>& cubes){
    //打开文件
    ofstream data_destination(file_name);
    
    data_destination << "# whlib cube mesh obj file" << endl;//文件头注释

    //获取当地时间
    time_t now = time(0);
    string date_time(ctime(&now));

    //注意时间后面自带换行
    data_destination << "# " << date_time;//写入存储时间

    //存储对象名
    std::vector<std::string> file_name_split = wh::utils::split(file_name,"/.\\");
    int file_name_index = file_name_split.size() - 2;
    data_destination << "o " << file_name_split[file_name_index]<<endl;//obj对象

    //存入点数据
    for(Cube cube : cubes){
        // cout<<cube.vertices.rows()<<endl;
        for(int i = 0; i < cube.vertices.rows(); i++){
            data_destination << "v" << " " << setiosflags(ios::fixed) << setprecision(10) << cube.vertices.row(i)[0];
            data_destination << " " << setiosflags(ios::fixed) << setprecision(10) << cube.vertices.row(i)[1];
            data_destination << " " << setiosflags(ios::fixed) << setprecision(10) << cube.vertices.row(i)[2] << endl;
        }
    }

    //存入面数据
    // cout<<"size:"<<cubes.size()<<endl;
    for(int i=0;i<cubes.size();i++){
        data_destination << "f" << " " <<8*i+1<<" "<<8*i+2<<" "<<8*i+3<<endl;
        data_destination << "f" << " " <<8*i+1<<" "<<8*i+3<<" "<<8*i+4<<endl;
        data_destination << "f" << " " <<8*i+1<<" "<<8*i+4<<" "<<8*i+5<<endl;
        data_destination << "f" << " " <<8*i+1<<" "<<8*i+5<<" "<<8*i+8<<endl;
        data_destination << "f" << " " <<8*i+1<<" "<<8*i+2<<" "<<8*i+7<<endl;
        data_destination << "f" << " " <<8*i+1<<" "<<8*i+7<<" "<<8*i+8<<endl;
        data_destination << "f" << " " <<8*i+2<<" "<<8*i+3<<" "<<8*i+6<<endl;
        data_destination << "f" << " " <<8*i+2<<" "<<8*i+6<<" "<<8*i+7<<endl;
        data_destination << "f" << " " <<8*i+3<<" "<<8*i+4<<" "<<8*i+6<<endl;
        data_destination << "f" << " " <<8*i+4<<" "<<8*i+5<<" "<<8*i+6<<endl;
        data_destination << "f" << " " <<8*i+5<<" "<<8*i+6<<" "<<8*i+7<<endl;
        data_destination << "f" << " " <<8*i+5<<" "<<8*i+7<<" "<<8*i+8<<endl;
    }
    
    data_destination.close();
}

//cube wireframe（线框写入obj文件）
void wh::utils::io::save_cube_wireframe_obj(const std::string file_name,wh::basic::Cube* cube_ptr){
    //打开文件
    ofstream data_destination(file_name);
    data_destination << "# whlib cube wireframe obj file" << endl;//文件头注释

    //获取当地时间
    time_t now = time(0);
    string date_time(ctime(&now));

    //注意时间后面自带换行
    data_destination << "# " << date_time;//写入存储时间

    //存储对象名
    std::vector<std::string> file_name_split = wh::utils::split(file_name,"/.\\");
    int file_name_index = file_name_split.size() - 2;
    data_destination << "o " << file_name_split[file_name_index]<<endl;//obj对象

    //存入点数据
    for(int i = 0; i < cube_ptr->vertices.rows(); i++){
        data_destination << "v" << " " << setiosflags(ios::fixed) << setprecision(10) << cube_ptr->vertices.row(i)[0];
        data_destination << " " << setiosflags(ios::fixed) << setprecision(10) << cube_ptr->vertices.row(i)[1];
        data_destination << " " << setiosflags(ios::fixed) << setprecision(10) << cube_ptr->vertices.row(i)[2] << endl;
    }

    //写入线框（注意顺序首个索引从小到大）
    data_destination << "l" << " " <<"1"<<" "<<"2"<<endl;
    data_destination << "l" << " " <<"2"<<" "<<"3"<<endl;
    data_destination << "l" << " " <<"3"<<" "<<"4"<<endl;
    data_destination << "l" << " " <<"4"<<" "<<"1"<<endl;
    data_destination << "l" << " " <<"4"<<" "<<"5"<<endl;
    data_destination << "l" << " " <<"5"<<" "<<"6"<<endl;
    data_destination << "l" << " " <<"6"<<" "<<"3"<<endl;
    data_destination << "l" << " " <<"6"<<" "<<"7"<<endl;
    data_destination << "l" << " " <<"7"<<" "<<"2"<<endl;
    data_destination << "l" << " " <<"7"<<" "<<"8"<<endl;
    data_destination << "l" << " " <<"8"<<" "<<"1"<<endl;
    data_destination << "l" << " " <<"8"<<" "<<"5"<<endl;
    data_destination.close();
}

//cube wireframes（多个线框写入obj文件）
void wh::utils::io::save_cube_wireframes_obj(const string file_name,const vector<wh::basic::Cube>& cubes){
    //打开文件
    ofstream data_destination(file_name);
    data_destination << "# whlib cube wireframes obj file" << endl;//文件头注释

    //获取当地时间
    time_t now = time(0);
    string date_time(ctime(&now));

    //注意时间后面自带换行
    data_destination << "# " << date_time;//写入存储时间

    //存储对象名
    std::vector<std::string> file_name_split = wh::utils::split(file_name,"/.\\");
    int file_name_index = file_name_split.size() - 2;
    data_destination << "o " << file_name_split[file_name_index]<<endl;//obj对象

    //存入点数据
    for(Cube cube:cubes){
        for(int i = 0; i < cube.vertices.rows(); i++){
            data_destination << "v" << " " << setiosflags(ios::fixed) << setprecision(10) << cube.vertices.row(i)[0];
            data_destination << " " << setiosflags(ios::fixed) << setprecision(10) << cube.vertices.row(i)[1];
            data_destination << " " << setiosflags(ios::fixed) << setprecision(10) << cube.vertices.row(i)[2] << endl;
        }
    }
    
    //写入线框（注意顺序首个索引从小到大）
    for(int i=0;i<cubes.size();i++){
        data_destination << "l" << " " <<8*i+1<<" "<<8*i+2<<endl;
        data_destination << "l" << " " <<8*i+2<<" "<<8*i+3<<endl;
        data_destination << "l" << " " <<8*i+3<<" "<<8*i+4<<endl;
        data_destination << "l" << " " <<8*i+4<<" "<<8*i+1<<endl;
        data_destination << "l" << " " <<8*i+4<<" "<<8*i+5<<endl;
        data_destination << "l" << " " <<8*i+5<<" "<<8*i+6<<endl;
        data_destination << "l" << " " <<8*i+6<<" "<<8*i+3<<endl;
        data_destination << "l" << " " <<8*i+6<<" "<<8*i+7<<endl;
        data_destination << "l" << " " <<8*i+7<<" "<<8*i+2<<endl;
        data_destination << "l" << " " <<8*i+7<<" "<<8*i+8<<endl;
        data_destination << "l" << " " <<8*i+8<<" "<<8*i+1<<endl;
        data_destination << "l" << " " <<8*i+8<<" "<<8*i+5<<endl;
    }
    data_destination.close();
}

void wh::utils::io::save_cube_wireframes_obj(const std::string file_name,const std::set<wh::basic::Cube>& cubes){
    //打开文件
    ofstream data_destination(file_name);
    data_destination << "# whlib cube wireframes obj file" << endl;//文件头注释

    //获取当地时间
    time_t now = time(0);
    string date_time(ctime(&now));

    //注意时间后面自带换行
    data_destination << "# " << date_time;//写入存储时间

    //存储对象名
    std::vector<std::string> file_name_split = wh::utils::split(file_name,"/.\\");
    int file_name_index = file_name_split.size() - 2;
    data_destination << "o " << file_name_split[file_name_index]<<endl;//obj对象

    //存入点数据
    for(Cube cube:cubes){
        for(int i = 0; i < cube.vertices.rows(); i++){
            data_destination << "v" << " " << setiosflags(ios::fixed) << setprecision(10) << cube.vertices.row(i)[0];
            data_destination << " " << setiosflags(ios::fixed) << setprecision(10) << cube.vertices.row(i)[1];
            data_destination << " " << setiosflags(ios::fixed) << setprecision(10) << cube.vertices.row(i)[2] << endl;
        }
    }
    
    //写入线框（注意顺序首个索引从小到大）
    for(int i=0;i<cubes.size();i++){
        data_destination << "l" << " " <<8*i+1<<" "<<8*i+2<<endl;
        data_destination << "l" << " " <<8*i+2<<" "<<8*i+3<<endl;
        data_destination << "l" << " " <<8*i+3<<" "<<8*i+4<<endl;
        data_destination << "l" << " " <<8*i+4<<" "<<8*i+1<<endl;
        data_destination << "l" << " " <<8*i+4<<" "<<8*i+5<<endl;
        data_destination << "l" << " " <<8*i+5<<" "<<8*i+6<<endl;
        data_destination << "l" << " " <<8*i+6<<" "<<8*i+3<<endl;
        data_destination << "l" << " " <<8*i+6<<" "<<8*i+7<<endl;
        data_destination << "l" << " " <<8*i+7<<" "<<8*i+2<<endl;
        data_destination << "l" << " " <<8*i+7<<" "<<8*i+8<<endl;
        data_destination << "l" << " " <<8*i+8<<" "<<8*i+1<<endl;
        data_destination << "l" << " " <<8*i+8<<" "<<8*i+5<<endl;
    }
    data_destination.close();
}

//读取polygon mesh
void wh::utils::io::load_polygon_mesh_obj(const std::string file_name,wh::basic::Polygon_mesh *polygon_mesh_ptr){
    //打开文件
    ifstream data_source(file_name);
    if(!data_source.is_open()){
        cout << "no data source." << endl;
        return;
    }

    //读入文件
    string line;
    vector<string> line_split;
    unsigned int vertices_amount = 0;//顶点数量
    unsigned int faces_amount = 0;//面片数量

    bool polygon_mesh_type_is_confirmed = false;// polygon mesh类型是否确定
    int polygon_type = 3;//polygon_mesh的类型（三角面片还是四边形面片，默认是三角面片）
    //确定
    while(getline(data_source, line)){   
        if(line[0] == 'v'){   
            //line_split = split(line, " ");
            vertices_amount++;
            //cout << count << endl;
            /** resize()效率太低，改成先遍历点的个数，再resize()一次
            point_cloud_ptr->conservative_resize((++point_cloud_ptr->size), 3);
            point_cloud_ptr->points(point_cloud_ptr->size-1, 0) = atof(line_split[1].c_str());
            point_cloud_ptr->points(point_cloud_ptr->size-1, 1) = atof(line_split[2].c_str());
            point_cloud_ptr->points(point_cloud_ptr->size-1, 2) = atof(line_split[3].c_str());
            */
        }

        if(line[0] == 'f'){
            faces_amount++;
            if(!polygon_mesh_type_is_confirmed){
                line_split=split(line," ");
                polygon_type=line_split.size()-1;
            }
        }
    }

    data_source.clear();//先要clear()才能回到文件头
    data_source.seekg(0, ios::beg);
    
    polygon_mesh_ptr->vertices.resize(vertices_amount, 3);
    polygon_mesh_ptr->faces.resize(faces_amount,polygon_type);

    cout<<"vertices_amount:"<<vertices_amount<<endl;
    cout<<"faces_amount:"<<faces_amount<<endl;

    vertices_amount=0;
    faces_amount=0;
    while(getline(data_source, line)){   
        switch(line[0]){   
            case 'v':
                line_split = split(line, " ");
                polygon_mesh_ptr->vertices(vertices_amount, 0) = atof(line_split[1].c_str());
                polygon_mesh_ptr->vertices(vertices_amount, 1) = atof(line_split[2].c_str());
                polygon_mesh_ptr->vertices(vertices_amount, 2) = atof(line_split[3].c_str());
                vertices_amount++;
                break;
            case 'f':
                line_split = split(line, " ");
                for(int i=0;i<polygon_type;i++){
                    polygon_mesh_ptr->faces(faces_amount, i) = atoi(line_split[i+1].c_str());
                }
                faces_amount++;
                break;
            default:
                cout<<line<<endl;
        }
    }
    cout<<"Load Polygon Mesh Successfull!"<<endl;
    data_source.close();
}

//保存Polygon mesh
void wh::utils::io::save_polygon_mesh_obj(const std::string file_name,wh::basic::Polygon_mesh *polygon_mesh_ptr){
    //打开文件
    ofstream data_destination(file_name);
    data_destination << "# whlib polygon mesh obj file" << endl;//文件头注释

    //获取当地时间
    time_t now = time(0);
    string date_time(ctime(&now));

    //注意时间后面自带换行
    data_destination << "# " << date_time;//写入存储时间

    //存储对象名
    std::vector<std::string> file_name_split = wh::utils::split(file_name,"/.\\");
    int file_name_index = file_name_split.size() - 2;
    data_destination << "o " << file_name_split[file_name_index]<<endl;//obj对象
    cout<<"vertices_amount:"<<polygon_mesh_ptr->vertices.rows()<<endl;
    cout<<"faces_amount:"<<polygon_mesh_ptr->faces.rows()<<endl;
    //存入点数据
    for(int i = 0; i < polygon_mesh_ptr->vertices.rows(); i++){
        data_destination << "v" << " " << setiosflags(ios::fixed) << setprecision(10) << polygon_mesh_ptr->vertices.row(i)[0];
        data_destination << " " << setiosflags(ios::fixed) << setprecision(10) << polygon_mesh_ptr->vertices.row(i)[1];
        data_destination << " " << setiosflags(ios::fixed) << setprecision(10) << polygon_mesh_ptr->vertices.row(i)[2] << endl;
    }
    
    //写入面片信息
    int polygon_mesh_type=polygon_mesh_ptr->faces.cols();//获取是三角面片是是正方形面片
    for(int i=0;i<polygon_mesh_ptr->faces.rows();i++){
        data_destination << "f";
        for(int j=0;j<polygon_mesh_type;j++){
            //cout<<"face:"<<polygon_mesh_ptr->faces.row(i)[j]<<endl;
            data_destination<<" "<<polygon_mesh_ptr->faces.row(i)[j];
        }
        data_destination<<endl;
    }
    cout<<"Save Polygon Mesh Successfully!"<<endl;
    data_destination.close();
}