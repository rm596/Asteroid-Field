#include  "Explosion.h"
#include <algorithm>
#include <GL/freeglut_std.h>
#include "vec3.h"
#include <iostream>

explosion::explosion()
{
}

explosion::explosion(vec3 _centro, vec3 _direcao)
{
	//indice particula a trabalhar 
	this->LastUsedParticle = 0;

	//INICIO TEMPO
	this->lastTime = glutGet(GLUT_ELAPSED_TIME);

	this->centro = _centro;
	this->direcao = _direcao;
}

void explosion::setShader(shader s)
{
	this->_shader = s;
}

void explosion::setTexture(texture t)
{
	this->_texture = t;
}

void explosion::setCentro(float xx, float yy, float zz)
{
	this->centro = vec3(xx, yy, zz);
}

int explosion::findDeadParticles()
{
	//procuramos desde ultima para frebte
	for (int i = LastUsedParticle; i < n_particles_explosion; i++) {
		if (particlesContainer[i].getLife() < 0) {
			LastUsedParticle = i;
			return i;
		}
	}

	//se nao encontramos, procuramos desde inicio
	for (int i = 0; i < LastUsedParticle; i++) {
		if (particlesContainer[i].getLife() < 0) {
			LastUsedParticle = i;
			return i;
		}
	}

	//just in case
	return 0;
}

void explosion::create_particles()
{
	//gestao tempos, queremos criar novas particulas de x em x tempo
	double currentTime = glutGet(GLUT_ELAPSED_TIME);
	this->delta = currentTime - lastTime;
	lastTime = currentTime;

	//controlar numero particulas criadas em x tempo
	this->new_particles = (int)(delta * n_particles_explosion);

	//limitamos numero particulas criadas para 160
	if (new_particles > (int)(0.036f * n_particles_explosion))
		new_particles = (int)(0.036f * n_particles_explosion);

	//para todas novas particulas
	for (int i = 0; i < new_particles; i++)
	{
		//encontramos particula morta 
		int index = findDeadParticles();

		//damos-lhe vida   
		particlesContainer[index].setLife(20.0f);

		//damos-lhe posicao a nova particula
		particlesContainer[index].setPosition(centro);

		//cor random
		float L0 = 230, HI = 175;
		particlesContainer[index].setColor(start_color_r, start_color_g, start_color_b, start_color_a);

		//tamanho random
		L0 = 0.3f, HI = 0.8f;

		float size = L0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - L0)));
		particlesContainer[index].setSize(size);
	}
}

