#ifndef _H_SCENENODE
#define _H_SCENENODE

#include <stdlib.h> 
#include <list> 
#include "GL/glew.h"
#include "shader.h"
#include "vec3.h"
#include "mat4.h"
#include "qtrn.h"
#include "obj.h"
#include "texture.h"

#define DEGREESTORADIANS 0.0174532925

/* CHECK IT THIS IS STILL NEDED
// structure to pass points to the class
typedef struct {
	GLfloat XYZW[4];
	GLfloat RGBA[4];
} Vertex;*/

class scenenode
{
private:
	// the shader program duhhh....
	shader* shaderprogram = NULL;

	/* MESH */
	// stores vao and vbo ids respectively
	GLuint VaoId, VboId[2];

	/* buffer ids */
	GLuint vertexbuffer, uvbuffer, normalbuffer, alphabuffer;
	GLuint materialbuffer[3];

	// number of points
	GLuint size;

	/* updates final transformation matrix
	should be called everytime a transformation ocurs */
	void updateTransformation();

	/* mesh */
	obj obj_mesh;

	/* object texture */
	texture my_texture;

	/* object is using texture */
	bool is_texture = false;

protected:
	/* Transformation */
	// final transformation Matrix combining all transformations
	mat4 modelMatrix;

	// current translation matrix 
	mat4 translation;

	/* USE ONE OR ANOTHER */
	// current rotation quaternion
	qtrn rotationQ;

	// current scaling matrix
	mat4 scaling;

	/* Initializes matrixes with identity */
	void initMatrixes();

	/* Initializes quanternions */
	void initQuaternion();

public:
	//constructors
	scenenode();

	/* read obj */
	void setObj(obj mesh);

	/* loads mesh */
	void load_data(const obj obj_mesh);

	/* sets texture */
	void setTexture(texture _texture);

	/* get functions */
	GLuint getVao();

	GLuint* getVbo();

	mat4 getModelMatrix();

	/* gets shader program currently associated with object or NULL if none*/
	shader* getShaderId();

	/* sets the shaders currently used by object */
	void setShaderProgram(shader* s);

	/* clears the shaders currently used by object */
	void clearShaderProgram();

	/*destroys shader program and vertex and fragment shaders attached to it*/
	void destroy();

	/*draws object*/
	void draw();

	/*draws object*/
	void draw(mat4 * viewprojectionarray);

	//void draw(ShaderProgram program, Matrix4 viewProjection[2]);

	/* TRANSFORMATIONS */
	/*translates the object using a Vertor3*/
	void translate(vec3 t);

	/*sets the translation to the vector 3 passed as parameter*/
	void setTranslation(vec3 t);

	/* rotates using a quaternion */
	void rotate(float angle, vec3 axis);

	/*sets current object rotation*/
	void setRotation(float angle, vec3 axis);

	/* sets the object model matrix */
	void setModelMatrix(mat4 m);

	/*scales object*/
	void scale(vec3 t);

	/*sets scale of current object*/
	void setScale(vec3 t);
};

#endif