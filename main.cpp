#include "includes.h"
#include "controller.h"
#define CAPTION "Asteroid Field"

int WinX = 1024, WinY = 860;
int WindowHandle = 0;
unsigned int FrameCount = 0;

shader s;  // shader nave
shader s2; // shader asteroids
shader s3; // shader skybox
shader s4; // shader particles nave
shader s5; // lightspeed
shader s6; // missil inner
shader s7; // missil outer
shader s8; // explosao
shader s9; // flash

camera main_camera;

controller scene_controller;

nave xwing;
asteroid asteroid_field[150];
int active_asteroids;

scenenode skybox, flash;
texture part_text, sky_tex, xwing_tex;

lightspeed ls;

missil pewpew[4];


vec3 ep_position = vec3(0, 0, -500);
explosion ep;
float flash_alfa = 0;

float direction = 0;
/////////////////////////////////////////////////////////////////////// ERRORS

bool isOpenGLError() {
	bool isError = false;
	GLenum errCode;
	const GLubyte *errString;
	while ((errCode = glGetError()) != GL_NO_ERROR) {
		isError = true;
		errString = gluErrorString(errCode);
		std::cerr << "OpenGL ERROR [" << errString << "]." << std::endl;
	}
	return isError;
}

void checkOpenGLError(std::string error)
{
	if (isOpenGLError()) {
		std::cerr << error << std::endl;
		exit(EXIT_FAILURE);
	}
}

/////////////////////////////////////////////////////////////////////// SHADERs
void createShaderProgram()
{
	/**/
	// nave
	s = shader();
	//s.createShaderProgram("shaders/vertex.glsl", "shaders/fragment.glsl");
	s.createShaderProgram("shaders/nave_vs.glsl", "shaders/nave_fs.glsl");

	s.link();
	s.setUniformId("ModelMatrix");
	s.setUniformId("ViewMatrix");
	s.setUniformId("ProjectionMatrix");

	// MAYBE THOS GOES TO CLASS NAVE????
	s.setUniformId("lightPosition");
	s.setUniformId("cameraPosition");
	s.setUniformId("LightPower");
	s.setUniformId("LightColor");
	s.setUniformId("gSampler");

	checkOpenGLError("ERROR: Could not create shaders.");

	// asteroids
	s2 = shader();
	s2.createShaderProgram("shaders/asteroid_vertex.glsl", "shaders/asteroid_fragment.glsl");
	s2.link();
	s2.setUniformId("ModelMatrix");
	s2.setUniformId("ViewMatrix");
	s2.setUniformId("ProjectionMatrix");
	s2.setUniformId("lightPosition");
	s2.setUniformId("cameraPosition");
	s2.setUniformId("LightPower");
	s2.setUniformId("LightColor");
	s2.setUniformId("gSampler");
	s2.setUniformId("NoiseTexture");
	s2.setUniformId("NoiseTexture2");

	checkOpenGLError("ERROR: Could not create shaders.");

	// skybox
	s3 = shader();
	s3.createShaderProgram("shaders/sky_vert.glsl", "shaders/sky_frag.glsl");
	s3.link();
	s3.setUniformId("ModelMatrix");
	s3.setUniformId("ViewMatrix");
	s3.setUniformId("ProjectionMatrix");
	s3.setUniformId("gSampler");

	checkOpenGLError("ERROR: Could not create shaders.");

	// particles nave
	s4 = shader();
	s4.createShaderProgram("shaders/particula_vs.glsl", "shaders/particula_fs.glsl");
	s4.link();
	s4.setUniformId("ModelMatrix");
	s4.setUniformId("ViewMatrix");
	s4.setUniformId("ProjectionMatrix");
	s4.setUniformId("gSampler");

	checkOpenGLError("ERROR: Could not create shaders.");

	//light speed and velocity
	s5 = shader();
	s5.createShaderProgram("shaders/lspeed_vs.glsl", "shaders/lspeed_fs.glsl");
	s5.link();
	s5.setUniformId("ModelMatrix");
	s5.setUniformId("ViewMatrix");
	s5.setUniformId("ProjectionMatrix");
	s5.setUniformId("scale_factor");

	checkOpenGLError("ERROR: Could not create shaders.");

	//missil 1
	s6 = shader();
	s6.createShaderProgram("shaders/SimpleVertexShader.glsl", "shaders/SimpleFragmentShader.glsl");
	s6.link();
	s6.setUniformId("ModelMatrix");
	s6.setUniformId("ViewMatrix");
	s6.setUniformId("ProjectionMatrix");

	checkOpenGLError("ERROR: Could not create shaders.");

	//missil 2
	s7 = shader();
	s7.createShaderProgram("shaders/SimpleVertexShader2.glsl", "shaders/SimpleFragmentShader2.glsl");
	s7.link();
	s7.setUniformId("ModelMatrix");
	s7.setUniformId("ViewMatrix");
	s7.setUniformId("ProjectionMatrix");

	checkOpenGLError("ERROR: Could not create shaders.");

	//explosion
	s8 = shader();
	s8.createShaderProgram("shaders/explosion_vs.glsl", "shaders/explosion_fs.glsl");
	s8.link();
	s8.setUniformId("ModelMatrix");
	s8.setUniformId("ViewMatrix");
	s8.setUniformId("ProjectionMatrix");
	s8.setUniformId("scale_factor_x");
	s8.setUniformId("scale_factor_y");
	s8.setUniformId("scale_factor_z");

	checkOpenGLError("ERROR: Could not create shaders.");

	//flash bang
	s9 = shader();
	s9.createShaderProgram("shaders/flash_vertex.glsl", "shaders/flash_fragment.glsl");
	s9.link();
	s9.setUniformId("ModelMatrix");
	s9.setUniformId("ViewMatrix");
	s9.setUniformId("ProjectionMatrix");
	s9.setUniformId("alpha");

	checkOpenGLError("ERROR: Could not create shaders.");
}

