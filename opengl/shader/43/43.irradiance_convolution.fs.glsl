#version 330 core
// 间接光照中的diffuse部分
/**
    采样以法线为中心的半球，积一次分，放到cubemap中，之后只需要采样就完事了
*/
out vec4 FragColor;
in vec3 WorldPos;

uniform samplerCube environmentMap;

const float PI = 3.14159265359;

void main()
{
    vec3 N = normalize(WorldPos); //注意这是半球面的法线，也就是世界坐标系中的位置

    vec3 irradiance = vec3(0.0);

    // tangent space calculation from origin point
    vec3 up = vec3(0.0, 1.0, 0.0);
    vec3 right = cross(up, N);
    up = cross(N, right);

    float sampleDelta = 0.025;//采样间隔
    float nrSamples = 0.0f;//采样数量
    for(float phi = 0.0; phi < 2.0 * PI; phi += sampleDelta)
    {
        for(float theta = 0.0; theta < 0.5 * PI; theta += sampleDelta)
        {
            //从球坐标转换到直角坐标系
            vec3 tangentSample = vec3(sin(theta) * cos(phi), sin(theta) * sin(phi), cos(theta));
            //从tangent space 转变到世界坐标系中
            vec3 sampleVec = tangentSample.x * right + tangentSample.y * up + tangentSample.z * N;

            irradianceMap += texture(environmentMap, sampleVec).rgb * cos(theta) * sin(theta);
            nrSamples ++;
        }
    }
    irradiance = PI * irradiance * (1.0 / float(nrSamples));
    FragColor = vec4(irradiance, 1.0);
}