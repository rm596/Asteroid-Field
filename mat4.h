#ifndef _H_MATRIX4
#define _H_MATRIX4

#include <GL/glew.h>

#include "mat3.h"
#include "vec3.h"
#include "vec2.h"
#include "vec4.h"

class mat4 {
private:
	float matrix[4][4];  //iniciar a zero
public:
	//CONSTRUTORES
	mat4();
	mat4(float x);  //matriz identidade 
	mat4(float x1, float x2, float x3, float x4, float x5, float x6, float x7, float x8, float x9, float x10, float x11, float x12, float x13, float x14, float x15, float x16);  //construtor

	void set(int y, int x, float value);  //set por posicao

	float get(int y, int x) const;  //get na posicao x, y

	//OPERADORES
	mat4 operator+(const mat4 & other);
	mat4 operator-(const mat4 & other);
	mat4 operator*(const mat4 & other);

	//retornar matrix float[16] em transpose
	GLfloat * getMatrix();  //retornar matrix para GLSL

	mat4 & get();  //obter objecto

	void clean();  //clean matrix

	void println() const;  //imprimir
};

//OPERACOES GEOMETRICAS
mat4 translate(const mat4 & matrix, const vec3 & txy);
mat4 scale(const mat4 & matrix, const vec3 & scale);
mat4 rotation(mat4 & matrix, const float angle, const vec3 & axis);
mat4 shear(mat4 & matrix, float factor_b, float factor_c, float factor_d, float factor_f, float factor_g, float factor_i);

mat4 copy_mat3(mat3 & matrix);

vec4 operator*(const mat4 & matriz, vec4 & vector);

#endif
