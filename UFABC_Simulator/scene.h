#ifndef SCENE_H
#define SCENE_H

#include "object.h"

class Scene
{
	public:
		Scene();
		~Scene();

		void drawScene(Camera, Light, float, QQuaternion);
		unsigned int addObject(QString);
		void updateAspectRatio(int, int);
		Object& fetchObject(unsigned int);

	private:
		unsigned int numObjects;
		unsigned int index;
		Object *object;
};

#endif // SCENE_H
