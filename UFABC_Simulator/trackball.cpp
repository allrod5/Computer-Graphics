#include "trackball.h"
TrackBall::TrackBall()
{

}

void TrackBall::updateRotation(Mouse &mouse)
{
	if (mouse.trackingMouse)
		return;

    QTime currentTime = QTime::currentTime();
	mouse.angle = mouse.velocity * mouse.lastTime.msecsTo(currentTime);
	rotation = QQuaternion::fromAxisAndAngle(mouse.axis, mouse.angle) * rotation;
	return;
}

void TrackBall::mouseMove(Mouse &mouse)
{
	rotation = QQuaternion::fromAxisAndAngle(mouse.axis, mouse.angle) * rotation;
}
