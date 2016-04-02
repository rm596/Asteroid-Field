#ifndef _SHADER
#define _SHADER

#define VERTEX 0
#define FRAGMENT 1

#include <GL/glew.h>
#include <string>
#include <iostream>
#include <map>

#include "mat4.h";



class shader
{
private:
	GLuint programId;
	GLuint _ids[2];

	// uniforms for current shader program
	std::map<std::string, GLuint> uniforms;

public:
	//construtor
	shader();  //construtor vazio

	//id
	GLuint getProgramId();

	//ler file
	char* readTextFile(std::string fileName);

	//criar programa
	void createShaderProgram(std::string vextexFileName, std::string fragmentFileName);
	void destroyShaderProgram();

	// link unlink
	void link();
	void unlink();

	//set uniform
	void setUniformId(const GLchar *name);
	GLuint getUniformId(std::string name);

	//erros
	bool isOpenGLError();
	void checkOpenGLError(std::string error);
};

#endif