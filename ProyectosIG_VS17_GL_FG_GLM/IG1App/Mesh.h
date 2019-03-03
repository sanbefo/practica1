//#pragma once
#ifndef _H_Mesh_H_
#define _H_Mesh_H_

#include <GL/freeglut.h>
#include <glm.hpp>

//-------------------------------------------------------------------------

class Mesh 
{
public:
	static Mesh* createRGBAxes(GLdouble l); // creates a new 3D RGB axes mesh
 
	Mesh(void) { };
	~Mesh(void);
	virtual void render();

	glm::dvec3* getVertices() { return vertices; };  // vertex array
	glm::dvec4* getColors() { return colors; };      // color array
	glm::dvec2* getTextures() { return textures; };  // texture array

	// POLIESPIRAL
	static Mesh* generaPoliespiral(glm::dvec2 verIni, GLdouble angIni, GLdouble incrAng, GLdouble ladoIni, GLdouble incrLado, GLuint numVert);

	// DRAGON
	static Mesh* generaDragon(GLuint numVert);

	// TRIANGULO
	static Mesh* generaTriangulo(GLdouble r);
	static Mesh* generaTrianguloRGB(GLdouble r);
	static Mesh* generaTrianguloAnimado(GLdouble r);

	// RECTANGULO
	static Mesh* generaRectangulo(GLdouble w, GLdouble h);
	static Mesh* generaRectanguloRGB(GLdouble w, GLdouble h);
	static Mesh* generaSuelo(GLdouble w, GLdouble h);
	static Mesh* generaRectanguloTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh);

	//ESTRELLA 3D
	static Mesh* generaEstrella3D(GLdouble re, GLdouble np, GLdouble h);
	static Mesh* generaEstrellaTexCor(GLdouble r, GLdouble nL, GLdouble h);

	//CAJA
	static Mesh* generaContCubo(GLdouble l);
	static Mesh* generaCajaTexCor(GLdouble l);
protected:

	GLuint numVertices = 0;   // arrays size (number of elements)
	GLuint primitive = GL_TRIANGLES;  // graphic primitive: GL_POINTS, GL_LINES, GL_TRIANGLES, ...

	glm::dvec3* vertices = nullptr;  // vertex array
	glm::dvec4* colors = nullptr;    // color array
	glm::dvec2* textures = nullptr;    // texture array
};

//-------------------------------------------------------------------------

#endif //_H_Scene_H_