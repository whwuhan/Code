/**
 * 网格Mesh头文件
*/
#ifndef MESH_WH_H
#define MESH_WH_H
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <shader.h>

#include <string>
#include <vector>

//点结构体
struct Vertex{
    glm::vec3 Position;     //点的位置
    glm::vec3 Normal;       //点法线
    glm::vec2 TexCoords;    //点纹理坐标
    glm::vec3 Tangent;      //切线
    glm::vec3 Bitangent;    //双切线
};

//纹理结构体
struct Texture{
    unsigned int id;        //纹理ID
    std::string type;       //类型
    std::string path;       //路径
};

class Mesh{
public:
    //mesh Data
    std::vector<Vertex>         vertices;   //顶点
    std::vector<unsigned int>   indices;    //顶点索引
    std::vector<Texture>        textures;   //纹理
    unsigned int VAO;

    //构造函数
    Mesh(std::vector<Vertex> vertices,std::vector<unsigned int> indices,std::vector<Texture> textures);
    
    //绘制
    void Draw(Shader &shader);

private:
    //绘制数据
    unsigned int VBO, EBO;

    //初始化所有buffer
    void setupMesh();
};
#endif