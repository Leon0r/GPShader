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

	Shader(char* vertexPath, char* fragmentPath, char* geometryPath);

	virtual ~Shader();

	void use(); // activa el shader

	void setBool(const std::string & name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;


private:
	GLuint _id;

	void checkCompileErrors(unsigned int shader, std::string type);
	std::string loadShaderSource(char* fileName);
	GLuint loadShader(GLenum type, char* fileName);
	void linkProgram(GLuint vertexShader, GLuint fragmentShader, GLuint geometryShader);
};


#endif // !SHADER_H