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
	delete scene;
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
	mouse.resizeViewport(w, h);
	update();
}

void OpenGLWidget::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene->drawScene(camera, light, zoom, trackBall.rotation);
	update();
}

void OpenGLWidget::animate() {
	update();
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent * event) {
	if(mouse.mouseMove(event->localPos())) {
		trackBall.mouseMove(mouse);
		scene->fetchObject(currentObject).mouseMove(mouse);
	}
}

void OpenGLWidget::mousePressEvent(QMouseEvent * event) {
	mouse.mousePress(event->localPos());
	if(event->button()& Qt::LeftButton){
		trackBall.updateRotation(mouse);
	} else if(event->button()& Qt::RightButton) {
		currentObject = scene->addObject("ufabc_blocoA");
		mouse.persistence = true;
		mouse.trackingMouse = true;
		this->setMouseTracking(true);
	} else if(event->button()& Qt::MiddleButton) {
		scene->fetchObject(currentObject).updateOrientation(mouse);
		/*scene->addObject("pig");*/
		/*scene->fetchObject(currentObject).moveObject(mouse, event->localPos());*/
	}

}

void OpenGLWidget::wheelEvent(QWheelEvent * event) {
    zoom += 0.001*event->delta();
	if(zoom<0.5)
		zoom = 0.5;
	else if(zoom>5)
		zoom = 5;
}

void OpenGLWidget::mouseReleaseEvent(QMouseEvent * event) {
	mouse.mouseRelease(event->localPos());
	if(event->button()== Qt::LeftButton)
		trackBall.updateRotation(mouse);
	else if(event->button()== Qt::MiddleButton)
		scene->fetchObject(currentObject).updateOrientation(mouse);
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
	else if(event->text()=="r")
		scene->fetchObject(currentObject).rotateObject(5.0f);
	else if(event->text()=="y")
		scene->fetchObject(currentObject).rotateObject(-5.0f);
	else if(event->text()=="f")
		scene->fetchObject(currentObject).moveObject(0.05,0,0);
	else if(event->text()=="h")
		scene->fetchObject(currentObject).moveObject(-0.05,0,0);
	else if(event->text()=="g")
		scene->fetchObject(currentObject).moveObject(0,0,0.05);
	else if(event->text()=="t")
		scene->fetchObject(currentObject).moveObject(0,0,-0.05);
	else if(event->text()=="1")
		currentObject = 2;
	else if(event->text()=="2")
		currentObject = 3;
	else if(event->text()=="3")
		currentObject = 4;
	else if(event->text()=="4")
		currentObject = 5;
	else if(event->text()=="5")
		currentObject = 6;
	else if(event->text()=="6")
		currentObject = 7;
	else if(event->text()=="7")
		currentObject = 8;
	else if(event->text()=="8")
		currentObject = 9;
	else if(event->text()=="9")
		currentObject = 10;

}

void OpenGLWidget::newGame()
{
	currentObject = scene->addObject("terrain");
	currentObject = scene->addObject("dome");
}
