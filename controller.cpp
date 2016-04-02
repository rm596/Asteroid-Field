#include "controller.h"

controller::controller(){}

controller::controller(asteroid *a, int n_a, camera *c, nave *n, missil *m, explosion *e, lightspeed *_ls)
{
	this->asteroid_field = a;
	this->asteroids_number = n_a;
	this->main_camera = c;
	this->xwing = n;
	this->pewpew = m;
	this->boom = e;
	this->ls = _ls;
	this->time = 0;

	this->is_play = false;
}


void controller::update()
{
	int current_frame = glutGet(GLUT_ELAPSED_TIME);

	if (this->is_play)
	{
		update_asteroids();
		if (action > 1)
		{
			for (int i = 0; i < this->asteroids_number; i++)
				asteroid_field[i].translate(vec3(0, 0, 0.5));

			this->real_position += vec3(0, 0, 0.5);
		}
		time += current_frame - last_frame;

		if (time >= actions[action])
		{
			execute_actions();
			check_actions();
		}
	}

	last_frame = current_frame;
}

void controller::execute_actions()
{
	switch (this->action)
	{
	case 0:
		(*this->xwing).setActive(true);
		(*this->xwing).translate(vec3(0,0,-5));
		break;
	case 1:
		(*this->xwing).start_engine();
		break;

		//rotate1
	case 2:
		(*this->xwing).rotate(0.5, vec3(0, 0, 1));
		(*this->main_camera).rotate(0.5, vec3(0.0f, 1.0f, 0.0f));
		for (int i = 0; i < this->asteroids_number; i++)
			asteroid_field[i].translate(vec3(1, 0, 0));

		this->real_position += vec3(1, 0, 0);
		break;
	case 3:
		for (int i = 0; i < this->asteroids_number; i++)
			asteroid_field[i].translate(vec3(1, 0, 0));

		this->real_position += vec3(1, 0, 0);
		break;
	case 4:
		(*this->main_camera).rotate(-0.5, vec3(0.0f, 1.0f, 0.0f));
		(*this->xwing).rotate(-0.5, vec3(0, 0, 1));
		break;

		//rotate2
	case 5:
		(*this->xwing).rotate(-0.5, vec3(0, 0, 1));
		(*this->main_camera).rotate(-0.5, vec3(0.0f, 1.0f, 0.0f));
		for (int i = 0; i < this->asteroids_number; i++)
			asteroid_field[i].translate(vec3(-1, 0, 0));

		this->real_position += vec3(-1, 0, 0);

		break;
	case 6:
		for (int i = 0; i < this->asteroids_number; i++)
			asteroid_field[i].translate(vec3(-1, 0, 0));

		this->real_position += vec3(-1, 0, 0);
		break;
	case 7:
		(*this->xwing).rotate(0.5, vec3(0, 0, 1));
		(*this->main_camera).rotate(0.5, vec3(0.0f, 1.0f, 0.0f));
		break;

		//rotate3
	case 8:
		(*this->xwing).rotate(0.5, vec3(0, 0, 1));
		(*this->main_camera).rotate(0.5, vec3(0.0f, 1.0f, 0.0f));
		for (int i = 0; i < this->asteroids_number; i++)
			asteroid_field[i].translate(vec3(1, 0, 0));

		this->real_position += vec3(1, 0, 0);
		break;
	case 9:
		for (int i = 0; i < this->asteroids_number; i++)
			asteroid_field[i].translate(vec3(1, 0, 0));

		this->real_position += vec3(1, 0, 0);
		break;
	case 10:
		(*this->main_camera).rotate(-0.5, vec3(0.0f, 1.0f, 0.0f));
		(*this->xwing).rotate(-0.5, vec3(0, 0, 1));
		break;
		//rotate4
	case 11:
		(*this->xwing).rotate(-0.5, vec3(0, 0, 1));
		(*this->main_camera).rotate(-0.5, vec3(0.0f, 1.0f, 0.0f));
		for (int i = 0; i < this->asteroids_number; i++)
			asteroid_field[i].translate(vec3(-1, 0, 0));

		this->real_position += vec3(-1, 0, 0);

		break;
	case 12:
		for (int i = 0; i < this->asteroids_number; i++)
			asteroid_field[i].translate(vec3(-1, 0, 0));

		this->real_position += vec3(-1, 0, 0);
		break;
	case 13:
		(*this->xwing).rotate(0.5, vec3(0, 0, 1));
		(*this->main_camera).rotate(0.5, vec3(0.0f, 1.0f, 0.0f));
		break;
		//rotate5
	case 14:
		(*this->xwing).rotate(-0.5, vec3(0, 0, 1));
		(*this->main_camera).rotate(-0.5, vec3(0.0f, 1.0f, 0.0f));
		for (int i = 0; i < this->asteroids_number; i++)
			asteroid_field[i].translate(vec3(-1, 0, 0));

		this->real_position += vec3(-1, 0, 0);

		break;
	case 15:
		for (int i = 0; i < this->asteroids_number; i++)
			asteroid_field[i].translate(vec3(-1, 0, 0));

		this->real_position += vec3(-1, 0, 0);
		break;
	case 16:
		(*this->xwing).rotate(0.5, vec3(0, 0, 1));
		(*this->main_camera).rotate(0.5, vec3(0.0f, 1.0f, 0.0f));
		break;
		//rotate6
	case 17:
		(*this->xwing).rotate(0.5, vec3(0, 0, 1));
		(*this->main_camera).rotate(0.5, vec3(0.0f, 1.0f, 0.0f));
		for (int i = 0; i < this->asteroids_number; i++)
			asteroid_field[i].translate(vec3(1, 0, 0));

		this->real_position += vec3(1, 0, 0);

		break;
	case 18:
		for (int i = 0; i < this->asteroids_number; i++)
			asteroid_field[i].translate(vec3(1, 0, 0));

		this->real_position += vec3(1, 0, 0);
		break;
	case 19:
		(*this->xwing).rotate(-0.5, vec3(0, 0, 1));
		(*this->main_camera).rotate(-0.5, vec3(0.0f, 1.0f, 0.0f));
		break;
		// shoot 3 times
	case 20:
		shoot();
		break;
	case 21:
		shoot();
		break;
	case 22:
		shoot();
		break;
		// rotate7
	case 23:
		(*this->xwing).rotate(0.5, vec3(0, 0, 1));
		(*this->main_camera).rotate(0.5, vec3(0.0f, 1.0f, 0.0f));
		for (int i = 0; i < this->asteroids_number; i++)
			asteroid_field[i].translate(vec3(1, 0, 0));

		this->real_position += vec3(1, 0, 0);
		break;
	case 24:
		for (int i = 0; i < this->asteroids_number; i++)
			asteroid_field[i].translate(vec3(1, 0, 0));

		this->real_position += vec3(1, 0, 0);
		break;
	case 25:
		(*this->main_camera).rotate(-0.5, vec3(0.0f, 1.0f, 0.0f));
		(*this->xwing).rotate(-0.5, vec3(0, 0, 1));
		break;

		//shoot 3 times
	case 26:
		shoot();
		break;
	case 27:
		shoot();
		break;
	case 28:
		shoot();
		break;
		// lightspeed
	case 29:
		(*this->main_camera).setPosition(vec3(0, 0, -25));
		(*this->main_camera).setMoving(false);
		(*this->main_camera).reset(vec3(0, 0, -25));
		break;
	case 30:
		(*this->xwing).stop_engine();
		(*this->ls).set_jump(true);
		break;
	case 31:
		(*this->main_camera).translate(vec3(0,0,0.3));
		break;
	case 32:
		(*this->xwing).translate(vec3(0, 0, -5));
		break;
	case 33:
		//(0*this->xwing).setActive(false);
		(*this->xwing).translate(vec3(0,0,-1000));
		//printf("acao 32\n");
		break;
	default:
		(*this->xwing).setActive(false);
		break;
	}
	//printf("cumulo: ");
	this->real_position.println();
}