void destroyShaderProgram()
{
	s.destroyShaderProgram();
	s2.destroyShaderProgram();
	s3.destroyShaderProgram();
	s4.destroyShaderProgram();
	s5.destroyShaderProgram();
	s6.destroyShaderProgram();
	s7.destroyShaderProgram();
	s8.destroyShaderProgram();
	s9.destroyShaderProgram();

	checkOpenGLError("ERROR: Could not destroy shaders.");
}

/////////////////////////////////////////////////////////////////////// VAOs & VBOs

/* group of 10 asteroids */
void populateAsteroidAux(vec3 origin, int index)
{
	asteroid_field[index + 0].setShaderProgram(&s2);
	asteroid_field[index + 0].init();
	asteroid_field[index + 0].scale(vec3(0.5f, 0.5f, 0.5f));
	asteroid_field[index + 0].translate(origin + vec3(0, 2, -134));
	asteroid_field[index + 0].rotate(32, vec3(1, 0, 0));
	asteroid_field[index + 0].setDirection(vec3(-1.0f, 0.0f, 0.0f));
	asteroid_field[index + 0].setVelocity(0.01f);

	asteroid_field[index + 1].setShaderProgram(&s2);
	asteroid_field[index + 1].init();
	asteroid_field[index + 1].scale(vec3(0.7f, 0.7f, 0.5f));
	asteroid_field[index + 1].translate(origin + vec3(31, -14, -196));
	asteroid_field[index + 1].rotate(55, vec3(0, 1, -1));
	asteroid_field[index + 1].setDirection(vec3(1.0f, 1.0f, 0.0f));
	asteroid_field[index + 1].setVelocity(0.01f);

	asteroid_field[index + 2].setShaderProgram(&s2);
	asteroid_field[index + 2].init();
	asteroid_field[index + 2].scale(vec3(0.5f, 0.5f, 0.5f));
	asteroid_field[index + 2].translate(origin + vec3(73, -60, -265));
	asteroid_field[index + 2].rotate(120, vec3(1, 1, 0));
	asteroid_field[index + 2].setDirection(vec3(0.0f, 1.0f, 0.0f));
	asteroid_field[index + 2].setVelocity(0.01f);

	asteroid_field[index + 3].setShaderProgram(&s2);
	asteroid_field[index + 3].init();
	asteroid_field[index + 3].scale(vec3(0.08f, 0.08f, 0.08f));
	asteroid_field[index + 3].translate(origin + vec3(-10, -1, -32));
	asteroid_field[index + 3].rotate(100, vec3(1, 1, 0));
	asteroid_field[index + 3].setDirection(vec3(0.0f, 0.0f, 1.0f));
	asteroid_field[index + 3].setVelocity(0.1f);

	asteroid_field[index + 4].setShaderProgram(&s2);
	asteroid_field[index + 4].init();
	asteroid_field[index + 4].scale(vec3(0.2f, 0.2f, 0.2f));
	asteroid_field[index + 4].translate(origin + vec3(-6, -43, -148));
	asteroid_field[index + 4].rotate(120, vec3(1, 1, 0));
	asteroid_field[index + 4].setDirection(vec3(0.0f, 1.0f, 1.0f));
	asteroid_field[index + 4].setVelocity(0.01f);

	asteroid_field[index + 5].setShaderProgram(&s2);
	asteroid_field[index + 5].init();
	asteroid_field[index + 5].scale(vec3(0.3f, 0.3f, 0.3f));
	asteroid_field[index + 5].translate(origin + vec3(-32, -40, -158));
	asteroid_field[index + 5].rotate(10, vec3(1, 1, 0));
	asteroid_field[index + 5].setDirection(vec3(-1.0f, 0.0f, -1.0f));
	asteroid_field[index + 5].setVelocity(0.01f);

	asteroid_field[index + 6].setShaderProgram(&s2);
	asteroid_field[index + 6].init();
	asteroid_field[index + 6].scale(vec3(0.08f, 0.08f, 0.08f));
	asteroid_field[index + 6].translate(origin + vec3(12, -30, -142));
	asteroid_field[index + 6].rotate(100, vec3(0, 1, 0.5f));
	asteroid_field[index + 6].setDirection(vec3(0.2f, 0.0f, -1.0f));
	asteroid_field[index + 6].setVelocity(0.01f);

	asteroid_field[index + 7].setShaderProgram(&s2);
	asteroid_field[index + 7].init();
	asteroid_field[index + 7].scale(vec3(0.6f, 0.6f, 0.6f));
	asteroid_field[index + 7].translate(origin + vec3(-80, -12, -358));
	asteroid_field[index + 7].rotate(120, vec3(1, 1, 0));
	asteroid_field[index + 7].setDirection(vec3(1.0f, 0.4f, 0.0f));
	asteroid_field[index + 7].setVelocity(0.01f);

	asteroid_field[index + 8].setShaderProgram(&s2);
	asteroid_field[index + 8].init();
	asteroid_field[index + 8].scale(vec3(0.05f, 0.05f, 0.05f));
	asteroid_field[index + 8].translate(origin + vec3(14, -21, -249));
	asteroid_field[index + 8].rotate(120, vec3(1, 1, 0));
	asteroid_field[index + 8].setDirection(vec3(0.0f, 1.0f, 0.2f));
	asteroid_field[index + 8].setVelocity(0.01f);

	asteroid_field[index + 9].setShaderProgram(&s2);
	asteroid_field[index + 9].init();
	asteroid_field[index + 9].scale(vec3(0.2f, 0.2f, 0.2f));
	asteroid_field[index + 9].translate(origin + vec3(-100, -16, -350));
	asteroid_field[index + 9].rotate(120, vec3(1, 1, 0));
	asteroid_field[index + 9].setDirection(vec3(0.3f, 0.0f, 1.0f));
	asteroid_field[index + 9].setVelocity(0.01f);

	/**/
	asteroid_field[index + 0].play();
	asteroid_field[index + 1].play();
	asteroid_field[index + 2].play();
	asteroid_field[index + 3].play();
	asteroid_field[index + 4].play();
	asteroid_field[index + 5].play();
	asteroid_field[index + 6].play();
	asteroid_field[index + 7].play();
	asteroid_field[index + 8].play();
	asteroid_field[index + 9].play();
	/**/

	checkOpenGLError("ERROR: Could not destroy shaders.");
}

