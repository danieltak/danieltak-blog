---
title: "Quebra de Texto num Widget de Table usando QWidget"
date: '2024-02-27T23:11:32-03:00'
# weight: 1
# aliases: ["/first"]
tags: ["Qt", "GUI", "Tabela"]
categorias: ["C++", "Qt", "Snippet"]
author: "danieltak"
# author: ["Me", "You"] # multiple authors
showToc: true
TocOpen: false
draft: false
hidemeta: false
comments: false
description: "Word Wrap no Table Widget do Qt"
disableHLJS: true # to disable highlightjs
disableShare: false
disableHLJS: false
hideSummary: false
searchHidden: false
ShowReadingTime: true
ShowBreadCrumbs: true
ShowPostNavLinks: true
ShowWordCount: true
ShowRssButtonInSectionTermList: true
UseHugoToc: true
cover:
    image: "<image path/url>" # image path/url
    alt: "<alt text>" # alt text
    caption: "<text>" # display caption under cover
    relative: false # when using page bundles set this to true
    hidden: true # only hide on current single page
editPost:
    URL: "https://github.com/danieltak/danieltak-blog/blob/master/content"
    Text: "Sugerir Alterações" # edit text
    appendFilePath: true # to append file path to Edit link
---

## Introdução

O word wrapping automático do Qt utilizando alguns flags funcionava corretamente na classe `QTableWidget`, porém outras propriedades não eram atendidas ao usar a classe padrão, para personalizar e contornar os delegates podem ser usados.

Pela minha experiência, o `QTableWidget` é muito limitado, para um widget tão complexo como a tabela, dificilmente você criará uma classe que atenderá à todos requisitos de tabelas de um projeto inteiro e eventualmente você precisará criar um delegate para implementar funcionalidades personalizadas.

A solução foi criar um `QStyledItemDelegate` e sobrecarregar a função sizeHint calculando o tamanho usando o tamanho da fonte e a largura de cada coluna.

## Flags

O [enum do Modo de Word Wrap][1] pode ser utilizado numa classe `QLabel`, em que as opções a seguir não funcionaram numa classe [QtableWidget][2], você pode adicionar um QLabel ao cellWidget de uma tabela, mas não é a maneira mais recomendada.


| Constante                                 | Valor | Descrição                                                                                                                                       |
|-------------------------------------------|-------|-------------------------------------------------------------------------------------------------------------------------------------------------|
| QTextOption::NoWrap                       | 0     | O texto não é quebrado automaticamente.                                                                                                         |
| QTextOption::WordWrap                     | 1     | O texto é quebrado nos limites das palavras.                                                                                                    |
| QTextOption::ManualWrap                   | 2     | O mesmo de QTextOption::NoWrap                                                                                                                  |
| QTextOption::WrapAnywhere                 | 3     | O texto pode ser quebrado em qualquer ponto de uma linha,   mesmo que ocorra no meio de uma palavra.                                            |
| QTextOption::WrapAtWordBoundaryOrAnywhere | 4     | Se possível, a quebra ocorre no limite de uma palavra;   caso contrário, ocorrerá no ponto apropriado da linha, mesmo no meio de uma   palavra. |

## Classe Padrão

Usando a função `setWordWrap( bool on )` da classe `QTableView`, isso é possível e a função `resizeRowsToContents()` é usada para redimensionar as linhas.

Um [exemplo de código][3] que exemplifica o problema pode ser visto no repositório do Github.

No código abaixo strings aleatórias são geradas num [QTableWidget][2] 5 x 5, com 8 palavras de contendo 5 letras, em cada célula da tabela.

```cpp
// Arquivo .cpp, os arquivos .h e .ui e o main podem ser vistos no exemplo de código completo
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
```

## Delegate

Um `delegate` é um tipo que representa referências a métodos com uma lista de parâmetros e um tipo de retorno específicos. Ao instanciar um `delegate`, você pode associar sua instância a qualquer método com uma assinatura e um tipo de retorno compatíveis. Você pode invocar (ou chamar) o método por meio da instância `delegate`.

Os `delegates` são usados para passar métodos como argumentos para outros métodos. Os manipuladores de eventos nada mais são do que métodos que são invocados por meio de `delegates`.

