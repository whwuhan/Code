//物体的顶点着色器
#version 330 core
//输入
layout (location=0) in vec3 aPos;
layout (location=1) in vec3 aNormal;

//输出
out vec3 FragPos;//传输给片段着色器的顶点位置
out vec3 Normal;//传输给片段着色器的顶点法线

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
    FragPos = vec3(model * vec4(aPos,1.0f));//移动到世界坐标系中的某个位置
    Normal = aNormal;

    gl_Position = projection * view * vec4(FragPos,1.0f);
}
