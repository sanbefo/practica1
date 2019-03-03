#include "Mesh.h"

using namespace glm;

//-------------------------------------------------------------------------

Mesh ::~Mesh(void) 
{
  delete[] vertices;  vertices = nullptr;
  delete[] colors;    colors = nullptr;
  delete[] textures;    textures = nullptr;
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
	if (textures != nullptr) {
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_DOUBLE, 0, textures);
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

Mesh * Mesh::generaTrianguloRGB(GLdouble r)
{
	Mesh * m = generaTriangulo(r);

	m->colors = new dvec4[m->numVertices];
	m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
	m->colors[1] = dvec4(0.0, 1.0, 0.0, 1.0);
	m->colors[2] = dvec4(0.0, 0.0, 1.0, 1.0);

	return m;
}

Mesh * Mesh::generaTrianguloAnimado(GLdouble r)
{
	Mesh * m = generaTriangulo(r);
	m->colors = new dvec4[m->numVertices];
	m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
	m->colors[1] = dvec4(1.0, 0.0, 0.0, 1.0);
	m->colors[2] = dvec4(1.0, 0.0, 0.0, 1.0);

	return m;
}

Mesh * Mesh::generaRectangulo(GLdouble w, GLdouble h)
{
	Mesh* m = new Mesh();
	m->primitive = GL_TRIANGLE_STRIP;
	m->numVertices = 4;

	m->vertices = new dvec3[m->numVertices];

	m->vertices[0] = dvec3(0.0, h, 0.0);
	m->vertices[1] = dvec3(w, h, 0.0);
	m->vertices[2] = dvec3(0.0, 0.0, 0.0);
	m->vertices[3] = dvec3(w, 0.0, 0.0);

	return m;
}

Mesh * Mesh::generaRectanguloTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh)
{
	Mesh *m = generaSuelo(w, h);
	m->textures = new dvec2[m->numVertices];
	m->textures[0] = dvec2(0, rh);
	m->textures[1] = dvec2(0, 0);
	m->textures[2] = dvec2(rw, rh);
	m->textures[3] = dvec2(rw, 0);

	return m;
}

Mesh * Mesh::generaSuelo(GLdouble w, GLdouble h)
{
	Mesh* m = new Mesh();
	m->primitive = GL_TRIANGLE_STRIP;
	m->numVertices = 4;

	m->vertices = new dvec3[m->numVertices];

	m->vertices[0] = dvec3(0.0, 0.0, h);
	m->vertices[1] = dvec3(w, 0.0, h);
	m->vertices[2] = dvec3(0.0, 0.0, 0.0);
	m->vertices[3] = dvec3(w, 0.0, 0.0);

	return m;
}

Mesh * Mesh::generaRectanguloRGB(GLdouble w, GLdouble h)
{
	Mesh * m = generaRectangulo(w, h);

	m->colors = new dvec4[m->numVertices];
	m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
	m->colors[1] = dvec4(0.0, 1.0, 0.0, 1.0);
	m->colors[2] = dvec4(0.0, 0.0, 1.0, 1.0);
	m->colors[3] = dvec4(0.0, 0.0, 0.0, 1.0);

	return m;
}

Mesh * Mesh::generaEstrella3D(GLdouble re, GLdouble np, GLdouble h)
{
	Mesh* m = new Mesh();
	m->primitive = GL_TRIANGLE_FAN;
	m->numVertices = 2 * np + 2;

	m->vertices = new dvec3[m->numVertices];
	double x = 30;
	double y = 30;
	double ang = 0;

	m->vertices[0] = dvec3(0.0, 0.0, 0.0);
	
	for (int i = 1; i < m->numVertices - 1; i++)
	{
		double z = 1;
		if (i % 2 == 0)
			z = 2;
		x = (re / z) * cos(radians(ang));
		y = (re / z) * sin(radians(ang));
		m->vertices[i] = dvec3(x, y, h);
		ang += 360 / (m->numVertices - 2);
	}
	m->vertices[m->numVertices - 1] = m->vertices[1];

	return m;
}

Mesh * Mesh::generaEstrellaTexCor(GLdouble r, GLdouble nL, GLdouble h)
{
	Mesh *m = generaEstrella3D(r, nL, h);
	m->numVertices = 2 * nL + 2;
	m->textures = new dvec2[m->numVertices];
	double x = 30;
	double y = 30;
	double ang = 0;

	m->textures[0] = dvec2(0.0, 0.0);

	for (int i = 1; i < m->numVertices - 1; i++)
	{
		double z = 0.5;
		if (i % 2 == 0)
			z = 0.25;
		x = z * cos(radians(ang));
		y = z * sin(radians(ang));
		m->textures[i] = dvec2(x, y);
		ang += 360 / (m->numVertices - 2);
	}
	m->textures[m->numVertices - 1] = m->textures[1];

	return m;
}

Mesh * Mesh::generaContCubo(GLdouble l)
{
	Mesh* m = new Mesh();
	m->primitive = GL_TRIANGLE_STRIP;
	m->numVertices = 10;

	m->vertices = new dvec3[m->numVertices];
	double x = l / 2;

	m->vertices[0] = dvec3(-x, x, -x);
	m->vertices[1] = dvec3(-x, -x, -x); 
	m->vertices[2] = dvec3(-x, x, x);
	m->vertices[3] = dvec3(-x, -x, x);
	m->vertices[4] = dvec3(x, x, x);
	m->vertices[5] = dvec3(x, -x, x);
	m->vertices[6] = dvec3(x, x, -x);
	m->vertices[7] = dvec3(x, -x,-x);
	m->vertices[8] = m->vertices[0];
	m->vertices[9] = m->vertices[1];

	return m;
}

Mesh * Mesh::generaCajaTexCor(GLdouble l)
{
	Mesh *m = generaContCubo(l);

	m->textures = new dvec2[m->numVertices];
	double x = 1;
	m->textures[0] = dvec2(0, 0);
	m->textures[1] = dvec2(1, 0);
	m->textures[2] = dvec2(0, 1);
	m->textures[3] = dvec2(1, 1);
	m->textures[4] = dvec2(0, 0);
	m->textures[5] = dvec2(1, 0);
	m->textures[6] = dvec2(0, 1);
	m->textures[7] = dvec2(1, 1);
	m->textures[8] = m->textures[0];
	m->textures[9] = m->textures[1];
	return m;
}
