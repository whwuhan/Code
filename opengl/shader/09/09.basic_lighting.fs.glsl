//物体的片段着色器
#version 330 core
out vec4 FragColor;

in vec3 Normal;//法线
in vec3 FragPos;//物体顶点在世界坐标系中的坐标

uniform vec3 lightPos;//光源在世界坐标系中的位置
uniform vec3 lightColor;//光照颜色
uniform vec3 objectColor;//物体的颜色

void main(){
    //环境光照
    //环境光照强度
    float ambientStrength = 0.1;
    //环境光照
    vec3 ambient = ambientStrength * lightColor;

    //漫反射光照
    vec3 norm = normalize(Normal);//归一化顶点法线!!!!!
    vec3 lightDir = normalize(lightPos - FragPos);//光照方向（其实是光照方向的反方向）
    float diff = max(dot(norm, lightDir), 0.0f);//计算漫反射的强度，光照方向和法向量之间的夹角越大，影响越小
    vec3 diffuse = diff * lightColor;//漫反射

    vec3 result = (ambient + diffuse) * objectColor;//计算混合结果
    FragColor = vec4(result, 1.0);
}
