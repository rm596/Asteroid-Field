#version 330 core
layout (location = 0) out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} fs_in;

uniform sampler2D diffuseTexture;

void main()
{           
    vec3 color = texture(diffuseTexture, fs_in.TexCoords).rgb;
    FragColor = vec4(color, 1.0f);
}