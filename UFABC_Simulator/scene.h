#ifndef SCENE_H
#define SCENE_H

#include "object.h"
#include <vector>

class Scene
{
	public:
		Scene();
		~Scene();

		void drawScene(Camera, Light);
		void addObject(QString, int, int);
		void removeLastObject();
		void addTerrain(QString, int, int);
		void addAmbient(QString, int, int);
		void updateAspectRatio(int, int);
		Object& fetchObject(unsigned int);
		Object& fetchCurrentObject();
		bool isPlacingObject();

	private:
		unsigned int numObjects;
		QList<Object*> objectList;
};

#endif // SCENE_H
