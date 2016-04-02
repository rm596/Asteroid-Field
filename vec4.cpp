#include <iostream>
#include <cmath>

#include "vec4.h"

#define PI 3.14159265


vec4::vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w)
{
}

float vec4::get_x()
{
	return this->x;
}

float vec4::get_y()
{
	return this->y;
}

float vec4::get_z()
{
	return this->z;
}

float vec4::get_w()
{
	return this->w;
}

const void vec4::set_x(const float value)
{
	this->x = value;
}

const void vec4::set_y(const float value)
{
	this->y = value;
}

const void vec4::set_z(const float value)
{
	this->z = value;
}

const void vec4::set_w(const float value)
{
	this->w = value;
}

vec4 vec4::normalize()
{
	float s = 1 / (this->get_w() * sqrt(this->get_x() * this->get_x() + this->get_y() * this->get_y() + this->get_z() * this->get_z()));
	float x = this->get_x(), y = this->get_y(), z = this->get_z();
	return vec4(this->get_x() * s, this->get_y() * s, this->get_z() * s, 1.0f);
}

const bool vec4::vEqual(const vec4 & v1)
{
	return (fabs(this->x - v1.x) < vThreshold && fabs(this->y - v1.y) < vThreshold &&
		fabs(this->z - v1.z) < vThreshold && fabs(this->w - v1.w) < vThreshold);
}
//clean matrix
void vec4::clean()
{

}

const void vec4::println()
{
	std::cout << "<" << this->get_x() << ", " << this->get_y() << ", " << this->get_z() << ", " << this->get_w() << ">" << std::endl;
}