void populateAsteroidfield()
{
	//center asteroids
	populateAsteroidAux(vec3(115, 10, -500), 0);
	populateAsteroidAux(vec3(115, 50, -750), 10);
	populateAsteroidAux(vec3(115, +15, -1000), 20);
	populateAsteroidAux(vec3(115, 20, -1300), 30);
	populateAsteroidAux(vec3(115, -0, -1800), 40);

	populateAsteroidAux(vec3(-115, 10, -500), 50);
	populateAsteroidAux(vec3(-115, 0, -750), 60);
	populateAsteroidAux(vec3(-115, +15, -1000), 70);
	populateAsteroidAux(vec3(-115, 10, -1300), 80);
	populateAsteroidAux(vec3(-115, 0, -1800), 90);

	asteroid_field[100].setShaderProgram(&s2);
	asteroid_field[100].init();
	asteroid_field[100].scale(vec3(4.5f, 4.5f, 4.5f));
	asteroid_field[100].translate(vec3(-76, -200, -2483));
	asteroid_field[100].rotate(32, vec3(1, 0, 0));
	asteroid_field[100].setDirection(vec3(-1.0f, 0.0f, 0.0f));
	asteroid_field[100].setVelocity(0.01f);

	active_asteroids = 101;
}

void createBufferObjects()
{
	//NAVE
	xwing_tex.loadTexture2D("objetos/noise.png", true);
	xwing_tex.setFiltering(TEXTURE_FILTER_MAG_BILINEAR, TEXTURE_FILTER_MIN_BILINEAR_MIPMAP);

	obj xwing_obj = obj();
	xwing_obj.createMesh(std::string("objetos/xwing.obj"), std::string("objetos/xwing.mtl"));

	// sets xwing
	xwing = nave();
	xwing.setObj(xwing_obj);
	xwing.load_data(xwing_obj);
	xwing.setTexture(xwing_tex);
	xwing.setShaderProgram(&s);
	xwing.setCamera(&main_camera);
	xwing.setMotoresShader(&s4);
	xwing.rotate(180, vec3(0, 1, 0));
	xwing.translate(vec3(0,0,100));
	xwing.scale(vec3(3, 3, 3));
	xwing.initMotores();


	/**/
	checkOpenGLError("ERROR: Could not destroy shaders.");

	populateAsteroidfield();

	obj skybox_obj = obj();
	skybox_obj.createMesh(std::string("objetos/skybox3.obj"), std::string("objetos/skybox.mtl"));

	sky_tex.loadTexture2D("objetos/purplenebula_up2.tga", true);
	sky_tex.setFiltering(TEXTURE_FILTER_MAG_BILINEAR, TEXTURE_FILTER_MIN_TRILINEAR);

	skybox = scenenode();
	skybox.setObj(skybox_obj);
	skybox.load_data(skybox_obj);
	skybox.setShaderProgram(&s3);
	skybox.setTexture(sky_tex);
	skybox.scale(vec3(500.0f, 500.0f, 500.f));

	checkOpenGLError("ERROR: Could not destroy shaders.");

	ls = lightspeed(vec3(0, 0, 1));
	ls.setShader(s5);
	ls.streming();

	checkOpenGLError("ERROR: Could not destroy shaders.");

	ep = explosion(vec3(0, 0, 0), vec3(1, 1, 1));
	ep.setShader(s8);
	ep.streming();

	checkOpenGLError("ERROR: Could not destroy shaders.");

	obj missile_obj = obj();
	missile_obj.createMesh(std::string("objetos/missile.obj"), std::string("objetos/missile.mtl"));

	obj flash_obj = obj();
	flash_obj.createMesh(std::string("objetos/flash.obj"), std::string("objetos/flash.mtl"));

	flash = scenenode();
	flash.setObj(flash_obj);
	flash.load_data(flash_obj);
	flash.setShaderProgram(&s9);
	flash.setTranslation(vec3(0, 0, 0));


	pewpew[0] = missil();
	pewpew[0].setObj(missile_obj);
	pewpew[0].setShaders(&s6, &s7);
	pewpew[0].setPosition(vec3(-4.0f, 1.14f, -3.25));
	pewpew[0].setDirection(vec3(0, 0, -1));
	pewpew[0].setSpeed(-1.5);

	pewpew[1] = missil();
	pewpew[1].setObj(missile_obj);
	pewpew[1].setShaders(&s6, &s7);
	pewpew[1].setPosition(vec3(4.48, 1.14, -3.25));
	pewpew[1].setDirection(vec3(0, 0, -1));
	pewpew[1].setSpeed(-1.5);

	pewpew[2] = missil();
	pewpew[2].setObj(missile_obj);
	pewpew[2].setShaders(&s6, &s7);
	pewpew[2].setPosition(vec3(-4.01f, -2.1f, 0));
	pewpew[2].setDirection(vec3(0, 0, -1));
	pewpew[2].setSpeed(-1.5);

	pewpew[3] = missil();
	pewpew[3].setObj(missile_obj);
	pewpew[3].setShaders(&s6, &s7);
	pewpew[3].setPosition(vec3(4.47f, -2.1f, 0));
	pewpew[3].setDirection(vec3(0, 0, -1));
	pewpew[3].setSpeed(-1.5);

	checkOpenGLError("ERROR: Could not destroy shaders.");
}

