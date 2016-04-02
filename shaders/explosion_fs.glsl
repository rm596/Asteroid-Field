#version 330 core

// Ouput data
out vec4 color;

in vec4 particlecolor;

//texturas
in vec2 UV;
uniform sampler2D gSampler; //textura activa

void main(void)
{
	color = particlecolor;
}