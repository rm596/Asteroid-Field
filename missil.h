#ifndef _H_MISSIL
#define _H_MISSIL

#include "scenenode.h"
#include "texture.h"
#include "shader.h"
#include "obj.h"
#include "vec3.h"

class missil
{
private:
	scenenode outer;
	scenenode inner;

	vec3 position;
	vec3 direction;

	float speed;

	//resets missile
	void init();

public:
	missil();

	// raper functions for both scene nodes
	void setObj(obj obj);
	void setTexture(texture tex);
	void setShaders(shader * inner, shader * outer);

	void draw();

	// updates missil
	void update();

	// set missile parameters
	void setPosition(vec3 p);

	// set direction
	void setDirection(vec3 d);

	// set speed
	void setSpeed(float s);

	// get missil parameters
	vec3 getPosition();
	vec3 getDirection();
	float getSpeed();

	void destroy();

	/*******************************
	 * transformations
	 *******************************/
	void translate(vec3 t);

};

#endif