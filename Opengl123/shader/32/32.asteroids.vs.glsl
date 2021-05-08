#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in mat4 ainstanceMatrix;//值得注意的是，这里实际上是占用了location,3，4，5，6因为他是4*4的矩阵，有4个vec4变量

out vec2 TexCoords;

uniform mat4 projection;
uniform mat4 view;
//uniform mat4 model;不要model了因为现在是使用instanceMatrix

void main()
{
    TexCoords = aTexCoords;
    gl_Position = projection * view * ainstanceMatrix * vec4(aPos, 1.0f); 
}