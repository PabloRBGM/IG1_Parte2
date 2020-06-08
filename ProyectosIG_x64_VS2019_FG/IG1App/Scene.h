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
	int mId = 4;
	void setState(int id);
	void init();

    void render(Camera const& cam) const;
	void update();

	//Métodos antes de tener la clase Light
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

	// Métodos con la clase Light, para activar/desactivar las luces
	void enableDirLight() { directionalLight->enable(); }
	void disableDirLight() { directionalLight->disable(); }
	void enablePosLight() { positionalLight->enable(); }
	void disablePosLight() { positionalLight->disable(); }
	void enableSpotLight() { spotSceneLight->enable(); }
	void disableSpotLight() { spotSceneLight->disable(); }
	void enableFoco() { if( avion != nullptr) foco->enable(); }
	void disableFoco() { if (avion != nullptr) foco->disable(); }
	void enableMinero() { minero->enable(); }
	void disableMinero() { minero->disable(); }
	// Extra
	void enableFocoA() { foco_A->enable(); }
	void disableFocoA() { foco_A->disable(); }
	void enableSirena() { if (sirenCube != nullptr) sirena->enable(); }
	void disableSirena() { if (sirenCube != nullptr) sirena->disable(); }
	// Para mover el avion
	void move() { if (avion != nullptr) avion->move(); }
	void sirenMove() { if(sirenCube != nullptr) sirenCube->move(); }
protected:
	void free();
	void setGL();
	void resetGL();
	void setLights();
	std::vector<Abs_Entity*> gObjects;  // Entities (graphic objects) of the scene
	std::vector<Abs_Entity*> translucentgObjects;  // Entities (graphic objects) of the scene
	std::vector<Texture*> gTextures;	//
	
	DirLight* directionalLight = nullptr;
	PosLight* positionalLight = nullptr;
	SpotLight* spotSceneLight = nullptr;
	SpotLight* foco = nullptr;
	PosLight* minero = nullptr;
	

	// Extra 
	// Usamos las teclas 'n' y 'm' para activar y desactivar este foco
	SpotLight* foco_A = nullptr;
	SpotLight* sirena = nullptr;
	// Para mover el avion usamos una referencia
	// Para mover el sirenCube tambien
	Avion* avion = nullptr;
	SirenCube* sirenCube = nullptr;
	// Metodos y variables sin la clase Light
	void sceneDirLight(Camera const& cam) const;
	void scenePosLight(Camera const& cam) const;
	void sceneSpotLight(Camera const& cam) const;

	bool light0_Enabled = false;
	bool light1_Enabled = false;
	bool light2_Enabled = true;
};
//-------------------------------------------------------------------------

#endif //_H_Scene_H_