void destroyBufferObjects()
{
	xwing.destroy();

	for (int i = 0; i < active_asteroids; i++)
	{
		asteroid_field[i].destroy();
	}

	skybox.destroy();

	pewpew[0].destroy();
	pewpew[1].destroy();
	pewpew[2].destroy();
	pewpew[3].destroy();
}

void createCamera()
{
	main_camera = camera(vec3(0, 0, -25));
	main_camera.setPerspective(30, 640.0f / 480.0f, 1, 1500);
	main_camera.rotate(5, vec3(1.0f, 0.0f, 0.0f));
}

//explosao
void drawExplosion()
{
	if (ep.enable_explosion)
	{
		if (ep.enable_flash)
		{
			asteroid_field[100].translate(vec3(0, 1000, 0));
			flash_alfa = 1.0;
			ep.enable_flash = false;
		}

		flash_alfa -= 0.05;

		glUseProgram(s8.getProgramId());
		glBindVertexArray(ep._VAO);

		ep.Loop();

		glUniform1f(s8.getUniformId("scale_factor_x"), ep.scale_factor_x);
		glUniform1f(s8.getUniformId("scale_factor_y"), ep.scale_factor_y);
		glUniform1f(s8.getUniformId("scale_factor_z"), ep.scale_factor_z);

		mat4 model = scale(mat4(1.0f), vec3(0.1, 0.1, 0.1));
		model = translate(model, scene_controller.getExplosionPosition());

		glUniformMatrix4fv(s8.getUniformId("ViewMatrix"), 1, GL_FALSE, main_camera.getViewMatrix().getMatrix());
		glUniformMatrix4fv(s8.getUniformId("ProjectionMatrix"), 1, GL_FALSE, main_camera.getProjectionMatrix().getMatrix());
		glUniformMatrix4fv(s8.getUniformId("ModelMatrix"), 1, GL_FALSE, model.getMatrix());

		glUseProgram(0);
		glBindVertexArray(0);
	}
	if (ep.frames == 0)
	{
		ep = explosion(vec3(0, 0, 0), vec3(1, 1, 1));
		ep.setShader(s8);
		ep.streming();
		flash_alfa = 0;
	}
	checkOpenGLError("ERROR: Could not draw EXPLOSION");
}

