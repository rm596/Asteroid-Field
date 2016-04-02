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

// marble
uniform sampler3D NoiseTexture;
uniform sampler2D NoiseTexture2;
in vec3 exPosition;
in vec3 exNormal;

//granite
const vec3 baseColor = vec3(0.10, 0.10, 0.10);

//const vec3 MarbleColor = vec3(0.5,0.25,0.3);
//const vec3 VeinColor = vec3(0.85,0.7,0.75);

const vec3 MarbleColor = vec3(0.2,0.2,0.2);
const vec3 VeinColor = vec3(0.75,0.75,0.75);

const float NoiseFactor = 1.5;
const float PositionFactor = 10;
const float IntensityFactor = 14;

uniform mat4 ModelMatrix; 
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

out vec4 out_Color4;

//texturas
in vec2 outUV;
uniform sampler2D gSampler; //textura activa

void main(void)
{
	
/**/
	// noise 2d
	float noise = texture2D(NoiseTexture2, outUV).r * 0.5 + 0.5;

	float intensity = clamp(noise * NoiseFactor, 0.0, 1.0);
	intensity = cos(exPosition.x * PositionFactor + intensity * IntensityFactor) * 0.5 + 0.5;   
	vec3 color = mix(MarbleColor, VeinColor, intensity); 
/**/

	vec3 materialAmbientColor = vec3(0.1, 0.1, 0.1) * materialAmbient;

	float _distance = length(lightPosition - Position_world_space);

	vec3 n = normalize(Normal_camera_space);
	vec3 l = normalize(Light_Direction_camera_space);

	float cosTheta = clamp( dot(n, l), 0, 1 );


	vec3 E = normalize(Eye_Direction_camera_space);
	vec3 R = reflect(-l, n);

	float cosAlpha = clamp( dot(E, R), 0, 1 );

	//BLIN 
	float Blinn = 1;

	if(cosTheta > 0.0) {
		// BLINN SPECULAR TERM (using half-vector H)
		vec3 H = normalize(l + E);

		float NdotH = max(dot(n, H), 0.0);

		//valor baixo para GL_SHININESS
		float MaterialShininess = 3;

		//http://stackoverflow.com/questions/10264624/how-to-set-material-for-metallike-silver-in-opengl
		Blinn = pow(NdotH, MaterialShininess * 4.0);
	}

	//cor final
	vec3 out_Color3 = 
	materialAmbientColor * LightColor+ 
	materialDiffuse * LightColor * LightPower * cosTheta / (_distance * _distance) +
	materialSpecular * LightColor * Blinn * LightPower * pow(cosAlpha, 5) / (_distance * _distance);

	//light
	//out_Color4 = vec4( out_Color3, 1.0);
	//texture
	//out_Color4 = texture2D(gSampler, outUV);
	//light + texture
	out_Color4 = 0.5 * vec4( out_Color3, 1.0) + 0.5 * texture2D(gSampler, outUV);
	// marmore + light
	//out_Color4 = 0.5 * vec4( out_Color3, 1.0) + 0.5 * vec4(color, 1.0);
	//granito
	//out_Color4 = vec4(vec3(noise),1.0);
	// light + granito
	//out_Color4 = 0.1 * vec4(baseColor, 1.0) + 0.4 * vec4( out_Color3, 1.0) + 0.5 * vec4(vec3(noise),1.0);
	
/**/
}