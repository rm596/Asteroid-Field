#include "qtrn.h"

#define DEGREESTORADIANS 0.0174532925

qtrn::qtrn() {

	this->t = 1.0f;
	this->v = vec3(0, 0, 0);
}

qtrn::qtrn(float angle, vec3 axis)
{
	float angle_deg = angle * DEGREESTORADIANS;

	/*printf("angle: %f\n",angle_deg);
	printf("axis:\n");
	axis.println();
	printf("\n");

	printf("cos: %f\n", cosf(angle_deg / 2.0f));
	printf("sen: %f\n", sinf(angle_deg / 2.0f));

	printf("v: \n");
	(axis * sinf(angle_deg / 2.0f)).println();*/

	this->t = cosf(angle_deg / 2.0f);
	this->v = axis * sinf(angle_deg / 2.0f);

}



void qtrn::setT(float t)
{
	this->t = t;
}

void qtrn::setV(vec3 v)
{
	this->v = v;
}

void qtrn::print()
{
	printf("%.2f + %.2fi + %.2fj + %.2fk\n", this->t, this->v.X(), this->v.Y(), this->v.Z());
}

void qtrn::printMatrix()
{

}

float qtrn::norm()
{
	return sqrtf(this->t*this->t + this->v.X()*this->v.X() + this->v.Y()*this->v.Y() + this->v.Z()*this->v.Z());
}

void qtrn::Normalize()
{
	float normInv = 1 / this->norm();

	this->t * normInv;
	this->v * normInv;
}

qtrn qtrn::Normalized()
{
	float normInv = 1 / this->norm();

	//return this->copy(this->t * normInv, this->v * normInv);

	qtrn res = qtrn();
	res.setT(this->t * normInv);
	res.setV(this->v * normInv);

	return res;
}

float qtrn::getT()
{
	return this->t;
}

vec3 qtrn::getV()
{
	return this->v;
}

mat3 qtrn::getAsMatrix3()
{
	float x = this->v.X();
	float y = this->v.Y();
	float z = this->v.Z();

	return mat3(
		1.0f - 2 * y*y - 2 * z*z, 2 * x*y + 2 * t*z, 2 * x*z - 2 * t*y,
		2 * x*y - 2 * t*z, 1 - 2 * x*x - 2 * z*z, 2 * y*z + 2 * t*x,
		2 * x*z + 2 * t*y, 2 * y*z - 2 * t*x, 1 - 2 * x*x - 2 * y*y
		);
}

mat4 qtrn::getAsMatrix4()
{
	float x = this->v.X();
	float y = this->v.Y();
	float z = this->v.Z();

	return mat4(
		1.0f - 2 * y*y - 2 * z*z, 2 * x*y + 2 * t*z, 2 * x*z - 2 * t*y, 0.0f,
		2 * x*y - 2 * t*z, 1 - 2 * x*x - 2 * z*z, 2 * y*z + 2 * t*x, 0.0f,
		2 * x*z + 2 * t*y, 2 * y*z - 2 * t*x, 1 - 2 * x*x - 2 * y*y, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
		);
}

float qtrn::getAngle()
{
	float cos = acosf(this->t);

	return 2 * cos;
}

float qtrn::getAngleDegrees()
{
	return this->getAngle() / DEGREESTORADIANS;
}

vec3 qtrn::getAxis()
{
	float angle = this->getAngle();

	if (angle == 0)
		return vec3(1.0f, 0.0f, 0.0f);

	return this->v*(1 / sqrt(1 - this->t*this->t));
}

qtrn qtrn::operator+(qtrn q)
{
	qtrn res = qtrn();

	res.setT(this->t + q.getT());
	res.setV(this->v + q.getV());

	return q;
}

void qtrn::operator+=(qtrn q)
{
	this->t += q.getT();
	this->v += q.getV();
}

qtrn qtrn::operator-(qtrn q)
{
	qtrn res = qtrn();

	res.setT(this->t - q.getT());
	res.setV(this->v - q.getV());

	return q;
}

void qtrn::operator-=(qtrn q)
{
	this->t -= q.getT();
	this->v -= q.getV();
}

qtrn qtrn::operator*(float e)
{
	qtrn q = qtrn();
	q.setT(this->t*e);
	q.setV(this->v*e);

	return q;
}

void qtrn::operator*=(float e)
{
	this->t *= e;
	this->v *= e;
}

qtrn qtrn::operator*(qtrn q)
{
	qtrn res = qtrn();

	res.setT(this->t*q.getT() - this->v.dot(q.getV()));
	res.setV(this->t*q.getV() + q.getT()*this->v + this->v.cross(q.getV()));

	return res;
}

void qtrn::operator*=(qtrn q)
{
	float t = this->t;
	float x = this->v.X();
	float y = this->v.Y();
	float z = this->v.Z();

	/*this->t = this->t*q.getT() - this->v.innerProduct(q.getV());
	this->v = this->t*q.getV() + q.getT()*this->v + this->v.outerProduct(q.getV());*/

	this->t = t * q.getT() - x * q.getV().X() - y * q.getV().Y() - z * q.getV().Z();

	this->v = vec3(
		t * q.getV().X() + x * q.getT() + y * q.getV().Z() - z * q.getV().Y(),
		t * q.getV().Y() + y * q.getT() + z * q.getV().X() - x * q.getV().Z(),
		t * q.getV().Z() + z * q.getT() + x * q.getV().Y() - y * q.getV().X()
		);

}


qtrn operator* (float e, qtrn q)
{
	return q * e;
}

qtrn qtrn::conjugate()
{
	qtrn q = qtrn();
	q.setT(this->t);
	q.setV(-this->v);

	return q;
}