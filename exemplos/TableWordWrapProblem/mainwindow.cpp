#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QHeaderView>
#include <QTableWidget>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle( "Word Wrap Function" );

    QTableWidget *tableWidget = new QTableWidget (5, 5, ui->centralwidget);
    tableWidget->setGeometry( 0, 0, 640, 480 );
    tableWidget->setWordWrap(true);

    int width = 100;

    for( int row = 0; row < tableWidget->rowCount(); row++ )
    {
        for( int column = 0; column < tableWidget->columnCount(); column++ )
        {
            QString randomString = GetRandomString();

            QTableWidgetItem* tableItem = tableWidget->item( row, column );
            if( tableItem == nullptr )
            {
                tableItem = new QTableWidgetItem( randomString );
                tableWidget->setItem( row, column, tableItem );
            }
            else
            {
                tableItem->setText( randomString );
            }

            tableWidget->setColumnWidth(column, width);
            tableWidget->horizontalHeader()->resizeSection(column, width);
        }
    }

    tableWidget->resizeRowsToContents();

}

QString MainWindow::GetRandomString() const
{
    const QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
    const int randomWordLength = 5;
    const int randomWordCount = 8;

    QString randomString;
    for( int wordCount = 0; wordCount < randomWordCount; ++wordCount )
    {
        for( int wordLength = 0; wordLength < randomWordLength; ++wordLength )
        {
            int index = QRandomGenerator::global()->generate() % possibleCharacters.length();
            QChar nextChar = possibleCharacters.at(index);
            randomString.append(nextChar);
        }
        randomString.append(" ");
    }
    return randomString;
}

MainWindow::~MainWindow()
{
    delete ui;
}
