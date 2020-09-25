#include <Mesh_wh.h>


Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
:vertices(vertices),indices(indices),textures(textures){
    setupMesh();
}

void Mesh::Draw(Shader& shader){
    //纹理的命名标准，前面是纹理的类型，后面是纹理的编号，例如texture_diffuseN
    //纹理的编号
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;
    for(unsigned int i = 0;i < textures.size();i++){
        //激活对应纹理
        glActiveTexture(GL_TEXTURE0 + i);

        std::string number;
        std::string name = textures[i].type;
        if(name == "texture_diffuse"){
            number = std::to_string(diffuseNr++);
        }else if(name == "texture_specular"){
            number = std::to_string(specularNr++);
        }else if(name == "texture_normal"){
            number = std::to_string(normalNr++);
        }else if(name == "texture_height"){
            number = std::to_string(heightNr++);
        }

        //将采样器设置到正确的纹理单
        unsigned int location = glGetUniformLocation(shader.ID, (name + number).c_str());
        glUniform1i(location, i);//设置值
        //绑定纹理
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }

    //绘制mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}

//初始化
void Mesh::setupMesh(){
    //创建VAO VBO EBO（绘制数据）
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    //绑定VAO
    glBindVertexArray(VAO);
    //将原始数据加载到VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);  

    //将索引加载到EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    //设置VAO
    //点的位置
    glEnableVertexAttribArray(0);	
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    //点法线
    glEnableVertexAttribArray(1);	
    //注意offsetof(s, m) s是结构体名称 m是结构体的属性 返回属性在结构体中的偏移量
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    //点的纹理坐标
    glEnableVertexAttribArray(2);	
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
    //点的切线
    // glEnableVertexAttribArray(3);
    // glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
    // //点的双切线
    // glEnableVertexAttribArray(4);
    // glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));

    //解绑VAO
    glBindVertexArray(0);
}