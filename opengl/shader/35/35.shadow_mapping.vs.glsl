#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;

out VS_OUT {
    vec3 FragPos;   // 将顶点在世界坐标系中的位置传递给片段着色器
    vec3 Normal;    // 顶点的法线（注意是经过model矩阵移动过后的顶点法线）
    vec2 TexCoords; // 顶点的纹理坐标
    vec4 FragPosLightSpace;// 顶点在光源空间中的坐标位置（类比相机坐标系，只是视角是从光源看出来）
} vs_out;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 lightSpaceMatrix;

void main()
{
    vs_out.FragPos = vec3(model * vec4(aPos, 1.0));
    vs_out.Normal = transpose(inverse(mat3(model))) * aNormal;
    vs_out.TexCoords = aTexCoords;
    vs_out.FragPosLightSpace = lightSpaceMatrix * vec4(vs_out.FragPos, 1.0); // 光源坐标系中的坐标
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}