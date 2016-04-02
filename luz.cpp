#include "luz.h"

luz::luz(){}

luz::luz(vec3 pos, float red, float green, float blue)
{
	this->setColor(red, green, blue);
	this->setPosition(pos);
}

void luz::setColor(float red, float green, float blue)
{
	this->setRed(red);
	this->setGreen(green);
	this->setBlue(blue);
}

void luz::setRed(float color)
{
	this->cor[0] = color;
}

void luz::setGreen(float color)
{
	this->cor[1] = color;
}

void luz::setBlue(float color)
{
	this->cor[2] = color;
}

void luz::setPosition(vec3 pos)
{
	this->posicao = pos;
}

float* luz::getColor()
{
	return this->cor;
}

vec3 luz::getPosition()
{
	return this->posicao;
}

float* luz::getPositionArray()
{
	float temp[3];

	temp[0] = this->posicao.X();
	temp[1] = this->posicao.Y();
	temp[2] = this->posicao.Z();

	return temp;
}

float luz::getPotencia()
{
	return this->potencia;
}

void luz::setPotencia(float p)
{
	this->potencia = p;
}

void luz::setCamera(camera* c)
{
	this->main_camera = c;
}

float* luz::getCameraPosition()
{
	return (*this->main_camera).getEyeArray();
}