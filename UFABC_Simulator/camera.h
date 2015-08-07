# ifndef CAMERA_H
# define CAMERA_H
# include <QVector3D>
# include <QKeyEvent>
# include <fstream>
# include <limits>
# include <iostream>

#include <QQuaternion>
#include <QTime>

#include <cmath>
#include <math.h>

#include "mouse.h"

class Camera
{
public :
    Camera ();
    QVector3D eye;
    QVector3D at;
    QVector3D up;

	void updateRotation(Mouse&);
	void mouseMove(Mouse&);
	void move(Mouse&, const QPointF&);
	void enableMovimentation(bool);
	bool isMoving();
	void setZoom(double);
	void updateZoom(double);
	QQuaternion& getRotation();

//private :
	double maxZoom;
	double minZoom;
	double minHeight;
	double maxHeight;
	QQuaternion rotation;
	bool moving;
	double lastAngle;
	double lastHeight;
	double zoom;
	double xyZoom;
	const double rad2deg;
};
# endif // CAMERA_H
