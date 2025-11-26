#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    myLogFunc( "My Message" );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::myLogFunc(QString qStr, const char *cFile, const int cLine)
{
    qInfo() << qStr << cFile << cLine;
}
