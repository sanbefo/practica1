#include "Mesh.h"

using namespace glm;

//-------------------------------------------------------------------------

Mesh ::~Mesh(void) 
{
  delete[] vertices;  vertices = nullptr;
  delete[] colors;    colors = nullptr;
}
//-------------------------------------------------------------------------

void Mesh::render()
{
  if (vertices != nullptr) {
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, vertices);  // number of coordinates per vertex, type of each coordinate, stride, pointer 
    if (colors != nullptr) {
      glEnableClientState(GL_COLOR_ARRAY);
      glColorPointer(4, GL_DOUBLE, 0, colors);   // number of coordinates per color, type of each coordinate, stride, pointer 
    }
	
    glDrawArrays(primitive, 0, numVertices);   // primitive graphic, first index and number of elements to be rendered

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
  }
}
//-------------------------------------------------------------------------

Mesh * Mesh::createRGBAxes(GLdouble l)
{
  Mesh* m = new Mesh();
  m->primitive = GL_LINES;
  m->numVertices = 6;

  m->vertices = new dvec3[m->numVertices];
  // X axis vertices
  m->vertices[0] = dvec3(0.0, 0.0, 0.0);   
  m->vertices[1] = dvec3(l, 0.0, 0);
  // Y axis vertices
  m->vertices[2] = dvec3(0, 0.0, 0.0);
  m->vertices[3] = dvec3(0.0, l, 0.0); 
  // Z axis vertices
  m->vertices[4] = dvec3(0.0, 0.0, 0.0);
  m->vertices[5] = dvec3(0.0, 0.0, l);

  m->colors = new dvec4[m->numVertices];
  // X axis color: red  ( Alpha = 1 : fully opaque)
  m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
  m->colors[1] = dvec4(1.0, 0.0, 0.0, 1.0);
  // Y axis color: green
  m->colors[2] = dvec4(0.0, 1.0, 0.0, 1.0);
  m->colors[3] = dvec4(0.0, 1.0, 0.0, 1.0);
  // Z axis color: blue
  m->colors[4] = dvec4(0.0, 0.0, 1.0, 1.0);
  m->colors[5] = dvec4(0.0, 0.0, 1.0, 1.0);
 
  return m; 
}
//-------------------------------------------------------------------------
Mesh * Mesh::generaPoliespiral(dvec2 verIni, GLdouble angIni, GLdouble
	incrAng, GLdouble ladoIni, GLdouble incrLado, GLuint numVert)
{
	Mesh* m2 = new Mesh();
	m2->primitive = GL_LINE_STRIP;
	m2->numVertices = numVert;

	m2->vertices = new dvec3[m2->numVertices];

	double x = verIni.x;
	double y = verIni.y;

	for (int i = 0; i < m2->numVertices; i++)
	{
		m2->vertices[i] = dvec3(x, y, 0.0);

		x = x + ladoIni * cos(radians(angIni));
		y = y + ladoIni * sin(radians(angIni));
		ladoIni += incrLado;
		angIni += incrAng;
	}

	return m2;
}

//-------------------------------------------------------------------------
Mesh * Mesh::generaDragon(GLuint numVert)
{
	Mesh* m = new Mesh();
	m->primitive = GL_POINTS;
	m->numVertices = numVert;

	m->vertices = new dvec3[m->numVertices];

	double pr1 = 0.787473;
	double pr2 = 1 - pr1;
	double x = 0;
	double y = 0;

	for (int i = 0; i < m->numVertices; i++)
	{
		m->vertices[i] = dvec3(x, y, 0.0);
		double azar = rand() / double(RAND_MAX);
		double aux = x;
		if (azar < pr1) {
			x = 0.824074 * x + 0.281482 * y - 0.882290;
			y = -0.212346 * aux + 0.864198 * y - 0.110607;
		} // T1
		else {
			x = 0.088272 * x + 0.520988 * y + 0.785360;
			y = -0.463889 * aux - 0.377778 * y + 8.095795;
		} // T2
	}

	return m;
}

Mesh * Mesh::generaTriangulo(GLdouble r)
{
	Mesh* m = new Mesh();
	m->primitive = GL_TRIANGLES;
	m->numVertices = 3;

	m->vertices = new dvec3[m->numVertices];

	double angIni = 90;
	double x = 0;
	double y = 0;

//	centro C = (0, 0) y radio R = r:
	for (int i = 0; i < 3; i++)
	{
		

		x = r * cos(radians(angIni));
		y = r * sin(radians(angIni));
		m->vertices[i] = dvec3(x, y, 0.0);
		angIni += 120;
	}

	return m;
}

//Mesh * Mesh::generaTrianguloRGB(GLdouble r)
//{
//	Mesh* m = new Mesh();
//	m->primitive = GL_TRIANGLES;
//	m->numVertices = 3;
//
//	Mesh * m = generaTriangulo(r);
//
//	return m;
//}