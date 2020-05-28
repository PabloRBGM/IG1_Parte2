//#pragma once
#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Camera.h"
#include "Entity.h"
#include "Texture.h"
#include "Light.h"

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
	//M�todos antes de tener la clase Light
	void setLight0(bool b) {
		light0_Enabled = b;
	}
	void setLight1(bool b) {
		light1_Enabled = b;
	}
	void setLight2(bool b) {
		light2_Enabled = b;
	}
	void turnOffLights();
	//M�todos con la clase Light;
	void enableDirLight() { directionalLight->enable(); }
	void disableDirLight() { directionalLight->disable(); }
	void enablePosLight() { positionalLight->enable(); }
	void disablePosLight() { positionalLight->disable(); }
	void enableSpotLight() { spotSceneLight->enable(); }
	void disableSpotLight() { spotSceneLight->disable(); }
	void enableFoco() { foco->enable(); }
	void disableFoco() { foco->disable(); }
protected:
	void free();
	void setGL();
	void resetGL();
	void sceneDirLight(Camera const& cam) const;
	void scenePosLight(Camera const& cam) const;
	void sceneSpotLight(Camera const& cam) const;
	void setLights();
	std::vector<Abs_Entity*> gObjects;  // Entities (graphic objects) of the scene
	std::vector<Abs_Entity*> translucentgObjects;  // Entities (graphic objects) of the scene
	std::vector<Texture*> gTextures;	//
	bool light0_Enabled = false;
	bool light1_Enabled = false;
	bool light2_Enabled = true;

	DirLight* directionalLight = nullptr;
	PosLight* positionalLight = nullptr;
	SpotLight* spotSceneLight = nullptr;
	SpotLight* foco = nullptr;

};
//-------------------------------------------------------------------------

#endif //_H_Scene_H_

