#ifndef _H_ASTEROID
#define _H_ASTEROID

#include "scenenode.h"
#include "texture.h"
#include "luz.h"
#include "perlin/ppm.h"
#include "perlin/PerlinNoise.h"

#include <stdlib.h>
//to test perlin noise
#include <cmath>

class asteroid : public scenenode
{
private:
	vec3 direction;
	vec3 rotationAxis;
	float velocity;

	bool is_playing;

	texture asteroid_texture;

	luz * external_light;

public:
	/* constructors */
	asteroid();

	asteroid(vec3 initialPosition);

	/* initializes asteroid variables */
	void init();

	/* sets asteroid moving direction */
	void setDirection(vec3 d);

	/* sets the velocity the asteroid moves */
	void setVelocity(float v);

	/* plays pauses asteroid movement */
	void play();

	/* sets an external light preferably from xwing */
	void setExternalLight(luz* l);

	/* draws and updates position */
	void draw();

	/* updates asteroid location */
	void update();

	vec3 get_position();

};

#endif