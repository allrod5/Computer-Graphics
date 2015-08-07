
#ifndef TRACKBALL_H
#define TRACKBALL_H

#include <QVector3D>
#include <QQuaternion>
#include <QTime>

#include <cmath>
#include <math.h>

//#include <mouse.h>

//class Mouse;

class TrackBall
{
public:
    TrackBall();

	/*void updateRotation(Mouse&);
	void mouseMove(Mouse&);*/

	QQuaternion rotation;

private:
	//Mouse mouse;
};

#endif
