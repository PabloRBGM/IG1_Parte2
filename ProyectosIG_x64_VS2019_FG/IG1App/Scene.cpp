#include "Scene.h"
#include "CheckML.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>
#include <iostream>
using namespace glm;
//-------------------------------------------------------------------------
//creamos los objectos que queremos y los añadimos a gObjects 
void Scene::init()
{ 
	setGL();  // OpenGL settings
	setLights();
	gObjects.push_back(new EjesRGB(400.0));
	glClearColor(0.7, 0.8, 0.9, 0.0);
	//-----------------------------------------------------------------------------------------------
	//Escena 3D, Entidades Cuadricas
	if (mId == 1) {
	
		Sphere* esfera = new Sphere(100.0);
		esfera->setColor({ 1.0,0.3,0.0 });
		gObjects.push_back(esfera);

		Cylinder* conoIzq = new Cylinder(15.0, 0, 45.0);
		glm::dmat4 mAux = conoIzq->modelMat();
		mAux = translate(mAux, dvec3(-30, 30, 70));
		conoIzq->setModelMat(mAux);
		conoIzq->setColor({ 0.18,0.545,0.443 });
		gObjects.push_back(conoIzq);

		Cylinder* conoDer = new Cylinder(15.0, 0, 45.0);
		glm::dmat4 mAuxC2 = conoDer->modelMat();
		mAuxC2 = translate(mAuxC2, dvec3(30, 30, 70));
		conoDer->setModelMat(mAuxC2);
		conoDer->setColor({ 0.0,0.0,1.0 });
		gObjects.push_back(conoDer);


		Disk* disco = new Disk(50, 100, 50, 2);
		glm::dmat4 mAuxDisk = disco->modelMat();
		mAuxDisk = translate(mAuxDisk, dvec3(0, 75, 0));
		mAuxDisk = rotate(mAuxDisk, radians(-90.0), dvec3(1.0, 0, 0));
		disco->setModelMat(mAuxDisk);
		disco->setColor({ 1.0,0.0,0.0 });
		gObjects.push_back(disco);

		PartialDisk* partDisco = new PartialDisk(70, 90, 50, 2, 90, 180);
		glm::dmat4 mAuxPartDisk = partDisco->modelMat();
		mAuxPartDisk = translate(mAuxPartDisk, dvec3(0, 0, 60));
		partDisco->setModelMat(mAuxPartDisk);
		partDisco->setColor({ 0.0,1.0,0.0 });
		gObjects.push_back(partDisco);
	}
	else if (mId == 2) {
		/*AnilloCuadrado* anillo = new AnilloCuadrado();
		gObjects.push_back(anillo);*/
		EntityWithIndexMesh* cubo = new Cubo();
		cubo->setmColor(dvec4(1.0, 0.0, 0.0, 1.0));
		gObjects.push_back(cubo);

	}
	else if (mId == 3) {
		CompoundEntity*  helices = new CompoundEntity();
		Cylinder* conoDer = new Cylinder(15.0, 10.0, 50.0);
		glm::dmat4 mAuxC2 = conoDer->modelMat();
		mAuxC2 = translate(mAuxC2, dvec3(0, 0, 115));
		mAuxC2 = rotate(mAuxC2, radians(90.0), dvec3(0, 1, 0));
		conoDer->setModelMat(mAuxC2);
		conoDer->setColor({ 0.0,0.0,1.0 });

		Cylinder* conoIzq = new Cylinder(15.0, 10.0, 50.0);
		glm::dmat4 mAuxC1 = conoIzq->modelMat();

		mAuxC1 = translate(mAuxC1, dvec3(0, 0, 115));
		mAuxC1 = rotate(mAuxC1, radians(270.0), dvec3(0, 1, 0));
		conoIzq->setModelMat(mAuxC1);
		conoIzq->setColor({ 0.0,0.0,1.0 });

		helices->addEntity(conoDer);
		helices->addEntity(conoIzq);
		//-----------------------------------------------------------------------
		CompoundEntity* chasis = new CompoundEntity();
		Sphere* sphere = new Sphere(100.0);
		sphere->setColor({ 1.0, 0.0 ,0.0 });

		chasis->addEntity(sphere);
		chasis->addEntity(helices);
		//---------------------------------------
		avion = new Avion();
		avion->addEntity(chasis);
		Cubo* cubo = new CuboCooper();
		glm::dmat4 mAuxCubo = cubo->modelMat();
		mAuxCubo = scale(mAuxCubo, dvec3(3.5,0.3, 1.5));
		cubo->setModelMat(mAuxCubo);
		//cubo->setmColor({ 0.0, 1.0 ,0.0, 1.0 });
		glm::dmat4 mAuxAvion = avion->modelMat();
		mAuxAvion = translate(mAuxAvion, dvec3(0, 150, 0));
		mAuxAvion = scale(mAuxAvion, dvec3(0.2, 0.2, 0.2));
		avion->setModelMat(mAuxAvion);
		avion->addEntity(cubo);
		
		gObjects.push_back(avion);
		//foco en la misma posición que el avion
		foco->setPosDir(fvec3(0, 150, 0));

		avion->setLight(foco);
		avion->setHelices(helices);
		//----------------------------------------------
		Esfera* esfera = new Esfera(100.0, 200, 200);
		esfera->setmColor(dvec4(0.0, 1.0, 1.0, 1.0));
		Material* goldMat = new Material();
		goldMat->setGold();
		//goldMat->setCopper();
		esfera->setMaterial(goldMat);//pone material a la esfera
		gObjects.push_back(esfera);
		
		//para ver que se ven igual las dos eferas, con Sphere y con Esfera
		/*Sphere* sphere2 = new Sphere(100.0);
		sphere2->setColor(fvec3(0.498, 1.0, 0.831));
		glm::dmat4 mAuxC4 = sphere2->modelMat();

		mAuxC4 = translate(mAuxC4, dvec3(200, 0, 0));
		sphere2->setModelMat(mAuxC4);
		gObjects.push_back(sphere2);*/
	}
	else if (mId == 4) {

		//Texturas
		gTextures.push_back(new Texture());
		gTextures[0]->load("../Bmps/checker.bmp");
		gTextures.push_back(new Texture());
		gTextures[1]->load("../Bmps/stones.bmp");

		GridCube* gCube = new GridCube(200, 1, gTextures[0], gTextures[1]);
		gObjects.push_back(gCube);
		/*Grid* grid = new Grid(200, 1);
		grid->setmColor({ 0.0,0.0,1.0,1.0 });
		glm::dmat4 mAux = grid->modelMat();

		mAux = translate(mAux, dvec3(-100, 0, -100));
		mAux = rotate(mAux, radians(90.0), dvec3(1, 0, 0));
		grid->setModelMat(mAux);
		grid->setTexture(gTextures[0]);
		gObjects.push_back(grid);*/
	}
}

