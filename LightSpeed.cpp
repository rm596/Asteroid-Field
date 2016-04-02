#include "LightSpeed.h"
#include <algorithm>
#include <GL/freeglut_std.h>
#include "vec3.h"

lightspeed::lightspeed()
{
}

lightspeed::lightspeed(vec3 _direcao)
{
	//indice particula a trabalhar
	this->LastUsedParticle = 0;

	//INICIO TEMPO
	this->lastTime = glutGet(GLUT_ELAPSED_TIME);

	this->direcao = _direcao;
}

void lightspeed::setShader(shader s)
{
	this->_shader = s;
}

void lightspeed::setTexture(texture t)
{
	this->_texture = t;
}

void lightspeed::set_max_amount_particles(float number)
{
	this->max_amount_particles = number;
}

void lightspeed::set_min_radius_particles(float number)
{
	this->min_radius_particles = number;
}

void lightspeed::set_max_radius_particles(float number)
{
	this->max_radius_particles = number;
}

void lightspeed::set_scale_factor(float number)
{
	this->scale = number;
}

void lightspeed::set_direction(float x, float y, float z)
{
	this->direcao = vec3(x, y, z);
}

void lightspeed::set_jump(bool r)
{
	this->enable_speed = r;

}

void lightspeed::set_live_color(float r, float g, float b, float a)
{
	this->live_r = r;
	this->live_g = g;
	this->live_b = b;
	this->live_a = a;
}

void lightspeed::set_dead_color(float r, float g, float b, float a)
{
	this->dead_r = r;
	this->dead_g = g;
	this->dead_b = b;
	this->dead_a = a;
}

void lightspeed::set_zz(float z)
{
	this->ZZ = z;
}

float lightspeed::get_scale()
{
	return this->scale;
}

int lightspeed::findDeadParticles()
{
	//procuramos desde ultima para frebte
	for (int i = LastUsedParticle; i<n_light_speed; i++) {
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

void lightspeed::create_particles()
{
	//gestao tempos, queremos criar novas particulas de x em x tempo
	double currentTime = glutGet(GLUT_ELAPSED_TIME);
	this->delta = currentTime - lastTime;
	lastTime = currentTime;

	//controlar numero particulas criadas em x tempo
	this->new_particles = (int)(delta * n_light_speed);

	//limitamos numero particulas criadas para 160
	if (new_particles > (int)(max_amount_particles * n_light_speed))
		new_particles = (int)(max_amount_particles * n_light_speed);

	//para todas novas particulas 
	for (int i = 0; i < new_particles; i++)
	{    
		//encontramos particula morta  
		int index = findDeadParticles();

		//damos-lhe vida   
		particlesContainer[index].setLife(15.0f); 

		float L0 = min_radius_particles, HI = max_radius_particles;
		float x = L0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - L0)));
		float y = L0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - L0)));

		L0 = 0, HI = ZZ;

		float z = 0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - L0)));

		//damos-lhe posicao a nova particula
		particlesContainer[index].setPosition(vec3(x, y, z));

		particlesContainer[index].setColor(live_r, live_g, live_b, live_a);

		//tamanho random 
		L0 = 0.3f, HI = 0.8f;

		float size = L0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - L0)));
		particlesContainer[index].setSize(1);
	}
} 
   
