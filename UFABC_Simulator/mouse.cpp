#include "mouse.h"

Mouse::Mouse()
{
	velocity = 0.0;
	trackingMouse = false;
	persistence = false;
	lastTime = QTime::currentTime();
}

void Mouse::mouseMove(const QPointF &p)
{
	if (!trackingMouse)
		return;

	QTime currentTime = QTime::currentTime();
	int msecs = lastTime.msecsTo(currentTime);
	if (msecs) {
		vector = QVector2D(p.x()/viewportWidth, p.y()/viewportHeight)-lastPos;
		velocity = vector.length() / msecs;
		lastPos = QVector2D(p.x()/viewportWidth, p.y()/viewportHeight);
		lastTime = currentTime;
	}
}

void Mouse::mousePress(const QPointF &p)
{
	trackingMouse = true;
	lastTime = QTime::currentTime();
	lastPos = QVector2D(p.x()/viewportWidth, p.y()/viewportHeight);
	velocity = 0.0;
}

void Mouse::mouseRelease(const QPointF &p)
{
	mouseMove(p);
	if(!persistence)
		trackingMouse = false;
}

void Mouse::resizeViewport(int width, int height)
{
	viewportWidth = static_cast<double>(width);
	viewportHeight = static_cast<double>(height);
}
