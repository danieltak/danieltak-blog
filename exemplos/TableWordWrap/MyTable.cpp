#include "MyTable.h"

#include "MyTableDelegate.h"

#include <QRandomGenerator>

MyTable::MyTable(QWidget *parent)
    : QTableWidget{parent}
{
    this->setItemDelegate( new MyTableDelegate( this ) );
}

QString MyTable::GetRandomString() const
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

void MyTable::PopulateDummyTable()
{
    for( int row = 0; row < this->rowCount(); row++ )
    {
        for( int column = 0; column < this->columnCount(); column++ )
        {
            QString randomString = GetRandomString();

            QTableWidgetItem* tableItem = this->item( row, column );
            if( tableItem == nullptr )
            {
                tableItem = new QTableWidgetItem( randomString );
                this->setItem( row, column, tableItem );
            }
            else
            {
                tableItem->setText( randomString );
            }
        }
        this->setRowHeight( row, this->sizeHintForRow(row) );
    }
}
