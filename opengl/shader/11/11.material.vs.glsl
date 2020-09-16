//物体着色器
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 FragPos;           //传递给片段着色器的顶点的位置（是在世界坐标系中的位置，因为要计算光照）
out vec3 Normal;            //传递给片段着色器的顶点法线

uniform mat4 model;         //模型矩阵
uniform mat4 view;          //观察矩阵
uniform mat4 projection;    //投影矩阵

void main(){
    FragPos = vec3(model * vec4(aPos, 1.0f));
    Normal = mat3(transpose(inverse(model))) * aNormal;

    gl_Position = projection * view * vec4(FragPos, 1.0f);//前面已经和model矩阵相乘了
}