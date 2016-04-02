#include <iostream>
#include <cmath>
#include <iomanip>

#include <GL/glew.h>

#include "mat4.h"

using namespace std;

mat4::mat4()
{
}

//COLUMN MAJOR
/*
construtor por numero
*/
mat4::mat4(float x) : matrix()
{
	matrix[0][0] = x; matrix[0][1] = 0.0f;  matrix[0][2] = 0.0f;  matrix[0][3] = 0.0f;
	matrix[1][0] = 0.0f; matrix[1][1] = x;  matrix[1][2] = 0.0f;  matrix[1][3] = 0.0f;
	matrix[2][0] = 0.0f; matrix[2][1] = 0.0f;  matrix[2][2] = x;  matrix[2][3] = 0.0f;
	matrix[3][0] = 0.0f; matrix[3][1] = 0.0f;  matrix[3][2] = 0.0f;  matrix[3][3] = x;
}

mat4::mat4(float x1, float x2, float x3, float x4, float x5, float x6, float x7, float x8, float x9, float x10, float x11, float x12, float x13, float x14, float x15, float x16)
{
	matrix[0][0] = x1; matrix[0][1] = x5;  matrix[0][2] = x9;  matrix[0][3] = x13;
	matrix[1][0] = x2; matrix[1][1] = x6;  matrix[1][2] = x10;  matrix[1][3] = x14;
	matrix[2][0] = x3; matrix[2][1] = x7;  matrix[2][2] = x11;  matrix[2][3] = x15;
	matrix[3][0] = x4; matrix[3][1] = x8;  matrix[3][2] = x12;  matrix[3][3] = x16;
}

//GET MATRIX PARA GLSL
GLfloat * mat4::getMatrix()
{
	GLfloat Matrix[16];
	int index = 0;

	//prencher matriz
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Matrix[index++] = matrix[j][i];
			//cout << Matrix[index++] << " ";
		}
		//cout << endl;
	}
	return Matrix;
}

/*
set na posicao do valor
*/
void mat4::set(int y, int x, float value)
{
	matrix[y][x] = value;
}

float mat4::get(int y, int x) const
{
	return matrix[y][x];
}

//Get OBJECTO
mat4 & mat4::get()
{
	return *this;
}

//clean matrix por threshold 
void mat4::clean()
{
	float matThreshold = 1.0e-5;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (fabs(this->get(i, j)) < matThreshold)
			{
				this->set(i, j, 0.0f);
			}
		}
	}
}


/*
imprimir matriz
*/
void mat4::println() const
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << setprecision(5) << this->get(i, j) << " ";
		}
		cout << endl;
	}
}

/*
OPERADORES
*/
mat4 mat4::operator+(const mat4 & other)
{
	mat4 result(0.0f);
	result.set(0, 0, this->get(0, 0) + other.get(0, 0));
	result.set(0, 1, this->get(0, 1) + other.get(0, 1));
	result.set(0, 2, this->get(0, 2) + other.get(0, 2));
	result.set(0, 3, this->get(0, 3) + other.get(0, 3));

	result.set(1, 0, this->get(1, 0) + other.get(1, 0));
	result.set(1, 1, this->get(1, 1) + other.get(1, 1));
	result.set(1, 2, this->get(1, 2) + other.get(1, 2));
	result.set(1, 3, this->get(1, 3) + other.get(1, 3));

	result.set(2, 0, this->get(2, 0) + other.get(2, 0));
	result.set(2, 1, this->get(2, 1) + other.get(2, 1));
	result.set(2, 2, this->get(2, 2) + other.get(2, 2));
	result.set(2, 3, this->get(2, 3) + other.get(2, 3));

	result.set(3, 0, this->get(3, 0) + other.get(3, 0));
	result.set(3, 1, this->get(3, 1) + other.get(3, 1));
	result.set(3, 2, this->get(3, 2) + other.get(3, 2));
	result.set(3, 3, this->get(3, 3) + other.get(3, 3));

	return result;
}

mat4 mat4::operator-(const mat4 & other)
{
	mat4 result(0.0f);
	result.set(0, 0, this->get(0, 0) - other.get(0, 0));
	result.set(0, 1, this->get(0, 1) - other.get(0, 1));
	result.set(0, 2, this->get(0, 2) - other.get(0, 2));
	result.set(0, 3, this->get(0, 3) - other.get(0, 3));

	result.set(1, 0, this->get(1, 0) - other.get(1, 0));
	result.set(1, 1, this->get(1, 1) - other.get(1, 1));
	result.set(1, 2, this->get(1, 2) - other.get(1, 2));
	result.set(1, 3, this->get(1, 3) - other.get(1, 3));

	result.set(2, 0, this->get(2, 0) - other.get(2, 0));
	result.set(2, 1, this->get(2, 1) - other.get(2, 1));
	result.set(2, 2, this->get(2, 2) - other.get(2, 2));
	result.set(2, 3, this->get(2, 3) - other.get(2, 3));

	result.set(3, 0, this->get(3, 0) - other.get(3, 0));
	result.set(3, 1, this->get(3, 1) - other.get(3, 1));
	result.set(3, 2, this->get(3, 2) - other.get(3, 2));
	result.set(3, 3, this->get(3, 3) - other.get(3, 3));

	return result;
}

