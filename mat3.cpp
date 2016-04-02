#include <iostream>
#include <cmath>

#include "mat3.h"
#include <iomanip>

//TODO: SUBSTITUIR POR float matrix[9];

using namespace std;

//COLUMN MAJOR
/*
construtor por numero
*/
mat3::mat3(float x) : matrix()
{
	matrix[0][0] = x; matrix[0][1] = 0.0f;  matrix[0][2] = 0.0f;
	matrix[1][0] = 0.0f; matrix[1][1] = x;  matrix[1][2] = 0.0f;
	matrix[2][0] = 0.0f; matrix[2][1] = 0.0f;  matrix[2][2] = x;
}

/*
construtor
*/
mat3::mat3(float x1, float x2, float x3, float x4, float x5, float x6, float x7, float x8, float x9)
{
	matrix[0][0] = x1; matrix[0][1] = x4;  matrix[0][2] = x7;
	matrix[1][0] = x2; matrix[1][1] = x5;  matrix[1][2] = x8;
	matrix[2][0] = x3; matrix[2][1] = x6;  matrix[2][2] = x9;
}

/*
construtor
*/
mat3::mat3(float data[9])
{
	matrix[0][0] = data[0]; matrix[0][1] = data[3];  matrix[0][2] = data[6];
	matrix[1][0] = data[1]; matrix[1][1] = data[4];  matrix[1][2] = data[7];
	matrix[2][0] = data[2]; matrix[2][1] = data[5];  matrix[2][2] = data[8];
}

/*
construtor vec3
*/
mat3::mat3(const vec3 & column1, const vec3 & column2, const vec3 & column3)
{
	matrix[0][0] = column1.X(); matrix[0][1] = column2.X();  matrix[0][2] = column3.X();
	matrix[1][0] = column1.Y(); matrix[1][1] = column2.Y();  matrix[1][2] = column3.Y();
	matrix[2][0] = column1.Z(); matrix[2][1] = column2.Z();  matrix[2][2] = column3.Z();
}

/*
set na posicao do valor
*/
void mat3::set(int y, int x, float value)
{
	matrix[y][x] = value;
}

/*
set por array
*/
void mat3::set(const float matrix[])
{
	this->set(0, 0, matrix[0]);
	this->set(0, 1, matrix[3]);
	this->set(0, 2, matrix[6]);

	this->set(1, 0, matrix[1]);
	this->set(1, 1, matrix[4]);
	this->set(1, 2, matrix[7]);

	this->set(2, 0, matrix[2]);
	this->set(2, 1, matrix[5]);
	this->set(2, 2, matrix[8]);
}

/*
set linha matriz por array
*/
void mat3::setRow(int row, const float matrix[])
{
	this->set(row, 0, matrix[0]);
	this->set(row, 1, matrix[1]);
	this->set(row, 2, matrix[2]);
}

/*
set linha matriz por array
*/
void mat3::setRow(int row, const vec3 & _row)
{
	this->set(row, 0, _row.X());
	this->set(row, 1, _row.Y());
	this->set(row, 2, _row.Z());
}

/*
set coluna matriz por array
*/
void mat3::setColumn(int column, const float matrix[])
{
	this->set(0, column, matrix[0]);
	this->set(1, column, matrix[1]);
	this->set(2, column, matrix[2]);
}

/*
set coluna matriz por array
*/
void mat3::setColumn(int column, const vec3 & _column)
{
	this->set(0, column, _column.X());
	this->set(1, column, _column.Y());
	this->set(2, column, _column.Z());
}

/*
copiar matriz
*/
void mat3::operator=(const mat3 & other)
{
	this->set(0, 0, other.get(0, 0));
	this->set(0, 1, other.get(0, 1));
	this->set(0, 2, other.get(0, 2));

	this->set(1, 0, other.get(1, 0));
	this->set(1, 1, other.get(1, 1));
	this->set(1, 2, other.get(1, 2));

	this->set(2, 0, other.get(2, 0));
	this->set(2, 1, other.get(2, 1));
	this->set(2, 2, other.get(2, 2));
}

//OPERADORES ENTRE MATRIZES
mat3 mat3::operator+(const mat3 & other)
{
	mat3 result(0.0f);
	result.set(0, 0, this->get(0, 0) + other.get(0, 0));
	result.set(0, 1, this->get(0, 1) + other.get(0, 1));
	result.set(0, 2, this->get(0, 2) + other.get(0, 2));

	result.set(1, 0, this->get(1, 0) + other.get(1, 0));
	result.set(1, 1, this->get(1, 1) + other.get(1, 1));
	result.set(1, 2, this->get(1, 2) + other.get(1, 2));

	result.set(2, 0, this->get(2, 0) + other.get(2, 0));
	result.set(2, 1, this->get(2, 1) + other.get(2, 1));
	result.set(2, 2, this->get(2, 2) + other.get(2, 2));
	return result;
}