void drawSkybox()
{
	glUseProgram(s3.getProgramId());
	glUniformMatrix4fv(s3.getUniformId("ViewMatrix"), 1, GL_FALSE, main_camera.getViewMatrix().getMatrix());
	glUniformMatrix4fv(s3.getUniformId("ProjectionMatrix"), 1, GL_FALSE, main_camera.getProjectionMatrix().getMatrix());

	glDepthMask(GL_FALSE);
	skybox.draw();
	glDepthMask(GL_TRUE);

	checkOpenGLError("ERROR: Could not draw SKYBOX");
}

void drawXWing()
{
	glUseProgram(s.getProgramId());
	glUniformMatrix4fv(s.getUniformId("ViewMatrix"), 1, GL_FALSE, main_camera.getViewMatrix().getMatrix());
	glUniformMatrix4fv(s.getUniformId("ProjectionMatrix"), 1, GL_FALSE, main_camera.getProjectionMatrix().getMatrix());

	glDisable(GL_CULL_FACE);
	xwing.draw();
	glEnable(GL_CULL_FACE);
	glUseProgram(0);   
	checkOpenGLError("ERROR: Could not draw XWING");
}

void drawAsteroids()
{
	glUseProgram(s2.getProgramId());

	glUniformMatrix4fv(s2.getUniformId("ViewMatrix"), 1, GL_FALSE, main_camera.getViewMatrix().getMatrix());
	glUniformMatrix4fv(s2.getUniformId("ProjectionMatrix"), 1, GL_FALSE, main_camera.getProjectionMatrix().getMatrix());
	//USA A LUZ DA NAVE NOS ASTEROIDS
	//posicao da luz
	glUniform3fv(s2.getUniformId("lightPosition"), 1, xwing.getLuz().getPositionArray());
	//posicao camera		
	glUniform3fv(s2.getUniformId("cameraPosition"), 1, xwing.getLuz().getCameraPosition());
	//potencia luz
	glUniform1f(s2.getUniformId("LightPower"), xwing.getLuz().getPotencia());
	//cor luz 
	glUniform3fv(s2.getUniformId("LightColor"), 1, xwing.getLuz().getColor());

	for (int i = 0; i < active_asteroids; i++)
	{
		asteroid_field[i].draw();
	}

	glUseProgram(0);

	checkOpenGLError("ERROR: Could not draw ASTEROIDS");
}

