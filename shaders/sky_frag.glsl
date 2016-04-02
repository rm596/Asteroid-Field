	#version 330 core

	in vec4 ex_Color;

	//out vec4 out_Color;
	out vec4 out_color;

	//texturas
	in vec2 UV;
	uniform sampler2D gSampler; //textura activa

	void main(void)
	{
		out_color = vec4(texture( gSampler, UV ).rgb, 1.0);
		//out_Color = ex_Color;
		//out_color = vec4(1.0, 0.0, 0.0, 1.0);
	}
	
	