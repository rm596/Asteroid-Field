#include "camera.h"

camera::camera() : scenenode() {}

/* not used right now */
camera::camera(vec3 eye, vec3 center, vec3 up) : scenenode()
{
	this->eye = eye;
	this->center = center;
	this->up = up;


	vec3 v = (center - eye).normalize();
	vec3 s = v.cross(up).normalize();
	vec3 u = s.cross(v);

	this->view =
		mat4(
			s.X(), u.X(), -v.X(), 0.0f,
			s.Y(), u.Y(), -v.Y(), 0.0f,
			s.Z(), u.Z(), -v.Z(), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
			)
		*
		mat4(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			-eye.X(), -eye.Y(), -eye.Z(), 1.0f
			);
}

camera::camera(vec3 ini)
{
	this->eye = vec3(0.0f,0.0f,0.0f);
	this->initMatrixes();
	this->initQuaternion();

	this->view = mat4(1.0);
	this->translate(ini); // sets initial translation
}

void camera::updateViewProjectionArray()
{
	vec4 temp = vec4(
		0,
		0,
		0,
		1.0f
		);

	temp = this->modelMatrix * temp;

	this->eye = vec3(temp.get_x() / temp.get_w(), temp.get_y() / temp.get_w(), temp.get_z() / temp.get_w());

	//this->eye = vec3(this->modelMatrix.get(0, 3), this->modelMatrix.get(1, 3), this->modelMatrix.get(2, 3));

	this->viewProjectionArray[0] = this->modelMatrix; // model matrix of the camera object

	this->viewProjectionArray[1] = this->projectionPerspective;

	/*glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(GLfloat) * 16, this->viewProjectionArray[0].getArray());
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(GLfloat) * 16, sizeof(GLfloat) * 16, this->viewProjectionArray[1].getArray());
	glBindBuffer(GL_UNIFORM_BUFFER, 0);*/
}

void camera::setPerspective(GLfloat fovy, GLfloat aspect, GLfloat znear, GLfloat zfar)
{
	GLfloat d = 1 / tanf((fovy*DEGREESTORADIANS) / 2);

	this->projectionPerspective = mat4(
		d / aspect, 0.0f, 0.0f, 0.0f,
		0.0f, d, 0.0f, 0.0f,
		0.0f, 0.0f, (znear + zfar) / (znear - zfar), -1.0f,
		0.0f, 0.0f, (2 * zfar*znear) / (znear - zfar), 0.0f
		);

	this->updateViewProjectionArray();
}

mat4 * camera::getViewProjectionArray()
{
	return this->viewProjectionArray;
}

mat4 camera::getViewMatrix()
{
	return this->getViewProjectionArray()[0];
}

mat4 camera::getProjectionMatrix()
{
	return this->getViewProjectionArray()[1];
}

void camera::translate(vec3 t)
{
	scenenode::translate(t);
	this->updateViewProjectionArray();
}

void camera::rotate(float angle, vec3 axis)
{
	if (this->is_moving)
	{
		scenenode::rotate(angle, axis);
		this->updateViewProjectionArray();
	}
}

float* camera::getEyeArray()
{
	float temp[3];

	temp[0] = this->eye.X();
	temp[1] = this->eye.Y();
	temp[2] = this->eye.Z();

	return temp;
}

void camera::setPosition(vec3 position)
{
	scenenode::setTranslation(position);
	this->updateViewProjectionArray();
}

void camera::setMoving(bool b)
{
	this->is_moving = b;
}

bool camera::getMoving()
{
	return this->is_moving;
}

void camera::reset(vec3 ini)
{
	this->eye = vec3(0.0f, 0.0f, 0.0f);
	this->initMatrixes();
	this->initQuaternion();

	this->view = mat4(1.0);
	this->translate(ini); // sets initial translation
}