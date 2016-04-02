	#version 330 core

	in vec4 in_Position;
	out vec4 ex_Color;

	
	uniform vec4 in_Color;

	uniform mat4 ModelMatrix;
	uniform mat4 ViewMatrix;
	uniform	mat4 ProjectionMatrix;

	void main(void)
	{
		gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * in_Position;
		ex_Color = in_Color;
	}