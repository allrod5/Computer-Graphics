#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	this->showFullScreen();
	setWindowFlags( Qt::FramelessWindowHint );
	this->layout()->setContentsMargins(0,0,0,0);
}

MainWindow::~MainWindow()
{
    delete ui;
}
