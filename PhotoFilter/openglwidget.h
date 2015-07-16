#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLPaintDevice>
#include <QPainter>
#include <QFont>

#include <QWidget>
#include <QWindow>
#include <QSurfaceFormat>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QVector4D>
#include <QFileDialog>
#include <QImage>
#include <QRgb>
#include <QColor>
#include <QOpenGLTexture>
#include <QOpenGLFramebufferObject>
#include "fileoperationsfromresource.h"

#include <QtOpenGL>
#include <fstream>
#include <limits>
#include <iostream>

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:    
    explicit OpenGLWidget(QWidget *parent = 0);
    void destroyVBOs();
    void createVBOs();
    void createShaders();
    void destroyShaders();

    ~OpenGLWidget();
signals:
    void signalSendImage(QImage *img);
public slots:
    void slotRecvImage(QImage *img);
    void slotSendImage();
	void shaderChanged (int i);
protected:

    void initializeGL();
    void resizeGL(int width ,int height);
    void paintGL();

private:
    void paintImg(QImage *img);
    QOpenGLShader *vertexShader;
    QOpenGLShader *fragmentShader;
    QOpenGLShaderProgram *shaderProgram;    
    QOpenGLBuffer *vboIndices;
    QOpenGLBuffer *vboTextureCoordinate;
    QImage *imgOrig;
	unsigned int currentShader;
};

#endif // OPENGLWIDGET_H