mat4 mat4::operator*(const mat4 & other)
{
	mat4 result(0.0f);

	result.set(0, 0, this->get(0, 0) * other.get(0, 0) + this->get(0, 1) * other.get(1, 0) + this->get(0, 2) * other.get(2, 0) + this->get(0, 3) * other.get(3, 0));
	result.set(0, 1, this->get(0, 0) * other.get(0, 1) + this->get(0, 1) * other.get(1, 1) + this->get(0, 2) * other.get(2, 1) + this->get(0, 3) * other.get(3, 1));
	result.set(0, 2, this->get(0, 0) * other.get(0, 2) + this->get(0, 1) * other.get(1, 2) + this->get(0, 2) * other.get(2, 2) + this->get(0, 3) * other.get(3, 2));
	result.set(0, 3, this->get(0, 0) * other.get(0, 3) + this->get(0, 1) * other.get(1, 3) + this->get(0, 2) * other.get(2, 3) + this->get(0, 3) * other.get(3, 3));

	result.set(1, 0, this->get(1, 0) * other.get(0, 0) + this->get(1, 1) * other.get(1, 0) + this->get(1, 2) * other.get(2, 0) + this->get(1, 3) * other.get(3, 0));
	result.set(1, 1, this->get(1, 0) * other.get(0, 1) + this->get(1, 1) * other.get(1, 1) + this->get(1, 2) * other.get(2, 1) + this->get(1, 3) * other.get(3, 1));
	result.set(1, 2, this->get(1, 0) * other.get(0, 2) + this->get(1, 1) * other.get(1, 2) + this->get(1, 2) * other.get(2, 2) + this->get(1, 3) * other.get(3, 2));
	result.set(1, 3, this->get(1, 0) * other.get(0, 3) + this->get(1, 1) * other.get(1, 3) + this->get(1, 2) * other.get(2, 3) + this->get(1, 3) * other.get(3, 3));

	result.set(2, 0, this->get(2, 0) * other.get(0, 0) + this->get(2, 1) * other.get(1, 0) + this->get(2, 2) * other.get(2, 0) + this->get(2, 3) * other.get(3, 0));
	result.set(2, 1, this->get(2, 0) * other.get(0, 1) + this->get(2, 1) * other.get(1, 1) + this->get(2, 2) * other.get(2, 1) + this->get(2, 3) * other.get(3, 1));
	result.set(2, 2, this->get(2, 0) * other.get(0, 2) + this->get(2, 1) * other.get(1, 2) + this->get(2, 2) * other.get(2, 2) + this->get(2, 3) * other.get(3, 2));
	result.set(2, 3, this->get(2, 0) * other.get(0, 3) + this->get(2, 1) * other.get(1, 3) + this->get(2, 2) * other.get(2, 3) + this->get(2, 3) * other.get(3, 3));

	result.set(3, 0, this->get(3, 0) * other.get(0, 0) + this->get(3, 1) * other.get(1, 0) + this->get(3, 2) * other.get(2, 0) + this->get(3, 3) * other.get(3, 0));
	result.set(3, 1, this->get(3, 0) * other.get(0, 1) + this->get(3, 1) * other.get(1, 1) + this->get(3, 2) * other.get(2, 1) + this->get(3, 3) * other.get(3, 1));
	result.set(3, 2, this->get(3, 0) * other.get(0, 2) + this->get(3, 1) * other.get(1, 2) + this->get(3, 2) * other.get(2, 2) + this->get(3, 3) * other.get(3, 2));
	result.set(3, 3, this->get(3, 0) * other.get(0, 3) + this->get(3, 1) * other.get(1, 3) + this->get(3, 2) * other.get(2, 3) + this->get(3, 3) * other.get(3, 3));

	return result;
}

/*
OPERAÇÕES GEOMETRICAS
*/
mat4 translate(const mat4 & matrix, const vec3 & txyz)
{
	mat4 identity(1.0f);
	identity.set(0, 3, txyz.X());
	identity.set(1, 3, txyz.Y());
	identity.set(2, 3, txyz.Z());

	mat4 copy = matrix;

	return copy * identity;
}

