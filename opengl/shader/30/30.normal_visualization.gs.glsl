/* 
* 用几何着色器绘制法线
* 几何着色器的输入就是一个图元的所有顶点
*/
#version 330 core
layout (triangles) in;//表示输入的图元类型
layout (line_strip, max_vertices = 6) out;//表示输出的图元类型

in VS_OUT{
    vec3 normal;
} gs_in[];

const float MAGNITUDE = 0.2;

uniform mat4 projection;

void GenerateLine(int index){
    gl_Position = projection * gl_in[index].gl_Position;//通过投影矩阵，将法线的一个顶点位置找到
    EmitVertex();
    gl_Position = projection * (gl_in[index].gl_Position + vec4(gs_in[index].normal, 0.0) * MAGNITUDE);//法线的第二个顶点
    EmitVertex();
    EndPrimitive();
}

void main(){
    //之所以是3个点，是因为输入的图元类型是三角形，而三角形只有3个顶点
    GenerateLine(0); // first vertex normal
    GenerateLine(1); // second vertex normal
    GenerateLine(2); // third vertex normal
}  