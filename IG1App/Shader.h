//#pragma once
#ifndef SHADER_H
#define SHADER_H

//#include <glm.hpp>
#include<gl/glad.h>
#include <string>


class Shader
{
public:

	Shader(const char* vertexPath, const char* fragmentPath);

	void use(); // activa el shader

	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;

private:
	GLuint _id;

	void checkCompileErrors(unsigned int shader, std::string type);
};


#endif // !SHADER_H