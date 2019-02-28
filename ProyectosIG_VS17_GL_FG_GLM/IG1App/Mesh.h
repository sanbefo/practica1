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

	// POLIESPIRAL
	static Mesh* generaPoliespiral(glm::dvec2 verIni, GLdouble angIni, GLdouble incrAng, GLdouble ladoIni, GLdouble incrLado, GLuint numVert);

	// DRAGON
	static Mesh* generaDragon(GLuint numVert);

	// TRIANGULO
	static Mesh* generaTriangulo(GLdouble r);
	static Mesh* generaTrianguloRGB(GLdouble r);

	// RECTANGULO
	static Mesh* generaRectangulo(GLdouble w, GLdouble h);
	static Mesh* generaRectanguloRGB(GLdouble w, GLdouble h);

	//ESTRELLA 3D
	static Mesh* generaEstrella3D(GLdouble re, GLdouble np, GLdouble h);

	//CAJA
	static Mesh* generaContCubo(GLdouble l);
protected:

	GLuint numVertices = 0;   // arrays size (number of elements)
	GLuint primitive = GL_TRIANGLES;  // graphic primitive: GL_POINTS, GL_LINES, GL_TRIANGLES, ...

	glm::dvec3* vertices = nullptr;  // vertex array
	glm::dvec4* colors = nullptr;    // color array
};

//-------------------------------------------------------------------------

#endif //_H_Scene_H_