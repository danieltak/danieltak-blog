#include "MyTableDelegate.h"

#include <QApplication>
#include <QFontMetrics>
#include <QTableWidget>

MyTableDelegate::MyTableDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{}

void MyTableDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (true == index.isValid())
    {
        QStyleOptionViewItem itemOption(option);
        const QWidget *widget = option.widget;

        initStyleOption(&itemOption, index);


        QStyle *style = widget ? widget->style() : QApplication::style();

        style->drawControl(QStyle::CE_ItemViewItem,
                           &itemOption,
                           painter,
                           widget);
    }
}

QSize MyTableDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    int height = 0;
    int width = 0;
    const int rowSpacing = 5;

    if (true == index.isValid())
    {
        QString currentText = index.data().toString();
        QTableWidget* parent = static_cast<QTableWidget*> (this->parent());

        if (nullptr !=  parent)
        {
            QFontMetrics metrics(parent->font());
            int fontHeight = parent->font().pixelSize();

            if (true == currentText.isEmpty())
            {
                currentText = "H";
            }

            QSize textSize =  metrics.size(Qt::TextSingleLine, currentText);

            int textHeight = textSize.height();
            int textWidth  = textSize.width();
            width = parent->columnWidth(index.column());

            if  (true == parent->wordWrap()
                && ( width <= textWidth ) )
            {
                QString qStrSliced;
                int iStartPos = 0;
                int iLineCount = 1;

                for( int iChar = 0; iChar <= currentText.size(); iChar++ )
                {
                    qStrSliced = currentText.sliced( iStartPos, iChar - iStartPos );
                    int iSlicedWidth = metrics.size( Qt::TextSingleLine, qStrSliced ).width();
                    if( iSlicedWidth >= width )
                    {
                        int iLastSpacePos = iStartPos + qStrSliced.lastIndexOf( QChar::Space, -1 );
                        if ( iLastSpacePos > -1 )
                        {
                            iStartPos = iLastSpacePos;
                            iChar = iLastSpacePos;
                        }
                        else
                        {
                            iStartPos = iChar;
                        }
                        iLineCount++;
                    }
                    else if( true == qStrSliced.contains( QChar::LineFeed ) )
                    {
                        iLineCount++;
                        iStartPos = iChar;
                    }
                    else
                    {
                        //
                    }
                }

                height =  iLineCount * textHeight;
            }
            else
            {
                height = ( (currentText.count("\n") + 1) * fontHeight) + 2;
            }

            height +=  rowSpacing;
        }
    }

    return QSize(width, height);
}


