#version 330 core
/**
输入一个图元(三角形)的三个顶点，分别使用cubeMap的留个朝向渲染，输入6个三角形(不同视角的同一个三角形)
*/
layout (triangles) in;//输入的图元是三角形的三个点（几何着色器都是输入图元的点）
layout (triangle_strip, max_vertices = 18) out;//输出(triangle_strip)是相互连接的三角形 输出是6个三角形

uniform mat4 shadowMatrices[6];//包含投影矩阵和观察矩阵 投影矩阵都是相同的，观察矩阵不同，因为要朝6个不同的方向查看

out vec4 FragPos;

void main()
{
    for(int face = 0; face < 6; ++face)
    {
        gl_Layer = face; // built-in variable that specifies to which face we render.
        for(int i = 0; i < 3; ++i)// for each triangle's vertices
        {
            FragPos = gl_in[i].gl_Position;//将世界坐标传递给fragment shader gl_in内置类型，详情见geometry shader
            gl_Position = shadowMatrices[face] * FragPos;//将顶点转换到light space的观察空间，注意要转换6次，因为要朝6个方向看
            EmitVertex();
        }
        EndPrimitive();
    }
}