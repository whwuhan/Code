//平行光片段着色器（不再需要光的位置，而需要只需要光的方向）
#version 330 core
out vec4 FragColor;

//材质结构体
struct Material{
    //材质对环境光的贡献一般和漫反射一样
    sampler2D diffuse;      //漫反射贴图
    sampler2D specular;     //镜面光贴图
    float shininess;        //反光度
};

//光线结构图
struct Light{
    //vec3 position; 平行光不再需要光源的位置
    vec3 direction;     //平行光的方向

    vec3 ambient;       //环境光
    vec3 diffuse;       //漫反射
    vec3 specular;      //镜面反射
};

in vec3 FragPos;        //片段在世界坐标系中的位置
in vec3 Normal;         //片段在世界坐标系中的法线
in vec2 TexCoords;      //贴图坐标

uniform vec3 viewPos;           //视角位置
uniform Material material;      //材质
uniform Light light;            //光线

void main(){
    //环境光
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;

    //漫反射
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-light.direction);        //注意这里光的方向实际是平行光的逆方向
    float diff = max(dot(norm, lightDir), 0.0f);        //漫反射强度
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;

    //镜面反射
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);         //注意这里光的入射方向又和平行光的逆方向相反
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);  //镜面反射强度
    vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0f);
}
