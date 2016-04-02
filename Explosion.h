#ifndef _EXPLOSION
#define _EXPLOSION

#include <GL/glew.h>

#include "Shader.h"
#include "texture.h"

#include "Particle.h" 

//numaro partuculas
const int n_particles_explosion = 10000;

//vertices de uma particula
static const GLfloat vbo_data_explosion[] = {
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

static const GLfloat uv_data_explosion[] = {
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

class explosion
{
private:
	//numero particulas criadas
	int new_particles;

	//nos geramos particulas novas de x em x tempo
	double lastTime, delta;

	//indice ultima particula actualizada
	int LastUsedParticle;

	vec3 direcao;
	vec3 centro;
public:
	//frames animacao
	int frames = 130;
	bool enable_explosion = false;
	bool enable_flash = true;

	//cor inicial
	float start_color_r = 255, start_color_g = 255, start_color_b = 0, start_color_a = 5;
	float middle_color_r = 255, middle_color_g = 255, middle_color_b = 0, middle_color_a = 150;
	float end_color_r = 255, end_color_g = 69, end_color_b = 0, end_color_a = 65;

	//construtor
	explosion();
	explosion(vec3 centro, vec3 direcao);

	shader _shader;
	texture _texture;

	vec3 velocity = vec3(1, 1, 1);
	float scale_factor_x = 1;
	float scale_factor_y = 1;
	float scale_factor_z = 1;

	/*
	SETS
	*/
	void setShader(shader s);
	void setTexture(texture t);
	void set_frames(int number);
	void setCentro(float xx, float yy, float zz);
	void set_velocity(float x, float y, float z);
	void set_scale_factor(float valuex, float valuey, float valuez);

	void set_start_color(float r, float g, float b, float a);
	void set_middle_color(float r, float g, float b, float a);
	void set_end_color(float r, float g, float b, float a);


	//bufers
	GLuint _VAO;
	GLuint particles_vertex_buffer;
	GLuint particles_position_buffer;
	GLuint particles_color_buffer;
	GLuint particles_uv_buffer;

	//ARRAYS COM DADOS
	//guardamos posicoes de todas particulas 
	GLfloat* particule_position_data = new GLfloat[n_particles_explosion * 4];

	//guardamos cores todas particulas
	GLubyte* particule_color_data = new GLubyte[n_particles_explosion * 4];

	//array com particulas
	particle particlesContainer[n_particles_explosion];

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

	void bum();
	void draw();
};

#endif
