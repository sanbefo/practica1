#include "Scene.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

//-------------------------------------------------------------------------

void Scene::init()
{ // OpenGL basic setting
  glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)
  glEnable(GL_DEPTH_TEST);  // enable Depth test 
  glEnable(GL_TEXTURE_2D);
     
  // lights
  // textures  
  // meshes

  // Graphics objects (entities) of the scene
    grObjects.push_back(new EjesRGB(200.0));
  //  grObjects.push_back(new Poliespiral(glm::dvec2(0, 0), 0, 160, 1, 10, 50));
//  grObjects.push_back(new Dragon(3000));
//  grObjects.push_back(new Triangulo(40));
//  grObjects.push_back(new Rectangulo(300, 250));
  grObjects.push_back(new Suelo(500, 500, 30, 30));
  grObjects.push_back(new Estrella3D(100, 6, 100));  // dvec3(0, 150, 0)
  //grObjects.push_back(new Caja(100));
}

void Scene::update()
{
	for (Entity* el : grObjects)
	{
		el->update();
	}
}

void Scene::escena2D()
{
	grObjects.clear();
	glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);  // enable Depth test 
	grObjects.push_back(new EjesRGB(200.0));
	grObjects.push_back(new Dragon(3000));
	grObjects.push_back(new Triangulo(100));
	grObjects.push_back(new Rectangulo(80, 100));
}

void Scene::escena3D()
{
	grObjects.clear();
	glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);  // enable Depth test 
	grObjects.push_back(new EjesRGB(200.0));
	grObjects.push_back(new Suelo(500, 500));
	grObjects.push_back(new Estrella3D(100, 6, 100));  // dvec3(0, 150, 0)
	grObjects.push_back(new Caja(100));
}
//-------------------------------------------------------------------------

Scene::~Scene()
{ // free memory and resources   
  
  for (Entity* el: grObjects)
  {
	  delete el;  el = nullptr;
  }
}
//-------------------------------------------------------------------------

void Scene::render(Camera const& cam)
{
	for (Entity* el: grObjects)
	{
		el->render(cam);
	}
}
//-------------------------------------------------------------------------