void drawLightSpeed()
{
	mat4 mls = scale(mat4(1.0), vec3(0.02, 0.02, 0.15));

	glUseProgram(s5.getProgramId());
	glBindVertexArray(ls._VAO);

	ls.jump();
	ls.Loop();

	glUniform1f(s5.getUniformId("scale_factor"), ls.get_scale());
	glUniformMatrix4fv(s5.getUniformId("ModelMatrix"), 1, GL_FALSE, mls.getMatrix());

	// CAMARA!!"!!!!!!!
	glUniformMatrix4fv(s5.getUniformId("ViewMatrix"), 1, GL_FALSE, main_camera.getViewMatrix().getMatrix());
	glUniformMatrix4fv(s5.getUniformId("ProjectionMatrix"), 1, GL_FALSE, main_camera.getProjectionMatrix().getMatrix());

	glUseProgram(0);
	checkOpenGLError("ERROR: Could not draw LS");
}

void drawMissil()
{
	if (scene_controller.isFiring())
	{
		glUseProgram(s6.getProgramId());
		glUniformMatrix4fv(s6.getUniformId("ViewMatrix"), 1, GL_FALSE, main_camera.getViewMatrix().getMatrix());
		glUniformMatrix4fv(s6.getUniformId("ProjectionMatrix"), 1, GL_FALSE, main_camera.getProjectionMatrix().getMatrix());
		glUseProgram(0);
		checkOpenGLError("ERROR: Could not draw MISSIL1");

		glUseProgram(s7.getProgramId());
		glUniformMatrix4fv(s7.getUniformId("ViewMatrix"), 1, GL_FALSE, main_camera.getViewMatrix().getMatrix());
		glUniformMatrix4fv(s7.getUniformId("ProjectionMatrix"), 1, GL_FALSE, main_camera.getProjectionMatrix().getMatrix());
		glUseProgram(0);
		checkOpenGLError("ERROR: Could not draw MISSIL2");

		pewpew[0].draw();
		pewpew[1].draw();
		pewpew[2].draw();
		pewpew[3].draw();
	}
}

