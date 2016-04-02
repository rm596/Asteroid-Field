#ifndef _H_CONTROLLER
#define _H_CONTROLLER

#include "includes.h"


/* class that controlls the scene */
class controller
{
private:
	asteroid *asteroid_field;
	int asteroids_number;
	nave *xwing;
	missil *pewpew;
	explosion *boom;
	lightspeed *ls;
	camera *main_camera;

	vec3 real_position = vec3(0.0f, 0.0f, 0.0f);

	// variables controling lasers... pew pew
	bool firing = false;
	int firetime = 0;
	int firemax = 3000;
	int lightredmax = 200;
	int lightred = 0;
	vec3 ep_position;

	int time;

	// current action
	int action = 0;

	// action times
	int actions[34] = { 
		3000, 
		200, 
		//rotate1
		20000, 
		0, 
		0, 
		//rotate2
		1000,
		0,
		0,
		//rotate3
		0,
		0,
		0,
		//rotate4
		5000,
		0,
		0,
		//rotate5
		10000,
		0,
		0,
		//rotate6
		2000,
		0,
		0,
		//shoot
		2000,
		900,
		900,
		//rotate7
		0,
		0,
		0,
		//shot
		1000,
		900,
		900,
		//lightspeed
		20000,
		// go ship go
		1000,
		1000,
		0,
		0// default
	};

	int last_frame;
	bool is_play;

	// variables for asteroid updater
	////////////////////////////TIME
	int timeDeltaMax = 5000; // Limit the maximum delta to 5000ms = 5s (really low fps)
	int timemin = 17;
	int timetotal = 0;
	int timeCurrent = 0, timeDelta = 0, timePrevious = 0;

	void check_actions();
	void execute_actions();

public:
	void shoot();

	vec3 getExplosionPosition();

	bool isFiring();

	controller();

	controller(asteroid *a, int n_a, camera *c, nave *n, missil *m, explosion *e, lightspeed *_ls);

	/* should be called in each update */
	void update();

	void play();

	void stop();

	void update_asteroids();
};

#endif