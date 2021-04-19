//#pragma once

//#include <glad/glad.h>

#include<fstream>
#include<string>

#include<GL/glew.h>
#include<GL/glfw3.h>

#include<glm.hpp>
#include<vec2.hpp>
#include<vec3.hpp>
#include<vec4.hpp>
#include<mat4x4.hpp>
#include<gtc\type_ptr.hpp>

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	virtual ~Shader();

	void use();
	void setBool(const std::string & name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;

	unsigned int _id;

private:
	void checkCompileErrors(unsigned int shader, std::string type);

};

