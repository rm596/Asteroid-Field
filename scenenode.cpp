#include "scenenode.h"

scenenode::scenenode()
{
	// initializes transformations
	this->initMatrixes();
	this->initQuaternion();
}

void scenenode::setObj(obj mesh)
{
	this->obj_mesh = mesh;

	this->size = mesh.getVertices().size();

	//todo optimize this duh!!!!!!!!!
}

void scenenode::load_data(const obj obj_mesh)
{
	glGenVertexArrays(1, &this->VaoId);
	glBindVertexArray(this->VaoId);
	{

		//VERTICES
		glGenBuffers(1, &vertexbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glBufferData(GL_ARRAY_BUFFER, this->obj_mesh.getVertices().size() * sizeof(Obj_vertex), &this->obj_mesh.getVertices()[0], GL_STATIC_DRAW);

		//LAYOUT LOCATION = 0
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Obj_vertex), 0);

		// TEXTURAS
		if (this->obj_mesh.TexcoordsLoaded)
		{
			glGenBuffers(1, &uvbuffer);
			glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
			glBufferData(GL_ARRAY_BUFFER, this->obj_mesh.getTextcoords().size() * sizeof(Obj_texcoord), &this->obj_mesh.getTextcoords()[0], GL_STATIC_DRAW);

			//LAYOUT LOCATION = 1
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Obj_texcoord), 0);
		}

		// NORMAL
		if (this->obj_mesh.NormalsLoaded)
		{
			glGenBuffers(1, &normalbuffer);
			glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
			glBufferData(GL_ARRAY_BUFFER, this->obj_mesh.getNormals().size() * sizeof(Obj_normal), &this->obj_mesh.getNormals()[0], GL_STATIC_DRAW);

			//LAYOUT LOCATION = 2
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Obj_normal), 0);
		}

		if (this->obj_mesh.MaterialLoaded)
		{
			//AMBIENTE
			glGenBuffers(1, &materialbuffer[0]);
			glBindBuffer(GL_ARRAY_BUFFER, materialbuffer[0]);
			glBufferData(GL_ARRAY_BUFFER, this->obj_mesh.getAmbient().size() * sizeof(Obj_color), &this->obj_mesh.getAmbient()[0], GL_STATIC_DRAW);
			//LAYOUT LOCATION = 3
			glEnableVertexAttribArray(3);
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Obj_color), 0);

			//DIFUSA
			glGenBuffers(1, &materialbuffer[1]);
			glBindBuffer(GL_ARRAY_BUFFER, materialbuffer[1]);
			glBufferData(GL_ARRAY_BUFFER, this->obj_mesh.getDiffuse().size() * sizeof(Obj_color), &this->obj_mesh.getDiffuse()[0], GL_STATIC_DRAW);
			//LAYOUT LOCATION = 4
			glEnableVertexAttribArray(4);
			glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Obj_color), 0);

			//ESPECULAR
			glGenBuffers(1, &materialbuffer[2]);
			glBindBuffer(GL_ARRAY_BUFFER, materialbuffer[2]);
			glBufferData(GL_ARRAY_BUFFER, this->obj_mesh.getSpecular().size() * sizeof(Obj_color), &this->obj_mesh.getSpecular()[0], GL_STATIC_DRAW);
			//LAYOUT LOCATION = 5
			glEnableVertexAttribArray(5);
			glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(Obj_color), 0);

			//Alpha
			glGenBuffers(1, &alphabuffer);
			glBindBuffer(GL_ARRAY_BUFFER, alphabuffer);
			glBufferData(GL_ARRAY_BUFFER, this->obj_mesh.getAlfa().size() * sizeof(GLfloat), &this->obj_mesh.getAlfa()[0], GL_STATIC_DRAW);
			//LAYOUT LOCATION = 6
			glEnableVertexAttribArray(6);
			glVertexAttribPointer(6, 1, GL_FLOAT, GL_FALSE, sizeof(GLfloat), 0);

			// clear
			glBindVertexArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

	}

	this->obj_mesh.freeMeshData();
}

void scenenode::setTexture(texture _texture)
{
	this->my_texture = _texture;
	this->is_texture = true;
}

