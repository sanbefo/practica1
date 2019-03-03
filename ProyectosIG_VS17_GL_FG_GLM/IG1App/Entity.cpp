#include "Entity.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

//-------------------------------------------------------------------------

void Entity::update()
{
}

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
	mesh = Mesh::generaTrianguloAnimado(r);
}

Rectangulo::Rectangulo(GLdouble w, GLdouble h) : Entity()
{
	mesh = Mesh::generaRectanguloRGB(w, h);
}

Suelo::Suelo(GLdouble w, GLdouble h) : Entity()
{
	mesh = Mesh::generaSuelo(w, h);
}

Suelo::Suelo(GLdouble w, GLdouble h, GLuint rw, GLuint rh) : Entity()
{
	mesh = Mesh::generaRectanguloTexCor(w, h, rw, rh);
	textura.load("..\\Bmps\\baldosaC.bmp");
}

//Estrella3D::Estrella3D(GLdouble re, GLdouble np, GLdouble h) : Entity()  // dvec3 pos
//{
//	mesh = Mesh::generaEstrella3D(re, np, h);
//	modelMat = translate(modelMat, dvec3(0, 100, 0));
//}

Estrella3D::Estrella3D(GLdouble r, GLdouble nL, GLdouble h) : Entity()
{
	mesh = Mesh::generaEstrellaTexCor(r, nL, h);
	modelMat = translate(modelMat, dvec3(0, 100, 0));
	textura.load("..\\Bmps\\baldosaP.bmp");
}

Caja::Caja(GLdouble l) : Entity()
{
	mesh = Mesh::generaCajaTexCor(l);
	textura.load("..\\Bmps\\container.bmp");
	texturaInner.load("..\\Bmps\\papelE.bmp");
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

Suelo::~Suelo()
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
		matAux = scale(matAux, dvec3(40, 40, 0));
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
		dmat4 mat = modelMat;
		double x = 100 * cos(radians(anguloTraslada));
		double y = 100 * sin(radians(anguloTraslada));
		modelMat = translate(modelMat, dvec3(x, y, 0));
		uploadMvM(cam.getViewMat());
		modelMat = rotate(modelMat, radians(anguloRota), dvec3(0, 0, 1));
		uploadMvM(cam.getViewMat());
		mesh->render();
		modelMat = mat;
	}
}

void Triangulo::update()
{
	anguloRota += 3;
	anguloTraslada += 3;
}

void Rectangulo::render(Camera const& cam)
{
	if (mesh != nullptr) {
		uploadMvM(cam.getViewMat());
		glColor3d(0, 0, 1);
		mesh->render();
	}
}

void Suelo::render(Camera const& cam)
{
	if (mesh != nullptr) {
		uploadMvM(cam.getViewMat());
		textura.bind();
		mesh->render();
		textura.unbind();
	}
}

void Estrella3D::render(Camera const& cam)
{
	if (mesh != nullptr) {
		dmat4 mat = modelMat;
		modelMat = translate(mat, dvec3(0, 100, 0));

		modelMat = rotate(modelMat, radians(anguloRota), dvec3(0, 1, 0));
		modelMat = rotate(modelMat, radians(anguloRota), dvec3(0, 0, 1));
		uploadMvM(cam.getViewMat());
		glLineWidth(1);
		textura.bind();
		mesh->render();
		modelMat = rotate(modelMat, radians(180.0), dvec3(1, 0, 0));
		uploadMvM(cam.getViewMat());
		mesh->render();
		glLineWidth(1);
		mesh->render();
		modelMat = mat;
		textura.unbind();
	}
}

void Estrella3D::update()
{
	anguloRota++;
}

void Caja::render(Camera const& cam)
{
	if (mesh != nullptr) {
		dmat4 mat = modelMat;
		modelMat = translate(mat, dvec3(0, 50, 0));
		uploadMvM(cam.getViewMat());
		glLineWidth(2);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		textura.bind();
		mesh->render();
		textura.unbind();
		glDisable(GL_CULL_FACE);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		texturaInner.bind();
		mesh->render();
		modelMat = mat;
		glLineWidth(1);
		texturaInner.unbind();
		glDisable(GL_CULL_FACE);
	}
}

//glCullFace(GL_FRONT / GL_BACK);
