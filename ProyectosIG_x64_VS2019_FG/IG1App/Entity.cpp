#include "Entity.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>
#include "Light.h"
#include <iostream>
using namespace glm;

//-------------------------------------------------------------------------

void Abs_Entity::upload(dmat4 const& modelViewMat) const 
{ 
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(modelViewMat));  // transfers modelView matrix to the GPU
}
//-------------------------------------------------------------------------
void Abs_Entity::update() {}
//-------------------------------------------------------------------------

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
		glEnable(GL_COLOR_MATERIAL);
		mMesh->render();
		glDisable(GL_COLOR_MATERIAL);
		glLineWidth(1);
	}
}
//-------------------------------------------------------------------------
//constructora que genera el poligo inscrito en un radio rd con nimL vertices
Poligono::Poligono(GLuint numL, GLdouble rd) : Abs_Entity()
{
	mMesh = Mesh::generaPoligono(numL, rd);
}
Poligono::~Poligono() {
	delete mMesh; mMesh = nullptr;
}
//renderizamos el poligono que queramos
void Poligono::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication

		upload(aMat);
		glLineWidth(2);
		glColor3d(mColor.r, mColor.g, mColor.b);
		mMesh->render();
		glLineWidth(1);
		
	}
}
//constructora que genera el triangulo de puntos de sierspinki
Sierpinski::Sierpinski(GLdouble rd, GLuint numP) : Abs_Entity() {
	mMesh = Mesh::generaSierpinski(rd, numP);
}
//destructora
Sierpinski::~Sierpinski() {
	delete mMesh; mMesh = nullptr;
}
//renderizamos el triangulo de sierpinski
void Sierpinski::render(dmat4 const& modelViewMat) const {
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication

		upload(aMat);
		glPointSize(2);
		glColor4dv(value_ptr(mColor));
		mMesh->render();
		glPointSize(1);
	}
}

//constructora
TrianguloRGB::TrianguloRGB(GLdouble rd) : Abs_Entity() {
	mMesh = Mesh::generaTrianguloRGB(rd);

}
//destructora
TrianguloRGB::~TrianguloRGB() {
	delete mMesh; mMesh = nullptr;
}

//renderizamos el trianguloRGB poniendo color por la aprte de atras
void TrianguloRGB::render(dmat4 const& modelViewMat) const {
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication

		upload(aMat);
		glPolygonMode(GL_BACK, GL_LINE);
		mMesh->render();
	}
}

//  movemos el triangulo RGB por la circunferencia y lo rotamos 
void TrianguloRGB::update() {

	dmat4 mI(1.0);
	mModelMat = translate(mI, dvec3(300 * cos(radians(globalAngle)), 300 * sin(radians(globalAngle)), 0.0)); //move to relPos
	mModelMat = rotate(mModelMat, radians(localAngle), dvec3(0.0, 0.0, 1.0));//rotate himself.

	globalAngle += 5;//increase globalAngle
	localAngle -=5;//increase localAngle 
}

//Genera el rectangulo RGB
RectanguloRGB::RectanguloRGB(GLdouble w, GLdouble h) : Abs_Entity() {
	mMesh = Mesh::generaRectanguloRGB(w, h);
}
//destructora
RectanguloRGB::~RectanguloRGB() {
	delete mMesh; mMesh = nullptr;
}
//ponemos color a la parte de atras del rectangulo
void RectanguloRGB::render(dmat4 const& modelViewMat) const {
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication

		upload(aMat);
		glPolygonMode(GL_BACK, GL_LINE);
		mMesh->render();
	}
}

//Rectangulo con textura
RectanguloTexCor::RectanguloTexCor(GLdouble w, GLdouble h) : Abs_Entity() {
	mMesh = Mesh::generaRectanguloTexCor(w, h, 1, 1);
}

//destructora
RectanguloTexCor::~RectanguloTexCor() {
	delete mMesh; mMesh = nullptr;
}

//renderizamos la textura
void RectanguloTexCor::render(dmat4 const& modelViewMat) const {
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		if (mTexture != nullptr)
			mTexture->bind(GL_REPLACE);
		upload(aMat);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		mMesh->render();
		if (mTexture != nullptr)
			mTexture->unbind();

	}
}

//Genera la estrella
Estrella3D::Estrella3D(GLdouble re, GLdouble np, GLdouble h) : Abs_Entity() {
	mMesh = Mesh::generaEstrellaTexCor(re, np, h);
}
//destructora
Estrella3D::~Estrella3D() {
	delete mMesh; mMesh = nullptr;
}

