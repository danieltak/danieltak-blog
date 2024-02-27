#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "MyTable.h"

#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle( "Word Wrap Delegate" );

    MyTable *tableWidget = new MyTable ( ui->centralwidget );
    tableWidget->setRowCount( 5 );
    tableWidget->setColumnCount( 5 );
    tableWidget->setGeometry( 0, 0, 640, 480 );

    const int width = 100;
    for( int column = 0; column < tableWidget->columnCount(); column++ )
    {
        tableWidget->setColumnWidth(column, width);
        tableWidget->horizontalHeader()->resizeSection(column, width);
    }

    tableWidget->PopulateDummyTable();
}

MainWindow::~MainWindow()
{
    delete ui;
}
