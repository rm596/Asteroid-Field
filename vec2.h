#ifndef _H_VECTOR2
#define _H_VECTOR2

class vec2 {
private:
	float x;
	float y;

public:
	vec2(); //construtor
	vec2(float xx, float yy); //construtor
	vec2(const vec2 & other); //copia

	//gets
	float X(void) const;
	float Y(void) const;

	//set
	void setX(float xx);
	void setY(float yy);

	//operadores
	bool operator== (const vec2& other) const;

	vec2 operator+ (const vec2 & other);
	void operator+= (const vec2 & other);
	vec2 operator+ (float n);

	vec2 operator- (const vec2 & other);
	void operator-= (const vec2 & other);
	vec2 operator- (float n);

	vec2 operator* (const vec2 & other);
	void operator*= (const vec2 & other);
	vec2 operator* (float n);
	void operator*= (float n);

	//norma vector
	float length(void) const;

	//distancia
	float distance(const vec2 & other);

	//produto interno, dot product, produto escalar
	float dot(const vec2 & other);

	//produto externo, cross
	float cross(const vec2 & other);

	//normalizacao
	vec2 normalize();

	//angulo vectores
	float angle(const vec2 & other);

	//imprimir
	void println();
};

//numero * vector
vec2 operator* (float n, const vec2 & other);

//negacao vector
vec2 operator- (const vec2 & other);


//CONVERSAO DE angulos para radianos
float degrees(float radians);
float radians(float degrees);

#endif // !_H_VECTOR
