#version 330 core

	//vertices, coordenadas textura, normais
	layout(location = 0) in vec3 in_Position;
	layout(location = 1) in vec2 in_UV;
	layout(location = 2) in vec3 in_Normal;
	
	//materiais
	//layout(location = 3) in vec3 in_Ambient;
	//layout(location = 4) in vec3 in_Diffuse;
	//layout(location = 5) in vec3 in_Specular;
	//layout(location = 6) in float in_alfa; 
	
	out vec4 ex_Color;

	uniform mat4 ModelMatrix;
	uniform mat4 ViewMatrix;
	uniform	mat4 ProjectionMatrix;

	/*uniform SharedMatrices
	{
		mat4 ViewMatrix;
		mat4 ProjectionMatrix;
	};*/
	

	void main(void)
	{
		gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(in_Position, 1);
		ex_Color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	}