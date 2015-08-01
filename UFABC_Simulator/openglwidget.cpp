#include "openglwidget.h"

OpenGLWidget::OpenGLWidget(QWidget* parent): QOpenGLWidget(parent) {
	angx = angy = angz = 0;
	tx = ty = tz = 0;
	sc = 1;
	zoom = 1;
	camX = camY = camZ = 0;

	scene = new Scene;
}

OpenGLWidget::~OpenGLWidget() {

}

void OpenGLWidget::initializeGL() {
	initializeOpenGLFunctions();

	std::cerr << "Version " << glGetString(GL_VERSION)<< "\n";
	std::cerr << "GLSL " << glGetString(GL_SHADING_LANGUAGE_VERSION)<<"\n";
	glEnable(GL_DEPTH_TEST);

	connect(&timer, SIGNAL(timeout()), this, SLOT(animate()));
	timer.start(25);
}

void OpenGLWidget::resizeGL(int w,int h) {
	glViewport(0, 0, w, h);
	scene->updateAspectRatio(w, h);
	//trackBall.resizeViewport(w, h);
	mouse.resizeViewport(w, h);
	update();
}

void OpenGLWidget::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene->drawScene(camera, light, zoom, camX, camY, camZ, trackBall.rotation);
	update();
}

void OpenGLWidget::animate() {
	update();
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent * event) {
	//trackBall.mouseMove(event->localPos());
	if(mouse.mouseMove(event->localPos()))
		trackBall.mouseMove(mouse);
}

void OpenGLWidget::mousePressEvent(QMouseEvent * event) {
	mouse.mousePress(event->localPos());
	if(event->button()& Qt::LeftButton) {
		//trackBall.mousePress(event->localPos());
		trackBall.updateRotation(mouse);
	} else if(event->button()& Qt::RightButton) {
		scene->addObject("ufabc_blocoA");
	} else if(event->button()& Qt::MiddleButton) {
		scene->fetchObject(1).moveObject(mouse, event->localPos());
	}
}

void OpenGLWidget::wheelEvent(QWheelEvent * event) {
    zoom += 0.001*event->delta();
	if(zoom<1)
		zoom = 1;
	else if(zoom>5)
		zoom = 5;
}

void OpenGLWidget::mouseReleaseEvent(QMouseEvent * event) {
	if(event->button()== Qt::LeftButton)
		mouse.mouseRelease(event->localPos());
		//trackBall.mouseRelease(event->localPos());
}

void OpenGLWidget::keyPressEvent(QKeyEvent * event) {
	if(event->text()=="w")
		camZ += 0.01;
	else if(event->text()=="s")
		camZ -= 0.01;
	else if(event->text()=="a")
		camX += 0.01;
	else if(event->text()=="d")
		camX -= 0.01;
	else if(event->text()=="i")
		camY -= 0.01;
	else if(event->text()=="k")
		camY += 0.01;
	else if(event->text()=="t")
		scene->fetchObject(1).moveObject(0.15,0,0);
	else if(event->text()=="g")
		scene->fetchObject(1).moveObject(-0.15,0,0);
	else if(event->text()=="f")
		scene->fetchObject(1).moveObject(0,0,0.15);
	else if(event->text()=="h")
		scene->fetchObject(1).moveObject(0,0,-0.15);
}

void OpenGLWidget::newGame()
{
	scene->addObject("terrain");
}
