#ifndef _H_LUZ
#define _H_LUZ

#include "vec3.h"
#include "camera.h"

class luz
{
private:
	vec3 posicao;
	float cor[3]; // RGB
	float potencia = 0.0f;
	camera * main_camera; // camera to use the position

public:
	// construtores
	luz();
	luz(vec3 pos, float red, float green, float blue);

	// set color functions
	void setColor(float red, float green, float blue);
	void setRed(float color);
	void setGreen(float color);
	void setBlue(float color);

	//sets position
	void setPosition(vec3 pos);

	//sets potency
	void setPotencia(float p);

	//sets main camera
	void setCamera(camera* c);

	// get functions
	float* getColor();
	vec3 getPosition();
	float* getPositionArray();
	float getPotencia();
	float* getCameraPosition();
};

#endif