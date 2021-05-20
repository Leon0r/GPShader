//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include "GLinclude.h"

#include "Mesh.h"

class Texture;
//-------------------------------------------------------------------------

class Abs_Entity  // abstract class
{
public:
	Abs_Entity(): mModelMat(1.0), mColor(1) {};  // 4x4 identity matrix
	virtual ~Abs_Entity() {};

	Abs_Entity(const Abs_Entity& e) = delete;  // no copy constructor
	Abs_Entity& operator=(const Abs_Entity& e) = delete;  // no copy assignment

	virtual void update() {};
	virtual void render(glm::dmat4 const& modelViewMat) const = 0;  // abstract method

	// modeling matrix
	glm::dmat4 const& modelMat() const { return mModelMat; };
	void setModelMat(glm::dmat4 const& aMat) { mModelMat = aMat; };
	void setColor(glm::dvec4 aColor);
	void setTexture(Texture* tex) { mTexture = tex; };
	void setShader(Shader* shader);

protected:

	Mesh* mMesh = nullptr;   // the mesh
	glm::dmat4 mModelMat;    // modeling matrix
	glm::dvec4 mColor;			 // color
	Texture* mTexture = nullptr; // textura
	Shader* mShader = nullptr; // shader

	// transfers modelViewMat to the GPU
	virtual void upload(glm::dmat4 const& mModelViewMat) const; 
};
//-------------------------------------------------------------------------

class EjesRGB : public Abs_Entity 
{
public:
	explicit EjesRGB(GLdouble l);
	~EjesRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------

class Poligono : public Abs_Entity
{
public:
	explicit Poligono(GLuint numL, GLdouble rd);
	~Poligono();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------

class Sierpinski : public Abs_Entity
{
public:
	explicit Sierpinski(GLdouble rd, GLuint numP);
	~Sierpinski();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------
class TrianguloRGB : public Abs_Entity
{
public:

	explicit TrianguloRGB(GLdouble rd);
	~TrianguloRGB();
	virtual void update();
	virtual void render(glm::dmat4 const& modelViewMat) const;

private:
	GLdouble _movementRadio = 200;
	GLdouble _movementAngle = -90;
	GLdouble _angleTurn = 0;

};

//-------------------------------------------------------------------------

class RectanguloRGB : public Abs_Entity
{
public:
	explicit RectanguloRGB(GLdouble w, GLdouble h);
	~RectanguloRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------

class Estrella3D : public Abs_Entity
{
public:
	explicit Estrella3D(GLdouble re, GLuint np, GLdouble h);
	~Estrella3D();
	virtual void update();
	virtual void render(glm::dmat4 const& modelViewMat) const;

private:
	GLdouble _angleTurnY = 0;
	GLdouble _angleTurnZ = 0;
};

//-------------------------------------------------------------------------
class Caja : public Abs_Entity
{
public:
	explicit Caja(GLdouble ld);
	~Caja();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	
	void setInsideTexture(Texture* tex) { insTexture = tex; };

private:
	Texture* insTexture = nullptr; // textura

};

//-------------------------------------------------------------------------
class Suelo : public Abs_Entity
{
public:
	explicit Suelo(GLdouble w, GLdouble h, GLuint rw, GLuint rh);
	~Suelo();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------
class Foto : public Abs_Entity
{
public:
	explicit Foto(GLdouble w, GLdouble h);
	~Foto();
	virtual void update();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------
#endif //_H_Entities_H_