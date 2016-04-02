#ifndef _LIGHT
#define _LIGHT

#include <GL/glew.h>

#include "Shader.h"
#include "texture.h"

#include "Particle.h" 
#include "Obj.h"

//numaro partuculas
const int n_light_speed = 10000;

//vertices de uma particula
static const GLfloat vbo_data_speed[] = {
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

class lightspeed
{
private:
	obj one;
	//numero particulas criadas
	int new_particles;

	//nos geramos particulas novas de x em x tempo
	double lastTime, delta;

	//indice ultima particula actualizada
	int LastUsedParticle;

	vec3 direcao;

	bool enable_speed = false;
	float max_amount_particles = 0.03f;    
	int min_radius_particles = -500;
	int max_radius_particles = 500;

	int frames1 = 300;

	float scale = 1;

	//cor particula viva    
	float live_r=255, live_g=255, live_b=255, live_a=35;

	//cor particula morta
	float dead_r = 225, dead_g = 225, dead_b = 233, dead_a = 50;

	//para criar particulas mais perto de mim
	float ZZ = -250;

public:
	//construtor
	lightspeed();
	lightspeed(vec3 direcao);

	shader _shader;
	texture _texture;

	void setShader(shader s);
	void setTexture(texture t);

	//bufers
	GLuint _VAO;
	GLuint particles_vertex_buffer;
	GLuint particles_position_buffer;
	GLuint particles_color_buffer;
	GLuint particles_uv_buffer;

	//ARRAYS COM DADOS
	//guardamos posicoes de todas particulas 
	GLfloat* particule_position_data = new GLfloat[n_light_speed * 4];

	//guardamos cores todas particulas
	GLubyte* particule_color_data = new GLubyte[n_light_speed * 4];

	//array com particulas
	particle particlesContainer[n_light_speed];

	//set dados
	void set_max_amount_particles(float number);
	void set_min_radius_particles(float number);
	void set_max_radius_particles(float number);
	void set_scale_factor(float number);
	void set_direction(float x, float y, float z);

	void set_jump(bool r);

	void set_live_color(float r, float g, float b, float a);
	void set_dead_color(float r, float g, float b, float a);
	void set_zz(float z);

	float get_scale();

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

	void jump();
};

#endif
