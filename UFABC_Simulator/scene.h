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
		void addObject(unsigned int);

	private:
		unsigned int numObjects;
		Object *object;
};

#endif // SCENE_H