void controller::check_actions()
{
	// conditions to stop each action
	switch (this->action)
	{
	case 0:
		if ((*this->xwing).get_position().Z() <= 0.0f)
		{
			action++;
			time = 0;
			//printf("action: %d\n", action);
		}
		break;
	case 1:
		action++;
		time = 0;
		//printf("action: %d\n", action);
		break;
		//rotate1
	case 2:
		if (time >= 20500)
		{
			action++;
			time = 0;
			//printf("action: %d\n", action);
		}
		break;
	case 3:
		if (time >= 3000)
		{
			action++;
			time = 0;
			//printf("action: %d\n", action);
		}
		break;
	case 4:
		if (time >= 500)
		{
			action++;
			time = 0;
			//printf("action: %d\n", action);
		}
		break;

		//rotate2
	case 5:
		if (time >= 1500)
		{
			action++;
			time = 0;
			//printf("action: %d\n", action);
		}
		break;
	case 6:
		if (time >= 1000)
		{
			action++;
			time = 0;
			//printf("action: %d\n", action);
		}
		break;
	case 7:
		if (time >= 500)
		{
			action++;
			time = 0;
			//printf("action: %d\n", action);
		}
		break;
		//rotate3
	case 8:
		if (time >= 500)
		{
			action++;
			time = 0;
			//printf("action: %d\n", action);
		}
		break;
	case 9:
		if (time >= 200)
		{
			action++;
			time = 0;
			//printf("action: %d\n", action);
		}
		break;
	case 10:
		if (time >= 500)
		{
			action++;
			time = 0;
			//printf("action: %d\n", action);
		}
		break;
		//rotate4
	case 11:
		if (time >= 5500)
		{
			action++;
			time = 0;
			//printf("action: %d\n", action);
		}
		break;
	case 12:
		if (time >= 1000)
		{
			action++;
			time = 0;
			//printf("action: %d\n", action);
		}
		break;
	case 13:
		if (time >= 500)
		{
			action++;
			time = 0;
			//printf("action: %d\n", action);
		}
		break;
		//rotate5
	case 14:
		if (time >= 10500)
		{
			action++;
			time = 0;
			//printf("action: %d\n", action);
		}
		break;
	case 15:
		if (time >= 1000)
		{
			action++;
			time = 0;
			//printf("action: %d\n", action);
		}
		break;
	case 16:
		if (time >= 500)
		{
			action++;
			time = 0;
			//printf("action: %d\n", action);
		}
		break;
		//rotate6
	case 17:
		if (time >= 2500)
		{
			action++;
			time = 0;
			//printf("action: %d\n", action);
		}
		break;
	case 18:
		if (time >= 500)
		{
			action++;
			time = 0;
			//printf("action: %d\n", action);
		}
		break;
	case 19:
		if (time >= 500)
		{
			action++;
			time = 0;
			//printf("action: %d\n", action);
		}
		break;
		//shoot 3 times
	case 20:
		action++;
		time = 0;
		//printf("action: %d\n", action);
		break;
	case 21:
		action++;
		time = 0;
		//printf("action: %d\n", action);
		break;
		
	case 22:
		action++;
		time = 0;
		//printf("action: %d\n", action);
		break;
		
		//rotate7
	case 23:
		if (time >= 500)
		{
			action++;
			time = 0;
			//printf("action: %d\n", action);
		}
		break;
	case 24:
		if (time >= 200)
		{
			action++;
			time = 0;
			//printf("action: %d\n", action);
		}
		break;
	case 25:
		if (time >= 500)
		{
			action++;
			time = 0;
			//printf("action: %d\n", action);
		}
		break;
		// shoot 3 times
	case 26:
		action++;
		time = 0;
		//printf("action: %d\n", action);
		break;
	case 27:
		action++;
		time = 0;
		//printf("action: %d\n", action);
		break;
	case 28:
		action++;
		time = 0;
		//printf("action: %d\n", action);
		break;
		//lightspeed
	case 29:
		action++;
		time = 0;
		//printf("action: %d\n", action);
		break;
	case 30:
		action++;
		time = 0;
		//printf("action: %d\n", action);
		break;
	case 31:
		if (time > 500)
		{
			action++;
			time = 0;
			//printf("action: %d\n", action);
		}
		break;
	case 32:
		if (time > 500)
		{
			action++;
			time = 0;
			//printf("action: %d\n", action);
		}
		break;
	case 33:
		action++;
		time = 0;
		//printf("action: %d\n", action);
		break;
	default:
		break;
	}
}


