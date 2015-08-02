#include "scene.h"

Scene::Scene()
{
	numObjects = 100;
	index = 0;
	object = new Object[numObjects];
}

Scene::~Scene()
{
	delete [] object;
}

void Scene::drawScene(Camera camera, Light light, float zoom, QQuaternion rotation)
{
	for(unsigned int i=0; i<index; i++)
		object[i].drawObject(camera, light, zoom, rotation);
}

unsigned int Scene::addObject(QString name)
{
	Object *obj = &object[index];
	obj->loadObject(name);
	return index++;
}

void Scene::updateAspectRatio(int w, int h)
{
	for(unsigned int i=0; i<numObjects; i++)
		object[i].updateAspectRatio(w, h);
}

Object& Scene::fetchObject(unsigned int id)
{
	return object[id];
}
