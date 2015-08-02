#ifndef MOUSE_H
#define MOUSE_H

#include <QVector3D>
#include <QQuaternion>
#include <QTime>
#include <QWidget>

#include <cmath>
#include <math.h>

class Mouse : public QWidget
{
public:
	Mouse();

	bool mouseMove(const QPointF& p);
	void mousePress(const QPointF& p);
	void mouseRelease(const QPointF& p);

	void resizeViewport(int width, int height);

	QVector3D axis;
	double velocity;
	double angle;

	QVector3D lastPos3D;
	QTime lastTime;
	bool trackingMouse;
	bool persistence;

	double viewportWidth;
	double viewportHeight;

	const double rad2deg;

	QVector3D mousePosTo3D(const QPointF& p);
};

#endif // MOUSE_H
