#version 330 core
/**

渲染LUT
渲染的是个quad
2D图像
横轴是NdotV
纵轴是roughness

*/
layout (location  = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

void main()
{
    TexCoords = aTexCoords;
    gl_Position = vec4(aPos, 1.0);
}