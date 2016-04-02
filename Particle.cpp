#include <iostream>
#include "Particle.h"

using namespace std;

particle::particle()
{
	this->life = 1.0f;  
	this->size = 0.8;    
	this->distance = rand() % 256;  
}

float particle::getDistance()
{ 
	return this->distance;  
}

float particle::getLife() 
{
	return this->life;
}

vec3 particle::getPosition()
{
	return this->position;
}

float particle::getSize()
{
	return this->size;
}

//CORES
float particle::getR()
{
	return this->r;
}

float particle::getG()
{
	return this->g;
}

float particle::getB()
{
	return this->b;
}

float particle::getA()
{
	return this->a;
}

void particle::setLife(float _life)
{
	this->life = _life;
}

void particle::setPosition(const vec3 & p)
{
	this->position = p;
}

void particle::setColor(float _r, float _g, float _b, float _a)
{
	this->r = _r;
	this->g = _g; 
	this->b = _b;
	this->a = _a;
}

void particle::setSize(float _size)
{
	this->size = _size;
}

void particle::setDistance(float _distance)
{
	this->distance = _distance;
}

bool particle::operator<(const particle & _particle)
{
	return this->distance > _particle.distance;
}
