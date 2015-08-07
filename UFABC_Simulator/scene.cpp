#include "scene.h"

Scene::Scene()
{
	numObjects = 100;
	objectList.reserve(100);
}

Scene::~Scene()
{
	//delete [] object;
}

bool Scene::isInitialized()
{
	return !objectList.isEmpty();
}

void Scene::drawScene(Camera camera, Light light)
{
	for(unsigned int i=0; i<objectList.size(); i++)
		objectList[i]->drawObject(camera, light);
}

void Scene::addTerrain(QString name, int w, int h)
{
	objectList.append(new Object);
	objectList.last()->lockObject();
	objectList.last()->loadObject(name);
	objectList.last()->updateAspectRatio(w, h);
}

void Scene::addAmbient(QString name, int w, int h)
{
	objectList.append(new Object);
	objectList.last()->lockObject();
	objectList.last()->loadObject(name);
	objectList.last()->updateAspectRatio(w, h);
}

void Scene::addObject(QString name, int w, int h)
{
	objectList.append(new Object);
	objectList.last()->loadObject(name);
	objectList.last()->updateAspectRatio(w, h);
}

void Scene::removeLastObject()
{
	objectList.removeLast();
}

void Scene::updateAspectRatio(int w, int h)
{
	for(unsigned int i=0; i<objectList.size(); i++)
		objectList[i]->updateAspectRatio(w, h);
}

Object& Scene::fetchObject(unsigned int id)
{
	return *objectList[id];
}

Object& Scene::fetchCurrentObject()
{
	return *objectList.last();
}

bool Scene::isPlacingObject()
{
	if(objectList.last()->lockState()==2)
		return false;
	return true;
}
