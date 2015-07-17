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

void MainWindow::shaderChanged(int i)
{
	/*QLayoutItem *child;
	while ((child = ui->settingsLayout->takeAt(0)) != 0) {
		delete child;
	}*/

	//qDeleteAll(ui->settingsLayout->children());
	//delete ui->widget->layout();

	/*if (ui->settingsLayout->layout()) {
		for (int i = 0; i < ui->settingsLayout->layout()->count(); i++) {
			delete ui->settingsLayout->layout()->itemAt(i)->widget();
		}
	}*/

	QLayout *labels = ui->labelsLayout->layout();
	if (labels) {
		for (int i = 0; i < labels->count(); i++) {
			delete labels->itemAt(i)->widget();
		}
	}

	QLayout *sliders = ui->slidersLayout->layout();
	if (labels) {
		for (int i = 0; i < sliders->count(); i++) {
			delete sliders->itemAt(i)->widget();
		}
	}

	QSlider *Slider[3];
	QLabel *Label[3];
	switch(i){
		case 0:
			break;
		case 1:
			Label[0] = new QLabel;
			Slider[0] = new QSlider(Qt::Horizontal);

			Label[0]->setText("Threshold: ");
			ui->labelsLayout->addWidget(Label[0]);
			Slider[0]->setRange(0,100);
			connect(Slider[0], SIGNAL(valueChanged(int)), ui->openGLWidget, SLOT(setEdgeThreshold(int)));
			ui->slidersLayout->addWidget(Slider[0]);

			break;
		case 2:
			Label[0] = new QLabel;
			Slider[0] = new QSlider(Qt::Horizontal);

			Label[0]->setText("Blur Size: ");
			ui->labelsLayout->addWidget(Label[0]);
			Slider[0]->setRange(0,100);
			connect(Slider[0], SIGNAL(valueChanged(int)), ui->openGLWidget, SLOT(setBlurSize(int)));
			ui->slidersLayout->addWidget(Slider[0]);

			break;
		case 3:
			Label[0] = new QLabel;
			Label[1] = new QLabel;
			Slider[0] = new QSlider(Qt::Horizontal);
			Slider[1] = new QSlider(Qt::Horizontal);

			Label[0]->setText("Bloom Size: ");
			ui->labelsLayout->addWidget(Label[0]);
			Slider[0]->setRange(0,100);
			connect(Slider[0], SIGNAL(valueChanged(int)), ui->openGLWidget, SLOT(setBlurSize(int)));
			ui->slidersLayout->addWidget(Slider[0]);

			Label[1]->setText("Luminosity Threshold: ");
			ui->labelsLayout->addWidget(Label[1]);
			Slider[1]->setRange(0,99);
			connect(Slider[1], SIGNAL(valueChanged(int)), ui->openGLWidget, SLOT(setLuminosityThreshold(int)));
			ui->slidersLayout->addWidget(Slider[1]);

			break;
		case 4:
			Label[0] = new QLabel;
			Slider[0] = new QSlider(Qt::Horizontal);

			Label[0]->setText("Gamma: ");
			ui->labelsLayout->addWidget(Label[0]);
			Slider[0]->setRange(0,100);
			connect(Slider[0], SIGNAL(valueChanged(int)), ui->openGLWidget, SLOT(setGamma(int)));
			ui->slidersLayout->addWidget(Slider[0]);

			break;
		case 5:

			break;
		case 6:

			break;
		case 7:
			Label[0] = new QLabel;
			Slider[0] = new QSlider(Qt::Horizontal);

			Label[0]->setText("Grid Size: ");
			ui->labelsLayout->addWidget(Label[0]);
			Slider[0]->setRange(0,100);
			connect(Slider[0], SIGNAL(valueChanged(int)), ui->openGLWidget, SLOT(setBillboardGrid(int)));
			ui->slidersLayout->addWidget(Slider[0]);

			break;

	}
}
