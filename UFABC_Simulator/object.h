#ifndef OBJECT_H
#define OBJECT_H

//#include "openglwidget.h"
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QVector4D>
#include <QVector3D>
#include <QVector2D>
#include <QOpenGLShader>

#include <QtOpenGL>

#include "camera.h"
#include "light.h"
#include "material.h"
#include "mouse.h"

#include "QFile"

#include <iostream>

class Object
{
	QOpenGLBuffer * vbocoordText ;
	QOpenGLTexture * texture ;
	QOpenGLTexture * colorTexture;
	QOpenGLTexture * colorTextureLayer;
	QImage image ;

public:
	Object();
	~Object();

	void lockObject();
	void loadObject(QString);
	void drawObject(Camera, Light);
	void updateAspectRatio(int, int);
	//void constraintObject();
	void moveObject(float, float, float);
	void moveObject(Mouse&, Camera&, const QPointF&);
	void rotateObject(QVector3D, float);
	void rotateObject(QQuaternion&);
	void updateOrientation(Mouse&, const QPointF&);
	void mouseMove(Mouse&, Camera&, const QPointF&);

	void mousePress();
	int lockState();

	void calculateNormals();
	void genTexCoordsCylinder();

	void destroyVBOs();
	void createVBOs();

	void createShaders();
	void destroyShaders();

private:
	void loadProperties(QString);

	QOpenGLBuffer * vboVertices ;
	QOpenGLBuffer * vboIndices ;
	QOpenGLBuffer * vboColors ;

	QVector3D * normals ;
	QVector4D * vertices ;
	QVector4D * colors ;
	unsigned int * indices ;

	QOpenGLShader * vertexShader ;
	QOpenGLShader * fragmentShader ;
	QOpenGLShaderProgram * shaderProgram ;

	unsigned int numVertices ;
	unsigned int numFaces ;

	QMatrix4x4 modelView , projectionMatrix ;
	QVector3D midPoint ;
	double invDiag ;

	Material material;
	unsigned int currentShader;

	QVector2D * texCoords;

	float relX;
	float relY;
	float relZ;

	QPointF lastPoint;

	QQuaternion orientation;
	bool positionLock;
	bool orientationLock;
};

#endif // OBJECT_H
