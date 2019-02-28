#include "Entity.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

//-------------------------------------------------------------------------

void Entity::uploadMvM(dmat4 const& modelViewMat) const
{ 
	dmat4 aMat = modelViewMat * modelMat;
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(aMat));
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

EjesRGB::EjesRGB(GLdouble l): Entity() 
{
  mesh = Mesh::createRGBAxes(l);
}

Poliespiral::Poliespiral(glm::dvec2 verIni, GLdouble angIni, GLdouble incrAng, GLdouble ladoIni, GLdouble incrLado, GLuint numVert) : Entity()
{
	mesh = Mesh::generaPoliespiral(verIni, angIni, incrAng, ladoIni, incrLado, numVert);
}

Dragon::Dragon(GLuint numVert) : Entity()
{
	mesh = Mesh::generaDragon(numVert);
}

Triangulo::Triangulo(GLdouble r) : Entity()
{
	mesh = Mesh::generaTrianguloRGB(r);
}

Rectangulo::Rectangulo(GLdouble w, GLdouble h) : Entity()
{
	mesh = Mesh::generaRectanguloRGB(w, h);
}

Estrella3D::Estrella3D(GLdouble re, GLdouble np, GLdouble h) : Entity()  // dvec3 pos
{
	mesh = Mesh::generaEstrella3D(re, np, h);

	modelMat = translate(modelMat, dvec3(0, 100, 0));
}

Caja::Caja(GLdouble l) : Entity()
{
	mesh = Mesh::generaContCubo(l);
}
//-------------------------------------------------------------------------

EjesRGB::~EjesRGB() 
{ 
	delete mesh; mesh = nullptr; 
};

Poliespiral::~Poliespiral()
{
	delete mesh; mesh = nullptr;
};

Dragon::~Dragon()
{
	delete mesh; mesh = nullptr;
};

Triangulo::~Triangulo()
{
	delete mesh; mesh = nullptr;
};

Rectangulo::~Rectangulo()
{
	delete mesh; mesh = nullptr;
};

Estrella3D::~Estrella3D()
{
	delete mesh; mesh = nullptr;
};

Caja::~Caja()
{
	delete mesh; mesh = nullptr;
};
//-------------------------------------------------------------------------

void EjesRGB::render(Camera const& cam)
{
	if (mesh != nullptr) {
		uploadMvM(cam.getViewMat()); 
		glLineWidth(2);
		mesh->render();
		glLineWidth(1);
	}
}

//-------------------------------------------------------------------------
void Poliespiral::render(Camera const& cam)
{
	if (mesh != nullptr) {
		uploadMvM(cam.getViewMat());
		glLineWidth(2);
		glColor3d(0, 0, 1);
		mesh->render();
		glLineWidth(1);
		glColor3d(1, 1, 1);
	}
}
//-------------------------------------------------------------------------
void Dragon::render(Camera const& cam)
{
	if (mesh != nullptr) {

		dmat4 matAux = cam.getViewMat();
//		matAux = scale(matAux, dvec3(-40, -170, 0));
		uploadMvM(matAux);
		glLineWidth(2);
		glColor3d(0, 0, 1);
		glPointSize(2);
		mesh->render();
		glLineWidth(1);
		glColor3d(1, 1, 1);
		glPointSize(1);
	}
}

void Triangulo::render(Camera const& cam)
{
	if (mesh != nullptr) {
		uploadMvM(cam.getViewMat());
		//glPolygonMode(GL_BACK, GL_LINE);
		//glPolygonMode(GL_BACK, GL_POINT);
//		glColor3d(0, 0, 1);
		mesh->render();
		/*glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);*/
	}
}

void Rectangulo::render(Camera const& cam)
{
	if (mesh != nullptr) {
		dmat4 mat = modelMat;
		modelMat = mat;
		modelMat = rotate(mat, radians(90.0), dvec3(1, 0, 0));
		uploadMvM(cam.getViewMat());
		glColor3d(0, 0, 1);
		modelMat = mat;
		mesh->render();
	}
}

void Estrella3D::render(Camera const& cam)
{
	if (mesh != nullptr) {
		dmat4 mat = modelMat;
		uploadMvM(cam.getViewMat());
		glLineWidth(2);
		glColor3d(1, 0, 0);
		mesh->render();
		modelMat = rotate(mat, radians(180.0), dvec3(1, 0, 0));
		uploadMvM(cam.getViewMat());
		mesh->render();
		glLineWidth(2);
		glColor3d(0, 1, 1);
		modelMat = mat;
		mesh->render();
	}
}

void Caja::render(Camera const& cam)
{
	if (mesh != nullptr) {
		dmat4 mat = modelMat;
		modelMat = translate(mat, dvec3(0, 50, 0));
		uploadMvM(cam.getViewMat());
		glLineWidth(2);
		glColor3d(1, 0, 1);
		mesh->render();
		modelMat = mat;
		glLineWidth(1);
		glColor3d(0, 0, 1);
	}
}