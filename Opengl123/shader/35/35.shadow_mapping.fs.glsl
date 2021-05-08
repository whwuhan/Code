#version 330 core
out vec4 FragColor;

in VS_OUT{
    vec3 FragPos;   // 将顶点在世界坐标系中的位置传递给片段着色器
    vec3 Normal;    // 顶点的法线（注意是经过model矩阵移动过后的顶点法线）
    vec2 TexCoords; // 顶点的纹理坐标
    vec4 FragPosLightSpace;// 顶点在光源空间中的坐标位置（类比相机坐标系，只是视角是从光源看出来）
} fs_in;

uniform sampler2D diffuseTexture;   // 漫反射贴图
uniform sampler2D shadowMap;        // 阴影贴图

uniform vec3 lightPos;
uniform vec3 viewPos;

// 计算是否在阴影中
float ShadowCalculation(vec4 fragPosLightSpace){
    // perform perspective divide 计算正交投影之后的坐标(计算光照是用的正交投影，而不是透视投影)
    // （注意投影矩阵只会显示视锥中的物体，同时会把坐标转化为标准设备坐标[-1,1]，将不在该范围的点裁剪掉）
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range 将坐标的范围转化到[0,1]
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r;
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // check whether current frag pos is in shadow
    // float bias = 0.005; // 加一个bias防止摩尔纹
    // 或者通过视角与fragment的法线计算bias
    vec3 lightDir = normalize(lightPos - fs_in.FragPos);
    vec3 normal = normalize(fs_in.Normal);
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005); 
    float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;
    return shadow;
}

void main(){
    vec3 color = texture(diffuseTexture, fs_in.TexCoords).rgb;  //贴图颜色
    vec3 normal = normalize(fs_in.Normal);
    vec3 lightColor = vec3(0.3);
    // ambient
    vec3 ambient = 0.3 * color;
    // diffuse
    vec3 lightDir = normalize(lightPos - fs_in.FragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * lightColor;
    // specular
    vec3 viewDir = normalize(viewPos - fs_in.FragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
    vec3 specular = spec * lightColor;
    // calculate shadow
    float shadow = ShadowCalculation(fs_in.FragPosLightSpace); // 判断是否在阴影中，如果是返回1.0否则返回0.0
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;
    FragColor = vec4(lighting, 1.0);
}

