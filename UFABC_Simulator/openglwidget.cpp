#include "openglwidget.h"

OpenGLWidget::OpenGLWidget(QWidget* parent): QOpenGLWidget(parent) {
	angx = angy = angz = 0;
	tx = ty = tz = 0;
	sc = 1;
    zoom = 0;
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
	/*glViewport(0, 0, w, h);
	projectionMatrix.setToIdentity();
	projectionMatrix.perspective(60.0, static_cast<qreal>(w)/static_cast<qreal>(h), 0.1, 20.0);
	trackBall.resizeViewport(w, h);
	update();*/
}

void OpenGLWidget::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene->drawScene(camera, light, zoom, camX, camY, camZ, trackBall.getRotation());
	update();
}

void OpenGLWidget::animate() {
	update();
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent * event) {
	trackBall.mouseMove(event->localPos());
}

void OpenGLWidget::mousePressEvent(QMouseEvent * event) {
	if(event->button()& Qt::LeftButton)
		trackBall.mousePress(event->localPos());
}

void OpenGLWidget::wheelEvent(QWheelEvent * event) {
    zoom += 0.001*event->delta();
}

void OpenGLWidget::mouseReleaseEvent(QMouseEvent * event) {
	if(event->button()== Qt::LeftButton)
		trackBall.mouseRelease(event->localPos());
}

void OpenGLWidget::keyPressEvent(QKeyEvent * event) {
	//std::cerr <<"Key pressed: "<< event->text().toStdString()<<"\n";
	if(event->text()=="w")
		camZ += 0.01;
	else if(event->text()=="s")
		camZ -= 0.01;
	else if(event->text()=="a")
		camX += 0.01;
	else if(event->text()=="d")
		camX -= 0.01;
}

void OpenGLWidget::addLUFABC()
{
	scene->addObject(0);
}

void OpenGLWidget::addRUFABC()
{
	scene->addObject(1);
}
