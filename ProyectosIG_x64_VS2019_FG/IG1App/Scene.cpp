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

	// allocate memory and load resources
    // Lights
    // Textures
	if (mId == 1) {
		gTextures.push_back(new Texture());
		gTextures.push_back(new Texture());
		gTextures.push_back(new Texture());
		gTextures.push_back(new Texture());
		gTextures.push_back(new Texture());
		gTextures.push_back(new Texture());

		gTextures[0]->load("../Bmps/baldosaP.bmp");//textura estrella
		gTextures[1]->load("../Bmps/baldosaC.bmp");//textura suelo
		gTextures[2]->load("../Bmps/container.bmp");//textura cubo fuera
		gTextures[3]->load("../Bmps/papelE.bmp");//textura cubo interior
		gTextures[4]->load("../Bmps/Zelda.bmp");//textura que se va a modificar en la foto
		gTextures[5]->load("../Bmps/windowV.bmp", 150);//textura de la cristalera
		// Graphics objects (entities) of the scene


		//cristalera
		Caja* cristalera = new Caja(600);
		cristalera->setTexture(gTextures[5]);
		cristalera->setModelMat(translate(dmat4(1.0), dvec3(-300, 0.0, -300)));
		cristalera->setModelMat(scale(cristalera->modelMat(), { 1.0, 0.5, 1.0 }));
		translucentgObjects.push_back(cristalera);

		//suelo centrado en el plano y = 0
		Suelo* suelo = new Suelo(600, 600, 10, 10);
		suelo->setTexture(gTextures[1]);
		suelo->setmColor({ 1.0, 1.0, 1.0, 1.0 });//le ponemos el color con el que modular
		suelo->setModelMat (rotate(suelo->modelMat(), radians(90.0), dvec3(1.0, 0.0, 0.0)));//rotate x axis.
		gObjects.push_back(suelo);

		//caja en el cuadrante -x, -z
		Caja* caja = new Caja(100);
		caja->setTexture(gTextures[2]);
		caja->setInteriorTexture(gTextures[3]);
		caja->setModelMat(translate(dmat4(1.0), {-200.0, 0.0, -200.0}));
		gObjects.push_back(caja);

		//estrella encima de la caja
		Estrella3D* star = new Estrella3D(50, 4, 50.0);
		star->setTexture(gTextures[0]);
		star->setModelMat(translate(dmat4(1.0), dvec3(-150.0, 250.0, -150.0)));
		gObjects.push_back(star);

		//foto centrada encima del suelo
		Foto* foto = new Foto(150, 100);
		foto->setModelMat(translate(dmat4(1.0), { 0.0, 2.0, 0.0 }));
		foto->setModelMat(rotate(foto->modelMat(), radians(90.0), dvec3(1.0, 0.0, 0.0)));
		gObjects.push_back(foto);


	}
	else if(mId == 0){
		
		Poligono* circle = new Poligono(360.0, 300);
		circle->setmColor({ 1.0, 0.0, 1.0,1.0 });
		Sierpinski* sier = new Sierpinski(300, 25000);
		sier->setmColor({1.0, 1.0, 0.0, 1.0});

		RectanguloRGB* rRGB = new RectanguloRGB(800, 600);
		rRGB->setModelMat(translate(rRGB->modelMat(), dvec3(0, 0, -100)));

		gObjects.push_back(circle);
		gObjects.push_back(sier);
		gObjects.push_back(rRGB);
		auto g = new TrianguloRGB(40.0);
		gObjects.push_back(g);
	}
	else if (mId == 2) {
		glClearColor(0.7, 0.8, 0.9, 0.0);

		Sphere* esfera = new Sphere(100.0);
		gObjects.push_back(esfera);

		Cylinder* cono = new Cylinder(50.0, 0, 100.0);
		glm::dmat4 mAux = cono->modelMat();
		mAux = translate(mAux, dvec3(0, 85, 0));
		mAux = rotate(mAux, radians(-90.0), dvec3(1.0, 0, 0));
		cono->setModelMat(mAux);
		gObjects.push_back(cono);

		Disk* disco = new Disk(50, 100, 50, 2);
		glm::dmat4 mAuxDisk = disco->modelMat();
		mAuxDisk = translate(mAuxDisk, dvec3(0, 75, 0));
		mAuxDisk = rotate(mAuxDisk, radians(-90.0), dvec3(1.0, 0, 0));
		disco->setModelMat(mAuxDisk);
		gObjects.push_back(disco);

		PartialDisk* partDisco = new PartialDisk(70, 90, 50, 2,90,180);
		glm::dmat4 mAuxPartDisk = partDisco->modelMat();
		mAuxPartDisk = translate(mAuxPartDisk, dvec3(0, 0, 60));
		//mAuxDisk = rotate(mAuxPartDisk, radians(-90.0), dvec3(1.0, 0, 0));
		partDisco->setModelMat(mAuxPartDisk);
		gObjects.push_back(partDisco);
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
	if(mId == 1)glEnable(GL_TEXTURE_2D);  


}
//-------------------------------------------------------------------------
void Scene::resetGL() 
{
	glClearColor(.0, .0, .0, .0);  // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);  // disable Depth test 	
	glDisable(GL_BLEND);
	//glDisable(GL_ALPHA_TEST);
	if (mId == 1)glDisable(GL_TEXTURE_2D);

}
//-------------------------------------------------------------------------

void Scene::render(Camera const& cam) const 
{
	cam.upload();
	sceneDirLight(cam);

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
