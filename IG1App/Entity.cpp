#include "Entity.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

#include "IG1App.h"
#include "Texture.h"

using namespace glm;

//-------------------------------------------------------------------------
void Abs_Entity::upload(dmat4 const& modelViewMat) const
{ 
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(modelViewMat));  // transfers modelView matrix to the GPU
}
//-------------------------------------------------------------------------


//- INICIO CLASE EJESRGB ------------------------------------------------------------------------

EjesRGB::EjesRGB(GLdouble l): Abs_Entity()
{
  mMesh = Mesh::createRGBAxes(l);
}
//-------------------------------------------------------------------------

EjesRGB::~EjesRGB() 
{ 
	delete mMesh; mMesh = nullptr; 
};
//-------------------------------------------------------------------------

void EjesRGB::render(dmat4 const& modelViewMat) const 
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);
		mMesh->render();
		glLineWidth(1);
	}
}

//- FIN CLASE EJESRGB ------------------------------------------------------------------------

//- INICIO CLASE POLIGONO ------------------------------------------------------------------------
Poligono::Poligono(GLuint numL, GLdouble rd) : Abs_Entity()
{
	mMesh = Mesh::generaPoligono(numL, rd);
}
//-------------------------------------------------------------------------

Poligono::~Poligono()
{
	delete mMesh; mMesh = nullptr;
};
//-------------------------------------------------------------------------

void Poligono::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
				
		glLineWidth(2);
		if (mShader != nullptr) {
			mShader->use();
		}
		else {
			glColor3d(mColor.r, mColor.g, mColor.b);
		}
		
		mMesh->render();

		glLineWidth(1);
		glColor3d(1.0, 1.0, 1.0);
	}
}
//- FIN CLASE POLIGONO ------------------------------------------------------------------------

//- INICIO CLASE Sierpinski ------------------------------------------------------------------------
Sierpinski::Sierpinski(GLdouble rd, GLuint numP) : Abs_Entity()
{
	mMesh = Mesh::generaSierpinski(rd, numP);
}
//-------------------------------------------------------------------------

Sierpinski::~Sierpinski()
{
	delete mMesh; mMesh = nullptr;
};
//-------------------------------------------------------------------------

void Sierpinski::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);

		glPointSize(2);
		glColor4dv(value_ptr(mColor));

		mMesh->render();

		glPointSize(1);
		glColor4dv(value_ptr(glm::dvec4(1.0, 1.0, 1.0, 1.0)));

	}
}
//- FIN CLASE Sierpinski ------------------------------------------------------------------------

//- INICIO CLASE TrianguloRGB ------------------------------------------------------------------------
TrianguloRGB::TrianguloRGB(GLdouble rd) : Abs_Entity()
{
	mMesh = Mesh::generaTrianguloRGB(rd);
}
//-------------------------------------------------------------------------

TrianguloRGB::~TrianguloRGB()
{
	delete mMesh; mMesh = nullptr;
}
void TrianguloRGB::update()
{
	GLdouble x;
	GLdouble y;
	x = _movementRadio * cos(radians(_movementAngle));
	y = _movementRadio * sin(radians(_movementAngle));


	glm::dmat4 aMat = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0.0f));
	aMat = aMat * glm::rotate(glm::dmat4(1.0f), glm::radians(_angleTurn), glm::dvec3(0, 0, 1.0));

	setModelMat(aMat);


	_movementAngle += 5;
	if (_movementAngle >= 360) _movementAngle = 0;

	_angleTurn -= 10;
	if (_angleTurn < 0) _angleTurn = 360;
}
;
//-------------------------------------------------------------------------

void TrianguloRGB::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);

		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_POINT);

		mMesh->render();
		
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	}
}
//- FIN CLASE TrianguloRGB ------------------------------------------------------------------------

//- INICIO CLASE RectanguloRGB ------------------------------------------------------------------------
RectanguloRGB::RectanguloRGB(GLdouble w, GLdouble h) : Abs_Entity()
{
	mMesh = Mesh::generaRectanguloRGB(w, h);
}
//-------------------------------------------------------------------------

RectanguloRGB::~RectanguloRGB()
{
	delete mMesh; mMesh = nullptr;
};
//-------------------------------------------------------------------------

void RectanguloRGB::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);

		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_POINT);

		mMesh->render();

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}
//- FIN CLASE RectanguloRGB ------------------------------------------------------------------------

//- INICIO CLASE Estrella3D ------------------------------------------------------------------------
Estrella3D::Estrella3D(GLdouble re, GLuint np, GLdouble h) : Abs_Entity()
{
	// mMesh = Mesh::generaEstrella3D(re, np, h);
	mMesh = Mesh::generaEstrellaTexCor(re, np, h);
}
//-------------------------------------------------------------------------

