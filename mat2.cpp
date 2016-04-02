#include <iostream>
#include <cmath>

#include "mat2.h"
#include <iomanip>

using namespace std;

// TODO: REPLACE WITH float matrix[4];

//COLUMN MAJOR
/*
construtor
*/
mat2::mat2(float x) : matrix()
{
	matrix[0][0] = x; matrix[0][1] = 0.0f;
	matrix[1][0] = 0.0f; matrix[1][1] = x;
}

/*
construtor
*/
mat2::mat2(float x1, float x2, float x3, float x4)
{
	matrix[0][0] = x1; matrix[0][1] = x3;
	matrix[1][0] = x2; matrix[1][1] = x4;
}

/*
construtor
*/
mat2::mat2(float data[4])
{
	matrix[0][0] = data[0]; matrix[0][1] = data[2];
	matrix[1][0] = data[1]; matrix[1][1] = data[3];
}

/*
construtor
*/
mat2::mat2(const vec2 & column1, const vec2 & column2)
{
	matrix[0][0] = column1.X(); matrix[0][1] = column2.X();
	matrix[1][0] = column1.Y(); matrix[1][1] = column2.Y();
}

/*
set na posicao do valor
*/
void mat2::set(int y, int x, float value)
{
	matrix[y][x] = value;
}

/*
set por array
*/
void mat2::set(const float matrix[])
{
	this->set(0, 0, matrix[0]);
	this->set(0, 1, matrix[2]);
	this->set(1, 0, matrix[1]);
	this->set(1, 1, matrix[3]);
}

/*
set linha matriz por array
*/
void mat2::setRow(int row, const float matrix[])
{
	this->set(row, 0, matrix[0]);
	this->set(row, 1, matrix[1]);
}

/*
set linha matriz por vector
*/
void mat2::setRow(int row, const vec2 & _row)
{
	this->set(row, 0, _row.X());
	this->set(row, 1, _row.Y());
}

/*
set coluna matriz por array
*/
void mat2::setColumn(int column, const float matrix[])
{
	this->set(0, column, matrix[0]);
	this->set(1, column, matrix[1]);
}

/*
set coluna matriz por array
*/
void mat2::setColumn(int column, const vec2 & _column)
{
	this->set(0, column, _column.X());
	this->set(1, column, _column.Y());
}

/*
copiar matriz
*/
void mat2::operator=(const mat2 & other)
{
	this->set(0, 0, other.get(0, 0));
	this->set(0, 1, other.get(0, 1));
	this->set(1, 0, other.get(1, 0));
	this->set(1, 1, other.get(1, 1));
}

//OPERADORES ENTRE MATRIZES
mat2 mat2::operator+(const mat2 & other)
{
	mat2 result(1);
	result.set(0, 0, this->get(0, 0) + other.get(0, 0));
	result.set(0, 1, this->get(0, 1) + other.get(0, 1));
	result.set(1, 0, this->get(1, 0) + other.get(1, 0));
	result.set(1, 1, this->get(1, 1) + other.get(1, 1));
	return result;
}

void mat2::operator+=(const mat2 & other)
{
	this->set(0, 0, this->get(0, 0) + other.get(0, 0));
	this->set(0, 1, this->get(0, 1) + other.get(0, 1));
	this->set(1, 0, this->get(1, 0) + other.get(1, 0));
	this->set(1, 1, this->get(1, 1) + other.get(1, 1));
}

mat2 mat2::operator-(const mat2 & other)
{
	mat2 result(1);
	result.set(0, 0, this->get(0, 0) - other.get(0, 0));
	result.set(0, 1, this->get(0, 1) - other.get(0, 1));
	result.set(1, 0, this->get(1, 0) - other.get(1, 0));
	result.set(1, 1, this->get(1, 1) - other.get(1, 1));
	return result;
}

void mat2::operator-=(const mat2 & other)
{
	this->set(0, 0, this->get(0, 0) - other.get(0, 0));
	this->set(0, 1, this->get(0, 1) - other.get(0, 1));
	this->set(1, 0, this->get(1, 0) - other.get(1, 0));
	this->set(1, 1, this->get(1, 1) - other.get(1, 1));
}

mat2 mat2::operator*(const mat2 & other)
{
	mat2 result(1);

	result.set(0, 0, this->get(0, 0) * other.get(0, 0) + this->get(0, 1) * other.get(1, 0));
	result.set(0, 1, this->get(0, 0) * other.get(0, 1) + this->get(0, 1) * other.get(1, 1));
	result.set(1, 0, this->get(1, 0) * other.get(0, 0) + this->get(1, 1) * other.get(1, 0));
	result.set(1, 1, this->get(1, 0) * other.get(0, 1) + this->get(1, 1) * other.get(1, 1));

	return result;
}

