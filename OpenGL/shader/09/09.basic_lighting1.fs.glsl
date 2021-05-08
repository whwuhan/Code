//物体的片段着色器
//新增镜面高光
#version 330 core
out vec4 FragColor;

in vec3 Normal;//法线
in vec3 FragPos;//物体顶点在世界坐标系中的坐标

uniform vec3 lightPos;//光源在世界坐标系中的位置
uniform vec3 lightColor;//光照颜色
uniform vec3 objectColor;//物体的颜色
uniform vec3 viewPos;//新增传递进来的摄像机位置（观察位置）

void main(){
    //环境光照
    float ambientStrength = 0.1;//环境光照强度
    vec3 ambient = ambientStrength * lightColor;//环境光照分量

    //漫反射光照
    vec3 norm = normalize(Normal);//归一化顶点法线!!!!!
    vec3 lightDir = normalize(lightPos - FragPos);//光照方向（其实是光照方向的反方向）
    float diff = max(dot(norm, lightDir), 0.0f);//计算漫反射的强度，光照方向和法向量之间的夹角越大，影响越小
    vec3 diffuse = diff * lightColor;//漫反射

    //镜面高光
    float specularStrength = 0.5;//镜面高光强度
    vec3 viewDir = normalize(viewPos - FragPos);//计算观察向量
    vec3 reflectDir = reflect(-lightDir, norm);//注意计算光线反射时，需要的光照方向和之间计算的光线方向相反
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);//反光度为32，反光度越高，散射能力越小，光点就越小
    vec3 specular = specularStrength * spec * lightColor;//

    vec3 result = (ambient + diffuse + specular) * objectColor;//计算混合结果
    FragColor = vec4(result, 1.0);
}
