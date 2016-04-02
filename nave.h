#ifndef _H_NAVE
#define _H_NAVE

#include "scenenode.h"
#include "luz.h"
#include "particles.h"

#include <vector>

class nave : public scenenode
{
private:
	luz l; // luz a influenciar a nave
	std::vector<particles> motores; // posição dos 4 motores da nave
	shader * motores_shader;

	camera *main_camera;
	
	//is engine enable
	bool enable_engine = false;

	//direction
	float direction = 0;
	void reset_engines();

	// controls if ship should be drawned
	bool active = false;

public:
	//construtores
	nave();

	/* set active */
	void setActive(bool a);

	/* inicializa os motores da nave*/
	void initMotores();

	//manipulates light
	void setLuz(luz _l_);

	luz getLuz();

	void setLuzPosicao(vec3 pos);

	//draws self complements base class
	void draw();

	/* sets the camera */
	void setCamera(camera* c);

	/* Motores da nave */
	void setMotoresShader(shader * s);
	particles * nave::getMotores(int position);

	/* TRANSFORMATIONS */
	/*translates the object using a Vertor3*/
	void translate(vec3 t);

	/*sets the translation to the vector 3 passed as parameter*/
	void setTranslation(vec3 t);

	/* rotates using a quaternion */
	void rotate(float angle, vec3 axis);

	/*sets current object rotation*/
	void setRotation(float angle, vec3 axis);

	/* lets the laser lightn affet ilumination */
	void shoot(bool b);

	/* starts ship engines */
	void start_engine();

	/* stops ships engines */
	void stop_engine();

	/* get position */
	vec3 get_position();
};

#endif