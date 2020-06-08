//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Mesh.h"
#include "Texture.h"
#include "Material.h"
#include "Light.h"
//-------------------------------------------------------------------------

class Abs_Entity  // abstract class
{
public:
	Abs_Entity(): mModelMat(1.0), mColor(1.0) {};  // 4x4 identity matrix
	virtual ~Abs_Entity() {};

	Abs_Entity(const Abs_Entity& e) = delete;  // no copy constructor
	Abs_Entity& operator=(const Abs_Entity& e) = delete;  // no copy assignment

	virtual void render(glm::dmat4 const& modelViewMat) const = 0;  // abstract method

	// modeling matrix
	glm::dmat4 const& modelMat() const { return mModelMat; };
	void setModelMat(glm::dmat4 const& aMat) { mModelMat = aMat; };
	void setmColor(glm::dvec4 const& aVec) { mColor = aVec; };//nuevo metodo para poner el color
	void setTexture(Texture* t) { mTexture = t; }	
	virtual void update();

protected:

	Mesh* mMesh = nullptr;   // the mesh
	Texture* mTexture = nullptr; // the texture
	glm::dmat4 mModelMat;    // modeling matrix
	glm::dvec4 mColor;
	// transfers modelViewMat to the GPU
	virtual void upload(glm::dmat4 const& mModelViewMat) const; 
};
//-------------------------------------------------------------------------

class EjesRGB : public Abs_Entity 
{
public:
	explicit EjesRGB(GLdouble l);
	~EjesRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------
class Poligono : public Abs_Entity
{
public:
	explicit Poligono(GLuint numL, GLdouble rd);
	~Poligono();
	virtual void render(glm::dmat4 const& modelViewMat ) const;
};

class Sierpinski : public Abs_Entity
{
public:
	explicit Sierpinski(GLdouble rd, GLuint numP);
	~Sierpinski();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

class TrianguloRGB : public Abs_Entity {
public :
	explicit TrianguloRGB(GLdouble rd);
	~TrianguloRGB();
	virtual void render(glm::dmat4 const& modelViewMat)const;
	virtual void update();
private:
	glm::f64 globalAngle = 0.0;
		glm::f64 localAngle=0.0;
};

class RectanguloRGB : public Abs_Entity {
public:
	explicit RectanguloRGB(GLdouble w, GLdouble h);
	~RectanguloRGB();
	virtual void render(glm::dmat4 const& modelViewMat)const;
};

class RectanguloTexCor : public Abs_Entity {
public:
	explicit RectanguloTexCor(GLdouble w, GLdouble h);
	~RectanguloTexCor();
	virtual void render(glm::dmat4 const& modelViewMat)const;
};


class Estrella3D : public Abs_Entity {
public:
	explicit Estrella3D(GLdouble re, GLdouble np, GLdouble h);
	~Estrella3D();
	virtual void render(glm::dmat4 const& modelViewMat)const;
	virtual void update();
private:
	glm::f64 ZAngle = 0.0;
	glm::f64 YAngle = 0.0;
};


class Suelo : public Abs_Entity {
public:
	explicit Suelo(GLdouble w, GLdouble h, GLuint rw, GLuint rh);
	~Suelo();
	virtual void render(glm::dmat4 const& modelViewMat)const;
};

class Caja : public Abs_Entity {
public:
	explicit Caja(GLdouble ld);
	~Caja();
	virtual void render(glm::dmat4 const& modelViewMat)const;
	void setInteriorTexture(Texture* texture) { cTexture = texture; }
protected:
	Texture* cTexture=nullptr;
};

class Foto : public Abs_Entity {
public:
	explicit Foto(GLdouble w, GLdouble h);
	~Foto();
	virtual void render(glm::dmat4 const& modelViewMat)const;
	virtual void update();
};

class QuadricEntity : public Abs_Entity {
public:
	 QuadricEntity() { q = gluNewQuadric(); };
	~QuadricEntity() { gluDeleteQuadric(q); };

