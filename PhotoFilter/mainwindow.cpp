#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qMediaPlayerPlayer=new QMediaPlayer(this);
    VideoSurface *videoSurface= new VideoSurface;
    qMediaPlayerPlayer->setVideoOutput(videoSurface);

    QObject::connect(this,SIGNAL(signalSendImage(QImage *)),ui->openGLWidget,SLOT(slotRecvImage(QImage *)));
    QObject::connect(ui->openGLWidget,SIGNAL(signalSendImage(QImage *)),this,SLOT(slotRecvImage(QImage *)));
    QObject::connect(videoSurface, SIGNAL(signalSendImage(QImage *)),ui->openGLWidget,SLOT(slotRecvImage(QImage *)));



}
void MainWindow::slotRecvImage(QImage *img){
    QString arq=QFileDialog::getSaveFileName(this,tr("Open File"),"","png (*.png);;jpg (*.jpg)" );
    if(arq.size()>0){
        img->save(arq);
    }
    delete img;
}

void MainWindow::slotOpenFile(){
    QString arq=QFileDialog::getOpenFileName(this, tr("Open File"),"","png (*.png);;jpg (*.jpg);;mp4 (*.mp4);;webm (*.webm)");
    if(arq.size()>0){
        if(arq.right(3)=="jpg" || arq.right(3)=="png"){
            emit signalSendImage(new QImage (arq));
        }
        else{
            qMediaPlayerPlayer->setMedia(QUrl::fromLocalFile(arq));
            qMediaPlayerPlayer->play();

        }
    }


}
MainWindow::~MainWindow()
{
    delete ui;

}