//renderizamos una estrella y luego le damos la vuelta y la volvemos a renderizar
void Estrella3D::render(dmat4 const& modelViewMat) const {
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		
		if (mTexture != nullptr)
			mTexture->bind(GL_REPLACE);
		upload(aMat);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		mMesh->render();

		aMat = aMat * rotate(dmat4(1.0), radians(180.0), dvec3(0.0, 1.0, 0.0));
		upload(aMat);	//carga en tarjeta y renderiza respecto a lo cargado
		mMesh->render();
		if (mTexture != nullptr)
			mTexture->unbind();
	}
}

//la rotamos en el eje Y y Z
void Estrella3D::update() {
	dmat4 mI(1.0);
	mModelMat = translate(dmat4(1.0), dvec3(-150.0, 250.0, -150.0)); //-50=tam lado caja

	mModelMat = rotate(mModelMat, radians(YAngle), dvec3(0.0, 1.0, 0.0));//rotate Y axis.
	mModelMat = rotate(mModelMat, radians(ZAngle), dvec3(0.0, 0.0, 1.0));//rotate Z axis.

	YAngle += 2;//increase yAngle
	ZAngle -= 4;//increase zAngle 
}

//repetimos la textura segun rw y rh
Suelo::Suelo(GLdouble w, GLdouble h, GLuint rw, GLuint rh) : Abs_Entity() {
	mMesh = Mesh::generaRectanguloTexCor(w, h,rw,rh);
}
//destructora
Suelo::~Suelo() {
	delete mMesh; mMesh = nullptr;
}

//ponemos color a la parte de atras del rectangulo, usamos modulate para mezclar colores si queremos
void Suelo::render(dmat4 const& modelViewMat) const {
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		glColor3d(mColor.r, mColor.g, mColor.b);
		mTexture->bind(GL_MODULATE); 
		upload(aMat);
		glPolygonMode(GL_BACK, GL_FILL);
		mMesh->render();
		mTexture->unbind();
	}
}

Caja::Caja(GLdouble ld) : Abs_Entity() {
	mMesh = Mesh::generaCajaTexCor(ld);
}
//destructora
Caja::~Caja() {
	delete mMesh; mMesh = nullptr; 
}
//renderizamos primero la cara exterior y luego la interior
void Caja::render(dmat4 const& modelViewMat) const {
	if (mMesh != nullptr) {
		glEnable(GL_CULL_FACE);
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication

												
		//renderizamos la parte de fuera
		if (mTexture != nullptr)
			mTexture->bind(GL_REPLACE);

		upload(aMat);
		glCullFace(GL_BACK);
		glPolygonMode(GL_BACK, GL_FILL);

		mMesh->render();

		//renderizamos la parte interior
		if (cTexture != nullptr)
			cTexture->bind(GL_REPLACE);
		glCullFace(GL_FRONT);
		glPolygonMode(GL_FRONT, GL_FILL);

		mMesh->render();

		//hacemos unbind
		if(mTexture!=nullptr)
			mTexture->unbind();
		if (cTexture != nullptr)
			cTexture->unbind();
		glDisable(GL_CULL_FACE);


	}
}

//Foto
Foto::Foto(GLdouble w, GLdouble h) : Abs_Entity() {
	mMesh = Mesh::generaRectanguloTexCor(w, h, 1, 1);

}

//destructora
Foto::~Foto() {
	delete mMesh; mMesh = nullptr;
}

//cogemos la imagen del buffer y la ponemos en la textura
void Foto::render(dmat4 const& modelViewMat) const {
	if (mMesh != nullptr) {

		mTexture->loadColorBuffer(0, 0, 0, 0);

		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		mMesh->render();
		mTexture->unbind();
	}
}

//actualizamos la foto 
void Foto::update() {
	mTexture->loadColorBuffer(0, 0, 0, 0);
	mTexture->unbind();
}

Disk::Disk(GLdouble innerRadius, GLdouble outerRadius, int slices, int rings)
{
	innerRadius_ = innerRadius;
	outerRadius_ = outerRadius;
	slices_ = slices;
	rings_ = rings;
}

void Disk::render(glm::dmat4 const& modelViewMat) const
{
	dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);
	
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(color.r, color.g, color.b);
	gluQuadricDrawStyle(q, GLU_FILL);
	gluDisk(q, innerRadius_, outerRadius_, slices_, rings_);
	glColor3f(1.0, 1.0, 1.0);
	glDisable(GL_COLOR_MATERIAL);
}

