#version 330 core
out vec4 FragColor;
in vec2 TexCoords;
in vec3 WorldPos;
in vec3 Normal;

// material parameters
uniform sampler2D albedoMap;
uniform sampler2D normalMap;
uniform sampler2D metallicMap;
uniform sampler2D roughnessMap;


// lights
uniform vec3 lightPositions[1];
uniform vec3 lightColors[1];

uniform vec3 camPos;

const float PI = 3.14159265359;

// Easy trick to get tangent-normals to world-space to keep PBR code simplified.
// Don't worry if you don't get what's going on; you generally want to do normal 
// mapping the usual way for performance anways; I do plan make a note of this 
// technique somewhere later in the normal mapping tutorial.
// 将tangent space中的法线转换到 world space 中
vec3 getNormalFromMap();

float DistributionGGX(vec3 N, vec3 H, float roughness); // normal distribution function
float GeometrySchlickGGX(float NdotV, float roughness); // geometry function
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness); // geometry function
vec3 fresnelSchlick(float cosTheta, vec3 F0); // fresnel equation

void main()
{
    // 注意albedo已经在sRGB空间中了（gamma correction那一章有介绍）
    // 现在先把他转换到线性空间中
    vec3 albedo = pow(texture(albedoMap, TexCoords).rgb, vec3(2.2));
    float metallic = texture(metallicMap, TexCoords).r;
    float roughness = texture(roughnessMap, TexCoords).r;
    float ao = 1.0f;

    vec3 N = getNormalFromMap();    // 从法线贴图中获取世界坐标系中的法线
    vec3 V = normalize(camPos - WorldPos);   //视角向量

    // calculate reflectance at normal incidence; if dia-electric (like plastic) use F0 
    // of 0.04 and if it's a metal, use the albedo color as F0 (metallic workflow)    
    vec3 F0 = vec3(0.04); 
    F0 = mix(F0, albedo, metallic);

    // reflectance equation 反射方程 也就是最外面的那个方程
    vec3 Lo = vec3(0.0);  // light out
    for(int i = 0; i < lightPositions.length(); ++i)
    {
        // calculate per-light radiance 计算每个光源的radiance，因为是点光源所以就一个方向上的radiance
        vec3 L = normalize(lightPositions[i] - WorldPos); // 光线方向
        vec3 H = normalize(V + L); // halfway vector
        float distance  = length(lightPositions[i] - WorldPos);
        float attenuation = 1.0 / (distance * distance); //衰减系数
        vec3 radiance = lightColors[i] * attenuation;

        // Cook-Torrance BRDF
        // 计算DFG
        float NDF = DistributionGGX(N, H, roughness);
        float G = GeometrySmith(N, V, L, roughness);
        vec3 F = fresnelSchlick(clamp(dot(H, V), 0.0, 1.0), F0);

        vec3 nominator = NDF * G * F;
        float denominator = 4 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0);
        vec3 specular = nominator / max(denominator, 0.001);

        // kS is equal to Fresnel
        vec3 kS = F;
        // for energy conservation, the diffuse and specular light can't
        // be above 1.0 (unless the surface emits light); to preserve this
        // relationship the diffuse component (kD) should equal 1.0 - kS.
        vec3 kD = vec3(1.0) - kS;
        // multiply kD by the inverse metalness such that only non-metals 
        // have diffuse lighting, or a linear blend if partly metal (pure metals
        // have no diffuse light).
        kD *= 1.0 - metallic;

        // scale light by NdotL
        float NdotL = max(dot(N, L), 0.0);

        // add to outgoing radiance Lo
        // note that we already multiplied the BRDF by the Fresnel (kS) 
        // so we won't multiply by kS again
        // 之所以不乘以kS，是因为 Fresnel可以代表kS
        Lo += (kD * albedo / PI + specular) * radiance * NdotL;
    }
    // ambient lighting (note that the next IBL tutorial will replace 
    // this ambient lighting with environment lighting).
    vec3 ambient = vec3(0.03) * albedo * ao;

    vec3 color = ambient + Lo;

    // HDR tonemapping
    color = color / (color + vec3(1.0));
    // gamma correct
    color = pow(color, vec3(1.0/2.2)); 

    FragColor = vec4(color, 1.0);
}

// Easy trick to get tangent-normals to world-space to keep PBR code simplified.
// Don't worry if you don't get what's going on; you generally want to do normal 
// mapping the usual way for performance anways; I do plan make a note of this 
// technique somewhere later in the normal mapping tutorial.
// 将tangent space中的法线转换到 world space 中
vec3 getNormalFromMap()
{   
    // 将[0,1]转换到[-1,1] 因为normalMap是一张贴图，颜色通道的范围是[0,1]
    vec3 tangentNormal = texture(normalMap, TexCoords).xyz * 2.0 - 1.0;

    // 求TBN矩阵（忘了就去看normal mapping那一章）
    // 求变化快慢（近似求斜率）
    // 相邻两个fragment的世界坐标的变化率（x和y方向的，注意y方向是朝下的）
    // 参考资料：https://www.cnblogs.com/flyfox1982/p/11141638.html
    vec3 dwp_dx = dFdx(WorldPos); // dwp = d(WorldPos)
    vec3 dwp_dy = dFdy(WorldPos);
    // 相邻两个fragment的uv坐标的变化率（x和y方向的，注意y方向是朝下的）
    vec2 dtc_dx = dFdx(TexCoords); // dtc = d(TexCoords)
    vec2 dtc_dy = dFdy(TexCoords);

    vec3 N = normalize(Normal);
    // 贴图拉伸
    vec3 T = normalize(dwp_dx * dtc_dy.t - dwp_dy * dtc_dx.t);
    // 从坐标系A转变到坐标系B，
    // 需要B的基在坐标系A下的表示矩阵的逆，而正交阵，逆=转置
    // 添加负号，可能是因为stb_image读取图片时y轴是向下的
    vec3 B = -normalize(cross(N, T)); 
    // vec3 B = normalize(cross(N, T));

    mat3 TBN = mat3(T, B, N);
    
    //将法线贴图中的法线，转换到世界坐标系中
    return normalize(TBN * tangentNormal);
}

// normal distribution function
float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a = roughness * roughness;
    float a2 = a * a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH * NdotH;

    float nom = a2; //分子
    float denom = (NdotH2 * (a2 - 1.0) + 1.0); //分母
    denom = PI * denom * denom;

    return nom / max(denom, 0.0000001);
}
// geometry function
float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = roughness + 1.0;
    float k = (r * r) / 8.0;

    float nom = NdotV;//分子
    float denom = NdotV * (1.0 - k) + k;//分母

    return nom / denom;
}

// geometry function 这个综合了直接光照和IBL
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}

// fresnel equations
vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(max(1.0 - cosTheta, 0.0), 5.0);
}