void drawFlash()
{
	glUseProgram(s9.getProgramId());
	glUniformMatrix4fv(s9.getUniformId("ViewMatrix"), 1, GL_FALSE, main_camera.getViewMatrix().getMatrix());
	glUniformMatrix4fv(s9.getUniformId("ProjectionMatrix"), 1, GL_FALSE, main_camera.getProjectionMatrix().getMatrix());
	glUniform1f(s9.getUniformId("alpha"), flash_alfa);

	flash.draw();
	flash.setScale(vec3(11, 11, 10));
	flash.setTranslation(vec3(0, 0, 0));
	glUseProgram(0);

	checkOpenGLError("ERROR: Could not draw FLASH");
}

void drawScene()
{
	drawSkybox();
	drawXWing();
	drawAsteroids();
	drawLightSpeed();
	drawExplosion();
	drawMissil();
	drawFlash();
}


/////////////////////////////////////////////////////////////////////// CALLBACKS

void cleanup()
{
	destroyShaderProgram();
	destroyBufferObjects();
}

void refresh(int value)
{
	glutPostRedisplay();
	glutTimerFunc(1000 / 60, refresh, 0);
}


void display()
{
	++FrameCount;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene_controller.update();
	drawScene();
	glutSwapBuffers();
}

void idle()
{
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	WinX = w;
	WinY = h;
	glViewport(0, 0, WinX, WinY);
}

void timer(int value)
{
	std::ostringstream oss;
	oss << CAPTION << ": " << FrameCount << " FPS @ (" << WinX << "x" << WinY << ")";
	std::string s = oss.str();
	glutSetWindow(WindowHandle);
	glutSetWindowTitle(s.c_str());
	FrameCount = 0;
	glutTimerFunc(1000, timer, 0);
}

/************************
* Keyboard Control
************************/
void keybordcontrol(unsigned char key, int x, int y)
{
	/*
	if (q)
	printf("now using quaternians\n");
	else
	printf("now using euler angles\n");

	}*/
	int k = 3;

	switch (key)
	{
	case 'a':
	{
		/*xwing.rotate(1, vec3(0, 0, 1));
		main_camera.rotate(0.25, vec3(0.0f, 1.0f, 0.0f));

		asteroid_field[0].translate(vec3(-1, 0, 0));*/
		//asteroid_field[active_asteroids - 1].translate(vec3(0, 1, 0));
		break;
	}
	case 'd':
		/*xwing.rotate(-1, vec3(0, 0, 1));
		main_camera.rotate(-0.25, vec3(0.0f, 1.0f, 0.0f));*/
		//asteroid_field[active_asteroids - 1].translate(vec3(0, -1, 0));
		break;
	case 'w':
		//asteroid_field[active_asteroids - 1].translate(vec3(0, 0, -1));
		break;
	case 's':
		//asteroid_field[active_asteroids - 1].translate(vec3(0, 0, 1));
		//pewpew[k].translate(vec3(0, -0.01, 0));
		break;
	case 'q':
		//asteroid_field[active_asteroids - 1].translate(vec3(1, 0, 0));
		//pewpew[k].translate(vec3(0, 0, 0.01));
		break;
	case 'e':
		//asteroid_field[active_asteroids - 1].translate(vec3(-1, 0, 0));
		//pewpew[k].translate(vec3(0, 0, -0.01));
		break;

	case 'x':
		//for (int i = 0; i < active_asteroids; i++)
		//	asteroid_field[i].translate(vec3(0, 0, 0.5));

		break;
	case 32:
		//printf("ativei a cena\n");
		//ls.set_jump(true);
		scene_controller.play();
		break;

		//FIRE
	case 'z':
		//scene_controller.shoot();
		/*printf("ativei a cena\n");
		firing = true;
		pewpew[0].setPosition(vec3(-4.0f, 1.14f, -3.25));
		pewpew[1].setPosition(vec3(4.48f, 1.14f, -3.25));
		pewpew[2].setPosition(vec3(-4.01f, -2.1f, 0));
		pewpew[3].setPosition(vec3(4.47f, -2.1f, 0));

		xwing.shoot(true);

		firetime = 0;

		printf("pewpew\n");*/

		break;
	}

}