PartialDisk::PartialDisk(GLdouble innerRadius, GLdouble outerRadius, int slices, int rings, GLdouble startAngle, GLdouble sweepAngle)
{
	innerRadius_ = innerRadius;
	outerRadius_ = outerRadius;
	slices_ = slices;
	rings_ = rings;
	startAngle_ = startAngle;
	sweepAngle_ = sweepAngle;
}

void PartialDisk::render(glm::dmat4 const& modelViewMat) const
{
	dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);
	 glEnable(GL_COLOR_MATERIAL);
	 glColor3f(color.r, color.g, color.b);
	 gluQuadricDrawStyle(q, GLU_FILL);
	 gluPartialDisk(q, innerRadius_, outerRadius_, slices_, rings_,startAngle_,sweepAngle_);
	 glColor3f(1.0, 1.0, 1.0);
	 glDisable(GL_COLOR_MATERIAL);
}
//Entidades cuadraticas
Sphere::Sphere(GLdouble rr) {
	r = rr; 
}

void Sphere::render(glm::dmat4 const& modelViewMat) const {
	dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(color.r, color.g, color.b);
	gluQuadricDrawStyle(q, GLU_FILL);
	gluSphere(q, r, 50, 50);
	glColor3f(1.0, 1.0, 1.0);
	glDisable(GL_COLOR_MATERIAL);

}

Cylinder::Cylinder(GLdouble baseR, GLdouble topR, GLdouble height) {
	bR = baseR;
	tR = topR;
	h = height;
}

void Cylinder::render(glm::dmat4 const& modelViewMat) const {
	dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(color.r, color.g, color.b);
	gluQuadricDrawStyle(q, GLU_FILL);
	gluCylinder(q, bR, tR, h, 50, 25);
	glColor3f(1.0, 1.0, 1.0);
	glDisable(GL_COLOR_MATERIAL);
}

AnilloCuadrado::AnilloCuadrado()
{
	mMesh = Mesh::generaAnilloCuadrado();
}

void AnilloCuadrado::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication

		upload(aMat);
		glEnable(GL_COLOR_MATERIAL);
		mMesh->render();
		glDisable(GL_COLOR_MATERIAL);
	}
}

//void EntityWithIndexMesh::setColor(glm::dvec4 color)
//{
//	for (int i = 0; i < mMesh->colors->size(); i++) {
//		mMesh->colors. = color;	
//	}
//}

/*void EntityWithIndexMesh::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication

		upload(aMat);
		glEnable(GL_COLOR_MATERIAL);
		//glColor3f(1.0, 0.0, 0.0);
		//glEnable(GL_COLOR_MATERIAL);
		mMesh->render();
		glDisable(GL_COLOR_MATERIAL);

	}
}*/

Cubo::Cubo()
{
	mMesh = IndexMesh::generaIndexCuboConTapas(100.0);
	static_cast<IndexMesh*>(mMesh)->buildNormalVectors();
}

void Cubo::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication

		upload(aMat);
		glEnable(GL_COLOR_MATERIAL);
		glColor3d(mColor.r, mColor.g, mColor.b);
		mMesh->render();
		glColor3f(1.0, 1.0, 1.0);
		glDisable(GL_COLOR_MATERIAL);
	}
		
	
}

void CuboCooper::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication

		upload(aMat);
		setCooper(); //
		mMesh->render();
	}
}



void CuboCooper::setCooper() const
{
	glm::fvec4 ambient = { 0.19125, 0.0735, 0.0225, 1.0 };
	glm::fvec4 diffuse = { 0.7038, 0.27048, 0.0828, 1.0 };
	glm::fvec4 specular = { 0.256777, 0.137622, 0.086014, 1.0 };
	GLuint face = GL_FRONT_AND_BACK;
	GLfloat expF = 12.8;

	glMaterialfv(face, GL_AMBIENT, value_ptr(ambient));
	glMaterialfv(face, GL_DIFFUSE, value_ptr(diffuse));
	glMaterialfv(face, GL_SPECULAR, value_ptr(specular));
	glMaterialf(face, GL_SHININESS, expF);
	glShadeModel(GL_SMOOTH);
}


CompoundEntity::CompoundEntity()
{
}

CompoundEntity::~CompoundEntity()
{
	for (Abs_Entity* el : gObjects)
	{
		delete el;  el = nullptr;
	}
	gObjects.clear();
}

