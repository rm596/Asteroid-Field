#version 330 core

//vertices de todas particulas
layout(location = 0) in vec3 squareVertices;

//posicao todas particulas e tamanho
layout(location = 1) in vec4 xyzs;

//cor todas particulas e alfa
layout(location = 2) in vec4 color; 

//coordenadas textura
layout(location = 3) in vec2 uv;

// Output data ; will be interpolated for each fragment.
out vec2 UV;
out vec4 particlecolor; 

uniform mat4 ModelMatrix; 
uniform float scale_factor;

//CAMERA 
/*uniform Camera
{
	mat4 ViewMatrix;
	mat4 ProjectionMatrix;
};*/

uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

void main(void)
{
	float particleSize = xyzs.w; // because we encoded it this way.
	vec3 particleCenter_wordspace = xyzs.xyz;

	mat4 Scale_Matrix;
	Scale_Matrix[0] = vec4(1, 0, 0, 0);
	Scale_Matrix[1] = vec4(0, 1, 0, 0);
	Scale_Matrix[2] = vec4(0, 0, scale_factor, 0);
	Scale_Matrix[3] = vec4(0, 0, 0, 1);

	vec3 vertexPosition_worldspace = particleCenter_wordspace + squareVertices * particleSize;
	
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * Scale_Matrix * vec4(vertexPosition_worldspace, 1.0f); 

	UV = uv;
	
	particlecolor = color;
}