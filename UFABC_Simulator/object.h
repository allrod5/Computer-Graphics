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
	void drawObject(Camera, Light, float, float, float, float, QQuaternion);
	void updateAspectRatio(int, int);

	void calculateNormals();
	void genTexCoordsCylinder();

	void destroyVBOs();
	void createVBOs();

	void createShaders();
	void destroyShaders();

private:
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
};

#endif // OBJECT_H
