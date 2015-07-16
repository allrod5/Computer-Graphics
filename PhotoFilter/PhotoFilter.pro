#-------------------------------------------------
#
# Project created by QtCreator 2015-06-10T16:29:45
#
#-------------------------------------------------

QT       += core gui opengl multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = trabalhoFinal3dImageProcessing
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    openglwidget.cpp \
    fileoperationsfromresource.cpp \
    videosurface.cpp

HEADERS  += mainwindow.h \
    openglwidget.h \
    fileoperationsfromresource.h \
    videosurface.h

FORMS    += mainwindow.ui

RESOURCES += \
    shaders.qrc

DISTFILES += \
    shader.frag \
    shader.vert \
    ImageProcessingShader/shader.frag \
    ImageProcessingShader/shader.vert \
    edgedetection.frag \
    edgedetection.vert \
    billboard.frag \
    billboard.vert \
    gaussianblur.frag \
    gaussianblur.vert \
    gammacorrection.frag \
    gammacorrection.vert \
    multisampling.frag \
    multisampling.vert \
    bloom.frag \
    bloom.vert \
    fisheye.frag \
    fisheye.vert
