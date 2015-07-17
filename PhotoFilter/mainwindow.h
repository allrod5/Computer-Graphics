#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QDebug>
#include <QMediaPlayer>
#include <QVideoProbe>
#include <QVideoFrame>
#include <QGraphicsVideoItem>
#include <QVideoWidget>
#include <QColor>
#include <QPushButton>
#include <QGridLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QFrame>
#include <QMessageBox>
#include <QSlider>
#include "videosurface.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void slotOpenFile();
    void slotRecvImage(QImage *img);
	void shaderChanged(int i);
signals:
void signalSendImage(QImage *img);
private:
    Ui::MainWindow *ui;
    QMediaPlayer *qMediaPlayerPlayer;
};

#endif // MAINWINDOW_H