void mat3::operator+=(const mat3 & other)
{
	this->set(0, 0, this->get(0, 0) + other.get(0, 0));
	this->set(0, 1, this->get(0, 1) + other.get(0, 1));
	this->set(0, 2, this->get(0, 2) + other.get(0, 2));

	this->set(1, 0, this->get(1, 0) + other.get(1, 0));
	this->set(1, 1, this->get(1, 1) + other.get(1, 1));
	this->set(1, 2, this->get(1, 2) + other.get(1, 2));

	this->set(2, 0, this->get(2, 0) + other.get(2, 0));
	this->set(2, 1, this->get(2, 1) + other.get(2, 1));
	this->set(2, 2, this->get(2, 2) + other.get(2, 2));
}

mat3 mat3::operator-(const mat3 & other)
{
	mat3 result(0.0f);
	result.set(0, 0, this->get(0, 0) - other.get(0, 0));
	result.set(0, 1, this->get(0, 1) - other.get(0, 1));
	result.set(0, 2, this->get(0, 2) - other.get(0, 2));

	result.set(1, 0, this->get(1, 0) - other.get(1, 0));
	result.set(1, 1, this->get(1, 1) - other.get(1, 1));
	result.set(1, 2, this->get(1, 2) - other.get(1, 2));

	result.set(2, 0, this->get(2, 0) - other.get(2, 0));
	result.set(2, 1, this->get(2, 1) - other.get(2, 1));
	result.set(2, 2, this->get(2, 2) - other.get(2, 2));
	return result;
}

void mat3::operator-=(const mat3 & other)
{
	this->set(0, 0, this->get(0, 0) - other.get(0, 0));
	this->set(0, 1, this->get(0, 1) - other.get(0, 1));
	this->set(0, 2, this->get(0, 2) - other.get(0, 2));

	this->set(1, 0, this->get(1, 0) - other.get(1, 0));
	this->set(1, 1, this->get(1, 1) - other.get(1, 1));
	this->set(1, 2, this->get(1, 2) - other.get(1, 2));

	this->set(2, 0, this->get(2, 0) - other.get(2, 0));
	this->set(2, 1, this->get(2, 1) - other.get(2, 1));
	this->set(2, 2, this->get(2, 2) - other.get(2, 2));
}

mat3 mat3::operator*(const mat3 & other)
{
	mat3 result(0.0f);

	result.set(0, 0, this->get(0, 0) * other.get(0, 0) + this->get(0, 1) * other.get(1, 0) + this->get(0, 2) * other.get(2, 0));
	result.set(0, 1, this->get(0, 0) * other.get(0, 1) + this->get(0, 1) * other.get(1, 1) + this->get(0, 2) * other.get(2, 1));
	result.set(0, 2, this->get(0, 0) * other.get(0, 2) + this->get(0, 1) * other.get(1, 2) + this->get(0, 2) * other.get(2, 2));

	result.set(1, 0, this->get(1, 0) * other.get(0, 0) + this->get(1, 1) * other.get(1, 0) + this->get(1, 2) * other.get(2, 0));
	result.set(1, 1, this->get(1, 0) * other.get(0, 1) + this->get(1, 1) * other.get(1, 1) + this->get(1, 2) * other.get(2, 1));
	result.set(1, 2, this->get(1, 0) * other.get(0, 2) + this->get(1, 1) * other.get(1, 2) + this->get(1, 2) * other.get(2, 2));

	result.set(2, 0, this->get(2, 0) * other.get(0, 0) + this->get(2, 1) * other.get(1, 0) + this->get(2, 2) * other.get(2, 0));
	result.set(2, 1, this->get(2, 0) * other.get(0, 1) + this->get(2, 1) * other.get(1, 1) + this->get(2, 2) * other.get(2, 1));
	result.set(2, 2, this->get(2, 0) * other.get(0, 2) + this->get(2, 1) * other.get(1, 2) + this->get(2, 2) * other.get(2, 2));

	return result;
}

mat3 mat3::operator*(const float n)
{
	mat3 result(1);

	result.set(0, 0, this->get(0, 0) * n);
	result.set(0, 1, this->get(0, 1) * n);
	result.set(0, 2, this->get(0, 2) * n);

	result.set(1, 0, this->get(1, 0) * n);
	result.set(1, 1, this->get(1, 1) * n);
	result.set(1, 2, this->get(1, 2) * n);

	result.set(2, 0, this->get(2, 0) * n);
	result.set(2, 1, this->get(2, 1) * n);
	result.set(2, 2, this->get(2, 2) * n);
	return result;
}

