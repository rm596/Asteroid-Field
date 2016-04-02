#ifndef _H_MATRIX3
#define _H_MATRIX3

#include "vec2.h"
#include "vec3.h"

class mat3 {
private:
	float matrix[3][3];  //iniciar a zero
public:
	mat3(float x);  //construtor
	mat3(float x1, float x2, float x3, float x4, float x5, float x6, float x7, float x8, float x9);  //construtor
	mat3(float data[9]);  //construtor
	mat3(const vec3 & column1, const vec3 & column2, const vec3 & column3); //construtor

	void set(int y, int x, float value);  //set na posicao y, x do valor
	void set(const float matrix[]);  //set por array

	void setRow(int row, const float matrix[]);  //set linha
	void setRow(int row, const vec3 & _row);  //set linha

	void setColumn(int column, const float matrix[]);  //set coluna
	void setColumn(int column, const vec3 & _column);  //set coluna

	float get(int y, int x) const;  //get na posicao x, y
	mat3 & get();

	void operator=(const mat3 & other);  //copiar matrix

	//operadores entre matrizes
	mat3 operator+(const mat3 & other);
	void operator+=(const mat3 & other);

	mat3 operator-(const mat3 & other);
	void operator-=(const mat3 & other);

	mat3 operator*(const mat3 & other);
	void operator*=(const float n);
	mat3 operator*(const float n);
	void operator*=(const mat3 & other);

	void identity();  //matrix identidade

	void matrixToArray(float matrix[3][3], float result[9]);  //matriz para array

	mat3 transpose();  //transposta matriz

	float determinant();  //determinante matriz

	mat3 inverse();  //inversa matriz

	void println() const;  //imprimir
};

//operadores a começar com numeros
mat3 operator* (float n, const mat3 & other);
mat3 operator- (const mat3 & other);

//TRANSFORMACOES GEOMETRICAS
mat3 translate(const mat3 & matrix, const vec2 & txy);

mat3 scale(const mat3 & matrix, const vec3 & scale);
mat3 scale(const mat3 & matrix, const vec2 & scale);

mat3 rotation(mat3 & matrix, const float angle, const vec3 & axis);

//matriz 3_3 * vector 3_1
vec3 operator*(const mat3 & matriz, const vec3 & vector);

#endif