void controller::shoot()
{
	this->firing = true;
	pewpew[0].setPosition(vec3(-4.0f, 1.14f, -3.25));
	pewpew[1].setPosition(vec3(4.48f, 1.14f, -3.25));
	pewpew[2].setPosition(vec3(-4.01f, -2.1f, 0));
	pewpew[3].setPosition(vec3(4.47f, -2.1f, 0));

	(*this->xwing).shoot(true);

	firetime = 0;
}

vec3 controller::getExplosionPosition()
{
	return this->ep_position;
}

bool controller::isFiring()
{
	return this->firing;
}

void controller::play()
{
	//printf("play\n");
	this->is_play = true;
}

void controller::stop()
{
	this->is_play = false;
}

/* updates scene based on time instead of frames */
void controller::update_asteroids() {
	timeCurrent = glutGet(GLUT_ELAPSED_TIME);
	timeDelta = timeCurrent - timePrevious;
	timePrevious = timeCurrent;
	if (timeDelta > timeDeltaMax) {
		timeDelta = timeDeltaMax;
	}

	timetotal += timeDelta;

	if (timetotal >= timemin)
	{
		timetotal = 0;
		// update functions goes here

		if (firing)
		{
			firetime += timeDelta;
			pewpew[0].update();
			pewpew[1].update();
			pewpew[2].update();
			pewpew[3].update();
		}

		if (firetime >= firemax)
		{
			//printf("boom\n");
			firetime = 0;
			firing = false;

			vec3 position = asteroid_field[100].get_position();
			position.setY(position.Y() + 250);
			position.setZ(position.Z() - 100);

			this->ep_position = position;
			(*this->boom).enable_explosion = true;
		}

		if (lightred >= lightredmax)
		{
			(*this->xwing).shoot(false);
			lightred = 0;
		}
		else
		{
			if (firing)
				lightred += timeDelta;
		}

		for (int i = 0; i < asteroids_number; i++)
		{
			this->asteroid_field[i].update();
		}
	}
}