void mat3::operator*=(const float n)
{
	this->set(0, 0, this->get(0, 0) * n);
	this->set(0, 1, this->get(0, 1) * n);
	this->set(0, 2, this->get(0, 2) * n);

	this->set(1, 0, this->get(1, 0) * n);
	this->set(1, 1, this->get(1, 1) * n);
	this->set(1, 2, this->get(1, 2) * n);

	this->set(2, 0, this->get(2, 0) * n);
	this->set(2, 1, this->get(2, 1) * n);
	this->set(2, 2, this->get(2, 2) * n);
}

void mat3::operator*=(const mat3 & other)
{
	mat3 copy1 = this->get();

	this->set(0, 0, copy1.get(0, 0) * other.get(0, 0) + copy1.get(0, 1) * other.get(1, 0) + copy1.get(0, 2) * other.get(2, 0));
	this->set(0, 1, copy1.get(0, 0) * other.get(0, 1) + copy1.get(0, 1) * other.get(1, 1) + copy1.get(0, 2) * other.get(2, 1));
	this->set(0, 2, copy1.get(0, 0) * other.get(0, 2) + copy1.get(0, 1) * other.get(1, 2) + copy1.get(0, 2) * other.get(2, 2));

	this->set(1, 0, copy1.get(1, 0) * other.get(0, 0) + copy1.get(1, 1) * other.get(1, 0) + copy1.get(1, 2) * other.get(2, 0));
	this->set(1, 1, copy1.get(1, 0) * other.get(0, 1) + copy1.get(1, 1) * other.get(1, 1) + copy1.get(1, 2) * other.get(2, 1));
	this->set(1, 2, copy1.get(1, 0) * other.get(0, 2) + copy1.get(1, 1) * other.get(1, 2) + copy1.get(1, 2) * other.get(2, 2));

	this->set(2, 0, copy1.get(2, 0) * other.get(0, 0) + copy1.get(2, 1) * other.get(1, 0) + copy1.get(2, 2) * other.get(2, 0));
	this->set(2, 1, copy1.get(2, 0) * other.get(0, 1) + copy1.get(2, 1) * other.get(1, 1) + copy1.get(2, 2) * other.get(2, 1));
	this->set(2, 2, copy1.get(2, 0) * other.get(0, 2) + copy1.get(2, 1) * other.get(1, 2) + copy1.get(2, 2) * other.get(2, 2));
}

/*
get na posicao
*/
float mat3::get(int y, int x) const
{
	return matrix[y][x];
}

/*
get this
*/
mat3 & mat3::get()
{
	return *this;
}

/*
matrix identidade
*/
void mat3::identity()
{
	this->set(0, 0, 1);
	this->set(0, 1, 0);
	this->set(0, 2, 0);

	this->set(1, 0, 0);
	this->set(1, 1, 1);
	this->set(1, 2, 0);

	this->set(2, 0, 0);
	this->set(2, 1, 0);
	this->set(2, 2, 1);
}

/*
transposta matrix
*/
mat3 mat3::transpose()
{
	mat3 result(0.0f);

	result.set(0, 0, this->get(0, 0));
	result.set(0, 1, this->get(1, 0));
	result.set(0, 2, this->get(2, 0));

	result.set(1, 0, this->get(0, 1));
	result.set(1, 1, this->get(1, 1));
	result.set(1, 2, this->get(2, 1));

	result.set(2, 0, this->get(0, 2));
	result.set(2, 1, this->get(1, 2));
	result.set(2, 2, this->get(2, 2));
	return result;
}

/*
determinante matrix
*/
float mat3::determinant()
{
	return this->get(0, 0) * (this->get(1, 1) * this->get(2, 2) - this->get(1, 2) * this->get(2, 1))
		- this->get(0, 1) * (this->get(1, 0) * this->get(2, 2) - this->get(1, 2) * this->get(2, 0))
		+ this->get(0, 2) * (this->get(1, 0) * this->get(2, 1) - this->get(1, 1) * this->get(2, 0));
}

