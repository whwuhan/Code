//光照贴图
#version 330 core
out vec4 FragColor;

//材质信息
struct Material{
    sampler2D diffuse;          //漫反射贴图
    sampler2D specular;         //镜面光贴图
    float shininess;            //反光度
};

//光照信息
struct Light{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main(){
    //环境光
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;    //环境光颜色一般都等于漫反射
    
    //漫反射
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;

    //镜面反射
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;

    //结果
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0f);
}