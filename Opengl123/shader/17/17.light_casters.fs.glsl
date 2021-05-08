//多光源（将不同的光源类型封装成函数）
//片段着色器
#version 330 core
out vec4 FragColor;

//材质结构体
struct Material{
    //材质对环境光的贡献一般和漫反射一样
    sampler2D diffuse;      //漫反射贴图
    sampler2D specular;     //镜面光贴图
    float shininess;        //反光度
};

// //光线结构体
// struct Light{
//     vec3 position;      //点光源的位置
//     vec3 direction;     //聚光的光照方向
//     float cutOff;       //内切光角
//     float outerCutOff;  //外切光角

//     vec3 ambient;       //环境光
//     vec3 diffuse;       //漫反射
//     vec3 specular;      //镜面反射

//     //衰减参数(Attenuation)
//     //衰减公式 = 1.0 / (constant + linear * distance + quadratic * distance ^ 2)
//     float constant;     //常数项（通常为1.0，保证衰减始终小于1.0）
//     float linear;       //一次项
//     float quadratic;    //二次项
// };

//定向光结构体
struct DirLight{
    vec3 direction;     //方向
    vec3 ambient;       //环境光
    vec3 diffuse;       //漫反射
    vec3 specular;      //镜面光反射
};

//点光源结构体
struct PointLight{
    vec3 position;      //位置

    float constant;     //衰减常数项
    float linear;       //衰减一次项
    float quadratic;    //衰减二次项

    vec3 ambient;       //环境光
    vec3 diffuse;       //漫反射
    vec3 specular;      //镜面反射
};

//聚光结构体
struct SpotLight{
    vec3 position;      //位置
    vec3 direction;     //方向
    float cutOff;       //内圆锥角度的余弦
    float outerCutOff;  //外圆锥角度的余弦

    float constant;     //衰减常数项
    float linear;       //衰减一次项
    float quadratic;    //衰减二次项

    vec3 ambient;       //环境光
    vec3 diffuse;       //漫反射
    vec3 specular;      //镜面反射
};

#define NR_POINT_LIGHTS 4   //点光源个数

in vec3 FragPos;        //片段在世界坐标系中的位置
in vec3 Normal;         //片段在世界坐标系中的法线
in vec2 TexCoords;      //贴图坐标

uniform vec3 viewPos;                               //视角位置
uniform DirLight dirLight;                          //定向光
uniform PointLight pointLights[NR_POINT_LIGHTS];     //多个点光源
uniform SpotLight spotLight;                        //聚光
uniform Material material;                          //材质
// uniform Light light;                             //光线

//光照函数原型
//定向光
vec3 CalcDirLight(DirLight light, vec3 Normal, vec3 viewDir);
//点光源
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
//聚光
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main(){
    // //环境光
    // vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;

    // //漫反射
    // vec3 norm = normalize(Normal);
    // vec3 lightDir = normalize(light.position - FragPos);//注意这里光的方向实际是光的逆方向
    // float diff = max(dot(norm, lightDir), 0.0f);        //漫反射强度
    // vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;

    // //镜面反射
    // vec3 viewDir = normalize(viewPos - FragPos);
    // vec3 reflectDir = reflect(-lightDir, norm);         //注意这里光的入射方向又和光的逆方向相反
    // float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);  //镜面反射强度
    // vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;

    // //聚光平滑边缘
    // float theta = dot(lightDir, normalize(-light.direction));   //内圆锥夹角余弦
    // float epsilon = (light.cutOff - light.outerCutOff);         //内外圆锥夹角余弦的差值
    // //计算聚光的光照强度 公式：强度 = （光线来源夹角的余弦 - 外圆锥夹角的余弦） / (内圆锥夹角的余弦 - 外圆锥夹角的余弦)
    // //clamp参数1.数值 2.数值的下限 3.数值的上限 如果超过上下限返回上限或者下限，否则返回数值
    // float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0f, 1.0f);
    // diffuse *= intensity;
    // specular *= intensity;
    
    // //衰减（attenuation）
    // float distance = length(light.position - FragPos);  //计算光源到片段的距离
    // float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // //计算衰减后的光照强度
    // ambient *= attenuation;
    // diffuse *= attenuation;
    // specular *= attenuation;

    // vec3 result = ambient + diffuse + specular;
    // FragColor = vec4(result, 1.0f);

    vec3 norm = normalize(Normal);                  //点的法线
    vec3 viewDir = normalize(viewPos - FragPos);    //视线方向（注意方向是从片段位置指向观看位置）

    //定向光（多个顶点光源）
    vec3 result = CalcDirLight(dirLight, norm, viewDir);
    for(int i = 0; i < NR_POINT_LIGHTS; i++){
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
    }

    //聚光
    result += CalcSpotLight(spotLight, norm, FragPos, viewDir);

    FragColor = vec4(result, 1.0f);
}

//计算定向光颜色
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir){
    vec3 lightDir = normalize(-light.direction);    //光源方向(注意和光照方向的区别)

    //漫反射
    float diff = max(dot(normal, lightDir), 0.0f);
    
    //镜面反射
    vec3 reflectDir = reflect(-lightDir, normal);   //反射方向
    float spec = pow(max(dot(reflectDir ,viewDir), 0.0f), material.shininess);

    //计算结果
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));  //注意这里材质对环境光的贡献和漫反射一样
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    return (ambient + diffuse + specular);
}

//计算点光源颜色
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir){
    vec3 lightDir = normalize(light.position - fragPos);    //光源方向(注意和光照方向的区别)

    //漫反射
    float diff = max(dot(normal, lightDir), 0.0f);
    //镜面反射
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(reflectDir, viewDir), 0.0f), material.shininess);
    //衰减
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    //计算结果
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

//计算聚光颜色
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir){
    vec3 lightDir = normalize(light.position - fragPos);    //光源方向(注意和光照方向的区别)

    //漫反射
    float diff = max(dot(normal, lightDir), 0.0f);

    //镜面反射
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);

    //衰减
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    //内外圆锥光照强度
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0f, 1.0f);
    
    //计算结果
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}