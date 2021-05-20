//#pragma once
#ifndef _H_Mesh_H_
#define _H_Mesh_H_

#include "GLinclude.h"
#include "Shader.h"

#include <vector>

//-------------------------------------------------------------------------

class Mesh 
{
public:
	static Mesh* createRGBAxes(GLdouble l); // creates a new 3D-RGB axes mesh
	
	// 2D
	static Mesh* generaPoligono(GLuint numL, GLdouble rd); // generate polygon vertex with numL sides inside a circle of radius rd 
	static Mesh* generaSierpinski(GLdouble rd, GLuint numP); // generates Sierpinski Triangle
	static Mesh* generaTrianguloRGB(GLdouble rd); // generates RGB triangle
	static Mesh* generaRectangulo(GLdouble w, GLdouble h); // generates rectangle
	static Mesh* generaRectanguloRGB(GLdouble w, GLdouble h); // generates RGB rectangle
	
	// 3D
	static Mesh* generaEstrella3D(GLdouble re, GLuint np, GLdouble h); // generates 3D star
	static Mesh* generaContCubo(GLdouble ld);
	
	// Texturas  
	static Mesh* generaRectanguloTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh);
	static Mesh* generaEstrellaTexCor(GLdouble re, GLuint np, GLdouble h);
	static Mesh* generaContCuboTexCor(GLdouble nl);

	Mesh() {};
	virtual ~Mesh() {};	

	Mesh(const Mesh & m) = delete;  // no copy constructor
	Mesh & operator=(const Mesh & m) = delete;  // no copy assignment
			
	virtual void render() const;
	
	GLuint size() const { return mNumVertices; };   // number of elements
	std::vector<glm::dvec3> const& vertices() const { return vVertices; };
	std::vector<glm::dvec4> const& colors() const { return vColors; };
	std::vector<glm::dvec2> const& textureVertices() const { return vTexCoords; };

	void setShader(Shader* shader);
	void setColor(glm::dvec4 aColor);
		
protected:
	
	GLuint mPrimitive = GL_TRIANGLES;   // graphic primitive: GL_POINTS, GL_LINES, GL_TRIANGLES, ...
	GLuint mNumVertices = 0;  // number of elements ( = vVertices.size())
	std::vector<glm::dvec3> vVertices;  // vertex array
	std::vector<glm::dvec4> vColors;    // color array
	std::vector<glm::dvec2> vTexCoords; // texture coords array
	virtual void draw() const;

	Shader* mShader = nullptr;
	unsigned int VBO, VAO;
};
//-------------------------------------------------------------------------

#endif //_H_Scene_H_