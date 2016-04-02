#include "missil.h"

vec3 adjustmissil = vec3(-0.12, 0.25, 0);

missil::missil()
{
	this->inner = scenenode();
	this->inner.translate(adjustmissil);
	this->inner.scale(vec3(0.025, 0.025, 0.04));
	this->outer = scenenode();
	//this->outer.translate(vec3(2, -10, 0));
	this->outer.scale(vec3(0.05, 0.05, 0.05));
}

void missil::init()
{

}

void missil::setObj(obj obj)
{
	this->inner.setObj(obj);
	this->outer.setObj(obj);

	this->inner.load_data(obj);
	this->outer.load_data(obj);
}

void missil::setTexture(texture tex)
{
	this->inner.setTexture(tex);
	this->outer.setTexture(tex);

}

void missil::setShaders(shader * inner, shader * outer)
{
	this->inner.setShaderProgram(inner);
	this->outer.setShaderProgram(outer);
}

void missil::draw()
{
	glUseProgram((*this->inner.getShaderId()).getProgramId());
	this->inner.draw();
	glUseProgram((*this->outer.getShaderId()).getProgramId());
	this->outer.draw();
}

void missil::setPosition(vec3 p)
{
	this->position = p;

	this->inner.setTranslation(this->position);
	this->inner.translate(adjustmissil);

	this->outer.setTranslation(this->position);
}

void missil::setDirection(vec3 d)
{
	this->direction = d.normalize();
}

void missil::setSpeed(float s)
{
	this->speed = s;
}

vec3 missil::getPosition()
{
	return this->position;
}

vec3 missil::getDirection()
{
	return this->direction;
}

float missil::getSpeed()
{
	return this->speed;
}

void missil::translate(vec3 t)
{
	outer.translate(t);
	inner.translate(t);
}

void missil::update()
{
	this->translate(vec3(0,0,this->speed));
}

void missil::destroy()
{
	this->outer.destroy();
	this->inner.destroy();
}
