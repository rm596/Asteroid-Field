
#include "asteroid.h"


asteroid::asteroid() : scenenode() {}

void asteroid::init()
{
	obj asteroid_obj = obj();

	int randNum = (rand() % 30) + 1;

	//printf("rand=%d\n",randNum);

	std::string rndobj = "objetos/asteroides/3Dmodels/asteroid"+ std::to_string(randNum) +".obj";

	asteroid_obj.createMesh(std::string(rndobj), std::string("objetos/asteroid.mtl"));

	//sets asteroids
	this->setObj(asteroid_obj);
	this->load_data(asteroid_obj);
	this->is_playing = false;
	this->direction = vec3(0.0f, 0.0f, 0.0f);
	this->velocity = 0.0f;
	this->rotationAxis = vec3(0.0f, 0.0f, 0.0f);

	int randNum2 = (rand() % 5) + 1;

	//printf("rand=%d\n", randNum2);

	std::string randtex = "objetos/asteroides/Textures/AM"+std::to_string(randNum2)+".jpg";
	this->asteroid_texture.loadTexture2D(randtex, true);

	this->asteroid_texture.setFiltering(TEXTURE_FILTER_MAG_BILINEAR, TEXTURE_FILTER_MIN_BILINEAR_MIPMAP);
	this->setTexture(this->asteroid_texture);
}



void asteroid::setDirection(vec3 d)
{
	this->direction = d.normalize();

	// find one of infinite perpendiculars using this formula
	//x1 * x2 + y1 * y2 + z1 * z2 = 0
	float z1 = d.Z();

	if (z1 == 0.0f) // avoid divide by 0
		z1 = 0.01f;


	float x = ((float)(rand() % 100)) / 100.0f;
	float y = ((float)(rand() % 100)) / 100.0f;

	float z = (-d.X()*x - d.Y()*y) / z1;

	// sets new vector as rotation axis
	this->rotationAxis = vec3(x, y, z).normalize();
}

void asteroid::setVelocity(float v)
{
	this->velocity = v;
}

void asteroid::play()
{
	this->is_playing = !this->is_playing;
	//printf("is playing: %d\n", this->is_playing);
}

void asteroid::setExternalLight(luz* l)
{
	this->external_light = l;
}


void asteroid::draw()
{

	scenenode::draw();
}

void asteroid::update()
{
	if (this->is_playing)
	{
		this->translate(this->velocity*this->direction);

		if (this->rotationAxis != vec3(0.0f, 0.0f, 0.0f))
		{
			this->rotate(20.0f*this->velocity, this->rotationAxis);
		}
	}
}

vec3 asteroid::get_position()
{
	float x = this->modelMatrix.get(0, 3);
	float y = this->modelMatrix.get(1, 3);
	float z = this->modelMatrix.get(2, 3);

	return vec3(x, y, z);
}