void Scene::setState(int id) { 
	mId = id;
	free();
	init();
}
void Scene::turnOffLights()
{
	/*light0_Enabled = false;
	light1_Enabled = false;
	light2_Enabled = false;*/
	directionalLight->disable();
	positionalLight->disable();
	spotSceneLight->disable();
	foco->disable();
	minero->disable();
	glm::fvec4 amb = {0.0, 0.0, 0.0, 1.0};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, value_ptr(amb));

	//glDisable(GL_LIGHTING);
}

//-------------------------------------------------------------------------
void Scene::free() 
{ // release memory and resources   

	for (Abs_Entity* el : gObjects)
	{
		delete el;  el = nullptr;
	}
	gObjects.clear();

	for (Abs_Entity* tel : translucentgObjects)
	{
		delete tel;  tel = nullptr;
	}
	translucentgObjects.clear();

	for (Texture* t : gTextures)
	{
		delete t;  t = nullptr;
	}
	gTextures.clear();

	//delete lights
	delete directionalLight;
	delete positionalLight;
	delete spotSceneLight;
	delete foco;
	delete minero;
}
//-------------------------------------------------------------------------
void Scene::setGL() 
{
	// OpenGL basic setting
	//glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);  // enable Depth test 
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	/*glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0);*/
	/*if(mId == 1)*/glEnable(GL_TEXTURE_2D);  
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);


}
//-------------------------------------------------------------------------
void Scene::resetGL() 
{
	glClearColor(.0, .0, .0, .0);  // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);  // disable Depth test 	
	glDisable(GL_BLEND);
	//glDisable(GL_ALPHA_TEST);
	/*if (mId == 1)*/
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glDisable(GL_NORMALIZE);
}
//-------------------------------------------------------------------------

void Scene::render(Camera const& cam) const 
{
	//Iluminación

	/*sceneDirLight(cam);
	scenePosLight(cam);
	sceneSpotLight(cam);*/
	if (directionalLight != nullptr)
		directionalLight->upload(cam.viewMat());
	if (positionalLight != nullptr)
		positionalLight->upload(cam.viewMat());
	if (spotSceneLight != nullptr)
		spotSceneLight->upload(cam.viewMat());
	if (foco != nullptr)
		foco->upload(cam.viewMat());
	if (minero != nullptr)
		minero->upload(dmat4(1.0));
	cam.upload();


	//Primero renderizamos opacos
	for (Abs_Entity* el : gObjects)
	{
		el->render(cam.viewMat());
	}
	//Luego traslucidos
	glDepthMask(GL_FALSE);
	for (Abs_Entity* tel : translucentgObjects)
	{
		tel->render(cam.viewMat());
	}
	glDepthMask(GL_TRUE);
}
//-------------------------------------------------------------------------

void Scene::update() {
	for (Abs_Entity* e : gObjects) {
		e->update();
	}
	//actualizamos el avion y el foco
}

