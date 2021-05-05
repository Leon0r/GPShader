//#pragma once
#ifndef _H_Scene_H_
#define _H_Scene_H_

#include "GLinclude.h"
#include "Camera.h"
#include "Entity.h"

#include "Shader.h"

#include <vector>

class Texture;
class Shader;
//-------------------------------------------------------------------------

class Scene	
{ 
public:
	Scene() {};
	~Scene() { free(); resetGL(); };

	Scene(const Scene& s) = delete;  // no copy constructor
	Scene& operator=(const Scene& s) = delete;  // no copy assignment
		
	void init();
	void update();

    void render(Camera const& cam) const;

	void changeScene(int id);
	
protected:
	void free();
	void setGL();
	void resetGL();

	std::vector<Abs_Entity*> gObjects;  // Entities (graphic objects) of the scene
	std::vector<Texture*> gTextures; 
	
	int mId = 1;

	Shader* myShader;
	unsigned int VBO, VAO;
};
//-------------------------------------------------------------------------

#endif //_H_Scene_H_