Qualquer método de qualquer classe ou estrutura acessível que corresponda ao tipo de `delegate` pode ser atribuído ao `delegate`. O método pode ser estático ou um método de instância. Essa flexibilidade significa que você pode alterar programaticamente as chamadas de método ou inserir novos códigos em classes existentes.

Essa capacidade de se referir a um método como parâmetro torna os `delegates` ideais para definir métodos de retorno de chamada. Você pode escrever um método que compare dois objetos em seu aplicativo. Esse método pode ser usado em um `delegate` para um algoritmo de classificação. Como o código de comparação é separado da biblioteca, o método de classificação pode ser mais geral.

### QAbstractItemDelegate

Um [QAbstractItemDelegate][5] fornece a interface e a funcionalidade comum para `delegates` na arquitetura de model/view. Os `delegates` exibem itens individuais em exibições e manipulam a edição de dados do modelo.

A classe [QAbstractItemDelegate][5] é uma das classes de [Model/View](https://doc.qt.io/qt-6/model-view-programming.html#model-view-classes) e faz parte da estrutura de [model/view](https://doc.qt.io/qt-6/model-view-programming.html) do Qt.

Para renderizar um item de forma personalizada, você deve reimplementar `paint()` e `sizeHint()`. A classe QStyledItemDelegate fornece implementações padrão para essas funções.

### Exemplo de Código

Muitas vezes você precisa controlar as cores, as bordas, as margens, entre outros parâmetros da tabela. Para realizar essa personalização, as funções padrões do Qt não atendem aos requisitos.

Portanto, é necessário criar classes de `Delegate` para os itens da tabela, ou seja, cada célula. Também para os itens de header, que não mostraremos nesse exemplo.

Ao modificar muito esse `delegate`, muitas vezes o wordp wrapping padrão não funcionará ou você necessita de margens personalizadas, o [exemplo de delegate][4] completo pode ser visto no repositório do Github.

Um loop for é usado para cortar a cadeia de caracteres e verificar a largura da cadeia de caracteres cortada usando a fonte atual; se for maior que a largura da coluna, ela será cortada na posição do último espaço.

Primeiro a classe MyTableDelegate é criada:

```cpp

// header

#ifndef MYTABLEDELEGATE_H
#define MYTABLEDELEGATE_H

#include <QPainter>
#include <QStyledItemDelegate>

class MyTableDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit MyTableDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const;

    virtual QSize sizeHint(const QStyleOptionViewItem &option,
                           const QModelIndex &index) const override;

signals:
};

#endif // MYTABLEDELEGATE_H

// CPP

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
    const int rowSpacing = 0;

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
```

E uma classe adapter do QTableWidget é criada com nome MyTable:

```cpp
// header
#ifndef MYTABLE_H
#define MYTABLE_H

#include <QTableWidget>

class MyTable : public QTableWidget
{
    Q_OBJECT
public:
    explicit MyTable(QWidget *parent = nullptr);

    QString GetRandomString() const;

    void PopulateDummyTable();

signals:
};

#endif // MYTABLE_H

// CPP

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
```

A Main Window:

```cpp
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
```

## Resultado

O resultado pode ser visto na figura abaixo, em que na esquerda a função do Word Wrap foi utilizada e na direita os `delegates`.

Com os `delegates` o espaçamento da margem ficou mais personalizado e menor, pois a variável `rowspacing` é igual a zero.

![Resultado](/posts/images/table-widget-word-wrap/Resultado.PNG)

## Referências

- [Wrap Mode Enum][1]

[1]: https://doc.qt.io/qt-6/qtextoption.html#WrapMode-enum

- [QTableWidget][2]

[2]: https://doc.qt.io/qt-6/qtablewidget.html

- [Exemplo QTableWidget][3]

[3]: https://github.com/danieltak/danieltak-blog/blob/master/exemplos/TableWordWrapProblem

- [Exemplo Delegate][4]

[4]: https://github.com/danieltak/danieltak-blog/blob/master/exemplos/TableWordWrap

- [QAbstractItemDelegate ][5]

[5]: https://doc.qt.io/qt-6/qabstractitemdelegate.html

