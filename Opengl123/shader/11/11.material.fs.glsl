//材质片段着色器，主要新增材质结构体和光线结构体
#version 330 core
out vec4 FragColor;

//材质结构体
struct Material{
    vec3 ambient;       //环境光照
    vec3 diffuse;       //漫反射
    vec3 specular;      //镜面反射
    float shininess;    //高光
};

//光照结构体
struct Light{
    vec3 position;      //光源位置
    vec3 ambient;       //环境光照
    vec3 diffuse;       //漫反射
    vec3 specular;      //镜面反射
};

in vec3 FragPos;        //物体顶点的世界坐标
in vec3 Normal;         //物体顶点的法线

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main(){
    //环境光照分量
    vec3 ambient = light.ambient * material.ambient;

    //漫反射
    vec3 norm = normalize(Normal);                              //先归一化法线
    vec3 lightDir = normalize(light.position - FragPos);        //光照方向
    float diff = max(dot(norm, lightDir), 0.0);                 //漫反射强度
    vec3 diffuse = light.diffuse * diff * material.diffuse;     //漫反射分量

    //镜面反射
    vec3 viewDir = normalize(viewPos - FragPos);                //视角方向
    vec3 reflectDir = reflect(-lightDir, norm);                //光线反射方向（注意前面的负号）
    //高光强度
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
    vec3 specular = light.specular * spec * material.specular;  //高光分量
    
    vec3 result = ambient + diffuse + specular;                 //将环境光照分量、漫反射分量、高光分量相加
    FragColor = vec4(result, 1.0f);
}