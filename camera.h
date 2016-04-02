#ifndef _H_CAMERA
#define _H_CAMERA

#include <math.h>

#include "scenenode.h"

#include "GL/glew.h"
#include "vec3.h"
#include "mat4.h"

#define ORTHOGONAL 0
#define PERSPECTIVE 1

#define DEGREESTORADIANS 0.0174532925

class camera : public scenenode
{
private:
	vec3 eye;
	vec3 center;
	vec3 up;

	mat4 view;
	mat4 projectionPerspective;

	mat4 viewProjection; // todo
	mat4 viewProjectionArray[2];

	void updateViewProjectionArray();

	bool is_moving = true; // controlls if camera can be moved

public:
	camera();

	camera(vec3 eye, vec3 center, vec3 up);

	camera(vec3 ini);

	// sets the projection matrix a perspective projection
	void setPerspective(GLfloat fovy, GLfloat aspect, GLfloat znear, GLfloat zfar);

	// returns an array with view matrix in position 0 and projection matrix in position 1
	mat4 * getViewProjectionArray();

	mat4 getViewMatrix();

	mat4 getProjectionMatrix();

	/*translates the object using a Vertor3*/
	void translate(vec3 t);

	/*rotates current object*/
	void rotate(float angle, vec3 axis);

	/* gets eye as array of floats */
	float* getEyeArray();

	/* sets camera position */
	void setPosition(vec3 position);

	void setMoving(bool b);

	bool getMoving();

	void reset(vec3 ini);
};

#endif