mat4 scale(const mat4 & matrix, const vec3 & scale)
{
	mat4 identity(1.0f);
	identity.set(0, 0, scale.X());
	identity.set(1, 1, scale.Y());
	identity.set(2, 2, scale.Z());

	mat4 copy = matrix;

	return copy * identity;
}

mat4 rotation(mat4 & matrix, const float angle, const vec3 & axis)
{
	mat3 identity(1.0f);
	mat3 dual(0, axis.Z(), -axis.Y(), -axis.Z(), 0, axis.X(), axis.Y(), -axis.X(), 0);

	mat3 dual_square = dual * dual;

	mat3 result = identity + (sin(radians(angle)))*dual + (1 - cos(radians(angle)))*dual_square;

	return matrix * copy_mat3(result);
}

mat4 shear(mat4 & matrix, float factor_b, float factor_c, float factor_d, float factor_f, float factor_g, float factor_i)
{
	mat4 identity(1.0f);
	identity.set(0, 1, factor_d);
	identity.set(0, 2, factor_g);

	identity.set(1, 0, factor_b);
	identity.set(1, 2, factor_i);

	identity.set(2, 0, factor_c);
	identity.set(2, 1, factor_f);

	return matrix * identity;
}

//auxilira para copiar mat3 para mat4
mat4 copy_mat3(mat3 & matrix)
{
	mat4 result(1.0f);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			result.set(i, j, matrix.get(i, j));
		}
	}
	return result;
}

//matriz 4_4 * vector 4_1
vec4 operator*(const mat4 & matriz, vec4 & vector)
{
	vec4 result(0, 0, 0, 0);
	result.set_x(matriz.get(0, 0) * vector.get_x() + matriz.get(0, 1) * vector.get_y() + matriz.get(0, 2) * vector.get_z() + matriz.get(0, 3) * vector.get_w());
	result.set_y(matriz.get(1, 0) * vector.get_x() + matriz.get(1, 1) * vector.get_y() + matriz.get(1, 2) * vector.get_z() + matriz.get(1, 3) * vector.get_w());
	result.set_z(matriz.get(2, 0) * vector.get_x() + matriz.get(2, 1) * vector.get_y() + matriz.get(2, 2) * vector.get_z() + matriz.get(2, 3) * vector.get_w());
	result.set_w(matriz.get(3, 0) * vector.get_x() + matriz.get(3, 1) * vector.get_y() + matriz.get(3, 2) * vector.get_z() + matriz.get(3, 3) * vector.get_w());

	return result;
}

/*

//VIEW MATRIX
mat4 lookAt(vec3 eye, vec3 center, vec3 up)
{
vec3 view = center - eye;
//view.println();

//cout << endl;

vec3 V = view.normalize();
//V.println();
//cout << endl;

mat3 dual_view = mat3(0, V.Z(), -V.Y(), -V.Z(), 0, V.X(), V.Y(), -V.X(), 0);
//dual_view.println();
//cout << endl;

vec3 side = dual_view * up;
//side.println();

vec3 S = side.normalize();
//S.println();
//cout << endl;

mat3 dual_S = mat3(0, S.Z(), -S.Y(), -S.Z(), 0, S.X(), S.Y(), -S.X(), 0);
vec3 U = dual_S * V;

mat4 R = mat4(S.X(), U.X(), -V.X(), 0, S.Y(), U.Y(), -V.Y(), 0, S.Z(), U.Z(), -V.Z(), 0, 0, 0, 0, 1);
//R.println();
//cout << endl;

mat4 T = translate(mat4(1.0f), -eye);
//T.println();
//cout << endl;

mat4 M = R*T;
//M.println();
//cout << endl;
return M;
}

mat4 ortho(float left, float right, float bottom, float top, float zNear, float zFar)
{
mat4 M = mat4(2 / (right - left), 0, 0, 0,
0, 2 / (top - bottom), 0, 0,
0, 0, -2 / (zFar - zNear), 0,
-(right + left)/(right-left), -(top + bottom)/(top - bottom), -(zFar + zNear)/(zFar - zNear), 1);

//M.println();

return M;
}

mat4 perspective(float fovy, float aspect, float zNear, float zFar)
{
float angle = fovy / 2;
float d = 1 / (tan(radians(angle)));

float A = (zNear + zFar) / (zNear - zFar);
float B = (2*zFar*zNear) / (zNear - zFar);

mat4 M = mat4((d/aspect), 0,0,0,
0,d,0,0,
0,0,A, -1,
0,0,B, 0
);
return M;
}
*/