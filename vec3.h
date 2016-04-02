#ifndef _H_VECTOR3
#define _H_VECTOR3


class vec3 {
private:
	float x;
	float y;
	float z;
public:
	vec3(); //construtor
	vec3(float xx, float yy, float zz); //construtor
	vec3(const vec3 & other); //copia

	//gets
	float X(void) const;
	float Y(void) const;
	float Z(void) const;

	float _x(void);
	float _y(void);
	float _z(void);

	//set
	void setX(float xx);
	void setY(float yy);
	void setZ(float zz);

	//operadores
	bool operator== (const vec3& other) const;
	bool operator!= (const vec3& other) const;

	vec3 operator+ (const vec3 & other);
	void operator+= (const vec3 & other);
	vec3 operator+ (const float n);

	vec3 operator- (const vec3 & other);
	void operator-= (const vec3 & other);
	vec3 operator- (const float n);

	vec3 operator* (const vec3 & other);
	void operator*= (const vec3 & other);
	vec3 operator* (const float n);
	void operator*= (const float n);

	//norma vector
	float length(void) const;

	//distancia
	float distance(const vec3 & other);

	//produto interno, dot product, produto escalar
	float dot(const vec3 & other);

	//produto externo, cross
	vec3 cross(const vec3 & other);

	//normalizacao
	vec3 normalize();

	//angulo vectores
	float angle(const vec3 & other);



	//imprimir
	void println();
};

vec3 operator* (float n, const vec3 & other);

vec3 operator- (const vec3 & other);

#endif // !_H_VECTOR