void CompoundEntity::render(glm::dmat4 const& modelViewMat) const
{

	dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication

	//upload(aMat);
	for (Abs_Entity* el : gObjects)
	{
		el->render(aMat);
	}
	
}



Cono::Cono(GLdouble h, GLdouble r, GLuint n) {
	// h=altura del cono, r=radio de la base
	// n=número de muestras, m=número de puntos del perfil
	int m = 3;
	dvec3* perfil = new dvec3[m];
	perfil[0] = dvec3(0.5, 0.0, 0.0);
	perfil[1] = dvec3(r, 0.0, 0.0);
	perfil[2] = dvec3(0.5, h, 0.0);
	mMesh =  MbR::generaIndexMeshByRevolution(m, n, perfil);
}

void Cono::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication

		upload(aMat);
		glEnable(GL_COLOR_MATERIAL);
		glColor3d(mColor.r, mColor.g, mColor.b);
		mMesh->render();
		glDisable(GL_COLOR_MATERIAL);

	}
}

Esfera::Esfera(GLdouble r, GLuint p, GLuint m) {
	dvec3* perfil = new dvec3[p];
	double angle = -90.0;
	for (int i = 0; i < p ; i++) {

		perfil[i] = dvec3(r * cos(radians(angle)), r * sin(radians(angle)), 0.0);
		angle += 180.0 / (p - 1.0);
	}
	perfil[0].x += 0.5;
	perfil[p - 1].x += 0.5;
	mMesh = MbR::generaIndexMeshByRevolution(p, m, perfil);
}

//Para que se se vea el material sin tener en cuenta el color desactivamos el Gl_Color_Material
void Esfera::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication

		upload(aMat);

		glEnable(GL_COLOR_MATERIAL);
		glColor3d(mColor.r, mColor.g, mColor.b);
		if (material != nullptr)
			material->upload();
		mMesh->render();
		glColor3f(1.0, 1.0, 1.0);
		glDisable(GL_COLOR_MATERIAL);
	}
}


void Avion::update()
{
	if (isMoving) {
		dmat4 mI(1.0);
		// movemos las helices
		dmat4 auxHec = helices->modelMat();
		auxHec = rotate(mI, radians(hecAngle), dvec3(0.0, 0.0, 1.0));
		helices->setModelMat(auxHec);
		hecAngle += 2;

		//  movemos el avion
		dmat4 aux = mModelMat;
		dvec3 translation = dvec3(0.0, cos(radians(globalAngle)), sin(radians(globalAngle)));
		aux = translate(mI, rad * translation); //move to relPos
		aux = rotate(aux, radians(globalAngle), dvec3(1.0, 0.0, 0.0));//rotate himself.
		aux = scale(aux, dvec3(0.2, 0.2, 0.2));
		mModelMat = aux;
		// mover el foco
		if (foco != nullptr) {
			foco->setPosDir(rad * translation);
			foco->setSpot(-translation, 20.0, 0.5);
		}


		globalAngle += 2;//increase globalAngle
	}
}

// Extra
Grid::Grid(GLdouble lado, GLuint nDiv)
{
	//mMesh = IndexMesh::generateGrid(lado, nDiv);
	mMesh = IndexMesh::generateGridTex(lado, nDiv);
}

void Grid::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		glEnable(GL_CULL_FACE);
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		if (mTexture != nullptr)
			mTexture->bind(GL_MODULATE);			
		upload(aMat);
		//glEnable(GL_COLOR_MATERIAL);
		//glColor3d(mColor.r, mColor.g, mColor.b);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	// para ver las lineas del grid
		glCullFace(GL_BACK);
		glPolygonMode(GL_BACK, GL_FILL);

		mMesh->render();
		if (mTexture != nullptr)
			mTexture->unbind();
		//glDisable(GL_COLOR_MATERIAL);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDisable(GL_CULL_FACE);
	}
}

