#pragma once

#include <iostream>
#include <math.h>
#include "vec3.h"
#include "mat3.h"
#include "mat4.h"

class qtrn
{
private:
	/*
	q = t + xi +yj + zk
	q = (t,v), v = (x,y,z)
	*/
	float t;
	vec3 v;

	/* returns a copy of current object */
	//Quaternion copy(float t, Vector3 v);

	void setT(float t);
	void setV(vec3 v);

public:
	/* constructors */
	qtrn();

	qtrn(float angle, vec3 axis);

	/* print quaternion */
	void print();
	void printMatrix();

	/* norm of the object */
	float norm();

	/* normalization */
	void Normalize();
	qtrn Normalized();

	/* get methods */
	float getT();
	vec3 getV();
	mat3 getAsMatrix3();
	mat4 getAsMatrix4();

	float getAngle();
	float getAngleDegrees();
	vec3 getAxis();

	/* Addition */
	qtrn operator+(qtrn q);
	void operator+=(qtrn q);

	/* Subtraction */
	qtrn operator-(qtrn q);
	void operator-=(qtrn q);

	/* multiply by number */
	qtrn operator*(float e);
	void operator*=(float e);

	/* Multiplication */
	qtrn operator*(qtrn q);
	void operator*=(qtrn q);

	/* Conjugate */
	qtrn conjugate();
};

qtrn operator* (float e, qtrn q);
