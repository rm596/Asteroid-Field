#version 330 core

layout (location = 0) in vec4 in_Position;
layout (location = 2) in vec2 in_UV;

out vec2 TexCoords;

void main()
{
    gl_Position = in_Position;
    TexCoords = in_UV;
}