void lightspeed::animate_particles()
{ 
	//vamos percorrer todo o array 
	int index = 0; 

	for (int i = 0; i < n_light_speed; i++) {

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
			
			//cor particula morta
			if (p.getLife() < randomLife)
			{
				p.setColor(dead_r, dead_g, dead_b, dead_a); 
			}  

			//se ainda estiver com vida
			if (p.getLife() > 0.0f)
			{		
				//vir na nossa direcao
				p.setPosition(p.getPosition() + direcao);

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

void lightspeed::sortParticles()
{
	std::sort(&this->particlesContainer[0], &this->particlesContainer[n_light_speed]);
}

void lightspeed::enable_location()
{
	//dados de posicao q contem velocidade e gravidade
	glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
	glBufferData(GL_ARRAY_BUFFER, n_light_speed * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
	glBufferSubData(GL_ARRAY_BUFFER, 0, n_light_speed * sizeof(GLfloat) * 4, particule_position_data);

	//dados de cor com transparencia
	glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
	glBufferData(GL_ARRAY_BUFFER, n_light_speed * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
	glBufferSubData(GL_ARRAY_BUFFER, 0, n_light_speed * sizeof(GLubyte) * 4, particule_color_data);

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
	//glEnableVertexAttribArray(3);
	//glBindBuffer(GL_ARRAY_BUFFER, particles_uv_buffer);
	//glVertexAttribPointer(3, 2, GL_FLOAT, 0, 0, (void*)0);
}

void lightspeed::streming()
{
	glGenVertexArrays(1, &_VAO);
	glBindVertexArray(_VAO);
	{
		//dados vertices para todas particulas
		glGenBuffers(1, &particles_vertex_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, particles_vertex_buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vbo_data_speed), vbo_data_speed, GL_STATIC_DRAW);

		//streaming
		//posicoes para todas particulas	
		glGenBuffers(1, &particles_position_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
		// metemos a null para preenchemos mais tarde
		glBufferData(GL_ARRAY_BUFFER, n_light_speed * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);

		//cores para todas partiulas
		glGenBuffers(1, &particles_color_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
		// metemos a null para preenchemos mais tarde
		glBufferData(GL_ARRAY_BUFFER, n_light_speed * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW);

		//dados vertices para todas particulas
		//glGenBuffers(1, &particles_uv_buffer);
		//glBindBuffer(GL_ARRAY_BUFFER, particles_uv_buffer);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(uv_data_speed), uv_data_speed, GL_STATIC_DRAW);

	}
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0); 
}

void lightspeed::Loop()
{
	this->create_particles();
	this->animate_particles();
	this->sortParticles();
	this->enable_location();
	this->draw();
}

void lightspeed::draw()
{
	//activar textura
	//this->_texture.bindTexture(0);
	//int iSamplerLoc = glGetUniformLocation(this->_shader.getProgramId(), "gSampler");
	//this->_shader.checkOpenGLError("erro na textura");
	//glUniform1i(iSamplerLoc, 0);

	//mandar escala
	glUniform1f(glGetUniformLocation(this->_shader.getProgramId(), "scale_factor"), this->scale);

	// particles vertices, como usamos sempre mesmos vertices metemos zero com divisor
	glVertexAttribDivisor(0, 0);

	//posicoes, uma nova por cada particula, metemos 1 como divisor
	glVertexAttribDivisor(1, 1);

	//cores, uma nova por cada particula, metemos 1 como divisor
	glVertexAttribDivisor(2, 1);

	// 
	//glVertexAttribDivisor(3, 0);

	//desenhamos todas particulas ao mesmo tempo, com instancias
	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 26, n_light_speed);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	//glDisableVertexAttribArray(3);
}

void lightspeed::jump()
{
	//primeira fase
	if (enable_speed && frames1>200)
	{
		//dizer para particulas serem criadas mais perto uma das outras
		set_min_radius_particles(-350);
		set_max_radius_particles(350);

		//aumentar numero particulas criadas em cada frame
		set_max_amount_particles(0.026f);
		//diminuir velocidade
		set_direction(0, 0, 0.25);
		//alterar cor particulas
		set_live_color(234, 224, 251, 255);
		set_dead_color(74, 63, 155, 255);
		//model = scale(mat4(1.0f), vec3(0.02, 0.02, 0.35));

		//aproximar particulas de mim
		set_zz(-100);
		frames1 -= 1;
	}
	//segunda fase
	else if (enable_speed && frames1 > 150 && frames1 <= 200)
	{
		set_max_amount_particles(0.056f);
		set_direction(0, 0, 1);
		set_scale_factor(20);

		set_live_color(234, 224, 251, 255);
		set_dead_color(74, 63, 155, 255);
		//model = scale(mat4(1.0f), vec3(0.06, 0.06, 0.35));
		frames1 -= 1;
	}
	else if (enable_speed && frames1 > 100 && frames1 <= 150)
	{
		//model = scale(mat4(1.0f), vec3(0.06, 0.06, 0.55));
		frames1 -= 1;
	}
	//terceira fase
	else if (enable_speed && frames1 <= 100 && frames1>50)
	{
		//model = scale(mat4(1.0f), vec3(0.04, 0.04, 0.55));
		set_live_color(234, 224, 251, 10);
		set_dead_color(74, 63, 155, 10);
		set_max_amount_particles(0.05f);
		frames1 -= 1;
	} else if(enable_speed && frames1<=50)
	{
		set_live_color(234, 224, 251, 1);
		set_dead_color(74, 63, 155, 1);
		set_max_amount_particles(0.05f);
		frames1 -= 1;
	}
}
