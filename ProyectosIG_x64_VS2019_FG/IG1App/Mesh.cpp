#include "Mesh.h"
#include "CheckML.h"
#include <fstream>
using namespace std;
using namespace glm;
#include <iostream>
//-------------------------------------------------------------------------

void Mesh::draw() const 
{

    glDrawArrays(mPrimitive, 0, size());   // primitive graphic, first index and number of elements to be rendered
	/*unsigned int stripIndices[] =
	{ 0, 1, 2, 3, 4, 5, 6, 7, 0, 1 };
	glDrawElements(GL_TRIANGLE_STRIP, 10, GL_UNSIGNED_INT,
		stripIndices);*/
	
}
//-------------------------------------------------------------------------

void Mesh::render() const 
{
  if (vVertices.size() > 0) {  // transfer data
    // transfer the coordinates of the vertices
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, vVertices.data());  // number of coordinates per vertex, type of each coordinate, stride, pointer 
    if (vColors.size() > 0) { // transfer colors
      glEnableClientState(GL_COLOR_ARRAY);
      glColorPointer(4, GL_DOUBLE, 0, vColors.data());  // components number (rgba=4), type of each component, stride, pointer  
    }
    if (vTexCoords.size() > 0) {
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glTexCoordPointer(2, GL_DOUBLE, 0, vTexCoords.data());
    }
	if (vNormals.size() > 0) {
		glEnableClientState(GL_NORMAL_ARRAY);
		glNormalPointer(GL_DOUBLE, 0, vNormals.data());
	}


	draw();

    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

  }
}
//-------------------------------------------------------------------------

Mesh * Mesh::createRGBAxes(GLdouble l)
{
  Mesh* mesh = new Mesh();

  mesh->mPrimitive = GL_LINES;

  mesh->mNumVertices = 6;
  mesh->vVertices.reserve(mesh->mNumVertices);

  // X axis vertices
  mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
  mesh->vVertices.emplace_back(l, 0.0, 0.0);
  // Y axis vertices
  mesh->vVertices.emplace_back(0, 0.0, 0.0);
  mesh->vVertices.emplace_back(0.0, l, 0.0);
  // Z axis vertices
  mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
  mesh->vVertices.emplace_back(0.0, 0.0, l);

  mesh->vColors.reserve(mesh->mNumVertices);
  // X axis color: red  (Alpha = 1 : fully opaque)
  mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
  mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
  // Y axis color: green
  mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
  mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
  // Z axis color: blue
  mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
  mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
 
  return mesh;
}
//-------------------------------------------------------------------------
//genera un poligono con numL vertices inscrito en una circunferencia de radio rd
Mesh* Mesh::generaPoligono(GLuint numL, GLdouble rd) {
    Mesh* mesh = new Mesh();
    mesh->mPrimitive = GL_LINE_LOOP;

    mesh->mNumVertices = numL;
    mesh->vVertices.reserve(mesh->mNumVertices);

    float angle = 90;
    for (int i = 0; i < mesh->mNumVertices; i++) {
        mesh->vVertices.emplace_back(rd*cos(radians(angle)), rd * sin(radians(angle)), 0.0);
        angle += 360.0 / numL;
    }

    return mesh;
}
//genera el triangulo de sierpinski  con numP puntos inscrito en una circunferencia de radio rd
Mesh* Mesh::generaSierpinski(GLdouble rd, GLuint numP) {
    Mesh* triangulo = generaPoligono(3, rd);

    Mesh* mesh = new Mesh();
    mesh->mPrimitive = GL_POINTS;

    mesh->mNumVertices = numP;
    mesh->vVertices.reserve(mesh->mNumVertices);

    dvec3 P_K1 = triangulo->vVertices[rand() % 3];
    dvec3 P_Ti;
    dvec3 Pk;
    for (int i = 0; i < numP; i++) {
        P_Ti = triangulo->vVertices[rand() % 3];
         Pk = { (P_K1.x + P_Ti.x) / 2, (P_K1.y + P_Ti.y) / 2, (P_K1.z + P_Ti.z) / 2 };
         P_K1 = Pk;
         mesh->vVertices.emplace_back(Pk);

    }
    
    delete triangulo; triangulo = nullptr;
    return mesh;
}


//generamos el triangulo RGB
Mesh* Mesh::generaTrianguloRGB(GLdouble rd) {
    Mesh* mesh = generaPoligono(3, rd);
    mesh->mPrimitive = GL_TRIANGLES;
    mesh->vColors.reserve(mesh->mNumVertices);

    mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
    mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
    mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);

    return mesh;
}
//generamos el rectangulo con ancho w y alto h
Mesh* Mesh::generaRectangulo(GLdouble w, GLdouble h) {
    Mesh* mesh = new Mesh();

    mesh->mPrimitive = GL_TRIANGLE_STRIP;

    mesh->mNumVertices = 4;
    mesh->vVertices.reserve(mesh->mNumVertices);

    mesh->vVertices = { {-w / 2, h / 2, 0}, {-w / 2, -h / 2, 0}, {w / 2, h / 2, 0}, {w / 2, -h / 2, 0} };
   
    return mesh;
}

