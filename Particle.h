#ifndef _PARTICLE
#define _PARTICLE

#include "vec3.h"

class particle
{
private:
	//posicao
	vec3 position;

	//cor
	float r, g, b, a;

	//tamanho
	float size; 

	//vida
	float life;

	//distancia, para efeitos blending
	float distance;

public:
	//construtor
	particle();

	//GETS
	vec3 getPosition();
	float getDistance();
	float getLife();
	float getSize();

	//get componentes cor
	float getR();
	float getG();
	float getB();
	float getA();

	//SETS
	void setLife(float _life);
	void setPosition(const vec3 & p);
	void setColor(float r, float g, float b, float a);
	void setSize(float size);
	void setDistance(float _distance);

	//para ordenar
	bool operator<(const particle & _particle);
};
#endif
