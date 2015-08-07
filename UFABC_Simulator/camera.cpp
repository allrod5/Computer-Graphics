#include "camera.h"
Camera :: Camera () :  rad2deg(180.0 /3.1415)
{
	eye = QVector3D (1.0 , 0.5 , 0.0) ;
	at = QVector3D (0.0 , 0.0 , 0.0) ;
	up = QVector3D (0.0 , 1.0 , 0.0) ;
	moving = false;
	zoom = 1.0;
	xyZoom = 0.9;
	lastAngle = 0;
	lastHeight = 0.5;
	minZoom = 0.5;
	maxZoom = 2.0;
	minHeight = 0.0;
	maxHeight = 2.0;
}

void Camera::updateRotation(Mouse &mouse)
{
	/*if (mouse.trackingMouse)
		return;

	QTime currentTime = QTime::currentTime();
	mouse.angle = mouse.velocity * mouse.lastTime.msecsTo(currentTime);
	rotation = QQuaternion::fromAxisAndAngle(mouse.axis, mouse.angle) * rotation;

	return;*/
}

void Camera::mouseMove(Mouse &mouse)
{
	QVector2D* v = &mouse.vector;
	if(moving) {

		float newHeight = eye.y()+zoom*v->y();
		if(newHeight>maxHeight)
			newHeight = maxHeight;
		else if(newHeight<minHeight)
			newHeight = minHeight;


		eye.setY(newHeight);

		float s = sin(v->x()+lastAngle);
		float c = cos(v->x()+lastAngle);

		lastAngle += v->x();

		eye.setX(at.x() + zoom*s);
		eye.setZ(at.y() + zoom*c);

	}
}

void Camera::move(Mouse &mouse, const QPointF& p)
{
	/*if(p.x() <= 2) {
		eye.setX(eye.x()-sin(lastAngle)*0.1);
		at.setX(at.x()-sin(lastAngle)*0.1);
		eye.setZ(eye.z()-cos(lastAngle)*0.1);
		at.setZ(at.z()-cos(lastAngle)*0.1);
	} else if(p.x() >= mouse.viewportWidth-2) {
		eye.setX(eye.x()+sin(lastAngle)*0.1);
		at.setX(at.x()+sin(lastAngle)*0.1);
		eye.setZ(eye.z()+cos(lastAngle)*0.1);
		at.setZ(at.z()+cos(lastAngle)*0.1);
	}

	if(p.y() <= 1) {

	} else if(p.y() >= mouse.viewportHeight) {

	}*/
}

void Camera::enableMovimentation(bool flag)
{
	moving = flag;
}

bool Camera::isMoving()
{
	return moving;
}

void Camera::setZoom(double zoom)
{
	this->zoom = zoom;
	if(zoom < minZoom)
		zoom = minZoom;
	else if(zoom > maxZoom)
		zoom = maxZoom;
}

void Camera::updateZoom(double delta)
{
	zoom -= delta;
	if(zoom < minZoom)
		zoom = minZoom;
	else if(zoom > maxZoom)
		zoom = maxZoom;
	eye.setX(at.x() + zoom*sin(lastAngle));
	eye.setZ(at.y() + zoom*cos(lastAngle));
	//eye.setY(eye.y()-lastHeight);
}

/*QQuaternion& Camera::getRotation()
{
	return rotation;
}*/
