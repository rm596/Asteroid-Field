#version 330 core

in vec3 materialAmbient;
in vec3 materialDiffuse;
in vec3 materialSpecular;
in float materialAlfa;

in vec3 Eye_Direction_camera_space;
in vec3 Light_Direction_camera_space;
in vec3 Normal_camera_space;
in vec3 Position_world_space;

//LUZ
uniform vec3 lightPosition;
uniform float LightPower;
uniform vec3 LightColor;


out vec4 out_Color4;

//texturas
in vec2 exTexcoord;
uniform sampler2D gSampler; //textura activa

void main(void)
{
	//minha atenuacao
	float _distance = length(lightPosition - Position_world_space);

	//componente ambiente
	vec3 materialAmbientColor = vec3(0.1, 0.1, 0.1) * materialAmbient;

	//componente difusa
	vec3 n = normalize(Normal_camera_space);
	vec3 l = normalize(Light_Direction_camera_space);
	//se a luz estiver debaixo, n*l vai ser negativo, loco usamos clamp
	//intensidade
	float cosTheta = clamp( dot(n, l), 0, 1 );

	//componente especular
	vec3 E = normalize(Eye_Direction_camera_space);
	vec3 R = reflect(-l, n);
	//se a luz estiver debaixo, n*l vai ser negativo, loco usamos clamp
	//intensidade
	float cosAlpha = clamp( dot(E, R), 0, 1 );

	//BLIN 
	float Blinn = 1;

	if(cosTheta > 0.0) {
		// BLINN SPECULAR TERM (using half-vector H)
		vec3 H = normalize(l + E);

		float NdotH = max(dot(n, H), 0.0);

		//valor baixo para GL_SHININESS
		float MaterialShininess = 3;

		Blinn = pow(NdotH, MaterialShininess * 4.0);
	}
 
	//cor final
	vec3 out_Color3 = 
	materialAmbientColor * LightColor + 
	materialDiffuse * LightColor * LightPower * cosTheta / (_distance * _distance) +
	materialSpecular * LightColor * Blinn * LightPower * pow(cosAlpha, 5) / (_distance * _distance);


	float noise = 1;
	if(texture(gSampler, exTexcoord).r < 0.5 && texture(gSampler, exTexcoord).g < 0.5 && texture(gSampler, exTexcoord).b < 0.5)     
	{
		noise = texture(gSampler, exTexcoord).r * 0.25;
		out_Color4 = vec4(vec3(noise), 1.0) + vec4( out_Color3, 1.0) * 0.8;
		out_Color4.a = materialAlfa;


	} else {
		//transparencia para vidro
		out_Color4 = vec4( out_Color3, 1.0); 	
		out_Color4.a = materialAlfa;
	}

}