// Rotamos y trasladamos cada cara para que se vea como en el enunciado
GridCube::GridCube(GLdouble lado, GLuint nDiv, Texture* t1, Texture* t2)
{
	GLdouble mitad = lado / 2;
	glm::dmat4 mAux;
	// Bottom
	Grid* botGrid = new Grid(lado, nDiv);
	 mAux = botGrid->modelMat();
	mAux = translate(mAux, dvec3(-mitad, -mitad, -mitad));
	mAux = rotate(mAux, radians(90.0), dvec3(1, 0, 0));
	botGrid->setModelMat(mAux);
	botGrid->setTexture(t1);
	addEntity(botGrid);

	// Top
	Grid* topGrid = new Grid(lado, nDiv);
	mAux = topGrid->modelMat();
	mAux = rotate(mAux, radians(90.0), dvec3(0, 0, 1));
	mAux = translate(mAux, dvec3(mitad, -mitad, mitad));
	mAux = rotate(mAux, radians(90.0), dvec3(0, 1, 0));
	topGrid->setModelMat(mAux);
	topGrid->setTexture(t1);
	addEntity(topGrid);

	// Front
	Grid* frontGrid = new Grid(lado, nDiv);
	mAux = frontGrid->modelMat();
	mAux = rotate(mAux, radians(90.0), dvec3(0, 0, 1));
	mAux = translate(mAux, dvec3(-mitad, -mitad, mitad));
	frontGrid->setModelMat(mAux);
	frontGrid->setTexture(t2);
	addEntity(frontGrid);

	// Back
	Grid* backGrid = new Grid(lado, nDiv);
	mAux = backGrid->modelMat();
	mAux = rotate(mAux, radians(90.0), dvec3(0, 0, 1));
	mAux = rotate(mAux, radians(180.0), dvec3(1, 0, 0));
	mAux = translate(mAux, dvec3(-mitad, -mitad, mitad));
	backGrid->setModelMat(mAux);
	backGrid->setTexture(t2);
	addEntity(backGrid);

	// Right
	Grid* rightGrid = new Grid(lado, nDiv);
	mAux = rightGrid->modelMat();
	mAux = rotate(mAux, radians(90.0), dvec3(0, 0, 1));
	mAux = rotate(mAux, radians(90.0), dvec3(1, 0, 0));
	mAux = translate(mAux, dvec3(-mitad, -mitad, mitad));
	rightGrid->setModelMat(mAux);
	rightGrid->setTexture(t2);
	addEntity(rightGrid);

	// Left
	Grid* leftGrid = new Grid(lado, nDiv);
	mAux = leftGrid->modelMat();
	mAux = rotate(mAux, radians(90.0), dvec3(0, 0, 1));
	mAux = rotate(mAux, radians(-90.0), dvec3(1, 0, 0));
	mAux = translate(mAux, dvec3(-mitad, -mitad, mitad));
	leftGrid->setModelMat(mAux);
	leftGrid->setTexture(t2);
	addEntity(leftGrid);
}

SirenCube::SirenCube(GLdouble lado, GLuint nDiv, Texture* t1, Texture* t2, GLdouble rr) : rad(rr), offset_(lado/2)
{
	GridCube* gCube = new GridCube(lado, nDiv, t1, t2);
	addEntity(gCube);
	Esfera* siren = new Esfera(lado / 4, 100, 100);
	siren->setmColor(dvec4(1.0, 0.0, 0.0, 1.0));
	glm::dmat4 mAux = siren->modelMat();
	mAux = translate(mAux, dvec3(0, offset_, 0.0));
	siren->setModelMat(mAux);
	addEntity(siren);
	
}

void SirenCube::update()
{
	if (isMoving) {
		dmat4 mI(1.0);
		//posicionamos la luz, el offset es para colocarlo dentro de la sirena(la esfera roja) y no ilumine nada del cubo
		sirena->setPosDir(fvec3((rad + offset_) * sin(radians(lightAngle)), 0.0, (rad + offset_) * cos(radians(lightAngle))));
		
		//  movemos el toda la entidad
		dmat4 aux = mModelMat;
		dvec3 translation = dvec3(0.0, rad * cos(radians(globalAngle)), rad * sin(radians(globalAngle)));
		aux = translate(mI, translation); //move to relPos
		aux = rotate(aux, radians(globalAngle), dvec3(1.0, 0.0, 0.0));
		aux = scale(aux, dvec3(0.1, 0.1, 0.1));
		mModelMat = aux;

		// tal y como lo hemos hecho, el angulo que de rotacion y translacion tienen que ser el mismo
		globalAngle += 0.2;//incrementamos globalAngle		
		lightAngle += 2;//incrementamos el lightAngle 
	}
}

void SirenCube::render(glm::dmat4 const& modelViewMat) const
{
	dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication

	upload(aMat);

	// cargamos la luz de forma local al objeto
	if(sirena!=nullptr)
		sirena->upload(aMat);

	for (Abs_Entity* el : gObjects) {
		el->render(aMat);
	}
}