#pragma once
#ifndef SHADER_H

//#include <glad/glad.h>

#include<GL/glew.h>
#include<GL/glfw3.h>

#include<string>
#include<fstream>
#include <sstream>
#include <iostream>

#include<glm.hpp>
#include<vec2.hpp>
#include<vec3.hpp>
#include<vec4.hpp>
#include<mat4x4.hpp>
#include<gtc\type_ptr.hpp>

class Shader
{
public:
	// Constructor, lee y crea el shader
	/*const int versionMajor, const int versionMinor,
		char* vertexFile, char* fragmentFile, char* geometryFile = "")
		: versionMajor(versionMajor), versionMinor(versionMinor)*/

	Shader(const int versionMajor, const int versionMinor,
		char* vertexFile, char* fragmentFile, char* geometryFile);

	virtual ~Shader();

	void use(); // activa el shader
	void unuse();

	void set1i(GLint value, const GLchar* name);

	void set1f(GLfloat value, const GLchar* name);
	void setVec2f(glm::fvec2 value, const GLchar* name);
	void setVec3f(glm::fvec3 value, const GLchar* name);
	void setVec4f(glm::fvec4 value, const GLchar* name);

	void setMat3fv(glm::mat3 value, const GLchar* name, GLboolean transpose = GL_FALSE);
	void setMat4fv(glm::mat4 value, const GLchar* name, GLboolean transpose = GL_FALSE);


private:
	GLuint _id;
	const int _versionMajor;
	const int _versionMinor;

	void checkCompileErrors(unsigned int shader, std::string type);
	std::string loadShaderSource(char* fileName);
	GLuint loadShader(GLenum type, char* fileName);
	void linkProgram(GLuint vertexShader, GLuint fragmentShader, GLuint geometryShader);
};


#endif // !SHADER_H