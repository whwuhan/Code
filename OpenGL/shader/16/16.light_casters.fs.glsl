//聚光Spotlight 新增平滑/柔滑边缘
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

//光线结构图
struct Light{
    vec3 position;      //点光源的位置
    vec3 direction;     //聚光的光照方向
    float cutOff;       //内切光角
    float outerCutOff;  //外切光角

    vec3 ambient;       //环境光
    vec3 diffuse;       //漫反射
    vec3 specular;      //镜面反射

    //衰减参数(Attenuation)
    //衰减公式 = 1.0 / (constant + linear * distance + quadratic * distance ^ 2)
    float constant;     //常数项（通常为1.0，保证衰减始终小于1.0）
    float linear;       //一次项
    float quadratic;    //二次项
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
    vec3 lightDir = normalize(light.position - FragPos);//注意这里光的方向实际是光的逆方向
    float diff = max(dot(norm, lightDir), 0.0f);        //漫反射强度
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;

    //镜面反射
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);         //注意这里光的入射方向又和光的逆方向相反
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);  //镜面反射强度
    vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;

    //聚光平滑边缘
    float theta = dot(lightDir, normalize(-light.direction));   //内圆锥夹角余弦
    float epsilon = (light.cutOff - light.outerCutOff);         //内外圆锥夹角余弦的差值
    //计算聚光的光照强度 公式：强度 = （光线来源夹角的余弦 - 外圆锥夹角的余弦） / (内圆锥夹角的余弦 - 外圆锥夹角的余弦)
    //clamp参数1.数值 2.数值的下限 3.数值的上限 如果超过上下限返回上限或者下限，否则返回数值
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0f, 1.0f);
    diffuse *= intensity;
    specular *= intensity;
    
    //衰减（attenuation）
    float distance = length(light.position - FragPos);  //计算光源到片段的距离
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    //计算衰减后的光照强度
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0f);
}
