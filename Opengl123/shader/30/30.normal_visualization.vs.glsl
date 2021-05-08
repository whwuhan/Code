#version 330 core
layout (location=0) in vec3 aPos;
layout (location=1) in vec3 aNormal;

// interface block接口块 类似于C++的结构体
out VS_OUT{
    vec3 normal;
} vs_out;

uniform mat4 view;
uniform mat4 model;

void main(){
    mat3 normalMatrix = mat3(transpose(inverse(view * model))); //计算点法线经过仿射变换以后的法线 矩阵左上3*3的部分的逆的转置
    vs_out.normal = vec3(vec4(normalMatrix * aNormal, 0.0));
    gl_Position = view * model * vec4(aPos, 1.0);
}