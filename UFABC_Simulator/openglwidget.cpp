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
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	connect(&timer, SIGNAL(timeout()), this, SLOT(animate()));
	timer.start(25);
}

void OpenGLWidget::resizeGL(int w,int h) {
	glViewport(0, 0, w, h);
	scene->updateAspectRatio(w, h);
	mouse.resizeViewport(w, h);
	viewportWidth = w;
	viewportHeight = h;
	update();
}

void OpenGLWidget::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene->drawScene(camera, light);
	update();
}

void OpenGLWidget::animate() {
	update();
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent * event) {
	mouse.mouseMove(event->localPos());
	if(camera.isMoving())
		camera.mouseMove(mouse);
	scene->fetchCurrentObject().mouseMove(mouse, camera, event->localPos());

}

void OpenGLWidget::mousePressEvent(QMouseEvent * event) {
	mouse.mousePress(event->localPos());
	if(event->button()& Qt::LeftButton){
		camera.updateRotation(mouse);
		scene->fetchCurrentObject().mousePress();
	} else if(event->button()& Qt::RightButton) {
		if(scene->isPlacingObject()) {
			scene->removeLastObject();
		} else {
			scene->addObject(selectedObject, viewportWidth, viewportHeight);
			mouse.persistence = true;
			mouse.trackingMouse = true;
			this->setMouseTracking(true);
		}
		scene->fetchCurrentObject().mouseMove(mouse, camera, event->localPos());
	} else if(event->button()& Qt::MiddleButton) {
		camera.enableMovimentation(true);
		//scene->fetchObject(currentObject).updateOrientation(mouse);
		/*scene->addObject("pig", viewportWidth, viewportHeight);
		mouse.persistence = true;
		mouse.trackingMouse = true;
		this->setMouseTracking(true);*/
		/*scene->fetchObject(currentObject).moveObject(mouse, event->localPos());*/
	}

}

void OpenGLWidget::wheelEvent(QWheelEvent * event) {
	camera.updateZoom(0.001*event->delta());
}

void OpenGLWidget::mouseReleaseEvent(QMouseEvent * event) {
	mouse.mouseRelease(event->localPos());
	if(event->button()== Qt::LeftButton) {
		camera.updateRotation(mouse);
		scene->fetchCurrentObject().mousePress();
	} else if(event->button()== Qt::MiddleButton) {
		camera.enableMovimentation(false);
		//scene->fetchCurrentObject().updateOrientation(mouse, event->localPos());
	}
}

void OpenGLWidget::keyPressEvent(QKeyEvent * event) {
	/*if(event->text()=="w")
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
		scene->fetchObject(currentObject).moveObject(0,0,-0.05);*/
	if(event->text()=="0")
		selectedObject = "pig";
	else if(event->text()=="1")
		selectedObject = "ufabc_blocoA";
	else if(event->text()=="2")
		selectedObject = "ufabc_blocoB";
	else if(event->text()=="3")
		selectedObject = "";
	else if(event->text()=="4")
		selectedObject = "";
	else if(event->text()=="5")
		selectedObject = "";
	else if(event->text()=="6")
		selectedObject = "";
	else if(event->text()=="7")
		selectedObject = "";
	else if(event->text()=="8")
		selectedObject = "";
	else if(event->text()=="9")
		selectedObject = "";

}

void OpenGLWidget::newGame()
{
	scene->addAmbient("dome", viewportWidth, viewportHeight);
	scene->addTerrain("terrain", viewportWidth, viewportHeight);
}