void Scene::sceneDirLight(Camera const& cam) const {
	if (light0_Enabled) {		
		glEnable(GL_LIGHT0);
		glm::fvec4 posDir = { 1, 1, 1, 0 };
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixd(value_ptr(cam.viewMat()));
		glLightfv(GL_LIGHT0, GL_POSITION, value_ptr(posDir));
		glm::fvec4 ambient = { 0, 0, 0, 1 };
		glm::fvec4 diffuse = { 1, 1, 1, 1 };
		glm::fvec4 specular = { 0.5, 0.5, 0.5, 1 };
		glLightfv(GL_LIGHT0, GL_AMBIENT, value_ptr(ambient));

		glLightfv(GL_LIGHT0, GL_DIFFUSE, value_ptr(diffuse));
		glLightfv(GL_LIGHT0, GL_SPECULAR, value_ptr(specular));
	}
	else {
		glDisable(GL_LIGHT0);
	}
}

void Scene::scenePosLight(Camera const& cam) const {
	if (light1_Enabled) {
		glEnable(GL_LIGHT1);

		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixd(value_ptr(cam.viewMat()));

		glm::fvec4 ambient = { 0.0, 0.0, 0.0, 1 };
		glm::fvec4 diffuse = {0.2, 0.8, 0.2, 1 };
		glm::fvec4 specular = { 0.5, 0.5, 0.5, 1 };
		glLightfv(GL_LIGHT1, GL_AMBIENT, value_ptr(ambient));
		glLightfv(GL_LIGHT1, GL_DIFFUSE, value_ptr(diffuse));
		glLightfv(GL_LIGHT1, GL_SPECULAR, value_ptr(specular));

		glm::fvec4 posDir = { 150.0, 150.0, 0.0, 1.0 };
		glLightfv(GL_LIGHT1, GL_POSITION, value_ptr(posDir));

		glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1);
		glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0);
		glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0);
	}
	else {
		glDisable(GL_LIGHT1);
	}
}

void Scene::sceneSpotLight(Camera const& cam) const
{
	if (light2_Enabled) {
		glEnable(GL_LIGHT2);
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixd(value_ptr(cam.viewMat()));

		glm::fvec4 ambient = { 0, 0, 0, 1 };
		glm::fvec4 diffuse = { 0.3, 1, 0.3, 1 };
		glm::fvec4 specular = { 0.5, 1, 0.5, 1 };
		glLightfv(GL_LIGHT2, GL_AMBIENT, value_ptr(ambient));
		glLightfv(GL_LIGHT2, GL_DIFFUSE, value_ptr(diffuse));
		glLightfv(GL_LIGHT2, GL_SPECULAR, value_ptr(specular));

		glm::fvec4 posDir = { 0.0, 0.0, 200.0, 1.0 };
		glLightfv(GL_LIGHT2, GL_POSITION, value_ptr(posDir));

		GLdouble cutoff = 45.0;
		GLdouble epsilon = 0.5;
		glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, cutoff);
		glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, epsilon);
		//glm::fvec3 dir = { 0.0, 1.0, -1.0 };
		glm::fvec3 dir = { 0.0, 0.5, -1.0 };
		glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, value_ptr(dir));
	}
	else {
		glDisable(GL_LIGHT2);
	}
}

void Scene::setLights()
{
	directionalLight = new DirLight();
	directionalLight->setPosDir(glm::fvec4( 1, 1, 1, 0 ));
	directionalLight->setAmb(glm::fvec4(0, 0, 0, 1));
	directionalLight->setDiff(glm::fvec4(1, 1, 1, 1));
	directionalLight->setSpec(glm::fvec4(0.5, 0.5, 0.5, 1));

	positionalLight = new PosLight();
	positionalLight->setPosDir(glm::fvec4(150.0, 150.0, 0.0, 1.0));
	positionalLight->setAmb(glm::fvec4(0.0, 0.0, 0.0, 1));
	positionalLight->setDiff(glm::fvec4(0.3, 0.8, 0.1, 1));
	positionalLight->setSpec(glm::fvec4(0.7, 0.7, 0.7, 1));
	positionalLight->disable();

	spotSceneLight = new SpotLight();
	spotSceneLight->setPosDir(glm::fvec4(0.0, 0.0, 300.0, 1.0));
	spotSceneLight->setAmb(glm::fvec4(0, 0, 0, 1));
	spotSceneLight->setDiff(glm::fvec4(0.3, 1, 0.3, 1));
	spotSceneLight->setSpec(glm::fvec4(0.5, 1, 0.5, 1));
	spotSceneLight->setSpot(glm::fvec3(0.0, 0.0, -1.0), 45.0, 0.5);
	spotSceneLight->disable();

	foco = new SpotLight();
	foco->setSpot(glm::fvec3(0.0, -1.0, 0.0), 20.0, 0.5);
	foco->setAmb(glm::fvec4(0, 0, 0, 1));
	foco->disable();

	minero = new PosLight();
	minero->setPosDir(glm::fvec4(150.0, 150.0, 150.0, 1.0));
	minero->setAmb(glm::fvec4(0.0, 0.0, 0.0, 1));
	minero->setDiff(glm::fvec4(1, 1, 1, 1));
	minero->setSpec(glm::fvec4(0.5, 0.5, 0.5, 1));	
	minero->disable();
}
