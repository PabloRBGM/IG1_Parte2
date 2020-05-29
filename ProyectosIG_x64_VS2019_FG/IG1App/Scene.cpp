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
		//AnilloCuadrado* anillo = new AnilloCuadrado();
		//gObjects.push_back(anillo);
		EntityWithIndexMesh* cubo = new Cubo();
		cubo->setmColor(dvec4(1.0, 0.0, 0.0, 1.0));
		gObjects.push_back(cubo);

	}
	else if (mId == 3) {
		helices = new CompoundEntity();
		//gObjects.push_back(helices);

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
		gObjects.push_back(helices);
		//-----------------------------------------------------------------------
		CompoundEntity* chasis = new CompoundEntity();
		//gObjects.push_back(chasis);

		Sphere* sphere = new Sphere(100.0);
		sphere->setColor({ 1.0, 0.0 ,0.0 });

		chasis->addEntity(sphere);
		//chasis->addEntity(helices);
		//---------------------------------------
		avion = new CompoundEntity();
		avion->addEntity(chasis);
		Cubo* cubo = new Cubo();
		glm::dmat4 mAuxCubo = cubo->modelMat();

		//mAuxCubo = rotate(mAuxCubo, radians(270.0), dvec3(0, 1, 0));
		mAuxCubo = scale(mAuxCubo, dvec3(3.5,0.3, 1.5));
		cubo->setModelMat(mAuxCubo);
		//cubo->setmColor({ 0.0,1.0,0.0,1.0 });
		cubo->setIsCooperMat(false, true);
		glm::dmat4 mAuxAvion = avion->modelMat();
		mAuxAvion = translate(mAuxAvion, dvec3(0, 150, 0));
		mAuxAvion = scale(mAuxAvion, dvec3(0.2, 0.2, 0.2));
		avion->setModelMat(mAuxAvion);
		avion->addEntity(cubo);
		
		gObjects.push_back(avion);
		//foco en la misma posición que el avion
		foco->setPosDir(fvec3(0, 150, 0));
		/*Cono* cono = new Cono(100.0, 50.0, 3);
		cono->setmColor(dvec4(0.0, 0.0, 1.0, 1.0));
		glm::dmat4 mAuxC1 = cono->modelMat();

		mAuxC1 = translate(mAuxC1, dvec3(0, 150, 0));
		cono->setModelMat(mAuxC1);
		gObjects.push_back(cono);*/
	
		/*CompoundEntity* ce = new CompoundEntity;
		Cubo* cubo2 = new Cubo();
		cubo2->setmColor(dvec4(0.498, 1.0, 0.831, 1.0));*/

		//cubo2->setIsCooperMat();
		
		/*gObjects.push_back(ce);
		ce->addEntity(cubo2);*/
		//gObjects.push_back(cubo2);
		Esfera* esfera = new Esfera(100.0, 50, 50);
		esfera->setmColor(dvec4(0.498, 1.0, 0.831, 1.0));
		Material* goldMat = new Material();
		goldMat->setGold();
		esfera->setMaterial(goldMat);
		// True True = color macizo
		// True false = oro
		// false * = render sin caractericticas propias del material
		//esfera->setIsGoldMat(false, false);
		//esfera->setGold();
		gObjects.push_back(esfera);
		

		/*Sphere* sphere2 = new Sphere(100.0);
		sphere2->setColor(fvec3(0.498, 1.0, 0.831));
		glm::dmat4 mAuxC4 = sphere2->modelMat();

		mAuxC4 = translate(mAuxC4, dvec3(200, 0, 0));
		sphere2->setModelMat(mAuxC4);
		gObjects.push_back(sphere2);*/

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
	glm::fvec4 amb = {0.0, 0.0, 0.0, 1.0};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, value_ptr(amb));

	//glDisable(GL_LIGHTING);
}
void Scene::movement()
{
	if (isMoving) {
		dmat4 mI(1.0);
		// movemos las helices
		dmat4 auxHec = helices->modelMat();
		//auxHec = translate(mI, rad * translation);
		auxHec = rotate(mI, radians(hecAngle), dvec3(0.0, 0.0, 1.0));
		std::cout << hecAngle << std::endl;
		hecAngle += 2;
		
		//  movemos el avion
		dmat4 aux = avion->modelMat();
		dvec3 translation = dvec3(0.0, cos(radians(globalAngle)), sin(radians(globalAngle)));
		aux = translate(mI, rad * translation); //move to relPos
		aux = rotate(aux, radians(localAngle), dvec3(1.0, 0.0, 0.0));//rotate himself.
		aux = scale(aux, dvec3(0.2, 0.2, 0.2));
		avion->setModelMat(aux);
		// mover el foco
		foco->setPosDir(rad * translation);
		foco->setSpot(-translation, 20.0, 0.5);

		
		globalAngle += 2;//increase globalAngle
		localAngle += 2;//increase localAngle 
	}
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
	/*if (mId == 1)*/glDisable(GL_TEXTURE_2D);
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
	movement();
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

		//glLightfv(GL_LIGHT0, GL_DIFFUSE, value_ptr(diffuse));
		//glLightfv(GL_LIGHT0, GL_SPECULAR, value_ptr(specular));
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

	spotSceneLight = new SpotLight();
	spotSceneLight->setPosDir(glm::fvec4(0.0, 0.0, 200.0, 1.0));
	spotSceneLight->setAmb(glm::fvec4(0, 0, 0, 1));
	spotSceneLight->setDiff(glm::fvec4(0.3, 1, 0.3, 1));
	spotSceneLight->setSpec(glm::fvec4(0.5, 1, 0.5, 1));
	spotSceneLight->setSpot(glm::fvec3(0.0, 0.0, -1.0), 45.0, 0.5);

	foco = new SpotLight();
	//foco->setPosDir(glm::fvec4(0.0, 0.0, 200.0, 1.0)); //ahora da igual

	foco->setSpot(glm::fvec3(0.0, -1.0, 0.0), 20.0, 0.5);
	//foco->disable();
}
