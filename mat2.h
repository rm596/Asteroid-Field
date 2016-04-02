#ifndef _H_MATRIX2
#define _H_MATRIX2

#include "vec2.h";

class mat2 {
private:
	float matrix[2][2];  //iniciar a zero
public:
	mat2(float x);  //construtor
	mat2(float x1, float x2, float x3, float x4);  //construtor
	mat2(float data[4]);  //construtor
	mat2(const vec2 & column1, const vec2 & column2); //construtor

	void set(int y, int x, float value);  //set na posicao y, x do valor
	void set(const float matrix[]);  //set por array

	void setRow(int row, const float matrix[]);  //set linha
	void setRow(int row, const vec2 & _row);  //set linha

	void setColumn(int column, const float matrix[]);  //set coluna
	void setColumn(int column, const vec2 & _column);  //set coluna

	float get(int y, int x) const;  //get na posicao x, y
	mat2 & get();

	void operator=(const mat2 & other);  //copiar matrix

	//operadores entre matrizes
	mat2 operator+(const mat2 & other);
	void operator+=(const mat2 & other);

	mat2 operator-(const mat2 & other);
	void operator-=(const mat2 & other);

	mat2 operator*(const mat2 & other);
	void operator*=(const float n);
	mat2 operator*(const float n);
	void operator*=(const mat2 & other);

	void identity();  //matrix identidade

	void matrixToArray(float matrix[2][2], float result[4]);  //matriz para array

	mat2 transpose();  //transposta matriz

	float determinant();  //determinante matriz

	mat2 inverse();  //inversa matriz

	void println() const;  //imprimir
};

//operadores a começar com numeros
mat2 operator* (float n, const mat2 & other);
mat2 operator- (const mat2 & other);

//matriz 2_2 * vector 2_1
vec2 operator*(const mat2 & matriz, const vec2 & vector);

#endif
