#include "Shader.h"
#include "CheckML.h"
#include <iostream>

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
}

Shader::~Shader()
{
}

void Shader::use()
{
}

void Shader::setBool(const std::string& name, bool value) const
{
}

void Shader::setInt(const std::string& name, int value) const
{
}

void Shader::setFloat(const std::string& name, float value) const
{
}

void Shader::checkCompileErrors(unsigned int shader, std::string type)
{
}
