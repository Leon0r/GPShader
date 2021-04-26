#include "Shader.h"
#include "CheckML.h"
#include <iostream>

Shader::Shader(const int versionMajor, const int versionMinor,
	char* vertexPath, char* fragmentPath, char* geometryPath)
	: _versionMajor(versionMajor), _versionMinor(versionMinor)
{
	GLuint vertexShader = 0;
	GLuint geometryShader = 0;
	GLuint fragmentShader = 0;

	vertexShader = loadShader(GL_VERTEX_SHADER, vertexPath);

	if (geometryPath != "")
		geometryShader = loadShader(GL_GEOMETRY_SHADER, geometryPath);

	fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentPath);

	this->linkProgram(vertexShader, fragmentShader, geometryShader);

	//End
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteShader(geometryShader);
}


Shader::~Shader()
{
	glDeleteProgram(this->_id);
}

void Shader::use()
{
	glUseProgram(this->_id);
}

void Shader::unuse()
{
	glUseProgram(0);
}

void Shader::set1i(GLint value, const GLchar* name)
{
	this->use();

	glUniform1i(glGetUniformLocation(this->_id, name), value);

	this->unuse();
}

void Shader::set1f(GLfloat value, const GLchar* name)
{
	this->use();

	glUniform1f(glGetUniformLocation(this->_id, name), value);

	this->unuse();
}

void Shader::setVec2f(glm::fvec2 value, const GLchar* name)
{
	this->use();

	glUniform2fv(glGetUniformLocation(this->_id, name), 1, glm::value_ptr(value));

	this->unuse();
}

void Shader::setVec3f(glm::fvec3 value, const GLchar* name)
{
	this->use();

	glUniform3fv(glGetUniformLocation(this->_id, name), 1, glm::value_ptr(value));

	this->unuse();
}

void Shader::setVec4f(glm::fvec4 value, const GLchar* name)
{
	this->use();

	glUniform4fv(glGetUniformLocation(this->_id, name), 1, glm::value_ptr(value));

	this->unuse();
}

void Shader::setMat3fv(glm::mat3 value, const GLchar* name, GLboolean transpose)
{
	this->use();

	glUniformMatrix3fv(glGetUniformLocation(this->_id, name), 1, transpose, glm::value_ptr(value));

	this->unuse();
}

void Shader::setMat4fv(glm::mat4 value, const GLchar* name, GLboolean transpose)
{
	this->use();

	glUniformMatrix4fv(glGetUniformLocation(this->_id, name), 1, transpose, glm::value_ptr(value));

	this->unuse();
}

void Shader::checkCompileErrors(unsigned int shader, std::string type)
{
}

std::string Shader::loadShaderSource(char* fileName)
{
	std::string temp = "";
	std::string src = "";

	std::ifstream in_file;

	//Vertex
	in_file.open(fileName);

	if (in_file.is_open())
	{
		while (std::getline(in_file, temp))
			src += temp + "\n";
	}
	else
	{
		std::cout << "ERROR::SHADER::COULD_NOT_OPEN_FILE: " << fileName << "\n";
	}

	in_file.close();

	std::string versionNr =
		std::to_string(this->_versionMajor) +
		std::to_string(this->_versionMinor) +
		"0";

	src.replace(src.find("#version"), 12, ("#version " + versionNr));

	return src;
}

GLuint Shader::loadShader(GLenum type, char* fileName)
{
	char infoLog[512];
	GLint success;

	GLuint shader = glCreateShader(type);
	std::string str_src = this->loadShaderSource(fileName);
	const GLchar* src = str_src.c_str();
	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COULD_NOT_COMPILE_SHADER: " << fileName << "\n";
		std::cout << infoLog << "\n";
	}

	return shader;
}

void Shader::linkProgram(GLuint vertexShader, GLuint fragmentShader, GLuint geometryShader)
{
	char infoLog[512];
	GLint success;

	this->_id = glCreateProgram();

	glAttachShader(this->_id, vertexShader);

	if (geometryShader)
		glAttachShader(this->_id, geometryShader);

	glAttachShader(this->_id, fragmentShader);

	glLinkProgram(this->_id);

	glGetProgramiv(this->_id, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(this->_id, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COULD_NOT_LINK_PROGRAM" << "\n";
		std::cout << infoLog << "\n";
	}

	glUseProgram(0);
}
