#version 330 core
/*
    渲染一个立方体的顶点着色器
**/
layout (location = 0) in vec3 aPos;

out vec3 WorldPos;

uniform mat4 projection;
uniform mat4 view;


void main()
{   
    // 没有model矩阵就是想放在中心位置
    WorldPos = aPos;
    gl_Position =  projection * view * vec4(WorldPos, 1.0);
}