//utiliza generaRectangulo y le pone color
Mesh* Mesh::generaRectanguloRGB(GLdouble w, GLdouble h) {
    Mesh* mesh = generaRectangulo(w, h);
    mesh->vColors.reserve(mesh->mNumVertices);
    mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
    mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
    mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
    mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);

    return mesh;
}

//rectangulo con textura repetida en toda su superficie
Mesh* Mesh::generaRectanguloTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh) {
    Mesh* mesh = generaRectangulo(w, h);

    mesh->vTexCoords.reserve(mesh->mNumVertices);

    mesh->vTexCoords.emplace_back(0, rh);
    mesh->vTexCoords.emplace_back(0, 0);
    mesh->vTexCoords.emplace_back(rw, rh);
    mesh->vTexCoords.emplace_back(rw, 0);  
    return mesh;
}

//genera la estrella segun el numero de puntas
Mesh* Mesh::generaEstrella3D(GLdouble re, GLdouble np, GLdouble h) {
    Mesh* mesh = new Mesh();

    mesh->mPrimitive = GL_TRIANGLE_FAN;
    mesh->mNumVertices = 2 * np + 2;
    mesh->vVertices.reserve(mesh->mNumVertices);

    mesh->vVertices.emplace_back(0.0, 0.0, 0.0);//empieza en el cero

    float angle = 90;
    for (int i = 0; i < mesh->mNumVertices - 1; i++) {
        if (i % 2 == 0)  mesh->vVertices.emplace_back(re * cos(radians(angle)), re * sin(radians(angle)), h);//exterior
        else   mesh->vVertices.emplace_back(re * cos(radians(angle)) / 2, re * sin(radians(angle)) / 2, h);//interior

        angle += 360.0 / (mesh->mNumVertices - 2);
    }

    return mesh;
}

//textura con coordenadas
Mesh* Mesh::generaEstrellaTexCor(GLdouble re, GLuint np, GLdouble h) {
    Mesh* mesh = generaEstrella3D(re,np,h);

    mesh->vTexCoords.reserve(mesh->mNumVertices);
    mesh->vTexCoords.emplace_back(0.5, 0.5); //vertice central

    //modulo 8 para que utilice la parte que queremos de la textura en la cara correspondiente de la estrella
    for (int i = 0; i < mesh->mNumVertices-1; i++) {
        if (i % 8 == 0)         mesh->vTexCoords.emplace_back(1, 1);
        else if (i % 8 == 1)     mesh->vTexCoords.emplace_back(0.5, 1);
        else if (i % 8 == 2)     mesh->vTexCoords.emplace_back(0, 1);
        else if (i % 8 == 3)         mesh->vTexCoords.emplace_back(0, 0.5);
        else if (i % 8 == 4)     mesh->vTexCoords.emplace_back(0, 0);
        else if (i % 8 == 5)     mesh->vTexCoords.emplace_back(0.5, 0);
        else if (i % 8 == 6)         mesh->vTexCoords.emplace_back(1, 0);
        else if (i % 8 == 7)     mesh->vTexCoords.emplace_back(1, 0.5);
    }
    return mesh;
 }

//genera el cubo y le pasamos los vertices en el orden correspondiente
Mesh* Mesh::generaContCubo(GLdouble ld) {
    Mesh* mesh = new Mesh();

    mesh->mPrimitive = GL_TRIANGLE_STRIP;

    mesh->mNumVertices = 10;
    mesh->vVertices.reserve(mesh->mNumVertices);
    
    mesh->vVertices = { {0 , ld , ld }, {0 , 0 , ld }, {ld , ld , ld }, {ld , 0 , ld },
    {ld , ld , 0 }, {ld , 0 , 0 }, {0 , ld , 0 }, {0 , 0, 0}, 
    {0 , ld , ld }, {0 , 0 , ld } };

    return mesh;
}

//genera un cubo con la textura repetida correspondientemente
Mesh* Mesh::generaCajaTexCor(GLdouble nl) {
    Mesh* mesh = generaContCubo(nl);

    mesh->vTexCoords.reserve(mesh->mNumVertices);

    mesh->vTexCoords.emplace_back(0, 1);    //v0
    mesh->vTexCoords.emplace_back(0, 0);    //v1
    mesh->vTexCoords.emplace_back(1, 1);    //v2  
    mesh->vTexCoords.emplace_back(1, 0);    //v3

    mesh->vTexCoords.emplace_back(2, 1);    //v4
    mesh->vTexCoords.emplace_back(2, 0);    //v5
    mesh->vTexCoords.emplace_back(3, 1);    //v6
    mesh->vTexCoords.emplace_back(3, 0);    //v7

    mesh->vTexCoords.emplace_back(4, 1);    //v0
    mesh->vTexCoords.emplace_back(4, 0);    //v1
   

    return mesh;
 }

