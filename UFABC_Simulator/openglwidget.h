#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QVector4D>
#include <QVector3D>
#include <QOpenGLShader>

#include <QtOpenGL>
#include <fstream>
#include <limits>
#include <iostream>

#include "camera.h"
#include "light.h"
#include "material.h"
#include "scene.h"
#include "object.h"
#include "mouse.h"

class OpenGLWidget : public QOpenGLWidget , protected
QOpenGLFunctions
{
    Q_OBJECT
	void mouseMoveEvent(QMouseEvent * event);
	void mousePressEvent(QMouseEvent * event);
	void mouseReleaseEvent(QMouseEvent * event);
	void wheelEvent(QWheelEvent * event);
	void keyPressEvent(QKeyEvent * event);

	QTimer timer;
	Mouse mouse;

protected :
	void initializeGL();
	void resizeGL(int width , int height);
	void paintGL();

private :
    Camera camera ;
    Light light;
	Scene *scene;

	QString selectedObject;
	unsigned int currentObject;
	QWidget *mainWindow;

public :
	explicit OpenGLWidget(QWidget * parent = 0);
	~OpenGLWidget();

    float angx, angy, angz, sc,tx, ty, tz;
    float zoom;
	float camX, camY, camZ;

	int viewportWidth;
	int viewportHeight;


signals :
	void statusBarMessage(QString ns);

public slots :
	void animate();

	void newGame();
};



# endif // OPENGLWIDGET_H
