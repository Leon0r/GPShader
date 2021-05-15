#include "Scene.h"
#include "CheckML.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

#include "Texture.h"
#include "ColorsNames.h"

using namespace glm;
//-------------------------------------------------------------------------

void Scene::init()
{ 
	setGL();  // OpenGL settings

	// allocate memory and load resources
    // Lights -------------------------------
    // Textures -------------------------------
	Texture* texture = new Texture();
	texture->load("..\\Bmps\\baldosaC.bmp"); // 0
	gTextures.push_back(texture);

	texture = new Texture();
	texture->load("..\\Bmps\\baldosaF.bmp"); // 1
	gTextures.push_back(texture);
	
	texture = new Texture();
	texture->load("..\\Bmps\\baldosaP.bmp"); // 2
	gTextures.push_back(texture);
	
	texture = new Texture();
	texture->load("..\\Bmps\\container.bmp"); // 3
	gTextures.push_back(texture);
	
	texture = new Texture();
	texture->load("..\\Bmps\\grass.bmp"); // 4
	gTextures.push_back(texture);
	
	texture = new Texture();
	texture->load("..\\Bmps\\noche.bmp"); // 5
	gTextures.push_back(texture);
	
	texture = new Texture();
	texture->load("..\\Bmps\\papelC.bmp"); // 6
	gTextures.push_back(texture);
	
	texture = new Texture();
	texture->load("..\\Bmps\\papelE.bmp"); // 7
	gTextures.push_back(texture);
	
	texture = new Texture();
	texture->load("..\\Bmps\\windowC.bmp"); // 8
	gTextures.push_back(texture);
	
	texture = new Texture();
	texture->load("..\\Bmps\\windowV.bmp"); // 9
	gTextures.push_back(texture);
	
	texture = new Texture();
	texture->load("..\\Bmps\\Zelda.bmp"); // 10
	gTextures.push_back(texture);

	// set up vertex data (and buffer(s)) and configure vertex attribute


	// build and compile our shader program
	// ------------------------------------
	/*myShader = new Shader("..\\Shaders\\3.3.shader.vs", "..\\Shaders\\3.3.shader.fs"); // you can name your shader files however you like
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);*/



	Abs_Entity* aux;
	aux = new RectanguloRGB(0.5, 0.5);
	//aux = new Poligono(3, 100.0);
	aux->setShader(new Shader("..\\Shaders\\3.3.shader.vs", "..\\Shaders\\3.3.shader.fs"));
	gObjects.push_back(aux);
    // Graphics objects (entities) of the scene
	/*Abs_Entity* aux;
	if (mId == 0) {
		// gShader->use();

		aux = new Poligono(3, 200.0);
		aux->setColor(glm::dvec4(RGB_COLOR_AQUA, 1.0));
		gObjects.push_back(aux);

		aux = new Poligono(360, 200.0);
		aux->setColor(glm::dvec4(RGB_COLOR_TOMATO, 1.0));
		gObjects.push_back(aux);

		aux = new Sierpinski(200.0, 10000);
		aux->setColor(glm::dvec4(RGB_COLOR_PALETURQUOISE, 1.0));
		gObjects.push_back(aux);

		aux = new TrianguloRGB(20.0);
		aux->setModelMat(glm::translate(aux->modelMat(), glm::dvec3(0, -200, 0)));
		gObjects.push_back(aux);

		/* // Triangulo RGB cambiado de posicion
		aux->setModelMat(glm::translate(aux->modelMat(), glm::dvec3(50, -150, 0)));
		GLdouble dgrr = -25;
		aux->setModelMat(glm::rotate(aux->modelMat(), glm::radians(dgrr), glm::dvec3(1.0, 0, 0)));

		aux = new RectanguloRGB(1000.0, 1000.0);
		gObjects.push_back(aux);
		aux->setModelMat(glm::translate(aux->modelMat(), glm::dvec3(-500, -500, 0)));
	}
	else if (mId == 1) {
		 gObjects.push_back(new EjesRGB(400.0));	

		 /*aux = new Estrella3D(100.0, 6, 100.0);
		 aux->setColor(glm::dvec4(RGB_COLOR_PALETURQUOISE, 1.0));
		 gObjects.push_back(aux);

		 aux = new Suelo(150.0, 150.0, 2,3);
		 aux->setTexture(gTextures[0]);
		 aux->setModelMat(glm::translate(aux->modelMat(), glm::dvec3(0, -150, 0)));
		 gObjects.push_back(aux);

		 aux = new Estrella3D(20.0, 8, 20.0);
		 aux->setTexture(gTextures[2]);
		 gObjects.push_back(aux);

		/* Caja* aux2 = new Caja(100.0);
		 aux2->setInsideTexture(gTextures[6]);
		 aux2->setTexture(gTextures[3]);
		 gObjects.push_back(aux2);
		 
		 aux = new Foto(50.0, 50.0);
		 GLdouble dgrr = 90;
		 aux->setModelMat(glm::rotate(aux->modelMat(), glm::radians(dgrr), glm::dvec3(1.0, 0, 0))); 
		 aux->setModelMat(glm::translate(aux->modelMat(), glm::dvec3(50, 50, -1)));
		 gObjects.push_back(aux);

		 Caja* aux2 = new Caja(150.0);
		 texture = new Texture();
		 texture->load("..\\Bmps\\windowV.bmp", 150); // 9
		 aux2->setInsideTexture(texture);
		 aux2->setTexture(texture);
		 
		 aux2->setModelMat(glm::translate(aux2->modelMat(), glm::dvec3(75, 75, 75)));

		 gObjects.push_back(aux2);
	}*/
	
}

//-------------------------------------------------------------------------

void Scene::update()
{
	for (int i = 0; i < gObjects.size(); i++)
		gObjects[i]->update();
}

//-------------------------------------------------------------------------

void Scene::free() 
{ 
	/*glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);*/
	// release memory and resources   
	for (Texture* tx : gTextures) 
	{
		delete tx; tx = nullptr;
	}

	for (Abs_Entity* el : gObjects)
	{
		delete el;  el = nullptr;
	}
	gObjects.clear();
}
//-------------------------------------------------------------------------
void Scene::setGL() 
{
	// OpenGL basic setting
	glClearColor(0.0, 0.0, 0.0, 1.0);  // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);  // enable Depth test 
	glEnable(GL_TEXTURE_2D);  // enable textures
	glEnable(GL_BLEND); // enable blending

}
//-------------------------------------------------------------------------
void Scene::resetGL() 
{
	glClearColor(.0, .0, .0, .0);  // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);  // disable Depth test 	
	glDisable(GL_TEXTURE_2D);  // disable textures	
	glDisable(GL_BLEND); // disable blending
}
//-------------------------------------------------------------------------

void Scene::render(Camera const& cam) const 
{
	cam.upload();

	for (Abs_Entity* el : gObjects)
	{
		el->render(cam.viewMat());
	}
}
void Scene::changeScene(int id)
{
	mId = id;

	free();
	resetGL();

	init();
}
//-------------------------------------------------------------------------


