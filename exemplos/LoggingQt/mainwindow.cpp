#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qInfo() << "qInfo" << Qt::endl;

    qWarning() << "qWarning" << Qt::endl;

    qCritical() << "qCritical" << Qt::endl;

    //qFatal() << "qFatal" << Qt::endl;

    qDebug() << "qDebug" << Qt::endl;
}

MainWindow::~MainWindow()
{
    delete ui;
}
