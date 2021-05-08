#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture1;

void main()
{             
    vec4 texColor = texture(texture1, TexCoords);
    if(texColor.a < 0.1)
        discard;    //表示如果满足上述条件，就不会被着色器处理，会被丢弃(discard)
    FragColor = texColor;
}