#include "Scene.h"
#include "CheckML.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;
//-------------------------------------------------------------------------
//creamos los objectos que queremos y los añadimos a gObjects 
void Scene::init()
{ 
	setGL();  // OpenGL settings
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
		CompoundEntity* helices = new CompoundEntity();
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
		//-----------------------------------------------------------------------
		CompoundEntity* chasis = new CompoundEntity();
		//gObjects.push_back(chasis);

		Sphere* sphere = new Sphere(100.0);
		sphere->setColor({ 1.0, 0.0 ,0.0 });

		chasis->addEntity(sphere);
		chasis->addEntity(helices);
		//---------------------------------------
		CompoundEntity* avion = new CompoundEntity();
		avion->addEntity(chasis);
		Cubo* cubo = new Cubo();
		glm::dmat4 mAuxCubo = cubo->modelMat();

		//mAuxCubo = rotate(mAuxCubo, radians(270.0), dvec3(0, 1, 0));
		mAuxCubo = scale(mAuxCubo, dvec3(3.5,0.3, 1.5));
		cubo->setModelMat(mAuxCubo);
		cubo->setmColor({ 0.0,1.0,0.0,1.0 });

		glm::dmat4 mAuxAvion = avion->modelMat();
		mAuxAvion = translate(mAuxAvion, dvec3(0, 120, 0));
		mAuxAvion = scale(mAuxAvion, dvec3(0.2, 0.2, 0.2));
		avion->setModelMat(mAuxAvion);
		avion->addEntity(cubo);
		
		gObjects.push_back(avion);

		/*Cono* cono = new Cono(100.0, 50.0, 3);
		cono->setmColor(dvec4(0.0, 0.0, 1.0, 1.0));
		glm::dmat4 mAuxC1 = cono->modelMat();

		mAuxC1 = translate(mAuxC1, dvec3(0, 150, 0));
		cono->setModelMat(mAuxC1);
		gObjects.push_back(cono);*/
	

		
		Esfera* esfera = new Esfera(100.0, 50, 50);
		esfera->setmColor(dvec4(0.498, 1.0, 0.831, 1.0));
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


}
//-------------------------------------------------------------------------
void Scene::resetGL() 
{
	glClearColor(.0, .0, .0, .0);  // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);  // disable Depth test 	
	glDisable(GL_BLEND);
	//glDisable(GL_ALPHA_TEST);
	/*if (mId == 1)*/glDisable(GL_TEXTURE_2D);

}
//-------------------------------------------------------------------------

void Scene::render(Camera const& cam) const 
{
	sceneDirLight(cam);
	cam.upload();
	//sceneDirLight(cam);

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
}

void Scene::sceneDirLight(Camera const& cam) const {
	glEnable(GL_LIGHTING);
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
