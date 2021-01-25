#version 330 core
/*
    预运算 pre-compute
    将环境贴图(cubemap)进行卷积操作保存起来，作为渲染是的irradiance
*/
out vec4 FragColor
in vec3 WorldPos

uniform samplerCube environmentMap;

const float PI = 3.14159265359;

void main()
{
    // The world vector acts as the normal of a tangent surface
    // from the origin, aligned to WorldPos. Given this normal, calculate all
    // incoming radiance of the environment. The result of this radiance
    // is the radiance of light coming from -Normal direction, which is what
    // we use in the PBR shader to sample irradiance.
    vec3 N = normalize(WorldPos);

    vec3 irradiance = vec3(0.0);

    // tangent space calculation from origin point
    vec3 up    = vec3(0.0, 1.0, 0.0);
    vec3 right = cross(up, N);
    up            = cross(N, right);

    float sampleDelta = 0.025;
    float nrSample = 0.0;// 采样数量
    for(float phi = 0.0; phi < 2.0 * PI; phi += sampleDelta)
    {
        for(float theta = 0.0; theta < 0.5 * PI; theta += sampleDelta)
        {
            // spherical to cartesian (in tangent space) 在平行空间中，将求坐标转换成直角坐标
            vec3 tangentSample = vec3(sin(theta) * cos(phi), sin(theta) * sin(phi), cos(theta));
            // tangent space to world space
            vec3 sampleVec = tangentSample.x * right + tangentSample.y * up + tangentSample.z * N; 
            
            irradiance += texture(environmentMap, sampleVec).rgb * cos(theta) * sin(theta);
            nrSample++;
        }
    }

    irradiance = PI * irradiance * (1.0 / float(nrSamples));
    FragColor = vec4(irradiance, 1.0);
}