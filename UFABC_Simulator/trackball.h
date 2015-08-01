
#ifndef TRACKBALL_H
#define TRACKBALL_H

#include <QVector3D>
#include <QQuaternion>
#include <QTime>

#include <cmath>
#include <math.h>

#include <mouse.h>

class Mouse;

class TrackBall
{
public:
    TrackBall();
	/*void mouseMove(const QPointF& p);
    void mousePress(const QPointF& p);
	void mouseRelease(const QPointF& p);

	void resizeViewport(int width, int height);*/
	void updateRotation(Mouse&);

	void mouseMove(Mouse&);

	QQuaternion rotation;
private:

	/*QVector3D axis;
    double velocity;

    QVector3D lastPos3D;
    QTime lastTime;
	bool trackingMouse;

    double viewportWidth;
    double viewportHeight;

	const double rad2deg;

	QVector3D mousePosTo3D(const QPointF& p);*/

	Mouse mouse;
};

#endif
