#include "Particles.h"


particles::particles()
{
}

//construtor
particles::particles(vec3 _translate, vec3 _direcao)
{
	//indice particula a trabalhar
	this->LastUsedParticle = 0;
	  
	//INICIO TEMPO
	this->lastTime = glutGet(GLUT_ELAPSED_TIME);

	this->translate_to = _translate;
	this->centro = vec3(0, 0, 0);
	this->direcao = _direcao;
	this->reset_position = _translate;
}

void particles::setShader(shader* s)
{
	this->_shader = s;
}

void particles::setTexture(texture t)
{
	this->_texture = t;
}

void particles::setLife(float _life)
{
	this->life = _life;
}

void particles::setAlpha(float alpha1, float alpha2)
{
	this->a1 = alpha1;
	this->a2 = alpha2;
}

float particles::getLife()
{
	return this->life;
}

//CRIAR NOVAS PARTICULAS
void particles::create_particles()
{
	//gestao tempos, queremos criar novas particulas de x em x tempo
	double currentTime = glutGet(GLUT_ELAPSED_TIME);
	this->delta = currentTime - lastTime;
	lastTime = currentTime;

	//controlar numero particulas criadas em x tempo
	this->new_particles = (int)(delta * n_particles); 

	//limitamos numero particulas criadas para 160
	if (new_particles > (int)(0.016f * n_particles)) 
		new_particles = (int)(0.016f * n_particles);

	//para todas novas particulas
	for (int i = 0; i < new_particles; i++)
	{
		//encontramos particula morta 
		int index = findDeadParticles();

		//damos-lhe vida
		particlesContainer[index].setLife(this->getLife()); 

		//damos-lhe posicao a nova particula
		particlesContainer[index].setPosition(centro);

		//cor random
		float L0 = 230, HI = 175;
		if (a1 == 0)
			particlesContainer[index].setColor(255, 255, 0, a1);
		else
		{
			float opacity = L0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - L0)));
			particlesContainer[index].setColor(255, 255, 0, opacity);
		}
		 
		//tamanho random
		L0 = 0.3f, HI = 0.8f;    

		float size = L0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - L0)));
		particlesContainer[index].setSize(size);
	}
}

//para limitar movimento particula
float clip(float n, float lower, float upper) {
	return max(lower, min(n, upper));
}


//vamos percorrer todas as particulas e decidimos se aniamos ou matamos uma
void particles::animate_particles()
{
	//vamos percorrer todo o array 
	int index = 0;

	for (int i = 0; i < n_particles; i++) {

		//referencia a particula
		particle & p = particlesContainer[i];

		//vida positiva, animamos
		if(p.getLife() > 0.0f) 
		{
			//gerar numero aleatorio para retirar vida
			float minus = 0.21 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.21 - 0)));   
			p.setLife(p.getLife() - minus);

			//mudar cor particula, para quando esta quase sem vida
			float randomLife = 2.2 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2.2 - 1.5)));
			if(p.getLife() < randomLife)
			{
				p.setColor(255, 69, 0, a2);   
			}

			//se ainda estiver com vida
			if (p.getLife() > 0.0f)
			{				
				//movimento random particula
				int max = 1, min = -1;  
				int xx = rand() % (max - min + 1) + min; 
				int yy = rand() % (max - min + 1) + min;
				
				direcao.setX(xx);
				direcao.setY(clip( yy, -1, 1));

				p.setPosition(p.getPosition() + direcao);

				//alterar distanca camera por causa blending e para nao desenhar particulas mortas 
				float a =(p.getPosition() - p.getDistance()).length();
				p.setDistance(a*a); 
				
				//posicao e tamanho no GPU buffer
				particule_position_data[4 * index + 0] = p.getPosition().X();
				particule_position_data[4 * index + 1] = p.getPosition().Y();
				particule_position_data[4 * index + 2] = p.getPosition().Z();
				particule_position_data[4 * index + 3] = p.getSize();
				 
				//cores no GPU buffer 
				particule_color_data[4 * index + 0] = p.getR();
				particule_color_data[4 * index + 1] = p.getG();
				particule_color_data[4 * index + 2] = p.getB();
				particule_color_data[4 * index + 3] = p.getA();
			} 

			//para as particulas mosrtas nao serem desenhadas
			else
			{  
				p.setDistance(-1.0f);
			}
		}
		index++;
	}
}

void particles::setCentro(float xx, float yy, float zz)
{
	this->centro = vec3(xx, yy, zz);
}

