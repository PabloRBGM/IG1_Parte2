//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Mesh.h"
#include "Texture.h"

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

#endif //_H_Entities_H_