Mesh* Mesh::generaAnilloCuadrado()
{
	Mesh* mesh = new Mesh();
	mesh->mPrimitive = GL_TRIANGLE_STRIP;
	mesh->mNumVertices = 10;
	mesh->vVertices.reserve(mesh->mNumVertices);
	mesh->vColors.reserve(mesh->mNumVertices);
	mesh->vNormals.reserve(mesh->mNumVertices);

	mesh->vVertices = {
		{ 30.0, 30.0, 0.0 },
		{ 10.0, 10.0, 0.0 },
		{ 70.0, 30.0, 0.0 },
		{ 90.0, 10.0, 0.0 },
		{ 70.0, 70.0, 0.0 },
		{ 90.0, 90.0, 0.0 },
		{ 30.0, 70.0, 0.0 },
		{ 10.0, 90.0, 0.0 },
		{ 30.0, 30.0, 0.0 },
		{ 10.0, 10.0, 0.0 }
	};
	mesh->vColors = {
		{0.0, 0.0, 0.0,1.0},
		{1.0, 0.0, 0.0,1.0},
		{0.0, 1.0, 0.0,1.0 },
		{0.0, 0.0, 1.0,1.0},
		{1.0, 1.0, 0.0,1.0},
		{1.0, 0.0, 1.0,1.0},
		{0.0, 1.0, 1.0,1.0},
		{1.0, 0.0, 0.0,1.0},		{0.0, 0.0, 0.0,1.0},
		{1.0, 0.0, 0.0,1.0}	};

	//al ser paralelo al eje XY todas las normales son el eje X
	for (int i = 0; i < mesh->mNumVertices;i++) {
		mesh->vNormals.emplace_back(0.0,0.0,1.0 );
	}
	
	return mesh;
}

void IndexMesh::render() const
{
	if (vVertices.size() > 0) {  // transfer data
   // transfer the coordinates of the vertices
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_DOUBLE, 0, vVertices.data());  // number of coordinates per vertex, type of each coordinate, stride, pointer 
		if (vColors.size() > 0) { // transfer colors
			glEnableClientState(GL_COLOR_ARRAY);
			glColorPointer(4, GL_DOUBLE, 0, vColors.data());  // components number (rgba=4), type of each component, stride, pointer  
		}
		if (vTexCoords.size() > 0) {
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(2, GL_DOUBLE, 0, vTexCoords.data());
		}
		if (vNormals.size() > 0) {
			glEnableClientState(GL_NORMAL_ARRAY);
			glNormalPointer(GL_DOUBLE, 0, vNormals.data());
		}
		if (vIndices != nullptr) {
			glEnableClientState(GL_INDEX_ARRAY);
			glIndexPointer(GL_UNSIGNED_INT, 0, vIndices);
		}

		draw();

		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_INDEX_ARRAY);
	}
}

void IndexMesh::draw() const
{
	glDrawElements(mPrimitive, nNumIndices,
		GL_UNSIGNED_INT, vIndices);
}

IndexMesh* IndexMesh::generaIndexCuboConTapas(GLdouble lda)
{

	IndexMesh* indexMesh = new IndexMesh();
	indexMesh->mPrimitive = GL_TRIANGLES;
	indexMesh->mNumVertices = 8;
	indexMesh->vVertices.reserve(indexMesh->mNumVertices);
	indexMesh->vColors.reserve(indexMesh->mNumVertices);
	indexMesh->vNormals.reserve(indexMesh->mNumVertices);   //Tamño igual al vector de vértices
    GLdouble ld = lda / 2;
	indexMesh->vVertices = { {-ld , ld , ld }, {-ld , -ld , ld }, {ld , ld , ld }, {ld , -ld , ld },
   {ld , ld , -ld }, {ld , -ld , -ld }, {-ld , ld , -ld }, {-ld , -ld, -ld}};


	for (int i = 0; i < indexMesh->mNumVertices; i++) {
		indexMesh->vColors.emplace_back(1.0, 0.0, 0.0,1.0);
	}
    //indexMesh->vNormals = indexMesh->vVertices;
    //Construi
	indexMesh->nNumIndices = 36;

	indexMesh->vIndices = new GLuint[indexMesh->nNumIndices]{
		0, 1, 2,  2, 1, 3,
		2, 3, 4,  4, 3, 5,
	
		6, 5, 7,  4, 5, 6,
		6, 7, 0,  0, 7, 1,

        4, 0, 2, 6, 0, 4,
	    1, 7, 3,  3, 7, 5 
    };

	return indexMesh;
}

void IndexMesh::buildNormalVectors() {
    //inicializar las componentes del vector de normales al vector 0
    for (int i = 0; i < mNumVertices; i++) {
        vNormals.emplace_back(dvec3(0, 0, 0));
    }

    for (int i = 0; i < nNumIndices; i += 3) {
        glm::dvec3 n =
            glm::cross(
            (vVertices[vIndices[i + 2]] - vVertices[vIndices[i + 1]]),
                (vVertices[vIndices[i]] - vVertices[vIndices[i + 1]]));
        //sumamos a las normales del triangulo
        for (int j = i; j < i + 3; j++) {
            vNormals[vIndices[j]] += n;
        }
    }

    //normalizamos el vector de normales
    for (int i = 0; i < mNumVertices; i++) {
        vNormals[i] = glm::normalize(vNormals[i]);
    }
}