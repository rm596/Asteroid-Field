#include <iostream>
#include <cmath>

#include "vec2.h"

#define PI 3.14159265

using namespace std;

/*
construtor vazio
*/
vec2::vec2() : x(0), y(0) {
	//cout << "entrei inicial tudo zero" << endl;
	//cout << "valor de x: " << x << " valor de y:  " << y << endl;
}

/*
construtor
*/
vec2::vec2(float xx, float yy) : x(xx), y(yy) {
	//cout << "entrei inicial tudo preenhido" << endl;
	//cout << "valor de x: " << x << " valor de y:  " << y << endl;
}

/*
copia 2d
*/
vec2::vec2(const vec2& copia) :
x(copia.x),
y(copia.y)
{
	//cout << "entrei copia" << endl;
	//cout << "valor de x: " << x << " valor de y:  " << y << endl;
}

/*
componente x
*/
float vec2::X() const
{
	return this->x;
}

/*
componente y
*/
float vec2::Y() const
{
	return this->y;
}

/*
set componente x
*/
void vec2::setX(float xx)
{
	this->x = xx;
}

/*
set componente x
*/
void vec2::setY(float yy)
{
	this->y = yy;
}

/*
vectores iguais
*/
bool vec2::operator== (const vec2& other) const
{
	return x == other.x && y == other.y;
}

/*
soma 2 vectores
*/
vec2 vec2::operator+ (const vec2 & other)
{
	vec2 vector;

	vector.setX(x + other.X());
	vector.setY(y + other.Y());

	return vector;
}

/*
soma 2 vectores com set
*/
void vec2::operator+= (const vec2 & other)
{
	this->setX(x + other.X());
	this->setY(y + other.Y());
}

vec2 vec2::operator+ (float n)
{
	vec2 vector;

	vector.setX(x + n);
	vector.setY(y + n);

	return vector;
}

/*
subtracao 2 vectores
*/
vec2 vec2::operator- (const vec2 & other)
{
	vec2 vector;

	vector.setX(x - other.X());
	vector.setY(y - other.Y());

	return vector;
}

/*
subtracao 2 vectores com set
*/
void vec2::operator-= (const vec2 & other)
{
	this->setX(x - other.X());
	this->setY(y - other.Y());
}

vec2 vec2::operator- (float n)
{
	vec2 vector;

	vector.setX(x - n);
	vector.setY(y - n);

	return vector;
}

/*
multiplicacao 2 vectores
*/
vec2 vec2::operator* (const vec2 & other)
{
	vec2 vector;

	vector.setX(x * other.X());
	vector.setY(y * other.Y());

	return vector;
}

/*
multiplicacao 2 vectores set
*/
void vec2::operator*= (const vec2 & other)
{
	this->setX(x * other.X());
	this->setY(y * other.Y());
}

vec2 vec2::operator* (float n)
{
	vec2 vector;

	vector.setX(x * n);
	vector.setY(y * n);

	return vector;
}

void vec2::operator*= (float n)
{
	this->x *= n;
	this->y *= n;
}

/*
norma de um vector 2d
*/
float vec2::length(void) const
{
	return sqrt(pow(this->x, 2) + pow(this->y, 2));
}

/*
distancia vectores
*/
float vec2::distance(const vec2 & other)
{
	return sqrt(abs(pow(this->X() - other.X(), 2)) + (pow(this->Y() - other.Y(), 2)));
}

/*
produto interno
*/
float vec2::dot(const vec2 & other)
{
	return x * other.X() + y * other.Y();
}

/*
produto externo
2d
*/
float vec2::cross(const vec2 & other)
{
	//igual ao determinante de this * other
	return this->x * other.Y() - other.X() * this->y;
}

/*
normalizacao 2d
*/
vec2 vec2::normalize(void)
{
	vec2 vector;

	float norma = this->length();

	vector.setX(x / norma);
	vector.setY(y / norma);

	return vector;
}

/*
angulo entre 2 vectores em graus
2d
*/
float vec2::angle(const vec2 & other)
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

void vec2::println()
{
	cout << "<" << x << ", " << y << ">" << endl;
}

vec2 operator* (float n, const vec2 & other)
{
	vec2 result(n * other.X(), n * other.Y());
	return result;
}

vec2 operator- (const vec2 & other)
{
	vec2 result(-1 * other.X(), -1 * other.Y());
	return result;
}


/*
CONVERSAO ANGULOS RADIANOS
*/
float degrees(float radians)
{
	return (radians * 180) / PI;
}

float radians(float degrees)
{
	return degrees * (PI / 180);
}