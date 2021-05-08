#version 330 core
/*
    包含了PBR的直接光照部分
    也包含了PBR的间接光照部分（环境光ambient）
*/
out vec4 FragColor;
in vec2 TexCoords;
in vec3 WorldPos;
in vec3 Normal;

// material parameters 材质的参数 通常是贴图，这里为了简便取固定的值
uniform vec3 albedo;
uniform float metallic;
uniform float roughness;
uniform float ao;

// IBL 环境光照的cubemap和预先算好的look-up texture
uniform samplerCube irradianceMap;
uniform samplerCube prefilterMap;
uniform sampler2D brdfLUT;

// lights 光照位置和颜色
uniform vec3 lightPositions[4];
uniform vec3 lightColors[4];

// 相机位置
uniform vec3 camPos;

const float PI = 3.14159265359;

// NDF 法线分布方程
float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a = roughness * roughness;
    float a2 = a * a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH * NdotH;

    float nom = a2;// 分子
    float denom = NdotH2 * (a2 - 1.0) + 1.0; //分母
    denom = PI * denom * denom;

    return nom / denom;
}

// 几何项 Geometry Function 近似表示overshadow（只包含射入光线或者射出光线的overshadow）
float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = roughness + 1.0;
    float k = (r * r) / 8.0; //这里k用的是直接光照的计算方式

    float nom  = NdotV; //分子
    float denom = NdotV * (1 - k) + k; //分母

    return nom / denom; 
}

// 几何项 Geometry Function 因为光线射入时有部分光会被遮挡，同时射出时也会被遮挡，所以用上面的近似计算两次
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);

    float ggx1 = GeometrySchlickGGX(NdotV, roughness); //从p射出时遮挡后剩下的部分
    float ggx2 = GeometrySchlickGGX(NdotL, roughness); //从p射入时遮挡后剩下的部分

    return ggx1 * ggx2; 
}

// 菲涅尔项  Fresnel Equation 描述镜面反射光的比例
vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(max(1.0 - cosTheta, 0.0), 5.0);
}

// 带roughness的 菲涅尔项
vec3 fresnelSchlickRoughness(float cosTheta, vec3 F0, float roughness)
{
    return F0 + (max(vec3(1 - roughness), F0) - F0) * pow(max(1.0 - cosTheta, 0.0), 5.0);
}

void main()
{
    vec3 N = Normal;                            //法线
    vec3 V = normalize(camPos - WorldPos);      //视角
    vec3 R = reflect(-V, N);                    //反射向量

    // calculate reflectance at normal incidence; if dia-electric (like plastic) use F0 
    // of 0.04 and if it's a metal, use the albedo color as F0 (metallic workflow)    
    // 意思就是金属程度越高，albedo的贡献就越高，反之（为非金属）就使用初始的F0作为初始颜色
    vec3 F0 = vec3(0.04);
    F0 = mix(F0, albedo, metallic);

    // reflectance equation 渲染方程
    //=============直接光照部分==============
    vec3 Lo = vec3(0.0);
    for(int i = 0; i < lightPositions.length(); ++i)
    {
        // calculate per-light radiance 对每一个光源计算直接光照的radiance
        vec3 L = normalize(lightPositions[i] - WorldPos);
        vec3 H = normalize(V + L);
        float distance = length(lightPositions[i] - WorldPos); // 点到摄像机的距离
        float attenuation = 1.0 / (distance * distance);// 这里只用了简单的二次衰减
        vec3 radiance = lightColors[i] * attenuation; // 初始radiance

        // Cook-Torrance BRDF
        float NDF = DistributionGGX(N, H, roughness);
        float G = GeometrySmith(N, V, L, roughness);
        vec3 F = fresnelSchlick(max(dot(H, V), 0.0), F0);

        vec3 nominator = NDF * G * F;//分子
        float denominator = 4 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.001; // +0.001是防止除以0
        vec3 specular = nominator / denominator;

        // kS is equal to Fresnel
        vec3 kS = F;
        vec3 kD = vec3(1.0) - kS;
        // pure metals have no diffuse
        kD *= 1.0 - metallic;

        float NdotL = max(dot(N, L), 0.0);

        Lo += ((kD * albedo / PI) + specular) * radiance * NdotL;
    }
    //=============直接光照部分结束==============
    
    //=============间接光照部分==============
    // ambient lighting (we now use IBL as the ambient term)
    // 
    vec3 F = fresnelSchlickRoughness(max(dot(N, V), 0.0), F0, roughness);
    
    vec3 kS = F;
    vec3 kD = 1.0 - kS;
    kD *= 1.0 - metallic;	  
    
    vec3 irradiance = texture(irradianceMap, N).rgb;
    vec3 diffuse      = irradiance * albedo;
    
    // sample both the pre-filter map and the BRDF lut and combine them together as per the Split-Sum approximation to get the IBL specular part.
    const float MAX_REFLECTION_LOD = 4.0;
    vec3 prefilteredColor = textureLod(prefilterMap, R,  roughness * MAX_REFLECTION_LOD).rgb;    
    vec2 brdf  = texture(brdfLUT, vec2(max(dot(N, V), 0.0), roughness)).rg;
    vec3 specular = prefilteredColor * (F * brdf.x + brdf.y);

    vec3 ambient = (kD * diffuse + specular) * ao;
    
    vec3 color = ambient + Lo;
    //=============间接光照部分结束==============

    
    // HDR tonemapping
    color = color / (color + vec3(1.0));
    // gamma correct
    color = pow(color, vec3(1.0/2.2)); 

    FragColor = vec4(color , 1.0);
    
}
