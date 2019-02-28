#include "Scene.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

//-------------------------------------------------------------------------

void Scene::init()
{ // OpenGL basic setting
  glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)
  glEnable(GL_DEPTH_TEST);  // enable Depth test 
     
  // lights
  // textures  
  // meshes

  // Graphics objects (entities) of the scene
  //  grObjects.push_back(new EjesRGB(200.0));
  //  grObjects.push_back(new Poliespiral(glm::dvec2(0, 0), 0, 160, 1, 10, 50));
//  grObjects.push_back(new Dragon(3000));
//  grObjects.push_back(new Triangulo(40));
//  grObjects.push_back(new Rectangulo(100, 60));
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