void particles::setCentro(vec3 c)
{
	this->centro = c;

	for (int i = 0; i < n_particles; i++) {
		particle & p = particlesContainer[i];
		if (p.getLife() > 0.0f)
		{
			p.setPosition(this->centro);
		}
	}
}

void particles::translateTo(vec3 t)
{
	this->translate_to = t;
}

vec3 particles::getCentro()
{
	return this->translate_to;
}

void particles::reset()
{
	this->translate_to = reset_position;
}

//ENCONTRAR PARTICULAS MORTAS
int particles::findDeadParticles()
{
	//procuramos desde ultima para frebte
	for (int i = LastUsedParticle; i<n_particles; i++) {
		if (particlesContainer[i].getLife() < 0) {
			LastUsedParticle = i;
			return i;
		}
	}

	//se nao encontramos, procuramos desde inicio
	for (int i = 0; i<LastUsedParticle; i++) {
		if (particlesContainer[i].getLife() < 0) {
			LastUsedParticle = i;
			return i;
		}
	}

	//just in case
	return 0; 
}


//ordenar particulas
//para efeitos blending e nao desenharmos particulas mortas
void particles::sortParticles()
{
	std::sort(&this->particlesContainer[0], &this->particlesContainer[n_particles]);
}

/////////////////////////////////////////////////////////////////////////////////////////////////BUFFERS
/*
PARA FAZER STREMING
*/
void particles::streming()
{
	glGenVertexArrays(1, &_VAO);
	glBindVertexArray(_VAO);
	{
		//dados vertices para todas particulas
		glGenBuffers(1, &particles_vertex_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, particles_vertex_buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vbo_data), vbo_data, GL_STATIC_DRAW);

		//streaming
		//posicoes para todas particulas	
		glGenBuffers(1, &particles_position_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
		// metemos a null para preenchemos mais tarde
		glBufferData(GL_ARRAY_BUFFER, n_particles * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);

		//cores para todas partiulas
		glGenBuffers(1, &particles_color_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
		// metemos a null para preenchemos mais tarde
		glBufferData(GL_ARRAY_BUFFER, n_particles * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW);	

		//dados vertices para todas particulas
		glGenBuffers(1, &particles_uv_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, particles_uv_buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(uv_data), uv_data, GL_STATIC_DRAW);
		
	}
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
}

//mandamos dados actualizados para arrays respectivos que contem todas as particylas
void particles::enable_location()
{
	//dados de posicao q contem velocidade e gravidade
	glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
	glBufferData(GL_ARRAY_BUFFER, n_particles * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
	glBufferSubData(GL_ARRAY_BUFFER, 0, n_particles * sizeof(GLfloat) * 4, particule_position_data);

	//dados de cor com transparencia
	glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
	glBufferData(GL_ARRAY_BUFFER, n_particles * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
	glBufferSubData(GL_ARRAY_BUFFER, 0, n_particles * sizeof(GLubyte) * 4, particule_color_data);

	//activamos localizaçoes no shader

	//vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, particles_vertex_buffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, (void*)0);  
	 
	//movimento
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);

	//cores
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
	glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, (void*)0);

	//texturas
	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, particles_uv_buffer);
	glVertexAttribPointer(3, 2, GL_FLOAT, 0, 0, (void*)0);
}

void particles::Loop()  
{
	this->create_particles();  
	this->animate_particles(); 
	this->sortParticles();
	this->enable_location();
}

void particles::draw() 
{
	shader temp = *this->_shader;

	glUseProgram(temp.getProgramId());
	glBindVertexArray(this->_VAO);

	this->Loop(); 

	mat4 model = translate(mat4(1), translate_to);
	model = scale(model, vec3(0.1, 0.1, 0.1));

	glUniformMatrix4fv(temp.getUniformId("ModelMatrix"), 1, GL_FALSE, model.getMatrix());

	temp.checkOpenGLError("erro1");
	//activar textura
	this->_texture.bindTexture(0);

	temp.checkOpenGLError("erro2");
	glUniform1i(temp.getUniformId("gSampler"), 0);

	// particles vertices, como usamos sempre mesmos vertices metemos zero com divisor
	glVertexAttribDivisor(0, 0);  

	//posicoes, uma nova por cada particula, metemos 1 como divisor
	glVertexAttribDivisor(1, 1); 

	//cores, uma nova por cada particula, metemos 1 como divisor
	glVertexAttribDivisor(2, 1); 

	// 
	glVertexAttribDivisor(3, 0);

	//desenhamos todas particulas ao mesmo tempo, com instancias
	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 26, n_particles);           

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	 
}
     