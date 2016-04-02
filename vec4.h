#ifndef _H_VECTOR4
#define _H_VECTOR4


class vec4
{
private:
	float x, y, z, w;
	float vThreshold = (float)1.0e-5;
public:
	//construtor
	vec4(float x, float y, float z, float w);

	//get
	float get_x();
	float get_y();
	float get_z();
	float get_w();

	//set
	const void set_x(const float value);
	const void set_y(const float value);
	const void set_z(const float value);
	const void set_w(const float value);

	//normalizacao
	vec4 normalize();

	//igual
	const bool vEqual(const vec4& v);

	//clean
	void clean();

	//imprimir
	const void println();
};


#endif
