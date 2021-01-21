#version 330 core
out vec4 FragColor;
in vec3 WorldPos;

uniform sampler2D equirectangularMap;

// 获取当前世界坐标对应环境贴图的uv坐标
vec2 SampleSphericalMap(vec3 v);

const vec2 invAtan = vec2(0.1591, 0.3183);

void main()
{
    vec2 uv = SampleSphericalMap(normalize(WorldPos));  // 注意一定要归一化
    vec3 color = texture(equirectangularMap, uv).rgb;
    
    FragColor = vec4(color, 1.0);
}

vec2 SampleSphericalMap(vec3 v)
{
    // 将当前世界坐标转化为对应环境贴图的uv坐标
    // trigonometry magic (spherical to cartesian)
    vec2 uv = vec2(atan(v.z, v.x), asin(v.y));
    uv *= invAtan;
    uv += 0.5;
    return uv;
}
