#ifndef SCENE_H
#define SCENE_H

#include "object.h"

class Object;

class Scene
{
	public:
		Scene();
		~Scene();

		void drawScene(Camera, Light, float, float, float, float, QQuaternion);
		void addObject(QString);
		void updateAspectRatio(int, int);
		Object& fetchObject(unsigned int);

	private:
		unsigned int numObjects;
		unsigned int index;
		Object *object;
};

#endif // SCENE_H