	void setColor(glm::fvec3 c) { color = c; }
protected:
	GLUquadricObj* q;
	glm::fvec3 color = glm::fvec3(1.0, 1.0, 1.0);	//sin color por defecto
};
class Disk : public QuadricEntity {
public:
	explicit Disk(GLdouble innerRadius, GLdouble outerRadius, int slices, int rings);
	void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLdouble innerRadius_, outerRadius_;
	int slices_, rings_;
};
class PartialDisk : public QuadricEntity {
public:
	explicit PartialDisk(GLdouble innerRadius, GLdouble outerRadius, int slices, int rings,
		GLdouble startAngle, GLdouble sweepAngle);
	void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLdouble innerRadius_, outerRadius_;
	int slices_, rings_;
	GLdouble startAngle_, sweepAngle_;
};

class Sphere : public QuadricEntity {
public:
	explicit Sphere(GLdouble rr); // r es el radio de la esfera
	void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLdouble r;
};

class Cylinder : public QuadricEntity {
public:
	explicit Cylinder(GLdouble bR, GLdouble tR, GLdouble h);
	void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLdouble bR;
	GLdouble tR;
	GLdouble h;
};

class AnilloCuadrado : public Abs_Entity {
public:
	explicit AnilloCuadrado();
	virtual ~AnilloCuadrado() {	delete mMesh; mMesh = nullptr; }

	virtual void render(glm::dmat4 const& modelViewMat) const;
};



class EntityWithIndexMesh :public Abs_Entity {
public:
	EntityWithIndexMesh() {};
	virtual ~EntityWithIndexMesh() { delete mMesh; mMesh = nullptr; };
	//void setColor(glm::dvec4 color);
	virtual void render(glm::dmat4 const& modelViewMat) const {};
};

class Cubo :public EntityWithIndexMesh {
public:
	 Cubo();
	virtual ~Cubo() { };

	virtual void render(glm::dmat4 const& modelViewMat) const;
};

//Para las alas del avion con el material de cobre
class CuboCooper : public Cubo {
public:
	explicit CuboCooper() : Cubo() {}
	virtual ~CuboCooper() {}
	virtual void render(glm::dmat4 const& modelViewMat) const ;
private:
	void setCooper() const;
};

class CompoundEntity : public Abs_Entity {
public:
	CompoundEntity();
	virtual ~CompoundEntity();
	virtual void render(glm::dmat4 const& modelViewMat)const;
	
	virtual void addEntity(Abs_Entity* ae) {
		gObjects.push_back(ae);
	}
protected:
	std::vector<Abs_Entity*> gObjects;
	
};

// Para manejar el avion y su luz de forma mas sencilla
class Avion : public CompoundEntity {
public:
	explicit Avion() : CompoundEntity(), rad(150) {}
	explicit Avion(GLdouble rr) : CompoundEntity(),  rad(rr){}
	virtual ~Avion() { };
	void update() override;
	void setLight(SpotLight* l) { foco = l; }
	void setHelices(CompoundEntity* a) { helices = a; }
	void move() { isMoving = !isMoving; }

protected:
	SpotLight* foco = nullptr;
	CompoundEntity* helices = nullptr;
	GLdouble rad = 0.0;
	GLdouble globalAngle = 0.0;
	GLdouble localAngle = 0.0;
	GLdouble hecAngle = 0.0;
	bool isMoving = false;
};

class Cono :public EntityWithIndexMesh {
public:
	explicit Cono(GLdouble h, GLdouble r, GLuint n);
	~Cono() { };

	virtual void render(glm::dmat4 const& modelViewMat) const;
};

class EntityWithMaterial : public Abs_Entity {
public:
	EntityWithMaterial() : Abs_Entity() { };
	virtual ~EntityWithMaterial() { delete mMesh; mMesh = nullptr; delete material; };

	void setMaterial(Material* matl) { material = matl; };
protected:
	Material* material = nullptr;
};

class Esfera :public EntityWithMaterial {
public:
	explicit Esfera(GLdouble r, GLuint p, GLuint m);
	~Esfera() { };

	virtual void render(glm::dmat4 const& modelViewMat) const;
};

class Grid : public EntityWithIndexMesh {
public:
	explicit Grid(GLdouble lado, GLuint nDiv);
	~Grid() { };

	virtual void render(glm::dmat4 const& modelViewMat) const;
};

class GridCube : public CompoundEntity {
public:
	explicit GridCube(GLdouble lado, GLuint nDiv, Texture* t1, Texture* t2);
	~GridCube() { };
private:
	Texture* sideTex = nullptr;
	Texture* tapaTex = nullptr;
};

class SirenCube : public CompoundEntity {
public:
	explicit SirenCube(GLdouble lado, GLuint nDiv, Texture* t1, Texture* t2, GLdouble rr = 120);
	~SirenCube() { };

	void update() override;
	void move() { isMoving = !isMoving; }
	void setLight(SpotLight* l) { sirena = l; }

private:
	SpotLight* sirena = nullptr;
	GLdouble rad = 0.0;
	GLdouble globalAngle = 0.0;
	GLdouble localAngle = 0.0;
	bool isMoving = false;
};


#endif //_H_Entities_H_