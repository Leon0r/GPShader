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
	Shader(const char* vertexPath, const char* fragmentPath);
	virtual ~Shader();

	void use(); // activa el shader

	void setBool(const std::string & name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;

	unsigned int _id;

private:
	void checkCompileErrors(unsigned int shader, std::string type);

};


#endif // !SHADER_H