//TODO: CHECK IF THIS MAKES SENSE
GLuint scenenode::getVao()
{
	return this->VaoId;
}

GLuint * scenenode::getVbo()
{
	return this->VboId;
}

shader* scenenode::getShaderId()
{
	return this->shaderprogram;
}

void scenenode::setShaderProgram(shader* s)
{
	this->shaderprogram = s;
}

void scenenode::clearShaderProgram()
{
	this->shaderprogram = NULL;
}

void scenenode::initMatrixes()
{
	this->translation = mat4(1.0);
	this->scaling = mat4(1.0);
	this->modelMatrix = mat4(1.0);
}

void scenenode::initQuaternion()
{
	this->rotationQ = qtrn(1, vec3(0, 0, 0));
}

// TODO
void scenenode::destroy()
{
	glBindVertexArray(this->VaoId);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);
	glDisableVertexAttribArray(5);
	glDisableVertexAttribArray(6);

	glDeleteBuffers(2, this->VboId);
	glDeleteVertexArrays(1, &this->VaoId);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void scenenode::draw()
{

	// if no shader is not associated with object or his parent the object is not drawn
	if ((this->getShaderId()))
	{

		glBindVertexArray(this->VaoId);
		glUseProgram((*this->getShaderId()).getProgramId());
		glUniformMatrix4fv((*this->getShaderId()).getUniformId("ModelMatrix"), 1, GL_FALSE, this->getModelMatrix().getMatrix());
		
		//float cameraposition[3] = { 0.0f, 0.0f, -20.0f };
		//float lightPosition[3] = { 0.0f, 10.0f, 30.0f };

		if (is_texture)
		{
			//activar textura
			this->my_texture.bindTexture(0);

			glUniform1i((*this->getShaderId()).getUniformId("gSampler"), 0);
		}

		glDrawArrays(GL_TRIANGLES, 0, this->size);

		glUseProgram(0);
		glBindVertexArray(0);
	}

}

/******************************
 * TRANFORMATIONS SECTION
 ******************************/

void scenenode::updateTransformation()
{
	this->modelMatrix = this->translation * this->rotationQ.getAsMatrix4() * this->scaling;

	/*printf("transformation matrix\n");
	this->modelMatrix.println();
	/*printf("\n");
	printf("rotation qtrn\n");
	this->rotationQ.getAsMatrix4().println();
	printf("\n");*/
}

void scenenode::translate(vec3 t)
{
	this->translation.set(0, 3, this->translation.get(0, 3) + t.X());
	this->translation.set(1, 3, this->translation.get(1, 3) + t.Y());
	this->translation.set(2, 3, this->translation.get(2, 3) + t.Z());

	//this->translation.println();

	this->updateTransformation();
}

void scenenode::setTranslation(vec3 t)
{
	this->translation.set(0, 3, t.X());
	this->translation.set(1, 3, t.Y());
	this->translation.set(2, 3, t.Z());

	this->updateTransformation();
}

void scenenode::rotate(float angle, vec3 axis)
{

	qtrn r = qtrn(angle, axis);

	/*printf("new quaternion\n");
	axis.println();
	r.print();
	printf("\n");*/

	this->rotationQ = r * this->rotationQ;

	this->updateTransformation();
}

void scenenode::setRotation(float angle, vec3 axis)
{
	qtrn r = qtrn(angle, axis);

	this->rotationQ = r;

	this->updateTransformation();
}

void scenenode::scale(vec3 t)
{
	this->scaling.set(0, 0, this->scaling.get(0, 0) * t.X());
	this->scaling.set(1, 1, this->scaling.get(1, 1) * t.Y());
	this->scaling.set(2, 2, this->scaling.get(2, 2) * t.Z());

	this->updateTransformation();
}

void scenenode::setScale(vec3 t)
{
	this->scaling.set(0, 0, t.X());
	this->scaling.set(1, 1, t.Y());
	this->scaling.set(2, 2, t.Z());

	this->updateTransformation();
}


mat4 scenenode::getModelMatrix()
{
	return this->modelMatrix;
}


void scenenode::setModelMatrix(mat4 m)
{
	this->modelMatrix = m;
}
