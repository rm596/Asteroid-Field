#version 330 core

// Ouput data
out vec4 color;

in vec4 particlecolor;

//texturas
in vec2 UV;
uniform sampler2D gSampler; //textura activa

void main(void)
{
	vec4 color_texture = texture( gSampler, UV ) * particlecolor;

	if (color_texture.r < 0.3 && color_texture.g < 0.3 && color_texture.b < 0.3)
	{
      discard; 
	}
	
	color = color_texture;
}