mat2 mat2::operator*(const float n)
{
	mat2 result(1);

	result.set(0, 0, this->get(0, 0) * n);
	result.set(0, 1, this->get(0, 1) * n);
	result.set(1, 0, this->get(1, 0) * n);
	result.set(1, 1, this->get(1, 1) * n);

	return result;
}

void mat2::operator*=(const float n)
{
	this->set(0, 0, this->get(0, 0) * n);
	this->set(0, 1, this->get(0, 1) * n);
	this->set(1, 0, this->get(1, 0) * n);
	this->set(1, 1, this->get(1, 1) * n);
}

void mat2::operator*=(const mat2 & other)
{
	mat2 copy1 = this->get();

	this->set(0, 0, copy1.get(0, 0) * other.get(0, 0) + copy1.get(0, 1) * other.get(1, 0));
	this->set(0, 1, copy1.get(0, 0) * other.get(0, 1) + copy1.get(0, 1) * other.get(1, 1));
	this->set(1, 0, copy1.get(1, 0) * other.get(0, 0) + copy1.get(1, 1) * other.get(1, 0));
	this->set(1, 1, copy1.get(1, 0) * other.get(0, 1) + copy1.get(1, 1) * other.get(1, 1));
}


/*
get na posicao
*/
float mat2::get(int y, int x) const
{
	return matrix[y][x];
}

/*
get this
*/
mat2 & mat2::get()
{
	return *this;
}

/*
matrix identidade
*/
void mat2::identity()
{
	this->set(0, 0, 1);
	this->set(0, 1, 0);
	this->set(1, 0, 0);
	this->set(1, 1, 1);
}

/*
transposta matrix
*/
mat2 mat2::transpose()
{
	mat2 result(0.0f);

	result.set(0, 0, this->get(0, 0));
	result.set(0, 1, this->get(1, 0));
	result.set(1, 0, this->get(0, 1));
	result.set(1, 1, this->get(1, 1));

	return result;
}

/*
determinante matrix
*/
float mat2::determinant()
{
	return this->get(0, 0) * this->get(1, 1) - this->get(1, 0) * this->get(0, 1);
}

/*
inversa matrix
*/
mat2 mat2::inverse()
{

	float determinant = this->determinant();

	if (determinant == 0)
		determinant = 1;

	float aux = 1 / determinant;

	mat2 result(0.0f);

	result.set(0, 0, this->get(1, 1));
	result.set(0, 1, -this->get(0, 1));
	result.set(1, 0, -this->get(1, 0));
	result.set(1, 1, this->get(0, 0));

	result *= aux;

	return result;
}

//AUXILIAR
/*
multiplicar numero por matriz
*/
mat2 operator* (float n, const mat2 & other)
{
	mat2 result(1);

	result.set(0, 0, other.get(0, 0) * n);
	result.set(0, 1, other.get(0, 1) * n);
	result.set(1, 0, other.get(1, 0) * n);
	result.set(1, 1, other.get(1, 1) * n);

	return result;
}

/*
multiplicar -1 por matriz
*/
mat2 operator- (const mat2 & other)
{
	mat2 result(1);

	result.set(0, 0, other.get(0, 0) * -1);
	result.set(0, 1, other.get(0, 1) * -1);
	result.set(1, 0, other.get(1, 0) * -1);
	result.set(1, 1, other.get(1, 1) * -1);

	return result;
}
/*
passar matrix a array
*/
void mat2::matrixToArray(float matrix[2][2], float result[4])
{
	result[0] = matrix[0][0];
	result[1] = matrix[0][1];
	result[2] = matrix[1][0];
	result[3] = matrix[1][1];
}

/*
imprimir matriz
*/
void mat2::println() const
{
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			cout << setprecision(2) << this->get(i, j) << " ";
		}
		cout << endl;
	}
}

/*
multiplicacao vector por matriz
*/
vec2 operator*(const mat2 & matriz, const vec2 & vector)
{
	float x = matriz.get(0, 0) * vector.X() + matriz.get(0, 1) * vector.Y();
	float y = matriz.get(1, 0) * vector.X() + matriz.get(1, 1) * vector.Y();
	return vec2(x, y);
}