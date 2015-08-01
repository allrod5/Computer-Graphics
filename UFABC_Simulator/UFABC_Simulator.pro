#-------------------------------------------------
#
# Project created by QtCreator 2015-06-21T15:02:33
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UFABC_Simulator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    openglwidget.cpp \
    trackball.cpp \
    camera.cpp \
    light.cpp \
    material.cpp \
    object.cpp \
    scene.cpp \
    mouse.cpp

HEADERS  += mainwindow.h \
    openglwidget.h \
    trackball.h \
    camera.h \
    light.h \
    material.h \
    object.h \
    scene.h \
    mouse.h

FORMS    += mainwindow.ui

DISTFILES += \
    vshader1.glsl \
    fshader1.glsl \
    phong_vshader.glsl \
    phong_fshader.glsl \
    flat_vshader.glsl \
    flat_fshader.glsl \
    cartoon_fshader.glsl \
    cartoon_vshader.glsl \
    blinn-phong_vshader.glsl \
    blinn-phong_fshader.glsl \
    texture_fshader.glsl \
    texture_vshader.glsl

RESOURCES += \
    resources.qrc
