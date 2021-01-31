#version 330 core
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

