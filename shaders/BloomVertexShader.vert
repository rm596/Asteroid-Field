#version 330 core
layout (location = 0) in vec4 in_Position;
layout (location = 1) in vec3 in_Normal;
layout (location = 2) in vec2 in_UV;

out VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} vs_out;

uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;

void main()
{
    gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * in_Position;
    vs_out.FragPos = vec3(ModelMatrix * in_Position);   
    vs_out.TexCoords = in_UV;
        
    mat3 normalMatrix = transpose(inverse(mat3(ModelMatrix)));
    vs_out.Normal = normalize(normalMatrix * in_Normal);
}