/************************
* Mouse control
*************************/

int startX, startY;
bool tracking = false;

void processMouseMotion(int xx, int yy)
{
	float deltaX;
	float deltaY;

	deltaX = -xx + startX;
	deltaY = yy - startY;

	startX = xx;
	startY = yy;

	if (tracking)
	{
		//printf("eu sedafadsfdas\n");
		main_camera.rotate(deltaX, vec3(0.0f, 1.0f, 0.0f));
		main_camera.rotate(deltaY, vec3(1.0f, 0.0f, 0.0f));
	}
}

void processMouseButtons(int button, int state, int xx, int yy)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		tracking = true;
		startX = xx;
		startY = yy;

	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		tracking = false;
	}
}

void mouseWheel(int wheel, int direction, int x, int y)
{
	main_camera.translate(vec3(0.0f, 0.0f, 0.1f*direction));
}

/////////////////////////////////////////////////////////////////////// SETUP

void setController()
{
	scene_controller = controller(asteroid_field, active_asteroids, &main_camera, &xwing, pewpew, &ep, &ls);
}

void setupCallbacks()
{
	glutCloseFunc(cleanup);
	glutDisplayFunc(display);
	//glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutTimerFunc(0, timer, 0);
	glutTimerFunc(0, refresh, 0);
	// controls TODO: MELHOR FORMA DE FAZER ISTO
	glutKeyboardFunc(keybordcontrol);
	glutMotionFunc(processMouseMotion);
	glutMouseFunc(processMouseButtons);
	glutMouseWheelFunc(mouseWheel);
}

void setupOpenGL() {
	std::cerr << "CONTEXT: OpenGL v" << glGetString(GL_VERSION) << std::endl;
	glClearColor(0.85f, 0.85f, 0.85f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);
	glDepthRange(0.0, 1.0);
	glClearDepth(1.0);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	/*glDisable(GL_CULL_FACE);
	glFrontFace(GL_CCW);*/

	//transparencia
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void setupGLEW() {
	glewExperimental = GL_TRUE;
	GLenum result = glewInit();
	if (result != GLEW_OK) {
		std::cerr << "ERROR glewInit: " << glewGetString(result) << std::endl;
		exit(EXIT_FAILURE);
	}
	GLenum err_code = glGetError();
}

void setupGLUT(int argc, char* argv[])
{
	glutInit(&argc, argv);

	glutInitContextVersion(3, 3);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glutInitWindowSize(WinX, WinY);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	WindowHandle = glutCreateWindow(CAPTION);
	if (WindowHandle < 1) {
		std::cerr << "ERROR: Could not create a new rendering window." << std::endl;
		exit(EXIT_FAILURE);
	}
}

void init(int argc, char* argv[])
{
	setupGLUT(argc, argv);
	setupGLEW();
	setupOpenGL();
	createShaderProgram();
	createCamera();
	createBufferObjects();
	setupCallbacks();
	setController();
}

int main(int argc, char* argv[])
{
	init(argc, argv);
	glutMainLoop();

	exit(EXIT_SUCCESS);
}

///////////////////////////////////////////////////////////////////////