/*
inversa matrix
*/
mat3 mat3::inverse()
{
	float determinant = this->determinant();

	mat3 transpose = this->transpose();

	float m11, m12, m13, m21, m22, m23, m31, m32, m33;

	m11 = transpose.get(1, 1) * transpose.get(2, 2) - transpose.get(2, 1) * transpose.get(1, 2);
	m12 = transpose.get(1, 0) * transpose.get(2, 2) - transpose.get(2, 0) * transpose.get(1, 2);
	m13 = transpose.get(1, 0) * transpose.get(2, 1) - transpose.get(2, 0) * transpose.get(1, 1);

	m21 = transpose.get(0, 1) * transpose.get(2, 2) - transpose.get(2, 1) * transpose.get(0, 2);
	m22 = transpose.get(0, 0) * transpose.get(2, 2) - transpose.get(2, 0) * transpose.get(0, 2);
	m23 = transpose.get(0, 0) * transpose.get(2, 1) - transpose.get(2, 0) * transpose.get(0, 1);

	m31 = transpose.get(0, 1) * transpose.get(1, 2) - transpose.get(1, 1) * transpose.get(0, 2);
	m32 = transpose.get(0, 0) * transpose.get(1, 2) - transpose.get(1, 0) * transpose.get(0, 2);
	m33 = transpose.get(0, 0) * transpose.get(1, 1) - transpose.get(1, 0) * transpose.get(0, 1);

	float adj[] = { m11, -1 * m12, m13, -1 * m21, m22, -1 * m23, m31, -1 * m32, m33 };

	mat3 mt(adj);

	if (determinant == 0)
		determinant = 1;

	float div = 1 / determinant;

	mt *= div;

	return mt.transpose();
}

//AUXILIAR
/*
multiplicar numero por matriz
*/
mat3 operator* (float n, const mat3 & other)
{
	mat3 result(1);

	result.set(0, 0, other.get(0, 0) * n);
	result.set(0, 1, other.get(0, 1) * n);
	result.set(0, 2, other.get(0, 2) * n);

	result.set(1, 0, other.get(1, 0) * n);
	result.set(1, 1, other.get(1, 1) * n);
	result.set(1, 2, other.get(1, 2) * n);

	result.set(2, 0, other.get(2, 0) * n);
	result.set(2, 1, other.get(2, 1) * n);
	result.set(2, 2, other.get(2, 2) * n);

	return result;
}

/*
multiplicar -1 por matriz
*/
mat3 operator- (const mat3 & other)
{
	mat3 result(1);
	int n = -1;

	result.set(0, 0, other.get(0, 0) * n);
	result.set(0, 1, other.get(0, 1) * n);
	result.set(0, 2, other.get(0, 2) * n);

	result.set(1, 0, other.get(1, 0) * n);
	result.set(1, 1, other.get(1, 1) * n);
	result.set(1, 2, other.get(1, 2) * n);

	result.set(2, 0, other.get(2, 0) * n);
	result.set(2, 1, other.get(2, 1) * n);
	result.set(2, 2, other.get(2, 2) * n);

	return result;
}
/*
passar matrix a array
*/
void mat3::matrixToArray(float matrix[3][3], float result[9])
{
	result[0] = matrix[0][0];
	result[1] = matrix[0][1];
	result[2] = matrix[0][2];

	result[3] = matrix[1][0];
	result[4] = matrix[1][1];
	result[5] = matrix[1][2];

	result[6] = matrix[2][0];
	result[7] = matrix[2][1];
	result[8] = matrix[2][2];
}

//TRANSFORMACOES GEOMETRICAS
mat3 translate(const mat3 & matrix, const vec2 & txy)
{
	mat3 identity(1.0f);
	identity.set(0, 2, txy.X());
	identity.set(1, 2, txy.Y());

	mat3 copy = matrix;

	return copy * identity;
}

mat3 scale(const mat3 & matrix, const vec3 & scale)
{
	mat3 identity(1.0f);
	identity.set(0, 0, scale.X());
	identity.set(1, 1, scale.Y());
	identity.set(2, 2, scale.Z());

	mat3 copy = matrix;

	return copy * identity;
}


mat3 scale(const mat3 & matrix, const vec2 & scale)
{
	mat3 identity(1.0f);
	identity.set(0, 0, scale.X());
	identity.set(1, 1, scale.Y());

	mat3 copy = matrix;

	return copy * identity;
}

//formula rodrigues
mat3 rotation(mat3 & matrix, const float angle, const vec3 & axis)
{
	mat3 identity(1.0f);
	mat3 dual(0, axis.Z(), -axis.Y(), -axis.Z(), 0, axis.X(), axis.Y(), -axis.X(), 0);

	mat3 dual_square = dual * dual;

	return matrix * (identity + (sin(angle))*dual + (1 - cos(angle))*dual_square);
}

/*
imprimir matriz
*/
void mat3::println() const
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << setprecision(2) << this->get(i, j) << " ";
		}
		cout << endl;
	}
}

/*
matriz 3_3 * vector 3_1
*/
vec3 operator*(const mat3 & matriz, const vec3 & vector)
{
	float x = matriz.get(0, 0) * vector.X() + matriz.get(0, 1) * vector.Y() + matriz.get(0, 2) * vector.Z();
	float y = matriz.get(1, 0) * vector.X() + matriz.get(1, 1) * vector.Y() + matriz.get(1, 2) * vector.Z();
	float z = matriz.get(2, 0) * vector.X() + matriz.get(2, 1) * vector.Y() + matriz.get(2, 2) * vector.Z();

	return vec3(x, y, z);
}