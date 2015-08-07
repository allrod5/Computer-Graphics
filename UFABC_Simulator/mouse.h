#ifndef MOUSE_H
#define MOUSE_H

#include <QVector3D>
#include <QQuaternion>
#include <QTime>
#include <QWidget>
#include <QVector2D>

#include <cmath>
#include <math.h>

class Mouse : public QWidget
{
public:
	Mouse();

	void mouseMove(const QPointF& p);
	void mousePress(const QPointF& p);
	void mouseRelease(const QPointF& p);

	void resizeViewport(int width, int height);

	double velocity;
	QVector2D vector;
	QVector2D lastPos;
	QTime lastTime;

	bool trackingMouse;
	bool persistence;

	double viewportWidth;
	double viewportHeight;
};

#endif // MOUSE_H
