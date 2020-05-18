//#pragma once
#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Camera.h"
#include "Entity.h"
#include "Texture.h"

#include <vector>

//-------------------------------------------------------------------------

class Scene	
{ 
public:
	Scene() {};
	~Scene() { free(); resetGL(); };

	Scene(const Scene& s) = delete;  // no copy constructor
	Scene& operator=(const Scene& s) = delete;  // no copy assignment
	int mId = 3;
	void setState(int id);
	void init();

    void render(Camera const& cam) const;
	void update();
protected:
	void free();
	void setGL();
	void resetGL();
	void sceneDirLight(Camera const& cam) const;

	std::vector<Abs_Entity*> gObjects;  // Entities (graphic objects) of the scene
	std::vector<Abs_Entity*> translucentgObjects;  // Entities (graphic objects) of the scene
	std::vector<Texture*> gTextures;	//
};
//-------------------------------------------------------------------------

#endif //_H_Scene_H_