Estrella3D::~Estrella3D()
{
	delete mMesh; mMesh = nullptr;
}
//-------------------------------------------------------------------------

void Estrella3D::update()
{
	glm::dmat4 aMat = glm::rotate(glm::dmat4(1.0f), glm::radians(_angleTurnY), glm::dvec3(0, 1.0, 0));
	aMat *= glm::rotate(glm::dmat4(1.0f), glm::radians(_angleTurnZ), glm::dvec3(0, 0, 1.0));
	
	setModelMat(aMat);

	_angleTurnY += 5;
	if (_angleTurnY >= 360) _angleTurnY = 0;

	_angleTurnZ -= 10;
	if (_angleTurnZ < 0) _angleTurnZ = 360;
}
//-------------------------------------------------------------------------

void Estrella3D::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {

		if (mTexture) {
			mTexture->bind(GL_MODULATE);
		}

		glm::dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		upload(aMat);
		mMesh->render();

		glm::dmat4 bMat = modelViewMat * mModelMat;  // glm matrix multiplication
		bMat = bMat * glm::rotate(glm::dmat4(1.0f), glm::radians((GLdouble)180), glm::dvec3(1.0, 0, 0));
		
		upload(bMat);
		mMesh->render();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		if (mTexture) {
			mTexture->unbind();
		}
	}
}
//- FIN CLASE Estrella3D ------------------------------------------------------------------------

//- INICIO CLASE Caja ------------------------------------------------------------------------
Caja::Caja(GLdouble ld) : Abs_Entity()
{
	mMesh = Mesh::generaContCuboTexCor(ld);
}
//-------------------------------------------------------------------------

Caja::~Caja()
{
	delete mMesh; mMesh = nullptr;
};
//-------------------------------------------------------------------------

void Caja::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_CULL_FACE);
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);

		if (mTexture) {
			glCullFace(GL_FRONT);
			mTexture->bind(GL_MODULATE);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			
			mMesh->render();
			mTexture->unbind();
		}

		if (insTexture) {
			insTexture->bind(GL_MODULATE);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glCullFace(GL_BACK);
			mMesh->render();
			insTexture->unbind();
		}
		glDisable(GL_CULL_FACE);

		/*mMesh->render();

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		
		if (insTexture) {
			insTexture->unbind();
		}
		if (mTexture) {
			mTexture->unbind();
		}*/		
	}
}
//- FIN CLASE RectanguloRGB ------------------------------------------------------------------------


//- INICIO CLASE Suelo ------------------------------------------------------------------------
Suelo::Suelo(GLdouble w, GLdouble h, GLuint rw, GLuint rh)
{
	mMesh = Mesh::generaRectanguloTexCor(w, h, rw, rh);
	glm::dmat4 aMat = rotate(glm::dmat4(1.0f), glm::radians(270.0), glm::dvec3(1.0, 0, 0));
	setModelMat(aMat);
}
//-------------------------------------------------------------------------

Suelo::~Suelo()
{
	delete mMesh; mMesh = nullptr;
}
//-------------------------------------------------------------------------

void Suelo::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		if (mTexture) {
			mTexture->bind(GL_MODULATE);
		}
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);

		mMesh->render();

		if (mTexture)
			mTexture->unbind();
	}
}
//- FIN CLASE Suelo ------------------------------------------------------------------------

//- INICIO CLASE Foto ------------------------------------------------------------------------
Foto::Foto(GLdouble w, GLdouble h) : Abs_Entity()
{
	mTexture = new Texture();

	mMesh = Mesh::generaRectanguloTexCor(w,h,1,1);
}
//-------------------------------------------------------------------------

Foto::~Foto()
{
	delete mMesh; mMesh = nullptr;
	delete mTexture; mTexture = nullptr;
}
//-------------------------------------------------------------------------

void Foto::update()
{
	mTexture->bind(GL_MODULATE);
	mTexture->loadColorBuffer(IG1App::s_ig1app.winWidth(), IG1App::s_ig1app.winHeigth(), GL_FRONT);
	//mTexture->loadColorBuffer(800, 600, GL_FRONT);
	mTexture->unbind();
}
//-------------------------------------------------------------------------

void Foto::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {

		if (mTexture) {
			mTexture->bind(GL_MODULATE);
		}

		glm::dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication

		upload(aMat);
		mMesh->render();

		if (mTexture) {
			mTexture->unbind();
		}
	}
}
//- FIN CLASE Foto ------------------------------------------------------------------------
