#version 330 core

//vertices, coordenadas textura, normais
layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec2 in_UV;
layout(location = 2) in vec3 in_Normal;

//materiais
layout(location = 3) in vec3 in_Ambient;
layout(location = 4) in vec3 in_Diffuse;
layout(location = 5) in vec3 in_Specular;
layout(location = 6) in float in_alfa; 

//posicao camera
uniform vec3 cameraPosition;
uniform vec3 lightPosition;

//direcao olho
out vec3 Eye_Direction_camera_space;
//direcao luz
out vec3 Light_Direction_camera_space;

out vec3 Normal_camera_space;

out vec3 Position_world_space;

//saida materiais
out vec3 materialAmbient;
out vec3 materialDiffuse;
out vec3 materialSpecular;
out float materialAlfa;

uniform mat4 ModelMatrix; 

// marble
out vec3 exPosition;
out vec3 exNormal;

out vec2 outUV;

//CAMERA 
/*uniform SharedMatrices
{
	mat4 ViewMatrix;
	mat4 ProjectionMatrix;
};*/

uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

void main(void)
{
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(in_Position, 1);
	
	Position_world_space = (ModelMatrix * vec4(in_Position, 1) ).xyz ;

	//vector desde vertice ate camera
	vec3 VertexPosition_camera_space = (ViewMatrix * ModelMatrix * vec4(in_Position, 1) ).xyz;
	Eye_Direction_camera_space = cameraPosition - VertexPosition_camera_space;

	//difusa
	vec3 Light_Position_camera_space = ( ViewMatrix * vec4(lightPosition, 1) ).xyz;
	Light_Direction_camera_space = Light_Position_camera_space + Eye_Direction_camera_space;


	Normal_camera_space = (ViewMatrix * ModelMatrix * vec4(in_Normal, 0)).xyz;

	//set materiais
	materialAmbient = in_Ambient;
	materialSpecular = in_Specular;
	materialDiffuse = in_Diffuse;
	materialAlfa = in_alfa;
	
	//marble
	exPosition = in_Position;
	exNormal = in_Normal;
	outUV = in_UV;
}