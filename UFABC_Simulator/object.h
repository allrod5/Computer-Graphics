#ifndef OBJECT_H
#define OBJECT_H

#include "openglwidget.h"

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

	void loadObject(QString);
	void drawObject(Camera, Light, float, QQuaternion);
	void updateAspectRatio(int, int);
	//void constraintObject();
	void moveObject(float, float, float);
	void moveObject(Mouse&, const QPointF&);
	void rotateObject(float);
	void rotateObject(QQuaternion&);
	void updateOrientation(Mouse&);
	void mouseMove(Mouse&);

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

	QQuaternion orientation;
};

#endif // OBJECT_H
