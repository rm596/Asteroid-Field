#include "shader.h"


//construtor vazio
shader::shader()
{
}

GLuint shader::getProgramId()
{
	return this->programId;
}

char * shader::readTextFile(std::string fileName) {
	FILE *fp;
	char *content = NULL;

	int count = 0;

	if (fileName != "") {
		fopen_s(&fp, fileName.c_str(), "r");

		if (fp != NULL) {

			fseek(fp, 0, SEEK_END);
			count = ftell(fp);
			rewind(fp);

			if (count > 0) {
				content = (char *)malloc(sizeof(char)* (count + 1));
				count = fread(content, sizeof(char), count, fp);
				content[count] = '\0';
			}
			fclose(fp);
		}
	}
	return content;
}

//criar programa
void shader::createShaderProgram(std::string vextexFileName, std::string fragmentFileName)
{
	// criar vertex shader
	char* vertexShader = readTextFile(vextexFileName);
	this->_ids[0] = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(this->_ids[0], 1, (const char**)&vertexShader, 0);
	glCompileShader(this->_ids[0]);

	//criar fragment shader
	char* fragmentShader = readTextFile(fragmentFileName);
	this->_ids[FRAGMENT] = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(this->_ids[FRAGMENT], 1, (const char**)&fragmentShader, 0);
	glCompileShader(this->_ids[FRAGMENT]);

	//criar programa
	this->programId = glCreateProgram();
	glAttachShader(this->programId, this->_ids[VERTEX]);
	glAttachShader(this->programId, this->_ids[FRAGMENT]);

	checkOpenGLError("ERROR: Could create shaders");
}


//destruir programa
void shader::destroyShaderProgram()
{
	glUseProgram(0);
	glDetachShader(programId, _ids[VERTEX]);
	glDetachShader(programId, _ids[FRAGMENT]);

	glDeleteShader(_ids[FRAGMENT]);
	glDeleteShader(_ids[VERTEX]);
	glDeleteProgram(programId);

	checkOpenGLError("ERROR: Could not destroy shaders.");
}

void shader::link()
{
	glLinkProgram(this->programId);
}

void shader::unlink()
{
	glLinkProgram(0);
}

void shader::setUniformId(const GLchar *name)
{
	this->uniforms[name] = glGetUniformLocation(this->programId, name);
}

GLuint shader::getUniformId(std::string name)
{
	return this->uniforms[name];
}

//ERROS
bool shader::isOpenGLError() {
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

void shader::checkOpenGLError(std::string error)
{
	if (isOpenGLError()) {
		std::cerr << error << std::endl;
		exit(EXIT_FAILURE);
	}
}