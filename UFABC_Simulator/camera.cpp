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
		/*if(newHeight>zoom)
			newHeight = zoom;
		float h = sqrt(1 - pow(newHeight,2));*/

		eye.setY(newHeight);

		/*zoom *= h;*/

		float s = sin(v->x()+lastAngle);
		float c = cos(v->x()+lastAngle);

		lastAngle += v->x();

		eye.setX(at.x() + zoom*s);
		eye.setZ(at.y() + zoom*c);


		//std::cerr << new_angle << " vs. " << asin(s) << "\n";

	}
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
