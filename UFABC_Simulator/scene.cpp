#include "scene.h"

Scene::Scene()
{
	numObjects = 2;
	object = new Object[numObjects];
}

Scene::~Scene()
{
	delete [] object;
}

void Scene::drawScene(Camera camera, Light light, float zoom, float camX, float camY, float camZ, QQuaternion rotation)
{
	for(int i=0; i<numObjects; i++)
		object[i].drawObject(camera, light, zoom, camX, camY, camZ, rotation);
}

void Scene::addObject(unsigned int id)
{
	//object[id] = new Object;
	if(id==0)
		object[id].loadObject("./Objects/ufabc.off");
	else
		object[id].loadObject("./Objects/camel.off");
}

void Scene::updateAspectRatio(int w, int h)
{
	for(int i=0; i<numObjects; i++)
		object[i].updateAspectRatio(w, h);
}
