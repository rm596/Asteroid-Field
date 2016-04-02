#ifndef _PARTICLES
#define _PARTICLES

#include <GL/glew.h>

#include "Shader.h"
#include "texture.h"

#include "Particle.h" 
#include <algorithm>
#include <GL/freeglut_std.h>
#include "vec3.h"

//numaro partuculas
const int n_particles = 10000;

//vertices de uma particula
static const GLfloat vbo_data[] = {
	// Front face
	-1,-1,1, 1,-1,1, -1,1,1, 1,1,1,
	// Right face
	1,1,1, 1,-1,1, 1,1,-1, 1,-1,-1,
	// Back face
	1,-1,-1, -1,-1,-1, 1,1,-1, -1,1,-1,
	// Left face
	-1,1,-1, -1,-1,-1, -1,1,1, -1,-1,1,
	// Bottom face
	-1,-1,1, -1,-1,-1, 1,-1,1, 1,-1,-1,

	// move to top
	1,-1,-1, -1,1,1,

	// Top Face
	-1,1,1, 1,1,1, -1,1,-1, 1,1,-1
};

static const GLfloat uv_data[] = {
	// Front face
	0,0, 1,0, 0,1, 1,1,
	// Right face
	0,1, 0,0, 1,1, 1,0,
	// Back face
	0,0, 1,0, 0,1, 1,1,
	// Left face
	0,1, 0,0, 1,1, 1,0,
	// Bottom face
	0,1, 0,0, 1,1, 1,0,

	1,0, 0,0,

	// Top face
	0,0, 1,0, 0,1, 1,1
};

class particles
{
private:
	//numero particulas criadas
	int new_particles;

	//nos geramos particulas novas de x em x tempo
	double lastTime, delta;

	//indice ultima particula actualizada
	int LastUsedParticle;

	//moviemento particulas
	vec3 direcao;
	//onde particulas nascem
	vec3 centro;
	//para mover com nave
	vec3 translate_to = vec3(0, 0, 0);
	//fazer reset
	vec3 reset_position;

	float life = 1;
	//color 1
	int a1 = 0;
	int a2 = 0;
public:
	//construtor
	particles();
	particles(vec3 translate, vec3 direcao);

	shader *_shader;
	texture _texture;

	void setShader(shader *s);
	void setTexture(texture t);

	//bufers
	GLuint _VAO;
	GLuint particles_vertex_buffer;
	GLuint particles_position_buffer;
	GLuint particles_color_buffer;
	GLuint particles_uv_buffer;

	//ARRAYS COM DADOS
	//guardamos posicoes de todas particulas 
	GLfloat* particule_position_data = new GLfloat[n_particles * 4];

	//guardamos cores todas particulas
	GLubyte* particule_color_data = new GLubyte[n_particles * 4];

	//array com particulas
	particle particlesContainer[n_particles];

	//CENTRO
	void setCentro(float xx, float yy, float zz);
	void setCentro(vec3 c);
	void translateTo(vec3 t);
	vec3 getCentro();
	void reset();

	void setLife(float _life);
	void setAlpha(float alpha1, float alpha2);
	float getLife();

	//encontrar particulas mortas
	//retorna indice da primeira encontrada
	int findDeadParticles();

	//criar novas particulas
	void create_particles();

	//fazer animacao
	void animate_particles();

	//ordenar particulas
	//precisamos ordenar pois elementos com blending, a ordem tem importancia
	void sortParticles();

	void enable_location();

	//carregar streaming
	void streming();

	void Loop();

	void draw();
};

#endif