void explosion::animate_particles()
{
	//vamos percorrer todo o array 
	int index = 0;

	for (int i = 0; i < n_particles_explosion; i++) {

		//referencia a particula
		particle & p = particlesContainer[i];

		//vida positiva, animamos
		if (p.getLife() > 0.0f)
		{
			//gerar numero aleatorio para retirar vida
			float minus = 0.21 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.21 - 0)));
			p.setLife(p.getLife() - minus);

			//mudar cor particula, para quando esta quase sem vida
			float randomLife = 2 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2 - 1.5)));

			if (p.getLife() < 7)
			{
				p.setColor(middle_color_r, middle_color_g, middle_color_b, middle_color_a);
			}

			if (p.getLife() < randomLife)
			{
				p.setColor(end_color_r, end_color_g, end_color_b, end_color_a);
			}

			//se ainda estiver com vida
			if (p.getLife() > 0.0f)
			{
				//movimento random particula
				int max = 10, min = -10;
				int xx = rand() % (max - min + 1) + min;
				int yy = rand() % (max - min + 1) + min;
				int zz = rand() % (max - min + 1) + min;

				//fazer circulo

				//if(p.getLife() < 7)
				//{
				vec3 new_direction = p.getPosition() + direcao * velocity;
				float distancia = new_direction.distance(centro);
				if (distancia < 500)
				{
					direcao.setX(xx);
					direcao.setZ(zz);
					direcao.setY(yy);
					p.setPosition(p.getPosition() + direcao * velocity);
				}
				//}				

				//alterar distanca camera por causa blending e para nao desenhar particulas mortas 
				float a = (p.getPosition() - p.getDistance()).length();
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

void explosion::sortParticles()
{
	std::sort(&this->particlesContainer[0], &this->particlesContainer[n_particles_explosion]);
}

void explosion::enable_location()
{
	//dados de posicao q contem velocidade e gravidade
	glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
	glBufferData(GL_ARRAY_BUFFER, n_particles_explosion * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
	glBufferSubData(GL_ARRAY_BUFFER, 0, n_particles_explosion * sizeof(GLfloat) * 4, particule_position_data);

	//dados de cor com transparencia
	glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
	glBufferData(GL_ARRAY_BUFFER, n_particles_explosion * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
	glBufferSubData(GL_ARRAY_BUFFER, 0, n_particles_explosion * sizeof(GLubyte) * 4, particule_color_data);

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

void explosion::streming()
{
	glGenVertexArrays(1, &_VAO);
	glBindVertexArray(_VAO);
	{
		//dados vertices para todas particulas
		glGenBuffers(1, &particles_vertex_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, particles_vertex_buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vbo_data_explosion), vbo_data_explosion, GL_STATIC_DRAW);

		//streaming
		//posicoes para todas particulas	
		glGenBuffers(1, &particles_position_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
		// metemos a null para preenchemos mais tarde
		glBufferData(GL_ARRAY_BUFFER, n_particles_explosion * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);

		//cores para todas partiulas
		glGenBuffers(1, &particles_color_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
		// metemos a null para preenchemos mais tarde
		glBufferData(GL_ARRAY_BUFFER, n_particles_explosion * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW);

		//dados vertices para todas particulas
		glGenBuffers(1, &particles_uv_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, particles_uv_buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(uv_data_explosion), uv_data_explosion, GL_STATIC_DRAW);

	}
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void explosion::Loop()
{
	this->create_particles();
	this->animate_particles();
	this->sortParticles();
	this->enable_location();
	this->draw();
}

void explosion::draw()
{
	//if (this->enable_explosion)
	//{
		//fazer animacao
		bum();

		// particles vertices, como usamos sempre mesmos vertices metemos zero com divisor
		glVertexAttribDivisor(0, 0);

		//posicoes, uma nova por cada particula, metemos 1 como divisor
		glVertexAttribDivisor(1, 1);

		//cores, uma nova por cada particula, metemos 1 como divisor
		glVertexAttribDivisor(2, 1);

		// 
		glVertexAttribDivisor(3, 0);

		//desenhamos todas particulas ao mesmo tempo, com instancias
		glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 26, n_particles_explosion);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(3);
	//}
}

void explosion::set_velocity(float x, float y, float z)
{
	this->velocity = vec3(x, y, z);
}

void explosion::set_scale_factor(float valuex, float valuey, float valuez)
{
	this->scale_factor_x = valuex;
	this->scale_factor_y = valuey;
	this->scale_factor_z = valuez;
}

void explosion::set_start_color(float r, float g, float b, float a)
{
	this->start_color_r = r;
	this->start_color_g = g;
	this->start_color_b = b;
	this->start_color_a = a;
}

void explosion::set_middle_color(float r, float g, float b, float a)
{
	this->middle_color_r = r;
	this->middle_color_g = g;
	this->middle_color_b = b;
	this->middle_color_a = a;
}

void explosion::set_end_color(float r, float g, float b, float a)
{
	this->end_color_r = r;
	this->end_color_g = g;
	this->end_color_b = b;
	this->end_color_a = a;
}

void explosion::bum()
{
	//contrair
	if (frames >= 100)
	{
		set_velocity(0.25, 0.25, 0.25);

		if (scale_factor_x < 0)
		{
			scale_factor_x = 0;
			scale_factor_y = 0;
			scale_factor_z = 0;
		}
		else
		{
			scale_factor_x -= 0.2;
			scale_factor_y -= 0.2;
			scale_factor_z += 1;
		}

		//cores
		set_start_color(255, 255, 0, 255);
		set_middle_color(255, 255, 0, 200);
		set_end_color(255, 0, 0, 255);
	}
	//expandir
	else
	{

		set_velocity(0.25, 0.25, 0.25);

		scale_factor_x += 0.15;
		scale_factor_y = 0.75;
		scale_factor_z += 0.15;

		set_start_color(255, 255, 0, 255);
		set_middle_color(255, 128, 0, 150);
		set_end_color(255, 255, 0, 255);
	}
	frames -= 1;
}

void explosion::set_frames(int number)
{
	this->frames = 130;
}

