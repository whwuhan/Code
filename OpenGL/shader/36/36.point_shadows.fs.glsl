#version 330 core
in VS_OUT
{
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} fs_in;
out vec4 FragColor;

uniform sampler2D diffuseTexture;
uniform samplerCube depthMap;

uniform vec3 lightPos;
uniform vec3 viewPos;


uniform float far_plane;
uniform bool shadows;

float ShadowCalculation(vec3 fragPos)
{
    //获取fragPos到光源的向量
    vec3 fragToLight = fragPos - lightPos;
    //获取深度图上的最近距离
    float closestDepth = texture(depthMap, fragToLight).r;
    //反归一化
    closestDepth *= far_plane;
    //当前的距离
    float currentDepth = length(fragToLight);
    //添加偏置值，防止摩尔纹
    float bias = 0.05;
    float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;
    return shadow;
}

void main()
{
    vec3 color = texture(diffuseTexture, fs_in.TexCoords).rgb;
    vec3 normal = normalize(fs_in.Normal);
    vec3 lightColor = vec3(0.3);
    //ambient
    vec3 ambient = 0.3 * color;
    //diffuse
    vec3 lightDir = normalize(lightPos - fs_in.FragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * lightColor;
    //specular
    vec3 viewDir = normalize(viewPos - fs_in.FragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(halfwayDir, normal), 0.0), 64.0);
    vec3 specular = spec * lightColor;
    //判断是否在阴影中
    float shadow = shadows ? ShadowCalculation(fs_in.FragPos) : 0.0;
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;
    FragColor = vec4(lighting, 1.0);
}

