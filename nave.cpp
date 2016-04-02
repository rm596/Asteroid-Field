#include "nave.h"

void nave::reset_engines()
{
	std::cout << "reset" << std::endl;
	this->getMotores(0)->reset();
	this->getMotores(1)->reset();
	this->getMotores(2)->reset();
	this->getMotores(3)->reset();
}

nave::nave()
{
	this->l = luz(vec3(0, 4, -3), 0.85f, 0.85f, 0.85f);
	this->l.setPotencia(50.0f);

	scenenode::scenenode();
}

void nave::initMotores()
{
	texture part_text;
	part_text.loadTexture2D("objetos/smoke2.jpg", true);
	part_text.setFiltering(TEXTURE_FILTER_MAG_BILINEAR, TEXTURE_FILTER_MIN_BILINEAR_MIPMAP);


	motores = std::vector<particles>(4);
	// motor1
	motores[0] = particles(vec3(-1, 1, 4.5), vec3(0, 0, 1));
	motores[0].setShader(this->motores_shader);
	motores[0].setTexture(part_text);
	motores[0].streming();
	(*this->motores_shader).checkOpenGLError("ERROR: Could not destroy shaders.");

	// motor2
	motores[1] = particles(vec3(-1, -1, 4.5), vec3(0, 0, 1));
	motores[1].setShader(this->motores_shader);
	motores[1].setTexture(part_text);
	motores[1].streming();
	(*this->motores_shader).checkOpenGLError("ERROR: Could not destroy shaders.");

	// motor3
	motores[2] = particles(vec3(1, -1, 4.5), vec3(0, 0, 1));
	motores[2].setShader(this->motores_shader);
	motores[2].setTexture(part_text);
	motores[2].streming();
	(*this->motores_shader).checkOpenGLError("ERROR: Could not destroy shaders.");

	// motor4
	motores[3] = particles(vec3(1, 1, 4.5), vec3(0, 0, 1));
	motores[3].setShader(this->motores_shader);
	motores[3].setTexture(part_text);
	motores[3].streming();
	(*this->motores_shader).checkOpenGLError("ERROR: Could not destroy shaders.");

	this->enable_engine = true;
}

void nave::setMotoresShader(shader * s)
{
	this->motores_shader = s;
}

particles * nave::getMotores(int position)
{
	return  & this->motores[position];

}

void nave::setLuz(luz _l_)
{
	this->l = _l_;
}

void nave::setLuzPosicao(vec3 pos)
{
	this->l.setPosition(pos);
}

luz nave::getLuz()
{
	return this->l;
}

void nave::setCamera(camera* c)
{
	this->main_camera = c;
	this->l.setCamera(c);
}

void nave::setActive(bool a)
{
	this->active = a;
}

void nave::draw()
{
	if (this->active)
	{
		// if no shader is not associated with object or his parent the object is not drawn
		if ((this->getShaderId()))
		{
			shader temp = *this->getShaderId();
			glUseProgram(temp.getProgramId());
			//posicao da luz
			glUniform3fv(temp.getUniformId("lightPosition"), 1, l.getPositionArray());
			//posicao camera	
			float cameraPosition[] = { 0, 3, -3 };
			glUniform3fv(temp.getUniformId("cameraPosition"), 1, cameraPosition);
			//potencia luz
			glUniform1f(temp.getUniformId("LightPower"), l.getPotencia());
			//cor luz 
			glUniform3fv(temp.getUniformId("LightColor"), 1, l.getColor());

			temp.checkOpenGLError("error loading light");

		}
		scenenode::draw();

		glUseProgram(0);

		shader temp2 = (*this->motores_shader);
		camera tempcamera = (*this->main_camera);

		glUseProgram(temp2.getProgramId());

		//TODO: passar isto para a camara talvez...
		glUniformMatrix4fv(temp2.getUniformId("ViewMatrix"), 1, GL_FALSE, tempcamera.getViewMatrix().getMatrix());
		glUniformMatrix4fv(temp2.getUniformId("ProjectionMatrix"), 1, GL_FALSE, tempcamera.getProjectionMatrix().getMatrix());

		this->motores[0].draw();
		this->motores[1].draw();
		this->motores[2].draw();
		this->motores[3].draw();

		glUseProgram(0);
		glBindVertexArray(0);

		temp2.checkOpenGLError("ERROR: Could not draw scene.");
	}

}

void nave::translate(vec3 t)
{
	//this->motores[0].setCentro(this->motores[0].getCentro() + t);
	scenenode::translate(t);
}

void nave::rotate(float angle, vec3 axis)
{
	scenenode::rotate(angle, axis);

	if(enable_engine)
	{
		this->direction += angle;

		mat3 rotation_mat = rotation(mat3(1.0), angle * 0.0172, axis);
		
		vec3 centro = this->getMotores(0)->getCentro();
		centro = rotation_mat * centro;
		this->getMotores(0)->translateTo(centro);

		centro = this->getMotores(1)->getCentro();
		centro = rotation_mat * centro;
		this->getMotores(1)->translateTo(centro);

		centro = this->getMotores(2)->getCentro();
		centro = rotation_mat * centro;
		this->getMotores(2)->translateTo(centro);

		centro = this->getMotores(3)->getCentro();
		centro = rotation_mat * centro;
		this->getMotores(3)->translateTo(centro);

		if (this->direction == 0.0f)
			reset_engines();
	}
}

void nave::shoot(bool b)
{
	if (b)
	{
		//this->l.setRed(1.0);
		this->l.setColor(1, 0.85, 0.85);
	}
		
	else {
		//this->l.setRed(0.85);
		this->l.setColor(0.85, 0.85, 0.85);
	}
}

void nave::start_engine()
{
	this->reset_engines();
	this->getMotores(0)->setLife(5);
	this->getMotores(0)->setAlpha(65, 65);

	this->getMotores(1)->setLife(5);
	this->getMotores(1)->setAlpha(65, 65);

	this->getMotores(2)->setLife(5);
	this->getMotores(2)->setAlpha(65, 65);

	this->getMotores(3)->setLife(5);
	this->getMotores(3)->setAlpha(65, 65);
}

void nave::stop_engine()
{
	this->getMotores(0)->setAlpha(0, 0);

	this->getMotores(1)->setAlpha(0, 0);

	this->getMotores(2)->setAlpha(0, 0);

	this->getMotores(3)->setAlpha(0, 0);

	this->getMotores(0)->translateTo(vec3(0, 0, 1000));
	this->getMotores(1)->translateTo(vec3(0, 0, 1000));
	this->getMotores(2)->translateTo(vec3(0, 0, 1000));
	this->getMotores(3)->translateTo(vec3(0, 0, 1000));
}

vec3 nave::get_position()
{
	float x = this->modelMatrix.get(0, 3);
	float y = this->modelMatrix.get(1, 3);
	float z = this->modelMatrix.get(2, 3);

	return vec3(x, y, z);
}