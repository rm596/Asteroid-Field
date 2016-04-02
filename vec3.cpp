#include <iostream>
#include <cmath>

#include "vec3.h"

#define PI 3.14159265

using namespace std;

/*
construtor vazio
*/
vec3::vec3() : x(0), y(0), z(0) {}

/*
construtor
*/
vec3::vec3(float xx, float yy, float zz) : x(xx), y(yy), z(zz) {}

/*
copia 2d
*/
vec3::vec3(const vec3& copia) :
x(copia.x),
y(copia.y),
z(copia.z)
{}

/*
componente x
*/
float vec3::X() const
{
	return this->x;
}

/*
componente y
*/
float vec3::Y() const
{
	return this->y;
}

/*
componente z
*/
float vec3::Z() const
{
	return this->z;
}

float vec3::_x(void)
{
	return this->x;
}

float vec3::_y(void)
{
	return this->y;
}

float vec3::_z(void)
{
	return this->z;
}

/*
set componente x
*/
void vec3::setX(float xx)
{
	this->x = xx;
}

/*
set componente x
*/
void vec3::setY(float yy)
{
	this->y = yy;
}

/*
set componente z
*/
void vec3::setZ(float zz)
{
	this->z = zz;
}

/*
vectores iguais
*/
bool vec3::operator== (const vec3& other) const
{
	return x == other.x && y == other.y && z == other.z;
}

/*
vectores diferentes
*/
bool vec3::operator!= (const vec3& other) const
{
	return x != other.x && y != other.y && z != other.z;
}

/*
soma 2 vectores
*/
vec3 vec3::operator+ (const vec3 & other)
{
	vec3 vector;

	vector.setX(x + other.X());
	vector.setY(y + other.Y());
	vector.setZ(z + other.Z());

	return vector;
}

/*
soma 2 vectores void
*/
void vec3::operator+= (const vec3 & other)
{
	this->setX(x + other.X());
	this->setY(y + other.Y());
	this->setZ(z + other.Z());
}

vec3 vec3::operator+ (const float n)
{
	vec3 vector;

	vector.setX(x + n);
	vector.setY(y + n);
	vector.setZ(z + n);

	return vector;
}

vec3 vec3::operator- (const float n)
{
	vec3 vector;

	vector.setX(x - n);
	vector.setY(y - n);
	vector.setZ(z - n);

	return vector;
}

vec3 vec3::operator* (const float n)
{
	vec3 vector;

	vector.setX(x * n);
	vector.setY(y * n);
	vector.setZ(z * n);

	return vector;
}

void vec3::operator*= (const float n)
{
	this->setX(x * n);
	this->setY(y * n);
	this->setZ(z * n);
}

/*
subtracao 2 vectores
*/
vec3 vec3::operator- (const vec3 & other)
{
	vec3 vector;

	vector.setX(x - other.X());
	vector.setY(y - other.Y());
	vector.setZ(z - other.Z());

	return vector;
}

/*
subtracao 2 vectores set
*/
void vec3::operator-= (const vec3 & other)
{
	this->setX(x - other.X());
	this->setY(y - other.Y());
	this->setZ(z - other.Z());
}

/*
multiplicacao 2 vectores
*/
vec3 vec3::operator* (const vec3 & other)
{
	vec3 vector;

	vector.setX(x * other.X());
	vector.setY(y * other.Y());
	vector.setZ(z * other.Z());

	return vector;
}

/*
multiplicacao 2 vectores set
*/
void vec3::operator*= (const vec3 & other)
{
	this->setX(x * other.X());
	this->setY(y * other.Y());
	this->setZ(z * other.Z());
}

/*
norma de um vector 3d
*/
float vec3::length(void) const
{
	return sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
}

/*
distancia vectores
*/
float vec3::distance(const vec3 & other)
{
	return sqrt(abs(pow(this->X() - other.X(), 2)) + (pow(this->Y() - other.Y(), 2)) + (pow(this->Z() - other.Z(), 2)));
}

/*
produto interno
*/
float vec3::dot(const vec3 & other)
{
	return x * other.X() + y * other.Y() + z * other.Z();
}

/*
produto externo
3d
*/
vec3 vec3::cross(const vec3 & other)
{
	//i
	float i = this->y * other.Z() - other.Y() * this->Z();
	//negativo j 
	float j = this->x * other.Z() - other.X() * this->Z();
	//k
	float k = this->x * other.Y() - other.X() * this->y;

	return vec3(i, -j, k);
}

/*
normalizacao 3d
*/
vec3 vec3::normalize(void)
{
	vec3 vector;

	float norma = this->length();

	vector.setX(x / norma);
	vector.setY(y / norma);
	vector.setZ(z / norma);

	return vector;
}

/*
angulo entre 2 vectores em graus
3d
*/
float vec3::angle(const vec3 & other)
{
	//dot product
	float prod_escalar = this->dot(other);

	//norma 1
	float norma1 = this->length();

	//norma 2
	float norma2 = other.length();

	float param = prod_escalar / (norma1 * norma2);

	return acos(param) * 180.0 / PI;
}

void vec3::println()
{
	cout << "<" << x << ", " << y << ", " << z << ">" << endl;
}

/*
numero vezes vector
*/
vec3 operator* (float n, const vec3 & other)
{
	vec3 result(n * other.X(), n * other.Y(), n * other.Z());
	return result;
}

/*
negativo da vector
*/
vec3 operator- (const vec3 & other)
{
	vec3 result(-1 * other.X(), -1 * other.Y(), -1 * other.Z());
	return result;
}

